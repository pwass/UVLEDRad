
#ifndef UVLEDSteppingAction_h
#define UVLEDSteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

class UVLEDEventAction;

class G4LogicalVolume;


class UVLEDSteppingAction : public G4UserSteppingAction
{
  public:
    UVLEDSteppingAction(UVLEDEventAction* eventAction);
    virtual ~UVLEDSteppingAction();

    // method from the base class
    virtual void UserSteppingAction(const G4Step*);

  private:
    UVLEDEventAction*  fEventAction;
    G4LogicalVolume* fScoringVolume;
};

#endif
