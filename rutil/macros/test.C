void test()
{
	write();
	read();
}

void write()
{
	gSystem->Load("libR2Util");

	std::vector<TLorentzVector> *v = 0;

	TFile *fout = new TFile("test.root", "RECREATE");
	TTree * test = new TTree("tree", "tree");
	TBranch *b = test->Branch("testB", &v, 1, 64000);

	std::vector<TLorentzVector> &vref = *v;

	for (Int_t i = 0; i < 10; i++)
	{
		vref.clear();
		for (Int_t j = 0; j < i+10; j++)
		{
			TLorentzVector tlv(j, j, j, j*i);
			vref.push_back(tlv);
		}
		b->SetAddress(&v);
		b->Fill();
		test->Fill();
	}
	fout->Write();
	fout->Close();
}

void read()
{
	gSystem->Load("libR2Util");

	std::vector<TLorentzVector> *v = 0;

	TFile *fin = new TFile("test.root");
	TTree * test = (TTree*)fin->Get("tree"));
	TBranch *b = test->SetBranchAddress("testB", &v);

	for (Int_t i = 0; i < test->GetEntries(); ++i)
	{
		test->GetEvent(i);
		cout << v->size() << endl;
	}
}