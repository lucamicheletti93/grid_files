#if !defined(__CINT__) || defined(__MAKECINT__)
#include <stdio.h>
#include <iostream>
#include <fstream>

#include <TCanvas.h>
#include <TTree.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TProfile.h>
#include <TStyle.h>
#include <TLegend.h>
#include <TLine.h>
#include <TList.h>
#include <TSystem.h>
#include <TGrid.h>
#include <TString.h>
#include <TStopwatch.h>
#include <TGraphErrors.h>
#include <TMath.h>
#include <TStopwatch.h>
#include "/home/luca/GITHUB/polarization_classes/DataProcessor.h"
#endif

void checkTrigger(){
  gStyle -> SetOptStat(0);

  const int nRuns = 137;
  int runNumber[nRuns] = {246994,246991,246989,246984,246982,246980,246949,246948,246945,246942,246937,246930,246871,246867,246865,246864,246859,246855,246851,246847,246846,246845,246844,246809,246808,
                          246807,246806,246805,246804,246765,246763,246760,246759,246758,246757,246755,246751,246750,246676,246675,246495,246493,246488,246487,246434,246433,246431,246428,246424,246392,
                          246391,246390,246276,246275,246272,246225,246222,246220,246217,246182,246181,246178,246153,246152,246151,246148,246115,246113,246089,246087,246053,246049,246048,246042,246037,
                          246036,246012,246003,246001,245996,245963,245954,245952,245949,245833,245831,245829,245793,245785,245775,245766,245759,245752,245738,245731,245729,245705,245700,245692,245683,
                          245554,245543,245542,245540,245535,245507,245505,245504,245501,245496,245450,245446,245410,245409,245407,245401,245353,245347,245346,245345,245343,245259,245253,245233,245232,
                          245231,245152,245151,245146,245145,245068,245066,245064,244983,244982,244980,244918};


  /*Float_t fPercentV0M;
  Bool_t fIsPhysSelected;
  char fTrigClass[500];

  TFile *fileTest = new TFile("/media/luca/488AE2208AE20A70/PbPb_2015_Trees_pDCA/Tree_244982.root","READ");
  TTree *treeTest = (TTree*) fileTest -> Get("PbPbTree");
  treeTest -> SetBranchAddress("PercentV0M",&fPercentV0M);
  treeTest -> SetBranchAddress("IsPhysSelected",&fIsPhysSelected);
  treeTest -> SetBranchAddress("FiredTriggerClasses",fTrigClass);

  TH1F *hPercentileV0M_CINT7 = new TH1F("hPercentileV0M_CINT7","hPercentileV0M_CINT7",201,-1,200);
  for(int i = 0;i < treeTest -> GetEntries();i++){
    treeTest -> GetEntry(i);
    //if(fIsPhysSelected){
      TString Trigger = fTrigClass;
      Bool_t TriggerSelected = kFALSE;
      if(Trigger.Contains("CINT7-B-NOPF-MUFAST")) TriggerSelected = kTRUE;
      if(TriggerSelected){
        hPercentileV0M_CINT7 -> Fill(fPercentV0M);
      }
    //}
  }

  hPercentileV0M_CINT7 -> Draw();
  return;*/

  Long_t *dummy1 = 0, *dummy2 = 0, *dummy3 = 0, *dummy4 = 0;
  for(int i = 0;i < nRuns;i++){
    if(gSystem -> GetPathInfo(Form("/media/luca/488AE2208AE20A70/PbPb_2015_Trees_pDCA/Tree_%i.root",runNumber[i]),dummy1,dummy2,dummy3,dummy4) != 0){
      printf("The file does not exist, plz process it \n");
      continue;
    }
    else{
      printf("The file exists! \n");
      if(gSystem -> GetPathInfo(Form("/home/luca/cernbox/JPSI/Jpsi_polarization_data_sync/hist_trigger_response_function/Hist_%i.root",runNumber[i]),dummy1,dummy2,dummy3,dummy4) != 0){
        printf("--->  The Histo does not exist, plz process it \n");
        TFile *fileData = new TFile(Form("/media/luca/488AE2208AE20A70/PbPb_2015_Trees_pDCA/Tree_%i.root",runNumber[i]),"READ");
        TTree *treeData = (TTree*) fileData -> Get("PbPbTree");
        DataProcessor checkTrig(treeData);
        checkTrig.ComputeTriggerResponseFunction("FullStat",Form("/home/luca/cernbox/JPSI/Jpsi_polarization_data_sync/hist_trigger_response_function/Hist_%i.root",runNumber[i]));
        fileData -> Close();
      }
      else{continue;}
    }
  }

  TH1D *histSumLowPtSM = new TH1D("histSumLowPtSM","",100,0.,10.);
  TH1D *histSumAllPtSM = new TH1D("histSumAllPtSM","",100,0.,10.);
  TH1D *histSumLowPtSMpDCA = new TH1D("histSumLowPtSMpDCA","",100,0.,10.);
  TH1D *histSumAllPtSMpDCA = new TH1D("histSumAllPtSMpDCA","",100,0.,10.);

  for(int i = 0;i < nRuns;i++){
    if(gSystem -> GetPathInfo(Form("/home/luca/cernbox/JPSI/Jpsi_polarization_data_sync/hist_trigger_response_function/Hist_%i.root",runNumber[i]),dummy1,dummy2,dummy3,dummy4) == 0){
      TFile *fileHistTriggerResponseFunction = new TFile(Form("/home/luca/cernbox/JPSI/Jpsi_polarization_data_sync/hist_trigger_response_function/Hist_%i.root",runNumber[i]));
      TH1D *histLowPtSM = (TH1D*) fileHistTriggerResponseFunction -> Get("fHistLowPtSM"); histLowPtSM -> SetDirectory(0); histSumLowPtSM -> Add(histLowPtSM);
      TH1D *histAllPtSM = (TH1D*) fileHistTriggerResponseFunction -> Get("fHistAllPtSM"); histAllPtSM -> SetDirectory(0); histSumAllPtSM -> Add(histAllPtSM);
      TH1D *histLowPtSMpDCA = (TH1D*) fileHistTriggerResponseFunction -> Get("fHistLowPtSMpDCA"); histLowPtSMpDCA -> SetDirectory(0); histSumLowPtSMpDCA -> Add(histLowPtSMpDCA);
      TH1D *histAllPtSMpDCA = (TH1D*) fileHistTriggerResponseFunction -> Get("fHistAllPtSMpDCA"); histAllPtSMpDCA -> SetDirectory(0); histSumAllPtSMpDCA -> Add(histAllPtSMpDCA);
      fileHistTriggerResponseFunction -> Close();
    }
  }

  TH1D *histTriggerResponseFunctionDataSM = new TH1D("histTriggerResponseFunctionDataSM","",100,0.,10.);
  histTriggerResponseFunctionDataSM -> Divide(histSumLowPtSM,histSumAllPtSM,1,1,"B");
  histTriggerResponseFunctionDataSM -> SetLineColor(kBlue);
  histTriggerResponseFunctionDataSM -> SetMarkerColor(kBlue);

  TH1D *histTriggerResponseFunctionDataSMpDCA = new TH1D("histTriggerResponseFunctionDataSMpDCA","",100,0.,10.);
  histTriggerResponseFunctionDataSMpDCA -> Divide(histSumLowPtSMpDCA,histSumAllPtSMpDCA,1,1,"B");
  histTriggerResponseFunctionDataSMpDCA -> SetLineColor(kRed);
  histTriggerResponseFunctionDataSMpDCA -> SetMarkerColor(kRed);

  TH2D *histGridTriggerResponseFunction = new TH2D("histGridTriggerResponseFunction","",100,0.,10.,100,0.,1.2);
  histGridTriggerResponseFunction -> GetXaxis() -> SetTitle("#it{p}_{T} (GeV/#it{c})");

  TLegend *legendGenCost = new TLegend(0.3,0.1,0.5,0.2);
  legendGenCost ->AddEntry(histTriggerResponseFunctionDataSM,"No pDCA","lp");
  legendGenCost -> AddEntry(histTriggerResponseFunctionDataSMpDCA,"With pDCA","lp");

  TCanvas *canvasTriggerResponseFunction = new TCanvas("canvasTriggerResponseFunction","canvasTriggerResponseFunction",20,20,600,600);
  histGridTriggerResponseFunction -> Draw();
  histTriggerResponseFunctionDataSM -> Draw("Esame");
  histTriggerResponseFunctionDataSMpDCA -> Draw("Esame");
  legendGenCost -> Draw();

  TH1D *histRatioTriggerResponseFunction = new TH1D("histRatioTriggerResponseFunction","",100,0.,10.);
  histRatioTriggerResponseFunction -> Divide(histTriggerResponseFunctionDataSMpDCA,histTriggerResponseFunctionDataSM,1,1);
  histRatioTriggerResponseFunction -> SetLineColor(kBlack);

  TCanvas *canvasRatioTriggerResponseFunction = new TCanvas("canvasRatioTriggerResponseFunction","canvasRatioTriggerResponseFunction",20,20,600,600);
  histRatioTriggerResponseFunction -> Draw();

  //============================================================================

  /*int RUN_NUMBER[137] = {246994,246991,246989,246984,246982,246980,246949,246948,246945,246942,246937,246930,246871,246867,246865,246864,246859,246855,246851,246847,246846,246845,246844,246809,246808,
                       246807,246806,246805,246804,246765,246763,246760,246759,246758,246757,246755,246751,246750,246676,246675,246495,246493,246488,246487,246434,246433,246431,246428,246424,246392,
                       246391,246390,246276,246275,246272,246225,246222,246220,246217,246182,246181,246178,246153,246152,246151,246148,246115,246113,246089,246087,246053,246049,246048,246042,246037,
                       246036,246012,246003,246001,245996,245963,245954,245952,245949,245833,245831,245829,245793,245785,245775,245766,245759,245752,245738,245731,245729,245705,245700,245692,245683,
                       245554,245543,245542,245540,245535,245507,245505,245504,245501,245496,245450,245446,245410,245409,245407,245401,245353,245347,245346,245345,245343,245259,245253,245233,245232,
                       245231,245152,245151,245146,245145,245068,245066,245064,244983,244982,244980,244918};

  char FILE_NAME_IN[400];
  //sprintf(FILE_NAME_IN,"TESTS/SLIM_VERSION/Tree_%i.root",RUN_NUMBER);
  //sprintf(FILE_NAME_IN,"GRID_FILES/Tree_%i.root",RUN_NUMBER);
  int RUN_MIN = 0;
  int RUN_MAX = 30;

  int CMUL7[137],CINT7[137];

  for(int j = RUN_MIN;j < RUN_MAX;j++){
    //sprintf(FILE_NAME_IN,"../../../PbPb_2015_TREE/Tree_%i.root",RUN_NUMBER[j]); //MAC PATH
    //sprintf(FILE_NAME_IN,"../../PbPb_2015_TREE/TREE_RELOADED/Tree_%i.root",RUN_NUMBER[j]); //MAC PATH
    //sprintf(FILE_NAME_IN,"../../../../PbPb_2015_TREE/TREE_RELOADED/Tree_%i.root",RUN_NUMBER[j]); //MAC PATH
    sprintf(FILE_NAME_IN,"/media/luca/488AE2208AE20A70/PbPb_2015_Trees_pDCA/Tree_%i.root",RUN_NUMBER[j]);

    int counterCMUL = 0;
    int counterCINT = 0;
    //OPENING THE FILE
    //============================================================================
    TChain *chain = new TChain("PbPbTree");
    Long_t *dummy1 = 0, *dummy2 = 0, *dummy3 = 0, *dummy4 = 0;
    if(gSystem -> GetPathInfo(FILE_NAME_IN,dummy1,dummy2,dummy3,dummy4) != 0){
      CMUL7[j] = 0;
      CINT7[j] = 0;
      continue;
    }

      printf("Opening %s\n",FILE_NAME_IN);
      chain -> Add(FILE_NAME_IN);

      char TrigClass[200];
      chain -> SetBranchAddress("FiredTriggerClasses",TrigClass);

      Int_t NEntries = chain -> GetEntries();
      //Int_t NEntries = 10000;
      for(int i = 0;i < NEntries;i++){
        printf("%i -> %i : %3.2f%\r",NEntries,i,(double) i/NEntries*100);
        chain -> GetEntry(i);
        TString Trigger = TrigClass;
        if(Trigger.Contains("CMUL7-B-NOPF-MUFAST")) counterCMUL++;
        if(Trigger.Contains("CINT7-B-NOPF-MUFAST")) counterCINT++;
      }
    printf("\n \n");
    printf("====================\n");
    printf("RUN = %i\n",RUN_NUMBER[j]);
    printf("CMUL7 = %i\n",counterCMUL);
    printf("CINT7 = %i\n",counterCINT);
    printf("====================\n");
    CMUL7[j] = counterCMUL;
    CINT7[j] = counterCINT;
  }

  //using namespace std;
  return;
  ofstream OUTPUT_FILE;
  OUTPUT_FILE.open ("check_trigger.txt");
  OUTPUT_FILE << "RUN NUMBER" << " " << "CMUL7" << " " << "CINT7" << "\n";
  for(int i = RUN_MIN;i < RUN_MAX;i++){
    //myfile << "Writing this to a file.\n";
    OUTPUT_FILE << RUN_NUMBER[i] << " " << CMUL7[i] << " " << CINT7[i] << "\n";
  }
  OUTPUT_FILE.close();*/
}
