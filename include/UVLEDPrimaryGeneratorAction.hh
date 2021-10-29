
#ifndef UVLEDPrimaryGeneratorAction_h
#define UVLEDPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"

class G4Event;

class UVLEDPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    UVLEDPrimaryGeneratorAction();    
   ~UVLEDPrimaryGeneratorAction();

  public:
    virtual void GeneratePrimaries(G4Event*);
    const G4ParticleGun* GetParticleGun() const { return fParticleGun; }
            
  private:
    G4ParticleGun*  fParticleGun;
};

#endif
