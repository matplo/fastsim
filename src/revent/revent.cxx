#include "revent.h"
#include "header.h"

#include <TFile.h>
#include <TTree.h>
#include <TLorentzVector.h>


#include <iostream> // needed for io
using namespace std;
//using namespace fastjet; - conflicts with root
namespace fj = fastjet;
//using namespace Pythia8; - conflicts with root
namespace py = Pythia8;

REvent::REvent()
	: fout(0)
	, tree(0)
	, pPythia(0)
{
	;
}

REvent::~REvent()
{
	fout->Close();
	fout->Delete();
}

void REvent::Init(const char *foutname)
{
	fout = new TFile(foutname, "RECREATE");
	fout->cd();

	tree = new TTree("t", "t");

}

void REvent::Write()
{
	fout->Write();
}

void REvent::FillBranch(const char* name, std::vector <fj::PseudoJet> in)
{
	//std::vector<TLorentzVector> *pv = new std::vector<TLorentzVector>;
	std::vector<TLorentzVector> *pv = 0;
	TBranch *b = tree->GetBranch(name);
	if (b == 0)
	{
		b = tree->Branch(name, &pv, 1);
	}
	b->SetAddress(&pv);
	std::vector<TLorentzVector> &v  = *pv;
	TLorentzVector tlv;
	for (int i = 0; i < in.size(); ++i)
	{
		//tlv.SetPtEtaPhiE(in[i].perp(), in[i].eta(), in[i].phi_02pi(), in[i].e());
		tlv.SetPtEtaPhiE(in[i].perp(), in[i].eta(), in[i].phi(), in[i].e());
		v.push_back(tlv);
	}
	b->Fill();
	pv->clear();
	delete pv;
}

void REvent::FinishEvent()
{
	//tree->Fill();
	Int_t n = tree->GetEntries();
	tree->SetEntries(n + 1);
}

void REvent::FillHeader(Header *hp)
{
	Header &h = *hp;
	TBranch *b = tree->GetBranch(h.fName.c_str());
	if (b == 0)
	{
		b = tree->Branch(h.fName.c_str(), &h.fValues[0], h.fVarNames.c_str());
	}
	b->SetAddress(&h.fValues[0]);
	b->Fill();
}

void REvent::SetPythia(Pythia8::Pythia *p)
{
	pPythia = p;
}

