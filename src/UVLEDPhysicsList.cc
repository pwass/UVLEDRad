
#include "UVLEDPhysicsList.hh"

#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4EmStandardPhysics.hh"
#include "G4SystemOfUnits.hh"


UVLEDPhysicsList::UVLEDPhysicsList() 
: G4VModularPhysicsList(){
  SetVerboseLevel(1);
  
  defaultCutValue = 0.1*mm;

  // Default physics
  RegisterPhysics(new G4DecayPhysics());

  // Radioactive decay
  RegisterPhysics(new G4RadioactiveDecayPhysics());

  // EM physics
  RegisterPhysics(new G4EmStandardPhysics());
}


UVLEDPhysicsList::~UVLEDPhysicsList()
{ 
}


void UVLEDPhysicsList::SetCuts()
{
  SetCutsWithDefault();
}  
