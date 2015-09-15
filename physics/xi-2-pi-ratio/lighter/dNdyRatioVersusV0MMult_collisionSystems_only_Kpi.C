{
//=========Macro generated from canvas: cdNdyRatio_V0M/cdNdyRatio
//=========  (Tue Sep 15 15:18:29 2015) by ROOT version5.34/30
   TCanvas *cdNdyRatio_V0M = new TCanvas("cdNdyRatio_V0M", "cdNdyRatio",0,0,1000,700);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   cdNdyRatio_V0M->SetHighLightColor(2);
   cdNdyRatio_V0M->Range(-0.1228788,0.08,3.877121,0.2133333);
   cdNdyRatio_V0M->SetFillColor(10);
   cdNdyRatio_V0M->SetBorderMode(0);
   cdNdyRatio_V0M->SetBorderSize(2);
   cdNdyRatio_V0M->SetLogx();
   cdNdyRatio_V0M->SetTickx(1);
   cdNdyRatio_V0M->SetTicky(1);
   cdNdyRatio_V0M->SetLeftMargin(0.15);
   cdNdyRatio_V0M->SetBottomMargin(0.15);
   cdNdyRatio_V0M->SetFrameFillColor(0);
   cdNdyRatio_V0M->SetFrameBorderMode(0);
   cdNdyRatio_V0M->SetFrameFillColor(0);
   cdNdyRatio_V0M->SetFrameBorderMode(0);
   
   TH1F *hframe__7 = new TH1F("hframe__7","",1000,0,3000);
   hframe__7->SetMinimum(0.1);
   hframe__7->SetMaximum(0.2);
   hframe__7->SetDirectory(0);
   hframe__7->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#ff0000");
   hframe__7->SetLineColor(ci);
   hframe__7->GetXaxis()->SetTitle("#LTd#it{N}_{ch}/d#it{#eta}#GT_{|#it{#eta}| < 0.5}");
   hframe__7->GetXaxis()->SetRange(1,1000);
   hframe__7->GetXaxis()->SetMoreLogLabels();
   hframe__7->GetXaxis()->SetLabelFont(42);
   hframe__7->GetXaxis()->SetLabelOffset(0);
   hframe__7->GetXaxis()->SetLabelSize(0.05);
   hframe__7->GetXaxis()->SetTitleSize(0.06);
   hframe__7->GetXaxis()->SetTitleOffset(1.08);
   hframe__7->GetXaxis()->SetTitleFont(42);
   hframe__7->GetYaxis()->SetTitle("d#it{N}/d#it{y} Ratio");
   hframe__7->GetYaxis()->SetLabelFont(42);
   hframe__7->GetYaxis()->SetLabelOffset(0.01);
   hframe__7->GetYaxis()->SetLabelSize(0.05);
   hframe__7->GetYaxis()->SetTitleSize(0.06);
   hframe__7->GetYaxis()->SetTitleOffset(1.3);
   hframe__7->GetYaxis()->SetTitleFont(42);
   hframe__7->GetZaxis()->SetLabelFont(42);
   hframe__7->GetZaxis()->SetLabelSize(0.05);
   hframe__7->GetZaxis()->SetTitleSize(0.06);
   hframe__7->GetZaxis()->SetTitleFont(42);
   hframe__7->Draw(" ");
   
   TGraphErrors *gre = new TGraphErrors(11);
   gre->SetName("IntegratedRatiodNdy_Ktopi_stat");
   gre->SetTitle("Graph");

   ci = TColor::GetColor("#009900");
   gre->SetFillColor(ci);
   gre->SetFillStyle(0);

   ci = TColor::GetColor("#009900");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#009900");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.5);
   gre->SetPoint(0,25.30085,0.1368552);
   gre->SetPointError(0,0.0862803,0.0005024988);
   gre->SetPoint(1,20.84913,0.1361666);
   gre->SetPointError(1,0.02997,0.0003835382);
   gre->SetPoint(2,16.51347,0.1347734);
   gre->SetPointError(2,0.00999,0.0001414467);
   gre->SetPoint(3,13.45653,0.1329628);
   gre->SetPointError(3,0.00999,0.0001163203);
   gre->SetPoint(4,11.50694,0.1315399);
   gre->SetPointError(4,0.00998,0.0001196082);
   gre->SetPoint(5,10.07952,0.1305612);
   gre->SetPointError(5,0.009959999,0.0001231891);
   gre->SetPoint(6,8.447464,0.1288728);
   gre->SetPointError(6,0,9.531451e-05);
   gre->SetPoint(7,6.724329,0.1270872);
   gre->SetPointError(7,0,0.0001046058);
   gre->SetPoint(8,5.397827,0.1252544);
   gre->SetPointError(8,0,0.0001094317);
   gre->SetPoint(9,3.896809,0.1220302);
   gre->SetPointError(9,0,9.00697e-05);
   gre->SetPoint(10,2.261159,0.1156889);
   gre->SetPointError(10,0,8.785395e-05);
   
   TH1F *Graph_IntegratedRatiodNdy_Ktopi_stat37 = new TH1F("Graph_IntegratedRatiodNdy_Ktopi_stat37","Graph",100,2.035043,27.69973);
   Graph_IntegratedRatiodNdy_Ktopi_stat37->SetMinimum(0.1134253);
   Graph_IntegratedRatiodNdy_Ktopi_stat37->SetMaximum(0.1395334);
   Graph_IntegratedRatiodNdy_Ktopi_stat37->SetDirectory(0);
   Graph_IntegratedRatiodNdy_Ktopi_stat37->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_IntegratedRatiodNdy_Ktopi_stat37->SetLineColor(ci);
   Graph_IntegratedRatiodNdy_Ktopi_stat37->GetXaxis()->SetLabelFont(42);
   Graph_IntegratedRatiodNdy_Ktopi_stat37->GetXaxis()->SetLabelOffset(0);
   Graph_IntegratedRatiodNdy_Ktopi_stat37->GetXaxis()->SetLabelSize(0.05);
   Graph_IntegratedRatiodNdy_Ktopi_stat37->GetXaxis()->SetTitleSize(0.06);
   Graph_IntegratedRatiodNdy_Ktopi_stat37->GetXaxis()->SetTitleOffset(1.08);
   Graph_IntegratedRatiodNdy_Ktopi_stat37->GetXaxis()->SetTitleFont(42);
   Graph_IntegratedRatiodNdy_Ktopi_stat37->GetYaxis()->SetLabelFont(42);
   Graph_IntegratedRatiodNdy_Ktopi_stat37->GetYaxis()->SetLabelOffset(0.01);
   Graph_IntegratedRatiodNdy_Ktopi_stat37->GetYaxis()->SetLabelSize(0.05);
   Graph_IntegratedRatiodNdy_Ktopi_stat37->GetYaxis()->SetTitleSize(0.06);
   Graph_IntegratedRatiodNdy_Ktopi_stat37->GetYaxis()->SetTitleOffset(1.3);
   Graph_IntegratedRatiodNdy_Ktopi_stat37->GetYaxis()->SetTitleFont(42);
   Graph_IntegratedRatiodNdy_Ktopi_stat37->GetZaxis()->SetLabelFont(42);
   Graph_IntegratedRatiodNdy_Ktopi_stat37->GetZaxis()->SetLabelSize(0.05);
   Graph_IntegratedRatiodNdy_Ktopi_stat37->GetZaxis()->SetTitleSize(0.06);
   Graph_IntegratedRatiodNdy_Ktopi_stat37->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_IntegratedRatiodNdy_Ktopi_stat37);
   
   gre->Draw("pe1");
   
   gre = new TGraphErrors(11);
   gre->SetName("IntegratedRatiodNdy_Ktopi_sys");
   gre->SetTitle("Graph");

   ci = TColor::GetColor("#009900");
   gre->SetFillColor(ci);
   gre->SetFillStyle(0);

   ci = TColor::GetColor("#009900");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#009900");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.5);
   gre->SetPoint(0,25.30085,0.1368552);
   gre->SetPointError(0,0.7590256,0.01110297);
   gre->SetPoint(1,20.84913,0.1361666);
   gre->SetPointError(1,0.6254739,0.01044155);
   gre->SetPoint(2,16.51347,0.1347734);
   gre->SetPointError(2,0.4954042,0.01008689);
   gre->SetPoint(3,13.45653,0.1329628);
   gre->SetPointError(3,0.4036959,0.009820339);
   gre->SetPoint(4,11.50694,0.1315399);
   gre->SetPointError(4,0.3452082,0.009646104);
   gre->SetPoint(5,10.07952,0.1305612);
   gre->SetPointError(5,0.3023856,0.009520577);
   gre->SetPoint(6,8.447464,0.1288728);
   gre->SetPointError(6,0.2534239,0.009336047);
   gre->SetPoint(7,6.724329,0.1270872);
   gre->SetPointError(7,0.2017299,0.009146262);
   gre->SetPoint(8,5.397827,0.1252544);
   gre->SetPointError(8,0.1619348,0.009067329);
   gre->SetPoint(9,3.896809,0.1220302);
   gre->SetPointError(9,0.1169043,0.009779987);
   gre->SetPoint(10,2.261159,0.1156889);
   gre->SetPointError(10,0.06783476,0.01229891);
   
   TH1F *Graph_IntegratedRatiodNdy_Ktopi_sys38 = new TH1F("Graph_IntegratedRatiodNdy_Ktopi_sys38","Graph",100,1.973992,28.44653);
   Graph_IntegratedRatiodNdy_Ktopi_sys38->SetMinimum(0.09893312);
   Graph_IntegratedRatiodNdy_Ktopi_sys38->SetMaximum(0.152415);
   Graph_IntegratedRatiodNdy_Ktopi_sys38->SetDirectory(0);
   Graph_IntegratedRatiodNdy_Ktopi_sys38->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_IntegratedRatiodNdy_Ktopi_sys38->SetLineColor(ci);
   Graph_IntegratedRatiodNdy_Ktopi_sys38->GetXaxis()->SetLabelFont(42);
   Graph_IntegratedRatiodNdy_Ktopi_sys38->GetXaxis()->SetLabelOffset(0);
   Graph_IntegratedRatiodNdy_Ktopi_sys38->GetXaxis()->SetLabelSize(0.05);
   Graph_IntegratedRatiodNdy_Ktopi_sys38->GetXaxis()->SetTitleSize(0.06);
   Graph_IntegratedRatiodNdy_Ktopi_sys38->GetXaxis()->SetTitleOffset(1.08);
   Graph_IntegratedRatiodNdy_Ktopi_sys38->GetXaxis()->SetTitleFont(42);
   Graph_IntegratedRatiodNdy_Ktopi_sys38->GetYaxis()->SetLabelFont(42);
   Graph_IntegratedRatiodNdy_Ktopi_sys38->GetYaxis()->SetLabelOffset(0.01);
   Graph_IntegratedRatiodNdy_Ktopi_sys38->GetYaxis()->SetLabelSize(0.05);
   Graph_IntegratedRatiodNdy_Ktopi_sys38->GetYaxis()->SetTitleSize(0.06);
   Graph_IntegratedRatiodNdy_Ktopi_sys38->GetYaxis()->SetTitleOffset(1.3);
   Graph_IntegratedRatiodNdy_Ktopi_sys38->GetYaxis()->SetTitleFont(42);
   Graph_IntegratedRatiodNdy_Ktopi_sys38->GetZaxis()->SetLabelFont(42);
   Graph_IntegratedRatiodNdy_Ktopi_sys38->GetZaxis()->SetLabelSize(0.05);
   Graph_IntegratedRatiodNdy_Ktopi_sys38->GetZaxis()->SetTitleSize(0.06);
   Graph_IntegratedRatiodNdy_Ktopi_sys38->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_IntegratedRatiodNdy_Ktopi_sys38);
   
   gre->Draw("pe2");
   
   gre = new TGraphErrors(11);
   gre->SetName("IntegratedRatiodNdy_Ktopi_sys");
   gre->SetTitle("Graph");

   ci = TColor::GetColor("#009900");
   gre->SetFillColor(ci);
   gre->SetFillStyle(0);

   ci = TColor::GetColor("#009900");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#009900");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.5);
   gre->SetPoint(0,25.30085,0.1368552);
   gre->SetPointError(0,0.7590256,0.01110297);
   gre->SetPoint(1,20.84913,0.1361666);
   gre->SetPointError(1,0.6254739,0.01044155);
   gre->SetPoint(2,16.51347,0.1347734);
   gre->SetPointError(2,0.4954042,0.01008689);
   gre->SetPoint(3,13.45653,0.1329628);
   gre->SetPointError(3,0.4036959,0.009820339);
   gre->SetPoint(4,11.50694,0.1315399);
   gre->SetPointError(4,0.3452082,0.009646104);
   gre->SetPoint(5,10.07952,0.1305612);
   gre->SetPointError(5,0.3023856,0.009520577);
   gre->SetPoint(6,8.447464,0.1288728);
   gre->SetPointError(6,0.2534239,0.009336047);
   gre->SetPoint(7,6.724329,0.1270872);
   gre->SetPointError(7,0.2017299,0.009146262);
   gre->SetPoint(8,5.397827,0.1252544);
   gre->SetPointError(8,0.1619348,0.009067329);
   gre->SetPoint(9,3.896809,0.1220302);
   gre->SetPointError(9,0.1169043,0.009779987);
   gre->SetPoint(10,2.261159,0.1156889);
   gre->SetPointError(10,0.06783476,0.01229891);
   
   TH1F *Graph_IntegratedRatiodNdy_Ktopi_sys39 = new TH1F("Graph_IntegratedRatiodNdy_Ktopi_sys39","Graph",100,1.973992,28.44653);
   Graph_IntegratedRatiodNdy_Ktopi_sys39->SetMinimum(0.09893312);
   Graph_IntegratedRatiodNdy_Ktopi_sys39->SetMaximum(0.152415);
   Graph_IntegratedRatiodNdy_Ktopi_sys39->SetDirectory(0);
   Graph_IntegratedRatiodNdy_Ktopi_sys39->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_IntegratedRatiodNdy_Ktopi_sys39->SetLineColor(ci);
   Graph_IntegratedRatiodNdy_Ktopi_sys39->GetXaxis()->SetLabelFont(42);
   Graph_IntegratedRatiodNdy_Ktopi_sys39->GetXaxis()->SetLabelOffset(0);
   Graph_IntegratedRatiodNdy_Ktopi_sys39->GetXaxis()->SetLabelSize(0.05);
   Graph_IntegratedRatiodNdy_Ktopi_sys39->GetXaxis()->SetTitleSize(0.06);
   Graph_IntegratedRatiodNdy_Ktopi_sys39->GetXaxis()->SetTitleOffset(1.08);
   Graph_IntegratedRatiodNdy_Ktopi_sys39->GetXaxis()->SetTitleFont(42);
   Graph_IntegratedRatiodNdy_Ktopi_sys39->GetYaxis()->SetLabelFont(42);
   Graph_IntegratedRatiodNdy_Ktopi_sys39->GetYaxis()->SetLabelOffset(0.01);
   Graph_IntegratedRatiodNdy_Ktopi_sys39->GetYaxis()->SetLabelSize(0.05);
   Graph_IntegratedRatiodNdy_Ktopi_sys39->GetYaxis()->SetTitleSize(0.06);
   Graph_IntegratedRatiodNdy_Ktopi_sys39->GetYaxis()->SetTitleOffset(1.3);
   Graph_IntegratedRatiodNdy_Ktopi_sys39->GetYaxis()->SetTitleFont(42);
   Graph_IntegratedRatiodNdy_Ktopi_sys39->GetZaxis()->SetLabelFont(42);
   Graph_IntegratedRatiodNdy_Ktopi_sys39->GetZaxis()->SetLabelSize(0.05);
   Graph_IntegratedRatiodNdy_Ktopi_sys39->GetZaxis()->SetTitleSize(0.06);
   Graph_IntegratedRatiodNdy_Ktopi_sys39->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_IntegratedRatiodNdy_Ktopi_sys39);
   
   gre->Draw("pe0x0");
   
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(7);
   grae->SetName("HepData8420d22x1y155");
   grae->SetTitle("HepData8420d22x1y155");

   ci = TColor::GetColor("#0000ff");
   grae->SetFillColor(ci);
   grae->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   grae->SetLineColor(ci);

   ci = TColor::GetColor("#0000ff");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(33);
   grae->SetMarkerSize(1.5);
   grae->SetPoint(0,45,0.143);
   grae->SetPointError(0,1,1,0.01270512,0.01270512);
   grae->SetPoint(1,36.2,0.1401);
   grae->SetPointError(1,0.8,0.8,0.01162841,0.01162841);
   grae->SetPoint(2,30.5,0.1386);
   grae->SetPointError(2,0.7,0.7,0.01114451,0.01114451);
   grae->SetPoint(3,23.2,0.1358);
   grae->SetPointError(3,0.5,0.5,0.01054941,0.01054941);
   grae->SetPoint(4,16.1,0.1325);
   grae->SetPointError(4,0.4,0.4,0.009788258,0.009788258);
   grae->SetPoint(5,9.8,0.129);
   grae->SetPointError(5,0.2,0.2,0.008602906,0.008602906);
   grae->SetPoint(6,4.4,0.1227);
   grae->SetPointError(6,0.1,0.1,0.007698052,0.007698052);
   
   TH1F *Graph_HepData8420d22x1y1555 = new TH1F("Graph_HepData8420d22x1y1555","/HepData/8420/d22x1y1",100,0.13,50.17);
   Graph_HepData8420d22x1y1555->SetMinimum(0.1109316);
   Graph_HepData8420d22x1y1555->SetMaximum(0.1597754);
   Graph_HepData8420d22x1y1555->SetDirectory(0);
   Graph_HepData8420d22x1y1555->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_HepData8420d22x1y1555->SetLineColor(ci);
   Graph_HepData8420d22x1y1555->GetXaxis()->SetLabelFont(42);
   Graph_HepData8420d22x1y1555->GetXaxis()->SetLabelOffset(0);
   Graph_HepData8420d22x1y1555->GetXaxis()->SetLabelSize(0.05);
   Graph_HepData8420d22x1y1555->GetXaxis()->SetTitleSize(0.06);
   Graph_HepData8420d22x1y1555->GetXaxis()->SetTitleOffset(1.08);
   Graph_HepData8420d22x1y1555->GetXaxis()->SetTitleFont(42);
   Graph_HepData8420d22x1y1555->GetYaxis()->SetLabelFont(42);
   Graph_HepData8420d22x1y1555->GetYaxis()->SetLabelOffset(0.01);
   Graph_HepData8420d22x1y1555->GetYaxis()->SetLabelSize(0.05);
   Graph_HepData8420d22x1y1555->GetYaxis()->SetTitleSize(0.06);
   Graph_HepData8420d22x1y1555->GetYaxis()->SetTitleOffset(1.3);
   Graph_HepData8420d22x1y1555->GetYaxis()->SetTitleFont(42);
   Graph_HepData8420d22x1y1555->GetZaxis()->SetLabelFont(42);
   Graph_HepData8420d22x1y1555->GetZaxis()->SetLabelSize(0.05);
   Graph_HepData8420d22x1y1555->GetZaxis()->SetTitleSize(0.06);
   Graph_HepData8420d22x1y1555->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_HepData8420d22x1y1555);
   
   grae->Draw("pe2");
   
   grae = new TGraphAsymmErrors(10);
   grae->SetName("/HepData/8463/d37x1y1");
   grae->SetTitle("/HepData/8463/d37x1y1");

   ci = TColor::GetColor("#ff0000");
   grae->SetFillColor(ci);
   grae->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   grae->SetLineColor(ci);

   ci = TColor::GetColor("#ff0000");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(34);
   grae->SetMarkerSize(1.5);
   grae->SetPoint(0,1601,0.1485);
   grae->SetPointError(0,60,60,0.01040433,0.01040433);
   grae->SetPoint(1,1294,0.1496);
   grae->SetPointError(1,49,49,0.01050428,0.01050428);
   grae->SetPoint(2,966,0.1497);
   grae->SetPointError(2,37,37,0.0105019,0.0105019);
   grae->SetPoint(3,649,0.1497);
   grae->SetPointError(3,23,23,0.01050428,0.01050428);
   grae->SetPoint(4,426,0.1488);
   grae->SetPointError(4,15,15,0.01040433,0.01040433);
   grae->SetPoint(5,261,0.1469);
   grae->SetPointError(5,9,9,0.01030776,0.01030776);
   grae->SetPoint(6,149,0.144);
   grae->SetPointError(6,6,6,0.01011237,0.01011237);
   grae->SetPoint(7,76,0.1385);
   grae->SetPointError(7,4,4,0.009718539,0.009718539);
   grae->SetPoint(8,35,0.1333);
   grae->SetPointError(8,2,2,0.009334345,0.009334345);
   grae->SetPoint(9,13.4,0.1296);
   grae->SetPointError(9,1.2,1.6,0.00917878,0.00917878);
   
   TH1F *Graph_HepData8463d37x1y16 = new TH1F("Graph_/HepData/8463/d37x1y16","/HepData/8463/d37x1y1",100,10.98,1825.88);
   Graph_HepData8463d37x1y16->SetMinimum(0.1164429);
   Graph_HepData8463d37x1y16->SetMaximum(0.1641826);
   Graph_HepData8463d37x1y16->SetDirectory(0);
   Graph_HepData8463d37x1y16->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_HepData8463d37x1y16->SetLineColor(ci);
   Graph_HepData8463d37x1y16->GetXaxis()->SetLabelFont(42);
   Graph_HepData8463d37x1y16->GetXaxis()->SetLabelOffset(0);
   Graph_HepData8463d37x1y16->GetXaxis()->SetLabelSize(0.05);
   Graph_HepData8463d37x1y16->GetXaxis()->SetTitleSize(0.06);
   Graph_HepData8463d37x1y16->GetXaxis()->SetTitleOffset(1.08);
   Graph_HepData8463d37x1y16->GetXaxis()->SetTitleFont(42);
   Graph_HepData8463d37x1y16->GetYaxis()->SetLabelFont(42);
   Graph_HepData8463d37x1y16->GetYaxis()->SetLabelOffset(0.01);
   Graph_HepData8463d37x1y16->GetYaxis()->SetLabelSize(0.05);
   Graph_HepData8463d37x1y16->GetYaxis()->SetTitleSize(0.06);
   Graph_HepData8463d37x1y16->GetYaxis()->SetTitleOffset(1.3);
   Graph_HepData8463d37x1y16->GetYaxis()->SetTitleFont(42);
   Graph_HepData8463d37x1y16->GetZaxis()->SetLabelFont(42);
   Graph_HepData8463d37x1y16->GetZaxis()->SetLabelSize(0.05);
   Graph_HepData8463d37x1y16->GetZaxis()->SetTitleSize(0.06);
   Graph_HepData8463d37x1y16->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_HepData8463d37x1y16);
   
   grae->Draw("pe2");
   
   TLegend *leg = new TLegend(0.18,0.58,0.87,0.88,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.045);
   leg->SetLineColor(0);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   TLegendEntry *entry=leg->AddEntry("NULL","ALICE V0 Multiplicity Classes, (K^{+} + K^{-}) / (#pi^{+} + #pi^{-})","h");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(62);
   entry=leg->AddEntry("IntegratedRatiodNdy_Ktopi_sys","pp, #sqrt{#it{s}} = 7 TeV","pf");

   ci = TColor::GetColor("#009900");
   entry->SetFillColor(ci);

   ci = TColor::GetColor("#009900");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#009900");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(22);
   entry->SetMarkerSize(1.5);
   entry->SetTextFont(42);
   entry=leg->AddEntry("HepData8420d22x1y155","p-Pb, #sqrt{s_{NN}} = 5.02 TeV","pf");

   ci = TColor::GetColor("#0000ff");
   entry->SetFillColor(ci);

   ci = TColor::GetColor("#0000ff");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#0000ff");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(33);
   entry->SetMarkerSize(1.5);
   entry->SetTextFont(42);
   entry=leg->AddEntry("/HepData/8463/d37x1y1","Pb-Pb, #sqrt{s_{NN}} = 2.76 TeV","pf");

   ci = TColor::GetColor("#ff0000");
   entry->SetFillColor(ci);

   ci = TColor::GetColor("#ff0000");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#ff0000");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(34);
   entry->SetMarkerSize(1.5);
   entry->SetTextFont(42);
   leg->Draw();
   cdNdyRatio_V0M->Modified();
   cdNdyRatio_V0M->cd();
   cdNdyRatio_V0M->SetSelected(cdNdyRatio_V0M);
}
