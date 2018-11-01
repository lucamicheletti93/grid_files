AliAnalysisTaskJPsiTreeMC *AddTaskJPsiTreeMC_Grid(Int_t run){

//****************************************************************************************
// Add task class.
// The attached class prepares and draws some kinematical distributions of muons/dimuons
// Roberta
//****************************************************************************************

   printf("Creating Task for Muon/Dimuon Histos\n");

   // Get the pointer to the existing analysis manager via the static access method.
   //==============================================================================
   AliAnalysisManager *mgr = AliAnalysisManager::GetAnalysisManager();
   if (!mgr) {
      ::Error("AddTaskppJPsi", "No analysis manager to connect to.");
      return NULL;
   }
   TString fnameout_norun;
   TString fnameout;
   fnameout_norun = "MCJpsiTreefirststep_%d.root";
   fnameout.Form(fnameout_norun.Data(), run);
   printf("Fnameout = %s\n",fnameout.Data());


   AliAnalysisDataContainer *coutput1 = mgr->CreateContainer("cTree0",TTree::Class(),AliAnalysisManager::kOutputContainer,fnameout);

   AliAnalysisTaskJPsiTreeMC *MCJPsiTask = new AliAnalysisTaskJPsiTreeMC("AliAnalysisTaskJPsiTreeMC");

   MCJPsiTask->SetBeamEnergy(5.02);
   mgr->AddTask(MCJPsiTask);

   mgr->ConnectInput(MCJPsiTask,0,mgr->GetCommonInputContainer());
   mgr->ConnectOutput(MCJPsiTask,1,coutput1);

   return MCJPsiTask;
}
