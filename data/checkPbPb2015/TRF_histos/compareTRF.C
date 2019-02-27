void compareTRF(){
    gStyle -> SetOptStat(0);

    TFile *fileTRF_AOD175 = new TFile("/home/luca/cernbox/JPSI/Jpsi_polarization_data_sync/hist_checkPbPb2015/AOD175/hist_TRF_sum.root","READ");
    TList *listTRF_AOD175 = (TList*) fileTRF_AOD175 -> Get("chist0");
    TH1D *histAllPtSM_AOD175 = (TH1D*) listTRF_AOD175 -> FindObject("histAllPtSM"); histAllPtSM_AOD175 -> SetDirectory(0);
    histAllPtSM_AOD175 -> Sumw2(); histAllPtSM_AOD175 -> SetLineColor(kRed+2);
    TH1D *histLowPtSM_AOD175 = (TH1D*) listTRF_AOD175 -> FindObject("histLowPtSM"); histLowPtSM_AOD175 -> SetDirectory(0);
    histLowPtSM_AOD175 -> Sumw2(); histLowPtSM_AOD175 -> SetLineColor(kRed+2);
    TH1D *histAllPtDM_AOD175 = (TH1D*) listTRF_AOD175 -> FindObject("histAllPtDM_25eta4"); histAllPtDM_AOD175 -> SetDirectory(0);
    histAllPtDM_AOD175 -> Sumw2(); histAllPtDM_AOD175 -> SetLineColor(kBlue+2);
    TH1D *histLowPtDM_AOD175 = (TH1D*) listTRF_AOD175 -> FindObject("histLowPtDM_25eta4"); histLowPtDM_AOD175 -> SetDirectory(0);
    histLowPtDM_AOD175 -> Sumw2(); histLowPtDM_AOD175 -> SetLineColor(kBlue+2);

    TFile *fileTRF_no_PS_no_CMUL7 = new TFile("/home/luca/cernbox/JPSI/Jpsi_polarization_data_sync/hist_checkPbPb2015/no_PS_no_CMUL7/hist_TRF_sum.root","READ");
    TList *listTRF_no_PS_no_CMUL7 = (TList*) fileTRF_no_PS_no_CMUL7 -> Get("chist0");
    TH1D *histAllPtSM_no_PS_no_CMUL7 = (TH1D*) listTRF_no_PS_no_CMUL7 -> FindObject("histAllPtSM"); histAllPtSM_no_PS_no_CMUL7 -> SetDirectory(0);
    histAllPtSM_no_PS_no_CMUL7 -> Sumw2(); histAllPtSM_no_PS_no_CMUL7 -> SetLineColor(kRed);
    TH1D *histLowPtSM_no_PS_no_CMUL7 = (TH1D*) listTRF_no_PS_no_CMUL7 -> FindObject("histLowPtSM"); histLowPtSM_no_PS_no_CMUL7 -> SetDirectory(0);
    histLowPtSM_no_PS_no_CMUL7 -> Sumw2(); histLowPtSM_no_PS_no_CMUL7 -> SetLineColor(kRed);
    TH1D *histAllPtDM_no_PS_no_CMUL7 = (TH1D*) listTRF_no_PS_no_CMUL7 -> FindObject("histAllPtDM_25eta4"); histAllPtDM_no_PS_no_CMUL7 -> SetDirectory(0);
    histAllPtDM_no_PS_no_CMUL7 -> Sumw2(); histAllPtDM_no_PS_no_CMUL7 -> SetLineColor(kBlue);
    TH1D *histLowPtDM_no_PS_no_CMUL7 = (TH1D*) listTRF_no_PS_no_CMUL7 -> FindObject("histLowPtDM_25eta4"); histLowPtDM_no_PS_no_CMUL7 -> SetDirectory(0);
    histLowPtDM_no_PS_no_CMUL7 -> Sumw2(); histLowPtDM_no_PS_no_CMUL7 -> SetLineColor(kBlue);

    TFile *fileTRF_PS_CMUL7 = new TFile("/home/luca/cernbox/JPSI/Jpsi_polarization_data_sync/hist_checkPbPb2015/PS_CMUL7/hist_TRF_sum.root","READ");
    TList *listTRF_PS_CMUL7 = (TList*) fileTRF_PS_CMUL7 -> Get("chist0");
    TH1D *histAllPtSM_PS_CMUL7 = (TH1D*) listTRF_PS_CMUL7 -> FindObject("histAllPtSM"); histAllPtSM_PS_CMUL7 -> SetDirectory(0);
    histAllPtSM_PS_CMUL7 -> Sumw2(); histAllPtSM_PS_CMUL7 -> SetLineColor(kOrange); histAllPtSM_PS_CMUL7 -> SetMarkerStyle(20); histAllPtSM_PS_CMUL7 -> SetMarkerColor(kOrange);
    TH1D *histLowPtSM_PS_CMUL7 = (TH1D*) listTRF_PS_CMUL7 -> FindObject("histLowPtSM"); histLowPtSM_PS_CMUL7 -> SetDirectory(0);
    histLowPtSM_PS_CMUL7 -> Sumw2(); histLowPtSM_PS_CMUL7 -> SetLineColor(kOrange); histLowPtSM_PS_CMUL7 -> SetMarkerStyle(20); histLowPtSM_PS_CMUL7 -> SetMarkerColor(kOrange);
    TH1D *histAllPtDM_PS_CMUL7 = (TH1D*) listTRF_PS_CMUL7 -> FindObject("histAllPtDM_25eta4"); histAllPtDM_PS_CMUL7 -> SetDirectory(0);
    histAllPtDM_PS_CMUL7 -> Sumw2(); histAllPtDM_PS_CMUL7 -> SetLineColor(kAzure); histAllPtDM_PS_CMUL7 -> SetMarkerStyle(20); histAllPtDM_PS_CMUL7 -> SetMarkerColor(kAzure);
    TH1D *histLowPtDM_PS_CMUL7 = (TH1D*) listTRF_PS_CMUL7 -> FindObject("histLowPtDM_25eta4"); histLowPtDM_PS_CMUL7 -> SetDirectory(0);
    histLowPtDM_PS_CMUL7 -> Sumw2(); histLowPtDM_PS_CMUL7 -> SetLineColor(kAzure); histLowPtDM_PS_CMUL7 -> SetMarkerStyle(20); histLowPtDM_PS_CMUL7 -> SetMarkerColor(kAzure);

    TFile *fileBiswarup = new TFile("/home/luca/Scrivania/nuovo/Muon_Lpt_by_Apt.root","READ");
    TH1D *histBiswarupTRFData =  (TH1D*) fileBiswarup -> Get("hData25y4"); histBiswarupTRFData -> SetDirectory(0); histBiswarupTRFData -> SetMarkerStyle(25); histBiswarupTRFData -> SetLineColor(kBlack);
    TH1D *histBiswarupTRFMC =  (TH1D*) fileBiswarup -> Get("hMC25y4"); histBiswarupTRFMC -> SetDirectory(0); histBiswarupTRFData -> SetLineColor(kMagenta);
    fileBiswarup -> Close();

    TH1D *histTRFSM_AOD175 = new TH1D("histTRFSM_AOD175","histTRFSM_AOD175",500,0.,50.);
    histTRFSM_AOD175 -> Divide(histLowPtSM_AOD175,histAllPtSM_AOD175,1,1); histTRFSM_AOD175 -> SetLineColor(kRed); histTRFSM_AOD175 -> SetMarkerStyle(28);
 
    TH1D *histTRFDM_AOD175 = new TH1D("histTRFDM_AOD175","histTRFDM_AOD175",500,0.,50.);
    histTRFDM_AOD175 -> Divide(histLowPtDM_AOD175,histAllPtDM_AOD175,1,1); histTRFDM_AOD175 -> SetLineColor(kGreen+2); histTRFDM_AOD175 -> SetMarkerStyle(28);

    TH1D *histTRFSM_no_PS_no_CMUL7 = new TH1D("histTRFSM_no_PS_no_CMUL7","histTRFSM_no_PS_no_CMUL7",500,0.,50.);
    histTRFSM_no_PS_no_CMUL7 -> Divide(histLowPtSM_no_PS_no_CMUL7,histAllPtSM_no_PS_no_CMUL7,1,1); histTRFSM_no_PS_no_CMUL7 -> SetLineColor(kRed);
 
    TH1D *histTRFDM_no_PS_no_CMUL7 = new TH1D("histTRFDM_no_PS_no_CMUL7","histTRFDM_no_PS_no_CMUL7",500,0.,50.);
    histTRFDM_no_PS_no_CMUL7 -> Divide(histLowPtDM_no_PS_no_CMUL7,histAllPtDM_no_PS_no_CMUL7,1,1); histTRFDM_no_PS_no_CMUL7 -> SetLineColor(kGreen+2);

    TH1D *histTRFSM_PS_CMUL7 = new TH1D("histTRFSM_PS_CMUL7","histTRFSM_PS_CMUL7",500,0.,50.);
    histTRFSM_PS_CMUL7 -> Divide(histLowPtSM_PS_CMUL7,histAllPtSM_PS_CMUL7,1,1); histTRFSM_PS_CMUL7 -> SetLineColor(kOrange); histTRFSM_PS_CMUL7 -> SetMarkerSize(0.5); histTRFSM_PS_CMUL7 -> SetMarkerStyle(20); histTRFSM_PS_CMUL7 -> SetMarkerColor(kOrange);
 
    TH1D *histTRFDM_PS_CMUL7 = new TH1D("histTRFDM_PS_CMUL7","histTRFDM_PS_CMUL7",500,0.,50.);
    histTRFDM_PS_CMUL7 -> Divide(histLowPtDM_PS_CMUL7,histAllPtDM_PS_CMUL7,1,1); histTRFDM_PS_CMUL7 -> SetLineColor(kAzure); histTRFDM_PS_CMUL7 -> SetMarkerSize(0.5); histTRFDM_PS_CMUL7 -> SetMarkerStyle(20); histTRFDM_PS_CMUL7 -> SetMarkerColor(kAzure);

    TH2D *histGridTRF = new TH2D("histGridTRF","",100,0.,10.,100,0.,1.2);

    TLegend *legendCompTRF = new TLegend(0.6,0.7,0.89,0.89);
    legendCompTRF -> AddEntry(histTRFSM_no_PS_no_CMUL7,"SM - no PS, no CMUL7","LP");
    legendCompTRF -> AddEntry(histTRFDM_no_PS_no_CMUL7,"DM - no PS, no CMUL7","LP");
    //legendCompTRF -> AddEntry(histTRFSM_PS_CMUL7,"SM - PS, CMUL7","LP");
    legendCompTRF -> AddEntry(histTRFDM_PS_CMUL7,"DM - PS, CMUL7","LP");
    legendCompTRF -> AddEntry(histBiswarupTRFData,"Data Biswarup","LP");
    legendCompTRF -> AddEntry(histBiswarupTRFMC,"MC Biswarup","LP");
    legendCompTRF -> AddEntry(histTRFSM_AOD175,"SM - AOD175","LP");
    legendCompTRF -> AddEntry(histTRFDM_AOD175,"DM - AOD175","LP");
    

    TCanvas *canvasCompTRF = new TCanvas("canvasCompTRF","canvasCompTRF",600,600);
    histGridTRF -> Draw();
    histTRFSM_no_PS_no_CMUL7 -> Draw("Esame");
    histTRFDM_no_PS_no_CMUL7 -> Draw("Esame");
    histTRFSM_AOD175 -> Draw("Esame");
    histTRFDM_AOD175 -> Draw("Esame");
    histTRFDM_PS_CMUL7 -> Draw("Esame");
    histBiswarupTRFData -> Draw("EPsame");
    histBiswarupTRFMC -> Draw("Esame");
    legendCompTRF -> Draw("same");

    return;

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