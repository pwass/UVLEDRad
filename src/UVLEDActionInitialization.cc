
#include "UVLEDActionInitialization.hh"
#include "UVLEDPrimaryGeneratorAction.hh"
#include "UVLEDRunAction.hh"
#include "UVLEDEventAction.hh"
#include "UVLEDSteppingAction.hh"

UVLEDActionInitialization::UVLEDActionInitialization()
 : G4VUserActionInitialization()
{}

UVLEDActionInitialization::~UVLEDActionInitialization()
{}

void UVLEDActionInitialization::BuildForMaster() const
{
  SetUserAction(new UVLEDRunAction);
}

void UVLEDActionInitialization::Build() const
{
  SetUserAction(new UVLEDPrimaryGeneratorAction);
  SetUserAction(new UVLEDRunAction);
  
  UVLEDEventAction* eventAction = new UVLEDEventAction;
  SetUserAction(eventAction);
  
  SetUserAction(new UVLEDSteppingAction(eventAction));
}  
