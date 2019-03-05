AliAnalysisTaskPbPbJPsiTree_Dimuon *AddTaskPbPbJPsiTree_Dimuon_Grid(Int_t RunNumber){

//****************************************************************************************
// Add task class to fill a tree with dimuon infos 
// Roberta
//****************************************************************************************

   printf("Creating Task for Muon/Dimuon Histos in PbPb\n");

   AliAnalysisManager *mgr = AliAnalysisManager::GetAnalysisManager();
   if (!mgr) {
      ::Error("AddTaskPbPbJPsi_Dimuon", "No analysis manager to connect to.");
      return NULL;
   }
   TString fnameout_norun = "Tree_%d.root";
   TString fnameout;
   fnameout.Form(fnameout_norun.Data(), RunNumber);
   printf("Fnameout = %s\n",fnameout.Data());

   AliAnalysisDataContainer *coutput1 = mgr -> CreateContainer("chist0",TList::Class(),AliAnalysisManager::kOutputContainer,fnameout);

   AliAnalysisTaskPbPbJPsiTree_Dimuon *PbPbJPsiTask = new AliAnalysisTaskPbPbJPsiTree_Dimuon("AliAnalysisTaskPbPbJPsiTree_Dimuon");

   ///////////////////////////////////////////////////////////////////////////// // WORNING!
   //PbPbJPsiTask -> SelectCollisionCandidates(AliVEvent::kMuonUnlikeLowPt7 | AliVEvent::kMuonLikeLowPt7 | AliVEvent::kMuonSingleLowPt7 | AliVEvent::kMuonSingleHighPt7  | AliVEvent::kINT7inMUON  | AliVEvent::kINT7 | AliVEvent::kMuonUnlikePB | AliVEvent::kMuonLikePB | AliVEvent::kMB);
   /////////////////////////////////////////////////////////////////////////////

   // WORNING!
   //PbPbJPsiTask -> SetBeamEnergy(5.44);  // define by hand the beam energy
   //PbPbJPsiTask -> SetBeamEnergy(2.51);  // define by hand the beam energy -> to be resetted for the new jobs
   PbPbJPsiTask -> SetBeamEnergy(5.02);
   mgr -> AddTask(PbPbJPsiTask);

   mgr -> ConnectInput(PbPbJPsiTask,0,mgr->GetCommonInputContainer());
   mgr -> ConnectOutput(PbPbJPsiTask,1,coutput1);

   return PbPbJPsiTask;
}
