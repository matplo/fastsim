{
//=========Macro generated from canvas: cMeanPt_V0M/cMeanPt
//=========  (Tue Sep 15 15:25:36 2015) by ROOT version5.34/30

   TFile fout("MeanPtV0MMult.root", "recreate");
   TList *outl = new TList();

   TCanvas *cMeanPt_V0M = new TCanvas("cMeanPt_V0M", "cMeanPt",12,83,1000,700);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   cMeanPt_V0M->SetHighLightColor(2);
   cMeanPt_V0M->Range(-0.1228788,-0.13,3.877121,2.403333);
   cMeanPt_V0M->SetFillColor(10);
   cMeanPt_V0M->SetBorderMode(0);
   cMeanPt_V0M->SetBorderSize(2);
   cMeanPt_V0M->SetLogx();
   cMeanPt_V0M->SetTickx(1);
   cMeanPt_V0M->SetTicky(1);
   cMeanPt_V0M->SetLeftMargin(0.15);
   cMeanPt_V0M->SetBottomMargin(0.15);
   cMeanPt_V0M->SetFrameFillColor(0);
   cMeanPt_V0M->SetFrameBorderMode(0);
   cMeanPt_V0M->SetFrameFillColor(0);
   cMeanPt_V0M->SetFrameBorderMode(0);
   
   TH1F *hframe__8 = new TH1F("hframe__8","",1000,0,3000);
   hframe__8->SetMinimum(0.25);
   hframe__8->SetMaximum(2.15);
   hframe__8->SetDirectory(0);
   hframe__8->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#ff0000");
   hframe__8->SetLineColor(ci);
   hframe__8->GetXaxis()->SetTitle("#LTd#it{N}_{ch}/d#it{#eta}#GT_{|#it{#eta}| < 0.5}");
   hframe__8->GetXaxis()->SetRange(1,1000);
   hframe__8->GetXaxis()->SetMoreLogLabels();
   hframe__8->GetXaxis()->SetLabelFont(42);
   hframe__8->GetXaxis()->SetLabelOffset(0);
   hframe__8->GetXaxis()->SetLabelSize(0.05);
   hframe__8->GetXaxis()->SetTitleSize(0.06);
   hframe__8->GetXaxis()->SetTitleOffset(1.08);
   hframe__8->GetXaxis()->SetTitleFont(42);
   hframe__8->GetYaxis()->SetTitle("#LT#it{p}_{T}#GT (GeV/#it{c})");
   hframe__8->GetYaxis()->SetLabelFont(42);
   hframe__8->GetYaxis()->SetLabelOffset(0.01);
   hframe__8->GetYaxis()->SetLabelSize(0.05);
   hframe__8->GetYaxis()->SetTitleSize(0.06);
   hframe__8->GetYaxis()->SetTitleOffset(1.3);
   hframe__8->GetYaxis()->SetTitleFont(42);
   hframe__8->GetZaxis()->SetLabelFont(42);
   hframe__8->GetZaxis()->SetLabelSize(0.05);
   hframe__8->GetZaxis()->SetTitleSize(0.06);
   hframe__8->GetZaxis()->SetTitleFont(42);
   hframe__8->Draw(" ");
   
   TGraphErrors *gre = new TGraphErrors(11);
   gre->SetName("MeanPt_ResultsforPionSum_stat");
   gre->SetTitle("Graph");
   gre->SetFillColor(4);
   gre->SetFillStyle(0);
   gre->SetLineColor(4);

   ci = TColor::GetColor("#0000cc");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(1.5);
   gre->SetPoint(0,25.30085,0.5504051);
   gre->SetPointError(0,0.0862803,0.000536488);
   gre->SetPoint(1,20.84913,0.5357772);
   gre->SetPointError(1,0.02997,0.0002507323);
   gre->SetPoint(2,16.51347,0.5173371);
   gre->SetPointError(2,0.00999,0.0001135948);
   gre->SetPoint(3,13.45653,0.5016416);
   gre->SetPointError(3,0.00999,0.0001038733);
   gre->SetPoint(4,11.50694,0.4905663);
   gre->SetPointError(4,0.00998,0.0001062884);
   gre->SetPoint(5,10.07952,0.4813896);
   gre->SetPointError(5,0.009959999,0.0001102858);
   gre->SetPoint(6,8.447464,0.4700067);
   gre->SetPointError(6,0,8.333315e-05);
   gre->SetPoint(7,6.724329,0.4560493);
   gre->SetPointError(7,0,8.766349e-05);
   gre->SetPoint(8,5.397827,0.4429742);
   gre->SetPointError(8,0,9.043352e-05);
   gre->SetPoint(9,3.896809,0.424058);
   gre->SetPointError(9,0,7.279283e-05);
   gre->SetPoint(10,2.261159,0.3906971);
   gre->SetPointError(10,0,6.519221e-05);

   outl.Add(gre);
   
   TH1F *Graph_MeanPt_ResultsforPionSum_stat50 = new TH1F("Graph_MeanPt_ResultsforPionSum_stat50","Graph",100,2.035043,27.69973);
   Graph_MeanPt_ResultsforPionSum_stat50->SetMinimum(0.374601);
   Graph_MeanPt_ResultsforPionSum_stat50->SetMaximum(0.5669725);
   Graph_MeanPt_ResultsforPionSum_stat50->SetDirectory(0);
   Graph_MeanPt_ResultsforPionSum_stat50->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_MeanPt_ResultsforPionSum_stat50->SetLineColor(ci);
   Graph_MeanPt_ResultsforPionSum_stat50->GetXaxis()->SetLabelFont(42);
   Graph_MeanPt_ResultsforPionSum_stat50->GetXaxis()->SetLabelOffset(0);
   Graph_MeanPt_ResultsforPionSum_stat50->GetXaxis()->SetLabelSize(0.05);
   Graph_MeanPt_ResultsforPionSum_stat50->GetXaxis()->SetTitleSize(0.06);
   Graph_MeanPt_ResultsforPionSum_stat50->GetXaxis()->SetTitleOffset(1.08);
   Graph_MeanPt_ResultsforPionSum_stat50->GetXaxis()->SetTitleFont(42);
   Graph_MeanPt_ResultsforPionSum_stat50->GetYaxis()->SetLabelFont(42);
   Graph_MeanPt_ResultsforPionSum_stat50->GetYaxis()->SetLabelOffset(0.01);
   Graph_MeanPt_ResultsforPionSum_stat50->GetYaxis()->SetLabelSize(0.05);
   Graph_MeanPt_ResultsforPionSum_stat50->GetYaxis()->SetTitleSize(0.06);
   Graph_MeanPt_ResultsforPionSum_stat50->GetYaxis()->SetTitleOffset(1.3);
   Graph_MeanPt_ResultsforPionSum_stat50->GetYaxis()->SetTitleFont(42);
   Graph_MeanPt_ResultsforPionSum_stat50->GetZaxis()->SetLabelFont(42);
   Graph_MeanPt_ResultsforPionSum_stat50->GetZaxis()->SetLabelSize(0.05);
   Graph_MeanPt_ResultsforPionSum_stat50->GetZaxis()->SetTitleSize(0.06);
   Graph_MeanPt_ResultsforPionSum_stat50->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_MeanPt_ResultsforPionSum_stat50);
   
   gre->Draw("samepe1");
   
   gre = new TGraphErrors(11);
   gre->SetName("MeanPt_ResultsforPionSum_sys");
   gre->SetTitle("Graph");
   gre->SetFillColor(4);
   gre->SetFillStyle(0);
   gre->SetLineColor(4);

   ci = TColor::GetColor("#0000cc");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(1.5);
   gre->SetPoint(0,25.30085,0.5504051);
   gre->SetPointError(0,0.7590256,0.009017657);
   gre->SetPoint(1,20.84913,0.5357772);
   gre->SetPointError(1,0.6254739,0.008019046);
   gre->SetPoint(2,16.51347,0.5173371);
   gre->SetPointError(2,0.4954042,0.00740641);
   gre->SetPoint(3,13.45653,0.5016416);
   gre->SetPointError(3,0.4036959,0.007127255);
   gre->SetPoint(4,11.50694,0.4905663);
   gre->SetPointError(4,0.3452082,0.007018102);
   gre->SetPoint(5,10.07952,0.4813896);
   gre->SetPointError(5,0.3023856,0.006933787);
   gre->SetPoint(6,8.447464,0.4700067);
   gre->SetPointError(6,0.2534239,0.006571886);
   gre->SetPoint(7,6.724329,0.4560493);
   gre->SetPointError(7,0.2017299,0.00627178);
   gre->SetPoint(8,5.397827,0.4429742);
   gre->SetPointError(8,0.1619348,0.006360468);
   gre->SetPoint(9,3.896809,0.424058);
   gre->SetPointError(9,0.1169043,0.006625931);
   gre->SetPoint(10,2.261159,0.3906971);
   gre->SetPointError(10,0.06783476,0.009193384);
   
   outl.Add(gre);


   TH1F *Graph_MeanPt_ResultsforPionSum_sys51 = new TH1F("Graph_MeanPt_ResultsforPionSum_sys51","Graph",100,1.973992,28.44653);
   Graph_MeanPt_ResultsforPionSum_sys51->SetMinimum(0.3637119);
   Graph_MeanPt_ResultsforPionSum_sys51->SetMaximum(0.5772146);
   Graph_MeanPt_ResultsforPionSum_sys51->SetDirectory(0);
   Graph_MeanPt_ResultsforPionSum_sys51->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_MeanPt_ResultsforPionSum_sys51->SetLineColor(ci);
   Graph_MeanPt_ResultsforPionSum_sys51->GetXaxis()->SetLabelFont(42);
   Graph_MeanPt_ResultsforPionSum_sys51->GetXaxis()->SetLabelOffset(0);
   Graph_MeanPt_ResultsforPionSum_sys51->GetXaxis()->SetLabelSize(0.05);
   Graph_MeanPt_ResultsforPionSum_sys51->GetXaxis()->SetTitleSize(0.06);
   Graph_MeanPt_ResultsforPionSum_sys51->GetXaxis()->SetTitleOffset(1.08);
   Graph_MeanPt_ResultsforPionSum_sys51->GetXaxis()->SetTitleFont(42);
   Graph_MeanPt_ResultsforPionSum_sys51->GetYaxis()->SetLabelFont(42);
   Graph_MeanPt_ResultsforPionSum_sys51->GetYaxis()->SetLabelOffset(0.01);
   Graph_MeanPt_ResultsforPionSum_sys51->GetYaxis()->SetLabelSize(0.05);
   Graph_MeanPt_ResultsforPionSum_sys51->GetYaxis()->SetTitleSize(0.06);
   Graph_MeanPt_ResultsforPionSum_sys51->GetYaxis()->SetTitleOffset(1.3);
   Graph_MeanPt_ResultsforPionSum_sys51->GetYaxis()->SetTitleFont(42);
   Graph_MeanPt_ResultsforPionSum_sys51->GetZaxis()->SetLabelFont(42);
   Graph_MeanPt_ResultsforPionSum_sys51->GetZaxis()->SetLabelSize(0.05);
   Graph_MeanPt_ResultsforPionSum_sys51->GetZaxis()->SetTitleSize(0.06);
   Graph_MeanPt_ResultsforPionSum_sys51->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_MeanPt_ResultsforPionSum_sys51);
   
   gre->Draw("samepe2");
   
   gre = new TGraphErrors(11);
   gre->SetName("MeanPt_ResultsforPionSum_sys");
   gre->SetTitle("Graph");
   gre->SetFillColor(4);
   gre->SetFillStyle(0);
   gre->SetLineColor(4);

   ci = TColor::GetColor("#0000cc");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(1.5);
   gre->SetPoint(0,25.30085,0.5504051);
   gre->SetPointError(0,0.7590256,0.009017657);
   gre->SetPoint(1,20.84913,0.5357772);
   gre->SetPointError(1,0.6254739,0.008019046);
   gre->SetPoint(2,16.51347,0.5173371);
   gre->SetPointError(2,0.4954042,0.00740641);
   gre->SetPoint(3,13.45653,0.5016416);
   gre->SetPointError(3,0.4036959,0.007127255);
   gre->SetPoint(4,11.50694,0.4905663);
   gre->SetPointError(4,0.3452082,0.007018102);
   gre->SetPoint(5,10.07952,0.4813896);
   gre->SetPointError(5,0.3023856,0.006933787);
   gre->SetPoint(6,8.447464,0.4700067);
   gre->SetPointError(6,0.2534239,0.006571886);
   gre->SetPoint(7,6.724329,0.4560493);
   gre->SetPointError(7,0.2017299,0.00627178);
   gre->SetPoint(8,5.397827,0.4429742);
   gre->SetPointError(8,0.1619348,0.006360468);
   gre->SetPoint(9,3.896809,0.424058);
   gre->SetPointError(9,0.1169043,0.006625931);
   gre->SetPoint(10,2.261159,0.3906971);
   gre->SetPointError(10,0.06783476,0.009193384);
   outl.Add(gre);

   TH1F *Graph_MeanPt_ResultsforPionSum_sys52 = new TH1F("Graph_MeanPt_ResultsforPionSum_sys52","Graph",100,1.973992,28.44653);
   Graph_MeanPt_ResultsforPionSum_sys52->SetMinimum(0.3637119);
   Graph_MeanPt_ResultsforPionSum_sys52->SetMaximum(0.5772146);
   Graph_MeanPt_ResultsforPionSum_sys52->SetDirectory(0);
   Graph_MeanPt_ResultsforPionSum_sys52->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_MeanPt_ResultsforPionSum_sys52->SetLineColor(ci);
   Graph_MeanPt_ResultsforPionSum_sys52->GetXaxis()->SetLabelFont(42);
   Graph_MeanPt_ResultsforPionSum_sys52->GetXaxis()->SetLabelOffset(0);
   Graph_MeanPt_ResultsforPionSum_sys52->GetXaxis()->SetLabelSize(0.05);
   Graph_MeanPt_ResultsforPionSum_sys52->GetXaxis()->SetTitleSize(0.06);
   Graph_MeanPt_ResultsforPionSum_sys52->GetXaxis()->SetTitleOffset(1.08);
   Graph_MeanPt_ResultsforPionSum_sys52->GetXaxis()->SetTitleFont(42);
   Graph_MeanPt_ResultsforPionSum_sys52->GetYaxis()->SetLabelFont(42);
   Graph_MeanPt_ResultsforPionSum_sys52->GetYaxis()->SetLabelOffset(0.01);
   Graph_MeanPt_ResultsforPionSum_sys52->GetYaxis()->SetLabelSize(0.05);
   Graph_MeanPt_ResultsforPionSum_sys52->GetYaxis()->SetTitleSize(0.06);
   Graph_MeanPt_ResultsforPionSum_sys52->GetYaxis()->SetTitleOffset(1.3);
   Graph_MeanPt_ResultsforPionSum_sys52->GetYaxis()->SetTitleFont(42);
   Graph_MeanPt_ResultsforPionSum_sys52->GetZaxis()->SetLabelFont(42);
   Graph_MeanPt_ResultsforPionSum_sys52->GetZaxis()->SetLabelSize(0.05);
   Graph_MeanPt_ResultsforPionSum_sys52->GetZaxis()->SetTitleSize(0.06);
   Graph_MeanPt_ResultsforPionSum_sys52->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_MeanPt_ResultsforPionSum_sys52);
   
   gre->Draw("samepe0x0");
   
   gre = new TGraphErrors(11);
   gre->SetName("MeanPt_ResultsforKaonSum_stat");
   gre->SetTitle("Graph");

   ci = TColor::GetColor("#00cc00");
   gre->SetFillColor(ci);
   gre->SetFillStyle(0);

   ci = TColor::GetColor("#00cc00");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#009900");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(24);
   gre->SetMarkerSize(1.5);
   gre->SetPoint(0,25.30085,0.9606179);
   gre->SetPointError(0,0.0862803,0.002225772);
   gre->SetPoint(1,20.84913,0.9301159);
   gre->SetPointError(1,0.02997,0.001007098);
   gre->SetPoint(2,16.51347,0.8897109);
   gre->SetPointError(2,0.00999,0.0004380932);
   gre->SetPoint(3,13.45653,0.8564624);
   gre->SetPointError(3,0.00999,0.0004152225);
   gre->SetPoint(4,11.50694,0.8323061);
   gre->SetPointError(4,0.00998,0.0004309745);
   gre->SetPoint(5,10.07952,0.8116576);
   gre->SetPointError(5,0.009959999,0.0004558726);
   gre->SetPoint(6,8.447464,0.7870132);
   gre->SetPointError(6,0,0.0003431652);
   gre->SetPoint(7,6.724329,0.754069);
   gre->SetPointError(7,0,0.000378423);
   gre->SetPoint(8,5.397827,0.7235572);
   gre->SetPointError(8,0,0.0003946005);
   gre->SetPoint(9,3.896809,0.6760029);
   gre->SetPointError(9,0,0.0003170758);
   gre->SetPoint(10,2.261159,0.5894686);
   gre->SetPointError(10,0,0.0002974352);
   outl.Add(gre);
   
   TH1F *Graph_MeanPt_ResultsforKaonSum_stat53 = new TH1F("Graph_MeanPt_ResultsforKaonSum_stat53","Graph",100,2.035043,27.69973);
   Graph_MeanPt_ResultsforKaonSum_stat53->SetMinimum(0.551804);
   Graph_MeanPt_ResultsforKaonSum_stat53->SetMaximum(1.000211);
   Graph_MeanPt_ResultsforKaonSum_stat53->SetDirectory(0);
   Graph_MeanPt_ResultsforKaonSum_stat53->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_MeanPt_ResultsforKaonSum_stat53->SetLineColor(ci);
   Graph_MeanPt_ResultsforKaonSum_stat53->GetXaxis()->SetLabelFont(42);
   Graph_MeanPt_ResultsforKaonSum_stat53->GetXaxis()->SetLabelOffset(0);
   Graph_MeanPt_ResultsforKaonSum_stat53->GetXaxis()->SetLabelSize(0.05);
   Graph_MeanPt_ResultsforKaonSum_stat53->GetXaxis()->SetTitleSize(0.06);
   Graph_MeanPt_ResultsforKaonSum_stat53->GetXaxis()->SetTitleOffset(1.08);
   Graph_MeanPt_ResultsforKaonSum_stat53->GetXaxis()->SetTitleFont(42);
   Graph_MeanPt_ResultsforKaonSum_stat53->GetYaxis()->SetLabelFont(42);
   Graph_MeanPt_ResultsforKaonSum_stat53->GetYaxis()->SetLabelOffset(0.01);
   Graph_MeanPt_ResultsforKaonSum_stat53->GetYaxis()->SetLabelSize(0.05);
   Graph_MeanPt_ResultsforKaonSum_stat53->GetYaxis()->SetTitleSize(0.06);
   Graph_MeanPt_ResultsforKaonSum_stat53->GetYaxis()->SetTitleOffset(1.3);
   Graph_MeanPt_ResultsforKaonSum_stat53->GetYaxis()->SetTitleFont(42);
   Graph_MeanPt_ResultsforKaonSum_stat53->GetZaxis()->SetLabelFont(42);
   Graph_MeanPt_ResultsforKaonSum_stat53->GetZaxis()->SetLabelSize(0.05);
   Graph_MeanPt_ResultsforKaonSum_stat53->GetZaxis()->SetTitleSize(0.06);
   Graph_MeanPt_ResultsforKaonSum_stat53->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_MeanPt_ResultsforKaonSum_stat53);
   
   gre->Draw("samepe1");
   
   gre = new TGraphErrors(11);
   gre->SetName("MeanPt_ResultsforKaonSum_sys");
   gre->SetTitle("Graph");

   ci = TColor::GetColor("#00cc00");
   gre->SetFillColor(ci);
   gre->SetFillStyle(0);

   ci = TColor::GetColor("#00cc00");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#009900");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(24);
   gre->SetMarkerSize(1.5);
   gre->SetPoint(0,25.30085,0.9606179);
   gre->SetPointError(0,0.7590256,0.01417384);
   gre->SetPoint(1,20.84913,0.9301159);
   gre->SetPointError(1,0.6254739,0.01286197);
   gre->SetPoint(2,16.51347,0.8897109);
   gre->SetPointError(2,0.4954042,0.01231566);
   gre->SetPoint(3,13.45653,0.8564624);
   gre->SetPointError(3,0.4036959,0.01210057);
   gre->SetPoint(4,11.50694,0.8323061);
   gre->SetPointError(4,0.3452082,0.01200537);
   gre->SetPoint(5,10.07952,0.8116576);
   gre->SetPointError(5,0.3023856,0.01185798);
   gre->SetPoint(6,8.447464,0.7870132);
   gre->SetPointError(6,0.2534239,0.01186864);
   gre->SetPoint(7,6.724329,0.754069);
   gre->SetPointError(7,0.2017299,0.01177929);
   gre->SetPoint(8,5.397827,0.7235572);
   gre->SetPointError(8,0.1619348,0.01195226);
   gre->SetPoint(9,3.896809,0.6760029);
   gre->SetPointError(9,0.1169043,0.01297464);
   gre->SetPoint(10,2.261159,0.5894686);
   gre->SetPointError(10,0.06783476,0.01536901);
   outl.Add(gre);
   
   TH1F *Graph_MeanPt_ResultsforKaonSum_sys54 = new TH1F("Graph_MeanPt_ResultsforKaonSum_sys54","Graph",100,1.973992,28.44653);
   Graph_MeanPt_ResultsforKaonSum_sys54->SetMinimum(0.5340304);
   Graph_MeanPt_ResultsforKaonSum_sys54->SetMaximum(1.014861);
   Graph_MeanPt_ResultsforKaonSum_sys54->SetDirectory(0);
   Graph_MeanPt_ResultsforKaonSum_sys54->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_MeanPt_ResultsforKaonSum_sys54->SetLineColor(ci);
   Graph_MeanPt_ResultsforKaonSum_sys54->GetXaxis()->SetLabelFont(42);
   Graph_MeanPt_ResultsforKaonSum_sys54->GetXaxis()->SetLabelOffset(0);
   Graph_MeanPt_ResultsforKaonSum_sys54->GetXaxis()->SetLabelSize(0.05);
   Graph_MeanPt_ResultsforKaonSum_sys54->GetXaxis()->SetTitleSize(0.06);
   Graph_MeanPt_ResultsforKaonSum_sys54->GetXaxis()->SetTitleOffset(1.08);
   Graph_MeanPt_ResultsforKaonSum_sys54->GetXaxis()->SetTitleFont(42);
   Graph_MeanPt_ResultsforKaonSum_sys54->GetYaxis()->SetLabelFont(42);
   Graph_MeanPt_ResultsforKaonSum_sys54->GetYaxis()->SetLabelOffset(0.01);
   Graph_MeanPt_ResultsforKaonSum_sys54->GetYaxis()->SetLabelSize(0.05);
   Graph_MeanPt_ResultsforKaonSum_sys54->GetYaxis()->SetTitleSize(0.06);
   Graph_MeanPt_ResultsforKaonSum_sys54->GetYaxis()->SetTitleOffset(1.3);
   Graph_MeanPt_ResultsforKaonSum_sys54->GetYaxis()->SetTitleFont(42);
   Graph_MeanPt_ResultsforKaonSum_sys54->GetZaxis()->SetLabelFont(42);
   Graph_MeanPt_ResultsforKaonSum_sys54->GetZaxis()->SetLabelSize(0.05);
   Graph_MeanPt_ResultsforKaonSum_sys54->GetZaxis()->SetTitleSize(0.06);
   Graph_MeanPt_ResultsforKaonSum_sys54->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_MeanPt_ResultsforKaonSum_sys54);
   
   gre->Draw("samepe2");
   
   gre = new TGraphErrors(11);
   gre->SetName("MeanPt_ResultsforKaonSum_sys");
   gre->SetTitle("Graph");

   ci = TColor::GetColor("#00cc00");
   gre->SetFillColor(ci);
   gre->SetFillStyle(0);

   ci = TColor::GetColor("#00cc00");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#009900");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(24);
   gre->SetMarkerSize(1.5);
   gre->SetPoint(0,25.30085,0.9606179);
   gre->SetPointError(0,0.7590256,0.01417384);
   gre->SetPoint(1,20.84913,0.9301159);
   gre->SetPointError(1,0.6254739,0.01286197);
   gre->SetPoint(2,16.51347,0.8897109);
   gre->SetPointError(2,0.4954042,0.01231566);
   gre->SetPoint(3,13.45653,0.8564624);
   gre->SetPointError(3,0.4036959,0.01210057);
   gre->SetPoint(4,11.50694,0.8323061);
   gre->SetPointError(4,0.3452082,0.01200537);
   gre->SetPoint(5,10.07952,0.8116576);
   gre->SetPointError(5,0.3023856,0.01185798);
   gre->SetPoint(6,8.447464,0.7870132);
   gre->SetPointError(6,0.2534239,0.01186864);
   gre->SetPoint(7,6.724329,0.754069);
   gre->SetPointError(7,0.2017299,0.01177929);
   gre->SetPoint(8,5.397827,0.7235572);
   gre->SetPointError(8,0.1619348,0.01195226);
   gre->SetPoint(9,3.896809,0.6760029);
   gre->SetPointError(9,0.1169043,0.01297464);
   gre->SetPoint(10,2.261159,0.5894686);
   gre->SetPointError(10,0.06783476,0.01536901);
   outl.Add(gre);
   
   TH1F *Graph_MeanPt_ResultsforKaonSum_sys55 = new TH1F("Graph_MeanPt_ResultsforKaonSum_sys55","Graph",100,1.973992,28.44653);
   Graph_MeanPt_ResultsforKaonSum_sys55->SetMinimum(0.5340304);
   Graph_MeanPt_ResultsforKaonSum_sys55->SetMaximum(1.014861);
   Graph_MeanPt_ResultsforKaonSum_sys55->SetDirectory(0);
   Graph_MeanPt_ResultsforKaonSum_sys55->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_MeanPt_ResultsforKaonSum_sys55->SetLineColor(ci);
   Graph_MeanPt_ResultsforKaonSum_sys55->GetXaxis()->SetLabelFont(42);
   Graph_MeanPt_ResultsforKaonSum_sys55->GetXaxis()->SetLabelOffset(0);
   Graph_MeanPt_ResultsforKaonSum_sys55->GetXaxis()->SetLabelSize(0.05);
   Graph_MeanPt_ResultsforKaonSum_sys55->GetXaxis()->SetTitleSize(0.06);
   Graph_MeanPt_ResultsforKaonSum_sys55->GetXaxis()->SetTitleOffset(1.08);
   Graph_MeanPt_ResultsforKaonSum_sys55->GetXaxis()->SetTitleFont(42);
   Graph_MeanPt_ResultsforKaonSum_sys55->GetYaxis()->SetLabelFont(42);
   Graph_MeanPt_ResultsforKaonSum_sys55->GetYaxis()->SetLabelOffset(0.01);
   Graph_MeanPt_ResultsforKaonSum_sys55->GetYaxis()->SetLabelSize(0.05);
   Graph_MeanPt_ResultsforKaonSum_sys55->GetYaxis()->SetTitleSize(0.06);
   Graph_MeanPt_ResultsforKaonSum_sys55->GetYaxis()->SetTitleOffset(1.3);
   Graph_MeanPt_ResultsforKaonSum_sys55->GetYaxis()->SetTitleFont(42);
   Graph_MeanPt_ResultsforKaonSum_sys55->GetZaxis()->SetLabelFont(42);
   Graph_MeanPt_ResultsforKaonSum_sys55->GetZaxis()->SetLabelSize(0.05);
   Graph_MeanPt_ResultsforKaonSum_sys55->GetZaxis()->SetTitleSize(0.06);
   Graph_MeanPt_ResultsforKaonSum_sys55->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_MeanPt_ResultsforKaonSum_sys55);
   
   gre->Draw("samepe0x0");
   
   gre = new TGraphErrors(11);
   gre->SetName("MeanPt_ResultsforProtonSum_stat");
   gre->SetTitle("Graph");
   gre->SetFillColor(2);
   gre->SetFillStyle(0);
   gre->SetLineColor(2);

   ci = TColor::GetColor("#cc0000");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(29);
   gre->SetMarkerSize(1.5);
   gre->SetPoint(0,25.30085,1.175839);
   gre->SetPointError(0,0.0862803,0.003445743);
   gre->SetPoint(1,20.84913,1.12983);
   gre->SetPointError(1,0.02997,0.0015412);
   gre->SetPoint(2,16.51347,1.072913);
   gre->SetPointError(2,0.00999,0.0007225977);
   gre->SetPoint(3,13.45653,1.022732);
   gre->SetPointError(3,0.00999,0.0006995811);
   gre->SetPoint(4,11.50694,0.984702);
   gre->SetPointError(4,0.00998,0.0007034253);
   gre->SetPoint(5,10.07952,0.9571498);
   gre->SetPointError(5,0.009959999,0.000738936);
   gre->SetPoint(6,8.447464,0.9204525);
   gre->SetPointError(6,0,0.0005656528);
   gre->SetPoint(7,6.724329,0.8761413);
   gre->SetPointError(7,0,0.000605392);
   gre->SetPoint(8,5.397827,0.832285);
   gre->SetPointError(8,0,0.0006363582);
   gre->SetPoint(9,3.896809,0.7758812);
   gre->SetPointError(9,0,0.0005161854);
   gre->SetPoint(10,2.261159,0.6699754);
   gre->SetPointError(10,0,0.0004829965);
   outl.Add(gre);
   
   TH1F *Graph_MeanPt_ResultsforProtonSum_stat56 = new TH1F("Graph_MeanPt_ResultsforProtonSum_stat56","Graph",100,2.035043,27.69973);
   Graph_MeanPt_ResultsforProtonSum_stat56->SetMinimum(0.6185131);
   Graph_MeanPt_ResultsforProtonSum_stat56->SetMaximum(1.230264);
   Graph_MeanPt_ResultsforProtonSum_stat56->SetDirectory(0);
   Graph_MeanPt_ResultsforProtonSum_stat56->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_MeanPt_ResultsforProtonSum_stat56->SetLineColor(ci);
   Graph_MeanPt_ResultsforProtonSum_stat56->GetXaxis()->SetLabelFont(42);
   Graph_MeanPt_ResultsforProtonSum_stat56->GetXaxis()->SetLabelOffset(0);
   Graph_MeanPt_ResultsforProtonSum_stat56->GetXaxis()->SetLabelSize(0.05);
   Graph_MeanPt_ResultsforProtonSum_stat56->GetXaxis()->SetTitleSize(0.06);
   Graph_MeanPt_ResultsforProtonSum_stat56->GetXaxis()->SetTitleOffset(1.08);
   Graph_MeanPt_ResultsforProtonSum_stat56->GetXaxis()->SetTitleFont(42);
   Graph_MeanPt_ResultsforProtonSum_stat56->GetYaxis()->SetLabelFont(42);
   Graph_MeanPt_ResultsforProtonSum_stat56->GetYaxis()->SetLabelOffset(0.01);
   Graph_MeanPt_ResultsforProtonSum_stat56->GetYaxis()->SetLabelSize(0.05);
   Graph_MeanPt_ResultsforProtonSum_stat56->GetYaxis()->SetTitleSize(0.06);
   Graph_MeanPt_ResultsforProtonSum_stat56->GetYaxis()->SetTitleOffset(1.3);
   Graph_MeanPt_ResultsforProtonSum_stat56->GetYaxis()->SetTitleFont(42);
   Graph_MeanPt_ResultsforProtonSum_stat56->GetZaxis()->SetLabelFont(42);
   Graph_MeanPt_ResultsforProtonSum_stat56->GetZaxis()->SetLabelSize(0.05);
   Graph_MeanPt_ResultsforProtonSum_stat56->GetZaxis()->SetTitleSize(0.06);
   Graph_MeanPt_ResultsforProtonSum_stat56->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_MeanPt_ResultsforProtonSum_stat56);
   
   gre->Draw("samepe1");
   
   gre = new TGraphErrors(11);
   gre->SetName("MeanPt_ResultsforProtonSum_sys");
   gre->SetTitle("Graph");
   gre->SetFillColor(2);
   gre->SetFillStyle(0);
   gre->SetLineColor(2);

   ci = TColor::GetColor("#cc0000");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(29);
   gre->SetMarkerSize(1.5);
   gre->SetPoint(0,25.30085,1.175839);
   gre->SetPointError(0,0.7590256,0.02487067);
   gre->SetPoint(1,20.84913,1.12983);
   gre->SetPointError(1,0.6254739,0.02490211);
   gre->SetPoint(2,16.51347,1.072913);
   gre->SetPointError(2,0.4954042,0.02466207);
   gre->SetPoint(3,13.45653,1.022732);
   gre->SetPointError(3,0.4036959,0.02518005);
   gre->SetPoint(4,11.50694,0.984702);
   gre->SetPointError(4,0.3452082,0.02683991);
   gre->SetPoint(5,10.07952,0.9571498);
   gre->SetPointError(5,0.3023856,0.02720478);
   gre->SetPoint(6,8.447464,0.9204525);
   gre->SetPointError(6,0.2534239,0.0278192);
   gre->SetPoint(7,6.724329,0.8761413);
   gre->SetPointError(7,0.2017299,0.02925585);
   gre->SetPoint(8,5.397827,0.832285);
   gre->SetPointError(8,0.1619348,0.0309525);
   gre->SetPoint(9,3.896809,0.7758812);
   gre->SetPointError(9,0.1169043,0.03264043);
   gre->SetPoint(10,2.261159,0.6699754);
   gre->SetPointError(10,0.06783476,0.03802097);
   outl.Add(gre);
   
   TH1F *Graph_MeanPt_ResultsforProtonSum_sys57 = new TH1F("Graph_MeanPt_ResultsforProtonSum_sys57","Graph",100,1.973992,28.44653);
   Graph_MeanPt_ResultsforProtonSum_sys57->SetMinimum(0.5750789);
   Graph_MeanPt_ResultsforProtonSum_sys57->SetMaximum(1.257585);
   Graph_MeanPt_ResultsforProtonSum_sys57->SetDirectory(0);
   Graph_MeanPt_ResultsforProtonSum_sys57->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_MeanPt_ResultsforProtonSum_sys57->SetLineColor(ci);
   Graph_MeanPt_ResultsforProtonSum_sys57->GetXaxis()->SetLabelFont(42);
   Graph_MeanPt_ResultsforProtonSum_sys57->GetXaxis()->SetLabelOffset(0);
   Graph_MeanPt_ResultsforProtonSum_sys57->GetXaxis()->SetLabelSize(0.05);
   Graph_MeanPt_ResultsforProtonSum_sys57->GetXaxis()->SetTitleSize(0.06);
   Graph_MeanPt_ResultsforProtonSum_sys57->GetXaxis()->SetTitleOffset(1.08);
   Graph_MeanPt_ResultsforProtonSum_sys57->GetXaxis()->SetTitleFont(42);
   Graph_MeanPt_ResultsforProtonSum_sys57->GetYaxis()->SetLabelFont(42);
   Graph_MeanPt_ResultsforProtonSum_sys57->GetYaxis()->SetLabelOffset(0.01);
   Graph_MeanPt_ResultsforProtonSum_sys57->GetYaxis()->SetLabelSize(0.05);
   Graph_MeanPt_ResultsforProtonSum_sys57->GetYaxis()->SetTitleSize(0.06);
   Graph_MeanPt_ResultsforProtonSum_sys57->GetYaxis()->SetTitleOffset(1.3);
   Graph_MeanPt_ResultsforProtonSum_sys57->GetYaxis()->SetTitleFont(42);
   Graph_MeanPt_ResultsforProtonSum_sys57->GetZaxis()->SetLabelFont(42);
   Graph_MeanPt_ResultsforProtonSum_sys57->GetZaxis()->SetLabelSize(0.05);
   Graph_MeanPt_ResultsforProtonSum_sys57->GetZaxis()->SetTitleSize(0.06);
   Graph_MeanPt_ResultsforProtonSum_sys57->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_MeanPt_ResultsforProtonSum_sys57);
   
   gre->Draw("samepe2");
   
   gre = new TGraphErrors(11);
   gre->SetName("MeanPt_ResultsforProtonSum_sys");
   gre->SetTitle("Graph");
   gre->SetFillColor(2);
   gre->SetFillStyle(0);
   gre->SetLineColor(2);

   ci = TColor::GetColor("#cc0000");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(29);
   gre->SetMarkerSize(1.5);
   gre->SetPoint(0,25.30085,1.175839);
   gre->SetPointError(0,0.7590256,0.02487067);
   gre->SetPoint(1,20.84913,1.12983);
   gre->SetPointError(1,0.6254739,0.02490211);
   gre->SetPoint(2,16.51347,1.072913);
   gre->SetPointError(2,0.4954042,0.02466207);
   gre->SetPoint(3,13.45653,1.022732);
   gre->SetPointError(3,0.4036959,0.02518005);
   gre->SetPoint(4,11.50694,0.984702);
   gre->SetPointError(4,0.3452082,0.02683991);
   gre->SetPoint(5,10.07952,0.9571498);
   gre->SetPointError(5,0.3023856,0.02720478);
   gre->SetPoint(6,8.447464,0.9204525);
   gre->SetPointError(6,0.2534239,0.0278192);
   gre->SetPoint(7,6.724329,0.8761413);
   gre->SetPointError(7,0.2017299,0.02925585);
   gre->SetPoint(8,5.397827,0.832285);
   gre->SetPointError(8,0.1619348,0.0309525);
   gre->SetPoint(9,3.896809,0.7758812);
   gre->SetPointError(9,0.1169043,0.03264043);
   gre->SetPoint(10,2.261159,0.6699754);
   gre->SetPointError(10,0.06783476,0.03802097);
   outl.Add(gre);
   
   TH1F *Graph_MeanPt_ResultsforProtonSum_sys58 = new TH1F("Graph_MeanPt_ResultsforProtonSum_sys58","Graph",100,1.973992,28.44653);
   Graph_MeanPt_ResultsforProtonSum_sys58->SetMinimum(0.5750789);
   Graph_MeanPt_ResultsforProtonSum_sys58->SetMaximum(1.257585);
   Graph_MeanPt_ResultsforProtonSum_sys58->SetDirectory(0);
   Graph_MeanPt_ResultsforProtonSum_sys58->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_MeanPt_ResultsforProtonSum_sys58->SetLineColor(ci);
   Graph_MeanPt_ResultsforProtonSum_sys58->GetXaxis()->SetLabelFont(42);
   Graph_MeanPt_ResultsforProtonSum_sys58->GetXaxis()->SetLabelOffset(0);
   Graph_MeanPt_ResultsforProtonSum_sys58->GetXaxis()->SetLabelSize(0.05);
   Graph_MeanPt_ResultsforProtonSum_sys58->GetXaxis()->SetTitleSize(0.06);
   Graph_MeanPt_ResultsforProtonSum_sys58->GetXaxis()->SetTitleOffset(1.08);
   Graph_MeanPt_ResultsforProtonSum_sys58->GetXaxis()->SetTitleFont(42);
   Graph_MeanPt_ResultsforProtonSum_sys58->GetYaxis()->SetLabelFont(42);
   Graph_MeanPt_ResultsforProtonSum_sys58->GetYaxis()->SetLabelOffset(0.01);
   Graph_MeanPt_ResultsforProtonSum_sys58->GetYaxis()->SetLabelSize(0.05);
   Graph_MeanPt_ResultsforProtonSum_sys58->GetYaxis()->SetTitleSize(0.06);
   Graph_MeanPt_ResultsforProtonSum_sys58->GetYaxis()->SetTitleOffset(1.3);
   Graph_MeanPt_ResultsforProtonSum_sys58->GetYaxis()->SetTitleFont(42);
   Graph_MeanPt_ResultsforProtonSum_sys58->GetZaxis()->SetLabelFont(42);
   Graph_MeanPt_ResultsforProtonSum_sys58->GetZaxis()->SetLabelSize(0.05);
   Graph_MeanPt_ResultsforProtonSum_sys58->GetZaxis()->SetTitleSize(0.06);
   Graph_MeanPt_ResultsforProtonSum_sys58->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_MeanPt_ResultsforProtonSum_sys58);
   
   gre->Draw("samepe0x0");
   
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(7);
   grae->SetName("HepData/8420/d20x1y1");
   grae->SetTitle("HepData/8420/d20x1y1");

   ci = TColor::GetColor("#66ff00");
   grae->SetFillColor(ci);
   grae->SetFillStyle(0);

   ci = TColor::GetColor("#66ff00");
   grae->SetLineColor(ci);

   ci = TColor::GetColor("#66ff00");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(26);
   grae->SetMarkerSize(1.5);
   grae->SetPoint(0,45,0.9366);
   grae->SetPointError(0,1,1,0.1003911,0.1003911);
   grae->SetPoint(1,36.2,0.9177);
   grae->SetPointError(1,0.8,0.8,0.08255247,0.08255247);
   grae->SetPoint(2,30.5,0.901);
   grae->SetPointError(2,0.7,0.7,0.07798551,0.07798551);
   grae->SetPoint(3,23.2,0.8764);
   grae->SetPointError(3,0.5,0.5,0.07384876,0.07384876);
   grae->SetPoint(4,16.1,0.8317);
   grae->SetPointError(4,0.4,0.4,0.0667048,0.0667048);
   grae->SetPoint(5,9.8,0.7722);
   grae->SetPointError(5,0.2,0.2,0.05592218,0.05592218);
   grae->SetPoint(6,4.4,0.6809);
   grae->SetPointError(6,0.1,0.1,0.0396207,0.0396207);
   outl.Add(grae);
   
   TH1F *Graph_HepData8420d20x1y11 = new TH1F("Graph_HepData/8420/d20x1y11","/HepData/8420/d20x1y1",100,0.13,50.17);
   Graph_HepData8420d20x1y11->SetMinimum(0.6017081);
   Graph_HepData8420d20x1y11->SetMaximum(1.076562);
   Graph_HepData8420d20x1y11->SetDirectory(0);
   Graph_HepData8420d20x1y11->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_HepData8420d20x1y11->SetLineColor(ci);
   Graph_HepData8420d20x1y11->GetXaxis()->SetLabelFont(42);
   Graph_HepData8420d20x1y11->GetXaxis()->SetLabelOffset(0);
   Graph_HepData8420d20x1y11->GetXaxis()->SetLabelSize(0.05);
   Graph_HepData8420d20x1y11->GetXaxis()->SetTitleSize(0.06);
   Graph_HepData8420d20x1y11->GetXaxis()->SetTitleOffset(1.08);
   Graph_HepData8420d20x1y11->GetXaxis()->SetTitleFont(42);
   Graph_HepData8420d20x1y11->GetYaxis()->SetLabelFont(42);
   Graph_HepData8420d20x1y11->GetYaxis()->SetLabelOffset(0.01);
   Graph_HepData8420d20x1y11->GetYaxis()->SetLabelSize(0.05);
   Graph_HepData8420d20x1y11->GetYaxis()->SetTitleSize(0.06);
   Graph_HepData8420d20x1y11->GetYaxis()->SetTitleOffset(1.3);
   Graph_HepData8420d20x1y11->GetYaxis()->SetTitleFont(42);
   Graph_HepData8420d20x1y11->GetZaxis()->SetLabelFont(42);
   Graph_HepData8420d20x1y11->GetZaxis()->SetLabelSize(0.05);
   Graph_HepData8420d20x1y11->GetZaxis()->SetTitleSize(0.06);
   Graph_HepData8420d20x1y11->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_HepData8420d20x1y11);
   
   grae->Draw("samepe2");
   
   grae = new TGraphAsymmErrors(7);
   grae->SetName("HepData/8420/d21x1y1");
   grae->SetTitle("HepData/8420/d21x1y1");

   ci = TColor::GetColor("#00ffff");
   grae->SetFillColor(ci);
   grae->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   grae->SetLineColor(ci);

   ci = TColor::GetColor("#00ffff");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(22);
   grae->SetMarkerSize(1.5);
   grae->SetPoint(0,45,0.5453);
   grae->SetPointError(0,1,1,0.01764313,0.01764313);
   grae->SetPoint(1,36.2,0.5375);
   grae->SetPointError(1,0.8,0.8,0.01693812,0.01693812);
   grae->SetPoint(2,30.5,0.5293);
   grae->SetPointError(2,0.7,0.7,0.01666073,0.01666073);
   grae->SetPoint(3,23.2,0.5142);
   grae->SetPointError(3,0.5,0.5,0.01550774,0.01550774);
   grae->SetPoint(4,16.1,0.4944);
   grae->SetPointError(4,0.4,0.4,0.01476787,0.01476787);
   grae->SetPoint(5,9.8,0.4705);
   grae->SetPointError(5,0.2,0.2,0.01379855,0.01379855);
   grae->SetPoint(6,4.4,0.4336);
   grae->SetPointError(6,0.1,0.1,0.01155422,0.01155422);
   outl.Add(grae);
   
   TH1F *Graph_HepData8420d21x1y12 = new TH1F("Graph_HepData8420d21x1y12","HepData/8420/d21x1y1",100,0.13,50.17);
   Graph_HepData8420d21x1y12->SetMinimum(0.407956);
   Graph_HepData8420d21x1y12->SetMaximum(0.5770329);
   Graph_HepData8420d21x1y12->SetDirectory(0);
   Graph_HepData8420d21x1y12->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_HepData8420d21x1y12->SetLineColor(ci);
   Graph_HepData8420d21x1y12->GetXaxis()->SetLabelFont(42);
   Graph_HepData8420d21x1y12->GetXaxis()->SetLabelOffset(0);
   Graph_HepData8420d21x1y12->GetXaxis()->SetLabelSize(0.05);
   Graph_HepData8420d21x1y12->GetXaxis()->SetTitleSize(0.06);
   Graph_HepData8420d21x1y12->GetXaxis()->SetTitleOffset(1.08);
   Graph_HepData8420d21x1y12->GetXaxis()->SetTitleFont(42);
   Graph_HepData8420d21x1y12->GetYaxis()->SetLabelFont(42);
   Graph_HepData8420d21x1y12->GetYaxis()->SetLabelOffset(0.01);
   Graph_HepData8420d21x1y12->GetYaxis()->SetLabelSize(0.05);
   Graph_HepData8420d21x1y12->GetYaxis()->SetTitleSize(0.06);
   Graph_HepData8420d21x1y12->GetYaxis()->SetTitleOffset(1.3);
   Graph_HepData8420d21x1y12->GetYaxis()->SetTitleFont(42);
   Graph_HepData8420d21x1y12->GetZaxis()->SetLabelFont(42);
   Graph_HepData8420d21x1y12->GetZaxis()->SetLabelSize(0.05);
   Graph_HepData8420d21x1y12->GetZaxis()->SetTitleSize(0.06);
   Graph_HepData8420d21x1y12->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_HepData8420d21x1y12);
   
   grae->Draw("samepe2");
   
   grae = new TGraphAsymmErrors(7);
   grae->SetName("HepData/8420/d18x1y1");
   grae->SetTitle("HepData/8420/d18x1y1");

   ci = TColor::GetColor("#ff6600");
   grae->SetFillColor(ci);
   grae->SetFillStyle(0);

   ci = TColor::GetColor("#ff6600");
   grae->SetLineColor(ci);

   ci = TColor::GetColor("#ff6600");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(23);
   grae->SetMarkerSize(1.5);
   grae->SetPoint(0,45,1.248);
   grae->SetPointError(0,1,1,0.04759202,0.04759202);
   grae->SetPoint(1,36.2,1.223);
   grae->SetPointError(1,0.8,0.8,0.05470832,0.05470832);
   grae->SetPoint(2,30.5,1.186);
   grae->SetPointError(2,0.7,0.7,0.05706137,0.05706137);
   grae->SetPoint(3,23.2,1.132);
   grae->SetPointError(3,0.5,0.5,0.04627094,0.04627094);
   grae->SetPoint(4,16.1,1.053);
   grae->SetPointError(4,0.4,0.4,0.038,0.038);
   grae->SetPoint(5,9.8,0.9607);
   grae->SetPointError(5,0.2,0.2,0.03295709,0.03295709);
   grae->SetPoint(6,4.4,0.8208);
   grae->SetPointError(6,0.1,0.1,0.02663475,0.02663475);
   outl.Add(grae);
   
   TH1F *Graph_HepData8420d18x1y13 = new TH1F("Graph_HepData/8420/d18x1y13","/HepData/8420/d18x1y1",100,0.13,50.17);
   Graph_HepData8420d18x1y13->SetMinimum(0.7440226);
   Graph_HepData8420d18x1y13->SetMaximum(1.345735);
   Graph_HepData8420d18x1y13->SetDirectory(0);
   Graph_HepData8420d18x1y13->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_HepData8420d18x1y13->SetLineColor(ci);
   Graph_HepData8420d18x1y13->GetXaxis()->SetLabelFont(42);
   Graph_HepData8420d18x1y13->GetXaxis()->SetLabelOffset(0);
   Graph_HepData8420d18x1y13->GetXaxis()->SetLabelSize(0.05);
   Graph_HepData8420d18x1y13->GetXaxis()->SetTitleSize(0.06);
   Graph_HepData8420d18x1y13->GetXaxis()->SetTitleOffset(1.08);
   Graph_HepData8420d18x1y13->GetXaxis()->SetTitleFont(42);
   Graph_HepData8420d18x1y13->GetYaxis()->SetLabelFont(42);
   Graph_HepData8420d18x1y13->GetYaxis()->SetLabelOffset(0.01);
   Graph_HepData8420d18x1y13->GetYaxis()->SetLabelSize(0.05);
   Graph_HepData8420d18x1y13->GetYaxis()->SetTitleSize(0.06);
   Graph_HepData8420d18x1y13->GetYaxis()->SetTitleOffset(1.3);
   Graph_HepData8420d18x1y13->GetYaxis()->SetTitleFont(42);
   Graph_HepData8420d18x1y13->GetZaxis()->SetLabelFont(42);
   Graph_HepData8420d18x1y13->GetZaxis()->SetLabelSize(0.05);
   Graph_HepData8420d18x1y13->GetZaxis()->SetTitleSize(0.06);
   Graph_HepData8420d18x1y13->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_HepData8420d18x1y13);
   
   grae->Draw("samepe2");
   
   grae = new TGraphAsymmErrors(10);
   grae->SetName("HepData8463d32x1y1");
   grae->SetTitle("HepData8463d32x1y1");

   ci = TColor::GetColor("#000066");
   grae->SetFillColor(ci);
   grae->SetFillStyle(0);

   ci = TColor::GetColor("#000066");
   grae->SetLineColor(ci);

   ci = TColor::GetColor("#000066");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(27);
   grae->SetMarkerSize(1.5);
   grae->SetPoint(0,1601,0.517);
   grae->SetPointError(0,60,60,0.019,0.019);
   grae->SetPoint(1,1294,0.517);
   grae->SetPointError(1,49,49,0.018,0.018);
   grae->SetPoint(2,966,0.517);
   grae->SetPointError(2,37,37,0.017,0.017);
   grae->SetPoint(3,649,0.512);
   grae->SetPointError(3,23,23,0.017,0.017);
   grae->SetPoint(4,426,0.504);
   grae->SetPointError(4,15,15,0.017,0.017);
   grae->SetPoint(5,261,0.492);
   grae->SetPointError(5,9,9,0.017,0.017);
   grae->SetPoint(6,149,0.478);
   grae->SetPointError(6,6,6,0.017,0.017);
   grae->SetPoint(7,76,0.465);
   grae->SetPointError(7,4,4,0.017,0.017);
   grae->SetPoint(8,35,0.452);
   grae->SetPointError(8,2,2,0.017,0.017);
   grae->SetPoint(9,13.4,0.434);
   grae->SetPointError(9,1.2,1.6,0.014,0.014);
   outl.Add(grae);
   
   TH1F *Graph_HepData8463d32x1y14 = new TH1F("Graph_HepData8463d32x1y14","/HepData/8463/d32x1y1",100,10.98,1825.88);
   Graph_HepData8463d32x1y14->SetMinimum(0.4084);
   Graph_HepData8463d32x1y14->SetMaximum(0.5476);
   Graph_HepData8463d32x1y14->SetDirectory(0);
   Graph_HepData8463d32x1y14->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_HepData8463d32x1y14->SetLineColor(ci);
   Graph_HepData8463d32x1y14->GetXaxis()->SetLabelFont(42);
   Graph_HepData8463d32x1y14->GetXaxis()->SetLabelOffset(0);
   Graph_HepData8463d32x1y14->GetXaxis()->SetLabelSize(0.05);
   Graph_HepData8463d32x1y14->GetXaxis()->SetTitleSize(0.06);
   Graph_HepData8463d32x1y14->GetXaxis()->SetTitleOffset(1.08);
   Graph_HepData8463d32x1y14->GetXaxis()->SetTitleFont(42);
   Graph_HepData8463d32x1y14->GetYaxis()->SetLabelFont(42);
   Graph_HepData8463d32x1y14->GetYaxis()->SetLabelOffset(0.01);
   Graph_HepData8463d32x1y14->GetYaxis()->SetLabelSize(0.05);
   Graph_HepData8463d32x1y14->GetYaxis()->SetTitleSize(0.06);
   Graph_HepData8463d32x1y14->GetYaxis()->SetTitleOffset(1.3);
   Graph_HepData8463d32x1y14->GetYaxis()->SetTitleFont(42);
   Graph_HepData8463d32x1y14->GetZaxis()->SetLabelFont(42);
   Graph_HepData8463d32x1y14->GetZaxis()->SetLabelSize(0.05);
   Graph_HepData8463d32x1y14->GetZaxis()->SetTitleSize(0.06);
   Graph_HepData8463d32x1y14->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_HepData8463d32x1y14);
   
   grae->Draw("samepe2");
   
   grae = new TGraphAsymmErrors(10);
   grae->SetName("HepData8463d32x1y3");
   grae->SetTitle("HepData8463d32x1y3");

   ci = TColor::GetColor("#66cc66");
   grae->SetFillColor(ci);
   grae->SetFillStyle(0);

   ci = TColor::GetColor("#66cc66");
   grae->SetLineColor(ci);

   ci = TColor::GetColor("#66cc66");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(33);
   grae->SetMarkerSize(1.5);
   grae->SetPoint(0,1601,0.876);
   grae->SetPointError(0,60,60,0.026,0.026);
   grae->SetPoint(1,1294,0.872);
   grae->SetPointError(1,49,49,0.025,0.025);
   grae->SetPoint(2,966,0.871);
   grae->SetPointError(2,37,37,0.027,0.027);
   grae->SetPoint(3,649,0.86);
   grae->SetPointError(3,23,23,0.029,0.029);
   grae->SetPoint(4,426,0.842);
   grae->SetPointError(4,15,15,0.032,0.032);
   grae->SetPoint(5,261,0.818);
   grae->SetPointError(5,9,9,0.03,0.03);
   grae->SetPoint(6,149,0.79);
   grae->SetPointError(6,6,6,0.028,0.028);
   grae->SetPoint(7,76,0.76);
   grae->SetPointError(7,4,4,0.028,0.028);
   grae->SetPoint(8,35,0.737);
   grae->SetPointError(8,2,2,0.027,0.027);
   grae->SetPoint(9,13.4,0.711);
   grae->SetPointError(9,1.2,1.6,0.027,0.027);
   outl.Add(grae);
   
   TH1F *Graph_HepData8463d32x1y35 = new TH1F("Graph_HepData8463d32x1y35","/HepData/8463/d32x1y3",100,10.98,1825.88);
   Graph_HepData8463d32x1y35->SetMinimum(0.6622);
   Graph_HepData8463d32x1y35->SetMaximum(0.9238);
   Graph_HepData8463d32x1y35->SetDirectory(0);
   Graph_HepData8463d32x1y35->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_HepData8463d32x1y35->SetLineColor(ci);
   Graph_HepData8463d32x1y35->GetXaxis()->SetLabelFont(42);
   Graph_HepData8463d32x1y35->GetXaxis()->SetLabelOffset(0);
   Graph_HepData8463d32x1y35->GetXaxis()->SetLabelSize(0.05);
   Graph_HepData8463d32x1y35->GetXaxis()->SetTitleSize(0.06);
   Graph_HepData8463d32x1y35->GetXaxis()->SetTitleOffset(1.08);
   Graph_HepData8463d32x1y35->GetXaxis()->SetTitleFont(42);
   Graph_HepData8463d32x1y35->GetYaxis()->SetLabelFont(42);
   Graph_HepData8463d32x1y35->GetYaxis()->SetLabelOffset(0.01);
   Graph_HepData8463d32x1y35->GetYaxis()->SetLabelSize(0.05);
   Graph_HepData8463d32x1y35->GetYaxis()->SetTitleSize(0.06);
   Graph_HepData8463d32x1y35->GetYaxis()->SetTitleOffset(1.3);
   Graph_HepData8463d32x1y35->GetYaxis()->SetTitleFont(42);
   Graph_HepData8463d32x1y35->GetZaxis()->SetLabelFont(42);
   Graph_HepData8463d32x1y35->GetZaxis()->SetLabelSize(0.05);
   Graph_HepData8463d32x1y35->GetZaxis()->SetTitleSize(0.06);
   Graph_HepData8463d32x1y35->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_HepData8463d32x1y35);
   
   grae->Draw("samepe2");
   
   grae = new TGraphAsymmErrors(10);
   grae->SetName("HepData8463d32x1y5");
   grae->SetTitle("HepData8463d32x1y5");

   ci = TColor::GetColor("#ff3300");
   grae->SetFillColor(ci);
   grae->SetFillStyle(0);

   ci = TColor::GetColor("#ff3300");
   grae->SetLineColor(ci);

   ci = TColor::GetColor("#ff3300");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(34);
   grae->SetMarkerSize(1.5);
   grae->SetPoint(0,1601,1.333);
   grae->SetPointError(0,60,60,0.033,0.033);
   grae->SetPoint(1,1294,1.324);
   grae->SetPointError(1,49,49,0.033,0.033);
   grae->SetPoint(2,966,1.311);
   grae->SetPointError(2,37,37,0.034,0.034);
   grae->SetPoint(3,649,1.281);
   grae->SetPointError(3,23,23,0.033,0.033);
   grae->SetPoint(4,426,1.237);
   grae->SetPointError(4,15,15,0.032,0.032);
   grae->SetPoint(5,261,1.178);
   grae->SetPointError(5,9,9,0.03,0.03);
   grae->SetPoint(6,149,1.118);
   grae->SetPointError(6,6,6,0.028,0.028);
   grae->SetPoint(7,76,1.05);
   grae->SetPointError(7,4,4,0.027,0.027);
   grae->SetPoint(8,35,0.987);
   grae->SetPointError(8,2,2,0.025,0.025);
   grae->SetPoint(9,13.4,0.905);
   grae->SetPointError(9,1.2,1.6,0.026,0.026);
   outl.Add(grae);

   TH1F *Graph_HepData8463d32x1y56 = new TH1F("Graph_/HepData/8463/d32x1y56","/HepData/8463/d32x1y5",100,10.98,1825.88);
   Graph_HepData8463d32x1y56->SetMinimum(0.8303);
   Graph_HepData8463d32x1y56->SetMaximum(1.4147);
   Graph_HepData8463d32x1y56->SetDirectory(0);
   Graph_HepData8463d32x1y56->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_HepData8463d32x1y56->SetLineColor(ci);
   Graph_HepData8463d32x1y56->GetXaxis()->SetLabelFont(42);
   Graph_HepData8463d32x1y56->GetXaxis()->SetLabelOffset(0);
   Graph_HepData8463d32x1y56->GetXaxis()->SetLabelSize(0.05);
   Graph_HepData8463d32x1y56->GetXaxis()->SetTitleSize(0.06);
   Graph_HepData8463d32x1y56->GetXaxis()->SetTitleOffset(1.08);
   Graph_HepData8463d32x1y56->GetXaxis()->SetTitleFont(42);
   Graph_HepData8463d32x1y56->GetYaxis()->SetLabelFont(42);
   Graph_HepData8463d32x1y56->GetYaxis()->SetLabelOffset(0.01);
   Graph_HepData8463d32x1y56->GetYaxis()->SetLabelSize(0.05);
   Graph_HepData8463d32x1y56->GetYaxis()->SetTitleSize(0.06);
   Graph_HepData8463d32x1y56->GetYaxis()->SetTitleOffset(1.3);
   Graph_HepData8463d32x1y56->GetYaxis()->SetTitleFont(42);
   Graph_HepData8463d32x1y56->GetZaxis()->SetLabelFont(42);
   Graph_HepData8463d32x1y56->GetZaxis()->SetLabelSize(0.05);
   Graph_HepData8463d32x1y56->GetZaxis()->SetTitleSize(0.06);
   Graph_HepData8463d32x1y56->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_HepData8463d32x1y56);
   
   grae->Draw("samepe2");
   
   TLegend *leg = new TLegend(0.18,0.58,0.87,0.88,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.045);
   leg->SetLineColor(0);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   TLegendEntry *entry=leg->AddEntry("NULL","ALICE V0 Multiplicity Classes","h");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("NULL","pp","");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("NULL","p-Pb","");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("NULL","Pb-Pb","");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("NULL","#sqrt{#it{s}} = 7 TeV","");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("NULL","#sqrt{s_{NN}} = 5.02 TeV","");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("NULL","#sqrt{s_{NN}} = 2.76 TeV","");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("MeanPt_ResultsforPionSum_sys","#pi^{+} + #pi^{-}","pf");
   entry->SetFillColor(4);
   entry->SetLineColor(4);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#0000cc");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1.5);
   entry->SetTextFont(42);
   entry=leg->AddEntry("HepData/8420/d21x1y1","#pi^{+} + #pi^{-}","pf");

   ci = TColor::GetColor("#00ffff");
   entry->SetFillColor(ci);

   ci = TColor::GetColor("#00ffff");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#00ffff");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(22);
   entry->SetMarkerSize(1.5);
   entry->SetTextFont(42);
   entry=leg->AddEntry("HepData8463d32x1y1","#pi^{+}","pf");

   ci = TColor::GetColor("#000066");
   entry->SetFillColor(ci);

   ci = TColor::GetColor("#000066");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#000066");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(27);
   entry->SetMarkerSize(1.5);
   entry->SetTextFont(42);
   entry=leg->AddEntry("MeanPt_ResultsforKaonSum_sys","K^{+} + K^{-}","pf");

   ci = TColor::GetColor("#00cc00");
   entry->SetFillColor(ci);

   ci = TColor::GetColor("#00cc00");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#009900");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(24);
   entry->SetMarkerSize(1.5);
   entry->SetTextFont(42);
   entry=leg->AddEntry("HepData/8420/d20x1y1","K^{+} + K^{-}","pf");

   ci = TColor::GetColor("#66ff00");
   entry->SetFillColor(ci);

   ci = TColor::GetColor("#66ff00");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#66ff00");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(26);
   entry->SetMarkerSize(1.5);
   entry->SetTextFont(42);
   entry=leg->AddEntry("HepData8463d32x1y3","K^{+}","pf");

   ci = TColor::GetColor("#66cc66");
   entry->SetFillColor(ci);

   ci = TColor::GetColor("#66cc66");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#66cc66");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(33);
   entry->SetMarkerSize(1.5);
   entry->SetTextFont(42);
   entry=leg->AddEntry("MeanPt_ResultsforProtonSum_sys","p + #bar{p}","pf");
   entry->SetFillColor(2);
   entry->SetLineColor(2);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#cc0000");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(29);
   entry->SetMarkerSize(1.5);
   entry->SetTextFont(42);
   entry=leg->AddEntry("HepData/8420/d18x1y1","p + #bar{p}","pf");

   ci = TColor::GetColor("#ff6600");
   entry->SetFillColor(ci);

   ci = TColor::GetColor("#ff6600");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#ff6600");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(23);
   entry->SetMarkerSize(1.5);
   entry->SetTextFont(42);
   entry=leg->AddEntry("HepData8463d32x1y5","p","pf");

   ci = TColor::GetColor("#ff3300");
   entry->SetFillColor(ci);

   ci = TColor::GetColor("#ff3300");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#ff3300");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(34);
   entry->SetMarkerSize(1.5);
   entry->SetTextFont(42);
   leg->Draw();
   cMeanPt_V0M->Modified();
   cMeanPt_V0M->cd();
   cMeanPt_V0M->SetSelected(cMeanPt_V0M);

   fout.cd();
   outl.Write();
   fout.Write();
   fout.Close();
}
