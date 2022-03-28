#include "run.hh"

MyRunAction::MyRunAction() {

}

MyRunAction::~MyRunAction() {

}

void MyRunAction::BeginOfRunAction(const G4Run* run) {
	G4AnalysisManager *man = G4AnalysisManager::Instance();
	
	man->OpenFile("output.root");
	
	man->CreateNtuple("Photons", "Photons");
	man->CreateNtupleIColumn("fEvent");
	man->CreateNtupleDColumn("fX");
	man->CreateNtupleDColumn("fY");
	man->CreateNtupleDColumn("fZ");
	man->CreateNtupleDColumn("fWlen");
	man->FinishNtuple(0);
	
	man->CreateNtuple("Hits", "Hits");
	man->CreateNtupleIColumn("fEvent");
	man->CreateNtupleDColumn("fX");
	man->CreateNtupleDColumn("fY");
	man->CreateNtupleDColumn("fZ");
	man->FinishNtuple(1);
	
	man->CreateNtuple("Scoring", "Scoring");
	man->CreateNtupleDColumn("fEdep");
	man->FinishNtuple(2);
	
	man->CreateH1("fEdep", "Energy Deposition", 100, 0.,  0.7*MeV);
} 

void MyRunAction::EndOfRunAction(const G4Run*) {
	G4AnalysisManager *man = G4AnalysisManager::Instance();
	
	man->Write();
	man->CloseFile();
} 
