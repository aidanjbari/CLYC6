#include "stepping.hh"

MySteppingAction::MySteppingAction(MyEventAction *eventAction) {
	fEventAction = eventAction;
}

MySteppingAction::~MySteppingAction() {

}

void MySteppingAction::UserSteppingAction(const G4Step *step) {
	G4Track *track = step->GetTrack();
	G4double energy = track->GetKineticEnergy();
	if (energy < 0.1) {
		track->SetTrackStatus(fStopAndKill);
		return;
	}
	/*G4LogicalVolume *volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
	
	const MyDetectorConstruction *detectorConstruction = static_cast<const MyDetectorConstruction*> (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
	
	G4LogicalVolume *fScoringVolume = detectorConstruction->GetScoringVolume();
	
	if(volume != fScoringVolume)
		return;*/
		
	G4double edep = step->GetTotalEnergyDeposit();
	fEventAction->AddEdep(edep);
}
