#if !defined(__CINT__) || defined(__MAKECINT__)
#include "AliAnalysisAlien.h"
#endif

AliAnalysisGrid* CreateAlienHandler(const char *runMode, TString GridDir, TString DataPattern, Int_t RunNumber, TString AliPhysicsVersion, Bool_t gridMerge)
{

  AliAnalysisAlien *plugin = new AliAnalysisAlien();

  plugin->SetRunMode(runMode); //Set the run mode (can be "full", "test", "offline", "submit" or "terminate")

  plugin->SetNtestFiles(1); // num of test files in "test" mode

  plugin->SetAliPhysicsVersion(AliPhysicsVersion.Data());

  plugin->AddIncludePath("-I$ALICE_ROOT/include -I$ALICE_PHYSICS/include");

  plugin->SetDataPattern(DataPattern.Data());
  plugin->SetGridDataDir(GridDir.Data()); // Data
  //plugin->SetRunPrefix("000");

  plugin->AddRunNumber(RunNumber);  //provide run number COMMENTATO
  //  plugin->SetRunRange(138653, 138666);  //Alternatively use run range

  char outdirname[250];  // Define alien work directory where all files will be copied. Relative to alien $HOME.
//  sprintf(outdirname,"pA2016/8TeV/LHC16r/MC/MC_JPsi_systeff/MCTrees/%d",RunNumber);
//  sprintf(outdirname,"pA2016/8TeV/LHC16r/MC/MC_JPsi_LHC16n/MCTrees/%d",RunNumber);
  //sprintf(outdirname,"MC_pA_Psi2s_first_step/pA_output_tree/%d",RunNumber);
  //sprintf(outdirname,"MC_Jpsi_2017/pA_output_tree/%d",RunNumber);
  //sprintf(outdirname,"MC_PbPb_Jpsi_2015/LHC15o/PbPb_output_tree/%d",RunNumber);
  sprintf(outdirname,"MC_PbPb_Jpsi_2018c11_nofastb/PbPb_output_tree/%d",RunNumber);

  plugin->SetGridWorkingDir(outdirname);  // NOTE: Change name here every new run!!!eclare alien output directory. Relative to working directory.
  plugin->SetGridOutputDir("OutputTree"); // In this case will be $HOME/work/output
  plugin->SetOutputToRunNo(kFALSE); // we want the run number as output subdirectory
  plugin->SetDefaultOutputs(kTRUE);
 // plugin->SetMergeExcludes("AliAOD.Muons.root");

  plugin->SetMergeViaJDL(gridMerge);

  plugin->SetAnalysisSource("AliAnalysisTaskReadJPsiMC.cxx AliAnalysisTaskJPsiTreeMC.cxx");
  plugin->SetAdditionalLibs("AliAnalysisTaskReadJPsiMC.cxx AliAnalysisTaskReadJPsiMC.h AddTaskReadJPsiMC_Grid.C AliAnalysisTaskJPsiTreeMC.cxx AliAnalysisTaskJPsiTreeMC.h AddTaskJPsiTreeMC_Grid.C");

  plugin->SetOverwriteMode(kFALSE); // Declare the output file names separated by blanks.(can be like: file.root or file.root@ALICE::Niham::File)

  Int_t nNoOfInputFiles=0;  // Optionally set maximum number of input files/subjob (default 100, put 0 to ignore)
  if (nNoOfInputFiles != 0) plugin->SetSplitMaxInputFileNumber(nNoOfInputFiles);
//   plugin->SetMaxInitFailed(15); // Optionally set number of failed jobs that will trigger killing waiting sub-jobs.
  plugin->SetMasterResubmitThreshold(90); // Optionally resubmit threshold.
  plugin->SetTTL(18000); // Optionally set time to live (default 30000 sec)
  plugin->SetInputFormat("xml-single"); // Optionally set input format (default xml-single)

  return plugin;
}
