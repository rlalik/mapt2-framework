#include "GeometryReadIn.h"

GeometryReadIn::GeometryReadIn (UserGeant4Geometry *geo, string filename_)
{
    geometry = geo;
    repeat = false;
    filename = filename_;
}


void GeometryReadIn::read ()
{
  // Check if file is there and open file
  datei.open(filename.c_str() ,std::fstream::in);
  if (datei.fail())
    {
      std::cout << "Could not open file " << filename;
      return;
    }
  string line = "";
  // Read file by line
  while (!datei.eof())
    {
       getline(datei,line);
       readline(line);
    }

  // Close stream
  datei.close ();
}



void GeometryReadIn::readline (string l)
{
  string line = l;

  if (line[0] == '#')
    {
      // Comment. Do nothing.
    }

  else if (line.find("Repeat") == 0)
    {
      // Since now, repeated CAD files -> other read in function
      repeat = true;
    }

  // Leerzeile ausschließen -> Zeile hat Komma
  else if (line.find("\"") != string::npos)
    {
      if (!repeat)
	     {
    	  string data  [4];
    	  unsigned int startpos = 0;
    	  unsigned int endpos = 0;

    	  for (int i = 0; i < 4; i++)
    	    {
    	      endpos = line.find(',',startpos+1);

    	      data[i] = line.substr(startpos,endpos);
    	      data[i] = data[i].substr(data[i].find('\"')+1,data[i].rfind('\"'));
    	      data[i].erase (data[i].find('\"'));
    	      startpos = endpos;
    	    }
    	    loadPart(data[0],data[1],data[2],data[3]);
	   }
      else
	     {
    	  string data  [6];
    	  unsigned int startpos = 0;
    	  unsigned int endpos = 0;

    	  for (int i = 0; i < 6; i++)
    	    {
    	      endpos = line.find(',',startpos+1);

    	      data[i] = line.substr(startpos,endpos);
    	      data[i] = data[i].substr(data[i].find('\"')+1,data[i].rfind('\"'));
    	      data[i].erase (data[i].find('\"'));
    	      startpos = endpos;
    	    }
            loadPart(data[0],data[1],data[2],data[3],data[4],data[5]);
	   }

    }
}



void GeometryReadIn::loadPart (string path_, string material_, string detector_, string color_)
{
    CADPart* part = new CADPart(geometry->getDrawable());
    part->Init(path_,material_,color_);
    geometry->addPart(part);
}

void GeometryReadIn::loadPart (string path_, string material_, string detector_, string color_, string start_, string end_)
{
    // start_ und end_ casting to int
    int start = 0;
    int end = 0;
    int detector = -1;
    stringstream convert_start(start_); // stringstream used for the conversion initialized with the contents of Text
    if ( !(convert_start >> start) )//give the value to start using the characters in the string
    {
        return; //if that fails return false
    }
    stringstream convert_end(end_); // stringstream used for the conversion initialized with the contents of Text

    if ( !(convert_end >> end) )//give the value to end using the characters in the string
    {
        return; //if that fails return false
    }

    stringstream convert_detector(detector_); // stringstream used for the conversion initialized with the contents of Text

    if ( !(convert_detector >> detector) )//give the value to end using the characters in the string
    {
        return; //if that fails return false
    }

    if (detector == 1) // fiber
    {
        // Iteration from start value to end value
        for (int i = start; i <= end; i++)
        {
            // cast int i to string to insert it in the file path
            string path = path_;
            string file_number = "";
            stringstream convert_i; // stringstream used for the conversion
            convert_i << i;//add the value of i to the characters in the stream
            file_number = convert_i.str();//set file_number to the content of the stream
            // insert file_number at right position in path -> right position: one charackter befor the " 10003_Core-1.STL"
            int position = path.find(" 10003_Core-1.STL");
            path.insert(position,file_number);


            CADFiber* part = new CADFiber(geometry->getDrawable());
            part->Init(path,material_,color_,i);

            // add part to geometry
            geometry->addPart(part);
        }
    }
    else    // normal CAD part
    {
        // Iteration from start value to end value
        for (int i = start; i <= end; i++)
        {
            // cast int i to string to insert it in the file path
            string path = path_;
            string file_number = "";
            stringstream convert_i; // stringstream used for the conversion
            convert_i << i;//add the value of i to the characters in the stream
            file_number = convert_i.str();//set file_number to the content of the stream
            // insert file_number at right position in path -> right position: one charackter after the "10100_FrameSciFi - ketek_pm3350-"
            int position = 0;
            if (path.find("ketek") != string::npos)
            {
                // it is a SiPM model
                position = 78;
            }
            else {
                // it is a wrapping or cladding
                position = 81;
            }
            path.insert(position,file_number);
            if (fileExist(path)){
                CADPart* part = new CADPart(geometry->getDrawable());
                part->Init(path,material_,color_);

                // add part to geometry
                geometry->addPart(part);
            }
        }
    }
}
