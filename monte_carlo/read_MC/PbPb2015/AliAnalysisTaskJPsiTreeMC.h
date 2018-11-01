#ifndef AliAnalysisTaskJPsiTreeMC_H
#define AliAnalysisTaskJPsiTreeMC_H

/* Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. *
 * See cxx source for full Copyright notice                               */

#include "AliAnalysisTaskSE.h"
#include "TTreeStream.h"//why?

class TObjArray;
class AliVParticle;
class AliAODEvent;
class TLorentzVector;
//class TList;

class AliAnalysisTaskJPsiTreeMC : public AliAnalysisTaskSE {
  public:

  AliAnalysisTaskJPsiTreeMC();
  AliAnalysisTaskJPsiTreeMC(const char *name);
  virtual ~AliAnalysisTaskJPsiTreeMC();

  void UserCreateOutputObjects();
  void UserExec(Option_t *option);
  void Terminate(Option_t *);
  //virtual void NotifyRun();

  void SetBeamEnergy(Double_t en) {fBeamEnergy=en;}
  void SetAnalysisType(const char* type) {fkAnalysisType=type;}
  void SetPeriod(TString period) {fPeriod=period;}

 private:
  AliAnalysisTaskJPsiTreeMC(const AliAnalysisTaskJPsiTreeMC&);
  AliAnalysisTaskJPsiTreeMC& operator=(const AliAnalysisTaskJPsiTreeMC&);

 //protected:

  Double_t fBeamEnergy;   // Energy of the beam (required for the CS angle)
  const char* fkAnalysisType; //ESD or AOD based analysis
  TString fPeriod; //period

  TTree         *fOutputTree	;      //! tree output

  Int_t		fNMuons_gen;		// muon tracks in the event
  Int_t		fNMuons_rec;		// muon tracks in the event
  Double_t	fVertex[3];		// x,y,z vertex
  Double_t	fPt_rec[300];		 // single mu pT
  Double_t	fE_rec[300];			// single mu E
  Double_t	fPx_rec[300];		// single mu px
  Double_t	fPy_rec[300];		// single mu py
  Double_t	fPz_rec[300];		// single mu pz
  Double_t	fY_rec[300];		// single mu y
  Double_t	fEta_rec[300];		// single mu eta
  Int_t		fMatchTrig_rec[300];		// single mu match trigger
  Double_t	fTrackChi2_rec[300];		// single mu chi2 track
  Double_t	fMatchTrigChi2_rec[300];	// single mu chi2 of match trigger
  Int_t	        fCharge_rec[300];		// single mu charge
  Double_t	fRAtAbsEnd_rec[300];		// single mu distance from beam center at end abs
  Int_t     fMuonId_rec[300];

  Int_t		  fNDimu_gen;			// dimuons in the event
  //Int_t		  fDimuMu_gen[3000][2];	// reference to single mus
  Double_t	fDimuPt_gen[3000];			    // dimuon pT
  Double_t	fDimuPx_gen[3000]; 		    // dimuon px
  Double_t	fDimuPy_gen[3000]; 		    // dimuon py
  Double_t	fDimuPz_gen[3000]; 		    // dimuon pz
  Double_t	fDimuY_gen[3000];			// dimuon y
  Double_t	fDimuMass_gen[3000];		// dimuon invariant mass
  Int_t	    fDimuCharge_gen[3000];		// dimuon charge
  Int_t	    fDimuMatch_gen[3000];		// dimuon match
  //////////////////////////////////////////////////////////////////////////////
  //Int_t     fNonZeroPx;
  //Int_t     fDiff_index[300];
  //Int_t     fNdaughters[300];
  //Int_t		  fPDGcode[3000][3];
  //Double_t  fDiffPx_gen[3000];
  Double_t  fCostHE_gen[3000];
  Double_t  fPhiHE_gen[3000];
  Double_t  fCostCS_gen[3000];
  Double_t  fPhiCS_gen[3000];
  //////////////////////////////////////////////////////////////////////////////

  Int_t		fNDimu_rec;			// dimuons in the event
  //Int_t		fDimuMu_rec[3000][2];	// reference to single mus
  Double_t	fDimuPt_rec[3000];			    // dimuon pT
  Double_t	fDimuPx_rec[3000]; 		    // dimuon px
  Double_t	fDimuPy_rec[3000]; 		    // dimuon py
  Double_t	fDimuPz_rec[3000]; 		    // dimuon pz
  Double_t	fDimuY_rec[3000];			// dimuon y
  Double_t	fDimuMass_rec[3000];		// dimuon invariant mass
  Int_t	        fDimuCharge_rec[3000];		// dimuon charge
  Int_t	        fDimuMatch_rec[3000];		// dimuon match
  //////////////////////////////////////////////////////////////////////////////
  Double_t  fCostHE_rec[3000];
  Double_t  fPhiHE_rec[3000];
  Double_t  fCostCS_rec[3000];
  Double_t  fPhiCS_rec[3000];
  //////////////////////////////////////////////////////////////////////////////

  AliAODEvent* fAODEvent;      //! AOD event  //tolgo !
//  TList *fOutput;  //!< List of histograms for data

 ClassDef(AliAnalysisTaskJPsiTreeMC,1);
};

#endif
