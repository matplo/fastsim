void draw(TString f2name, Int_t color=2)
{
	TString testf2name = f2name;
	TString testf2name = gSystem->FindFile("./", testf2name);
	if (testf2name.Length() <= 0)
		return;
	TFile *f2 = TFile::Open(f2name.Data());
	TTree *t2 = (TTree*)f2->Get("t");
	TString mtune = f2name.ReplaceAll("tree-default_emctrig_out_R_0.4_femcpar_mtune_", "").ReplaceAll(".root", "");
	TString smt = "ht" + mtune.ReplaceAll(".", "p");
	TString sdraw = TString::Format("t.bgtrk.Pt()>>%s(100,0,100)", smt.Data());
	cout << sdraw << endl;
	t2->Draw(sdraw.Data(), "hd.cent < 10" , "same");
	TH1 *h = (TH1*)gDirectory->FindObject(smt.Data());
	h->Scale(1./t2->GetEntries());
	Double_t mean, mult;
	mean = h->GetMean();
	mult = h->GetEntries() / t2->GetEntries();
	TString newTitle = TString::Format("mtune = %s mean=%1.2f mult=%1.2f", mtune.ReplaceAll("p", ".").Data(), mean, mult);
	h->SetTitle(newTitle.Data());
	h->SetLineColor(color);	
}

test_mtune()
{
	Double_t mean, mult;
	TFile *f1 = TFile::Open("tree-default_emctrig_out_R_0.4_femcpar.root");
	TTree *t1 = (TTree*)f1->Get("t");
	t1->Draw("t.bgtrk.Pt()>>ht1(100,0,100)", "hd.cent < 10" , "");
	TH1 *h = (TH1*)gDirectory->FindObject("ht1");
	h->Scale(1./t1->GetEntries());
	mean = h->GetMean();
	mult = h->GetEntries() / t1->GetEntries();
	TString newTitle = TString::Format("mtune = 1.0 mean=%1.2f mult=%1.2f", mean, mult);
	h->SetTitle(newTitle.Data());

	draw("tree-default_emctrig_out_R_0.4_femcpar_mtune_0.8.root", 1);
	draw("tree-default_emctrig_out_R_0.4_femcpar_mtune_1.2.root", 2);
	draw("tree-default_emctrig_out_R_0.4_femcpar_mtune_2.0.root", 3);

	gPad->BuildLegend();
}
