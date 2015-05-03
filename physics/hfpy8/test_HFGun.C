void test_HFGun()
{
	//Note: QUARKS d 1 u 2 s 3 c 4 b 5 t 6 b' 7 t' 8
	//      GLUE is 21 and is is default
	TH1D *h = new TH1D("h","h",1,20,21);
	h->Fill(20.5);
	HFGun p;
	p.SetSpectrum(h, 4); // set the input spectrum and the fPartonID
	//p.SetPartonID(2) - alternative...
	Int_t nevents = 10000;
	p.Generate(nevents);

	TFile *fin = new TFile("hfgun_default_output.root");
	TNtuple *tnh = (TNtuple*)fin->Get("tnh");	
	tnh->Draw("hpt/qpt>>htemp", "nd==0", "same");
	TH1 *hh = (TH1*)gDirectory->Get("htemp");
	hh->Scale(1./nevents);
	hh->SetLineColor(kRed);
	hh->SetTitle("z: hadrons from charm");

	TNtuple *tne = (TNtuple*)fin->Get("tne");	
	tne->Draw("ept/qpt>>htemp1", "", "same");
	TH1 *hh = (TH1*)gDirectory->Get("htemp1");
	hh->Scale(1./nevents);
	hh->SetTitle("z: electrons from charm");
	gPad->BuildLegend(0.1,0.6,0.4,0.9);
	gPad->Print("test_HFGun.pdf", ".pdf");
}
