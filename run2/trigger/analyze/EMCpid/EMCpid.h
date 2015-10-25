//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sun Oct 25 02:46:19 2015 by ROOT version 5.34/34
// from TTree EMCalTree/A tree with emcal information
// found on file: EMCalTree.root
//////////////////////////////////////////////////////////

#ifndef EMCpid_h
#define EMCpid_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class EMCpid {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           pdg;
   Double_t        energy;
   Char_t          isUnique;
   Char_t          isPhysicalPrimary;
   Double_t        pgx;
   Double_t        pgy;
   Double_t        pgz;
   Double_t        prx;
   Double_t        pry;
   Double_t        prz;
   Double_t        erx;
   Double_t        ery;
   Double_t        erz;

   // List of branches
   TBranch        *b_pdg;   //!
   TBranch        *b_energy;   //!
   TBranch        *b_isUnique;   //!
   TBranch        *b_isPhysicalPrimary;   //!
   TBranch        *b_pgx;   //!
   TBranch        *b_pgy;   //!
   TBranch        *b_pgz;   //!
   TBranch        *b_prx;   //!
   TBranch        *b_pry;   //!
   TBranch        *b_prz;   //!
   TBranch        *b_erx;   //!
   TBranch        *b_ery;   //!
   TBranch        *b_erz;   //!

   EMCpid(TTree *tree=0);
   virtual ~EMCpid();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef EMCpid_cxx

EMCpid::EMCpid(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("EMCalTree.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("root_archive.zip#EMCalTree.root");
      }
      f->GetObject("EMCalTree",tree);

   }
   Init(tree);
}

EMCpid::~EMCpid()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t EMCpid::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t EMCpid::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void EMCpid::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("pdg", &pdg, &b_pdg);
   fChain->SetBranchAddress("energy", &energy, &b_energy);
   fChain->SetBranchAddress("isUnique", &isUnique, &b_isUnique);
   fChain->SetBranchAddress("isPhysicalPrimary", &isPhysicalPrimary, &b_isPhysicalPrimary);
   fChain->SetBranchAddress("pgx", &pgx, &b_pgx);
   fChain->SetBranchAddress("pgy", &pgy, &b_pgy);
   fChain->SetBranchAddress("pgz", &pgz, &b_pgz);
   fChain->SetBranchAddress("prx", &prx, &b_prx);
   fChain->SetBranchAddress("pry", &pry, &b_pry);
   fChain->SetBranchAddress("prz", &prz, &b_prz);
   fChain->SetBranchAddress("erx", &erx, &b_erx);
   fChain->SetBranchAddress("ery", &ery, &b_ery);
   fChain->SetBranchAddress("erz", &erz, &b_erz);
   Notify();
}

Bool_t EMCpid::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void EMCpid::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t EMCpid::Cut(Long64_t /*entry*/)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef EMCpid_cxx
