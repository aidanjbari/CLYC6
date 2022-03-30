#include "detector.hh"

MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name) {

}

MySensitiveDetector::~MySensitiveDetector() {

}

G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist) {
	G4Track *track = aStep->GetTrack();
	
	G4double eDep = track->GetVertexKineticEnergy();
	
	G4AnalysisManager *man = G4AnalysisManager::Instance();
		
	G4LogicalVolume *volume = aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
	
	const MyDetectorConstruction *detectorConstruction = static_cast<const MyDetectorConstruction*> (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
	
	G4LogicalVolume *fScoringVolume = detectorConstruction->GetScoringVolume();
	
	if(volume != fScoringVolume)
		return true;
	
	if(eDep > 0.001) {
		man->FillNtupleDColumn(0, 0, eDep);
		man->AddNtupleRow(0);
		man->FillH1(0, eDep);
	}
	
	return true;
}
