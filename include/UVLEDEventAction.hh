
#ifndef UVLEDEventAction_h
#define UVLEDEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"


class UVLEDEventAction : public G4UserEventAction
{
  public:
    UVLEDEventAction();
    virtual ~UVLEDEventAction();
    
    virtual void BeginOfEventAction(const G4Event* event);
    virtual void EndOfEventAction(const G4Event* event);

    void AddEdep(G4double edep) { fEdep += edep; }

  private:
    G4double  fEdep;
};


#endif

    
