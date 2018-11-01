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

/* $Id: AliAnalysisTaskReadJPsiMC.cxx $ */

//-----------------------------------------------------------------------------
// Analysis task to compute muon/dimuon kinematic distributions
// The output is a list of histograms.
// The macro class can run on AOD or in the train with the ESD filter.
// R. Arnaldi
//
//-----------------------------------------------------------------------------

//#ifndef AliAnalysisTaskReadJPsiMC_CXX
//#define AliAnalysisTaskReadJPsiMC_CXX

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
#include "TLine.h"

#include "AliInputEventHandler.h"
#include "AliAODHeader.h"
#include "AliAODEvent.h"
#include "AliAODTrack.h"
#include "AliAnalysisManager.h"
#include "AliAnalysisTaskSE.h"
#include "AliAODMCParticle.h"
//#include "AliMultSelection.h"


#include "AliAnalysisTaskReadJPsiMC.h"

ClassImp(AliAnalysisTaskReadJPsiMC)
//__________________________________________________________________________
AliAnalysisTaskReadJPsiMC::AliAnalysisTaskReadJPsiMC() :
  AliAnalysisTaskSE(),
  fBeamEnergy(0.),
  fkAnalysisType(0x0),
  fPeriod(0x0),
  fAODEvent(0x0),
  fOutput(0x0)
{
  /// Default ctor.
}

//__________________________________________________________________________
AliAnalysisTaskReadJPsiMC::AliAnalysisTaskReadJPsiMC(const char *name) :
  AliAnalysisTaskSE(name),
  fBeamEnergy(0.),
  fkAnalysisType(0x0),
  fPeriod(0x0),
  fAODEvent(0x0),
  fOutput(0x0)
{
 //
  // Constructor. Initialization of Inputs and Outputs
  //
  Info("AliAnalysisTaskReadJPsiMC","Calling Constructor");

  DefineOutput(1,TList::Class());
}

//___________________________________________________________________________
AliAnalysisTaskReadJPsiMC& AliAnalysisTaskReadJPsiMC::operator=(const AliAnalysisTaskReadJPsiMC& c)
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
AliAnalysisTaskReadJPsiMC::AliAnalysisTaskReadJPsiMC(const AliAnalysisTaskReadJPsiMC& c) :
  AliAnalysisTaskSE(c),
  fBeamEnergy(c.fBeamEnergy),
  fkAnalysisType(c.fkAnalysisType),
  fPeriod(c.fPeriod),
  fAODEvent(c.fAODEvent),
  fOutput(c.fOutput)
 {
  //
  // Copy Constructor
  //
}

//___________________________________________________________________________
AliAnalysisTaskReadJPsiMC::~AliAnalysisTaskReadJPsiMC() {
  //
  //destructor
  //
  Info("~AliAnalysisTaskReadJPsiMC","Calling Destructor");
  if (AliAnalysisManager::GetAnalysisManager()->GetAnalysisType() != AliAnalysisManager::kProofAnalysis) delete fOutput;
}


//___________________________________________________________________________
void AliAnalysisTaskReadJPsiMC::UserCreateOutputObjects(){

  printf("\n\nsono in UserCreateOutputObject \n\n");

 //
 // output objects creation
 //
 fOutput = new TList();
 fOutput->SetOwner();

 //
 // MC signal
 //
  TH1D *hgenM_mother = new TH1D("hgenM_mother","hgenM_mother",100,0.,5.);
  TH1D *hgenPt_mother = new TH1D("hgenPt_mother","hgenPt_mother",150,0.,15.);
  TH1D *hgenY_mother = new TH1D("hgenY_mother","hgenY_mother",60,-4.,-2.5);

  TH1D *hgenM_mother_cuts = new TH1D("hgenM_mother_cuts","hgenM_mother_cuts",100,0.,5.);
  TH1D *hgenPt_mother_cuts = new TH1D("hgenPt_mother_cuts","hgenPt_mother_cuts",150,0.,15.);
  TH1D *hgenY_mother_cuts = new TH1D("hgenY_mother_cuts","hgenY_mother_cuts",60,-4.,-2.5);

  //////////////////////////////////////////////////////////////////////////////
  TH1D *hgenDiff_Px = new TH1D("hgenDiff_Px","hgenDiff_Px",1000,-0.2,0.2);
  TH2D *hgenDiff_PxPy = new TH2D("hgenDiff_PxPy","hgenDiff_PxPy",1000,-0.2,0.2,1000,-0.2,0.2);
  TH1D *hgenDiff_Pz = new TH1D("hgenDiff_Pz","hgenDiff_Pz",1000,-1.,1.);
  //////////////////////////////////////////////////////////////////////////////

 //
 // rec signal
 //
  TH1D *hrecM_cuts = new TH1D("hrecM_cuts","hrecM_cuts",100,0.,5.);
  TH1D *hrecPt_cuts = new TH1D("hrecPt_cuts","hrecPt_cuts",150,0.,15.);
  TH1D *hrecY_cuts = new TH1D("hrecY_cuts","hrecY_cuts",60,-4.,-2.5);

 fOutput->Add(hgenM_mother);
 fOutput->Add(hgenPt_mother);
 fOutput->Add(hgenY_mother);

 //////////////////////////////////////////////////////////////////////////////
 fOutput->Add(hgenDiff_Px);
 fOutput->Add(hgenDiff_PxPy);
 fOutput->Add(hgenDiff_Pz);
 //////////////////////////////////////////////////////////////////////////////

 fOutput->Add(hgenM_mother_cuts);
 fOutput->Add(hgenPt_mother_cuts);
 fOutput->Add(hgenY_mother_cuts);

 fOutput->Add(hrecM_cuts);
 fOutput->Add(hrecPt_cuts);
 fOutput->Add(hrecY_cuts);

 PostData(1,fOutput);

}

//_________________________________________________
void AliAnalysisTaskReadJPsiMC::UserExec(Option_t *)
{

  printf("\n\nsono in UserExec \n\n");

//
// Execute analysis for current event
//
  fAODEvent = dynamic_cast<AliAODEvent*> (InputEvent());
  if ( ! fAODEvent ) {
    AliError ("AOD event not found. Nothing done!");
    return;
  }

  //-----------------------------------------------
  // loop on events
  //-----------------------------------------------
  TClonesArray *mcarray = dynamic_cast<TClonesArray*>(fAODEvent->FindListObject(AliAODMCParticle::StdBranchName()));

  AliAODHeader *aodheader=dynamic_cast<AliAODHeader*>(fAODEvent->GetHeader());

   //-----------------------------------------------
   // loop on MC gen particles
   //-----------------------------------------------
    char hname[200];
    double diffx = 0;
    double diffy = 0;
    double diffz = 0;
    double mcpx,mumc0px,mumc1px;
    double mcpy,mumc0py,mumc1py;
    double mcpz,mumc0pz,mumc1pz;

    printf("\nmcarray->GetEntries()=%d\n",mcarray->GetEntries());

  for (Int_t i=0;i<mcarray->GetEntries();i++){
       AliAODMCParticle *mcp = (AliAODMCParticle *)mcarray->At(i);
       if(mcp->GetPdgCode()==443){
	   ((TH1D*)fOutput->FindObject("hgenM_mother"))->Fill(mcp->M());
	   ((TH1D*)fOutput->FindObject("hgenPt_mother"))->Fill(mcp->Pt());
	   ((TH1D*)fOutput->FindObject("hgenY_mother"))->Fill(mcp->Y());

     ///////////////////////////////////////////////////////////////////////////
     AliAODMCParticle *mcmu0 = (AliAODMCParticle *) mcarray -> At(mcp -> GetFirstDaughter());
     AliAODMCParticle *mcmu1 = (AliAODMCParticle *) mcarray -> At(mcp -> GetLastDaughter());
     mcpx = mcp -> Px();
     mumc0px = mcmu0 -> Px();
     mumc1px = mcmu1 -> Px();
     diffx = mumc0px + mumc1px - mcpx;
     mcpy = mcp -> Py();
     mumc0py = mcmu0 -> Py();
     mumc1py = mcmu1 -> Py();
     diffy = mumc0py + mumc1py - mcpy;
     mcpz = mcp -> Pz();
     mumc0pz = mcmu0 -> Pz();
     mumc1pz = mcmu1 -> Pz();
     diffz = mumc0pz + mumc1pz - mcpz;
     ((TH1D*)fOutput->FindObject("hgenDiff_Px"))->Fill(diffx);
     ((TH1D*)fOutput->FindObject("hgenDiff_PxPy"))->Fill(diffx,diffy);
     ((TH1D*)fOutput->FindObject("hgenDiff_Pz"))->Fill(diffz);
     ///////////////////////////////////////////////////////////////////////////

           if(mcp->Y()>-4 && mcp->Y()<-2.5){
	     if(mcp->Pt()<20){
  	       ((TH1D*)fOutput->FindObject("hgenM_mother_cuts"))->Fill(mcp->M());
	       ((TH1D*)fOutput->FindObject("hgenPt_mother_cuts"))->Fill(mcp->Pt());
	       ((TH1D*)fOutput->FindObject("hgenY_mother_cuts"))->Fill(mcp->Y());

              }
             }
	    }
	  }


   //-----------------------------------------------
   // loop on reconstructed particles
   //-----------------------------------------------
    char hname2[200];
    char hname3[200];

    Int_t ndimu=0;

    TRefArray *mutracks = new TRefArray();
    Int_t nmuons = fAODEvent->GetMuonTracks(mutracks);
    //printf("nmuons= %d\n",nmuons);
    for (Int_t i=0;i<nmuons;i++){
      AliAODTrack *mu0=(AliAODTrack*)mutracks->At(i);
      for(Int_t j=i+1;j<nmuons;j++){
        AliAODTrack *mu1=(AliAODTrack*)mutracks->At(j);
        AliAODDimuon *dimu=new AliAODDimuon(mu0,mu1);

        ndimu++;



//     for(int nd=0;nd<fAODEvent->GetNumberOfDimuons();nd++){
//       AliAODDimuon *dimu = dynamic_cast<AliAODDimuon*>(fAODEvent->GetDimuon(nd));
//       AliAODTrack *mu0 = dimu->GetMu(0);
//       AliAODTrack *mu1 = dimu->GetMu(1);

      Double_t DimuMass=999;
      Double_t DimuPt=-999;
      Double_t DimuY=-999;
      Double_t Match_Mu0=-999;
      Double_t Match_Mu1=-999;
      Double_t Pt_Mu0=-999;
      Double_t Pt_Mu1=-999;
      Double_t Eta_Mu0=-999;
      Double_t Eta_Mu1=-999;
      Double_t RAbs_Mu0=-999;
      Double_t RAbs_Mu1=-999;

      Match_Mu0=mu0->GetMatchTrigger();
      Match_Mu1=mu1->GetMatchTrigger();
      Eta_Mu0=mu0->Eta();
      Eta_Mu1=mu1->Eta();
      RAbs_Mu0=mu0->GetRAtAbsorberEnd();
      RAbs_Mu1=mu1->GetRAtAbsorberEnd();
      Pt_Mu0=mu0->Pt();
      Pt_Mu1=mu1->Pt();

      if((Eta_Mu0>-4 && Eta_Mu0<-2.5) && (Eta_Mu1>-4 && Eta_Mu1<-2.5)){
       if((RAbs_Mu0>17.6 && RAbs_Mu0<89.5) && (RAbs_Mu1>17.6 && RAbs_Mu1<89.5)){
	 if(Match_Mu0>1 && Match_Mu1>1){
           DimuY=dimu->Y();
           if(DimuY>-4 && DimuY<-2.5){
              DimuMass=dimu->Mass();
              if(dimu->Charge()==0) {
                DimuPt=dimu->Pt();
                if(dimu->Pt()<20) {

    	        ((TH1D*)(fOutput->FindObject("hrecM_cuts")))->Fill(DimuMass);
    	        ((TH1D*)(fOutput->FindObject("hrecPt_cuts")))->Fill(DimuPt);
    	        ((TH1D*)(fOutput->FindObject("hrecY_cuts")))->Fill(DimuY);


	        if(mu0->GetLabel()<0 || mu1->GetLabel()<0) continue;
	        AliAODMCParticle *mctrack0 = (AliAODMCParticle*) mcarray->At(mu0->GetLabel());
	        AliAODMCParticle *mctrack1 = (AliAODMCParticle*) mcarray->At(mu1->GetLabel());

		if(mu0->GetLabel() != mctrack0->GetLabel()) printf("\nCHECK 0: track label= %d, MC label=%d\n",mu0->GetLabel(),mctrack0->GetLabel());
                if(mu1->GetLabel() != mctrack1->GetLabel()) printf("\nCHECK 1: track label= %d, MC label=%d\n",mu1->GetLabel(),mctrack1->GetLabel());


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

//________________________________________________________________________
void AliAnalysisTaskReadJPsiMC::Terminate(Option_t *)
{

  printf("\n\nsono in terminate\n\n");

  gStyle->SetCanvasColor(10);
  gStyle->SetFrameFillColor(10);

  fOutput = dynamic_cast<TList*> (GetOutputData(1));

  TH1D *hgenM_mother = static_cast<TH1D*> (fOutput->FindObject("hgenM_mother"));
  TH1D *hgenPt_mother = static_cast<TH1D*> (fOutput->FindObject("hgenPtmother"));
  TH1D *hgenY_mother = static_cast<TH1D*> (fOutput->FindObject("hgenY_mother"));
  TH1D *hgenM_mother_cuts = static_cast<TH1D*> (fOutput->FindObject("hgenM_mother_cuts"));
  TH1D *hgenPt_mother_cuts = static_cast<TH1D*> (fOutput->FindObject("hgenPt_mother_cuts"));
  TH1D *hgenY_mother_cuts = static_cast<TH1D*> (fOutput->FindObject("hgenY_mother_cuts"));

  TH1D *hrecM_cuts = static_cast<TH1D*> (fOutput->FindObject("hrecM_cuts"));
  TH1D *hrecPt_cuts = static_cast<TH1D*> (fOutput->FindObject("hrecPt_cuts"));
  TH1D *hrecY_cuts = static_cast<TH1D*> (fOutput->FindObject("hrecY_cuts"));


  TCanvas *c1 = new TCanvas("c1","MC generated JPsi");
  c1->Divide(2,2);
  c1->cd(1);
  hgenM_mother->Draw();
  hgenM_mother_cuts->SetLineColor(2);
  hgenM_mother_cuts->Draw("same");
  hrecM_cuts->SetLineColor(8);
  hrecM_cuts->Draw("same");
//
//   c1->cd(2);
//   hgenPt_mother->Draw();
//   hgenPt_mother_cuts->SetLineColor(2);
//   hgenPt_mother_cuts->Draw("same");
//   hrecPt_cuts->SetLineColor(8);
//   hrecPt_cuts->Draw("same");
//
//   c1->cd(3);
//   hgenY_mother->Draw();
//   hgenY_mother_cuts->SetLineColor(2);
//   hgenY_mother_cuts->Draw("same");
//   hrecY_cuts->SetLineColor(8);
//   hrecY_cuts->Draw("same");


 }
