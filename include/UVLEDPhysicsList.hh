
#ifndef UVLEDPhysicsList_h
#define UVLEDPhysicsList_h 1

#include "G4VModularPhysicsList.hh"


class UVLEDPhysicsList: public G4VModularPhysicsList
{
public:
  UVLEDPhysicsList();
  virtual ~UVLEDPhysicsList();

  virtual void SetCuts();
};


#endif