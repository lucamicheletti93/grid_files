void compareTRF(){
    string filePath = "/home/luca/cernbox/JPSI/Jpsi_polarization_data_sync/new_hist_trigger_response_function_fixed/";
    TFile *fileTRF = new TFile(Form("%shist_TRF_sum.root",filePath.c_str()),"READ");
    TList *listTRF = (TList*) fileTRF -> Get("chist0");
    TH1D *histAllPtSM = (TH1D*) listTRF -> FindObject("histAllPtSM");  histAllPtSM -> Sumw2();
    TH1D *histLowPtSM = (TH1D*) listTRF -> FindObject("histLowPtSM"); histLowPtSM -> Sumw2();
    TH1D *histAllPtDM = (TH1D*) listTRF -> FindObject("histAllPtDM_25eta4"); histAllPtDM -> Sumw2();
    TH1D *histLowPtDM = (TH1D*) listTRF -> FindObject("histLowPtDM_25eta4"); histLowPtDM -> Sumw2();

    /*string nameFileBiswarupTRF = "/home/luca/cernbox/JPSI/Jpsi_polarization_data_sync/AccxEff/reweightingTest/testBiswarupTRF.root";
    TFile *fileBiswarupTRF = new TFile(nameFileBiswarupTRF.c_str(),"READ");
    TH1D *histBiswarupTRFData = (TH1D*) fileBiswarupTRF -> Get("histTriggerResponseFunctionDataSMpDCA"); histBiswarupTRFData -> SetDirectory(0);
    TH1D *histBiswarupTRFMC = (TH1D*) fileBiswarupTRF -> Get("histTriggerResponseFunctionMC"); histBiswarupTRFMC -> SetDirectory(0);
    fileBiswarupTRF -> Close();*/

    string nameFileBiswarupTRF = "/home/luca/Scrivania/nuovo/Data_divide_Pt.root";
    TFile *fileBiswarupTRF = new TFile(nameFileBiswarupTRF.c_str(),"READ");
    TH1D *histBiswarupTRFData = (TH1D*) fileBiswarupTRF -> Get("hData25y4"); histBiswarupTRFData -> SetDirectory(0);
    //TH1D *histBiswarupTRFMC = (TH1D*) fileBiswarupTRF -> Get("histTriggerResponseFunctionMC"); histBiswarupTRFMC -> SetDirectory(0);
    fileBiswarupTRF -> Close();
    
    histBiswarupTRFData -> SetLineColor(kBlack);

    TH1D *histTRFSM = new TH1D("histTRFSM","histTRFSM",500,0.,50.);
    histTRFSM -> Divide(histLowPtSM,histAllPtSM,1,1); histTRFSM -> SetLineColor(kRed);
 
    TH1D *histTRFDM = new TH1D("histTRFDM","histTRFDM",500,0.,50.);
    histTRFDM -> Divide(histLowPtDM,histAllPtDM,1,1); histTRFDM -> SetLineColor(kBlue);

    TCanvas *canvasComp = new TCanvas("canvasComp","canvasComp",600,600);
    //histTRFSM -> Draw("E");
    histTRFDM -> Draw("Esame");
    //histBiswarupTRFData -> Draw("Esame");


    TCanvas *canvasCompAllLow = new TCanvas("canvasCompAllLow","canvasCompAllLow",600,600);
    histAllPtDM -> Draw("E");
    histLowPtDM -> Draw("Esame");



    return;




    TFile *fLHC15o = new TFile("/home/luca/Scrivania/nuovo/Sum_LHC15o_PS.root");

    TH1D *h0Apt = (TH1D*)fLHC15o->Get("hAllpt_1M"); h0Apt -> SetLineColor(kRed);
    TH1D *h0Lpt = (TH1D*)fLHC15o->Get("hLpt_1M"); h0Lpt -> SetLineColor(kRed);

    /*TH2D *histGridComp = new TH2D("histGridComp","",100,0.,10.,100,0.,0.15);

    histAllPtDM -> Scale(1./histAllPtDM -> Integral());
    histLowPtDM -> Scale(1./histLowPtDM -> Integral());
    h0Apt -> Scale(1./h0Apt -> Integral());
    h0Lpt -> Scale(1./h0Lpt -> Integral());


    TCanvas *canvasComp = new TCanvas("canvasComp","canvasComp",1200,600);
    canvasComp -> Divide(2,1);

    canvasComp -> cd(1); histGridComp -> Draw(); histAllPtDM -> Draw("Esame"); h0Apt -> Draw("Esame");
    canvasComp -> cd(2); histGridComp -> Draw(); histLowPtDM -> Draw("Esame"); h0Lpt -> Draw("Esame");*/

    TH1D *histTRFLuca = new TH1D("histTRFLuca","",500,0.,50.);
    histTRFLuca -> Divide(histLowPtDM,histAllPtDM,1,1);

    TH1D *histTRFBisw = new TH1D("histTRFBisw","",500,0.,50.);
    histTRFBisw -> Divide(h0Lpt,h0Apt,1,1);

    TH2D *histGridTRFComp = new TH2D("histGridTRFComp","",100,0.,10.,100,0.,1.2);

    TCanvas *canvasTRF = new TCanvas("canvasTRF","canvasTRF",600,600);
    //histGridTRFComp -> Draw(); histTRFLuca -> Draw("EPsame"); histTRFBisw -> Draw("EPsame");
    histTRFLuca -> Draw("EP"); histTRFBisw -> Draw("EPsame");
}