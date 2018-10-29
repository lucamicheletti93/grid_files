from ROOT import *
from array import array
import os.path
import string

gROOT.ProcessLineSync(".x /home/luca/GITHUB/polarization_classes/DataProcessor.cxx+")
gStyle.SetOptStat(0)

#fileCMUL7Triggers = open("CMUL7Triggers.txt","w")
fileRunList = open("run_list.txt","r")
for eachLine in fileRunList:
    runNumber = ''
    for char in eachLine:
        if char.isdigit():
            runNumber += char
    if runNumber.isdigit():
        if os.path.isfile('/media/luca/488AE2208AE20A70/PbPb_2015_Trees_pDCA/Tree_' + runNumber + '.root'):
            print os.path.join('/media/luca/488AE2208AE20A70/PbPb_2015_Trees_pDCA/Tree_' + runNumber + '.root')
            if os.path.isfile('hist_trigger_response_function/Hist_' + runNumber + '.root'):
                print "The file was already processed"
            else:
                print "The file has to be processed"
                fileData = TFile.Open('/media/luca/488AE2208AE20A70/PbPb_2015_Trees_pDCA/Tree_' + runNumber + '.root')
                treeData = fileData.Get("PbPbTree")
                checkTrig = DataProcessor(treeData)
                checkTrig.ComputeTriggerResponseFunction("FullStat",'hist_trigger_response_function/Hist_' + runNumber + '.root')
                #fileCMUL7Triggers.write(str(checkTrig.GetCMUL7Triggers()) + "\n")
                del checkTrig
                fileData.Close()
        else:
            print os.path.join('File /media/luca/488AE2208AE20A70/PbPb_2015_Trees_pDCA/Tree_' + runNumber + '.root not found')
            #fileCMUL7Triggers.write("\n")
fileRunList.close()
#fileCMUL7Triggers.close()

histLowPtSM = []
histAllPtSM = []
histLowPtSMpDCA = []
histAllPtSMpDCA = []

histSumLowPtSM = TH1D("histSumLowPtSM","",100,0.,10.)
histSumAllPtSM = TH1D("histSumAllPtSM","",100,0.,10.)
histSumLowPtSMpDCA = TH1D("histSumLowPtSMpDCA","",100,0.,10.)
histSumAllPtSMpDCA = TH1D("histSumAllPtSMpDCA","",100,0.,10.)

index = 0

fileCMUL7Triggers = open("CMUL7Triggers.txt","w")
fileRunList = open("run_list.txt","r")
for eachLine in fileRunList:
    runNumber = ''
    for char in eachLine:
        if char.isdigit():
            runNumber += char
    if runNumber.isdigit():
        if os.path.isfile('hist_trigger_response_function/Hist_' + runNumber + '.root'):
            fileHistTriggerResponseFunction = TFile.Open('hist_trigger_response_function/Hist_' + runNumber + '.root')
            histLowPtSM.append(fileHistTriggerResponseFunction.Get("fHistLowPtSM")); histSumLowPtSM.Add(histLowPtSM[index]);
            histAllPtSM.append(fileHistTriggerResponseFunction.Get("fHistAllPtSM")); histSumAllPtSM.Add(histAllPtSM[index]);
            histLowPtSMpDCA.append(fileHistTriggerResponseFunction.Get("fHistLowPtSMpDCA")); histSumLowPtSMpDCA.Add(histLowPtSMpDCA[index]);
            histAllPtSMpDCA.append(fileHistTriggerResponseFunction.Get("fHistAllPtSMpDCA")); histSumAllPtSMpDCA.Add(histAllPtSMpDCA[index]);
            histCMUL7Triggers = fileHistTriggerResponseFunction.Get("fHistCMUL7Triggers")
            print "CMUL7 Triggers = " + str(histCMUL7Triggers.GetBinContent(1))
            fileCMUL7Triggers.write(str(histCMUL7Triggers.GetBinContent(1)) + "\n")
            fileHistTriggerResponseFunction.Close()
            index += 1
        else:
            fileCMUL7Triggers.write("\n")
fileRunList.close()
fileCMUL7Triggers.close()





histTriggerResponseFunctionDataSM = TH1D("histTriggerResponseFunctionDataSM","",100,0.,10.);
histTriggerResponseFunctionDataSM.Divide(histSumLowPtSM,histSumAllPtSM,1,1,"B");
histTriggerResponseFunctionDataSM.SetLineColor(kBlue);
histTriggerResponseFunctionDataSM.SetMarkerColor(kBlue);

histTriggerResponseFunctionDataSMpDCA = TH1D("histTriggerResponseFunctionDataSMpDCA","",100,0.,10.);
histTriggerResponseFunctionDataSMpDCA.Divide(histSumLowPtSMpDCA,histSumAllPtSMpDCA,1,1,"B");
histTriggerResponseFunctionDataSMpDCA.SetLineColor(kRed);
histTriggerResponseFunctionDataSMpDCA.SetMarkerColor(kRed);

histGridTriggerResponseFunction = TH2D("histGridTriggerResponseFunction","",100,0.,10.,100,0.,1.2)
histGridTriggerResponseFunction.GetXaxis().SetTitle("#it{p}_{T} (GeV/#it{c})")

legendGenCost = TLegend(0.3,0.1,0.5,0.2)
legendGenCost.AddEntry(histTriggerResponseFunctionDataSM,"No pDCA","lp")
legendGenCost.AddEntry(histTriggerResponseFunctionDataSMpDCA,"With pDCA","lp")

canvasTriggerResponseFunction = TCanvas("canvasTriggerResponseFunction","canvasTriggerResponseFunction",20,20,600,600);
histGridTriggerResponseFunction.Draw()
histTriggerResponseFunctionDataSM.Draw("Esame");
histTriggerResponseFunctionDataSMpDCA.Draw("Esame");
legendGenCost.Draw()

raw_input()
