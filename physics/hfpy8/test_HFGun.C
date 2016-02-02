void test_HFGun_pid(int partonID = 5)
{
	TString sfname = TString::Format("hfgun_default_output_%d.root", partonID);

	TString tcname = sfname + TString("-canvas");
	TCanvas *tc = new TCanvas(tcname.Data(), tcname.Data());
	tc->cd();
	//Note: QUARKS d 1 u 2 s 3 c 4 b 5 t 6 b' 7 t' 8
	//      GLUE is 21 and is is default
	//TH1D *h = new TH1D("h","h",1,20,21);
	TH1D *h = new TH1D("h","h",1,0,100);
	h->Fill(20.5);
	HFGun p;
	p.SetOutputFileName(sfname.Data());
	p.SetSpectrum(h, partonID); // set the input spectrum and the fPartonID
	//p.SetPartonID(2) - alternative...
	Int_t nevents = 1000000;
	p.Generate(nevents);

	TFile *fin = new TFile(sfname.Data());
	TNtuple *tnh = (TNtuple*)fin->Get("tnh");	
	tnh->Draw("hpt/qpt>>htemp", "nd==0", "same");
	TH1 *hh = (TH1*)gDirectory->Get("htemp");
	hh->Scale(1./nevents);
	hh->SetLineColor(kRed);
	hh->SetLineStyle(partonID - 3);
	hh->SetTitle(TString::Format("z: FS hadrons from partonID=%d",partonID));
	hh->SetMaximum(10.);

	//TFile *fin = new TFile(sfname.Data());
	//TNtuple *tnh = (TNtuple*)fin->Get("tnh");	
	tnh->Draw("hpt/qpt>>htemp2", "nd>1", "same");
	TH1 *hh = (TH1*)gDirectory->Get("htemp2");
	hh->Scale(1./nevents);
	hh->SetLineColor(kMagenta);
	hh->SetLineStyle(partonID - 3);
	hh->SetTitle(TString::Format("z: decaying hadrons from partonID=%d",partonID));
	hh->SetMaximum(10.);

	TNtuple *tne = (TNtuple*)fin->Get("tne");	
	tne->Draw("ept/qpt>>htemp1", "", "same");
	TH1 *hh = (TH1*)gDirectory->Get("htemp1");
	hh->Scale(1./nevents);
	hh->SetLineColor(kBlue);
	hh->SetLineStyle(partonID - 3);
	hh->SetTitle(TString::Format("z: electrons from partonID=%d",partonID));
	hh->SetMaximum(10.);

	gPad->BuildLegend(0.1,0.6,0.4,0.9);
	gPad->SetLogy();
	tc->Update();
	TString pdfname = TString::Format("test_HFGun_%d.pdf", partonID);
	tc->Print(pdfname.Data(), ".pdf");

}

void test_HFGun()
{
	test_HFGun_pid(4);
	test_HFGun_pid(5);
}

