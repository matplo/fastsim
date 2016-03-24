#define EMCpid_cxx
#include "EMCpid.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

#include <TH2F.h>
#include <TLorentzVector.h>
#include <TArrayI.h>
#include <TDatabasePDG.h>

#include "EMPartResp.h"

#include <iostream>
using namespace std;

Bool_t EMCpid::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.
   cout << "[i] ::Notify() Tree number: " << fChain->GetTreeNumber() << endl;
   //<< " of " << fChain->GetNtrees() << endl;

   return kTRUE;
}

void EMCpid::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L EMCpid.C
//      Root > EMCpid t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
	if (fChain == 0) return;

	EMPartResp resp;

	TFile *fout = new TFile("EMCpid.root", "RECREATE");
	fout->cd();
	TH2F *hepp = new TH2F("hepp", "hepp;p;E/p", 100, 0, 100, 30, 0, 3);

	Int_t cpids[] = {
		11, 13, 22, 111, 211, 221, 321, 2212, 2112,
		-11, -13, -22, -111, -211, -221, -321, -2212, -2112		
	};

	TArrayI pids(18, cpids);
	TH2F *heppid[18];
	TH2F *hepid[18];

	TDatabasePDG db;

	for (Int_t i = 0; i < pids.GetSize(); i++)
	{
		TParticlePDG *ppdg = db.GetParticle(pids.GetAt(i));
		TString pname = "unknown";
		if (ppdg)
		{
			pname = ppdg->GetName();
		}
		TString hname, htitle;
		hname  = TString::Format("hepp_pdg_%1.0f", pids.GetAt(i));
		htitle = TString::Format("pdg %1.0f %s;p;E/p", pids.GetAt(i), pname.Data());
		heppid[i]      = new TH2F(hname, htitle, 100, 0, 100, 30, 0, 3);
		hname  = TString::Format("hep_pdg_%1.0f", pids.GetAt(i));
		htitle = TString::Format("pdg %1.0f %s;p;E", pids.GetAt(i), pname.Data());
		hepid[i]       = new TH2F(hname, htitle, 100, 0, 100, 300, 0, 300);
	}
	Long64_t nentries = fChain->GetEntriesFast();

	Long64_t nbytes = 0, nb = 0;
	for (Long64_t jentry = 0; jentry < nentries; jentry++) {
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break;
		nb = fChain->GetEntry(jentry);   nbytes += nb;

		if (isUnique < 1)
			continue;
		if (isPhysicalPrimary < 1)
			continue;

		// if (Cut(ientry) < 0) continue;
		TVector3 pg(pgx, pgy, pgz);
		Double_t m    = db.GetParticle(pdg)->Mass();
		Double_t egen = TMath::Sqrt(pg.Mag2() + m*m);

		TLorentzVector p;
		p.SetPxPyPzE(pgx, pgy, pgz, egen);

		TVector3 er(erx, ery, erz);
		if (er.Mag() < 0.150)
			continue;

		if (p.P() < 0.150)
			continue;

		// energy is the reconstructed energy
		// cout << er.Mag() - energy << endl; // this should be zero

		hepp->Fill(p.P(), er.Mag() / p.P());
		for (Int_t i = 0; i < pids.GetSize(); i++)
		{
			if (pdg == pids[i])
			{
				//if (pdg == 22)
				//	{
				//		cout << "p.Mass():" << p.M() << endl;
				//		cout << "p=" << p.P() << " e=" << p.E() << " recE=" << er.Mag() << endl;
				//	}
				heppid[i]->Fill(p.P(), er.Mag() / p.P());
				hepid[i]->Fill(p.P(), er.Mag());

				resp.Fill(pdg, p.P(), er.Mag());
			}
		}
	}

	fout->Write();
	fout->Close();

	resp.WriteToFile();

	cout << "[i] Loop done." << endl;

}
