

#ifndef UVLEDActionInitialization_h
#define UVLEDActionInitialization_h 1

#include "G4VUserActionInitialization.hh"


class UVLEDActionInitialization : public G4VUserActionInitialization
{
  public:
    UVLEDActionInitialization();
    virtual ~UVLEDActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;
};

#endif

    
