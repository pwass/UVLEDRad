
#include "UVLEDSteppingAction.hh"
#include "UVLEDEventAction.hh"
#include "UVLEDDetectorConstruction.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"


UVLEDSteppingAction::UVLEDSteppingAction(UVLEDEventAction* eventAction)
: G4UserSteppingAction(),
  fEventAction(eventAction),
  fScoringVolume(0)
{}


UVLEDSteppingAction::~UVLEDSteppingAction()
{}


void UVLEDSteppingAction::UserSteppingAction(const G4Step* step)
{
  if (!fScoringVolume) { 
    const UVLEDDetectorConstruction* detectorConstruction
      = static_cast<const UVLEDDetectorConstruction*>
        (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    fScoringVolume = detectorConstruction->GetScoringVolume();   
  }

  // Get volume of the current step
  G4LogicalVolume* volume 
    = step->GetPreStepPoint()->GetTouchableHandle()
      ->GetVolume()->GetLogicalVolume();
      
  // Check if we are in scoring volume
  if (volume != fScoringVolume) return;

  // Collect energy deposited in this step
  G4double edepStep = step->GetTotalEnergyDeposit();
  fEventAction->AddEdep(edepStep);  
}

