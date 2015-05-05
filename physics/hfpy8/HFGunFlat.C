void HFGunFlat(Int_t nevents = 1e6, Double_t xmin = 0, Double_t xmax = 100)
{
	//Note: QUARKS d 1 u 2 s 3 c 4 b 5 t 6 b' 7 t' 8
	//      GLUE is 21 and is is default
	TH1D *h = new TH1D("h","h", 1, xmin, xmax);
	h->Fill((xmax - xmin)/2.);
	HFGun p;
	int partonID = 5; // charm is 4
	p.SetSpectrum(h, partonID); // set the input spectrum and the fPartonID
	//p.SetPartonID(2) - alternative...
	p.Generate(nevents);
}
