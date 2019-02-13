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

/* $Id: AliAnalysisTaskPbPbJPsiTree_Dimuon.cxx $ */

//-----------------------------------------------------------------------------
// Analysis task to compute muon/dimuon kinematic distributions
// The output is a list of histograms.
// The macro class can run on AOD or in the train with the ESD filter.
// R. Arnaldi
//
//-----------------------------------------------------------------------------

//#ifndef AliAnalysisTaskPbPbJPsiTree_Dimuon_CXX 
//#define AliAnalysisTaskPbPbJPsiTree_Dimuon_CXX

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
#include "AliMultSelection.h"  //for Centrality

#include "AliAnalysisTaskPbPbJPsiTree_Dimuon.h"

#include "AliAODZDC.h"
#include "AliMuonTrackCuts.h"   //pDCA

Double_t CostHE(AliAODTrack*, AliAODTrack*);
Double_t CostCS(AliAODTrack*, AliAODTrack*);
Double_t PhiHE(AliAODTrack*, AliAODTrack*);
Double_t PhiCS(AliAODTrack*, AliAODTrack*);

ClassImp(AliAnalysisTaskPbPbJPsiTree_Dimuon)
//__________________________________________________________________________
AliAnalysisTaskPbPbJPsiTree_Dimuon::AliAnalysisTaskPbPbJPsiTree_Dimuon() :
  AliAnalysisTaskSE(),
  fOutput(0x0),
  fNevt(0x0),
  fBeamEnergy(0.),
  fkAnalysisType(0x0),
  fPeriod(0x0),
  fCountTotEv(0x0),
  fCountTrigger(0x0),
  fCountCINT7(0x0),
  fCountCMUL7(0x0),
  fCountCMLL7(0x0),
  fCountCMSL7(0x0),
  fCountCMSH7(0x0),
  fMuonTrackCuts(0x0), //pDCA
  fNMuons(0x0),
  fNTracklets(0x0),
  fNContributors(0x0),
  fNDimu(0x0),
  fPercentV0M(0x0),
  fPercentCL0(0x0),
  fPercentCL1(0x0),
  fPercentV0A(0x0),
  fPercentV0C(0x0),
  fPercentZNA(0x0),
  fPercentZNC(0x0),
  fIsPileupFromSPDInMultBins(0x0),
  fIsPhysSelected(0x0),
  fAODEvent(0x0)
{
  //
  //Default ctor
  //
  fVertex[0] = 999.; fVertex[1] = 999.; fVertex[2] = 999.;
  for(Int_t i = 0;i < 300;i++){
    fPt[i] = 999;
    fE[i] = 999;
    fPx[i] = 999;
    fPy[i] = 999;
    fPz[i] = 999;
    fY[i] = 999;
    fEta[i] = 999;
    fMatchTrig[i] = 999;
    fTrackChi2[i] = 999;
    fMatchTrigChi2[i] = 999;
    fDCA[i] = 999;
    fCharge[i] = 999;
    fpDCA[i] = 999;   //pDCA
    fRAtAbsEnd[i] = 999;
    fMuonId[i] = 999;
  }
  for(Int_t i = 0;i < 3000;i++){
    fDimuPt[i] = 999;
    fDimuPx[i] = 999;
    fDimuPy[i] = 999;
    fDimuPz[i] = 999;
    fDimuY[i] = 999;
    fDimuMass[i] = 999;
    fDimuCharge[i] = 999;
    fDimuMatch[i] = 999;
    ////////////////////////////////////////////////////////////////////////////
    fCostHE[i] = 999;
    fPhiHE[i] = 999;
    fCostCS[i] = 999;
    fPhiCS[i] = 999;
    ////////////////////////////////////////////////////////////////////////////
    for(Int_t k = 0;k < 2;k++) fDimuMu[i][k] = 999;
  }
}

//__________________________________________________________________________
AliAnalysisTaskPbPbJPsiTree_Dimuon::AliAnalysisTaskPbPbJPsiTree_Dimuon(const char *name) :
  AliAnalysisTaskSE(name),
  fOutput(0x0),
  fNevt(0x0),
  fBeamEnergy(0.),
  fkAnalysisType(0x0),
  fPeriod(0x0),
  fCountTotEv(0x0),
  fCountTrigger(0x0),
  fCountCINT7(0x0),
  fCountCMUL7(0x0),
  fCountCMLL7(0x0),
  fCountCMSL7(0x0),
  fCountCMSH7(0x0),
  fMuonTrackCuts(0x0), //pDCA
  fNMuons(0x0),
  fNTracklets(0x0),
  fNContributors(0x0),
  fNDimu(0x0),
  fPercentV0M(0x0),
  fPercentCL0(0x0),
  fPercentCL1(0x0),
  fPercentV0A(0x0),
  fPercentV0C(0x0),
  fPercentZNA(0x0),
  fPercentZNC(0x0),
  fIsPileupFromSPDInMultBins(0x0),
  fIsPhysSelected(0x0),
  fAODEvent(0x0)
{
 //
  // Constructor. Initialization of Inputs and Outputs
  //
  Info("AliAnalysisTaskPbPbJPsiTree_Dimuon","Calling Constructor");

  fMuonTrackCuts = new AliMuonTrackCuts("StandardMuonTrackCuts", "TestStandardMuonTrackCuts");
  fMuonTrackCuts->SetFilterMask(AliMuonTrackCuts::kMuPdca);  //I select the Pdca cut in this way
  fMuonTrackCuts->SetAllowDefaultParams(kTRUE);

  fVertex[0] = 999.; fVertex[1] = 999.; fVertex[2] = 999.;
  for(Int_t i = 0;i < 300;i++){
    fPt[i] = 999;
    fE[i] = 999;
    fPx[i] = 999;
    fPy[i] = 999;
    fPz[i] = 999;
    fY[i] = 999;
    fEta[i] = 999;
    fMatchTrig[i] = 999;
    fTrackChi2[i] = 999;
    fMatchTrigChi2[i] = 999;
    fDCA[i] = 999;
    fCharge[i] = 999;
    fRAtAbsEnd[i] = 999;
    fpDCA[i] = 999.;   //pDCA
    fMuonId[i] = 999;
  }
  for(Int_t i = 0;i < 3000;i++){
    fDimuPt[i] = 999;
    fDimuPx[i] = 999;
    fDimuPy[i] = 999;
    fDimuPz[i] = 999;
    fDimuY[i] = 999;
    fDimuMass[i] = 999;
    fDimuCharge[i] = 999;
    fDimuMatch[i] = 999;
    ////////////////////////////////////////////////////////////////////////////
    fCostHE[i] = 999;
    fPhiHE[i] = 999;
    fCostCS[i] = 999;
    fPhiCS[i] = 999;
    ////////////////////////////////////////////////////////////////////////////
    for(Int_t k = 0;k < 2;k++) fDimuMu[i][k] = 999;
  }
  DefineOutput(1,TList::Class());
}

//___________________________________________________________________________
AliAnalysisTaskPbPbJPsiTree_Dimuon& AliAnalysisTaskPbPbJPsiTree_Dimuon::operator=(const AliAnalysisTaskPbPbJPsiTree_Dimuon& c)
{
  //
  // Assignment operator
  //
  if (this!=&c) {
    AliAnalysisTaskSE::operator=(c) ;
   // fNevt = c.fNevt ;
  }
  return *this;
}

//___________________________________________________________________________
AliAnalysisTaskPbPbJPsiTree_Dimuon::AliAnalysisTaskPbPbJPsiTree_Dimuon(const AliAnalysisTaskPbPbJPsiTree_Dimuon& c) :
  AliAnalysisTaskSE(c),
  fOutput(c.fOutput),
  fNevt(c.fNevt),
  fBeamEnergy(c.fBeamEnergy),
  fkAnalysisType(c.fkAnalysisType),
  fPeriod(c.fPeriod),
  fCountTotEv(c.fCountTotEv),
  fCountTrigger(c.fCountTrigger),
  fCountCINT7(c.fCountCINT7),
  fCountCMUL7(c.fCountCMUL7),
  fCountCMLL7(c.fCountCMLL7),
  fCountCMSL7(c.fCountCMSL7),
  fCountCMSH7(c.fCountCMSH7),
  fMuonTrackCuts(c.fMuonTrackCuts),  //pDCA
  fNMuons(c.fNMuons),
  fNTracklets(c.fNTracklets),
  fNContributors(c.fNContributors),
  fNDimu(c.fNDimu),
  fPercentV0M(c.fPercentV0M),
  fPercentCL0(c.fPercentCL0),
  fPercentCL1(c.fPercentCL1),
  fPercentV0A(c.fPercentV0A),
  fPercentV0C(c.fPercentV0C),
  fPercentZNA(c.fPercentZNA),
  fPercentZNC(c.fPercentZNC),
  fIsPileupFromSPDInMultBins(c.fIsPileupFromSPDInMultBins),
  fIsPhysSelected(c.fIsPhysSelected),
  fAODEvent(c.fAODEvent)
 {
  //
  // Copy Constructor
  //
}

//___________________________________________________________________________
AliAnalysisTaskPbPbJPsiTree_Dimuon::~AliAnalysisTaskPbPbJPsiTree_Dimuon() {
  //
  //destructor
  //
  Info("~AliAnalysisTaskPbPbJPsiTree_Dimuon","Calling Destructor");
  //if (AliAnalysisManager::GetAnalysisManager()->GetAnalysisType() != AliAnalysisManager::kProofAnalysis) delete fOutputTree;
  if( ! AliAnalysisManager::GetAnalysisManager() || ! AliAnalysisManager::GetAnalysisManager() -> IsProofMode()){
    if(fOutput){
      delete fOutput;
      fOutput = 0;
    }
  }
}
//___________________________________________________________________________
//
////ADD THE FOLLOWING 6 LINES!!!
void AliAnalysisTaskPbPbJPsiTree_Dimuon::NotifyRun()
{
//fMuonTrackCuts->GetMuonTrackCuts().SetPassName("pass2_muon");
//fMuonTrackCuts->SetAllowDefaultParams(kTRUE);
fMuonTrackCuts->SetRun(fInputHandler);
}
//___________________________________________________________________________
void AliAnalysisTaskPbPbJPsiTree_Dimuon::UserCreateOutputObjects(){
  fOutput = new TList();
  fOutput -> SetOwner();

  //TH1F *histProva = new TH1F("histProva","histProva",500,0.,50.);
  TH1D *histAllPtSM = new TH1D("histAllPtSM","histAllPtSM",500,0.,50.);
  TH1D *histLowPtSM = new TH1D("histLowPtSM","histLowPtSM",500,0.,50.);
  TH1D *histAllPtDM = new TH1D("histAllPtDM","histAllPtDM",500,0.,50.);
  TH1D *histLowPtDM = new TH1D("histLowPtDM","histLowPtDM",500,0.,50.);

  fOutput -> Add(histAllPtSM);
  fOutput -> Add(histLowPtSM);
  fOutput -> Add(histAllPtDM);
  fOutput -> Add(histLowPtDM);

  fOutput->ls();

 PostData(1,fOutput);

}

//_________________________________________________
void AliAnalysisTaskPbPbJPsiTree_Dimuon::UserExec(Option_t *)
{
  fNMuons = 0;
  fNTracklets = -1;
  fNContributors = -1;
  fNDimu = 0;
  fPercentV0M = -1.;
  fPercentCL0 = -1.;
  fPercentCL1 = -1.;
  fPercentV0A = -1.;
  fPercentV0C = -1.;
  fPercentZNA = -1.;
  fPercentZNC = -1.;
  fVertex[0] = 999.; fVertex[1] = 999.; fVertex[2] = 999.;
  for(Int_t i = 0;i < 300;i++){
    fPt[i] = 999.;
    fE[i] = 999.;
    fPx[i] = 999;
    fPy[i] = 999;
    fPz[i] = 999;
    fY[i] = 999.;
    fEta[i] = 999.;
    fMatchTrig[i] = 999.;
    fTrackChi2[i] = 999.;
    fMatchTrigChi2[i] = 999.;
    fDCA[i] = 999.;
    fCharge[i] = 999;
    fpDCA[i] = 999.;  //pDCA
    fRAtAbsEnd[i] = 999;
    fMuonId[i] = 999;
  }
  for(Int_t i = 0;i < 3000;i++){
    fDimuPt[i] = 999.;
    fDimuPx[i] = 999.;
    fDimuPy[i] = 999.;
    fDimuPz[i] = 999.;
    fDimuY[i] = 999.;
    fDimuMass[i] = 999.;
    fDimuCharge[i] = 999.;
    fDimuMatch[i] = 0;
    ////////////////////////////////////////////////////////////////////////////
    fCostHE[i] = 999.;
    fPhiHE[i] = 999.;
    fCostCS[i] = 999.;
    fPhiCS[i] = 999.;
    ////////////////////////////////////////////////////////////////////////////
    for(Int_t k = 0;k < 2;k++) fDimuMu[i][k] = 999;
  }

//
// Execute analysis for current event
//
  fAODEvent = dynamic_cast<AliAODEvent*> (InputEvent());
  if ( ! fAODEvent ) {
    AliError ("AOD event not found. Nothing done!");
    return;
  }


  char hname[200];
  AliAODHeader *aodheader = dynamic_cast<AliAODHeader*>(fAODEvent -> GetHeader());
  TString firedtrigger = aodheader -> GetFiredTriggerClasses();
  sprintf(fTrigClass,"%s",firedtrigger.Data());
  finpmask = aodheader -> GetL0TriggerInputs();

  Bool_t TriggerSelected_CINT7 = kFALSE;
  Bool_t TriggerSelected_CMUL7 = kFALSE;

  if(firedtrigger.Contains("CINT7-B-NOPF-MUFAST")){TriggerSelected_CINT7 = kTRUE;}
  if(firedtrigger.Contains("CMUL7-B-NOPF-MUFAST")){TriggerSelected_CMUL7 = kTRUE;}

  // to apply physics selection
  UInt_t fSelectMask = ((AliInputEventHandler*)(AliAnalysisManager::GetAnalysisManager() -> GetInputEventHandler())) -> IsEventSelected();
  fIsPhysSelected = fSelectMask & (AliVEvent::kMuonUnlikeLowPt7 | AliVEvent::kMuonLikeLowPt7 | AliVEvent::kMuonSingleLowPt7 | AliVEvent::kMuonSingleHighPt7  | AliVEvent::kINT7inMUON  | AliVEvent::kINT7);
  // warning: I added AliVEvent::kINT7 (MB in CENT cluster, while kINT7inMUON is MB in MUFAST)
  //printf("trigger = %s\n\n",fTrigClass);
  // centrality
  // https://twiki.cern.ch/twiki/bin/viewauth/ALICE/PACentStudiesRun2
  Float_t PercV0M = 300;
  Float_t PercCL0 = 300;
  Float_t PercCL1 = 300;
  Float_t PercV0A = 300;
  Float_t PercV0C = 300;
  Float_t PercZNA = 300;
  Float_t PercZNC = 300;

  AliMultSelection *MultSelection = 0x0;
  MultSelection = (AliMultSelection * ) fAODEvent -> FindListObject("MultSelection");
  if(!MultSelection){
    //If you get this warning (and lPercentiles 300) please check that the AliMultSelectionTask actually ran (before your task)
    AliWarning("AliMultSelection object not found!");
  }else{
    PercV0M = MultSelection -> GetMultiplicityPercentile("V0M");
    PercCL0 = MultSelection -> GetMultiplicityPercentile("CL0");
    PercCL1 = MultSelection -> GetMultiplicityPercentile("CL1");
    PercV0A = MultSelection -> GetMultiplicityPercentile("V0A");
    PercV0C = MultSelection -> GetMultiplicityPercentile("V0C");
    PercZNA = MultSelection -> GetMultiplicityPercentile("ZNA");
    PercZNC = MultSelection -> GetMultiplicityPercentile("ZNC");
  }
  fPercentV0M = PercV0M;
  fPercentCL0 = PercCL0;
  fPercentCL1 = PercCL1;
  fPercentV0A = PercV0A;
  fPercentV0C = PercV0C;
  fPercentZNA = PercZNA;
  fPercentZNC = PercZNC;

  // fIsPileupFromSPDInMultBins = fAODEvent->IsPileupFromSPDInMultBins();

  AliAODVertex *PrimVertex =  fAODEvent -> GetPrimaryVertex();
  fNContributors = PrimVertex -> GetNContributors();
  //fNTracklets = PrimVertex->GetNumberOfTracklets();
  fVertex[0] = PrimVertex -> GetX();
  fVertex[1] = PrimVertex -> GetY();
  fVertex[2] = PrimVertex -> GetZ();

  //
  // build dimuon object starting from single muons
  //
  //-------------------------------------------------------------------------
  // uncomment if reading AliMuonAODs (in PbPb)
  //-------------------------------------------------------------------------
  Int_t numdimu = 0;
  Int_t nummu = 0;

  Int_t ntracks = fAODEvent -> GetNumberOfTracks();

  // Single Muon Loop
  for(Int_t i = 0;i < ntracks;i++){
    //printf("i=%d \n",i);
    AliAODTrack *track = (AliAODTrack*) fAODEvent -> GetTrack(i);
    if(!fMuonTrackCuts -> IsSelected(track)){continue;}
    if(track -> IsMuonTrack()){
      if(TriggerSelected_CINT7){
        if(track -> Eta() > -4 && track -> Eta() < -2.5){
          if(track -> GetRAtAbsorberEnd() > 17.6 && track -> GetRAtAbsorberEnd() < 89.5){
            //printf("Eta = %f ; RAbs = %f ; TrMatch = %i \n",track -> Eta(),track -> GetRAtAbsorberEnd(),track -> GetMatchTrigger());
            if(track -> GetMatchTrigger() >= 1){((TH1D*)(fOutput -> FindObject("histAllPtSM"))) -> Fill(track -> Pt());}
            if(track -> GetMatchTrigger() >= 2){((TH1D*)(fOutput -> FindObject("histLowPtSM"))) -> Fill(track -> Pt());}
          }
        }
      }
    }
  }

  // Di-Muon Loop
  /*cout << "N DIMU = " << fAODEvent -> GetNumberOfDimuons() << endl;
  for(int i = 0;i < fAODEvent -> GetNumberOfDimuons();i++){
    AliAODDimuon *dimu = dynamic_cast <AliAODDimuon*> (fAODEvent -> GetDimuon(i));
    AliAODTrack *mu0 = dimu -> GetMu(0);
    AliAODTrack *mu1 = dimu -> GetMu(1);

    if(!fMuonTrackCuts -> IsSelected(mu0)){continue;}
    if(!fMuonTrackCuts -> IsSelected(mu1)){continue;}

    Double_t DimuMass = 999;
    Double_t DimuPt = -999;
    Double_t DimuY = -999;
    Double_t Match_Mu0 = -999;
    Double_t Match_Mu1 = -999;
    Double_t Pt_Mu0 = -999;
    Double_t Pt_Mu1 = -999;
    Double_t Eta_Mu0 = -999;
    Double_t Eta_Mu1 = -999;
    Double_t RAbs_Mu0 = -999;
    Double_t RAbs_Mu1 = -999;	  
    
    Match_Mu0 = mu0 -> GetMatchTrigger();
    Match_Mu1 = mu1 -> GetMatchTrigger();
    Eta_Mu0 = mu0 -> Eta();
    Eta_Mu1 = mu1 -> Eta();
    RAbs_Mu0 = mu0 -> GetRAtAbsorberEnd();
    RAbs_Mu1 = mu1 -> GetRAtAbsorberEnd();       
    Pt_Mu0 = mu0 -> Pt();
    Pt_Mu1 = mu1 -> Pt();

    cout << "LOOP DIMUONI" << endl;
    if((Eta_Mu0 > -4 && Eta_Mu0 < -2.5) && (Eta_Mu1 > -4 && Eta_Mu1 < -2.5)){
      cout << "ETA DIMUONI" << endl;
      if((RAbs_Mu0 > 17.6 && RAbs_Mu0 < 89.5) && (RAbs_Mu1 > 17.6 && RAbs_Mu1 < 89.5)){
        cout << "RABS DIMUONI" << endl;
        DimuY = dimu -> Y();
        if(DimuY > -4 && DimuY < -2.5){
          cout << "RAPIDITY DIMUONI" << endl;
          if(dimu -> Charge() == 0){
            cout << "CARICA" << endl;
            if(TriggerSelected_CINT7){
              cout << "TRIGGER" << endl;
              if(DimuPt > 0 && DimuPt < 50){
                cout << "PT" << endl;
                if(Match_Mu0 >= 1){((TH1D*)(fOutput -> FindObject("histAllPtDM"))) -> Fill(Pt_Mu0);}
		            if(Match_Mu1 >= 1){((TH1D*)(fOutput -> FindObject("histAllPtDM"))) -> Fill(Pt_Mu1);}
		            if(Match_Mu0 >= 2){((TH1D*)(fOutput -> FindObject("histLowPtDM"))) -> Fill(Pt_Mu0);}
		            if(Match_Mu1 >= 2){((TH1D*)(fOutput -> FindObject("histLowPtDM"))) -> Fill(Pt_Mu1);}
              }
            }
          }
        }
      }
    }
  }*/


  for(int i = 0;i < ntracks;i++){
    AliAODTrack *mu0 = (AliAODTrack*) fAODEvent -> GetTrack(i);
    if(!fMuonTrackCuts -> IsSelected(mu0)){continue;}
    if(mu0 -> IsMuonTrack()){
      if(mu0 -> Eta() > -4 && mu0 -> Eta() < -2.5){
        if(mu0 -> GetRAtAbsorberEnd() > 17.6 && mu0 -> GetRAtAbsorberEnd() < 89.5){
          for(int j = i+1;j < ntracks;j++){
            AliAODTrack *mu1 = (AliAODTrack*) fAODEvent -> GetTrack(j);
            if(!fMuonTrackCuts -> IsSelected(mu1)){continue;}
            if(mu1 -> IsMuonTrack()){
              if(mu1 -> Eta() > -4 && mu1 -> Eta() < -2.5){
                if(mu1 -> GetRAtAbsorberEnd() > 17.6 && mu1 -> GetRAtAbsorberEnd() < 89.5){
                  AliAODDimuon *dimu = new AliAODDimuon(mu0,mu1);
                  if(dimu -> Y() > -4 && dimu -> Y() < -2.5){
                    if(dimu -> Charge() == 0){
                      if(TriggerSelected_CINT7){
                        if(dimu -> Pt() > 0 && dimu -> Pt() < 50){
                          if(mu0 -> GetMatchTrigger() >= 1){((TH1D*)(fOutput -> FindObject("histAllPtDM"))) -> Fill(mu0 -> Pt());}
                          if(mu1 -> GetMatchTrigger() >= 1){((TH1D*)(fOutput -> FindObject("histAllPtDM"))) -> Fill(mu1 -> Pt());}
                          if(mu0 -> GetMatchTrigger() >= 2){((TH1D*)(fOutput -> FindObject("histLowPtDM"))) -> Fill(mu0 -> Pt());}
                          if(mu1 -> GetMatchTrigger() >= 2){((TH1D*)(fOutput -> FindObject("histLowPtDM"))) -> Fill(mu1 -> Pt());}
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }

  PostData(1,fOutput);
}
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
  cout << "CosTheta HE = " << cost << endl;
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
  Double_t mu2Charge = Mu1 -> Charge();
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

   cout << "Phi HE = " << phi*(180./TMath::Pi()) << endl;
   /*cout << "x ---> ";
   xaxis.Print();
   cout << "y ---> ";
   yaxis.Print();
   cout << "z ---> ";
   zaxis.Print();
   cout << "p Dimu ---> ";
   (pMu1Dimu.Vect()).Print();
   cout << "p Proj = ";
   (pProjDimu).Print();
   cout << "p Targ = ";
   (pTargDimu).Print();*/
   //cout << "y.z = " << yaxis.Dot(zaxis) << endl;
   //cout << "x.z = " << xaxis.Dot(zaxis) << endl;
   //cout << "x.y = " << xaxis.Dot(yaxis) << endl;
   /*(yaxis.Cross(zaxis)).Print();
   (zaxis.Cross(xaxis)).Print();
   (xaxis.Cross(yaxis)).Print();
   cout << "Lorentz Vector = ";
   pDimuCM.Print();*/
   cout << "================================" << endl;
   cout << "TLorentzVector pProjLab = ";
   (pProjCM).Print();
   cout << "TLorentzVector pTargLab = ";
   (pTargCM).Print();
   cout << "TLorentzVector mu1Lab " << "(" << mu1Charge << ") = ";
   pMu1CM.Print();
   cout << "TLorentzVector mu2Lab" << "(" << mu2Charge << ") = ";
   pMu2CM.Print();
   cout << "================================" << endl;

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
  cout << "CosTheta CS = " << cost << endl;
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

   cout << "Phi CS = " << phi*(180./TMath::Pi()) << endl;
   return phi;
}
//______________________________________________________________________________
void AliAnalysisTaskPbPbJPsiTree_Dimuon::Terminate(Option_t *)
{

 }
