void draw_phieta()
{
	TString fname = "./default_emctrig_out.root";
	draw_phieta_file(fname.Data());
}

void draw_phieta_file(const char* fname)
{
	TFile *fin = TFile::Open(fname);
	TNtuple *jEMC = (TNtuple*)fin->Get("jets_hard_EMC");
	jEMC->Draw("phi:eta", "(nEv==-1 && pT > 20)", "colz");
	TNtuple *jEMCc = (TNtuple*)fin->Get("jets_hard_EMCc");
	jEMCc->Draw("phi:eta", "(nEv==-1 && pT > 20)", "BOX same");
	TNtuple *jDMCc = (TNtuple*)fin->Get("jets_hard_DMCc");
	jDMCc->Draw("phi:eta", "(nEv==-1 && pT > 20)", "BOX same");
}
