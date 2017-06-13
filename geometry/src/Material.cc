

#include "Material.h"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......



//
// Constructor
//
//
Material::Material()
{
  man = G4NistManager::Instance();
  density = 0;
  a_mass = 0;

  G4double z;
  G4double a;

  // define Elements
  a = 1.01*g/mole;
  elH  = new G4Element("Hydrogen","H" , z= 1., a);

  a = 12.01*g/mole;
  elC  = new G4Element("Carbon"  ,"C" , z= 6., a);

  a = 14.01*g/mole;
  elN  = new G4Element("Nitrogen","N" , z= 7., a);

  a = 16.00*g/mole;
  elO  = new G4Element("Oxygen"  ,"O" , z= 8., a);

  a = 28.09*g/mole;
  elSi  = new G4Element("Silicon"  ,"Si" , z= 14., a);

  G4double ncomponents;
  G4double fractionmass;
  G4Material* mat = new G4Material ("mat",1.19*g/cm3, 3);
  mat->AddElement(elC, 5);
  mat->AddElement(elO, 2);
  mat->AddElement(elH, 8);

  G4double d = 1.19*g/cm3;
  matPMMA = new G4Material("PMMA", 1.19*g/cm3, ncomponents=1);
  matPMMA->AddMaterial(mat, fractionmass=1);


}
//
//


//
// Destruktor
//
//
Material::~Material()
{
    delete material;

    delete elH;
    delete elC;
    delete elN;
    delete elO;
    delete MPT;
}

//


//
// Init
//
//
bool Material::Init (string material_, double kB)
{
   name = material_;
   kBFiber = kB;


  // evaluating string name and assign the right material to G4Material* material

  // vaccum
  if (name == "vacuum")
    {
       buildVacuum();
    }

  //aluminium
  else if (name == "aluminium")
    {
      buildAluminium();
    }

  //silicon
  else if (name == "silicon")
    {
      buildSilicon();
    }

  //copper
  else if (name == "copper")
    {
      buildCopper();
    }

  //steel
  else if (name == "steel")
    {
      buildSteel();
    }

  //Carbon
  else if (name == "carbon")
    {
      buildCarbon();
    }

  //Teflon
  else if (name == "teflon")
    {
      buildTeflon();
    }

  //Kapton
  else if (name == "kapton")
    {
      buildKapton();
    }

  //Polystyrene
  else if (name == "polystyrene")
    {
      buildPolystyrene();
    }

  //ABS
  else if (name == "ABS")
    {
      buildABS();
    }

  //PEEK
  else if (name == "PEEK")
    {
      buildPEEK();
    }

  //FR4
  else if (name == "FR4")
    {
      buildFR4();
    }

  //PMMA
  else if (name == "PMMA")
    {
      buildPMMA();
    }

  //EpoxySiPM
  else if (name == "EpoxySiPM")
    {
      buildEpoxySiPM();
    }

  //MLI
  else if (name == "MLI")
    {
      buildMLI();
    }

  //EpoxyEPOTEK
  else if (name == "EpoxyEPOTEK")
    {
      buildEpoxyEPOTEK();
    }

  //Polystyrene
  else if (name == "polystyrene")
    {
      buildPolystyrene();
    }

  else
    {
      return false;
    }

  return true;

}



//
// getMaterial ()
//
//

G4Material* Material::getMaterial()
{
  return material;
}





//
// Build Vaccum
//
//

void  Material::buildVacuum()
{
  material  =
     new G4Material("Vacuum",      //Name as String
	            1,		   //Atomic Number,  in this case we use 1 for hydrogen
                    1.008*g/mole,  //Mass per Mole "Atomic Weight"  1.008*g/mole for Hydoren
		    1.e-25*g/cm3,  //Density of Vaccuum  *Cant be Zero, Must be small insted
	            kStateGas,     //kStateGas for Gas
                    2.73*kelvin,   //Temperatuer for ga
		    1.e-25*g/cm3); //Pressure for Vaccum

}
//
//



//
// Build Aluminium
//
//

void  Material::buildAluminium()
{
  material  = man->FindOrBuildMaterial("G4_Al");

  // density_
  density_ = 2.70;
  Z = material->GetZ();
  A = material->GetA();
  radiationLength = 24.01;

  // read in the CSDA and stopping values
  stoppingPower = readNistTable("/nfs/hicran/project/e18sat/analysis/pStarStoppingTables/h_on_alu_pstar.txt");
  CSDARange = readNistTable("/nfs/hicran/project/e18sat/analysis/pStarStoppingTables/csdarange_h_on_alu.txt");
  CSDARangeInverse = readNistTableInverse("/nfs/hicran/project/e18sat/analysis/pStarStoppingTables/csdarange_h_on_alu.txt");
  detour = readNistTable("/nfs/hicran/project/e18sat/analysis/pStarStoppingTables/detourfactor_h_on_alu.txt");
}
//
//



//
// Build Silicon
//
//

void  Material::buildSilicon()
{
  material  = man->FindOrBuildMaterial("G4_Si");
}
//
//


//
// Build Copper
//
//

void  Material::buildCopper()
{
  material  = man->FindOrBuildMaterial("G4_Cu");
}
//
//


//
// Build Steel
//
//

void  Material::buildSteel()
{
  material  = man->FindOrBuildMaterial("G4_STAINLESS-STEEL");
}
//
//



//
// Build Carbon
//
//

void  Material::buildCarbon()
{
  material  = man->FindOrBuildMaterial("G4_C");
}
//
//




//
// Build Teflon
//
//

void  Material::buildTeflon()
{
  material  = man->FindOrBuildMaterial("G4_TEFLON");
}
//
//



//
// Build Kapton
//
//

void  Material::buildKapton()
{
  material  = man->FindOrBuildMaterial("G4_KAPTON");
}
//
//




//
// Build Polystyrene
//
//

void  Material::buildPolystyrene()
{
  material  = man->FindOrBuildMaterial("G4_POLYSTYRENE");

  // optical properties for fibers
  // entries in prperty tables
  const G4int numEntries = 4;

  //momentum of the photon
  G4double energies[numEntries] = {1*eV,2*eV,3*eV,4*eV};

  // Fastcomponent
  G4double fast[numEntries] = {0.000134, 0.004432, 0.053991,0.241971};

  // Slowcomponent
  G4double slow[numEntries] = { 0.000010, 0.000020, 0.000030, 0.004000};

  // Refraction index
  G4double rInedx[numEntries] = {1.59, 1.59,1.59, 1.59};

  //Absorption length
  G4double absLength[numEntries] = {5*cm, 5*cm, 5*cm, 5*cm};

  // material properties table
  MPT = new G4MaterialPropertiesTable();
  MPT->AddProperty("FASTCOMPONENT",energies,fast,numEntries);
  MPT->AddProperty("SLOWCOMPONENT",energies,slow,numEntries);
  MPT->AddProperty("RINDEX",energies,rInedx,numEntries);
  MPT->AddProperty("ABSLENGTH",energies,absLength,numEntries);

  MPT->AddConstProperty("SCINTILLATIONYIELD",8.00/keV);
  MPT->AddConstProperty("RESOLUTIONSCALE",1.0);
  MPT->AddConstProperty("FASTTIMECONSTANT", 45.*ns);
  MPT->AddConstProperty("SLOWTIMECONSTANT",50.*ns);
  MPT->AddConstProperty("YIELDRATIO",0.5);


  material->SetMaterialPropertiesTable(MPT);

  // Set the Birks Constant for the fiber  scintillator
  material->GetIonisation()->SetBirksConstant(kBFiber*mm/MeV);
  // material->GetIonisation()->SetBirksConstant(0.15*mm/MeV);

  // density_
  density_ = 1.060;
  // Z and A
  Z = 3.5;
  A = 6.5;
  radiationLength = 43.79;

  // read in the CSDA and stopping values
  stoppingPower = readNistTable("/nfs/hicran/project/e18sat/analysis/pStarStoppingTables/h_on_poly_pstar.txt");
  CSDARange = readNistTable("/nfs/hicran/project/e18sat/analysis/pStarStoppingTables/csdarange_h_on_poly.txt");
  CSDARangeInverse = readNistTableInverse("/nfs/hicran/project/e18sat/analysis/pStarStoppingTables/csdarange_h_on_poly.txt");
  detour = readNistTable("/nfs/hicran/project/e18sat/analysis/pStarStoppingTables/detourfactor_h_on_poly.txt");


}
//
//




//
// Build ABS low desity
//
//

void  Material::buildABS()
{

  G4double d;
  G4double ncomponents;
  G4double natoms;
  G4double fractionmass;


  G4Material* acrylnitril = new G4Material ("acrylnitril",0.80*g/cm3, 3);
  acrylnitril->AddElement(elC, 3);
  acrylnitril->AddElement(elN, 1);
  acrylnitril->AddElement(elH, 3);


  G4Material* butadien = new G4Material ("butadien",d = 2.4982*1000*g/m3, ncomponents=2);
  butadien->AddElement(elC,  4);
  butadien->AddElement(elH, 6);


  G4Material* styrol = new G4Material ("styrol",d = 0.91*g/cm3, ncomponents=2);
  styrol->AddElement(elC,  8);
  styrol->AddElement(elH, 8);


  density = 1.04*g/cm3;
  material = new G4Material(name="ABS", density, ncomponents=3);
  material->AddMaterial(acrylnitril, fractionmass=0.2);
  material->AddMaterial(butadien,    fractionmass=0.2);
  material->AddMaterial(styrol,      fractionmass=0.6);


}
//
//



//
// Build PEEK
//
//

void  Material::buildPEEK()
{
  G4double d;
  G4double ncomponents;
  G4double natoms;
  G4double fractionmass;

  density = 1.32*g/cm3;
  material = new G4Material (name="PEEK",density, ncomponents=3);
  material->AddElement(elC, natoms= 19);
  material->AddElement(elO, natoms= 3);
  material->AddElement(elH, natoms= 14);
}
//
//



//
// Build FR4
//
//

void  Material::buildFR4()
{

  G4double d;
  G4double ncomponents;
  G4double natoms;
  G4double fractionmass;

  G4Material* epoxy = new G4Material ("epoxy",1.2*g/cm3, 2);
  epoxy->AddElement(elC, 2);
  epoxy->AddElement(elH, 2);

  // G4Material* sio = man->FindOrBuildMaterial("G4_SILICON_DIOXIDE");
  G4Material* sio = new G4Material ("sio",2.2*g/cm3, 2);
  sio->AddElement(elSi, 1);
  sio->AddElement(elO, 2);


  density = 1.86*g/cm3;
  material = new G4Material(name="FR4", density, ncomponents=2);
  material->AddMaterial(epoxy, fractionmass=0.472);
  material->AddMaterial(sio,fractionmass=0.528);



}
//
//




//
// Build PMMA
//
//

void  Material::buildPMMA()
{

  G4double d;
  G4double ncomponents;
  G4double natoms;
  G4double fractionmass;


  // G4Material* mat = new G4Material ("mat",1.19*g/cm3, 3);
  // mat->AddElement(elC, 5);
  // mat->AddElement(elO, 2);
  // mat->AddElement(elH, 8);
  //
  // density = 1.19*g/cm3;
  // material = new G4Material(name="PMMA", density, ncomponents=1);
  // material->AddMaterial(mat, fractionmass=1);

  material = matPMMA;

  // density_
  density_ = 1.19;
  // Z and A
  Z = 3.6;
  A = 6.6;
  radiationLength = 40.55;

  // read in the CSDA and stopping values
  stoppingPower = readNistTable("/nfs/hicran/project/e18sat/analysis/pStarStoppingTables/h_on_poly_pstar.txt");
  CSDARange = readNistTable("/nfs/hicran/project/e18sat/analysis/pStarStoppingTables/csdarange_h_on_poly.txt");
  CSDARangeInverse = readNistTableInverse("/nfs/hicran/project/e18sat/analysis/pStarStoppingTables/csdarange_h_on_poly.txt");
  detour = readNistTable("/nfs/hicran/project/e18sat/analysis/pStarStoppingTables/detourfactor_h_on_poly.txt");

}
//
//




//
// Build EpoxySiPM
//
//

void  Material::buildEpoxySiPM()
{
  G4double d;
  G4double ncomponents;
  G4double natoms;
  G4double fractionmass;

  density = 1.2*g/cm3;

  G4Material* epoxy = new G4Material ("EpoxySiPM",1.2*g/cm3, 2);
  epoxy->AddElement(elC, 2);
  epoxy->AddElement(elH, 2);

  material = epoxy;

  // define optical properties
  G4MaterialPropertiesTable* material_mt = new G4MaterialPropertiesTable();
  G4double Energy[]    = { 12.4*eV };
  const G4int m_enum = sizeof(Energy)/sizeof(G4double);

  G4double RIND[]  = { 1.50 };
  assert(sizeof(RIND) == sizeof(Energy));

  material_mt->AddProperty("RINDEX",Energy,RIND,m_enum);

  material->SetMaterialPropertiesTable(material_mt);

}
//
//



//
// Build MLI
//
//

void  Material::buildMLI()
{
  G4double d;
  G4double ncomponents;
  G4double natoms;
  G4double fractionmass;

  // density and material composition

  density = 1.44*g/cm3;
  material = new G4Material (name="MLI",density, ncomponents=2);
  material->AddMaterial(man->FindOrBuildMaterial("G4_KAPTON"), fractionmass=0.95);
  material->AddMaterial(man->FindOrBuildMaterial("G4_Al"),     fractionmass=0.05);

}
//
//




//
// Build EpoxyEPOTEK
//
//

void  Material::buildEpoxyEPOTEK()
{
  G4double d;
  G4double ncomponents;
  G4double natoms;
  G4double fractionmass;


  // TO BE DEFINED
  density = 1.2*g/cm3;

  material  = new G4Material(name="EpoxyEPOTEK" , density, ncomponents=2);
  material->AddElement(elC, natoms= 2);
  material->AddElement(elH, natoms= 2);

  // define optical properties
  G4MaterialPropertiesTable* material_mt = new G4MaterialPropertiesTable();
  G4double Energy[]    = { 70.036*eV };
  const G4int m_enum = sizeof(Energy)/sizeof(G4double);

  G4double RIND[]  = { 1.519 };
  assert(sizeof(RIND) == sizeof(Energy));

  material_mt->AddProperty("RINDEX",Energy,RIND,m_enum);

  material->SetMaterialPropertiesTable(material_mt);
}
//
//




double Material::stoppingPowerEval (double e)
{
    double d = stoppingPower->Eval(e);
    if (d != d)
    {
        std::cerr << "[Error] in stoppingPowerEval: Eval == nan" << "\n";
        return 1;
    }
    return d;
}
double Material::CSDARangeEval (double e)
{
    double d = CSDARange->Eval(e);
    if (d != d)
    {
        std::cerr << "[Error] in CSDARangeEval: Eval == nan" << "\n";
        return 1;
    }
    return d;
}
double Material::CSDARangeInverseEval (double e)
{
    double d = CSDARangeInverse->Eval(e);
    if (d != d)
    {
        std::cerr << "[Error] in CSDARangeInverse: Eval == nan" << "\n";
        return 1;
    }
    return d;
}
double Material::detourEval (double e)
{
    double d = detour->Eval(e);
    if (d != d)
    {
        std::cerr << "[Error] in detour: Eval == nan" << "\n";
        return 1;
    }
    return d;
}



TSpline3* Material::readNistTable(const char* filename)
{
    ifstream fin;
    TSpline3* spline;
    TGraph *graph;
    Int_t noofpoints=0;
    fin.open(filename, ifstream::in);
    if (fin.is_open())
    {
    	//cout<<"opened file"<<endl;
    	string line;
    	while(getline(fin,line))
        {
    	       ++noofpoints;
    	}
    	const Int_t number_of_points = noofpoints;
    	Double_t points_x [number_of_points];
    	Double_t points_y [number_of_points];
    	string var1, var2;
    	Int_t pointnr=0;
    	fin.clear();
    	fin.seekg(0);
    	while(getline(fin,line))
        {
    		//cout << line <<endl;
    		var1 = line.substr(0,9);
    		var2 = line.substr(10,9);
    		//cout<<"energy: "<<var1<<" stoppingpower: "<<var2<<endl;
    		points_x[pointnr] = atof(var1.c_str());
    		points_y[pointnr] = atof(var2.c_str());
    		++pointnr;
    	}
    	graph = new TGraph(number_of_points,points_x,points_y);
    	spline = new TSpline3(filename,points_x,points_y,number_of_points,0,1E-3,1E4);
    	// std::cout << "READIN \n";
    }
    else
    {
    	//cout<<"Error opening file at "<<filename<<endl;
    	std::cout << "ERROR AT READIN \n";
    	graph = new TGraph();
    	spline = new TSpline3();
    }
    fin.close();
    return spline;
}


TSpline3 * Material::readNistTableInverse(const char* filename)
{
    ifstream fin;
    TSpline3* spline;
    TGraph *graph;
	Int_t noofpoints=0;
	fin.open(filename, ifstream::in);
	if (fin.is_open()){
		//cout<<"opened file"<<endl;
		string line;
		while(getline(fin,line)){
			++noofpoints;
		}

		const Int_t number_of_points = noofpoints;
		Double_t points_x [number_of_points];
		Double_t points_y [number_of_points];
		string var1, var2;
		Int_t pointnr=0;
		fin.clear();
		fin.seekg(0);
		while(getline(fin,line)){
			//cout << line <<endl;
			var1 = line.substr(0,9);
			var2 = line.substr(10,9);
			//cout<<"energy: "<<var1<<" stoppingpower: "<<var2<<endl;
			points_x[pointnr] = atof(var2.c_str());
			points_y[pointnr] = atof(var1.c_str());
			++pointnr;
		}
		graph = new TGraph(number_of_points,points_x,points_y);
		spline = new TSpline3(filename,graph,0,1E-3,1E4);
		// printf("READIN \n");

	}


	else {
		//cout<<"Error opening file at "<<filename<<endl;
		printf("ERROR AT READIN \n");
		graph = new TGraph();
		spline = new TSpline3();
	}

	fin.close();
	return spline;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
