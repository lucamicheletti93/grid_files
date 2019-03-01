void compareTRF(){
    gStyle -> SetOptStat(0);

    TFile *file_MASS = new TFile("/home/luca/cernbox/JPSI/Jpsi_polarization_data_sync/tests/MASS/hist_TRF_sum.root","READ");
    TList *list_MASS = (TList*) file_MASS -> Get("chist0");
    TH1D *histAllPtSM_MASS = (TH1D*) list_MASS -> FindObject("histAllPtSM"); histAllPtSM_MASS -> SetDirectory(0);
    histAllPtSM_MASS -> Sumw2(); histAllPtSM_MASS -> SetLineColor(kRed);
    TH1D *histLowPtSM_MASS = (TH1D*) list_MASS -> FindObject("histLowPtSM"); histLowPtSM_MASS -> SetDirectory(0);
    histLowPtSM_MASS -> Sumw2(); histLowPtSM_MASS -> SetLineColor(kRed);
    TH1D *histAllPtDM_MASS = (TH1D*) list_MASS -> FindObject("histAllPtDM_25eta4"); histAllPtDM_MASS -> SetDirectory(0);
    histAllPtDM_MASS -> Sumw2(); histAllPtDM_MASS -> SetLineColor(kBlue);
    TH1D *histLowPtDM_MASS = (TH1D*) list_MASS -> FindObject("histLowPtDM_25eta4"); histLowPtDM_MASS -> SetDirectory(0);
    histLowPtDM_MASS -> Sumw2(); histLowPtDM_MASS -> SetLineColor(kBlue);

    TH1D *histTRFSM_MASS = new TH1D("histTRFSM_MASS","histTRFSM_MASS",500,0.,50.);
    histTRFSM_MASS -> Divide(histLowPtSM_MASS,histAllPtSM_MASS,1,1,"B"); histTRFSM_MASS -> SetLineColor(kRed); histTRFSM_MASS -> SetMarkerStyle(20); histTRFSM_MASS -> SetMarkerColor(kRed);

    TH1D *histTRFDM_MASS = new TH1D("histTRFDM_MASS","histTRFDM_MASS",500,0.,50.);
    histTRFDM_MASS -> Divide(histLowPtDM_MASS,histAllPtDM_MASS,1,1,"B"); histTRFDM_MASS -> SetLineColor(kBlue); histTRFDM_MASS -> SetMarkerStyle(20); histTRFDM_MASS -> SetMarkerColor(kBlue);

    TFile *file_CV0L7 = new TFile("/home/luca/cernbox/JPSI/Jpsi_polarization_data_sync/tests/CV0L7/hist_TRF_sum.root","READ");
    TList *list_CV0L7 = (TList*) file_CV0L7 -> Get("chist0");
    TH1D *histAllPtSM_CV0L7 = (TH1D*) list_CV0L7 -> FindObject("histAllPtSM"); histAllPtSM_CV0L7 -> SetDirectory(0);
    histAllPtSM_CV0L7 -> Sumw2(); histAllPtSM_CV0L7 -> SetLineColor(kMagenta);
    TH1D *histLowPtSM_CV0L7 = (TH1D*) list_CV0L7 -> FindObject("histLowPtSM"); histLowPtSM_CV0L7 -> SetDirectory(0);
    histLowPtSM_CV0L7 -> Sumw2(); histLowPtSM_CV0L7 -> SetLineColor(kMagenta);
    TH1D *histAllPtDM_CV0L7 = (TH1D*) list_CV0L7 -> FindObject("histAllPtDM_25eta4"); histAllPtDM_CV0L7 -> SetDirectory(0);
    histAllPtDM_CV0L7 -> Sumw2(); histAllPtDM_CV0L7 -> SetLineColor(kGreen);
    TH1D *histLowPtDM_CV0L7 = (TH1D*) list_CV0L7 -> FindObject("histLowPtDM_25eta4"); histLowPtDM_CV0L7 -> SetDirectory(0);
    histLowPtDM_CV0L7 -> Sumw2(); histLowPtDM_CV0L7 -> SetLineColor(kGreen);

    TH1D *histTRFSM_CV0L7 = new TH1D("histTRFSM_CV0L7","histTRFSM_CV0L7",500,0.,50.);
    histTRFSM_CV0L7 -> Divide(histLowPtSM_CV0L7,histAllPtSM_CV0L7,1,1,"B"); histTRFSM_CV0L7 -> SetLineColor(kMagenta); histTRFSM_CV0L7 -> SetMarkerStyle(20); histTRFSM_CV0L7 -> SetMarkerColor(kMagenta);

    TH1D *histTRFDM_CV0L7 = new TH1D("histTRFDM_CV0L7","histTRFDM_CV0L7",500,0.,50.);
    histTRFDM_CV0L7 -> Divide(histLowPtDM_CV0L7,histAllPtDM_CV0L7,1,1,"B"); histTRFDM_CV0L7 -> SetLineColor(kGreen); histTRFDM_CV0L7 -> SetMarkerStyle(20); histTRFDM_CV0L7 -> SetMarkerColor(kGreen);

    TFile *file_OLD_PS = new TFile("/home/luca/cernbox/JPSI/Jpsi_polarization_data_sync/tests/OLD_PS/hist_TRF_sum.root","READ");
    TList *list_OLD_PS = (TList*) file_OLD_PS -> Get("chist0");
    TH1D *histAllPtSM_OLD_PS = (TH1D*) list_OLD_PS -> FindObject("histAllPtSM"); histAllPtSM_OLD_PS -> SetDirectory(0);
    histAllPtSM_OLD_PS -> Sumw2(); histAllPtSM_OLD_PS -> SetLineColor(kOrange);
    TH1D *histLowPtSM_OLD_PS = (TH1D*) list_OLD_PS -> FindObject("histLowPtSM"); histLowPtSM_OLD_PS -> SetDirectory(0);
    histLowPtSM_OLD_PS -> Sumw2(); histLowPtSM_OLD_PS -> SetLineColor(kOrange);
    TH1D *histAllPtDM_OLD_PS = (TH1D*) list_OLD_PS -> FindObject("histAllPtDM_25eta4"); histAllPtDM_OLD_PS -> SetDirectory(0);
    histAllPtDM_OLD_PS -> Sumw2(); histAllPtDM_OLD_PS -> SetLineColor(kAzure+10);
    TH1D *histLowPtDM_OLD_PS = (TH1D*) list_OLD_PS -> FindObject("histLowPtDM_25eta4"); histLowPtDM_OLD_PS -> SetDirectory(0);
    histLowPtDM_OLD_PS -> Sumw2(); histLowPtDM_OLD_PS -> SetLineColor(kAzure+10);

    TH1D *histTRFSM_OLD_PS = new TH1D("histTRFSM_OLD_PS","histTRFSM_OLD_PS",500,0.,50.);
    histTRFSM_OLD_PS -> Divide(histLowPtSM_OLD_PS,histAllPtSM_OLD_PS,1,1,"B"); histTRFSM_OLD_PS -> SetLineColor(kOrange); histTRFSM_OLD_PS -> SetMarkerStyle(20); histTRFSM_OLD_PS -> SetMarkerColor(kOrange);

    TH1D *histTRFDM_OLD_PS = new TH1D("histTRFDM_OLD_PS","histTRFDM_OLD_PS",500,0.,50.);
    histTRFDM_OLD_PS -> Divide(histLowPtDM_OLD_PS,histAllPtDM_OLD_PS,1,1,"B"); histTRFDM_OLD_PS -> SetLineColor(kAzure+10); histTRFDM_OLD_PS -> SetMarkerStyle(20); histTRFDM_OLD_PS -> SetMarkerColor(kAzure+10);

    TFile *fileBiswarup = new TFile("/home/luca/Scrivania/nuovo/Muon_Lpt_by_Apt.root","READ");
    TH1D *histBiswarupTRFData =  (TH1D*) fileBiswarup -> Get("hData25y4"); 
    histBiswarupTRFData -> SetDirectory(0); histBiswarupTRFData -> SetMarkerStyle(21); histBiswarupTRFData -> SetLineColor(kBlack);
    TH1D *histBiswarupTRFMC =  (TH1D*) fileBiswarup -> Get("hMC25y4"); 
    histBiswarupTRFMC -> SetDirectory(0); histBiswarupTRFMC -> SetMarkerStyle(21);  histBiswarupTRFMC -> SetLineColor(kBlack);
    fileBiswarup -> Close();

    TLegend *legendTests = new TLegend(0.6,0.7,0.89,0.89);
    legendTests -> AddEntry(histTRFSM_MASS,"Single Muons - 2.7 < m < 3.2 GeV/c^{2}","LP");
    legendTests -> AddEntry(histTRFDM_MASS,"DiMuons - 2.7 < m < 3.2 GeV/c^{2}","LP");
    legendTests -> AddEntry(histTRFSM_CV0L7,"Single Muons - CINT7 + CV0L7","LP");
    legendTests -> AddEntry(histTRFDM_CV0L7,"DiMuons - CINT7 + CV0L7","LP");
    legendTests -> AddEntry(histTRFSM_OLD_PS,"Single Muons - OLD PS","LP");
    legendTests -> AddEntry(histTRFDM_OLD_PS,"DiMuons - OLD PS","LP");
    legendTests -> AddEntry(histBiswarupTRFData,"Biswarup data","LP");

    TH2D *histGridAllPt = new TH2D("histGridAllPt","",100,0.,10.,100,0.,30000);

    TCanvas *cavasAllPt = new TCanvas("cavasAllPt","cavasAllPt",1200,1200);
    histGridAllPt -> Draw();
    histAllPtSM_MASS -> Draw("EPsame");
    histAllPtDM_MASS -> Draw("EPsame");
    histAllPtSM_CV0L7 -> Draw("EPsame");
    histAllPtDM_CV0L7 -> Draw("EPsame");
    histAllPtSM_OLD_PS -> Draw("EPsame");
    histAllPtDM_OLD_PS -> Draw("EPsame");
    legendTests -> Draw("same");

    TH2D *histGridLowPt = new TH2D("histGridLowPt","",100,0.,10.,100,0.,6000);

    TCanvas *cavasLowPt = new TCanvas("cavasLowPt","cavasLowPt",1200,1200);
    histGridLowPt -> Draw();
    histLowPtSM_MASS -> Draw("EPsame");
    histLowPtDM_MASS -> Draw("EPsame");
    histLowPtSM_CV0L7 -> Draw("EPsame");
    histLowPtDM_CV0L7 -> Draw("EPsame");
    histLowPtSM_OLD_PS -> Draw("EPsame");
    histLowPtDM_OLD_PS -> Draw("EPsame");
    legendTests -> Draw("same");

    TH2D *histGridTests = new TH2D("histGridTests","",100,0.,10.,100,0.,1.2);

    TCanvas *cavasTests = new TCanvas("cavasTests","cavasTests",1200,1200);
    histGridTests -> Draw();
    histTRFSM_MASS -> Draw("EPsame");
    histTRFDM_MASS -> Draw("EPsame");
    histTRFSM_CV0L7 -> Draw("EPsame");
    histTRFDM_CV0L7 -> Draw("EPsame");
    histTRFSM_OLD_PS -> Draw("EPsame");
    histTRFDM_OLD_PS -> Draw("EPsame");
    histBiswarupTRFData -> Draw("EPsame");
    legendTests -> Draw("same");


    return;


    TFile *fileTRF_energy_beam_fixed = new TFile("/home/luca/cernbox/JPSI/Jpsi_polarization_data_sync/hist_checkPbPb2015/energy_beam_fixed/hist_TRF_sum.root","READ");
    TList *listTRF_energy_beam_fixed = (TList*) fileTRF_energy_beam_fixed -> Get("chist0");
    TH1D *histAllPtSM_energy_beam_fixed = (TH1D*) listTRF_energy_beam_fixed -> FindObject("histAllPtSM"); histAllPtSM_energy_beam_fixed -> SetDirectory(0);
    histAllPtSM_energy_beam_fixed -> Sumw2(); histAllPtSM_energy_beam_fixed -> SetLineColor(kMagenta+2);
    TH1D *histLowPtSM_energy_beam_fixed = (TH1D*) listTRF_energy_beam_fixed -> FindObject("histLowPtSM"); histLowPtSM_energy_beam_fixed -> SetDirectory(0);
    histLowPtSM_energy_beam_fixed -> Sumw2(); histLowPtSM_energy_beam_fixed -> SetLineColor(kMagenta+2);
    TH1D *histAllPtDM_energy_beam_fixed = (TH1D*) listTRF_energy_beam_fixed -> FindObject("histAllPtDM_25eta4"); histAllPtDM_energy_beam_fixed -> SetDirectory(0);
    histAllPtDM_energy_beam_fixed -> Sumw2(); histAllPtDM_energy_beam_fixed -> SetLineColor(kOrange+2);
    TH1D *histLowPtDM_energy_beam_fixed = (TH1D*) listTRF_energy_beam_fixed -> FindObject("histLowPtDM_25eta4"); histLowPtDM_energy_beam_fixed -> SetDirectory(0);
    histLowPtDM_energy_beam_fixed -> Sumw2(); histLowPtDM_energy_beam_fixed -> SetLineColor(kOrange+2);

    /*TFile *fileTRF_old_PS_CMUL7_or_CINT7 = new TFile("/home/luca/cernbox/JPSI/Jpsi_polarization_data_sync/hist_checkPbPb2015/old_PS_CMUL7_or_CINT7/hist_TRF_sum.root","READ");
    TList *listTRF_old_PS_CMUL7_or_CINT7 = (TList*) fileTRF_old_PS_CMUL7_or_CINT7 -> Get("chist0");
    TH1D *histAllPtSM_old_PS_CMUL7_or_CINT7 = (TH1D*) listTRF_old_PS_CMUL7_or_CINT7 -> FindObject("histAllPtSM"); histAllPtSM_old_PS_CMUL7_or_CINT7 -> SetDirectory(0);
    histAllPtSM_old_PS_CMUL7_or_CINT7 -> Sumw2(); histAllPtSM_old_PS_CMUL7_or_CINT7 -> SetLineColor(kMagenta+2);
    TH1D *histLowPtSM_old_PS_CMUL7_or_CINT7 = (TH1D*) listTRF_old_PS_CMUL7_or_CINT7 -> FindObject("histLowPtSM"); histLowPtSM_old_PS_CMUL7_or_CINT7 -> SetDirectory(0);
    histLowPtSM_old_PS_CMUL7_or_CINT7 -> Sumw2(); histLowPtSM_old_PS_CMUL7_or_CINT7 -> SetLineColor(kMagenta+2);
    TH1D *histAllPtDM_old_PS_CMUL7_or_CINT7 = (TH1D*) listTRF_old_PS_CMUL7_or_CINT7 -> FindObject("histAllPtDM_25eta4"); histAllPtDM_old_PS_CMUL7_or_CINT7 -> SetDirectory(0);
    histAllPtDM_old_PS_CMUL7_or_CINT7 -> Sumw2(); histAllPtDM_old_PS_CMUL7_or_CINT7 -> SetLineColor(kYellow+2);
    TH1D *histLowPtDM_old_PS_CMUL7_or_CINT7 = (TH1D*) listTRF_old_PS_CMUL7_or_CINT7 -> FindObject("histLowPtDM_25eta4"); histLowPtDM_old_PS_CMUL7_or_CINT7 -> SetDirectory(0);
    histLowPtDM_old_PS_CMUL7_or_CINT7 -> Sumw2(); histLowPtDM_old_PS_CMUL7_or_CINT7 -> SetLineColor(kYellow+2);*/

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

    TFile *fileLucaMC = new TFile("/home/luca/GITHUB/polarization/trigger_checks/triggerResponseFunction_test.root","READ");
    TH1D *histLucaTRFMC = (TH1D*) fileLucaMC -> Get("histTriggerResponseFunctionMC");
    histLucaTRFMC -> SetMarkerStyle(20); histLucaTRFMC -> SetMarkerColor(kBlack);

    TFile *fileBiswarup = new TFile("/home/luca/Scrivania/nuovo/Muon_Lpt_by_Apt.root","READ");
    TH1D *histBiswarupTRFData =  (TH1D*) fileBiswarup -> Get("hData25y4"); histBiswarupTRFData -> SetDirectory(0); histBiswarupTRFData -> SetMarkerStyle(25); histBiswarupTRFData -> SetLineColor(kBlack);
    TH1D *histBiswarupTRFMC =  (TH1D*) fileBiswarup -> Get("hMC25y4"); histBiswarupTRFMC -> SetDirectory(0); histBiswarupTRFData -> SetLineColor(kMagenta);
    fileBiswarup -> Close();

    TH1D *histTRFSM_AOD175 = new TH1D("histTRFSM_AOD175","histTRFSM_AOD175",500,0.,50.);
    histTRFSM_AOD175 -> Divide(histLowPtSM_AOD175,histAllPtSM_AOD175,1,1); histTRFSM_AOD175 -> SetLineColor(kRed); histTRFSM_AOD175 -> SetMarkerStyle(28);

    TH1D *histTRFDM_AOD175 = new TH1D("histTRFDM_AOD175","histTRFDM_AOD175",500,0.,50.);
    histTRFDM_AOD175 -> Divide(histLowPtDM_AOD175,histAllPtDM_AOD175,1,1); histTRFDM_AOD175 -> SetLineColor(kGreen+2); histTRFDM_AOD175 -> SetMarkerStyle(28);

    //TH1D *histTRFSM_old_PS_CMUL7_or_CINT7 = new TH1D("histTRFSM_old_PS_CMUL7_or_CINT7","histTRFSM_old_PS_CMUL7_or_CINT7",500,0.,50.);
    //histTRFSM_old_PS_CMUL7_or_CINT7 -> Divide(histLowPtSM_old_PS_CMUL7_or_CINT7,histAllPtSM_old_PS_CMUL7_or_CINT7,1,1); histTRFSM_old_PS_CMUL7_or_CINT7 -> SetLineColor(kMagenta+2); histTRFSM_old_PS_CMUL7_or_CINT7 -> SetMarkerStyle(29);

    //TH1D *histTRFDM_old_PS_CMUL7_or_CINT7 = new TH1D("histTRFDM_old_PS_CMUL7_or_CINT7","histTRFDM_old_PS_CMUL7_or_CINT7",500,0.,50.);
    //histTRFDM_old_PS_CMUL7_or_CINT7 -> Divide(histLowPtDM_old_PS_CMUL7_or_CINT7,histAllPtDM_old_PS_CMUL7_or_CINT7,1,1); histTRFDM_old_PS_CMUL7_or_CINT7 -> SetLineColor(kYellow+2); histTRFDM_old_PS_CMUL7_or_CINT7 -> SetMarkerStyle(29);

    TH1D *histTRFSM_energy_beam_fixed = new TH1D("histTRFSM_energy_beam_fixed","histTRFSM_energy_beam_fixed",500,0.,50.);
    histTRFSM_energy_beam_fixed -> Divide(histLowPtSM_energy_beam_fixed,histAllPtSM_energy_beam_fixed,1,1); histTRFSM_energy_beam_fixed -> SetLineColor(kMagenta); histTRFSM_energy_beam_fixed -> SetMarkerStyle(29);

    TH1D *histTRFDM_energy_beam_fixed = new TH1D("histTRFDM_energy_beam_fixed","histTRFDM_energy_beam_fixed",500,0.,50.);
    histTRFDM_energy_beam_fixed -> Divide(histLowPtDM_energy_beam_fixed,histAllPtDM_energy_beam_fixed,1,1); histTRFDM_energy_beam_fixed -> SetLineColor(kOrange); histTRFDM_energy_beam_fixed -> SetMarkerStyle(29);


    TH1D *histTRFSM_no_PS_no_CMUL7 = new TH1D("histTRFSM_no_PS_no_CMUL7","histTRFSM_no_PS_no_CMUL7",500,0.,50.);
    histTRFSM_no_PS_no_CMUL7 -> Divide(histLowPtSM_no_PS_no_CMUL7,histAllPtSM_no_PS_no_CMUL7,1,1); histTRFSM_no_PS_no_CMUL7 -> SetLineColor(kRed);

    TH1D *histTRFDM_no_PS_no_CMUL7 = new TH1D("histTRFDM_no_PS_no_CMUL7","histTRFDM_no_PS_no_CMUL7",500,0.,50.);
    histTRFDM_no_PS_no_CMUL7 -> Divide(histLowPtDM_no_PS_no_CMUL7,histAllPtDM_no_PS_no_CMUL7,1,1); histTRFDM_no_PS_no_CMUL7 -> SetLineColor(kGreen+2);

    TH1D *histTRFSM_PS_CMUL7 = new TH1D("histTRFSM_PS_CMUL7","histTRFSM_PS_CMUL7",500,0.,50.);
    histTRFSM_PS_CMUL7 -> Divide(histLowPtSM_PS_CMUL7,histAllPtSM_PS_CMUL7,1,1); histTRFSM_PS_CMUL7 -> SetLineColor(kOrange); histTRFSM_PS_CMUL7 -> SetMarkerSize(0.5); histTRFSM_PS_CMUL7 -> SetMarkerStyle(20); histTRFSM_PS_CMUL7 -> SetMarkerColor(kOrange);

    TH1D *histTRFDM_PS_CMUL7 = new TH1D("histTRFDM_PS_CMUL7","histTRFDM_PS_CMUL7",500,0.,50.);
    histTRFDM_PS_CMUL7 -> Divide(histLowPtDM_PS_CMUL7,histAllPtDM_PS_CMUL7,1,1); histTRFDM_PS_CMUL7 -> SetLineColor(kAzure); histTRFDM_PS_CMUL7 -> SetMarkerSize(0.5); histTRFDM_PS_CMUL7 -> SetMarkerStyle(20); histTRFDM_PS_CMUL7 -> SetMarkerColor(kAzure);



    /*
    TCanvas *canvasCompAllLow = new TCanvas("canvasCompAllLow","canvasCompAllLow",1200,600);
    canvasCompAllLow -> Divide(2,1);

    canvasCompAllLow -> cd(1);
    //histAllPtSM_no_PS_no_CMUL7 -> Draw("E");
    //histAllPtSM_PS_CMUL7 -> Draw("Esame");
    histAllPtSM_energy_beam_fixed -> Draw("Esame");
    //histAllPtDM_no_PS_no_CMUL7 -> Draw("Esame");
    //histAllPtDM_PS_CMUL7 -> Draw("Esame");

    canvasCompAllLow -> cd(2);
    //histLowPtSM_no_PS_no_CMUL7 -> Draw("E");
    //histLowPtSM_PS_CMUL7 -> Draw("Esame");
    histLowPtSM_energy_beam_fixed -> Draw("Esame");
    //histLowPtDM_no_PS_no_CMUL7 -> Draw("Esame");
    //histLowPtDM_PS_CMUL7 -> Draw("Esame");
    */





    TH2D *histGridTRF = new TH2D("histGridTRF","",100,0.,10.,100,0.,1.2);

    TLegend *legendCompTRF = new TLegend(0.6,0.7,0.89,0.89);
    legendCompTRF -> AddEntry(histTRFSM_no_PS_no_CMUL7,"Single Muons - no PS, no CMUL7","LP");
    legendCompTRF -> AddEntry(histTRFDM_no_PS_no_CMUL7,"DiMuons - no PS, no CMUL7","LP");
    //legendCompTRF -> AddEntry(histTRFSM_PS_CMUL7,"SM - PS, CMUL7","LP");
    legendCompTRF -> AddEntry(histTRFDM_PS_CMUL7,"DiMuons - PS, CMUL7 && CINT7","LP");
    legendCompTRF -> AddEntry(histBiswarupTRFData,"Data Biswarup","LP");
    legendCompTRF -> AddEntry(histBiswarupTRFMC,"MC Biswarup","LP");
    legendCompTRF -> AddEntry(histTRFSM_AOD175,"Single Muons - AOD175","LP");
    legendCompTRF -> AddEntry(histTRFDM_AOD175,"DiMuons - AOD175","LP");

    /*
    TCanvas *canvasCompTRF = new TCanvas("canvasCompTRF","canvasCompTRF",600,600);
    histGridTRF -> Draw();
    //histTRFSM_no_PS_no_CMUL7 -> Draw("Esame");
    //histTRFDM_no_PS_no_CMUL7 -> Draw("Esame");
    //histTRFSM_AOD175 -> Draw("Esame");
    //histTRFDM_AOD175 -> Draw("Esame");
    //histTRFDM_PS_CMUL7 -> Draw("Esame");
    histBiswarupTRFData -> Draw("EPsame");
    histBiswarupTRFMC -> Draw("Esame");
    //histTRFSM_old_PS_CMUL7_or_CINT7 -> Draw("EPsame");
    //histTRFDM_old_PS_CMUL7_or_CINT7 -> Draw("EPsame");
    histTRFSM_energy_beam_fixed -> Draw("EPsame");
    histTRFDM_energy_beam_fixed -> Draw("EPsame");
    //histLucaTRFMC -> Draw("EPsame");
    legendCompTRF -> Draw("same");
    */




    TFile *fLHC15o = new TFile("/home/luca/Scrivania/nuovo/Sum_LHC15o_PS.root");

    TH1D *h0Apt = (TH1D*)fLHC15o -> Get("hAllpt_1M"); h0Apt -> SetLineColor(kRed);
    TH1D *h0Lpt = (TH1D*)fLHC15o -> Get("hLpt_1M"); h0Lpt -> SetLineColor(kRed);

    TH2D *histGridComp = new TH2D("histGridComp","",100,0.,10.,100,0.,0.15);

    //histAllPtDM_energy_beam_fixed -> Scale(1./histAllPtSM_energy_beam_fixed -> Integral());
    //histLowPtDM_energy_beam_fixed -> Scale(1./histLowPtSM_energy_beam_fixed -> Integral());
    //h0Apt -> Scale(1./h0Apt -> Integral());
    //h0Lpt -> Scale(1./h0Lpt -> Integral());

    //histAllPtDM_energy_beam_fixed -> SetNormFactor(1);
    //histLowPtDM_energy_beam_fixed -> SetNormFactor(1);
    //h0Apt -> SetNormFactor(1);
    //h0Lpt -> SetNormFactor(1);


    TCanvas *canvasComp = new TCanvas("canvasComp","canvasComp",1200,600);
    canvasComp -> Divide(2,1);
    canvasComp -> cd(1); histGridComp -> Draw(); histAllPtDM_energy_beam_fixed -> Draw("Esame"); h0Apt -> Draw("Esame");
    canvasComp -> cd(2); histGridComp -> Draw(); histLowPtDM_energy_beam_fixed -> Draw("Esame"); h0Lpt -> Draw("Esame");



    TH1D *histL = (TH1D*) histLowPtDM_energy_beam_fixed -> Clone("histL");
    histL -> Divide(histAllPtDM_energy_beam_fixed);

    TH1D *histB = (TH1D*) h0Lpt -> Clone("histB"); histB -> SetLineColor(kGreen);
    histB -> Divide(h0Apt);


    TCanvas *canvasCompProva = new TCanvas("canvasCompProva","canvasCompProva",600,600);
    histL -> Draw("E");
    histB -> Draw("Esame");

    return;

    TH1D *histTRFLuca = new TH1D("histTRFLuca","",500,0.,50.);
    histTRFLuca -> Divide(histLowPtDM,histAllPtDM,1,1);

    TH1D *histTRFBisw = new TH1D("histTRFBisw","",500,0.,50.);
    histTRFBisw -> Divide(h0Lpt,h0Apt,1,1);

    TH2D *histGridTRFComp = new TH2D("histGridTRFComp","",100,0.,10.,100,0.,1.2);

    TCanvas *canvasTRF = new TCanvas("canvasTRF","canvasTRF",600,600);
    //histGridTRFComp -> Draw(); histTRFLuca -> Draw("EPsame"); histTRFBisw -> Draw("EPsame");
    //histTRFLuca -> Draw("EP"); histTRFBisw -> Draw("EPsame");
}
