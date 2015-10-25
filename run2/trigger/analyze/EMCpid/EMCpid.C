#define EMCpid_cxx
#include "EMCpid.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>


#include <TH2F.h>
#include <TLorentzVector.h>
#include <TArrayI.h>
#include <TDatabasePDG.h>

#include <iostream>
using namespace std;

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

	TFile *fout = new TFile("EMCpid.root", "RECREATE");
	fout->cd();
	TH2F *hepp = new TH2F("hepp", "hepp;p;E/p", 100, 0, 100, 30, 0, 3);

	Int_t cpids[] = {
		11, 13, 22, 111, 211, 221, 321, 2212, 2112,
		-11, -13, -22, -111, -211, -221, -321, -2212, -2112		
	};

	TArrayI pids(18, cpids);
	TH2F *heppid[18];

	TDatabasePDG db;

	for (Int_t i = 0; i < pids.GetSize(); i++)
	{
		TParticlePDG *ppdg = db.GetParticle(pids.GetAt(i));
		TString pname = "unknown";
		if (ppdg)
		{
			pname = ppdg->GetName();
		}
		TString hname  = TString::Format("hepp_pdg_%1.0f", pids.GetAt(i));
		TString htitle = TString::Format("pdg %1.0f %s;p;E/p", pids.GetAt(i), pname.Data());
		heppid[i]      = new TH2F(hname, htitle, 100, 0, 100, 30, 0, 3);
	}
	Long64_t nentries = fChain->GetEntriesFast();

	Long64_t nbytes = 0, nb = 0;
	for (Long64_t jentry = 0; jentry < nentries; jentry++) {
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break;
		nb = fChain->GetEntry(jentry);   nbytes += nb;
		// if (Cut(ientry) < 0) continue;
		TLorentzVector p;
		p.SetPxPyPzE(pgx, pgy, pgz, energy);
		TVector3 er(erx, ery, erz);
		if (er.Mag() <= 1e-3)
			continue;
		hepp->Fill(p.P(), er.Mag() / p.P());
		for (Int_t i = 0; i < pids.GetSize(); i++)
		{
			if (pdg == pids[i])
			{
				heppid[i]->Fill(p.P(), er.Mag() / p.P());
			}
		}
	}

	fout->Write();
	fout->Close();

}
