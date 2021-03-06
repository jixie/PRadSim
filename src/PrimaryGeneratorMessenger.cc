//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
// $Id: PrimaryGeneratorMessenger.cc,v 1.1 2010-10-18 15:56:17 maire Exp $
// GEANT4 tag $Name: geant4-09-04-patch-02 $
//
//

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "PrimaryGeneratorMessenger.hh"

#include "PrimaryGeneratorAction.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorMessenger::PrimaryGeneratorMessenger(PrimaryGeneratorAction *Gun) : Action(Gun)
{
    gunDir = new G4UIdirectory("/pradsim/gun/");
    gunDir->SetGuidance("PrimaryGenerator control");

    RndmCmd = new G4UIcmdWithAString("/pradsim/gun/rndm", this);
    RndmCmd->SetGuidance("Shoot randomly the incident particle.");
    RndmCmd->SetGuidance("  Choice : on(default), off");
    RndmCmd->SetParameterName("random", true);
    RndmCmd->SetDefaultValue("on");
    RndmCmd->SetCandidates("on off");
    RndmCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    GunTypeCmd = new G4UIcmdWithAString("/pradsim/gun/type", this);
    GunTypeCmd->SetGuidance("Choose a type of event generator.");
    GunTypeCmd->SetGuidance("  Choice : ring (default), elastic, moller");
    GunTypeCmd->SetParameterName("generator", true);
    GunTypeCmd->SetDefaultValue("ring");
    GunTypeCmd->SetCandidates("ring elastic moller");
    GunTypeCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorMessenger::~PrimaryGeneratorMessenger()
{
    delete RndmCmd;
    delete GunTypeCmd;
    delete gunDir;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PrimaryGeneratorMessenger::SetNewValue(
    G4UIcommand *command, G4String newValue)
{
    if (command == RndmCmd)
        Action->SetRndmFlag(newValue);

    if (command == GunTypeCmd)
        Action->SetGunType(newValue);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
