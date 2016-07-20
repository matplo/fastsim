void test_PGun()
{
	//Note: QUARKS d 1 u 2 s 3 c 4 b 5 t 6 b' 7 t' 8
	//      GLUE is 21 and is is default
	TH1D *h = new TH1D("h","h",1,20,21);
	h->Fill(20.5);
	PGun p;
	p.SetSpectrum(h, 2); // set the input spectrum and the fPartonID
	//p.SetPartonID(2) - alternative...
	p.Generate(10);
}
