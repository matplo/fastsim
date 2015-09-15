{
//AA points are: 60-80, 40-60, 20-40, 10-20, 0-10
//Npart :         22.52, 68.56, 157.2, 260.1, 355.
//=========Macro generated from canvas: XiOverPi/
//=========  (Tue Sep 15 09:04:59 2015) by ROOT version5.34/08

   Double_t npscale = 1.;
   Double_t escale  = 1.;//2.76;
   Int_t msize = 2;

   TCanvas *XiOverPi = new TCanvas("XiOverPi", "",395,172,800,600);
   gStyle->SetOptStat(0);
   XiOverPi->Range(-1.199792,-0.0025,4.00723,0.0075);
   XiOverPi->SetFillColor(10);
   XiOverPi->SetBorderMode(0);
   XiOverPi->SetBorderSize(2);
   XiOverPi->SetLogx();
   XiOverPi->SetLeftMargin(0.13);
   XiOverPi->SetRightMargin(0.02);
   XiOverPi->SetTopMargin(0.05);
   XiOverPi->SetBottomMargin(0.15);
   XiOverPi->SetFrameFillColor(0);
   XiOverPi->SetFrameBorderMode(0);
   XiOverPi->SetFrameBorderMode(0);
   
   TH1F *hDum__1__1 = new TH1F("hDum__1__1","",1,0.3,8000);
   hDum__1__1->SetMinimum(-0.001);
   hDum__1__1->SetMaximum(0.007);
   hDum__1__1->SetDirectory(0);
   hDum__1__1->SetStats(0);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#000099");
   hDum__1__1->SetLineColor(ci);
   hDum__1__1->GetXaxis()->SetTitle("#LTd#it{N}_{ch}/d#it{#eta}#GT_{|#it{#eta}|< 0.5} / S (1/fm^{2})");
   hDum__1__1->GetXaxis()->SetRange(1,1);
   hDum__1__1->GetXaxis()->SetLabelFont(42);
   hDum__1__1->GetXaxis()->SetLabelSize(0.045);
   hDum__1__1->GetXaxis()->SetTitleSize(0.06);
   hDum__1__1->GetXaxis()->SetTitleOffset(1.1);
   hDum__1__1->GetXaxis()->SetTitleFont(42);
   hDum__1__1->GetYaxis()->SetTitle("(#Xi^{-} + #bar{#Xi}^{+}) / (#pi^{-} + #pi^{+})");
   hDum__1__1->GetYaxis()->SetLabelFont(42);
   hDum__1__1->GetYaxis()->SetLabelSize(0.045);
   hDum__1__1->GetYaxis()->SetTitleSize(0.06);
   hDum__1__1->GetYaxis()->SetTitleOffset(0.8);
   hDum__1__1->GetYaxis()->SetTitleFont(42);
   hDum__1__1->GetZaxis()->SetLabelFont(42);
   hDum__1__1->GetZaxis()->SetLabelSize(0.06);
   hDum__1__1->GetZaxis()->SetTitleSize(0.035);
   hDum__1__1->GetZaxis()->SetTitleFont(42);
   hDum__1__1->Draw("AXIS");
   TLine *line = new TLine(100,0.004536,2000,0.004536);

   ci = TColor::GetColor("#cc0000");
   line->SetLineColor(ci);
   line->SetLineWidth(2);
   //line->Draw();
   line = new TLine(100,0.005039,2000,0.005039);

   ci = TColor::GetColor("#cc0000");
   line->SetLineColor(ci);
   line->SetLineStyle(7);
   line->SetLineWidth(2);
   //line->Draw();
   
   TGraphErrors *gre = new TGraphErrors(5);
   gre->SetName("PbPb_stat");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(21);
   gre->SetPoint(0,55.5,0.004440333);
   gre->SetPointError(0,3,0.0001110083);
   gre->SetPoint(1,205,0.005501285);
   gre->SetPointError(1,7.5,5.141388e-05);
   gre->SetPoint(2,537.5,0.005976331);
   gre->SetPointError(2,19,5.91716e-05);
   gre->SetPoint(3,966,0.005660793);
   gre->SetPointError(3,37,6.60793e-05);
   gre->SetPoint(4,1447.5,0.004986916);
   gre->SetPointError(4,54.5,5.981308e-05);

   ////Npart :         22.52, 68.56, 157.2, 260.1, 355.
   ////Ncol  :         26.71, 127.7, 438.4, 921.2, 1316, 1500.

   TGraphErrors *greAA1 = new TGraphErrors(5);
   greAA1->SetName("PbPb_statAA1");
   greAA1->SetTitle("GraphAA1");
   greAA1->SetFillColor(1);
   greAA1->SetLineColor(2);
   greAA1->SetMarkerColor(2);
   greAA1->SetMarkerStyle(20);
   greAA1->SetMarkerSize(msize);
   greAA1->SetPoint(0,55.5 / 7.,       0.004440333);
   greAA1->SetPoint(1,205 / 13.,       0.005501285);
   greAA1->SetPoint(2,537.5 / 21.,     0.005976331);
   greAA1->SetPoint(3,966 / 28.,       0.005660793);
   greAA1->SetPoint(4,1447.5 / 35.,    0.004986916);
   
   TH1F *Graph_Graph_PbPb_stat11 = new TH1F("Graph_Graph_PbPb_stat11","Graph",100,47.25,1646.95);
   Graph_Graph_PbPb_stat11->SetMinimum(0.004158707);
   Graph_Graph_PbPb_stat11->SetMaximum(0.006206121);
   Graph_Graph_PbPb_stat11->SetDirectory(0);
   Graph_Graph_PbPb_stat11->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph_PbPb_stat11->SetLineColor(ci);
   Graph_Graph_PbPb_stat11->GetXaxis()->SetLabelFont(42);
   Graph_Graph_PbPb_stat11->GetXaxis()->SetLabelSize(0.06);
   Graph_Graph_PbPb_stat11->GetXaxis()->SetTitleSize(0.05);
   Graph_Graph_PbPb_stat11->GetXaxis()->SetTitleFont(42);
   Graph_Graph_PbPb_stat11->GetYaxis()->SetLabelFont(42);
   Graph_Graph_PbPb_stat11->GetYaxis()->SetLabelSize(0.06);
   Graph_Graph_PbPb_stat11->GetYaxis()->SetTitleSize(0.05);
   Graph_Graph_PbPb_stat11->GetYaxis()->SetTitleFont(42);
   Graph_Graph_PbPb_stat11->GetZaxis()->SetLabelFont(42);
   Graph_Graph_PbPb_stat11->GetZaxis()->SetLabelSize(0.06);
   Graph_Graph_PbPb_stat11->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph_PbPb_stat11->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph_PbPb_stat11);
   
   //gre->Draw("p ");
   greAA1->Draw("p ");
   
   gre = new TGraphErrors(5);
   gre->SetName("PbPb_syst");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);
   gre->SetFillStyle(0);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(21);
   gre->SetPoint(0,55.5,0.004440333);
   gre->SetPointError(0,3,0.0004340838);
   gre->SetPoint(1,205,0.005501285);
   gre->SetPointError(1,7.5,0.0005423804);
   gre->SetPoint(2,537.5,0.005976331);
   gre->SetPointError(2,19,0.000582757);
   gre->SetPoint(3,966,0.005660793);
   gre->SetPointError(3,37,0.0005537133);
   gre->SetPoint(4,1447.5,0.004986916);
   gre->SetPointError(4,54.5,0.0004989475);
   
   TH1F *Graph_Graph_PbPb_syst22 = new TH1F("Graph_Graph_PbPb_syst22","Graph",100,47.25,1646.95);
   Graph_Graph_PbPb_syst22->SetMinimum(0.003750965);
   Graph_Graph_PbPb_syst22->SetMaximum(0.006814372);
   Graph_Graph_PbPb_syst22->SetDirectory(0);
   Graph_Graph_PbPb_syst22->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph_PbPb_syst22->SetLineColor(ci);
   Graph_Graph_PbPb_syst22->GetXaxis()->SetLabelFont(42);
   Graph_Graph_PbPb_syst22->GetXaxis()->SetLabelSize(0.06);
   Graph_Graph_PbPb_syst22->GetXaxis()->SetTitleSize(0.05);
   Graph_Graph_PbPb_syst22->GetXaxis()->SetTitleFont(42);
   Graph_Graph_PbPb_syst22->GetYaxis()->SetLabelFont(42);
   Graph_Graph_PbPb_syst22->GetYaxis()->SetLabelSize(0.06);
   Graph_Graph_PbPb_syst22->GetYaxis()->SetTitleSize(0.05);
   Graph_Graph_PbPb_syst22->GetYaxis()->SetTitleFont(42);
   Graph_Graph_PbPb_syst22->GetZaxis()->SetLabelFont(42);
   Graph_Graph_PbPb_syst22->GetZaxis()->SetLabelSize(0.06);
   Graph_Graph_PbPb_syst22->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph_PbPb_syst22->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph_PbPb_syst22);
   
   //gre->Draw("p e2");
   
   gre = new TGraphErrors(1);
   gre->SetName("pp7_stat");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.1);
   gre->SetPoint(0,6.01,0.003518931);
   gre->SetPointError(0,0.2,2.227668e-05);
   
   TH1F *Graph_Graph_pp7_stat33 = new TH1F("Graph_Graph_pp7_stat33","Graph",100,5.77,6.25);
   Graph_Graph_pp7_stat33->SetMinimum(0.003492199);
   Graph_Graph_pp7_stat33->SetMaximum(0.003545663);
   Graph_Graph_pp7_stat33->SetDirectory(0);
   Graph_Graph_pp7_stat33->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph_pp7_stat33->SetLineColor(ci);
   Graph_Graph_pp7_stat33->GetXaxis()->SetLabelFont(42);
   Graph_Graph_pp7_stat33->GetXaxis()->SetLabelSize(0.06);
   Graph_Graph_pp7_stat33->GetXaxis()->SetTitleSize(0.05);
   Graph_Graph_pp7_stat33->GetXaxis()->SetTitleFont(42);
   Graph_Graph_pp7_stat33->GetYaxis()->SetLabelFont(42);
   Graph_Graph_pp7_stat33->GetYaxis()->SetLabelSize(0.06);
   Graph_Graph_pp7_stat33->GetYaxis()->SetTitleSize(0.05);
   Graph_Graph_pp7_stat33->GetYaxis()->SetTitleFont(42);
   Graph_Graph_pp7_stat33->GetZaxis()->SetLabelFont(42);
   Graph_Graph_pp7_stat33->GetZaxis()->SetLabelSize(0.06);
   Graph_Graph_pp7_stat33->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph_pp7_stat33->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph_pp7_stat33);
   
   //gre->Draw("p");
   
   gre = new TGraphErrors(1);
   gre->SetName("pp7_syst");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);
   gre->SetFillStyle(0);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.1);
   gre->SetPoint(0,6.01,0.003518931);
   gre->SetPointError(0,0.2,0.0003489854);
   
   TH1F *Graph_Graph_pp7_syst44 = new TH1F("Graph_Graph_pp7_syst44","Graph",100,5.77,6.25);
   Graph_Graph_pp7_syst44->SetMinimum(0.003100148);
   Graph_Graph_pp7_syst44->SetMaximum(0.003937713);
   Graph_Graph_pp7_syst44->SetDirectory(0);
   Graph_Graph_pp7_syst44->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph_pp7_syst44->SetLineColor(ci);
   Graph_Graph_pp7_syst44->GetXaxis()->SetLabelFont(42);
   Graph_Graph_pp7_syst44->GetXaxis()->SetLabelSize(0.06);
   Graph_Graph_pp7_syst44->GetXaxis()->SetTitleSize(0.05);
   Graph_Graph_pp7_syst44->GetXaxis()->SetTitleFont(42);
   Graph_Graph_pp7_syst44->GetYaxis()->SetLabelFont(42);
   Graph_Graph_pp7_syst44->GetYaxis()->SetLabelSize(0.06);
   Graph_Graph_pp7_syst44->GetYaxis()->SetTitleSize(0.05);
   Graph_Graph_pp7_syst44->GetYaxis()->SetTitleFont(42);
   Graph_Graph_pp7_syst44->GetZaxis()->SetLabelFont(42);
   Graph_Graph_pp7_syst44->GetZaxis()->SetLabelSize(0.06);
   Graph_Graph_pp7_syst44->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph_pp7_syst44->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph_pp7_syst44);
   
   //gre->Draw("p e2");
   
   gre = new TGraphErrors(1);
   gre->SetName("pp900_stat");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(1.1);
   gre->SetPoint(0,3.81,0.003392677);
   gre->SetPointError(0,0.2,0.0006718646);
   
   TH1F *Graph_Graph_pp900_stat55 = new TH1F("Graph_Graph_pp900_stat55","Graph",100,3.57,4.05);
   Graph_Graph_pp900_stat55->SetMinimum(0.00258644);
   Graph_Graph_pp900_stat55->SetMaximum(0.004198915);
   Graph_Graph_pp900_stat55->SetDirectory(0);
   Graph_Graph_pp900_stat55->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph_pp900_stat55->SetLineColor(ci);
   Graph_Graph_pp900_stat55->GetXaxis()->SetLabelFont(42);
   Graph_Graph_pp900_stat55->GetXaxis()->SetLabelSize(0.06);
   Graph_Graph_pp900_stat55->GetXaxis()->SetTitleSize(0.05);
   Graph_Graph_pp900_stat55->GetXaxis()->SetTitleFont(42);
   Graph_Graph_pp900_stat55->GetYaxis()->SetLabelFont(42);
   Graph_Graph_pp900_stat55->GetYaxis()->SetLabelSize(0.06);
   Graph_Graph_pp900_stat55->GetYaxis()->SetTitleSize(0.05);
   Graph_Graph_pp900_stat55->GetYaxis()->SetTitleFont(42);
   Graph_Graph_pp900_stat55->GetZaxis()->SetLabelFont(42);
   Graph_Graph_pp900_stat55->GetZaxis()->SetLabelSize(0.06);
   Graph_Graph_pp900_stat55->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph_pp900_stat55->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph_pp900_stat55);
   
   //gre->Draw("p");
   
   gre = new TGraphErrors(1);
   gre->SetName("pp900_syst");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);
   gre->SetFillStyle(0);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(1.1);
   gre->SetPoint(0,3.81,0.003392677);
   gre->SetPointError(0,0.2,0.0003473011);
   
   TH1F *Graph_Graph_pp900_syst66 = new TH1F("Graph_Graph_pp900_syst66","Graph",100,3.57,4.05);
   Graph_Graph_pp900_syst66->SetMinimum(0.002975916);
   Graph_Graph_pp900_syst66->SetMaximum(0.003809438);
   Graph_Graph_pp900_syst66->SetDirectory(0);
   Graph_Graph_pp900_syst66->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph_pp900_syst66->SetLineColor(ci);
   Graph_Graph_pp900_syst66->GetXaxis()->SetLabelFont(42);
   Graph_Graph_pp900_syst66->GetXaxis()->SetLabelSize(0.06);
   Graph_Graph_pp900_syst66->GetXaxis()->SetTitleSize(0.05);
   Graph_Graph_pp900_syst66->GetXaxis()->SetTitleFont(42);
   Graph_Graph_pp900_syst66->GetYaxis()->SetLabelFont(42);
   Graph_Graph_pp900_syst66->GetYaxis()->SetLabelSize(0.06);
   Graph_Graph_pp900_syst66->GetYaxis()->SetTitleSize(0.05);
   Graph_Graph_pp900_syst66->GetYaxis()->SetTitleFont(42);
   Graph_Graph_pp900_syst66->GetZaxis()->SetLabelFont(42);
   Graph_Graph_pp900_syst66->GetZaxis()->SetLabelSize(0.06);
   Graph_Graph_pp900_syst66->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph_pp900_syst66->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph_pp900_syst66);
   
   //gre->Draw("p e2");
   
   gre = new TGraphErrors(7);
   gre->SetName("pPb_stat");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);

   ci = TColor::GetColor("#0000cc");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#0000cc");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(34);
   gre->SetPoint(0,45.15,0.005768621);
   gre->SetPointError(0,0,4.512445e-05);
   gre->SetPoint(1,36.22,0.005622045);
   gre->SetPointError(1,0,4.709984e-05);
   gre->SetPoint(2,30.46,0.005346414);
   gre->SetPointError(2,0,3.534208e-05);
   gre->SetPoint(3,23.24,0.005057942);
   gre->SetPointError(3,0,2.948387e-05);
   gre->SetPoint(4,16.08,0.0047482);
   gre->SetPointError(4,0,3.274952e-05);
   gre->SetPoint(5,9.82,0.004207201);
   gre->SetPointError(5,0,4.118303e-05);
   gre->SetPoint(6,4.41,0.003419286);
   gre->SetPointError(6,0,6.568653e-05);

   //pA:
   ////Npart :          2.94, 4.81, 7.42, 10.4, 12.7, 14.0, 15.7
   npscale = 1.;
   escale  = 1.;//5.02;
   gre_pA1 = new TGraphErrors(7);
   gre_pA1->SetName("pPb_stat_pA1");
   gre_pA1->SetTitle("Graph_pA1");
   gre_pA1->SetFillColor(1);

   ci = TColor::GetColor("#0000cc");
   gre_pA1->SetLineColor(ci);

   ci = TColor::GetColor("#0000cc");
   gre_pA1->SetMarkerColor(ci);
   gre_pA1->SetMarkerStyle(20);
   gre_pA1->SetMarkerSize(msize);
   gre_pA1->SetPoint(0,45.15/ 1.8,  0.005768621);
   gre_pA1->SetPoint(1,36.22/ 1.7,  0.005622045);
   gre_pA1->SetPoint(2,30.46/ 1.7,  0.005346414);
   gre_pA1->SetPoint(3,23.24/ 1.6,  0.005057942);
   gre_pA1->SetPoint(4,16.08/ 1.4,  0.0047482);
   gre_pA1->SetPoint(5,9.82 / 1.3,  0.004207201);
   gre_pA1->SetPoint(6,4.41 / 1.15, 0.003419286);

   TH1F *Graph_Graph_pPb_stat77 = new TH1F("Graph_Graph_pPb_stat77","Graph",100,0.3359997,49.224);
   Graph_Graph_pPb_stat77->SetMinimum(0.003107584);
   Graph_Graph_pPb_stat77->SetMaximum(0.006059761);
   Graph_Graph_pPb_stat77->SetDirectory(0);
   Graph_Graph_pPb_stat77->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph_pPb_stat77->SetLineColor(ci);
   Graph_Graph_pPb_stat77->GetXaxis()->SetLabelFont(42);
   Graph_Graph_pPb_stat77->GetXaxis()->SetLabelSize(0.06);
   Graph_Graph_pPb_stat77->GetXaxis()->SetTitleSize(0.05);
   Graph_Graph_pPb_stat77->GetXaxis()->SetTitleFont(42);
   Graph_Graph_pPb_stat77->GetYaxis()->SetLabelFont(42);
   Graph_Graph_pPb_stat77->GetYaxis()->SetLabelSize(0.06);
   Graph_Graph_pPb_stat77->GetYaxis()->SetTitleSize(0.05);
   Graph_Graph_pPb_stat77->GetYaxis()->SetTitleFont(42);
   Graph_Graph_pPb_stat77->GetZaxis()->SetLabelFont(42);
   Graph_Graph_pPb_stat77->GetZaxis()->SetLabelSize(0.06);
   Graph_Graph_pPb_stat77->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph_pPb_stat77->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph_pPb_stat77);
   
   //gre->Draw("p ");
   
   gre = new TGraphErrors(7);
   gre->SetName("pPb_syst");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);
   gre->SetFillStyle(0);

   ci = TColor::GetColor("#0000cc");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#0000cc");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(34);
   gre->SetPoint(0,45.15,0.005768621);
   gre->SetPointError(0,1,0.0004942234);
   gre->SetPoint(1,36.22,0.005622045);
   gre->SetPointError(1,0.8,0.0004865474);
   gre->SetPoint(2,30.46,0.005346414);
   gre->SetPointError(2,0.67,0.0004638555);
   gre->SetPoint(3,23.24,0.005057942);
   gre->SetPointError(3,0.51,0.0004403629);
   gre->SetPoint(4,16.08,0.0047482);
   gre->SetPointError(4,0.35,0.0004328247);
   gre->SetPoint(5,9.82,0.004207201);
   gre->SetPointError(5,0.21,0.0003910189);
   gre->SetPoint(6,4.41,0.003419286);
   gre->SetPointError(6,0.1,0.0003182441);
   
   TH1F *Graph_Graph_pPb_syst88 = new TH1F("Graph_Graph_pPb_syst88","Graph",100,0.1259997,50.334);
   Graph_Graph_pPb_syst88->SetMinimum(0.002784861);
   Graph_Graph_pPb_syst88->SetMaximum(0.006579025);
   Graph_Graph_pPb_syst88->SetDirectory(0);
   Graph_Graph_pPb_syst88->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph_pPb_syst88->SetLineColor(ci);
   Graph_Graph_pPb_syst88->GetXaxis()->SetLabelFont(42);
   Graph_Graph_pPb_syst88->GetXaxis()->SetLabelSize(0.06);
   Graph_Graph_pPb_syst88->GetXaxis()->SetTitleSize(0.05);
   Graph_Graph_pPb_syst88->GetXaxis()->SetTitleFont(42);
   Graph_Graph_pPb_syst88->GetYaxis()->SetLabelFont(42);
   Graph_Graph_pPb_syst88->GetYaxis()->SetLabelSize(0.06);
   Graph_Graph_pPb_syst88->GetYaxis()->SetTitleSize(0.05);
   Graph_Graph_pPb_syst88->GetYaxis()->SetTitleFont(42);
   Graph_Graph_pPb_syst88->GetZaxis()->SetLabelFont(42);
   Graph_Graph_pPb_syst88->GetZaxis()->SetLabelSize(0.06);
   Graph_Graph_pPb_syst88->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph_pPb_syst88->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph_pPb_syst88);
   
   //gre->Draw("p e2");
   
   TLegend *leg = new TLegend(0.143216,0.789199,0.420854,0.940767,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.033);
   leg->SetLineColor(0);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   TLegendEntry *entry=leg->AddEntry("TLine","#splitline{GSI-Heidelberg model}{Pb-Pb - T_{ch}=156MeV}","l");

   ci = TColor::GetColor("#cc0000");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("TLine","#splitline{THERMUS 2.3 model}{Pb-Pb - T_{ch}=155MeV}","l");

   ci = TColor::GetColor("#cc0000");
   entry->SetLineColor(ci);
   entry->SetLineStyle(7);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   leg->Draw();
   
   leg = new TLegend(0.51005,0.189895,0.967337,0.52439,NULL,"brNDC");
   leg->SetBorderSize(1);
   leg->SetTextSize(0.033);
   leg->SetLineColor(0);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   entry=leg->AddEntry("NULL","    #bf{ALICE}","h");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("pPb_stat","#splitline{Preliminary p-Pb #sqrt{#it{s}_{NN}} = 5.02 TeV}{V0A Mult. Evt. Classes (Pb-side)}","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#0000cc");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(34);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("pp900_stat","pp (MB) #sqrt{#it{s}} = 900 GeV","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(23);
   entry->SetMarkerSize(1.1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("pp7_syst","pp (MB) #sqrt{#it{s}} = 7 TeV","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(22);
   entry->SetMarkerSize(1.1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("PbPb_stat","Pb-Pb #sqrt{#it{s}_{NN}} = 2.76 TeV","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(2);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("Graph","#splitline{Preliminary pp #sqrt{#it{s}} = 7 TeV}{V0M Mult. Evt. Classes}","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#009900");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(8);
   entry->SetMarkerSize(1);
   leg->Draw();
   
   gre = new TGraphErrors(8);
   gre->SetName("Graph");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);
   gre->SetFillStyle(0);

   ci = TColor::GetColor("#009900");
   gre->SetLineColor(ci);
   gre->SetPoint(0,21.294,0.004956781);
   gre->SetPointError(0,0.639,0.0004834296);
   gre->SetPoint(1,16.513,0.004693559);
   gre->SetPointError(1,0.495,0.0004700706);
   gre->SetPoint(2,13.457,0.00472104);
   gre->SetPointError(2,0.404,0.0005086072);
   gre->SetPoint(3,11.507,0.00446398);
   gre->SetPointError(3,0.345,0.0004609848);
   gre->SetPoint(4,8.99,0.004165056);
   gre->SetPointError(4,0.271,0.0004376774);
   gre->SetPoint(5,6.057,0.003705069);
   gre->SetPointError(5,0.19,0.0003968855);
   gre->SetPoint(6,3.897,0.003070101);
   gre->SetPointError(6,0.143,0.0003686157);
   gre->SetPoint(7,2.261,0.00221639);
   gre->SetPointError(7,0.117,0.0003149202);
   
   TH1F *Graph_Graph9 = new TH1F("Graph_Graph9","Graph",100,0.1651,23.9119);
   Graph_Graph9->SetMinimum(0.001547596);
   Graph_Graph9->SetMaximum(0.005794085);
   Graph_Graph9->SetDirectory(0);
   Graph_Graph9->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph9->SetLineColor(ci);
   Graph_Graph9->GetXaxis()->SetLabelFont(42);
   Graph_Graph9->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph9->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph9->GetXaxis()->SetTitleFont(42);
   Graph_Graph9->GetYaxis()->SetLabelFont(42);
   Graph_Graph9->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph9->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph9->GetYaxis()->SetTitleFont(42);
   Graph_Graph9->GetZaxis()->SetLabelFont(42);
   Graph_Graph9->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph9->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph9->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph9);
   
   //gre->Draw("p5");
   
   gre = new TGraphErrors(8);
   gre->SetName("Graph");
   gre->SetTitle("Graph");

   ci = TColor::GetColor("#009900");
   gre->SetFillColor(ci);
   gre->SetFillStyle(3001);

   ci = TColor::GetColor("#009900");
   gre->SetLineColor(ci);
   gre->SetPoint(0,21.294,0.004956781);
   gre->SetPointError(0,0.639,0.0002927028);
   gre->SetPoint(1,16.513,0.004693559);
   gre->SetPointError(1,0.495,0.000273759);
   gre->SetPoint(2,13.457,0.00472104);
   gre->SetPointError(2,0.404,0.0003280602);
   gre->SetPoint(3,11.507,0.00446398);
   gre->SetPointError(3,0.345,0.0002597643);
   gre->SetPoint(4,8.99,0.004165056);
   gre->SetPointError(4,0.271,0.0002399933);
   gre->SetPoint(5,6.057,0.003705069);
   gre->SetPointError(5,0.19,0.0002066062);
   gre->SetPoint(6,3.897,0.003070101);
   gre->SetPointError(6,0.143,0.0001814318);
   gre->SetPoint(7,2.261,0.00221639);
   gre->SetPointError(7,0.117,0.000155551);

   //pp
   gre_pp = new TGraphErrors(8);
   gre_pp->SetName("Graph_pp");
   gre_pp->SetTitle("Graph_pp");

   ci = TColor::GetColor("#009900");
   gre_pp->SetFillColor(ci);
   gre_pp->SetFillStyle(3001);

   ci = TColor::GetColor("#009900");
   gre_pp->SetLineColor(ci);
   gre_pp->SetMarkerStyle(20);
   gre_pp->SetMarkerSize(msize);
   gre_pp->SetMarkerColor(ci);

   gre_pp->SetPoint(0,21.294/1.15,0.004956781);
   gre_pp->SetPoint(1,16.513/1.15,0.004693559);
   gre_pp->SetPoint(2,13.457/1.15,0.00472104);
   gre_pp->SetPoint(3,11.507/1.15,0.00446398);
   gre_pp->SetPoint(4,8.99/1.15,0.004165056);
   gre_pp->SetPoint(5,6.057/1.15,0.003705069);
   gre_pp->SetPoint(6,3.897/1.15,0.003070101);
   gre_pp->SetPoint(7,2.261/1.15,0.00221639);

   gre_pp->Draw("p l ");
   
   TH1F *Graph_Graph10 = new TH1F("Graph_Graph10","Graph",100,0.1651,23.9119);
   Graph_Graph10->SetMinimum(0.001741975);
   Graph_Graph10->SetMaximum(0.005568348);
   Graph_Graph10->SetDirectory(0);
   Graph_Graph10->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph10->SetLineColor(ci);
   Graph_Graph10->GetXaxis()->SetLabelFont(42);
   Graph_Graph10->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph10->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph10->GetXaxis()->SetTitleFont(42);
   Graph_Graph10->GetYaxis()->SetLabelFont(42);
   Graph_Graph10->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph10->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph10->GetYaxis()->SetTitleFont(42);
   Graph_Graph10->GetZaxis()->SetLabelFont(42);
   Graph_Graph10->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph10->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph10->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph10);
   
   //gre->Draw("p5");
   
   gre = new TGraphErrors(8);
   gre->SetName("Graph");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);

   ci = TColor::GetColor("#009900");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#009900");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(8);
   gre->SetPoint(0,21.294,0.004956781);
   gre->SetPointError(0,0,8.307374e-05);
   gre->SetPoint(1,16.513,0.004693559);
   gre->SetPointError(1,0,4.682106e-05);
   gre->SetPoint(2,13.457,0.00472104);
   gre->SetPointError(2,0,4.814255e-05);
   gre->SetPoint(3,11.507,0.00446398);
   gre->SetPointError(3,0,5.312203e-05);
   gre->SetPoint(4,8.99,0.004165056);
   gre->SetPointError(4,0,3.76588e-05);
   gre->SetPoint(5,6.057,0.003705069);
   gre->SetPointError(5,0,3.786656e-05);
   gre->SetPoint(6,3.897,0.003070101);
   gre->SetPointError(6,0,4.180637e-05);
   gre->SetPoint(7,2.261,0.00221639);
   gre->SetPointError(7,0,4.262234e-05);
   
   TH1F *Graph_Graph11 = new TH1F("Graph_Graph11","Graph",100,0.3577,23.1973);
   Graph_Graph11->SetMinimum(0.001887159);
   Graph_Graph11->SetMaximum(0.005326463);
   Graph_Graph11->SetDirectory(0);
   Graph_Graph11->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph11->SetLineColor(ci);
   Graph_Graph11->GetXaxis()->SetLabelFont(42);
   Graph_Graph11->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph11->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph11->GetXaxis()->SetTitleFont(42);
   Graph_Graph11->GetYaxis()->SetLabelFont(42);
   Graph_Graph11->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph11->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph11->GetYaxis()->SetTitleFont(42);
   Graph_Graph11->GetZaxis()->SetLabelFont(42);
   Graph_Graph11->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph11->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph11->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph11);
   
   //gre->Draw("p");
   
   leg = new TLegend(0.16,0.16,0.55,0.35,NULL,"brNDC");
   leg->SetBorderSize(1);
   leg->SetTextSize(0.033);
   leg->SetLineColor(0);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   entry=leg->AddEntry("NULL","#bf{MC productions - pp #sqrt{s}=7TeV}","h");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("g_MC","Pythia6-Perugia2011-NoCR","l");

   ci = TColor::GetColor("#336633");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("g_MC","Pythia6-Perugia2011-WithCR","l");

   ci = TColor::GetColor("#00cc00");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("g_MC","Pythia8-Monash-WithCR","l");

   ci = TColor::GetColor("#9933ff");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   leg->Draw();
   
   gre = new TGraphErrors(15);
   gre->SetName("g_MC");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);

   ci = TColor::GetColor("#336633");
   gre->SetLineColor(ci);
   gre->SetLineWidth(2);

   ci = TColor::GetColor("#9933ff");
   gre->SetMarkerColor(ci);
   gre->SetPoint(0,1.031077,0.001680745);
   gre->SetPointError(0,0,0);
   gre->SetPoint(1,1.154628,0.001878577);
   gre->SetPointError(1,0,0);
   gre->SetPoint(2,1.378037,0.00203928);
   gre->SetPointError(2,0,0);
   gre->SetPoint(3,1.850643,0.002181559);
   gre->SetPointError(3,0,0);
   gre->SetPoint(4,2.625787,0.002299367);
   gre->SetPointError(4,0,0);
   gre->SetPoint(5,3.58848,0.002363747);
   gre->SetPointError(5,0,0);
   gre->SetPoint(6,5.029962,0.002408833);
   gre->SetPointError(6,0,0);
   gre->SetPoint(7,7.037786,0.002431342);
   gre->SetPointError(7,0,0);
   gre->SetPoint(8,9.296931,0.00244924);
   gre->SetPointError(8,0,0);
   gre->SetPoint(9,11.12944,0.002453889);
   gre->SetPointError(9,0,0);
   gre->SetPoint(10,13.10306,0.002461807);
   gre->SetPointError(10,0,0);
   gre->SetPoint(11,16.04976,0.002459602);
   gre->SetPointError(11,0,0);
   gre->SetPoint(12,19.11507,0.002460675);
   gre->SetPointError(12,0,0);
   gre->SetPoint(13,22.29099,0.002462098);
   gre->SetPointError(13,0,0);
   gre->SetPoint(14,25.56513,0.002456875);
   gre->SetPointError(14,0,0);
   
   TH1F *Graph_g_MC12 = new TH1F("Graph_g_MC12","Graph",100,0.9279689,28.01854);
   Graph_g_MC12->SetMinimum(0.001602609);
   Graph_g_MC12->SetMaximum(0.002540233);
   Graph_g_MC12->SetDirectory(0);
   Graph_g_MC12->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_g_MC12->SetLineColor(ci);
   Graph_g_MC12->GetXaxis()->SetLabelFont(42);
   Graph_g_MC12->GetXaxis()->SetLabelSize(0.035);
   Graph_g_MC12->GetXaxis()->SetTitleSize(0.035);
   Graph_g_MC12->GetXaxis()->SetTitleFont(42);
   Graph_g_MC12->GetYaxis()->SetLabelFont(42);
   Graph_g_MC12->GetYaxis()->SetLabelSize(0.035);
   Graph_g_MC12->GetYaxis()->SetTitleSize(0.035);
   Graph_g_MC12->GetYaxis()->SetTitleFont(42);
   Graph_g_MC12->GetZaxis()->SetLabelFont(42);
   Graph_g_MC12->GetZaxis()->SetLabelSize(0.035);
   Graph_g_MC12->GetZaxis()->SetTitleSize(0.035);
   Graph_g_MC12->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_g_MC12);
   
   gre->Draw("l");
   
   gre = new TGraphErrors(15);
   gre->SetName("g_MC");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);

   ci = TColor::GetColor("#00cc00");
   gre->SetLineColor(ci);
   gre->SetLineWidth(2);

   ci = TColor::GetColor("#9933ff");
   gre->SetMarkerColor(ci);
   gre->SetPoint(0,1.069422,0.001687237);
   gre->SetPointError(0,0,0);
   gre->SetPoint(1,1.204354,0.001898569);
   gre->SetPointError(1,0,0);
   gre->SetPoint(2,1.452607,0.002066662);
   gre->SetPointError(2,0,0);
   gre->SetPoint(3,1.945297,0.002182933);
   gre->SetPointError(3,0,0);
   gre->SetPoint(4,2.720932,0.002254059);
   gre->SetPointError(4,0,0);
   gre->SetPoint(5,3.721593,0.002287185);
   gre->SetPointError(5,0,0);
   gre->SetPoint(6,5.166269,0.002300008);
   gre->SetPointError(6,0,0);
   gre->SetPoint(7,7.050058,0.002312886);
   gre->SetPointError(7,0,0);
   gre->SetPoint(8,9.128829,0.002320303);
   gre->SetPointError(8,0,0);
   gre->SetPoint(9,10.75438,0.002313706);
   gre->SetPointError(9,0,0);
   gre->SetPoint(10,12.36954,0.002316996);
   gre->SetPointError(10,0,0);
   gre->SetPoint(11,14.68195,0.002312115);
   gre->SetPointError(11,0,0);
   gre->SetPoint(12,16.96299,0.002310045);
   gre->SetPointError(12,0,0);
   gre->SetPoint(13,19.20945,0.002291208);
   gre->SetPointError(13,0,0);
   gre->SetPoint(14,21.45484,0.002292199);
   gre->SetPointError(14,0,0);
   
   TH1F *Graph_g_MC13 = new TH1F("Graph_g_MC13","Graph",100,0.9624798,23.49338);
   Graph_g_MC13->SetMinimum(0.00162393);
   Graph_g_MC13->SetMaximum(0.00238361);
   Graph_g_MC13->SetDirectory(0);
   Graph_g_MC13->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_g_MC13->SetLineColor(ci);
   Graph_g_MC13->GetXaxis()->SetLabelFont(42);
   Graph_g_MC13->GetXaxis()->SetLabelSize(0.035);
   Graph_g_MC13->GetXaxis()->SetTitleSize(0.035);
   Graph_g_MC13->GetXaxis()->SetTitleFont(42);
   Graph_g_MC13->GetYaxis()->SetLabelFont(42);
   Graph_g_MC13->GetYaxis()->SetLabelSize(0.035);
   Graph_g_MC13->GetYaxis()->SetTitleSize(0.035);
   Graph_g_MC13->GetYaxis()->SetTitleFont(42);
   Graph_g_MC13->GetZaxis()->SetLabelFont(42);
   Graph_g_MC13->GetZaxis()->SetLabelSize(0.035);
   Graph_g_MC13->GetZaxis()->SetTitleSize(0.035);
   Graph_g_MC13->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_g_MC13);
   
   gre->Draw("l");
   
   gre = new TGraphErrors(15);
   gre->SetName("g_MC");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);

   ci = TColor::GetColor("#9933ff");
   gre->SetLineColor(ci);
   gre->SetLineWidth(2);

   ci = TColor::GetColor("#9933ff");
   gre->SetMarkerColor(ci);
   gre->SetPoint(0,1.544728,0.001353637);
   gre->SetPointError(0,0,0);
   gre->SetPoint(1,1.69234,0.001556944);
   gre->SetPointError(1,0,0);
   gre->SetPoint(2,1.880837,0.001760228);
   gre->SetPointError(2,0,0);
   gre->SetPoint(3,2.152912,0.001959728);
   gre->SetPointError(3,0,0);
   gre->SetPoint(4,2.520702,0.002083955);
   gre->SetPointError(4,0,0);
   gre->SetPoint(5,3.17332,0.002109022);
   gre->SetPointError(5,0,0);
   gre->SetPoint(6,4.524881,0.002113438);
   gre->SetPointError(6,0,0);
   gre->SetPoint(7,6.231306,0.002119296);
   gre->SetPointError(7,0,0);
   gre->SetPoint(8,8.077805,0.00211583);
   gre->SetPointError(8,0,0);
   gre->SetPoint(9,9.616416,0.002114177);
   gre->SetPointError(9,0,0);
   gre->SetPoint(10,11.25603,0.002108617);
   gre->SetPointError(10,0,0);
   gre->SetPoint(11,13.67131,0.002108632);
   gre->SetPointError(11,0,0);
   gre->SetPoint(12,16.12758,0.002103963);
   gre->SetPointError(12,0,0);
   gre->SetPoint(13,18.60224,0.002103709);
   gre->SetPointError(13,0,0);
   gre->SetPoint(14,21.07411,0.002088573);
   gre->SetPointError(14,0,0);
   
   TH1F *Graph_g_MC14 = new TH1F("Graph_g_MC14","Graph",100,1.390255,23.02704);
   Graph_g_MC14->SetMinimum(0.001277072);
   Graph_g_MC14->SetMaximum(0.002195862);
   Graph_g_MC14->SetDirectory(0);
   Graph_g_MC14->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_g_MC14->SetLineColor(ci);
   Graph_g_MC14->GetXaxis()->SetLabelFont(42);
   Graph_g_MC14->GetXaxis()->SetLabelSize(0.035);
   Graph_g_MC14->GetXaxis()->SetTitleSize(0.035);
   Graph_g_MC14->GetXaxis()->SetTitleFont(42);
   Graph_g_MC14->GetYaxis()->SetLabelFont(42);
   Graph_g_MC14->GetYaxis()->SetLabelSize(0.035);
   Graph_g_MC14->GetYaxis()->SetTitleSize(0.035);
   Graph_g_MC14->GetYaxis()->SetTitleFont(42);
   Graph_g_MC14->GetZaxis()->SetLabelFont(42);
   Graph_g_MC14->GetZaxis()->SetLabelSize(0.035);
   Graph_g_MC14->GetZaxis()->SetTitleSize(0.035);
   Graph_g_MC14->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_g_MC14);

   greAA1->Draw("p l ");
   gre_pA1->Draw("p l ");
   
   gre->Draw("l");
   XiOverPi->Modified();
   XiOverPi->cd();
   XiOverPi->SetSelected(XiOverPi);
}
