void med_cent()
{
	TFile *fin = TFile::Open("/Volumes/MP/data/run2/trigger/2015-10-23/5TeV/hardQCD/default_emctrig_out_R_0.4_femc_0.1.root");
	TNtuple *triggers = (TNtuple*)fin->Get("triggers");

	TCanvas *tc = new TCanvas("med_cent", "med_cent", 500, 500);
	tc->Divide(2,1);
	tc->cd(1);
	triggers->Draw("JEmedECAL:npart>>hecal(100, 0, 100, 40, 0, 40)", "(JEmedECAL<60)*(xsec)", "colz");
	gPad->SetLogz();
	tc->cd(2);
	triggers->Draw("JEmedDCAL:npart>>hdcal(100, 0, 100, 40, 0, 40)", "(JEmedDCAL<37)*(xsec)", "colz");
	gPad->SetLogz();	
}