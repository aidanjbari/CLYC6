#include "construction.hh"

//Website for refractive index : refractiveindex.info

MyDetectorConstruction::MyDetectorConstruction() {

}

MyDetectorConstruction::~MyDetectorConstruction() {

}

G4VPhysicalVolume* MyDetectorConstruction::Construct() {
	G4NistManager *nist = G4NistManager::Instance();
	G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");
	
	G4double worldEnergy[2] = {1.239841939*eV/0.2, 1.239841939*eV/0.9};
	G4double rindexWorld[2] = {1.0, 1.0};
	
	G4MaterialPropertiesTable *mptWorld = new G4MaterialPropertiesTable();
	mptWorld->AddProperty("RINDEX", worldEnergy, rindexWorld, 2);
	worldMat->SetMaterialPropertiesTable(mptWorld);
	
	G4Box *solidWorld = new G4Box("solidWorld", 0.5*m, 0.5*m, 0.5*m);
	G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
	G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), logicWorld, "physWorld", 0, false, 0, true);
	
	G4Material *Clyc6 = new G4Material("CLYC6", 3.31*g/cm3, 4);
	Clyc6->AddElement(nist->FindOrBuildElement("Cs"), 2);
	Clyc6->AddElement(nist->FindOrBuildElement("Y"), 1);
	Clyc6->AddElement(nist->FindOrBuildElement("Cl"), 6);
	
	G4Isotope *Li6 = new G4Isotope("Li6", 3, 6, 6.015122*g/mole);
	G4Isotope *Li7 = new G4Isotope("Li7", 3, 7, 7.016004*g/mole);
	G4Element *Li = new G4Element("Li", "Li", 2);
	Li->AddIsotope(Li6, 95.*perCent);
	Li->AddIsotope(Li7, 5.*perCent);
	Clyc6->AddElement(Li, 1);
	
	G4double rEnergy[1] = {3.06133809*eV};
	G4double rindexClyc6[1] = {1.81};
	G4double absLengthE[2] = {100000.*eV, 662000.*eV};
	G4double absLength[2] = {0.2519*cm, 3.9841*cm};
	G4double scintEnergy[1] = {3.350924*eV};
	G4double scintIntensity[1] = {1.0};
	
	G4MaterialPropertiesTable *mptClyc6 = new G4MaterialPropertiesTable();
	mptClyc6->AddProperty("SCINTILLATIONCOMPONENT1", scintEnergy, scintIntensity, 1);
	mptClyc6->AddProperty("RINDEX", rEnergy, rindexClyc6, 1);
	mptClyc6->AddProperty("ABSLENGTH", absLengthE, absLength, 1);
	mptClyc6->AddConstProperty("SCINTILLATIONYIELD", 20./keV);
	mptClyc6->AddConstProperty("RESOLUTIONSCALE", 1.0);
	mptClyc6->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 1.*ns);
	mptClyc6->AddConstProperty("SCINTILLATIONYIELD1", 1.0);
	Clyc6->SetMaterialPropertiesTable(mptClyc6);
	
	G4Tubs *solidClyc6 = new G4Tubs("solidClyc6", 0.*cm, 5.08*cm, 5.08*cm, 0.*deg, 360.*deg);
	logicClyc6 = new G4LogicalVolume(solidClyc6, Clyc6, "logicClyc6");
	fScoringVolume = logicClyc6;
	G4VPhysicalVolume *physClyc6 = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.3*m), logicClyc6, "physClyc6", logicWorld, false, 1, true);
	
	return physWorld;
}

void MyDetectorConstruction::ConstructSDandField() {
	MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");
	
	logicClyc6->SetSensitiveDetector(sensDet);
}
