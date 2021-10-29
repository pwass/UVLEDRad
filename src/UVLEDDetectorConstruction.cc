
#include "UVLEDDetectorConstruction.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4RunManager.hh"
#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

#include "G4SDManager.hh"

#include "G4Region.hh"
#include "G4RegionStore.hh"
#include "G4ProductionCuts.hh"

#include "G4UnitsTable.hh"
#include "globals.hh"

#include "G4Element.hh"
#include "G4Isotope.hh"
#include "G4ElementTable.hh"
#include "G4Material.hh"
#include "G4MaterialTable.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Sphere.hh"

#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"

#include "G4UnionSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4PVReplica.hh"

#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4VPhysicalVolume.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

// Alpha values can also be added.
#define white   G4Colour(1.0, 1.0, 1.0, 0.6)
#define grey    G4Colour(0.5, 0.5, 0.5, 0.6)
#define red     G4Colour(1.0, 0.0, 0.0)
#define blue    G4Colour(0.0, 0.0, 1.0)
#define lblue   G4Colour(0.5, .75, .85)
#define cyan    G4Colour(0.0, 1.0, 1.0)
#define magenta G4Colour(1.0, 0.0, 1.0) 
#define yellow  G4Colour(1.0, 1.0, 0.0)
#define lyellow G4Colour(0.941, 0.902, 0.549)
#define black   G4Colour(0.0, 0.0, 0.0)
#define green   G4Colour(0.0, 1.0, 0.0)
#define orange  G4Colour(1.0, 0.5, 0.0)
#define purple  G4Colour(0.6, .33, .65) 

UVLEDDetectorConstruction::UVLEDDetectorConstruction()
: G4VUserDetectorConstruction(),
  fScoringVolume(0)
{
  
  DefineMaterials();

}

UVLEDDetectorConstruction::~UVLEDDetectorConstruction()
{ }

G4VPhysicalVolume* UVLEDDetectorConstruction::Construct() {
 
 return ConstructExp();

}

void UVLEDDetectorConstruction::DefineMaterials()
{
  // Define elements
  G4Element* elementH  = new G4Element("Hydrogen",  "H",  1., 1.00794*g/mole);
  G4Element* elementC  = new G4Element("Carbon",    "C",  6., 12.0107*g/mole);
  G4Element* elementN  = new G4Element("Nitrogen",  "N",  7., 14.0067*g/mole);
  G4Element* elementO  = new G4Element("Oxygen",    "O",  8., 15.9994*g/mole);
  G4Element* elementAl = new G4Element("Aluminium", "Al", 13., 26.9815*g/mole);
  G4Element* elementSi = new G4Element("Silicon",   "Si", 14., 28.0855*g/mole);
  G4Element* elementCu = new G4Element("Copper",    "Cu", 29.,  63.546*g/mole);
  G4Element* elementGa = new G4Element("Gallium",   "Ga", 31.,  69.723*g/mole);
  
  // Define materials
  // Aluminium
  aluminium = new G4Material("aluminium", 2.70*g/cm3, 1);
  aluminium->AddElement(elementAl, 1.00);
  
  // Quartz
  // Assume lens is made from fused quartz.
  Quartz = new G4Material("Quartz", 2.200*g/cm3, 2);
  Quartz->AddElement(elementSi, 1) ;
  Quartz->AddElement(elementO, 2) ;
  
  // Gallium Nitride
  // Assume LED die is made from GaN.
  GaN = new G4Material("Gallium Nitride", 6.15*g/cm3, 2);
  GaN->AddElement(elementN,  2);
  GaN->AddElement(elementGa,  1);

  // Copper
  copper = new G4Material("copper", 8.92*g/cm3, 1);
  copper->AddElement(elementCu, 1.00);

  // Silicon
  silicon = new G4Material("silicon", 2.33*g/cm3, 1);
  silicon->AddElement(elementSi, 1.00);
  
  // Kapton
  Kapton = new G4Material("Kapton", 1.43*g/cm3, 4);
  Kapton -> AddElement(elementH, 10);
  Kapton -> AddElement(elementO,  5);
  Kapton -> AddElement(elementC, 22);
  Kapton -> AddElement(elementN,  2);
   
  // Silicone Resin (Best Guess!)
  siliconeResin = new G4Material("Silicone Resin", 1.01*g/cm3, 4);
  siliconeResin->AddElement(elementO, 6);
  siliconeResin->AddElement(elementH, 4);
  siliconeResin->AddElement(elementC, 2);
  siliconeResin->AddElement(elementSi, 2);
       
  //Air   
  Air = new G4Material("Air", 1.290*mg/cm3, 2);
  Air->AddElement(elementN, 70.0*perCent);
  Air->AddElement(elementO, 30.0*perCent);   

}

G4VPhysicalVolume* UVLEDDetectorConstruction::ConstructExp(){

  //--------------------------------------------------------------------------
  //World
  //-------------------------------------------------------------------------

  G4Box* wld_sol  = new G4Box("World", 5.0*m, 5.0*m, 5.0*m);
	 
  G4LogicalVolume* wld_log  = new G4LogicalVolume(wld_sol, Air, "wld_log");
		   
  G4VPhysicalVolume* wld_phys = new G4PVPlacement(0, G4ThreeVector(), "wld_phys", wld_log, NULL, false, 0);
    
  wld_log->SetVisAttributes(G4VisAttributes::Invisible);

    
  //--------------------------------------------------------------------------
  // UVLED
  //-------------------------------------------------------------------------
  // Main Can.
  
  G4Tubs* ledCan = new G4Tubs("ledCan", 3.75*mm, 4.0*mm, 3.0*mm, 0.0*deg, 360.0*deg);
    
  G4LogicalVolume* ledCan_log = new G4LogicalVolume(ledCan, aluminium, "ledCan_log");
    
  G4VPhysicalVolume* ledCan_phys = new G4PVPlacement(0, G4ThreeVector(0.0*mm, 0.0*mm, 0.0*mm), "ledCan_phys", ledCan_log, wld_phys, false, 0);

  //--------------------------------------------------------------------------
  // Base of Can.
  
  G4Tubs* ledBase = new G4Tubs("ledBase", 0.0*mm, 4.5*mm, 0.5*mm, 0.0*deg, 360.*deg);
    
  G4LogicalVolume* ledBase_log = new G4LogicalVolume(ledBase, aluminium, "ledBase_log");
    
  G4VPhysicalVolume* ledBase_phys = new G4PVPlacement(0, G4ThreeVector(0.0*mm, 0.0*mm, -3.5*mm), "ledBase_phys", ledBase_log, wld_phys, false, 0);

  //--------------------------------------------------------------------------
  // Lens.
  
  G4Sphere* ledLens = new G4Sphere("ledLens", 0.0*mm, 3.15*mm, 0.0*deg, twopi, 0.0*deg, pi);
	    
  G4LogicalVolume* ledLens_log = new G4LogicalVolume(ledLens, Quartz, "ledLens_log");
		    
  G4VPhysicalVolume* ledLens_phys = new G4PVPlacement(0, G4ThreeVector(0.0*mm, 0.0*mm, +2.75*mm), "ledLens_phys", ledLens_log, wld_phys, false, 0);

  //--------------------------------------------------------------------------
  // Case Lip.
  
  G4Tubs* ledLip = new G4Tubs("ledLip", 3.15*mm, 3.75*mm, 0.25*mm, 0.0*deg, 360.0*deg);
    
  G4LogicalVolume* ledLip_log = new G4LogicalVolume(ledLip, aluminium, "ledLip_log");
    
  G4VPhysicalVolume* ledLip_phys = new G4PVPlacement(0, G4ThreeVector(0.0*mm, 0.0*mm, +2.75*mm), "ledLip_phys", ledLip_log, wld_phys, false, 0);
  
  //--------------------------------------------------------------------------
  // LED Circuit Board.
  // Cannot measure directly but think dimensions seem reasonable estimates by eye.
  
  G4Box* ledBoard  = new G4Box("ledBoard", 1.0*mm, 0.4*mm, 0.3*mm);
	 
  G4LogicalVolume* ledBoard_log  = new G4LogicalVolume(ledBoard, silicon, "ledBoard_log");
		   
  G4VPhysicalVolume* ledBoard_phys = new G4PVPlacement(0, G4ThreeVector(-0.25*mm, 0.0*mm, -2.7*mm), "ledBoard_phys", ledBoard_log, wld_phys, false, 0);
  
  //--------------------------------------------------------------------------
  // LED Semiconductor Die.
  // Cannot measure directly but think dimensions seem reasonable estimates by eye.
  
  G4Box* ledDie  = new G4Box("ledDie", 0.25*mm, 0.25*mm, 0.125*mm);
	 
  G4LogicalVolume* ledDie_log  = new G4LogicalVolume(ledDie, GaN, "ledDie_log");
		   
  G4VPhysicalVolume* ledDie_phys = new G4PVPlacement(0, G4ThreeVector(0.0*mm, 0.0*mm, -2.275*mm), "ledDie_phys", ledDie_log, wld_phys, false, 0);
 
  //--------------------------------------------------------------------------
  //Visual attributes
  //--------------------------------------------------------------------------
  
  G4VisAttributes* grey_vat = new G4VisAttributes(grey);
  grey_vat->SetVisibility(true);
  grey_vat->SetForceSolid(true);
  
  G4VisAttributes* yellow_vat = new G4VisAttributes(yellow);
  yellow_vat->SetVisibility(true);
  yellow_vat->SetForceSolid(true);
  
  G4VisAttributes* white_vat = new G4VisAttributes(white);
  white_vat->SetVisibility(true);
  white_vat->SetForceSolid(true);

  G4VisAttributes* cyan_vat = new G4VisAttributes(cyan);
  cyan_vat->SetVisibility(true);
  cyan_vat->SetForceSolid(true);
  
  G4VisAttributes* black_vat = new G4VisAttributes(black);
  black_vat->SetVisibility(true);
  black_vat->SetForceSolid(true);
  
  ledCan_log->SetVisAttributes(grey_vat);
  ledBase_log->SetVisAttributes(yellow_vat);
  ledLens_log->SetVisAttributes(white_vat);
  ledLip_log->SetVisAttributes(grey_vat);
  ledBoard_log->SetVisAttributes(cyan_vat);
  ledDie_log->SetVisAttributes(black_vat);
  
  // Set scoring volume.
  fScoringVolume = ledBoard_log;
  
 
  // return  
  return wld_phys;
}


void UVLEDDetectorConstruction::UpdateGeometry(){

  // Clean old geometry, if any
  G4GeometryManager::GetInstance()->OpenGeometry();
  G4PhysicalVolumeStore::GetInstance()->Clean();
  G4LogicalVolumeStore::GetInstance()->Clean();
  G4SolidStore::GetInstance()->Clean();
    
  G4RunManager::GetRunManager()->DefineWorldVolume(ConstructExp());
  G4RunManager::GetRunManager()->GeometryHasBeenModified();
  
}
