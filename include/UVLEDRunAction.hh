
#ifndef UVLEDRunAction_h
#define UVLEDRunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

class G4Run;
class G4LogicalVolume;

class UVLEDRunAction : public G4UserRunAction
{
  public:
    UVLEDRunAction();
    virtual ~UVLEDRunAction();

    virtual G4Run* GenerateRun();
    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);
};

#endif

