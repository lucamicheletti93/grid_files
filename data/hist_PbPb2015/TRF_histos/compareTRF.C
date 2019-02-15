void compareTRF(){
    string filePath = "/home/luca/cernbox/JPSI/Jpsi_polarization_data_sync/hist_trigger_response_function_fixed/";
    TFile *fileTRF = new TFile(Form("%shist_TRF_sum.root",filePath.c_str()),"READ");
    TList *listTRF = (TList*) fileTRF -> Get("chist0");
    TH1D *histAllPtSM = (TH1D*) listTRF -> FindObject("histAllPtSM"); histAllPtSM -> Sumw2();
    TH1D *histLowPtSM = (TH1D*) listTRF -> FindObject("histLowPtSM"); histLowPtSM -> Sumw2();
    TH1D *histAllPtDM = (TH1D*) listTRF -> FindObject("histAllPtDM"); histAllPtDM -> Sumw2();
    TH1D *histLowPtDM = (TH1D*) listTRF -> FindObject("histLowPtDM"); histLowPtDM -> Sumw2();

    TH1D *histTRFSM = new TH1D("histTRFSM","histTRFSM",500,0.,50.);
    histTRFSM -> Divide(histLowPtSM,histAllPtSM); histTRFSM -> SetLineColor(kRed);
 
    TH1D *histTRFDM = new TH1D("histTRFDM","histTRFDM",500,0.,50.);
    histTRFDM -> Divide(histLowPtDM,histAllPtDM); histTRFDM -> SetLineColor(kBlue);

    TCanvas *canvasComp = new TCanvas("canvasComp","canvasComp",600,600);
    histTRFSM -> Draw("E");
    histTRFDM -> Draw("Esame");
}