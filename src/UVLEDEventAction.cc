
#include "UVLEDEventAction.hh"
#include "UVLEDRun.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"


UVLEDEventAction::UVLEDEventAction()
: G4UserEventAction(),
  fEdep(0.)
{} 

UVLEDEventAction::~UVLEDEventAction()
{}

void UVLEDEventAction::BeginOfEventAction(const G4Event*)
{    
  fEdep = 0.;
}

void UVLEDEventAction::EndOfEventAction(const G4Event*)
{   
  // Accumulate statistics in UVLEDRun
  UVLEDRun* run 
    = static_cast<UVLEDRun*>(
        G4RunManager::GetRunManager()->GetNonConstCurrentRun());
  run->AddEdep(fEdep);
}

