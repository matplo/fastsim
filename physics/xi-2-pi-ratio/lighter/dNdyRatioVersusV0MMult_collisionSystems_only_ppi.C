{
//=========Macro generated from canvas: cdNdyRatio_V0M/cdNdyRatio
//=========  (Tue Sep 15 15:18:29 2015) by ROOT version5.34/30
   TCanvas *cdNdyRatio_V0M = new TCanvas("cdNdyRatio_V0M", "cdNdyRatio",0,0,1000,700);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   cdNdyRatio_V0M->SetHighLightColor(2);
   cdNdyRatio_V0M->Range(-0.1228788,0.032,3.877121,0.08533333);
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
   
   TH1F *hframe__8 = new TH1F("hframe__8","",1000,0,3000);
   hframe__8->SetMinimum(0.04);
   hframe__8->SetMaximum(0.08);
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
   hframe__8->GetYaxis()->SetTitle("d#it{N}/d#it{y} Ratio");
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
   gre->SetName("IntegratedRatiodNdy_ptopi_stat");
   gre->SetTitle("Graph");

   ci = TColor::GetColor("#009900");
   gre->SetFillColor(ci);
   gre->SetFillStyle(0);

   ci = TColor::GetColor("#009900");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#009900");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(26);
   gre->SetMarkerSize(1.5);
   gre->SetPoint(0,25.30085,0.05336206);
   gre->SetPointError(0,0.0862803,0.0002612336);
   gre->SetPoint(1,20.84913,0.0553136);
   gre->SetPointError(1,0.02997,0.0001649031);
   gre->SetPoint(2,16.51347,0.05596078);
   gre->SetPointError(2,0.00999,6.990165e-05);
   gre->SetPoint(3,13.45653,0.05611708);
   gre->SetPointError(3,0.00999,6.25875e-05);
   gre->SetPoint(4,11.50694,0.0562508);
   gre->SetPointError(4,0.00998,6.380161e-05);
   gre->SetPoint(5,10.07952,0.05631232);
   gre->SetPointError(5,0.009959999,6.715342e-05);
   gre->SetPoint(6,8.447464,0.05621536);
   gre->SetPointError(6,0,5.246816e-05);
   gre->SetPoint(7,6.724329,0.05604173);
   gre->SetPointError(7,0,5.635823e-05);
   gre->SetPoint(8,5.397827,0.05526944);
   gre->SetPointError(8,0,5.97306e-05);
   gre->SetPoint(9,3.896809,0.05377321);
   gre->SetPointError(9,0,5.088419e-05);
   gre->SetPoint(10,2.261159,0.04813909);
   gre->SetPointError(10,0,4.875282e-05);
   
   TH1F *Graph_IntegratedRatiodNdy_ptopi_stat40 = new TH1F("Graph_IntegratedRatiodNdy_ptopi_stat40","Graph",100,2.035043,27.69973);
   Graph_IntegratedRatiodNdy_ptopi_stat40->SetMinimum(0.04726143);
   Graph_IntegratedRatiodNdy_ptopi_stat40->SetMaximum(0.05720838);
   Graph_IntegratedRatiodNdy_ptopi_stat40->SetDirectory(0);
   Graph_IntegratedRatiodNdy_ptopi_stat40->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_IntegratedRatiodNdy_ptopi_stat40->SetLineColor(ci);
   Graph_IntegratedRatiodNdy_ptopi_stat40->GetXaxis()->SetLabelFont(42);
   Graph_IntegratedRatiodNdy_ptopi_stat40->GetXaxis()->SetLabelOffset(0);
   Graph_IntegratedRatiodNdy_ptopi_stat40->GetXaxis()->SetLabelSize(0.05);
   Graph_IntegratedRatiodNdy_ptopi_stat40->GetXaxis()->SetTitleSize(0.06);
   Graph_IntegratedRatiodNdy_ptopi_stat40->GetXaxis()->SetTitleOffset(1.08);
   Graph_IntegratedRatiodNdy_ptopi_stat40->GetXaxis()->SetTitleFont(42);
   Graph_IntegratedRatiodNdy_ptopi_stat40->GetYaxis()->SetLabelFont(42);
   Graph_IntegratedRatiodNdy_ptopi_stat40->GetYaxis()->SetLabelOffset(0.01);
   Graph_IntegratedRatiodNdy_ptopi_stat40->GetYaxis()->SetLabelSize(0.05);
   Graph_IntegratedRatiodNdy_ptopi_stat40->GetYaxis()->SetTitleSize(0.06);
   Graph_IntegratedRatiodNdy_ptopi_stat40->GetYaxis()->SetTitleOffset(1.3);
   Graph_IntegratedRatiodNdy_ptopi_stat40->GetYaxis()->SetTitleFont(42);
   Graph_IntegratedRatiodNdy_ptopi_stat40->GetZaxis()->SetLabelFont(42);
   Graph_IntegratedRatiodNdy_ptopi_stat40->GetZaxis()->SetLabelSize(0.05);
   Graph_IntegratedRatiodNdy_ptopi_stat40->GetZaxis()->SetTitleSize(0.06);
   Graph_IntegratedRatiodNdy_ptopi_stat40->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_IntegratedRatiodNdy_ptopi_stat40);
   
   gre->Draw("pe1");
   
   gre = new TGraphErrors(11);
   gre->SetName("IntegratedRatiodNdy_ptopi_sys");
   gre->SetTitle("Graph");

   ci = TColor::GetColor("#009900");
   gre->SetFillColor(ci);
   gre->SetFillStyle(0);

   ci = TColor::GetColor("#009900");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#009900");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(26);
   gre->SetMarkerSize(1.5);
   gre->SetPoint(0,25.30085,0.05336206);
   gre->SetPointError(0,0.7590256,0.004501955);
   gre->SetPoint(1,20.84913,0.0553136);
   gre->SetPointError(1,0.6254739,0.00448197);
   gre->SetPoint(2,16.51347,0.05596078);
   gre->SetPointError(2,0.4954042,0.004473123);
   gre->SetPoint(3,13.45653,0.05611708);
   gre->SetPointError(3,0.4036959,0.004487556);
   gre->SetPoint(4,11.50694,0.0562508);
   gre->SetPointError(4,0.3452082,0.004554136);
   gre->SetPoint(5,10.07952,0.05631232);
   gre->SetPointError(5,0.3023856,0.004581195);
   gre->SetPoint(6,8.447464,0.05621536);
   gre->SetPointError(6,0.2534239,0.004619666);
   gre->SetPoint(7,6.724329,0.05604173);
   gre->SetPointError(7,0.2017299,0.004714034);
   gre->SetPoint(8,5.397827,0.05526944);
   gre->SetPointError(8,0.1619348,0.004829708);
   gre->SetPoint(9,3.896809,0.05377321);
   gre->SetPointError(9,0.1169043,0.005259475);
   gre->SetPoint(10,2.261159,0.04813909);
   gre->SetPointError(10,0.06783476,0.00636391);
   
   TH1F *Graph_IntegratedRatiodNdy_ptopi_sys41 = new TH1F("Graph_IntegratedRatiodNdy_ptopi_sys41","Graph",100,1.973992,28.44653);
   Graph_IntegratedRatiodNdy_ptopi_sys41->SetMinimum(0.03986335);
   Graph_IntegratedRatiodNdy_ptopi_sys41->SetMaximum(0.06280534);
   Graph_IntegratedRatiodNdy_ptopi_sys41->SetDirectory(0);
   Graph_IntegratedRatiodNdy_ptopi_sys41->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_IntegratedRatiodNdy_ptopi_sys41->SetLineColor(ci);
   Graph_IntegratedRatiodNdy_ptopi_sys41->GetXaxis()->SetLabelFont(42);
   Graph_IntegratedRatiodNdy_ptopi_sys41->GetXaxis()->SetLabelOffset(0);
   Graph_IntegratedRatiodNdy_ptopi_sys41->GetXaxis()->SetLabelSize(0.05);
   Graph_IntegratedRatiodNdy_ptopi_sys41->GetXaxis()->SetTitleSize(0.06);
   Graph_IntegratedRatiodNdy_ptopi_sys41->GetXaxis()->SetTitleOffset(1.08);
   Graph_IntegratedRatiodNdy_ptopi_sys41->GetXaxis()->SetTitleFont(42);
   Graph_IntegratedRatiodNdy_ptopi_sys41->GetYaxis()->SetLabelFont(42);
   Graph_IntegratedRatiodNdy_ptopi_sys41->GetYaxis()->SetLabelOffset(0.01);
   Graph_IntegratedRatiodNdy_ptopi_sys41->GetYaxis()->SetLabelSize(0.05);
   Graph_IntegratedRatiodNdy_ptopi_sys41->GetYaxis()->SetTitleSize(0.06);
   Graph_IntegratedRatiodNdy_ptopi_sys41->GetYaxis()->SetTitleOffset(1.3);
   Graph_IntegratedRatiodNdy_ptopi_sys41->GetYaxis()->SetTitleFont(42);
   Graph_IntegratedRatiodNdy_ptopi_sys41->GetZaxis()->SetLabelFont(42);
   Graph_IntegratedRatiodNdy_ptopi_sys41->GetZaxis()->SetLabelSize(0.05);
   Graph_IntegratedRatiodNdy_ptopi_sys41->GetZaxis()->SetTitleSize(0.06);
   Graph_IntegratedRatiodNdy_ptopi_sys41->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_IntegratedRatiodNdy_ptopi_sys41);
   
   gre->Draw("pe2");
   
   gre = new TGraphErrors(11);
   gre->SetName("IntegratedRatiodNdy_ptopi_sys");
   gre->SetTitle("Graph");

   ci = TColor::GetColor("#009900");
   gre->SetFillColor(ci);
   gre->SetFillStyle(0);

   ci = TColor::GetColor("#009900");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#009900");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(26);
   gre->SetMarkerSize(1.5);
   gre->SetPoint(0,25.30085,0.05336206);
   gre->SetPointError(0,0.7590256,0.004501955);
   gre->SetPoint(1,20.84913,0.0553136);
   gre->SetPointError(1,0.6254739,0.00448197);
   gre->SetPoint(2,16.51347,0.05596078);
   gre->SetPointError(2,0.4954042,0.004473123);
   gre->SetPoint(3,13.45653,0.05611708);
   gre->SetPointError(3,0.4036959,0.004487556);
   gre->SetPoint(4,11.50694,0.0562508);
   gre->SetPointError(4,0.3452082,0.004554136);
   gre->SetPoint(5,10.07952,0.05631232);
   gre->SetPointError(5,0.3023856,0.004581195);
   gre->SetPoint(6,8.447464,0.05621536);
   gre->SetPointError(6,0.2534239,0.004619666);
   gre->SetPoint(7,6.724329,0.05604173);
   gre->SetPointError(7,0.2017299,0.004714034);
   gre->SetPoint(8,5.397827,0.05526944);
   gre->SetPointError(8,0.1619348,0.004829708);
   gre->SetPoint(9,3.896809,0.05377321);
   gre->SetPointError(9,0.1169043,0.005259475);
   gre->SetPoint(10,2.261159,0.04813909);
   gre->SetPointError(10,0.06783476,0.00636391);
   
   TH1F *Graph_IntegratedRatiodNdy_ptopi_sys42 = new TH1F("Graph_IntegratedRatiodNdy_ptopi_sys42","Graph",100,1.973992,28.44653);
   Graph_IntegratedRatiodNdy_ptopi_sys42->SetMinimum(0.03986335);
   Graph_IntegratedRatiodNdy_ptopi_sys42->SetMaximum(0.06280534);
   Graph_IntegratedRatiodNdy_ptopi_sys42->SetDirectory(0);
   Graph_IntegratedRatiodNdy_ptopi_sys42->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_IntegratedRatiodNdy_ptopi_sys42->SetLineColor(ci);
   Graph_IntegratedRatiodNdy_ptopi_sys42->GetXaxis()->SetLabelFont(42);
   Graph_IntegratedRatiodNdy_ptopi_sys42->GetXaxis()->SetLabelOffset(0);
   Graph_IntegratedRatiodNdy_ptopi_sys42->GetXaxis()->SetLabelSize(0.05);
   Graph_IntegratedRatiodNdy_ptopi_sys42->GetXaxis()->SetTitleSize(0.06);
   Graph_IntegratedRatiodNdy_ptopi_sys42->GetXaxis()->SetTitleOffset(1.08);
   Graph_IntegratedRatiodNdy_ptopi_sys42->GetXaxis()->SetTitleFont(42);
   Graph_IntegratedRatiodNdy_ptopi_sys42->GetYaxis()->SetLabelFont(42);
   Graph_IntegratedRatiodNdy_ptopi_sys42->GetYaxis()->SetLabelOffset(0.01);
   Graph_IntegratedRatiodNdy_ptopi_sys42->GetYaxis()->SetLabelSize(0.05);
   Graph_IntegratedRatiodNdy_ptopi_sys42->GetYaxis()->SetTitleSize(0.06);
   Graph_IntegratedRatiodNdy_ptopi_sys42->GetYaxis()->SetTitleOffset(1.3);
   Graph_IntegratedRatiodNdy_ptopi_sys42->GetYaxis()->SetTitleFont(42);
   Graph_IntegratedRatiodNdy_ptopi_sys42->GetZaxis()->SetLabelFont(42);
   Graph_IntegratedRatiodNdy_ptopi_sys42->GetZaxis()->SetLabelSize(0.05);
   Graph_IntegratedRatiodNdy_ptopi_sys42->GetZaxis()->SetTitleSize(0.06);
   Graph_IntegratedRatiodNdy_ptopi_sys42->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_IntegratedRatiodNdy_ptopi_sys42);
   
   gre->Draw("pe0x0");
   
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(7);
   grae->SetName("/HepData/8420/d22x1y2");
   grae->SetTitle("/HepData/8420/d22x1y2");

   ci = TColor::GetColor("#0000ff");
   grae->SetFillColor(ci);
   grae->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   grae->SetLineColor(ci);

   ci = TColor::GetColor("#0000ff");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(27);
   grae->SetMarkerSize(1.5);
   grae->SetPoint(0,45,0.05588);
   grae->SetPointError(0,1,1,0.003171829,0.003171829);
   grae->SetPoint(1,36.2,0.05603);
   grae->SetPointError(1,0.8,0.8,0.003159019,0.003159019);
   grae->SetPoint(2,30.5,0.05622);
   grae->SetPointError(2,0.7,0.7,0.003145155,0.003145155);
   grae->SetPoint(3,23.2,0.05618);
   grae->SetPointError(3,0.5,0.5,0.003212756,0.003212756);
   grae->SetPoint(4,16.1,0.05639);
   grae->SetPointError(4,0.4,0.4,0.003202671,0.003202671);
   grae->SetPoint(5,9.8,0.05649);
   grae->SetPointError(5,0.2,0.2,0.003237823,0.003237823);
   grae->SetPoint(6,4.4,0.0535);
   grae->SetPointError(6,0.1,0.1,0.003072523,0.003072523);
   
   TH1F *Graph_HepData8420d22x1y27 = new TH1F("Graph_/HepData/8420/d22x1y27","/HepData/8420/d22x1y2",100,0.13,50.17);
   Graph_HepData8420d22x1y27->SetMinimum(0.04949744);
   Graph_HepData8420d22x1y27->SetMaximum(0.06065786);
   Graph_HepData8420d22x1y27->SetDirectory(0);
   Graph_HepData8420d22x1y27->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_HepData8420d22x1y27->SetLineColor(ci);
   Graph_HepData8420d22x1y27->GetXaxis()->SetLabelFont(42);
   Graph_HepData8420d22x1y27->GetXaxis()->SetLabelOffset(0);
   Graph_HepData8420d22x1y27->GetXaxis()->SetLabelSize(0.05);
   Graph_HepData8420d22x1y27->GetXaxis()->SetTitleSize(0.06);
   Graph_HepData8420d22x1y27->GetXaxis()->SetTitleOffset(1.08);
   Graph_HepData8420d22x1y27->GetXaxis()->SetTitleFont(42);
   Graph_HepData8420d22x1y27->GetYaxis()->SetLabelFont(42);
   Graph_HepData8420d22x1y27->GetYaxis()->SetLabelOffset(0.01);
   Graph_HepData8420d22x1y27->GetYaxis()->SetLabelSize(0.05);
   Graph_HepData8420d22x1y27->GetYaxis()->SetTitleSize(0.06);
   Graph_HepData8420d22x1y27->GetYaxis()->SetTitleOffset(1.3);
   Graph_HepData8420d22x1y27->GetYaxis()->SetTitleFont(42);
   Graph_HepData8420d22x1y27->GetZaxis()->SetLabelFont(42);
   Graph_HepData8420d22x1y27->GetZaxis()->SetLabelSize(0.05);
   Graph_HepData8420d22x1y27->GetZaxis()->SetTitleSize(0.06);
   Graph_HepData8420d22x1y27->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_HepData8420d22x1y27);
   
   grae->Draw("pe2");
   
   grae = new TGraphAsymmErrors(10);
   grae->SetName("/HepData/8463/d36x1y1");
   grae->SetTitle("/HepData/8463/d36x1y1");

   ci = TColor::GetColor("#ff0000");
   grae->SetFillColor(ci);
   grae->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   grae->SetLineColor(ci);

   ci = TColor::GetColor("#ff0000");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(28);
   grae->SetMarkerSize(1.5);
   grae->SetPoint(0,1601,0.04559);
   grae->SetPointError(0,60,60,0.003191269,0.003191269);
   grae->SetPoint(1,1294,0.04569);
   grae->SetPointError(1,49,49,0.003201562,0.003201562);
   grae->SetPoint(2,966,0.04629);
   grae->SetPointError(2,37,37,0.003240988,0.003240988);
   grae->SetPoint(3,649,0.04722);
   grae->SetPointError(3,23,23,0.003311223,0.003311223);
   grae->SetPoint(4,426,0.04825);
   grae->SetPointError(4,15,15,0.003381789,0.003381789);
   grae->SetPoint(5,261,0.04955);
   grae->SetPointError(5,9,9,0.003472823,0.003472823);
   grae->SetPoint(6,149,0.05111);
   grae->SetPointError(6,6,6,0.003584522,0.003584522);
   grae->SetPoint(7,76,0.0524);
   grae->SetPointError(7,4,4,0.003676588,0.003676588);
   grae->SetPoint(8,35,0.05368);
   grae->SetPointError(8,2,2,0.003772758,0.003772758);
   grae->SetPoint(9,13.4,0.05436);
   grae->SetPointError(9,1.2,1.6,0.00384138,0.00384138);
   
   TH1F *Graph_HepData8463d36x1y18 = new TH1F("Graph_/HepData/8463/d36x1y18","/HepData/8463/d36x1y1",100,10.98,1825.88);
   Graph_HepData8463d36x1y18->SetMinimum(0.04081847);
   Graph_HepData8463d36x1y18->SetMaximum(0.05978164);
   Graph_HepData8463d36x1y18->SetDirectory(0);
   Graph_HepData8463d36x1y18->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Graph_HepData8463d36x1y18->SetLineColor(ci);
   Graph_HepData8463d36x1y18->GetXaxis()->SetLabelFont(42);
   Graph_HepData8463d36x1y18->GetXaxis()->SetLabelOffset(0);
   Graph_HepData8463d36x1y18->GetXaxis()->SetLabelSize(0.05);
   Graph_HepData8463d36x1y18->GetXaxis()->SetTitleSize(0.06);
   Graph_HepData8463d36x1y18->GetXaxis()->SetTitleOffset(1.08);
   Graph_HepData8463d36x1y18->GetXaxis()->SetTitleFont(42);
   Graph_HepData8463d36x1y18->GetYaxis()->SetLabelFont(42);
   Graph_HepData8463d36x1y18->GetYaxis()->SetLabelOffset(0.01);
   Graph_HepData8463d36x1y18->GetYaxis()->SetLabelSize(0.05);
   Graph_HepData8463d36x1y18->GetYaxis()->SetTitleSize(0.06);
   Graph_HepData8463d36x1y18->GetYaxis()->SetTitleOffset(1.3);
   Graph_HepData8463d36x1y18->GetYaxis()->SetTitleFont(42);
   Graph_HepData8463d36x1y18->GetZaxis()->SetLabelFont(42);
   Graph_HepData8463d36x1y18->GetZaxis()->SetLabelSize(0.05);
   Graph_HepData8463d36x1y18->GetZaxis()->SetTitleSize(0.06);
   Graph_HepData8463d36x1y18->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_HepData8463d36x1y18);
   
   grae->Draw("pe2");
   
   TLegend *leg = new TLegend(0.18,0.58,0.87,0.88,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.045);
   leg->SetLineColor(0);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   TLegendEntry *entry=leg->AddEntry("NULL","ALICE V0 Multiplicity Classes, (p + #bar{p}) / (#pi^{+} + #pi^{-})","h");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(62);
   entry=leg->AddEntry("IntegratedRatiodNdy_ptopi_sys","pp, #sqrt{#it{s}} = 7 TeV","pf");

   ci = TColor::GetColor("#009900");
   entry->SetFillColor(ci);

   ci = TColor::GetColor("#009900");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#009900");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(26);
   entry->SetMarkerSize(1.5);
   entry->SetTextFont(42);
   entry=leg->AddEntry("/HepData/8420/d22x1y2","p-Pb, #sqrt{s_{NN}} = 5.02 TeV","pf");

   ci = TColor::GetColor("#0000ff");
   entry->SetFillColor(ci);

   ci = TColor::GetColor("#0000ff");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#0000ff");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(27);
   entry->SetMarkerSize(1.5);
   entry->SetTextFont(42);
   entry=leg->AddEntry("/HepData/8463/d36x1y1","Pb-Pb, #sqrt{s_{NN}} = 2.76 TeV","pf");

   ci = TColor::GetColor("#ff0000");
   entry->SetFillColor(ci);

   ci = TColor::GetColor("#ff0000");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#ff0000");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(28);
   entry->SetMarkerSize(1.5);
   entry->SetTextFont(42);
   leg->Draw();
   cdNdyRatio_V0M->Modified();
   cdNdyRatio_V0M->cd();
   cdNdyRatio_V0M->SetSelected(cdNdyRatio_V0M);
}
