#ifndef AliAnalysisTaskReadJPsiMC_H
#define AliAnalysisTaskReadJPsiMC_H

/* Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. *
 * See cxx source for full Copyright notice                               */

#include "AliAnalysisTaskSE.h"

class TObjArray;
class AliVParticle;
class AliAODEvent;
class TLorentzVector;
//class TList;

class AliAnalysisTaskReadJPsiMC : public AliAnalysisTaskSE {
  public:

  AliAnalysisTaskReadJPsiMC();
  AliAnalysisTaskReadJPsiMC(const char *name);
  virtual ~AliAnalysisTaskReadJPsiMC();

  void UserCreateOutputObjects();
  void UserExec(Option_t *option);
  void Terminate(Option_t *);
  //virtual void NotifyRun(); 
  
  void SetBeamEnergy(Double_t en) {fBeamEnergy=en;}
  void SetAnalysisType(const char* type) {fkAnalysisType=type;}
  void SetPeriod(TString period) {fPeriod=period;}
    
 private:
  AliAnalysisTaskReadJPsiMC(const AliAnalysisTaskReadJPsiMC&);
  AliAnalysisTaskReadJPsiMC& operator=(const AliAnalysisTaskReadJPsiMC&);
     
 //protected:
     
  Double_t fBeamEnergy;   // Energy of the beam (required for the CS angle)    
  const char* fkAnalysisType; //ESD or AOD based analysis
  TString fPeriod; //period
  AliAODEvent* fAODEvent;      //! AOD event  //tolgo !
  TList *fOutput;  //!< List of histograms for data
  
 ClassDef(AliAnalysisTaskReadJPsiMC,1);
};

#endif
