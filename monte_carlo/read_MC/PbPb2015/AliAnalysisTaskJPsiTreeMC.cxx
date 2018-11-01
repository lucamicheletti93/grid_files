/**************************************************************************
 * Copyright(c) 1998-2007, ALICE Experiment at CERN, All rights reserved. *
 *                                                                        *
 * Author: The ALICE Off-line Project.                                    *
 * Contributors are mentioned in the code where appropriate.              *
 *                                                                        *
 * Permission to use, copy, modify and distribute this software and its   *
 * documentation strictly for non-commercial purposes is hereby granted   *
 * without fee, provided that the above copyright notice appears in all   *
 * copies and that both the copyright notice and this permission notice   *
 * appear in the supporting documentation. The authors make no claims     *
 * about the suitability of this software for any purpose. It is          *
 * provided "as is" without express or implied warranty.                  *
 **************************************************************************/

/* $Id: AliAnalysisTaskJPsiTreeMC.cxx $ */

//-----------------------------------------------------------------------------
// Analysis task to compute muon/dimuon kinematic distributions
// The output is a tree.
// R. Arnaldi
//
//-----------------------------------------------------------------------------

//#ifndef AliAnalysisTaskJPsiTreeMC_CXX
//#define AliAnalysisTaskJPsiTreeMC_CXX

// ROOT includes
#include "TROOT.h"
#include "TH1.h"
#include "TH2.h"
#include "TAxis.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TMath.h"
#include "TObjString.h"
#include "TObjArray.h"
#include "TF1.h"
#include "TList.h"
#include "TStyle.h"
#include "TLorentzVector.h"
#include "TString.h"
#include "TTree.h"
#include "TFile.h"

#include "AliInputEventHandler.h"
#include "AliAODHeader.h"
#include "AliAODEvent.h"
#include "AliAODTrack.h"
#include "AliAnalysisManager.h"
#include "AliAnalysisTaskSE.h"
//#include "AliMultSelection.h"  //for Centrality
#include "AliAODMCParticle.h"
#include "AliAnalysisTaskJPsiTreeMC.h"

Double_t CostHE_mc(AliAODMCParticle*, AliAODMCParticle*);
Double_t CostCS_mc(AliAODMCParticle*, AliAODMCParticle*);
Double_t PhiHE_mc(AliAODMCParticle*, AliAODMCParticle*);
Double_t PhiCS_mc(AliAODMCParticle*, AliAODMCParticle*);
Double_t CostHE(AliAODTrack*, AliAODTrack*);
Double_t CostCS(AliAODTrack*, AliAODTrack*);
Double_t PhiHE(AliAODTrack*, AliAODTrack*);
Double_t PhiCS(AliAODTrack*, AliAODTrack*);

ClassImp(AliAnalysisTaskJPsiTreeMC)
//__________________________________________________________________________
AliAnalysisTaskJPsiTreeMC::AliAnalysisTaskJPsiTreeMC() :
  AliAnalysisTaskSE(),
  fOutputTree(0x0),
  fBeamEnergy(0.),
  fkAnalysisType(0x0),
  fPeriod(0x0),
  fNMuons_gen(0x0),
  fNDimu_gen(0x0),
  fNMuons_rec(0x0),
  fNDimu_rec(0x0),
  fAODEvent(0x0)
{
  //
  //Default ctor
  //
  fVertex[0] = 999.; fVertex[1] = 999.; fVertex[2] = 999.;
  for(Int_t i = 0; i < 300;i++){
    fPt_rec[i] = 999.;
    fE_rec[i] = 999.;
    fPx_rec[i] = 999;
    fPy_rec[i] = 999;
    fPz_rec[i] = 999;
    fY_rec[i] = 999.;
    fEta_rec[i] = 999.;
    fMatchTrig_rec[i] = 999.;
    fTrackChi2_rec[i] = 999.;
    fMatchTrigChi2_rec[i] = 999.;
    fCharge_rec[i] = 999;
    fRAtAbsEnd_rec[i] = 999;
    fMuonId_rec[i] = 999;
  }

  for(Int_t i = 0;i < 3000;i++){
    fDimuPt_gen[i] = 999.;
    fDimuPx_gen[i] = 999.;
    fDimuPy_gen[i] = 999.;
    fDimuPz_gen[i] = 999.;
    fDimuY_gen[i] = 999.;
    fDimuMass_gen[i] = 999.;
    fDimuCharge_gen[i] = 999;
    fDimuMatch_gen[i] = 999;
    ////////////////////////////////////////////////////////////////////////////
    //fDiff_index[i] = 999;
    //fNdaughters[i] = 999;
    //for(Int_t k = 0;k < 3;k++) fPDGcode[i][k] = 999;
    //fDiffPx_gen[i] = 999;
    fCostHE_gen[i] = 999;
    fPhiHE_gen[i] = 999;
    fCostCS_gen[i] = 999;
    fPhiCS_gen[i] = 999;
    ////////////////////////////////////////////////////////////////////////////

    //for(Int_t k=0;k<2;k++) fDimuMu_gen[i][k]=999;
    fDimuPt_rec[i] = 999.;
    fDimuPx_rec[i] = 999.;
    fDimuPy_rec[i] = 999.;
    fDimuPz_rec[i] = 999.;
    fDimuY_rec[i] = 999.;
    fDimuMass_rec[i] = 999.;
    fDimuCharge_rec[i] = 999;
    fDimuMatch_rec[i] = 999;
    //for(Int_t k=0;k<2;k++) fDimuMu_rec[i][k]=999;
    ////////////////////////////////////////////////////////////////////////////
    fCostHE_rec[i] = 999;
    fPhiHE_rec[i] = 999;
    fCostCS_rec[i] = 999;
    fPhiCS_rec[i] = 999;
    ////////////////////////////////////////////////////////////////////////////
  }
  //DefineOutput(1,TTree::Class());  //added
}

//__________________________________________________________________________
AliAnalysisTaskJPsiTreeMC::AliAnalysisTaskJPsiTreeMC(const char *name) :
  AliAnalysisTaskSE(name),
  fOutputTree(0x0),
  fBeamEnergy(0.),
  fkAnalysisType(0x0),
  fPeriod(0x0),
  fNMuons_gen(0x0),
  fNDimu_gen(0x0),
  fNMuons_rec(0x0),
  fNDimu_rec(0x0),
  fAODEvent(0x0)
{
  //
  // Constructor. Initialization of Inputs and Outputs
  //
  Info("AliAnalysisTaskJPsiTreeMC","Calling Constructor");
  fVertex[0] = 999.; fVertex[1] = 999.; fVertex[2] = 999.;
  for(Int_t i = 0;i < 300;i++){

    fPt_rec[i] = 999.;
    fE_rec[i] = 999.;
    fPx_rec[i] = 999;
    fPy_rec[i] = 999;
    fPz_rec[i] = 999;
    fY_rec[i] = 999.;
    fEta_rec[i] = 999.;
    fMatchTrig_rec[i] = 999.;
    fTrackChi2_rec[i] = 999.;
    fMatchTrigChi2_rec[i] = 999.;
    fCharge_rec[i] = 999;
    fRAtAbsEnd_rec[i] = 999;
    fMuonId_rec[i] = 999;

  }

  for(Int_t i = 0;i < 3000;i++){
    fDimuPt_gen[i] = 999.;
    fDimuPx_gen[i] = 999.;
    fDimuPy_gen[i] = 999.;
    fDimuPz_gen[i] = 999.;
    fDimuY_gen[i] = 999.;
    fDimuMass_gen[i] = 999.;
    fDimuCharge_gen[i] = 999;
    fDimuMatch_gen[i] = 999;
    //for(Int_t k=0;k<2;k++) fDimuMu_gen[i][k]=999;
    ////////////////////////////////////////////////////////////////////////////
    //fDiff_index[i] = 999;
    //fNdaughters[i] = 999;
    //for(Int_t k = 0;k < 3;k++) fPDGcode[i][k] = 999;
    //fDiffPx_gen[i] = 999;
    fCostHE_gen[i] = 999;
    fPhiHE_gen[i] = 999;
    fCostCS_gen[i] = 999;
    fPhiCS_gen[i] = 999;
    ////////////////////////////////////////////////////////////////////////////

    fDimuPt_rec[i] = 999.;
    fDimuPx_rec[i] = 999.;
    fDimuPy_rec[i] = 999.;
    fDimuPz_rec[i] = 999.;
    fDimuY_rec[i] = 999.;
    fDimuMass_rec[i] = 999.;
    fDimuCharge_rec[i] = 999;
    fDimuMatch_rec[i] = 999;
    //for(Int_t k=0;k<2;k++) fDimuMu_rec[i][k]=999;
    ////////////////////////////////////////////////////////////////////////////
    fCostHE_rec[i] = 999;
    fPhiHE_rec[i] = 999;
    fCostCS_rec[i] = 999;
    fPhiCS_rec[i] = 999;
    ////////////////////////////////////////////////////////////////////////////
  }
  DefineOutput(1,TTree::Class());
}

//___________________________________________________________________________
AliAnalysisTaskJPsiTreeMC& AliAnalysisTaskJPsiTreeMC::operator=(const AliAnalysisTaskJPsiTreeMC& c)
{
  //
  // Assignment operator
  //
  if (this!=&c) {
    AliAnalysisTaskSE::operator=(c) ;
  }
  return *this;
}

//___________________________________________________________________________
AliAnalysisTaskJPsiTreeMC::AliAnalysisTaskJPsiTreeMC(const AliAnalysisTaskJPsiTreeMC& c) :
  AliAnalysisTaskSE(c),
  fOutputTree(c.fOutputTree),
  fBeamEnergy(c.fBeamEnergy),
  fkAnalysisType(c.fkAnalysisType),
  fPeriod(c.fPeriod),
  fNMuons_gen(c.fNMuons_gen),
  fNDimu_gen(c.fNDimu_gen),
  fNMuons_rec(c.fNMuons_rec),
  fNDimu_rec(c.fNDimu_rec),
  fAODEvent(c.fAODEvent)
 {
  //
  // Copy Constructor
  //
}

//___________________________________________________________________________
AliAnalysisTaskJPsiTreeMC::~AliAnalysisTaskJPsiTreeMC() {
  //
  //destructor
  //
  Info("~AliAnalysisTaskJPsiTreeMC","Calling Destructor");
  if (AliAnalysisManager::GetAnalysisManager()->GetAnalysisType() != AliAnalysisManager::kProofAnalysis) delete fOutputTree;
}

//___________________________________________________________________________
void AliAnalysisTaskJPsiTreeMC::UserCreateOutputObjects(){

  // devo mettere la phys selection nel tree???
  if (fOutputTree) return; //already initialised ADDED

  OpenFile(1,"RECREATE");
  fOutputTree = new TTree("MCTree","Data Tree");

  fOutputTree->Branch("NMuons_gen",&fNMuons_gen,"NMuons_gen/I");
  fOutputTree->Branch("NDimu_gen",&fNDimu_gen,"NDimu_gen/I");
  //fOutputTree->Branch("DimuMu_gen",fDimuMu_gen,"DimuMu_gen[NDimu_gen][2]/I");
  fOutputTree->Branch("DimuPt_gen",fDimuPt_gen,"DimuPt_gen[NDimu_gen]/D");
  fOutputTree->Branch("DimuPx_gen",fDimuPx_gen,"DimuPx_gen[NDimu_gen]/D");
  fOutputTree->Branch("DimuPy_gen",fDimuPy_gen,"DimuPy_gen[NDimu_gen]/D");
  fOutputTree->Branch("DimuPz_gen",fDimuPz_gen,"DimuPz_gen[NDimu_gen]/D");
  fOutputTree->Branch("DimuY_gen",fDimuY_gen,"DimuY_gen[NDimu_gen]/D");
  fOutputTree->Branch("DimuMass_gen",fDimuMass_gen,"DimuMass_gen[NDimu_gen]/D");
  fOutputTree->Branch("DimuCharge_gen",fDimuCharge_gen,"DimuCharge_gen[NDimu_gen]/I");
  fOutputTree->Branch("DimuMatch_gen",fDimuMatch_gen,"DimuMatch_gen[NDimu_gen]/I");
  //////////////////////////////////////////////////////////////////////////////
  //fOutputTree->Branch("NonZeroPx",&fNonZeroPx,"NonZeroPx/I");
  //fOutputTree->Branch("Diff_index",fDiff_index,"Diff_index[NDimu_gen]/I");
  //fOutputTree->Branch("Ndaughters",fNdaughters,"Ndaughters[NDimu_gen]/I");
  //fOutputTree->Branch("PDGcode",fPDGcode,"PDGcode[NDimu_gen][3]/I");
  //fOutputTree->Branch("DiffPx_gen",fDiffPx_gen,"DiffPx_gen[NDimu_gen]/D");
  fOutputTree->Branch("CostHE_gen",fCostHE_gen,"CostHE_gen[NDimu_gen]/D");
  fOutputTree->Branch("PhiHE_gen",fPhiHE_gen,"PhiHE_gen[NDimu_gen]/D");
  fOutputTree->Branch("CostCS_gen",fCostCS_gen,"CostCS_gen[NDimu_gen]/D");
  fOutputTree->Branch("PhiCS_gen",fPhiCS_gen,"PhiCS_gen[NDimu_gen]/D");
  //////////////////////////////////////////////////////////////////////////////

  fOutputTree->Branch("NMuons_rec",&fNMuons_rec,"NMuons_rec/I");
  fOutputTree->Branch("Pt_rec",fPt_rec,"Pt_rec[NMuons_rec]/D");
  fOutputTree->Branch("E_rec",fE_rec,"E_rec[NMuons_rec]/D");
  fOutputTree->Branch("Px_rec",fPx_rec,"Px_rec[NMuons_rec]/D");
  fOutputTree->Branch("Py_rec",fPy_rec,"Py_rec[NMuons_rec]/D");
  fOutputTree->Branch("Pz_rec",fPz_rec,"Pz_rec[NMuons_rec]/D");
  fOutputTree->Branch("Y_rec",fY_rec,"Y_rec[NMuons_rec]/D");
  fOutputTree->Branch("Eta_rec",fEta_rec,"Eta_rec[NMuons_rec]/D");
  fOutputTree->Branch("MatchTrig_rec",fMatchTrig_rec,"MatchTrig_rec[NMuons_rec]/I");
  fOutputTree->Branch("TrackChi2_rec",fTrackChi2_rec,"TrackChi2_rec[NMuons_rec]/D");
  fOutputTree->Branch("MatchTrigChi2_rec",fMatchTrigChi2_rec,"MatchTrigChi2_rec[NMuons_rec]/D");
  fOutputTree->Branch("Charge_rec",fCharge_rec,"Charge_rec[NMuons_rec]/I");
  fOutputTree->Branch("RAtAbsEnd_rec",fRAtAbsEnd_rec,"RAtAbsEnd_rec[NMuons_rec]/D");
  fOutputTree->Branch("MuonId_rec",fMuonId_rec,"MuonId_rec[NMuons_rec]/I");

  fOutputTree->Branch("NDimu_rec",&fNDimu_rec,"NDimu_rec/I");
  //fOutputTree->Branch("DimuMu_rec",fDimuMu_rec,"DimuMu_rec[NDimu_rec][2]/I");
  fOutputTree->Branch("DimuPt_rec",fDimuPt_rec,"DimuPt_rec[NDimu_rec]/D");
  fOutputTree->Branch("DimuPx_rec",fDimuPx_rec,"DimuPx_rec[NDimu_rec]/D");
  fOutputTree->Branch("DimuPy_rec",fDimuPy_rec,"DimuPy_rec[NDimu_rec]/D");
  fOutputTree->Branch("DimuPz_rec",fDimuPz_rec,"DimuPz_rec[NDimu_rec]/D");
  fOutputTree->Branch("DimuY_rec",fDimuY_rec,"DimuY_rec[NDimu_rec]/D");
  fOutputTree->Branch("DimuMass_rec",fDimuMass_rec,"DimuMass_rec[NDimu_rec]/D");
  fOutputTree->Branch("DimuCharge_rec",fDimuCharge_rec,"DimuCharge_rec[NDimu_rec]/I");
  fOutputTree->Branch("DimuMatch_rec",fDimuMatch_rec,"DimuMatch_rec[NDimu_rec]/I");
  //////////////////////////////////////////////////////////////////////////////
  fOutputTree->Branch("CostHE_rec",fCostHE_rec,"CostHE_rec[NDimu_rec]/D");
  fOutputTree->Branch("PhiHE_rec",fPhiHE_rec,"PhiHE_rec[NDimu_rec]/D");
  fOutputTree->Branch("CostCS_rec",fCostCS_rec,"CostCS_rec[NDimu_rec]/D");
  fOutputTree->Branch("PhiCS_rec",fPhiCS_rec,"PhiCS_rec[NDimu_rec]/D");
  //////////////////////////////////////////////////////////////////////////////

  fOutputTree->ls();
  PostData(1,fOutputTree);
}

//_________________________________________________
void AliAnalysisTaskJPsiTreeMC::UserExec(Option_t *)
{

 printf("sono in tree user exec");

  //////////////////////////////////////////////////////////////////////////////
  //fNonZeroPx = 0;
  //////////////////////////////////////////////////////////////////////////////
  fNMuons_gen = 0;
  fNDimu_gen = 0;
  fNMuons_rec = 0;
  fNDimu_rec = 0;
  fVertex[0] = 999.; fVertex[1] = 999.; fVertex[2] = 999.;
  for(Int_t i = 0;i < 300;i++){

    fPt_rec[i] = 999.;
    fE_rec[i] = 999.;
    fPx_rec[i] = 999;
    fPy_rec[i] = 999;
    fPz_rec[i] = 999;
    fY_rec[i] = 999.;
    fEta_rec[i] = 999.;
    fMatchTrig_rec[i] = 999.;
    fTrackChi2_rec[i] = 999.;
    fMatchTrigChi2_rec[i] = 999.;
    fCharge_rec[i] = 999;
    fRAtAbsEnd_rec[i] = 999;
  }
  for(Int_t i = 0;i < 3000;i++){
    fDimuPt_gen[i] = 999.;
    fDimuPx_gen[i] = 999.;
    fDimuPy_gen[i] = 999.;
    fDimuPz_gen[i] = 999.;
    fDimuY_gen[i] = 999.;
    fDimuMass_gen[i] = 999.;
    fDimuCharge_gen[i] = 999.;
    fDimuMatch_gen[i] = 0;
    //for(Int_t k=0;k<2;k++) fDimuMu_gen[i][k]=999;
    ////////////////////////////////////////////////////////////////////////////
    //fDiff_index[i] = 999;
    //fNdaughters[i] = 999;
    //for(Int_t k = 0;k < 3;k++) fPDGcode[i][k] = 999;
    //fDiffPx_gen[i] = 999;
    fCostHE_gen[i] = 999;
    fPhiHE_gen[i] = 999;
    fCostCS_gen[i] = 999;
    fPhiCS_gen[i] = 999;
    ////////////////////////////////////////////////////////////////////////////

    fDimuPt_rec[i] = 999.;
    fDimuPx_rec[i] = 999.;
    fDimuPy_rec[i] = 999.;
    fDimuPz_rec[i] = 999.;
    fDimuY_rec[i] = 999.;
    fDimuMass_rec[i] = 999.;
    fDimuCharge_rec[i] = 999.;
    fDimuMatch_rec[i] = 0;
    //for(Int_t k=0;k<2;k++) fDimuMu_rec[i][k]=999;
    ////////////////////////////////////////////////////////////////////////////
    fCostHE_rec[i] = 999;
    fPhiHE_rec[i] = 999;
    fCostCS_rec[i] = 999;
    fPhiCS_rec[i] = 999;
    ////////////////////////////////////////////////////////////////////////////

  }

  //
  // Execute analysis for current event
  //
  fAODEvent = dynamic_cast<AliAODEvent*> (InputEvent());
  if ( ! fAODEvent ) {
    AliError ("AOD event not found. Nothing done!");
    return;
  }

  TClonesArray *mcarray = dynamic_cast<TClonesArray*>(fAODEvent->FindListObject(AliAODMCParticle::StdBranchName()));
  AliAODHeader *aodheader = dynamic_cast<AliAODHeader*>(fAODEvent->GetHeader());

  AliAODVertex *PrimVertex =  fAODEvent->GetPrimaryVertex();
  fVertex[0] = PrimVertex -> GetX();
  fVertex[1] = PrimVertex -> GetY();
  fVertex[2] = PrimVertex -> GetZ();

    //
    // build dimuon object starting from single muons
    //
    // generated events
  //printf("Macro Tree entries = %d\n",mcarray -> GetEntries());
  Int_t numdimu_gen = 0;
  //double diff = 0;
  for (Int_t i = 0;i < mcarray -> GetEntries();i++){
    Int_t nonzeroPx = 0;

    AliAODMCParticle *mcp = (AliAODMCParticle *)mcarray -> At(i);
    if(mcp -> GetPdgCode() == 443){
      AliAODMCParticle *mcmu0 = (AliAODMCParticle *) mcarray -> At(mcp -> GetFirstDaughter());
      AliAODMCParticle *mcmu1 = (AliAODMCParticle *) mcarray -> At(mcp -> GetLastDaughter());
      //fNdaughters[i] = mcp -> GetNDaughters();

      //if(TMath::Abs(mcmu0 -> GetPdgCode()) != 13 || TMath::Abs(mcmu1 -> GetPdgCode()) != 13) continue;

      fDimuPt_gen[i] = mcp -> Pt();
      fDimuPx_gen[i] = mcp -> Px();
      fDimuPy_gen[i] = mcp -> Py();
      fDimuPz_gen[i] = mcp -> Pz();
      fDimuY_gen[i] = mcp -> Y();
      fDimuMass_gen[i] = mcp -> M();
      fDimuCharge_gen[i] = mcp -> Charge();
      fDimuMatch_gen[i] = 0;

      //double mcPx = mcp -> Px();
      //double mcmu0Px = mcmu0 -> Px();
      //double mcmu1Px = mcmu1 -> Px();
      //double mcPy = mcp -> Py();
      //double mcmu0Py = mcmu0 -> Py();
      //double mcmu1Py = mcmu1 -> Py();
      //double mcPz = mcp -> Pz();
      //double mcmu0Pz = mcmu0 -> Pz();
      //double mcmu1Pz = mcmu1 -> Pz();

      //double mcP = TMath::Sqrt(mcPx*mcPx + mcPy*mcPy + mcPz*mcPz);
      //double mcmu0P = TMath::Sqrt(mcmu0Px*mcmu0Px + mcmu0Py*mcmu0Py + mcmu0Pz*mcmu0Pz);
      //double mcmu1P = TMath::Sqrt(mcmu1Px*mcmu1Px + mcmu1Py*mcmu1Py + mcmu1Pz*mcmu1Pz);

      //double sum = mcmu0Px + mcmu1Px;
      //double diff = sum - mcPx;
      //printf("\n");
      //printf(" %f + %f = %f -> %f \n",mcmu0P,mcmu1P,sum,mcP);
      //if(TMath::Abs(diff) > 0.1) nonzeroPx++;

      //int mother_index0 = mcmu0 -> GetMother();
      //int mother_index1 = mcmu1 -> GetMother();

      //fDiffPx_gen[i] = diff;
      //if(mcp -> GetNDaughters() == 3) fNdaughters[i] = mcp -> GetNDaughters();
      //fNdaughters[i] = mcp -> GetNDaughters();
      //fDiff_index[i] = (i - mother_index0) + (i - mother_index1);

      //fPDGcode[i][0] = mcp -> GetPdgCode();
      //fPDGcode[i][1] = mcmu0 -> GetPdgCode();
      //fPDGcode[i][2] = mcmu1 -> GetPdgCode();

      fCostHE_gen[i] = CostHE_mc(mcmu0,mcmu1);
      fPhiHE_gen[i] = PhiHE_mc(mcmu0,mcmu1);
      fCostCS_gen[i] = CostCS_mc(mcmu0,mcmu1);
      fPhiCS_gen[i] = PhiCS_mc(mcmu0,mcmu1);
	    numdimu_gen++;
      //fNonZeroPx = nonzeroPx;
    }

  }

  printf("\n");
  //printf("---------------------------> N of non zero PX = %i \n",nonzeroPx);
  //fNonZeroPx = nonzeroPx;
  fNDimu_gen = numdimu_gen;

  //devo mettere qualcosa sulle labels???


  //-------------------------------------------------------------------------
  // uncomment if reading AliMuonAODs (in PbPb)
  //-------------------------------------------------------------------------
  Int_t numdimu = 0;
  Int_t nummu = 0;
  TRefArray *mutracks = new TRefArray();
  Int_t nmuons = fAODEvent -> GetMuonTracks(mutracks);
  Int_t good_muons[300];
  Int_t muon_id[300];

  for(int i = 0;i < 300;i++){
    good_muons[i] = 0;
  }
  for(Int_t i = 0;i < nmuons;i++){
    printf("i=%d \n",i);
    AliAODTrack *mu0 = (AliAODTrack*)fAODEvent -> GetTrack(i);
    if (!mu0 -> IsMuonTrack()) continue;
    if (mu0 -> Eta() > -2.5 || mu0 -> Eta() < -4) continue;
    if (mu0 -> GetRAtAbsorberEnd() < 17.6 || mu0 -> GetRAtAbsorberEnd() > 89.5) continue;
    for(Int_t j = i+1;j < nmuons;j++){
  	  printf("j=%d \n",j);
      AliAODTrack *mu1 = (AliAODTrack*)fAODEvent -> GetTrack(j);
      if(!mu1 -> IsMuonTrack()) continue;
      if(mu1 -> Eta() > -2.5 || mu1 -> Eta() < -4) continue;
      if (mu1 -> GetRAtAbsorberEnd() < 17.6 || mu1 -> GetRAtAbsorberEnd() > 89.5) continue;

      AliAODDimuon *dimu = new AliAODDimuon(mu0,mu1);

      if(dimu -> Mass() > 2. && dimu -> Charge() == 0){

        good_muons[i] = 1;
        good_muons[j] = 1;

        fDimuMass_rec[numdimu] = dimu -> Mass();
        fDimuPt_rec[numdimu] = dimu -> Pt();
        fDimuPx_rec[numdimu] = dimu -> Px();
        fDimuPy_rec[numdimu] = dimu -> Py();
        fDimuPz_rec[numdimu] = dimu -> Pz();
        fDimuY_rec[numdimu] = dimu -> Y();
        fDimuCharge_rec[numdimu]= dimu -> Charge();
        //fDimuMu_rec[numdimu][0] = i; fDimuMu_rec[numdimu][1] = j;

        fCostHE_rec[numdimu] = CostHE(mu0,mu1);
        fPhiHE_rec[numdimu] = PhiHE(mu0,mu1);
        fCostCS_rec[numdimu] = CostCS(mu0,mu1);
        fPhiCS_rec[numdimu] = PhiCS(mu0,mu1);

        if(mu0 -> GetMatchTrigger() > 1 || mu1 -> GetMatchTrigger() > 1){fDimuMatch_rec[numdimu] = 1;}
        if(mu0 -> GetMatchTrigger() > 1 && mu1 -> GetMatchTrigger() > 1){fDimuMatch_rec[numdimu] = 2;}
        numdimu++;
        // delete mu1;
        // delete dimu;
      } // mass cut
      delete dimu;
        // delete mu1;
    }
    //nummu++;

    nummu = 0;
    for(Int_t i = 0;i < nmuons;i++){

      AliAODTrack *mu0 = (AliAODTrack*)fAODEvent -> GetTrack(i);
      if(good_muons[i] == 1){
        fMuonId_rec[nummu] = i;
        fCharge_rec[nummu] = mu0 -> Charge();
        fPt_rec[nummu] = mu0 -> Pt();
        fPx_rec[nummu] = mu0 -> Px();
        fPy_rec[nummu] = mu0 -> Py();
        fPz_rec[nummu] = mu0 -> Pz();
        fY_rec[nummu]  = mu0 -> Y();
        fEta_rec[nummu] = mu0 -> Eta();
        fE_rec[nummu] = mu0 -> E();
        // fDCA[nummu] = mu0->GetDCA();
        // fTrackChi2[nummu] = mui->GetChi2()/(2.*mu0->GetNHit()-5.);
        fMatchTrig_rec[nummu] = mu0 -> GetMatchTrigger();
        fMatchTrigChi2_rec[nummu] = mu0 -> GetChi2MatchTrigger();
        fRAtAbsEnd_rec[nummu] = mu0 -> GetRAtAbsorberEnd();
        nummu++;
      }

    }
    // delete mu0;
    }


    fNMuons_rec = nummu;
    fNDimu_rec = numdimu;
    fOutputTree->Fill();
    PostData(1,fOutputTree);
}
//______________________________________________________________________________
//MC PARTICLES
//______________________________________________________________________________
Double_t CostHE_mc(AliAODMCParticle* Mu0, AliAODMCParticle* Mu1){
  Double_t EBeam = 2510*208;
  Double_t mp = 195.323567174;
  //Double_t mp = 0.93827231;
  Double_t pbeam = TMath::Sqrt(EBeam*EBeam - mp*mp);
  Double_t pla10 = Mu0 -> Px();
  Double_t pla11 = Mu0 -> Py();
  Double_t pla12 = Mu0 -> Pz();
  Double_t e1 = Mu0 -> E();
  Double_t mu1Charge = Mu0 -> Charge();
  Double_t pla20 = Mu1 -> Px();
  Double_t pla21 = Mu1 -> Py();
  Double_t pla22 = Mu1 -> Pz();
  Double_t e2 = Mu1 -> E();
  //Double_t mu2Charge=Mu1->Charge();
  if(pla10==0 && pla11==0 && pla12==0 && e1==0 && mu1Charge==0 && pla20==0 && pla21==0 && pla22==0 && e2==0.){return -666.;}

  // Fill the Lorentz vector for projectile and target
  // For the moment we consider no crossing angle
  // Projectile runs towards the MUON arm
  TLorentzVector pProjLab(0.,0.,-pbeam,EBeam); // projectile
  TLorentzVector pTargLab(0.,0., pbeam,EBeam); // target
  //
  // --- Get the muons parameters in the LAB frame
  //
  TLorentzVector pMu1Lab(pla10,pla11,pla12,e1);
  TLorentzVector pMu2Lab(pla20,pla21,pla22,e2);
  //
  // --- Obtain the dimuon parameters in the LAB frame
  //
  TLorentzVector pDimuLab = pMu1Lab + pMu2Lab;
  //
  // --- Translate the dimuon parameters in the dimuon rest frame
  //
  TVector3 beta = (-1./pDimuLab.E())*pDimuLab.Vect();
  TLorentzVector pMu1Dimu = pMu1Lab;
  TLorentzVector pMu2Dimu = pMu2Lab;
  pMu1Dimu.Boost(beta);
  pMu2Dimu.Boost(beta);

  TVector3 zaxis;
  zaxis=(pDimuLab.Vect()).Unit();
  //
  // --- Calculation of the polarization angle (Helicity)
  // (angle between mu+ and the z axis defined above)
  //
  Double_t cost;
  if(mu1Charge > 0) {
    cost = zaxis.Dot((pMu1Dimu.Vect()).Unit());
  } else {
    cost = zaxis.Dot((pMu2Dimu.Vect()).Unit());
  }
  return cost;
}
//______________________________________________________________________________
//______________________________________________________________________________
Double_t PhiHE_mc(AliAODMCParticle* Mu0, AliAODMCParticle* Mu1){
  // Calculation the Helicity aimuthal angle (adapted from code by R. Arnaldi)
  Double_t EBeam = 2510*208;
  if(EBeam <= 0){
    printf("Can not compute phiHE with EBeam=%f\n",EBeam);
    return -999999999;
  }
  Double_t mp = 195.323567174;
  //Double_t mp = 0.93827231;
  Double_t pbeam = TMath::Sqrt(EBeam*EBeam - mp*mp);
  Double_t pla10 = Mu0 -> Px();
  Double_t pla11 = Mu0 -> Py();
  Double_t pla12 = Mu0 -> Pz();
  Double_t e1 = Mu0 -> E();
  Double_t mu1Charge = Mu0 -> Charge();
  Double_t pla20 = Mu1 -> Px();
  Double_t pla21 = Mu1 -> Py();
  Double_t pla22 = Mu1 -> Pz();
  Double_t e2 = Mu1 -> E();
  //Double_t mu2Charge=Mu1->Charge();
  if(pla10==0 && pla11==0 && pla12==0 && e1==0 && mu1Charge==0 && pla20==0 && pla21==0 && pla22==0 && e2==0.){return -666.;}

  // Fill the Lorentz vector for projectile and target
  // For the moment we consider no crossing angle
  // Projectile runs towards the MUON arm
  TLorentzVector pProjCM(0.,0.,-pbeam,EBeam); // projectile
  TLorentzVector pTargCM(0.,0., pbeam,EBeam); // target
  //
  // --- Get the muons parameters in the CM frame
  //
  TLorentzVector pMu1CM(pla10,pla11,pla12,e1);
  TLorentzVector pMu2CM(pla20,pla21,pla22,e2);
  //
  // --- Obtain the dimuon parameters in the CM frame
  //
  TLorentzVector pDimuCM = pMu1CM + pMu2CM;
  //
  // --- Translate the muon parameters in the dimuon rest frame
  //
  TVector3 zaxis = (pDimuCM.Vect()).Unit();
  //
  // --- Translate the dimuon parameters in the dimuon rest frame
  //
  TVector3 beta = (-1./pDimuCM.E())*pDimuCM.Vect();
  TLorentzVector pMu1Dimu = pMu1CM;
  TLorentzVector pMu2Dimu = pMu2CM;
  pMu1Dimu.Boost(beta);
  pMu2Dimu.Boost(beta);

  TLorentzVector pProjDimu = pProjCM;
  TLorentzVector pTargDimu = pTargCM;
  pProjDimu.Boost(beta);
  pTargDimu.Boost(beta);

  TVector3 yaxis = ((pProjDimu.Vect()).Cross(pTargDimu.Vect())).Unit();
  TVector3 xaxis = (yaxis.Cross(zaxis)).Unit();
  //
  // --- Calculation of the azimuthal angle (Helicity)
  //
   Double_t phi;
   if(mu1Charge>0) phi = TMath::ATan2((pMu1Dimu.Vect()).Dot(yaxis),(pMu1Dimu.Vect()).Dot(xaxis));
   else phi = TMath::ATan2((pMu2Dimu.Vect()).Dot(yaxis),(pMu2Dimu.Vect()).Dot(xaxis));

   return phi;
}
//______________________________________________________________________________
Double_t CostCS_mc(AliAODMCParticle* Mu0, AliAODMCParticle* Mu1){
  Double_t EBeam = 2510*208;
  Double_t mp = 195.323567174;
  //Double_t mp = 0.93827231;
  Double_t pbeam = TMath::Sqrt(EBeam*EBeam - mp*mp);
  Double_t pla10 = Mu0 -> Px();
  Double_t pla11 = Mu0 -> Py();
  Double_t pla12 = Mu0 -> Pz();
  Double_t e1 = Mu0 -> E();
  Double_t mu1Charge = Mu0 -> Charge();
  Double_t pla20 = Mu1 -> Px();
  Double_t pla21 = Mu1 -> Py();
  Double_t pla22 = Mu1 -> Pz();
  Double_t e2 = Mu1 -> E();
  Double_t mu2Charge = Mu1 -> Charge();
  if(pla10==0 && pla11==0 && pla12==0 && e1==0 && mu1Charge==0 && pla20==0 && pla21==0 && pla22==0 && e2==0.){return -666.;}

  // Fill the Lorentz vector for projectile and target
  // For the moment we do not consider the crossing angle
  // Projectile runs towards the MUON arm
  TLorentzVector pProjCM(0.,0.,-pbeam,EBeam); // projectile
  TLorentzVector pTargCM(0.,0., pbeam,EBeam); // target
  //
  // --- Get the muons parameters in the CM frame
  //
  TLorentzVector pMu1CM(pla10,pla11,pla12,e1);
  TLorentzVector pMu2CM(pla20,pla21,pla22,e2);
  //
  // --- Obtain the dimuon parameters in the CM frame
  //
  TLorentzVector pDimuCM = pMu1CM + pMu2CM;
  //
  // --- Translate the dimuon parameters in the dimuon rest frame
  //
  TVector3 beta = (-1./pDimuCM.E())*pDimuCM.Vect();
  TLorentzVector pMu1Dimu = pMu1CM;
  TLorentzVector pMu2Dimu = pMu2CM;
  TLorentzVector pProjDimu = pProjCM;
  TLorentzVector pTargDimu = pTargCM;
  pMu1Dimu.Boost(beta);
  pMu2Dimu.Boost(beta);
  pProjDimu.Boost(beta);
  pTargDimu.Boost(beta);
  //
  // --- Determine the z axis for the CS angle
  //
  TVector3 zaxisCS = (((pProjDimu.Vect()).Unit())-((pTargDimu.Vect()).Unit())).Unit();
  //
  // --- Determine the CS angle (angle between mu+ and the z axis defined above)
  //
  Double_t cost;
  if(mu1Charge > 0) {
    cost = zaxisCS.Dot((pMu1Dimu.Vect()).Unit());
    // Theta CS is not properly defined for Like-Sign muons
    if(mu2Charge > 0 && cost<0) cost = -cost;
  } else {
    // Theta CS is not properly defined for Like-Sign muons
    cost = zaxisCS.Dot((pMu2Dimu.Vect()).Unit());
    if(mu2Charge < 0 && cost<0) cost = -cost;
  }
  return cost;
}
//______________________________________________________________________________
Double_t PhiCS_mc(AliAODMCParticle* Mu0, AliAODMCParticle* Mu1){
  // Cosinus of the Collins-Soper polar decay angle
  Double_t EBeam = 2510*208;
  if(EBeam <= 0){
    printf("Can not compute phiCS with EBeam=%f\n",EBeam);
    return -999999999;
  }
  Double_t mp = 195.323567174;
  //Double_t mp = 0.93827231;
  Double_t pbeam = TMath::Sqrt(EBeam*EBeam - mp*mp);
  Double_t pla10 = Mu0 -> Px();
  Double_t pla11 = Mu0->Py();
  Double_t pla12 = Mu0->Pz();
  Double_t e1 = Mu0->E();
  Double_t mu1Charge = Mu0 -> Charge();
  Double_t pla20 = Mu1 -> Px();
  Double_t pla21 = Mu1 -> Py();
  Double_t pla22 = Mu1 -> Pz();
  Double_t e2 = Mu1 -> E();
  //Double_t mu2Charge=Mu1->Charge();
  if(pla10==0 && pla11==0 && pla12==0 && e1==0 && mu1Charge==0 && pla20==0 && pla21==0 && pla22==0 && e2==0.){return -666.;}

  // Fill the Lorentz vector for projectile and target
  // For the moment we do not consider the crossing angle
  // Projectile runs towards the MUON arm
  TLorentzVector pProjCM(0.,0.,-pbeam,EBeam); // projectile
  TLorentzVector pTargCM(0.,0., pbeam,EBeam); // target
  //
  // --- Get the muons parameters in the CM frame
  //
  TLorentzVector pMu1CM(pla10,pla11,pla12,e1);
  TLorentzVector pMu2CM(pla20,pla21,pla22,e2);
  //
  // --- Obtain the dimuon parameters in the CM frame
  //
  TLorentzVector pDimuCM = pMu1CM + pMu2CM;
  //
  // --- Translate the dimuon parameters in the dimuon rest frame
  //
  TVector3 beta = (-1./pDimuCM.E())*pDimuCM.Vect();
  TLorentzVector pMu1Dimu = pMu1CM;
  TLorentzVector pMu2Dimu = pMu2CM;
  TLorentzVector pProjDimu = pProjCM;
  TLorentzVector pTargDimu = pTargCM;
  pMu1Dimu.Boost(beta);
  pMu2Dimu.Boost(beta);
  pProjDimu.Boost(beta);
  pTargDimu.Boost(beta);
  //
  // --- Determine the z axis for the CS angle
  //
  TVector3 zaxisCS = (((pProjDimu.Vect()).Unit()) - ((pTargDimu.Vect()).Unit())).Unit();
  //
  // --- Determine the CS angle (angle between mu+ and the z axis defined above)
  //
   TVector3 yaxisCS = (((pProjDimu.Vect()).Unit()).Cross((pTargDimu.Vect()).Unit())).Unit();
   TVector3 xaxisCS = (yaxisCS.Cross(zaxisCS)).Unit();

   Double_t phi;
   if(mu1Charge>0) phi = TMath::ATan2((pMu1Dimu.Vect()).Dot(yaxisCS),((pMu1Dimu.Vect()).Dot(xaxisCS)));
   else phi = TMath::ATan2((pMu2Dimu.Vect()).Dot(yaxisCS),((pMu2Dimu.Vect()).Dot(xaxisCS)));

   return phi;
}
//______________________________________________________________________________
//AOD TRACKS
//______________________________________________________________________________
Double_t CostHE(AliAODTrack* Mu0, AliAODTrack* Mu1){
  Double_t EBeam = 2510*208;
  Double_t mp = 195.323567174;
  //Double_t mp = 0.93827231;
  Double_t pbeam = TMath::Sqrt(EBeam*EBeam - mp*mp);
  Double_t pla10 = Mu0 -> Px();
  Double_t pla11 = Mu0 -> Py();
  Double_t pla12 = Mu0 -> Pz();
  Double_t e1 = Mu0 -> E();
  Double_t mu1Charge = Mu0 -> Charge();
  Double_t pla20 = Mu1 -> Px();
  Double_t pla21 = Mu1 -> Py();
  Double_t pla22 = Mu1 -> Pz();
  Double_t e2 = Mu1 -> E();
  //Double_t mu2Charge=Mu1->Charge();
  if(pla10==0 && pla11==0 && pla12==0 && e1==0 && mu1Charge==0 && pla20==0 && pla21==0 && pla22==0 && e2==0.){return -666.;}

  // Fill the Lorentz vector for projectile and target
  // For the moment we consider no crossing angle
  // Projectile runs towards the MUON arm
  TLorentzVector pProjLab(0.,0.,-pbeam,EBeam); // projectile
  TLorentzVector pTargLab(0.,0., pbeam,EBeam); // target
  //
  // --- Get the muons parameters in the LAB frame
  //
  TLorentzVector pMu1Lab(pla10,pla11,pla12,e1);
  TLorentzVector pMu2Lab(pla20,pla21,pla22,e2);
  //
  // --- Obtain the dimuon parameters in the LAB frame
  //
  TLorentzVector pDimuLab = pMu1Lab + pMu2Lab;
  //
  // --- Translate the dimuon parameters in the dimuon rest frame
  //
  TVector3 beta = (-1./pDimuLab.E())*pDimuLab.Vect();
  TLorentzVector pMu1Dimu = pMu1Lab;
  TLorentzVector pMu2Dimu = pMu2Lab;
  pMu1Dimu.Boost(beta);
  pMu2Dimu.Boost(beta);

  TVector3 zaxis;
  zaxis=(pDimuLab.Vect()).Unit();
  //
  // --- Calculation of the polarization angle (Helicity)
  // (angle between mu+ and the z axis defined above)
  //
  Double_t cost;
  if(mu1Charge > 0) {
    cost = zaxis.Dot((pMu1Dimu.Vect()).Unit());
  } else {
    cost = zaxis.Dot((pMu2Dimu.Vect()).Unit());
  }
  return cost;
}
//______________________________________________________________________________
//______________________________________________________________________________
Double_t PhiHE(AliAODTrack* Mu0, AliAODTrack* Mu1){
  // Calculation the Helicity aimuthal angle (adapted from code by R. Arnaldi)
  Double_t EBeam = 2510*208;
  if(EBeam <= 0){
    printf("Can not compute phiHE with EBeam=%f\n",EBeam);
    return -999999999;
  }
  Double_t mp = 195.323567174;
  //Double_t mp = 0.93827231;
  Double_t pbeam = TMath::Sqrt(EBeam*EBeam - mp*mp);
  Double_t pla10 = Mu0 -> Px();
  Double_t pla11 = Mu0 -> Py();
  Double_t pla12 = Mu0 -> Pz();
  Double_t e1 = Mu0 -> E();
  Double_t mu1Charge = Mu0 -> Charge();
  Double_t pla20 = Mu1 -> Px();
  Double_t pla21 = Mu1 -> Py();
  Double_t pla22 = Mu1 -> Pz();
  Double_t e2 = Mu1 -> E();
  //Double_t mu2Charge=Mu1->Charge();
  if(pla10==0 && pla11==0 && pla12==0 && e1==0 && mu1Charge==0 && pla20==0 && pla21==0 && pla22==0 && e2==0.){return -666.;}

  // Fill the Lorentz vector for projectile and target
  // For the moment we consider no crossing angle
  // Projectile runs towards the MUON arm
  TLorentzVector pProjCM(0.,0.,-pbeam,EBeam); // projectile
  TLorentzVector pTargCM(0.,0., pbeam,EBeam); // target
  //
  // --- Get the muons parameters in the CM frame
  //
  TLorentzVector pMu1CM(pla10,pla11,pla12,e1);
  TLorentzVector pMu2CM(pla20,pla21,pla22,e2);
  //
  // --- Obtain the dimuon parameters in the CM frame
  //
  TLorentzVector pDimuCM = pMu1CM + pMu2CM;
  //
  // --- Translate the muon parameters in the dimuon rest frame
  //
  TVector3 zaxis = (pDimuCM.Vect()).Unit();
  //
  // --- Translate the dimuon parameters in the dimuon rest frame
  //
  TVector3 beta = (-1./pDimuCM.E())*pDimuCM.Vect();
  TLorentzVector pMu1Dimu = pMu1CM;
  TLorentzVector pMu2Dimu = pMu2CM;
  pMu1Dimu.Boost(beta);
  pMu2Dimu.Boost(beta);

  TLorentzVector pProjDimu = pProjCM;
  TLorentzVector pTargDimu = pTargCM;
  pProjDimu.Boost(beta);
  pTargDimu.Boost(beta);

  TVector3 yaxis = ((pProjDimu.Vect()).Cross(pTargDimu.Vect())).Unit();
  TVector3 xaxis = (yaxis.Cross(zaxis)).Unit();
  //
  // --- Calculation of the azimuthal angle (Helicity)
  //
   Double_t phi;
   if(mu1Charge>0) phi = TMath::ATan2((pMu1Dimu.Vect()).Dot(yaxis),(pMu1Dimu.Vect()).Dot(xaxis));
   else phi = TMath::ATan2((pMu2Dimu.Vect()).Dot(yaxis),(pMu2Dimu.Vect()).Dot(xaxis));

   return phi;
}
//______________________________________________________________________________
Double_t CostCS(AliAODTrack* Mu0, AliAODTrack* Mu1){
  Double_t EBeam = 2510*208;
  Double_t mp = 195.323567174;
  //Double_t mp = 0.93827231;
  Double_t pbeam = TMath::Sqrt(EBeam*EBeam - mp*mp);
  Double_t pla10 = Mu0 -> Px();
  Double_t pla11 = Mu0 -> Py();
  Double_t pla12 = Mu0 -> Pz();
  Double_t e1 = Mu0 -> E();
  Double_t mu1Charge = Mu0 -> Charge();
  Double_t pla20 = Mu1 -> Px();
  Double_t pla21 = Mu1 -> Py();
  Double_t pla22 = Mu1 -> Pz();
  Double_t e2 = Mu1 -> E();
  Double_t mu2Charge = Mu1 -> Charge();
  if(pla10==0 && pla11==0 && pla12==0 && e1==0 && mu1Charge==0 && pla20==0 && pla21==0 && pla22==0 && e2==0.){return -666.;}

  // Fill the Lorentz vector for projectile and target
  // For the moment we do not consider the crossing angle
  // Projectile runs towards the MUON arm
  TLorentzVector pProjCM(0.,0.,-pbeam,EBeam); // projectile
  TLorentzVector pTargCM(0.,0., pbeam,EBeam); // target
  //
  // --- Get the muons parameters in the CM frame
  //
  TLorentzVector pMu1CM(pla10,pla11,pla12,e1);
  TLorentzVector pMu2CM(pla20,pla21,pla22,e2);
  //
  // --- Obtain the dimuon parameters in the CM frame
  //
  TLorentzVector pDimuCM = pMu1CM + pMu2CM;
  //
  // --- Translate the dimuon parameters in the dimuon rest frame
  //
  TVector3 beta = (-1./pDimuCM.E())*pDimuCM.Vect();
  TLorentzVector pMu1Dimu = pMu1CM;
  TLorentzVector pMu2Dimu = pMu2CM;
  TLorentzVector pProjDimu = pProjCM;
  TLorentzVector pTargDimu = pTargCM;
  pMu1Dimu.Boost(beta);
  pMu2Dimu.Boost(beta);
  pProjDimu.Boost(beta);
  pTargDimu.Boost(beta);
  //
  // --- Determine the z axis for the CS angle
  //
  TVector3 zaxisCS = (((pProjDimu.Vect()).Unit())-((pTargDimu.Vect()).Unit())).Unit();
  //
  // --- Determine the CS angle (angle between mu+ and the z axis defined above)
  //
  Double_t cost;
  if(mu1Charge > 0) {
    cost = zaxisCS.Dot((pMu1Dimu.Vect()).Unit());
    // Theta CS is not properly defined for Like-Sign muons
    if(mu2Charge > 0 && cost<0) cost = -cost;
  } else {
    // Theta CS is not properly defined for Like-Sign muons
    cost = zaxisCS.Dot((pMu2Dimu.Vect()).Unit());
    if(mu2Charge < 0 && cost<0) cost = -cost;
  }
  return cost;
}
//______________________________________________________________________________
Double_t PhiCS(AliAODTrack* Mu0, AliAODTrack* Mu1){
  // Cosinus of the Collins-Soper polar decay angle
  Double_t EBeam = 2510*208;
  if(EBeam <= 0){
    printf("Can not compute phiCS with EBeam=%f\n",EBeam);
    return -999999999;
  }
  Double_t mp = 195.323567174;
  //Double_t mp = 0.93827231;
  Double_t pbeam = TMath::Sqrt(EBeam*EBeam - mp*mp);
  Double_t pla10 = Mu0 -> Px();
  Double_t pla11 = Mu0->Py();
  Double_t pla12 = Mu0->Pz();
  Double_t e1 = Mu0->E();
  Double_t mu1Charge = Mu0 -> Charge();
  Double_t pla20 = Mu1 -> Px();
  Double_t pla21 = Mu1 -> Py();
  Double_t pla22 = Mu1 -> Pz();
  Double_t e2 = Mu1 -> E();
  //Double_t mu2Charge=Mu1->Charge();
  if(pla10==0 && pla11==0 && pla12==0 && e1==0 && mu1Charge==0 && pla20==0 && pla21==0 && pla22==0 && e2==0.){return -666.;}

  // Fill the Lorentz vector for projectile and target
  // For the moment we do not consider the crossing angle
  // Projectile runs towards the MUON arm
  TLorentzVector pProjCM(0.,0.,-pbeam,EBeam); // projectile
  TLorentzVector pTargCM(0.,0., pbeam,EBeam); // target
  //
  // --- Get the muons parameters in the CM frame
  //
  TLorentzVector pMu1CM(pla10,pla11,pla12,e1);
  TLorentzVector pMu2CM(pla20,pla21,pla22,e2);
  //
  // --- Obtain the dimuon parameters in the CM frame
  //
  TLorentzVector pDimuCM = pMu1CM + pMu2CM;
  //
  // --- Translate the dimuon parameters in the dimuon rest frame
  //
  TVector3 beta = (-1./pDimuCM.E())*pDimuCM.Vect();
  TLorentzVector pMu1Dimu = pMu1CM;
  TLorentzVector pMu2Dimu = pMu2CM;
  TLorentzVector pProjDimu = pProjCM;
  TLorentzVector pTargDimu = pTargCM;
  pMu1Dimu.Boost(beta);
  pMu2Dimu.Boost(beta);
  pProjDimu.Boost(beta);
  pTargDimu.Boost(beta);
  //
  // --- Determine the z axis for the CS angle
  //
  TVector3 zaxisCS = (((pProjDimu.Vect()).Unit()) - ((pTargDimu.Vect()).Unit())).Unit();
  //
  // --- Determine the CS angle (angle between mu+ and the z axis defined above)
  //
   TVector3 yaxisCS = (((pProjDimu.Vect()).Unit()).Cross((pTargDimu.Vect()).Unit())).Unit();
   TVector3 xaxisCS = (yaxisCS.Cross(zaxisCS)).Unit();

   Double_t phi;
   if(mu1Charge>0) phi = TMath::ATan2((pMu1Dimu.Vect()).Dot(yaxisCS),((pMu1Dimu.Vect()).Dot(xaxisCS)));
   else phi = TMath::ATan2((pMu2Dimu.Vect()).Dot(yaxisCS),((pMu2Dimu.Vect()).Dot(xaxisCS)));

   return phi;
}
//______________________________________________________________________________
void AliAnalysisTaskJPsiTreeMC::Terminate(Option_t *)
{

 }
