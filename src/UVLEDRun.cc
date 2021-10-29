
#include "UVLEDRun.hh"

UVLEDRun::UVLEDRun()
: G4Run(),
  fEdep(0.), 
  fEdep2(0.)
{} 

UVLEDRun::~UVLEDRun()
{} 


void UVLEDRun::Merge(const G4Run* run)
{
  const UVLEDRun* localRun = static_cast<const UVLEDRun*>(run);
  fEdep  += localRun->fEdep;
  fEdep2 += localRun->fEdep2;

  G4Run::Merge(run); 
} 


void UVLEDRun::AddEdep (G4double edep)
{
  fEdep  += edep;
  fEdep2 += edep*edep;
}



