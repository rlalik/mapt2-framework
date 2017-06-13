#include "CADPart.h"

CADPart::CADPart (bool drawable_)
: AbsPart(drawable_) {

}

void CADPart::Init (string path_, string material_, string color_)
{
    path = path_;
    materialName = material_;
    color = color_;

    material = new Material ();
    material->Init(materialName,1.0);

    //
    // create CAD part
    //
    //
    G4ThreeVector offset = G4ThreeVector(0*cm,0*cm,0*cm);                                                       // no offset
    CADMesh* mesh = new CADMesh((char*) path_.c_str(), "STL");                                                  // load mesh
    mesh->SetScale(mm);                                                                                         // set scale
    mesh->SetOffset(offset);                                                                                    // set offset
    mesh->SetReverse(false);                                                                                    // not reversed
    logical = new G4LogicalVolume(mesh->TessellatedMesh(), material->getMaterial(), "cad_logical", 0, 0, 0);    // create logical volume


    // create a drawable object with vertices
    if (drawable) {
        // get vertices and triangles
        G4TessellatedSolid* tessellated = dynamic_cast<G4TessellatedSolid*>(logical->GetSolid());
        int numberFacets = tessellated->GetNumberOfFacets ();

        G4VFacet* facet;
        for (int i=0; i<numberFacets;i++)
        {
            facet = tessellated->GetFacet(i);
            int numberVertices = facet->GetNumberOfVertices();
            std::vector<int> triangle;

            for (int j=0; j<numberVertices; j++)
            {
                G4ThreeVector v = facet->GetVertex(j);
                bool alreadyInserted = false;
                int pos = 0;
                for (int  x=0; x < vertices.size(); x++)
                {
                    if (vertices[x] == TVector3(v.x(),v.y(),v.z()) )
                    {
                        pos = x;
                        alreadyInserted = true;
                        continue;
                    }
                }
                if (alreadyInserted)
                {
                    triangle.push_back(pos);
                }
                else
                {
                    vertices.push_back(TVector3(v.x(),v.y(),v.z()));
                    triangle.push_back((int)vertices.size()-1);
                }
            }
            triangles.push_back(triangle);
        }
        numberTriangles = triangles.size();
        numberVertices = vertices.size();
    }
    else {
        numberTriangles = 0;
        numberVertices = 0;
    }
}
