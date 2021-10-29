
#include "G4RunManager.hh"
#include "G4ScoringManager.hh"
#include "G4UImanager.hh"
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#include "UVLEDDetectorConstruction.hh"
#include "UVLEDPhysicsList.hh"
#include "UVLEDActionInitialization.hh"

#include "Randomize.hh"
#include <vector>


int main(int argc, char** argv) {

  // choose the Random engine
  CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine);
  
  // Construct the default run manager
  G4RunManager * runManager = new G4RunManager;
  
  // Activate command-based scorer
  G4ScoringManager::GetScoringManager();

  // set mandatory initialization classes
  runManager->SetUserInitialization(new UVLEDDetectorConstruction);
  runManager->SetUserInitialization(new UVLEDPhysicsList);
  
  // User action initialization
  runManager->SetUserInitialization(new UVLEDActionInitialization());

  
  //Initialize G4 kernel
  runManager->Initialize();
    
  
  // Get the pointer to the User Interface manager.
  G4UImanager * UI = G4UImanager::GetUIpointer();

  // Batch mode.
  if (argc!=1)
    {
     G4String command = "/control/execute ";
     G4String fileName = argv[1];
     UI->ApplyCommand(command+fileName);
    }    
  // Interactive mode : define visualization and UI terminal.
  else
    { 
#ifdef G4VIS_USE
      G4VisManager* visManager = new G4VisExecutive;
      visManager->Initialize();
#endif    
     
      G4UIsession * session = 0;
#ifdef G4UI_USE_TCSH
      session = new G4UIterminal(new G4UItcsh);      
#else
      session = new G4UIterminal();
#endif
#ifdef G4VIS_USE
      UI->ApplyCommand("/control/execute default.mac");     
#endif
      session->SessionStart();
      delete session;
     
#ifdef G4VIS_USE
      delete visManager;
#endif     
    }    

  delete runManager;

  return 0;
}

