/**************************************************************************
 * Copyright(c) 2013-2014, ALICE Experiment at CERN, All rights reserved. *
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

//#ifdef __ECLIPSE_IDE
#if !defined(__CINT__) || defined(__MAKECINT__)
#include "Riostream.h"
#include "TSystem.h"
#include "TChain.h"
#include "AliAnalysisTaskSE.h"
#include "AliAnalysisTask.h"
#include "AliAnalysisManager.h"
#include "AliAODInputHandler.h"

extern AliAnalysisGrid* CreateAlienHandler_Grid(const char *, Bool_t);
AliAnalysisTaskpPbJPsiTree_Dimuon* AddTaskpPbJPsiTree_Dimuon_Grid(Int_t );
AliAnalysisTaskpPbJPsi_Dimuon* AddTaskpPbJPsi_Dimuon_Grid(Int_t );
#endif

void Read_MC(const char *RunMode = "full",
            Int_t RunNumber = 266318,
		        Bool_t usePhysicsSelection = kFALSE,
            //TString GridDir="/alice/cern.ch/user/l/lmichele/MC_pA_Psi2s_first_step/out",
            //TString GridDir="/alice/cern.ch/user/p/pwgpp_mc/2017/33_Week/user_idas/Psi2S_MC/iter_00/Pbp/",
            //TString GridDir="/alice/sim/2017/LHC17j1a/",
            //TString GridDir = "/alice/cern.ch/user/l/lmichele/MC_PbPb_Jpsi_2015/LHC15o/out/",
            TString GridDir = "/alice/sim/2018/LHC18c11_nofastb/",


            TString DataPattern = "AOD/*/AliAOD.Muons.root",
            //TString DataPattern = "*AliAOD.Muons.root",
		        //TString DataPattern="*/1/*/AliAOD.Muons.root",
	          TString AliPhysicsVersion="vAN-20180930-1", // TO BE UPDATED EVERY TIME
	          Bool_t gridMerge = kTRUE){

  // RunMode can be set to "full" to produce Trees
  // RunMode can be set to "terminate" to do the merging of the Trees

  //------------------------------------------------------------------------------------
  // Load paths
  //------------------------------------------------------------------------------------
  gSystem -> AddIncludePath("-I$ALICE_PHYSICS/include");
  gSystem -> AddIncludePath("-I$ALICE_PHYSICS/OADB/COMMON/MULTIPLICITY");

  // lines to be included to set correctly the path to find my macros
  gROOT -> ProcessLine(".include $ALICE_PHYSICS/include");
  gROOT -> ProcessLine(".include $ALICE_ROOT/include");
  gROOT -> ProcessLine(".include $ROOTSYS/include");

  //------------------------------------------------------------------------------------
  // Handler and analysis manager
  //------------------------------------------------------------------------------------
  AliAnalysisManager *mgr = new AliAnalysisManager("Dimuon Tree creator");
  mgr -> SetDebugLevel(AliLog::kError);
 // mgr->SetRunFromPath(RunNumber);
  AliLog::SetGlobalLogLevel(AliLog::kDebug);

  AliAODInputHandler* aodH = new AliAODInputHandler();
  mgr -> SetInputEventHandler(aodH);

  AliAnalysisGrid *alienHandler = NULL;
  gROOT -> LoadMacro("CreateAlienHandler.C");
  alienHandler = CreateAlienHandler(RunMode,GridDir,DataPattern,RunNumber,AliPhysicsVersion,gridMerge);
  if(!alienHandler) return;
  mgr -> SetGridHandler(alienHandler);

  AliAnalysisDataContainer *cinput1 = NULL;
  cinput1 = mgr -> GetCommonInputContainer();

  //------------------------------------------------------------------------------------
  // Read centrality information (https://twiki.cern.ch/twiki/bin/viewauth/ALICE/PACentStudiesRun2)
  //------------------------------------------------------------------------------------
//   gROOT->LoadMacro("$ALICE_PHYSICS/OADB/COMMON/MULTIPLICITY/macros/AddTaskMultSelection.C");
//   AliMultSelectionTask * task = AddTaskMultSelection(kFALSE); // user mode:
//   task->SetUseDefaultCalib(kTRUE); // to use the default calib for runs not yet calibrated

  //------------------------------------------------------------------------------------
  // Add task to create a MC Tree
  //------------------------------------------------------------------------------------
  gROOT -> LoadMacro("AliAnalysisTaskJPsiTreeMC.cxx++g");  //NEEDED to run LOCALLY!!!!
  gROOT -> LoadMacro("AddTaskJPsiTreeMC_Grid.C");

  AliAnalysisTaskJPsiTreeMC *MCJPsiTreeTask = AddTaskJPsiTreeMC_Grid(RunNumber);

  //------------------------------------------------------------------------------------
  // Add task to project MC
  //------------------------------------------------------------------------------------
  gROOT -> LoadMacro("AliAnalysisTaskReadJPsiMC.cxx++g");  //NEEDED to run LOCALLY!!!!
  gROOT -> LoadMacro("AddTaskReadJPsiMC_Grid.C");
  AliAnalysisTaskReadJPsiMC* taskTree = AddTaskReadJPsiMC_Grid(RunNumber);

  if(usePhysicsSelection){
    taskTree ->SelectCollisionCandidates(AliVEvent::kMuonUnlikeLowPt7 |
    AliVEvent::kMuonLikeLowPt7 | AliVEvent::kINT7inMUON  | AliVEvent::kINT7);
    //warning: I added AliVEvent::kINT7
  }

  mgr -> AddTask(taskTree);

  //------------------------------------------------------------------------------------
  // Init analysis on GRID
  //------------------------------------------------------------------------------------
  if(!mgr -> InitAnalysis()) return;
  mgr -> PrintStatus();
  mgr -> StartAnalysis("grid");
}
