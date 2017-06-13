
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <limits>
#include <fstream>

#include "trianglemesh.h"


// read triangles from STL-file
void TTriangleMesh::ReadFile(const char *filename, int sldindex, char name[80]){
	// printf("Reading 001");
	std::ifstream f(filename, std::fstream::binary);
    if (f.is_open()){
        char header[80];
        unsigned int filefacecount, i;
        f.read((char*)header,80);   // read header
        for (i = 79; i >= 0; i--){
            if (header[i] == ' ') header[i] = 0;    // trim trailing whitespaces
            else break;
        }
        if (name) memcpy(name,header,80);
        f.read((char*)&filefacecount,4);
        // printf("Reading '%.80s' from '%s' containing %u triangles ... ",header,filename,filefacecount);    // print header

        for (i = 0; i < filefacecount && !f.eof(); i++){
            f.seekg(3*4,std::fstream::cur);  // skip normal in STL-file (will be calculated from vertices)
            float v[3][3];
            for (short j = 0; j < 3; j++){
                 f.read((char*)v[j],12);
            }
            f.seekg(2,std::fstream::cur);    // 2 attribute bytes, not used in the STL standard (http://www.ennex.com/~fabbers/StL.asp)
            triangles.push_back(TTriangle(CPoint(v[0][0], v[0][1], v[0][2]),
            							  CPoint(v[1][0], v[1][1], v[1][2]),
            							  CPoint(v[2][0], v[2][1], v[2][2]), sldindex));
        }
        f.close();
        // printf("Read %u triangles\n",i);
    }
    else{
        printf("Could not open '%s'!\n",filename);
        std::exit(-1);
    }
}

// build search tree
void TTriangleMesh::Init(){
	tree.rebuild(triangles.begin(), triangles.end());
	printf("Edges are (%f %f %f),(%f %f %f)\n",tree.bbox().min(0),tree.bbox().min(1),tree.bbox().min(2),
												tree.bbox().max(0),tree.bbox().max(1),tree.bbox().max(2));  // print the size of the root node
}

// test segment p1->p2 for collision with triangles and return a list of all found collisions
bool TTriangleMesh::Collision(const double p1[3], const double p2[3], std::set<TCollision> &colls){
	CPoint point1(p1[0], p1[1], p1[2]);
	CPoint point2(p2[0], p2[1], p2[2]);
	CSegment segment(point1, point2);

	std::list<CIntersection> out;
	tree.all_intersections(segment, std::back_inserter(out));
	for (std::list<CIntersection>::iterator i = out.begin(); i != out.end(); i++){
		if (*i){
#if CGAL_VERSION_NR<1040301000
			const CPoint *collp = CGAL::object_cast<CPoint>(&(*i)->first);
#else
			CPoint *collp = boost::get<CPoint>(&((*i)->first));
#endif
			if (collp){
				TCollision coll;
				coll.s = sqrt((*collp - point1).squared_length()/segment.squared_length());
				CIterator tri = (*i)->second;
				coll.sldindex = tri->sldindex;
				CVector n = tri->normal();
				coll.normal[0] = n[0];
				coll.normal[1] = n[1];
				coll.normal[2] = n[2];
				coll.distnormal = segment.to_vector()*n;
				colls.insert(coll);
			}
		}
	}
	return !(colls.empty());
}


int TTriangleMesh::nextIntersection(TVector3 startPoint, TVector3 direction, TVector3 &newPIn, TVector3 &newPOut, int &volumeIndex)
{
	direction.SetMag(1);
	startPoint = startPoint - 0.00005 * direction;
	CPoint point1(startPoint.x(), startPoint.y(), startPoint.z());
	direction = startPoint + 200 * direction;
	CPoint point2(direction.x(), direction.y(), direction.z());
	CSegment segment(point1, point2);

	std::set<TCollision2> colls;
	std::list<CIntersection> out;
	tree.all_intersections(segment, std::back_inserter(out));
	for (std::list<CIntersection>::iterator i = out.begin(); i != out.end(); i++){
		if (*i){
			#if CGAL_VERSION_NR<1040301000
			const CPoint *collp = CGAL::object_cast<CPoint>(&(*i)->first);
			#else
			CPoint *collp = boost::get<CPoint>(&((*i)->first));
			#endif
			if (collp){
				TCollision2 coll;
				coll.s = sqrt((*collp - point1).squared_length()/segment.squared_length());
				CIterator tri = (*i)->second;
				coll.sldindex = tri->sldindex;
				coll.point = *collp;
				CVector n = tri->normal();
				if (segment.to_vector()*n > 0)
					coll.entry = false;
				else
					coll.entry = true;
				colls.insert(coll);
			}
		}
	}
	// check number of collisions
	switch (colls.size())
	{
	case 0:
		std::cout << "0 intersections -> out of world" << "\n";
		return 0;
		break;
	case 1:
		std::cout << "1 intersections -> Error" << "\n";
		return -1;
		break;
	default:
		// more than 1 intersections -> take first two
		std::set<TCollision2>::iterator it;
		it = colls.begin();
		// if first intersection is an exit point -> it is the startPoint again -> skip it
		if(!it->entry)
			advance(it,1);
		int index = it->sldindex;
		CPoint pIn = it->point;
		advance(it,1);
		if (index != it->sldindex)
		{
			std::cerr << "Error in nextIntersection: volume index not the same: " << index << "\n";
			std::cerr << "\n\n" << "\nPrint colls: \n";
			for(auto f : colls) {
				std::cerr << f.sldindex << "(" << f.entry << ")" <<  " with s: " << f.s << "\n";
			}
			return -1;
		}
		volumeIndex = index;
		CPoint pOut = it->point;
		newPIn = TVector3 (pIn.x(),pIn.y(),pIn.z());
		newPOut = TVector3 (pOut.x(),pOut.y(),pOut.z());
		return 1;
		break;
	}


}




int TTriangleMesh::nextIntersection2(TVector3 startPoint, TVector3 direction, TVector3 &newPIn, TVector3 &newPOut, int &volumeIndex)
{
	direction.SetMag(1);
	startPoint = startPoint - 0.0000001 * direction;
	CPoint point1(startPoint.x(), startPoint.y(), startPoint.z());
	TVector3 p2 = startPoint + 3 * direction;
	CPoint point2(p2.x(), p2.y(), p2.z());
	CSegment segment(point1, point2);

	int counter = 1;
	while ((tree.number_of_intersected_primitives(segment) < 4) && (counter < 15))
	{
		counter++;
		p2 = startPoint + counter*counter * direction;
		point2 = CPoint (p2.x(), p2.y(), p2.z());
		segment = CSegment(point1, point2);
	}
	if (counter >= 100)
	{
		// particle left world
		// std::cout << "left world 1" << "\n";
		return 0; // left world
	}

	std::set<TCollision2> colls;
	std::list<CIntersection> out;
	tree.all_intersections(segment, std::back_inserter(out));
	for (std::list<CIntersection>::iterator i = out.begin(); i != out.end(); i++){
		if (*i){
			CPoint *collp = boost::get<CPoint>(&((*i)->first));
			if (collp){
				TCollision2 coll;
				coll.s = sqrt((*collp - point1).squared_length()); // /segment.squared_length());
				CIterator tri = (*i)->second;
				coll.sldindex = tri->sldindex;
				coll.point = *collp;
				CVector n = tri->normal();
				if (segment.to_vector()*n > 0)
					coll.entry = false;
				else
					coll.entry = true;
				colls.insert(coll);
			}
		}
	}
	// std::cout << "coll size " << colls.size() << "\n";
	// check number of collisions
	switch (colls.size())
	{
	case 0:
		std::cout << "0 intersections -> out of world" << "\n";
		return 0;
		break;
	case 1:
	case 2:
		std::cout << "< 2 intersections -> Error" << "\n";
		return -1;
		break;
	default:
		// more than 2 intersections
		std::set<TCollision2>::iterator it;
		it = colls.begin();
		// if first intersection is an exit point -> it is the startPoint again -> skip it
		// std::cout << it->entry << "\n";
		if(!it->entry)
			advance(it,1);
		int index = it->sldindex;
		CPoint pIn = it->point;
		advance(it,1);
		// std::cout << it->entry << "\n";
		if (index != it->sldindex)
		{
			// PROBLEM
			std::cerr << "Error in nextIntersection2: volume index not the same: " << index << " : " << it->sldindex << " / coll size: "<< colls.size() << "\n";
			// std::cerr << "\n" << "\nPrint colls: \n";
			// for(auto f : colls) {
			// 	std::cerr << f.sldindex << "(" << f.entry << ")" <<  " with s: " << f.s << "\n";
			// }
			return -1;
		}
		volumeIndex = index;
		CPoint pOut = it->point;
		newPIn = TVector3 (pIn.x(),pIn.y(),pIn.z());
		newPOut = TVector3 (pOut.x(),pOut.y(),pOut.z());
		// std::cout << "\n\n" << index << " with length in volume: " << (newPOut-newPIn).getMag() << "\n";
		// newPIn.print();
		// newPOut.print();
		return 1;
		break;
	}
}



int TTriangleMesh::nextIntersection3(TVector3 startPoint, TVector3 direction, TVector3 &newPIn, TVector3 &newPOut, int &volumeIndex)
{
	direction.SetMag(1);
	CPoint startCP (startPoint.x(),startPoint.y(),startPoint.z());

	double segmentLength = 1.5;
	TVector3 p1;
	TVector3 p2 = startPoint;
	std::set<TCollision2> colls;
	CSegment segment;
	CPoint point1;
	CPoint point2;

	while (true)
	{
	int counter = 0;
	bool found = false;
	do
	{
		p1 = p2;
		p2 = p2 + (counter+1) * segmentLength * direction;
		point1 = CPoint(p1.x(), p1.y(), p1.z());
		point2 = CPoint(p2.x(), p2.y(), p2.z());
		segment = CSegment(point1, point2);
		counter++;

	} while ((!tree.do_intersect(segment)) || (counter > 200/segmentLength));

	if (counter > 200/segmentLength)
	{
		// nothing found any more -> out of world
		std::cerr << "Warning in nextIntersection2: counter > 200/segmentLength" << "\n";
		std::cout << "0 intersections -> out of world" << "\n";
		return 0;

	}

	// find all collisions for this segment
	std::list<CIntersection> out;
	tree.all_intersections(segment, std::back_inserter(out));
	for (std::list<CIntersection>::iterator i = out.begin(); i != out.end(); i++){
		if (*i){
			CPoint *collp = boost::get<CPoint>(&((*i)->first));
			if (collp){
				TCollision2 coll;
				coll.s = sqrt((*collp - startCP).squared_length());
				CIterator tri = (*i)->second;
				coll.sldindex = tri->sldindex;
				coll.point = *collp;
				CVector n = tri->normal();
				if (segment.to_vector()*n > 0)
					coll.entry = false;
				else
					coll.entry = true;
				colls.insert(coll);
			}
		}
	}



	// check number of collisions
	switch (colls.size())
	{
	case 0:
		std::cerr << "Error in nextIntersection3: 0 interesctions in set" << "\n";
		return -1;
		break;
	case 1:
		{
		// one intersection in set -> test the next segments
		// shift start point for next segment
		p2 = p2 + 0.00001 * direction;
		break;
		}
	default:
		// more than 1 intersections -> take first two
		std::set<TCollision2>::iterator it;
		it = colls.begin();
		int index = it->sldindex;
		CPoint pIn = it->point;
		advance(it,1);
		if (index != it->sldindex)
		{
			// PROBLEM -> from multiple scattering
			std::cerr << "Error in nextIntersection3: volume index not the same: " << index << " : " << it->sldindex << " / coll size: "<< colls.size() << "\n";
			std::cerr << "\n\n" << "\nPrint colls: \n";
			for(auto f : colls) {
				std::cerr << f.sldindex << " with s: " << f.s << "\n";
				TVector3 p (f.point.x(),f.point.y(),f.point.z());
				p.Print();
			}
			return -1;
		}
		volumeIndex = index;
		CPoint pOut = it->point;
		newPIn = TVector3 (pIn.x(),pIn.y(),pIn.z());
		newPOut = TVector3 (pOut.x(),pOut.y(),pOut.z());
		return 1;
		break;
	}
	}
	std::cerr << "Error in nextIntersection3: while" << "\n";
}
