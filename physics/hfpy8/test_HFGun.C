void test_HFGun()
{
	//Note: QUARKS d 1 u 2 s 3 c 4 b 5 t 6 b' 7 t' 8
	//      GLUE is 21 and is is default
	TH1D *h = new TH1D("h","h",1,20,21);
	h->Fill(20.5);
	HFGun p;
	int partonID = 5; // charm is 4
	p.SetSpectrum(h, partonID); // set the input spectrum and the fPartonID
	//p.SetPartonID(2) - alternative...
	Int_t nevents = 10000;
	p.Generate(nevents);

	TFile *fin = new TFile("hfgun_default_output.root");
	TNtuple *tnh = (TNtuple*)fin->Get("tnh");	
	tnh->Draw("hpt/qpt>>htemp", "nd==0", "same");
	TH1 *hh = (TH1*)gDirectory->Get("htemp");
	hh->Scale(1./nevents);
	hh->SetLineColor(kRed);
	hh->SetTitle(TString::Format("z: hadrons from partonID=%d",partonID));

	TNtuple *tne = (TNtuple*)fin->Get("tne");	
	tne->Draw("ept/qpt>>htemp1", "", "same");
	TH1 *hh = (TH1*)gDirectory->Get("htemp1");
	hh->Scale(1./nevents);
	hh->SetTitle(TString::Format("z: electrons from partonID=%d",partonID));
	gPad->BuildLegend(0.1,0.6,0.4,0.9);
	gPad->Print("test_HFGun.pdf", ".pdf");

	TFile *fin = new TFile("hfgun_default_output.root");
	TNtuple *tnh = (TNtuple*)fin->Get("tnh");	
	tnh->Draw("hpt/qpt>>htemp2", "nd==1", "same");
	TH1 *hh = (TH1*)gDirectory->Get("htemp2");
	hh->Scale(1./nevents);
	hh->SetLineColor(kRed);
	hh->SetTitle(TString::Format("z: hadrons from partonID=%d",partonID));

}
