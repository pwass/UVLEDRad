
#ifndef UVLEDDetectorConstruction_h
#define UVLEDDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4LogicalVolume;
class G4Material;
class G4Box;
class G4Tubs;
class G4Sphere;
class G4VPhysicalVolume;
class G4VRotationMatrix;
class G4Region;
class G4ProductionCuts;


class UVLEDDetectorConstruction : public G4VUserDetectorConstruction {

  public:
    
    UVLEDDetectorConstruction();
    ~UVLEDDetectorConstruction();      
    G4VPhysicalVolume* Construct();
    void UpdateGeometry();
    G4LogicalVolume* GetScoringVolume() const { return fScoringVolume; }

  private:
    
    G4VPhysicalVolume* ConstructExp();
    void DefineMaterials();    
    G4Material* copper;
    G4Material* aluminium;
    G4Material* Kapton;
    G4Material* silicon;
    G4Material* siliconeResin;
    G4Material* Air;
    G4Material* Quartz;
    G4Material* GaN;
    
    protected:
    G4LogicalVolume*  fScoringVolume;
    
};

#endif

