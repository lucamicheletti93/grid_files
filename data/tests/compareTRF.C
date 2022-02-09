void compareTRF(){
    gStyle -> SetOptStat(0);

    TFile *file_KINT7inMUON_ONLY = new TFile("/home/luca/cernbox/JPSI/Jpsi_polarization_data_sync/fixed_hist_trigger_response_function/hist_TRF_sum.root","READ");
    TList *list_KINT7inMUON_ONLY = (TList*) file_KINT7inMUON_ONLY -> Get("chist0");
    TH1D *histAllPtSM_KINT7inMUON_ONLY = (TH1D*) list_KINT7inMUON_ONLY -> FindObject("histAllPtSM"); histAllPtSM_KINT7inMUON_ONLY -> SetDirectory(0);
    histAllPtSM_KINT7inMUON_ONLY -> Sumw2(); histAllPtSM_KINT7inMUON_ONLY -> SetLineColor(kOrange+8);
    TH1D *histLowPtSM_KINT7inMUON_ONLY = (TH1D*) list_KINT7inMUON_ONLY -> FindObject("histLowPtSM"); histLowPtSM_KINT7inMUON_ONLY -> SetDirectory(0);
    histLowPtSM_KINT7inMUON_ONLY -> Sumw2(); histLowPtSM_KINT7inMUON_ONLY -> SetLineColor(kOrange+8);
    TH1D *histAllPtDM_KINT7inMUON_ONLY = (TH1D*) list_KINT7inMUON_ONLY -> FindObject("histAllPtDM_25y4"); histAllPtDM_KINT7inMUON_ONLY -> SetDirectory(0);
    histAllPtDM_KINT7inMUON_ONLY -> Sumw2(); histAllPtDM_KINT7inMUON_ONLY -> SetLineColor(kAzure+8);
    TH1D *histLowPtDM_KINT7inMUON_ONLY = (TH1D*) list_KINT7inMUON_ONLY -> FindObject("histLowPtDM_25y4"); histLowPtDM_KINT7inMUON_ONLY -> SetDirectory(0);
    histLowPtDM_KINT7inMUON_ONLY -> Sumw2(); histLowPtDM_KINT7inMUON_ONLY -> SetLineColor(kAzure+8);

    TH1D *histAllPtDM_25y3 = (TH1D*) list_KINT7inMUON_ONLY -> FindObject("histAllPtDM_25y3"); histAllPtDM_25y3 -> SetDirectory(0);
    histAllPtDM_25y3 -> Sumw2(); histAllPtDM_KINT7inMUON_ONLY -> SetLineColor(kAzure+8);
    TH1D *histLowPtDM_25y3 = (TH1D*) list_KINT7inMUON_ONLY -> FindObject("histLowPtDM_25y3"); histLowPtDM_25y3 -> SetDirectory(0);
    histLowPtDM_25y3 -> Sumw2(); histLowPtDM_25y3 -> SetLineColor(kAzure+8);

    TH1D *histAllPtDM_3y35 = (TH1D*) list_KINT7inMUON_ONLY -> FindObject("histAllPtDM_3y35"); histAllPtDM_3y35 -> SetDirectory(0);
    histAllPtDM_3y35 -> Sumw2(); histAllPtDM_KINT7inMUON_ONLY -> SetLineColor(kAzure+8);
    TH1D *histLowPtDM_3y35 = (TH1D*) list_KINT7inMUON_ONLY -> FindObject("histLowPtDM_3y35"); histLowPtDM_3y35 -> SetDirectory(0);
    histLowPtDM_3y35 -> Sumw2(); histLowPtDM_3y35 -> SetLineColor(kAzure+8);

    TH1D *histAllPtDM_35y4 = (TH1D*) list_KINT7inMUON_ONLY -> FindObject("histAllPtDM_35y4"); histAllPtDM_35y4 -> SetDirectory(0);
    histAllPtDM_35y4 -> Sumw2(); histAllPtDM_KINT7inMUON_ONLY -> SetLineColor(kAzure+8);
    TH1D *histLowPtDM_35y4 = (TH1D*) list_KINT7inMUON_ONLY -> FindObject("histLowPtDM_35y4"); histLowPtDM_35y4 -> SetDirectory(0);
    histLowPtDM_35y4 -> Sumw2(); histLowPtDM_35y4 -> SetLineColor(kAzure+8);

    TH1D *histTRFSM_KINT7inMUON_ONLY = new TH1D("histTRFSM_KINT7inMUON_ONLY","histTRFSM_KINT7inMUON_ONLY",500,0.,50.);
    histTRFSM_KINT7inMUON_ONLY -> Divide(histLowPtSM_KINT7inMUON_ONLY,histAllPtSM_KINT7inMUON_ONLY,1,1,"B"); histTRFSM_KINT7inMUON_ONLY -> SetLineColor(kOrange+8); histTRFSM_KINT7inMUON_ONLY -> SetMarkerStyle(20); histTRFSM_KINT7inMUON_ONLY -> SetMarkerColor(kOrange+8);
    histTRFSM_KINT7inMUON_ONLY -> SetMarkerSize(0.8);

    TH1D *histTRFDM_KINT7inMUON_ONLY = new TH1D("histTRFDM_KINT7inMUON_ONLY","histTRFDM_KINT7inMUON_ONLY",500,0.,50.);
    histTRFDM_KINT7inMUON_ONLY -> Divide(histLowPtDM_KINT7inMUON_ONLY,histAllPtDM_KINT7inMUON_ONLY,1,1,"B"); histTRFDM_KINT7inMUON_ONLY -> SetLineColor(kAzure+8); histTRFDM_KINT7inMUON_ONLY -> SetMarkerStyle(20); histTRFDM_KINT7inMUON_ONLY -> SetMarkerColor(kAzure+8);
    histTRFDM_KINT7inMUON_ONLY -> SetMarkerSize(0.8);

    TH1D *histTRFDM_25y3 = new TH1D("histTRFDM_25y3","histTRFDM_25y3",500,0.,50.);
    histTRFDM_25y3 -> Divide(histLowPtDM_25y3,histAllPtDM_25y3,1,1,"B"); histTRFDM_25y3 -> SetLineColor(kAzure+8); histTRFDM_25y3 -> SetMarkerStyle(20); histTRFDM_25y3 -> SetMarkerColor(kAzure+8);
    histTRFDM_25y3 -> SetMarkerSize(0.8);

    TH1D *histTRFDM_3y35 = new TH1D("histTRFDM_3y35","histTRFDM_3y35",500,0.,50.);
    histTRFDM_3y35 -> Divide(histLowPtDM_3y35,histAllPtDM_3y35,1,1,"B"); histTRFDM_3y35 -> SetLineColor(kAzure+8); histTRFDM_3y35 -> SetMarkerStyle(20); histTRFDM_3y35 -> SetMarkerColor(kAzure+8);
    histTRFDM_3y35 -> SetMarkerSize(0.8);

    TH1D *histTRFDM_35y4 = new TH1D("histTRFDM_35y4","histTRFDM_35y4",500,0.,50.);
    histTRFDM_35y4 -> Divide(histLowPtDM_35y4,histAllPtDM_35y4,1,1,"B"); histTRFDM_35y4 -> SetLineColor(kAzure+8); histTRFDM_35y4 -> SetMarkerStyle(20); histTRFDM_35y4 -> SetMarkerColor(kAzure+8);
    histTRFDM_35y4 -> SetMarkerSize(0.8);

    TFile *file_KMUSPB = new TFile("/home/luca/GITHUB/grid_files/data/tests/KMUSPB/trees/hist_TRF_sum.root","READ");
    TList *list_KMUSPB = (TList*) file_KMUSPB -> Get("chist0");
    TH1D *histAllPtSM_KMUSPB = (TH1D*) list_KMUSPB -> FindObject("histAllPtSM"); histAllPtSM_KMUSPB -> SetDirectory(0);
    histAllPtSM_KMUSPB -> Sumw2(); histAllPtSM_KMUSPB -> SetLineColor(kMagenta);
    TH1D *histLowPtSM_KMUSPB = (TH1D*) list_KMUSPB -> FindObject("histLowPtSM"); histLowPtSM_KMUSPB -> SetDirectory(0);
    histLowPtSM_KMUSPB -> Sumw2(); histLowPtSM_KMUSPB -> SetLineColor(kMagenta);
    TH1D *histAllPtDM_KMUSPB = (TH1D*) list_KMUSPB -> FindObject("histAllPtDM_25eta4"); histAllPtDM_KMUSPB -> SetDirectory(0);
    histAllPtDM_KMUSPB -> Sumw2(); histAllPtDM_KMUSPB -> SetLineColor(kGreen);
    TH1D *histLowPtDM_KMUSPB = (TH1D*) list_KMUSPB -> FindObject("histLowPtDM_25eta4"); histLowPtDM_KMUSPB -> SetDirectory(0);
    histLowPtDM_KMUSPB -> Sumw2(); histLowPtDM_KMUSPB -> SetLineColor(kGreen);

    TH1D *histTRFSM_KMUSPB = new TH1D("histTRFSM_KMUSPB","histTRFSM_KMUSPB",500,0.,50.);
    histTRFSM_KMUSPB -> Divide(histLowPtSM_KMUSPB,histAllPtSM_KMUSPB,1,1,"B"); histTRFSM_KMUSPB -> SetLineColor(kMagenta); histTRFSM_KMUSPB -> SetMarkerStyle(20); histTRFSM_KMUSPB -> SetMarkerColor(kMagenta);

    TH1D *histTRFDM_KMUSPB = new TH1D("histTRFDM_KMUSPB","histTRFDM_KMUSPB",500,0.,50.);
    histTRFDM_KMUSPB -> Divide(histLowPtDM_KMUSPB,histAllPtDM_KMUSPB,1,1,"B"); histTRFDM_KMUSPB -> SetLineColor(kGreen); histTRFDM_KMUSPB -> SetMarkerStyle(20); histTRFDM_KMUSPB -> SetMarkerColor(kGreen);

    TFile *fileBiswarup = new TFile("/home/luca/Scrivania/nuovo/Muon_Lpt_by_Apt.root","READ");
    TH1D *histBiswarupTRFData =  (TH1D*) fileBiswarup -> Get("hData25y4"); 
    histBiswarupTRFData -> SetDirectory(0); histBiswarupTRFData -> SetMarkerStyle(24); histBiswarupTRFData -> SetLineColor(kBlack); histBiswarupTRFData -> SetMarkerSize(0.5);
    TH1D *histBiswarupTRFMC =  (TH1D*) fileBiswarup -> Get("hMC25y4"); 
    histBiswarupTRFMC -> SetDirectory(0); histBiswarupTRFMC -> SetMarkerStyle(24);  histBiswarupTRFMC -> SetLineColor(kBlack); histBiswarupTRFMC -> SetMarkerSize(0.5);
    fileBiswarup -> Close();

    TLegend *legendTests = new TLegend(0.6,0.7,0.89,0.89);
    legendTests -> AddEntry(histTRFSM_KINT7inMUON_ONLY,"Single Muons - KINT7inMUON only","LP");
    legendTests -> AddEntry(histTRFDM_KINT7inMUON_ONLY,"DiMuons - KINT7inMUON only","LP");
    //legendTests -> AddEntry(histTRFSM_KMUSPB,"Single Muons - KINT7inMUON + KMUSPB","LP");
    //legendTests -> AddEntry(histTRFDM_KMUSPB,"DiMuons - KINT7inMUON + KMUSPB","LP");
    legendTests -> AddEntry(histBiswarupTRFData,"Biswarup data","LP");

    TH2D *histGridAllPt = new TH2D("histGridAllPt","",100,0.,10.,100,0.,30000);

    TCanvas *cavasAllPt = new TCanvas("cavasAllPt","cavasAllPt",1200,1200);
    histGridAllPt -> Draw();
    histAllPtSM_KINT7inMUON_ONLY -> Draw("EPsame");
    histAllPtDM_KINT7inMUON_ONLY -> Draw("EPsame");
    histAllPtSM_KMUSPB -> Draw("EPsame");
    histAllPtDM_KMUSPB -> Draw("EPsame");
    legendTests -> Draw("same");

    TH2D *histGridLowPt = new TH2D("histGridLowPt","",100,0.,10.,100,0.,6000);

    TCanvas *cavasLowPt = new TCanvas("cavasLowPt","cavasLowPt",1200,1200);
    histGridLowPt -> Draw();
    histLowPtSM_KINT7inMUON_ONLY -> Draw("EPsame");
    histLowPtDM_KINT7inMUON_ONLY -> Draw("EPsame");
    //histLowPtSM_KMUSPB -> Draw("EPsame");
    //histLowPtDM_KMUSPB -> Draw("EPsame");
    legendTests -> Draw("same");

    TH2D *histGridTests = new TH2D("histGridTests","",100,0.,10.,100,0.,1.2);
    histGridTests -> GetXaxis() -> SetTitle("#it{p}_{T} (GeV/#it{c})");

    TCanvas *cavasTests = new TCanvas("cavasTests","cavasTests",1200,1200);
    histGridTests -> Draw();
    histTRFSM_KINT7inMUON_ONLY -> Draw("EPsame");
    histTRFDM_KINT7inMUON_ONLY -> Draw("EPsame");
    //histTRFSM_KMUSPB -> Draw("EPsame");
    //histTRFDM_KMUSPB -> Draw("EPsame");
    histBiswarupTRFData -> Draw("EPsame");
    legendTests -> Draw("same");


    TLatex *latexTitle = new TLatex();;

    TCanvas *canvasDifferentialTRF = new TCanvas("canvasDifferentialTRF","canvasDifferentialTRF",1200,1200);
    canvasDifferentialTRF -> Divide(2,2);

    canvasDifferentialTRF -> cd(1); histGridTests -> Draw(); histTRFDM_KINT7inMUON_ONLY -> Draw("EPsame"); latexTitle -> DrawLatex(3.5,1.25,"2.5 < y < 4.0");
    canvasDifferentialTRF -> cd(2); histGridTests -> Draw(); histTRFDM_25y3 -> Draw("EPsame"); latexTitle -> DrawLatex(3.5,1.25,"2.5 < y < 3.0");
    canvasDifferentialTRF -> cd(3); histGridTests -> Draw(); histTRFDM_3y35 -> Draw("EPsame"); latexTitle -> DrawLatex(3.5,1.25,"3.0 < y < 3.5");
    canvasDifferentialTRF -> cd(4); histGridTests -> Draw(); histTRFDM_35y4 -> Draw("EPsame"); latexTitle -> DrawLatex(3.5,1.25,"3.5 < y < 4.0");
}
