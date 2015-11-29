#include <TFile.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TF1.h>
#include <TH2.h>
#include <TH3.h>
#include <TStyle.h>
#include <TString.h>
#include <TObjArray.h>
#include <TMath.h>
#include <THashList.h>
#include <TPaveText.h>
#include <THnSparse.h>

TString runNumber = "000244982";
TString triggers = "INT7 EMCEG1 EMCEJ1 DMCEG1 DMCEJ1";
TString clusterListName = "AliAnalysisTaskSAQA_CaloClusters_TPC_BeforeTender_%s_histos";
TString patchTaskListName = "AliEmcalTriggerQATask_%s_histos";
TString patchListName = "histosAliEmcalTriggerQATask_%s_AliEmcalTriggerQAAP";
TString clusHistName = "fHistClusPhiEtaEnergy_0";
TString eventQAHistName = "fHistEventQA";
TString minBiasTrg = "INT7";
TString patchTypes = "EMCJEH EMCGAH";
Bool_t draw = kFALSE;

TString outputFileName = "histos_%s.root";

const Double_t phiDiv[3] = {0, 4, TMath::TwoPi()};  // separation EMCal/DCal
const TString det[2] = {"EMCal", "DCal"};
Color_t color[2] = {kRed+2, kBlue+2};

TObjArray* histos = new TObjArray();

TFile* OpenFile(const TString& run);
void runClusterAnalysis(TFile* file, const TString& trg);
void runPatchAnalysis(TFile* file, const TString& trge);
void doMedianAnalysis(THashList* hashlist, const TString& trg);
void doMaxVsMedianAnalysis(THashList* hashlist, const TString& trg, const char* type);
void doPatchSpectraAnalysis(THashList* hashlist, const TString& trg, const char* type);
void doRatios(const TString& trg, const char* label);
void SaveOutput();
TH2* ProjectWithWeights(TH3* h3, const char* hname);

void runAnalysis()
{
  TH1::AddDirectory(kFALSE);
  gStyle->SetOptStat(0);
  
  TFile* file = OpenFile(runNumber);
  if (!file) return;
  
  TObjArray* arrTrg = triggers.Tokenize(" ");
  TIter next(arrTrg);
  TObjString* objTrg = 0;

  while ((objTrg = static_cast<TObjString*>(next()))) {
    TString trg = objTrg->GetName();
    runClusterAnalysis(file, trg);
    runPatchAnalysis(file, trg);
  }
  
  next.Reset();

  TObjArray* patchTypesArr = patchTypes.Tokenize(" ");
  
  while ((objTrg = static_cast<TObjString*>(next()))) {
    TString trg = objTrg->GetName();
    doRatios(trg, "ClusterEnergy");

    TIter nextPatchType(patchTypesArr);
    TObjString* patchType = 0;
    while ((patchType = static_cast<TObjString*>(nextPatchType()))) {
      TString label;
	
      label = Form("%sOnlinePatchAmp", patchType->GetName());
      doRatios(trg, label);
	
      label = Form("%sOfflinePatchAmp", patchType->GetName());
      doRatios(trg, label);
    }
  }

  SaveOutput();
}

TFile* OpenFile(const TString& run)
{
  TString path = Form("%s/AnalysisResults.root", run.Data());
  TFile* file = TFile::Open(path);
  if (!file || file->IsZombie()) {
    Printf("Could not open file %s!", path.Data());
    file = 0;
  }
  return file;
}

void runClusterAnalysis(TFile* file, const TString& trg)
{
  TString listName = Form(clusterListName.Data(), trg.Data());
  TList* list = static_cast<TList*>(file->Get(listName));
  if (!list) {
    Printf("Could not get list %s!", listName.Data());
    return;
  }

  THnSparse* thn = static_cast<THnSparse*>(list->FindObject(eventQAHistName));
  if (!thn) {
    Printf("Could not get hist %s!", eventQAHistName.Data());
    return;
  }

  TString maxClusEnergyName = Form("MaxClusterEnergy_%s", trg.Data());
  TH1* maxClusEnergy = thn->Projection(1);
  maxClusEnergy->SetName(maxClusEnergyName);
  maxClusEnergy->SetTitle(maxClusEnergyName);
  maxClusEnergy->Sumw2();
  maxClusEnergy->SetMarkerStyle(kFullCircle);
  maxClusEnergy->SetMarkerSize(0.8);
  maxClusEnergy->SetMarkerColor(kBlack);
  maxClusEnergy->SetLineColor(kBlack);
  histos->Add(maxClusEnergy);

  TH3* h3 = static_cast<TH3*>(list->FindObject(clusHistName));
  if (!h3) {
    Printf("Could not get hist %s!", clusHistName.Data());
    return;
  }

  TString clusPosWeightName = Form("ClusterPositionEnergy_%s", trg.Data());
  TH2* clusPosWeight = ProjectWithWeights(h3, clusPosWeightName);
  histos->Add(clusPosWeight);
  
  if (draw) {
    TCanvas* canvasPosWeight = new TCanvas(clusPosWeightName, clusPosWeightName);
    canvasPosWeight->cd();
    clusPosWeight->Draw("colz");
  }
  
  TH2* clusPos = static_cast<TH2*>(h3->Project3D("yx"));
  TString clusPosName = Form("ClusterPosition_%s", trg.Data());
  clusPos->SetName(clusPosName);
  clusPos->SetTitle(clusPosName);
  histos->Add(clusPos);
 
  if (draw) {
    TCanvas* canvasPos = new TCanvas(clusPosName, clusPosName);
    canvasPos->cd();
    clusPos->Draw("colz");
  }

  TString canvClusEName(Form("ClusterEnergy_%s", trg.Data()));

  TCanvas* canvasEne = 0;
  if (draw) {
    canvasEne = new TCanvas(canvClusEName, canvClusEName);
    canvasEne->cd();
    canvasEne->SetLogy();
  }

  for (Int_t i = 0; i < 2; i++) {
    h3->GetYaxis()->SetRangeUser(phiDiv[i], phiDiv[i+1]);
  
    TH1* clusE = static_cast<TH1*>(h3->Project3D("z"));
    clusE->Rebin(2);
    clusE->Sumw2();
    clusE->SetMarkerStyle(kFullCircle);
    clusE->SetMarkerSize(0.8);
    clusE->SetMarkerColor(color[i]);
    clusE->SetLineColor(color[i]);
    histos->Add(clusE);
    TString clusEName = Form("ClusterEnergy_%s_%s", det[i].Data(), trg.Data());
    clusE->SetName(clusEName);
    clusE->SetTitle(clusEName);

    if (draw) {
      if (i>0) clusE->Draw("same");
      else clusE->Draw();
    }
  }
}

void runPatchAnalysis(TFile* file, const TString& trg)
{
  TString listName = Form(patchTaskListName.Data(), trg.Data());
  TList* list = static_cast<TList*>(file->Get(listName));
  if (!list) {
    Printf("Could not get list %s!", listName.Data());
    return;
  }

  TString hashlistName = Form(patchListName.Data(), trg.Data());
  THashList* hashlist = static_cast<THashList*>(list->FindObject(hashlistName));
  if (!hashlist) {
    Printf("Could not get hashlist %s!", hashlistName.Data());
    return;
  }
  
  doMedianAnalysis(hashlist, trg);
  doMaxVsMedianAnalysis(hashlist, trg, "Offline");
  doMaxVsMedianAnalysis(hashlist, trg, "Online");

  doPatchSpectraAnalysis(hashlist, trg, "Offline");
  doPatchSpectraAnalysis(hashlist, trg, "Online");
  doPatchSpectraAnalysis(hashlist, trg, "Recalc");
}

void doRatios(const TString& trg, const char* label)
{
  for (Int_t i = 0; i < 2; i++) {
    TString minBiasHistName = Form("%s_%s_%s", label, det[i].Data(), minBiasTrg.Data());
    TH1* minBiasHist = static_cast<TH1*>(histos->FindObject(minBiasHistName));
    if (!minBiasHist) {
      Printf("Could not find hist %s", minBiasHistName.Data());
      continue;
    }

    TH1* minBiasHistTemp = static_cast<TH1*>(minBiasHist->Clone("temp"));
    minBiasHistTemp->Rebin(5);
    
    TString histName = Form("%s_%s_%s", label, det[i].Data(), trg.Data());
    TH1* hist = static_cast<TH1*>(histos->FindObject(histName));
    if (!hist) {
      Printf("Could not find hist %s", histName.Data());
      continue;
    }

    TString ratioName = Form("%s_TriggerTurnOnCurve_%s_%s", label, det[i].Data(), trg.Data());
    TH1* ratio = static_cast<TH1*>(hist->Clone(ratioName));
    ratio->SetTitle(ratioName);
    ratio->Rebin(5);
    ratio->Divide(minBiasHistTemp);
    histos->Add(ratio);

    delete minBiasHistTemp;
    minBiasHistTemp = 0;
    
    if (draw) {
      TCanvas *canvas = new TCanvas(ratioName, ratioName);
      canvas->cd();
      ratio->Draw();
    }
  }
}

void SaveOutput()
{
  TString outputFilePathName = Form(outputFileName.Data(), runNumber.Data());
  TFile* file = TFile::Open(outputFilePathName, "recreate");
  file->cd();

  histos->Write();
  file->Close();
  delete file;
}

void doMedianAnalysis(THashList* hashlist, const TString& trg)
{
  TString medianCorrName = "EMCTRQA_histEMCalMedianVsDCalMedianOffline";
  TH2* meadianCorr = static_cast<TH2*>(hashlist->FindObject(medianCorrName));
  if (!meadianCorr) {
    Printf("Could not get hist %s!", medianCorrName.Data());
    return;
  }

  medianCorrName = Form("EMCalMedianVsDCalsMedianOffline_%s", trg.Data());
  TH2* meadianCorrCopy = static_cast<TH2*>(meadianCorr->Clone(medianCorrName));
  meadianCorrCopy->SetTitle(medianCorrName);
  meadianCorrCopy->GetXaxis()->SetRangeUser(0,400);
  meadianCorrCopy->GetYaxis()->SetRangeUser(0,400);
  histos->Add(meadianCorrCopy);

  medianCorrName += "_fit";
  TF1* fit = new TF1(medianCorrName, "pol1", 0, 1000);
  histos->Add(fit);
  
  if (draw) {
    TCanvas *canvasMedianCorr = new TCanvas(medianCorrName, medianCorrName);
    canvasMedianCorr->cd();
    canvasMedianCorr->SetLogz();
    meadianCorrCopy->Draw("colz");
    
    meadianCorrCopy->Fit(fit);

    TPaveText* pave = new TPaveText(0.1, 0.9, 0.4, 0.7, "brNDC");
    pave->SetBorderSize(0);
    pave->SetFillStyle(0);
    Double_t p0 = fit->GetParameter("p0");
    Double_t p1 = fit->GetParameter("p1");
    TString line1 = Form("p0 = %.3f", p0);
    TString line2 = Form("p1 = %.3f", p1);
    pave->AddText(line1);
    pave->AddText(line2);
    pave->Draw();
  }
  else {
    meadianCorrCopy->Fit(fit, "0");
  }
}

void doMaxVsMedianAnalysis(THashList* hashlist, const TString& trg, const char* type)
{
  TObjArray* patchTypesArr = patchTypes.Tokenize(" ");
  TIter next(patchTypesArr);
  TObjString* patchType = 0;
  while ((patchType = static_cast<TObjString*>(next()))) {
    for (Int_t i = 0; i < 2; i++) {
      for (Int_t j = 0; j < 2; j++) {
	TString histName = Form("EMCTRQA_hist%sMedianVs%sMax%s%s", det[i].Data(), det[j].Data(), patchType->GetName(), type);
	TH2* hist = static_cast<TH2*>(hashlist->FindObject(histName));
	if (!hist) {
	  Printf("Could not get hist %s!", histName.Data());
	  return;
	}

	histName = Form("%sMedianVs%sMax%s%s_%s", det[i].Data(), det[j].Data(), patchType->GetName(), type, trg.Data());
	TH2* histCopy = static_cast<TH2*>(hist->Clone(histName));
	histCopy->SetTitle(histName);
	histCopy->GetXaxis()->SetRangeUser(0,1000);
	histCopy->GetYaxis()->SetRangeUser(0,1000);
	histos->Add(histCopy);

	if (draw) {
	  TCanvas *canvas = new TCanvas(histName, histName);
	  canvas->cd();
	  canvas->SetLogz();
	  histCopy->Draw("colz");
	}

	if (i > j) {
	  histName = Form("%sMedian%s%s_%s", det[i].Data(), patchType->GetName(), type, trg.Data());
	  TH1* histMed = histCopy->ProjectionY(histName);
	  histMed->SetTitle(histName);
	  histMed->Sumw2();
	  histMed->SetMarkerStyle(kFullCircle);
	  histMed->SetMarkerSize(0.8);
	  histMed->SetMarkerColor(color[i]);
	  histMed->SetLineColor(color[i]);
	  histos->Add(histMed);

	  if (draw) {
	    TCanvas *canvasMed = new TCanvas(histName, histName);
	    canvasMed->cd();
	    canvasMed->SetLogy();
	    histMed->Draw();
	  }
	  
	  histName = Form("%sMax%s%s_%s", det[j].Data(), patchType->GetName(), type, trg.Data());
	  TH1* histMax = histCopy->ProjectionX(histName);
	  histMax->SetTitle(histName);
	  histMax->Sumw2();
	  histMax->SetMarkerStyle(kFullCircle);
	  histMax->SetMarkerSize(0.8);
	  histMax->SetMarkerColor(color[j]);
	  histMax->SetLineColor(color[j]);
	  histos->Add(histMax);

	  if (draw) {
	    TCanvas *canvasMax = new TCanvas(histName, histName);
	    canvasMax->cd();
	    canvasMax->SetLogy();
	    histMax->Draw();
	  }
	}
      }
    }
  }
}

void doPatchSpectraAnalysis(THashList* hashlist, const TString& trg, const char* type)
{
  TObjArray* patchTypesArr = patchTypes.Tokenize(" ");
  TIter next(patchTypesArr);
  TObjString* patchType = 0;
  while ((patchType = static_cast<TObjString*>(next()))) {
    for (Int_t i = 0; i < 2; i++) {
      TString histName = Form("EMCTRQA_hist%sPatchAmp%s%s", det[i].Data(), patchType->GetName(), type);
      TH1* hist = static_cast<TH1*>(hashlist->FindObject(histName));
      if (!hist) {
	Printf("Could not get hist %s!", histName.Data());
	return;
      }

      histName = Form("%s%sPatchAmp_%s_%s", patchType->GetName(), type, det[i].Data(), trg.Data());
      TH1* histCopy = static_cast<TH1*>(hist->Clone(histName));
      histCopy->SetTitle(histName);
      histCopy->Sumw2();
      histCopy->SetMarkerStyle(kFullCircle);
      histCopy->SetMarkerSize(0.8);
      histCopy->SetMarkerColor(color[i]);
      histCopy->SetLineColor(color[i]);
      histos->Add(histCopy);

      if (draw) {
	TCanvas *canvas = new TCanvas(histName, histName);
	canvas->cd();
	canvas->SetLogy();
	histCopy->Draw();
      }
    }
  }
}

TH2* ProjectWithWeights(TH3* h3, const char* hname)
{
  TH2* result = new TH2F(hname, hname,
			 h3->GetNbinsX(), h3->GetXaxis()->GetXmin(), h3->GetXaxis()->GetXmax(),
			 h3->GetNbinsY(), h3->GetYaxis()->GetXmin(), h3->GetYaxis()->GetXmax());
  
  for (Int_t x = 0; x <= h3->GetNbinsX()+1; x++) {
    for (Int_t y = 0; y <= h3->GetNbinsY()+1; y++) {
      Double_t sum = 0;
      for (Int_t z = 0; z <= h3->GetNbinsZ()+1; z++) {
	Double_t e = h3->GetZaxis()->GetBinCenter(z);
	sum += e*h3->GetBinContent(x, y, z);
      }
      result->SetBinContent(x, y, sum);
    }
  }

  return result;
}