void compareTRF(){
    gStyle -> SetOptStat(0);

    string filePath = "/home/luca/cernbox/JPSI/Jpsi_polarization_data_sync/hist_checkPbPb2015/no_PS_no_CMUL7/";
    TFile *fileTRF = new TFile(Form("%shist_TRF_sum.root",filePath.c_str()),"READ");
    TList *listTRF = (TList*) fileTRF -> Get("chist0");
    TH1D *histAllPtSM_no_PS_no_CMUL7 = (TH1D*) listTRF -> FindObject("histAllPtSM");  histAllPtSM_no_PS_no_CMUL7 -> Sumw2(); histAllPtSM_no_PS_no_CMUL7 -> SetLineColor(kRed);
    TH1D *histLowPtSM_no_PS_no_CMUL7 = (TH1D*) listTRF -> FindObject("histLowPtSM"); histLowPtSM_no_PS_no_CMUL7 -> Sumw2(); histLowPtSM_no_PS_no_CMUL7 -> SetLineColor(kRed);
    TH1D *histAllPtDM_no_PS_no_CMUL7 = (TH1D*) listTRF -> FindObject("histAllPtDM_25eta4"); histAllPtDM_no_PS_no_CMUL7 -> Sumw2(); histAllPtDM_no_PS_no_CMUL7 -> SetLineColor(kBlue);
    TH1D *histLowPtDM_no_PS_no_CMUL7 = (TH1D*) listTRF -> FindObject("histLowPtDM_25eta4"); histLowPtDM_no_PS_no_CMUL7 -> Sumw2(); histLowPtDM_no_PS_no_CMUL7 -> SetLineColor(kBlue);


    string filePath = "/home/luca/cernbox/JPSI/Jpsi_polarization_data_sync/hist_checkPbPb2015/PS_CMUL7/";
    TFile *fileTRF = new TFile(Form("%shist_TRF_sum.root",filePath.c_str()),"READ");
    TList *listTRF = (TList*) fileTRF -> Get("chist0");
    TH1D *histAllPtSM_PS_CMUL7 = (TH1D*) listTRF -> FindObject("histAllPtSM");  histAllPtSM_PS_CMUL7 -> Sumw2(); histAllPtSM_PS_CMUL7 -> SetLineColor(kOrange); histAllPtSM_PS_CMUL7 -> SetMarkerStyle(20); histAllPtSM_PS_CMUL7 -> SetMarkerColor(kOrange);
    TH1D *histLowPtSM_PS_CMUL7 = (TH1D*) listTRF -> FindObject("histLowPtSM"); histLowPtSM_PS_CMUL7 -> Sumw2(); histLowPtSM_PS_CMUL7 -> SetLineColor(kOrange); histLowPtSM_PS_CMUL7 -> SetMarkerStyle(20); histLowPtSM_PS_CMUL7 -> SetMarkerColor(kOrange);
    TH1D *histAllPtDM_PS_CMUL7 = (TH1D*) listTRF -> FindObject("histAllPtDM_25eta4"); histAllPtDM_PS_CMUL7 -> Sumw2(); histAllPtDM_PS_CMUL7 -> SetLineColor(kAzure); histAllPtDM_PS_CMUL7 -> SetMarkerStyle(20); histAllPtDM_PS_CMUL7 -> SetMarkerColor(kAzure);
    TH1D *histLowPtDM_PS_CMUL7 = (TH1D*) listTRF -> FindObject("histLowPtDM_25eta4"); histLowPtDM_PS_CMUL7 -> Sumw2(); histLowPtDM_PS_CMUL7 -> SetLineColor(kAzure); histLowPtDM_PS_CMUL7 -> SetMarkerStyle(20); histLowPtDM_PS_CMUL7 -> SetMarkerColor(kAzure);

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

    TH1D *histTRFSM_no_PS_no_CMUL7 = new TH1D("histTRFSM_no_PS_no_CMUL7","histTRFSM_no_PS_no_CMUL7",500,0.,50.);
    histTRFSM_no_PS_no_CMUL7 -> Divide(histLowPtSM_no_PS_no_CMUL7,histAllPtSM_no_PS_no_CMUL7,1,1);// histTRFSM_no_PS_no_CMUL7 -> SetLineColor(kRed);
 
    TH1D *histTRFDM_no_PS_no_CMUL7 = new TH1D("histTRFDM_no_PS_no_CMUL7","histTRFDM_no_PS_no_CMUL7",500,0.,50.);
    histTRFDM_no_PS_no_CMUL7 -> Divide(histLowPtDM_no_PS_no_CMUL7,histAllPtDM_no_PS_no_CMUL7,1,1);// histTRFDM_no_PS_no_CMUL7 -> SetLineColor(kBlue);


    TH1D *histTRFSM_PS_CMUL7 = new TH1D("histTRFSM_PS_CMUL7","histTRFSM_PS_CMUL7",500,0.,50.);
    histTRFSM_PS_CMUL7 -> Divide(histLowPtSM_PS_CMUL7,histAllPtSM_PS_CMUL7,1,1); histTRFSM_PS_CMUL7 -> SetLineColor(kOrange); histTRFSM_PS_CMUL7 -> SetMarkerStyle(20); histTRFSM_PS_CMUL7 -> SetMarkerColor(kOrange);
 
    TH1D *histTRFDM_PS_CMUL7 = new TH1D("histTRFDM_PS_CMUL7","histTRFDM_PS_CMUL7",500,0.,50.);
    histTRFDM_PS_CMUL7 -> Divide(histLowPtDM_PS_CMUL7,histAllPtDM_PS_CMUL7,1,1); histTRFDM_PS_CMUL7 -> SetLineColor(kAzure); histTRFDM_PS_CMUL7 -> SetMarkerStyle(20); histTRFDM_PS_CMUL7 -> SetMarkerColor(kAzure);

    TH2D *histGridTRF = new TH2D("histGridTRF","",100,0.,10.,100,0.,1.2);

    TCanvas *canvasComp = new TCanvas("canvasComp","canvasComp",600,600);
    histGridTRF -> Draw();
    histTRFSM_no_PS_no_CMUL7 -> Draw("Esame");
    histTRFDM_no_PS_no_CMUL7 -> Draw("Esame");
    histTRFSM_PS_CMUL7 -> Draw("Esame");
    histTRFDM_PS_CMUL7 -> Draw("Esame");
    histBiswarupTRFData -> Draw("Esame");

    TCanvas *canvasCompAllLow = new TCanvas("canvasCompAllLow","canvasCompAllLow",1200,600);
    canvasCompAllLow -> Divide(2,1);

    canvasCompAllLow -> cd(1);
    histAllPtSM_no_PS_no_CMUL7 -> Draw("E");
    histAllPtSM_PS_CMUL7 -> Draw("Esame");
    histAllPtDM_no_PS_no_CMUL7 -> Draw("Esame");
    histAllPtDM_PS_CMUL7 -> Draw("Esame");

    canvasCompAllLow -> cd(2);
    histLowPtSM_no_PS_no_CMUL7 -> Draw("E");
    histLowPtSM_PS_CMUL7 -> Draw("Esame");
    histLowPtDM_no_PS_no_CMUL7 -> Draw("Esame");
    histLowPtDM_PS_CMUL7 -> Draw("Esame");



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