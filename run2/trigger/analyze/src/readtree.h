//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Oct 29 17:53:06 2015 by ROOT version 5.34/34
// from TTree t/t
// found on file: /Volumes/SAMSUNG/data/run2/trigger/2015-10-29/hardQCD/default_emctrig_out_R_0.4_femcpar.root
//////////////////////////////////////////////////////////

#ifndef ReadTree_h
#define ReadTree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include <TObject.h>
#include <TVector3.h>
#include <TLorentzVector.h>

// Fixed size dimensions of array or collections stored in the TTree if any.
   const Int_t kMaxp = 367;
   const Int_t kMaxbgcl = 816;
   const Int_t kMaxbgtrk = 2590;
   const Int_t kMaxtgEJE = 1617;
   const Int_t kMaxtgEGA = 1299;
   const Int_t kMaxtgDJE = 825;
   const Int_t kMaxtgDGA = 869;
   const Int_t kMaxtgbgEJE = 1617;
   const Int_t kMaxtgbgEGA = 1232;
   const Int_t kMaxtgbgDJE = 825;
   const Int_t kMaxtgbgDGA = 836;
   const Int_t kMaxj = 48;
   const Int_t kMaxjf = 54;
   const Int_t kMaxjE = 11;
   const Int_t kMaxjD = 8;
   const Int_t kMaxjr = 122;
   const Int_t kMaxjEr = 28;
   const Int_t kMaxjDr = 20;
   const Int_t kMaxg = 2;
   const Int_t kMaxgE = 1;
   const Int_t kMaxgD = 1;

class ReadTree {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Double_t        hd_xsec;
   Double_t        hd_cent;
   Double_t        hd_rho;
   Double_t        hd_sigma;
   Int_t           p_;
   UInt_t          p_fUniqueID[kMaxp];   //[p_]
   UInt_t          p_fBits[kMaxp];   //[p_]
   UInt_t          p_fP_fUniqueID[kMaxp];   //[p_]
   UInt_t          p_fP_fBits[kMaxp];   //[p_]
   Double_t        p_fP_fX[kMaxp];   //[p_]
   Double_t        p_fP_fY[kMaxp];   //[p_]
   Double_t        p_fP_fZ[kMaxp];   //[p_]
   Double_t        p_fE[kMaxp];   //[p_]
   Int_t           bgcl_;
   UInt_t          bgcl_fUniqueID[kMaxbgcl];   //[bgcl_]
   UInt_t          bgcl_fBits[kMaxbgcl];   //[bgcl_]
   UInt_t          bgcl_fP_fUniqueID[kMaxbgcl];   //[bgcl_]
   UInt_t          bgcl_fP_fBits[kMaxbgcl];   //[bgcl_]
   Double_t        bgcl_fP_fX[kMaxbgcl];   //[bgcl_]
   Double_t        bgcl_fP_fY[kMaxbgcl];   //[bgcl_]
   Double_t        bgcl_fP_fZ[kMaxbgcl];   //[bgcl_]
   Double_t        bgcl_fE[kMaxbgcl];   //[bgcl_]
   Int_t           bgtrk_;
   UInt_t          bgtrk_fUniqueID[kMaxbgtrk];   //[bgtrk_]
   UInt_t          bgtrk_fBits[kMaxbgtrk];   //[bgtrk_]
   UInt_t          bgtrk_fP_fUniqueID[kMaxbgtrk];   //[bgtrk_]
   UInt_t          bgtrk_fP_fBits[kMaxbgtrk];   //[bgtrk_]
   Double_t        bgtrk_fP_fX[kMaxbgtrk];   //[bgtrk_]
   Double_t        bgtrk_fP_fY[kMaxbgtrk];   //[bgtrk_]
   Double_t        bgtrk_fP_fZ[kMaxbgtrk];   //[bgtrk_]
   Double_t        bgtrk_fE[kMaxbgtrk];   //[bgtrk_]
   Double_t        tg_maxjECAL;
   Double_t        tg_maxjDCAL;
   Double_t        tg_maxgECAL;
   Double_t        tg_maxgDCAL;
   Double_t        tg_medjECAL;
   Double_t        tg_medjDCAL;
   Double_t        tg_medgECAL;
   Double_t        tg_medgDCAL;
   Int_t           tgEJE_;
   UInt_t          tgEJE_fUniqueID[kMaxtgEJE];   //[tgEJE_]
   UInt_t          tgEJE_fBits[kMaxtgEJE];   //[tgEJE_]
   UInt_t          tgEJE_fP_fUniqueID[kMaxtgEJE];   //[tgEJE_]
   UInt_t          tgEJE_fP_fBits[kMaxtgEJE];   //[tgEJE_]
   Double_t        tgEJE_fP_fX[kMaxtgEJE];   //[tgEJE_]
   Double_t        tgEJE_fP_fY[kMaxtgEJE];   //[tgEJE_]
   Double_t        tgEJE_fP_fZ[kMaxtgEJE];   //[tgEJE_]
   Double_t        tgEJE_fE[kMaxtgEJE];   //[tgEJE_]
   Int_t           tgEGA_;
   UInt_t          tgEGA_fUniqueID[kMaxtgEGA];   //[tgEGA_]
   UInt_t          tgEGA_fBits[kMaxtgEGA];   //[tgEGA_]
   UInt_t          tgEGA_fP_fUniqueID[kMaxtgEGA];   //[tgEGA_]
   UInt_t          tgEGA_fP_fBits[kMaxtgEGA];   //[tgEGA_]
   Double_t        tgEGA_fP_fX[kMaxtgEGA];   //[tgEGA_]
   Double_t        tgEGA_fP_fY[kMaxtgEGA];   //[tgEGA_]
   Double_t        tgEGA_fP_fZ[kMaxtgEGA];   //[tgEGA_]
   Double_t        tgEGA_fE[kMaxtgEGA];   //[tgEGA_]
   Int_t           tgDJE_;
   UInt_t          tgDJE_fUniqueID[kMaxtgDJE];   //[tgDJE_]
   UInt_t          tgDJE_fBits[kMaxtgDJE];   //[tgDJE_]
   UInt_t          tgDJE_fP_fUniqueID[kMaxtgDJE];   //[tgDJE_]
   UInt_t          tgDJE_fP_fBits[kMaxtgDJE];   //[tgDJE_]
   Double_t        tgDJE_fP_fX[kMaxtgDJE];   //[tgDJE_]
   Double_t        tgDJE_fP_fY[kMaxtgDJE];   //[tgDJE_]
   Double_t        tgDJE_fP_fZ[kMaxtgDJE];   //[tgDJE_]
   Double_t        tgDJE_fE[kMaxtgDJE];   //[tgDJE_]
   Int_t           tgDGA_;
   UInt_t          tgDGA_fUniqueID[kMaxtgDGA];   //[tgDGA_]
   UInt_t          tgDGA_fBits[kMaxtgDGA];   //[tgDGA_]
   UInt_t          tgDGA_fP_fUniqueID[kMaxtgDGA];   //[tgDGA_]
   UInt_t          tgDGA_fP_fBits[kMaxtgDGA];   //[tgDGA_]
   Double_t        tgDGA_fP_fX[kMaxtgDGA];   //[tgDGA_]
   Double_t        tgDGA_fP_fY[kMaxtgDGA];   //[tgDGA_]
   Double_t        tgDGA_fP_fZ[kMaxtgDGA];   //[tgDGA_]
   Double_t        tgDGA_fE[kMaxtgDGA];   //[tgDGA_]
   Double_t        tgbg_maxjECAL;
   Double_t        tgbg_maxjDCAL;
   Double_t        tgbg_maxgECAL;
   Double_t        tgbg_maxgDCAL;
   Double_t        tgbg_medjECAL;
   Double_t        tgbg_medjDCAL;
   Double_t        tgbg_medgECAL;
   Double_t        tgbg_medgDCAL;
   Int_t           tgbgEJE_;
   UInt_t          tgbgEJE_fUniqueID[kMaxtgbgEJE];   //[tgbgEJE_]
   UInt_t          tgbgEJE_fBits[kMaxtgbgEJE];   //[tgbgEJE_]
   UInt_t          tgbgEJE_fP_fUniqueID[kMaxtgbgEJE];   //[tgbgEJE_]
   UInt_t          tgbgEJE_fP_fBits[kMaxtgbgEJE];   //[tgbgEJE_]
   Double_t        tgbgEJE_fP_fX[kMaxtgbgEJE];   //[tgbgEJE_]
   Double_t        tgbgEJE_fP_fY[kMaxtgbgEJE];   //[tgbgEJE_]
   Double_t        tgbgEJE_fP_fZ[kMaxtgbgEJE];   //[tgbgEJE_]
   Double_t        tgbgEJE_fE[kMaxtgbgEJE];   //[tgbgEJE_]
   Int_t           tgbgEGA_;
   UInt_t          tgbgEGA_fUniqueID[kMaxtgbgEGA];   //[tgbgEGA_]
   UInt_t          tgbgEGA_fBits[kMaxtgbgEGA];   //[tgbgEGA_]
   UInt_t          tgbgEGA_fP_fUniqueID[kMaxtgbgEGA];   //[tgbgEGA_]
   UInt_t          tgbgEGA_fP_fBits[kMaxtgbgEGA];   //[tgbgEGA_]
   Double_t        tgbgEGA_fP_fX[kMaxtgbgEGA];   //[tgbgEGA_]
   Double_t        tgbgEGA_fP_fY[kMaxtgbgEGA];   //[tgbgEGA_]
   Double_t        tgbgEGA_fP_fZ[kMaxtgbgEGA];   //[tgbgEGA_]
   Double_t        tgbgEGA_fE[kMaxtgbgEGA];   //[tgbgEGA_]
   Int_t           tgbgDJE_;
   UInt_t          tgbgDJE_fUniqueID[kMaxtgbgDJE];   //[tgbgDJE_]
   UInt_t          tgbgDJE_fBits[kMaxtgbgDJE];   //[tgbgDJE_]
   UInt_t          tgbgDJE_fP_fUniqueID[kMaxtgbgDJE];   //[tgbgDJE_]
   UInt_t          tgbgDJE_fP_fBits[kMaxtgbgDJE];   //[tgbgDJE_]
   Double_t        tgbgDJE_fP_fX[kMaxtgbgDJE];   //[tgbgDJE_]
   Double_t        tgbgDJE_fP_fY[kMaxtgbgDJE];   //[tgbgDJE_]
   Double_t        tgbgDJE_fP_fZ[kMaxtgbgDJE];   //[tgbgDJE_]
   Double_t        tgbgDJE_fE[kMaxtgbgDJE];   //[tgbgDJE_]
   Int_t           tgbgDGA_;
   UInt_t          tgbgDGA_fUniqueID[kMaxtgbgDGA];   //[tgbgDGA_]
   UInt_t          tgbgDGA_fBits[kMaxtgbgDGA];   //[tgbgDGA_]
   UInt_t          tgbgDGA_fP_fUniqueID[kMaxtgbgDGA];   //[tgbgDGA_]
   UInt_t          tgbgDGA_fP_fBits[kMaxtgbgDGA];   //[tgbgDGA_]
   Double_t        tgbgDGA_fP_fX[kMaxtgbgDGA];   //[tgbgDGA_]
   Double_t        tgbgDGA_fP_fY[kMaxtgbgDGA];   //[tgbgDGA_]
   Double_t        tgbgDGA_fP_fZ[kMaxtgbgDGA];   //[tgbgDGA_]
   Double_t        tgbgDGA_fE[kMaxtgbgDGA];   //[tgbgDGA_]
   Int_t           j_;
   UInt_t          j_fUniqueID[kMaxj];   //[j_]
   UInt_t          j_fBits[kMaxj];   //[j_]
   UInt_t          j_fP_fUniqueID[kMaxj];   //[j_]
   UInt_t          j_fP_fBits[kMaxj];   //[j_]
   Double_t        j_fP_fX[kMaxj];   //[j_]
   Double_t        j_fP_fY[kMaxj];   //[j_]
   Double_t        j_fP_fZ[kMaxj];   //[j_]
   Double_t        j_fE[kMaxj];   //[j_]
   Int_t           jf_;
   UInt_t          jf_fUniqueID[kMaxjf];   //[jf_]
   UInt_t          jf_fBits[kMaxjf];   //[jf_]
   UInt_t          jf_fP_fUniqueID[kMaxjf];   //[jf_]
   UInt_t          jf_fP_fBits[kMaxjf];   //[jf_]
   Double_t        jf_fP_fX[kMaxjf];   //[jf_]
   Double_t        jf_fP_fY[kMaxjf];   //[jf_]
   Double_t        jf_fP_fZ[kMaxjf];   //[jf_]
   Double_t        jf_fE[kMaxjf];   //[jf_]
   Int_t           jE_;
   UInt_t          jE_fUniqueID[kMaxjE];   //[jE_]
   UInt_t          jE_fBits[kMaxjE];   //[jE_]
   UInt_t          jE_fP_fUniqueID[kMaxjE];   //[jE_]
   UInt_t          jE_fP_fBits[kMaxjE];   //[jE_]
   Double_t        jE_fP_fX[kMaxjE];   //[jE_]
   Double_t        jE_fP_fY[kMaxjE];   //[jE_]
   Double_t        jE_fP_fZ[kMaxjE];   //[jE_]
   Double_t        jE_fE[kMaxjE];   //[jE_]
   Int_t           jD_;
   UInt_t          jD_fUniqueID[kMaxjD];   //[jD_]
   UInt_t          jD_fBits[kMaxjD];   //[jD_]
   UInt_t          jD_fP_fUniqueID[kMaxjD];   //[jD_]
   UInt_t          jD_fP_fBits[kMaxjD];   //[jD_]
   Double_t        jD_fP_fX[kMaxjD];   //[jD_]
   Double_t        jD_fP_fY[kMaxjD];   //[jD_]
   Double_t        jD_fP_fZ[kMaxjD];   //[jD_]
   Double_t        jD_fE[kMaxjD];   //[jD_]
   Int_t           jr_;
   UInt_t          jr_fUniqueID[kMaxjr];   //[jr_]
   UInt_t          jr_fBits[kMaxjr];   //[jr_]
   UInt_t          jr_fP_fUniqueID[kMaxjr];   //[jr_]
   UInt_t          jr_fP_fBits[kMaxjr];   //[jr_]
   Double_t        jr_fP_fX[kMaxjr];   //[jr_]
   Double_t        jr_fP_fY[kMaxjr];   //[jr_]
   Double_t        jr_fP_fZ[kMaxjr];   //[jr_]
   Double_t        jr_fE[kMaxjr];   //[jr_]
   Int_t           jEr_;
   UInt_t          jEr_fUniqueID[kMaxjEr];   //[jEr_]
   UInt_t          jEr_fBits[kMaxjEr];   //[jEr_]
   UInt_t          jEr_fP_fUniqueID[kMaxjEr];   //[jEr_]
   UInt_t          jEr_fP_fBits[kMaxjEr];   //[jEr_]
   Double_t        jEr_fP_fX[kMaxjEr];   //[jEr_]
   Double_t        jEr_fP_fY[kMaxjEr];   //[jEr_]
   Double_t        jEr_fP_fZ[kMaxjEr];   //[jEr_]
   Double_t        jEr_fE[kMaxjEr];   //[jEr_]
   Int_t           jDr_;
   UInt_t          jDr_fUniqueID[kMaxjDr];   //[jDr_]
   UInt_t          jDr_fBits[kMaxjDr];   //[jDr_]
   UInt_t          jDr_fP_fUniqueID[kMaxjDr];   //[jDr_]
   UInt_t          jDr_fP_fBits[kMaxjDr];   //[jDr_]
   Double_t        jDr_fP_fX[kMaxjDr];   //[jDr_]
   Double_t        jDr_fP_fY[kMaxjDr];   //[jDr_]
   Double_t        jDr_fP_fZ[kMaxjDr];   //[jDr_]
   Double_t        jDr_fE[kMaxjDr];   //[jDr_]
   Int_t           g_;
   UInt_t          g_fUniqueID[kMaxg];   //[g_]
   UInt_t          g_fBits[kMaxg];   //[g_]
   UInt_t          g_fP_fUniqueID[kMaxg];   //[g_]
   UInt_t          g_fP_fBits[kMaxg];   //[g_]
   Double_t        g_fP_fX[kMaxg];   //[g_]
   Double_t        g_fP_fY[kMaxg];   //[g_]
   Double_t        g_fP_fZ[kMaxg];   //[g_]
   Double_t        g_fE[kMaxg];   //[g_]
   Int_t           gE_;
   UInt_t          gE_fUniqueID[kMaxgE];   //[gE_]
   UInt_t          gE_fBits[kMaxgE];   //[gE_]
   UInt_t          gE_fP_fUniqueID[kMaxgE];   //[gE_]
   UInt_t          gE_fP_fBits[kMaxgE];   //[gE_]
   Double_t        gE_fP_fX[kMaxgE];   //[gE_]
   Double_t        gE_fP_fY[kMaxgE];   //[gE_]
   Double_t        gE_fP_fZ[kMaxgE];   //[gE_]
   Double_t        gE_fE[kMaxgE];   //[gE_]
   Int_t           gD_;
   UInt_t          gD_fUniqueID[kMaxgD];   //[gD_]
   UInt_t          gD_fBits[kMaxgD];   //[gD_]
   UInt_t          gD_fP_fUniqueID[kMaxgD];   //[gD_]
   UInt_t          gD_fP_fBits[kMaxgD];   //[gD_]
   Double_t        gD_fP_fX[kMaxgD];   //[gD_]
   Double_t        gD_fP_fY[kMaxgD];   //[gD_]
   Double_t        gD_fP_fZ[kMaxgD];   //[gD_]
   Double_t        gD_fE[kMaxgD];   //[gD_]

   // List of branches
   TBranch        *b_hd;   //!
   TBranch        *b_p_;   //!
   TBranch        *b_p_fUniqueID;   //!
   TBranch        *b_p_fBits;   //!
   TBranch        *b_p_fP_fUniqueID;   //!
   TBranch        *b_p_fP_fBits;   //!
   TBranch        *b_p_fP_fX;   //!
   TBranch        *b_p_fP_fY;   //!
   TBranch        *b_p_fP_fZ;   //!
   TBranch        *b_p_fE;   //!
   TBranch        *b_bgcl_;   //!
   TBranch        *b_bgcl_fUniqueID;   //!
   TBranch        *b_bgcl_fBits;   //!
   TBranch        *b_bgcl_fP_fUniqueID;   //!
   TBranch        *b_bgcl_fP_fBits;   //!
   TBranch        *b_bgcl_fP_fX;   //!
   TBranch        *b_bgcl_fP_fY;   //!
   TBranch        *b_bgcl_fP_fZ;   //!
   TBranch        *b_bgcl_fE;   //!
   TBranch        *b_bgtrk_;   //!
   TBranch        *b_bgtrk_fUniqueID;   //!
   TBranch        *b_bgtrk_fBits;   //!
   TBranch        *b_bgtrk_fP_fUniqueID;   //!
   TBranch        *b_bgtrk_fP_fBits;   //!
   TBranch        *b_bgtrk_fP_fX;   //!
   TBranch        *b_bgtrk_fP_fY;   //!
   TBranch        *b_bgtrk_fP_fZ;   //!
   TBranch        *b_bgtrk_fE;   //!
   TBranch        *b_tg;   //!
   TBranch        *b_tgEJE_;   //!
   TBranch        *b_tgEJE_fUniqueID;   //!
   TBranch        *b_tgEJE_fBits;   //!
   TBranch        *b_tgEJE_fP_fUniqueID;   //!
   TBranch        *b_tgEJE_fP_fBits;   //!
   TBranch        *b_tgEJE_fP_fX;   //!
   TBranch        *b_tgEJE_fP_fY;   //!
   TBranch        *b_tgEJE_fP_fZ;   //!
   TBranch        *b_tgEJE_fE;   //!
   TBranch        *b_tgEGA_;   //!
   TBranch        *b_tgEGA_fUniqueID;   //!
   TBranch        *b_tgEGA_fBits;   //!
   TBranch        *b_tgEGA_fP_fUniqueID;   //!
   TBranch        *b_tgEGA_fP_fBits;   //!
   TBranch        *b_tgEGA_fP_fX;   //!
   TBranch        *b_tgEGA_fP_fY;   //!
   TBranch        *b_tgEGA_fP_fZ;   //!
   TBranch        *b_tgEGA_fE;   //!
   TBranch        *b_tgDJE_;   //!
   TBranch        *b_tgDJE_fUniqueID;   //!
   TBranch        *b_tgDJE_fBits;   //!
   TBranch        *b_tgDJE_fP_fUniqueID;   //!
   TBranch        *b_tgDJE_fP_fBits;   //!
   TBranch        *b_tgDJE_fP_fX;   //!
   TBranch        *b_tgDJE_fP_fY;   //!
   TBranch        *b_tgDJE_fP_fZ;   //!
   TBranch        *b_tgDJE_fE;   //!
   TBranch        *b_tgDGA_;   //!
   TBranch        *b_tgDGA_fUniqueID;   //!
   TBranch        *b_tgDGA_fBits;   //!
   TBranch        *b_tgDGA_fP_fUniqueID;   //!
   TBranch        *b_tgDGA_fP_fBits;   //!
   TBranch        *b_tgDGA_fP_fX;   //!
   TBranch        *b_tgDGA_fP_fY;   //!
   TBranch        *b_tgDGA_fP_fZ;   //!
   TBranch        *b_tgDGA_fE;   //!
   TBranch        *b_tgbg;   //!
   TBranch        *b_tgbgEJE_;   //!
   TBranch        *b_tgbgEJE_fUniqueID;   //!
   TBranch        *b_tgbgEJE_fBits;   //!
   TBranch        *b_tgbgEJE_fP_fUniqueID;   //!
   TBranch        *b_tgbgEJE_fP_fBits;   //!
   TBranch        *b_tgbgEJE_fP_fX;   //!
   TBranch        *b_tgbgEJE_fP_fY;   //!
   TBranch        *b_tgbgEJE_fP_fZ;   //!
   TBranch        *b_tgbgEJE_fE;   //!
   TBranch        *b_tgbgEGA_;   //!
   TBranch        *b_tgbgEGA_fUniqueID;   //!
   TBranch        *b_tgbgEGA_fBits;   //!
   TBranch        *b_tgbgEGA_fP_fUniqueID;   //!
   TBranch        *b_tgbgEGA_fP_fBits;   //!
   TBranch        *b_tgbgEGA_fP_fX;   //!
   TBranch        *b_tgbgEGA_fP_fY;   //!
   TBranch        *b_tgbgEGA_fP_fZ;   //!
   TBranch        *b_tgbgEGA_fE;   //!
   TBranch        *b_tgbgDJE_;   //!
   TBranch        *b_tgbgDJE_fUniqueID;   //!
   TBranch        *b_tgbgDJE_fBits;   //!
   TBranch        *b_tgbgDJE_fP_fUniqueID;   //!
   TBranch        *b_tgbgDJE_fP_fBits;   //!
   TBranch        *b_tgbgDJE_fP_fX;   //!
   TBranch        *b_tgbgDJE_fP_fY;   //!
   TBranch        *b_tgbgDJE_fP_fZ;   //!
   TBranch        *b_tgbgDJE_fE;   //!
   TBranch        *b_tgbgDGA_;   //!
   TBranch        *b_tgbgDGA_fUniqueID;   //!
   TBranch        *b_tgbgDGA_fBits;   //!
   TBranch        *b_tgbgDGA_fP_fUniqueID;   //!
   TBranch        *b_tgbgDGA_fP_fBits;   //!
   TBranch        *b_tgbgDGA_fP_fX;   //!
   TBranch        *b_tgbgDGA_fP_fY;   //!
   TBranch        *b_tgbgDGA_fP_fZ;   //!
   TBranch        *b_tgbgDGA_fE;   //!
   TBranch        *b_j_;   //!
   TBranch        *b_j_fUniqueID;   //!
   TBranch        *b_j_fBits;   //!
   TBranch        *b_j_fP_fUniqueID;   //!
   TBranch        *b_j_fP_fBits;   //!
   TBranch        *b_j_fP_fX;   //!
   TBranch        *b_j_fP_fY;   //!
   TBranch        *b_j_fP_fZ;   //!
   TBranch        *b_j_fE;   //!
   TBranch        *b_jf_;   //!
   TBranch        *b_jf_fUniqueID;   //!
   TBranch        *b_jf_fBits;   //!
   TBranch        *b_jf_fP_fUniqueID;   //!
   TBranch        *b_jf_fP_fBits;   //!
   TBranch        *b_jf_fP_fX;   //!
   TBranch        *b_jf_fP_fY;   //!
   TBranch        *b_jf_fP_fZ;   //!
   TBranch        *b_jf_fE;   //!
   TBranch        *b_jE_;   //!
   TBranch        *b_jE_fUniqueID;   //!
   TBranch        *b_jE_fBits;   //!
   TBranch        *b_jE_fP_fUniqueID;   //!
   TBranch        *b_jE_fP_fBits;   //!
   TBranch        *b_jE_fP_fX;   //!
   TBranch        *b_jE_fP_fY;   //!
   TBranch        *b_jE_fP_fZ;   //!
   TBranch        *b_jE_fE;   //!
   TBranch        *b_jD_;   //!
   TBranch        *b_jD_fUniqueID;   //!
   TBranch        *b_jD_fBits;   //!
   TBranch        *b_jD_fP_fUniqueID;   //!
   TBranch        *b_jD_fP_fBits;   //!
   TBranch        *b_jD_fP_fX;   //!
   TBranch        *b_jD_fP_fY;   //!
   TBranch        *b_jD_fP_fZ;   //!
   TBranch        *b_jD_fE;   //!
   TBranch        *b_jr_;   //!
   TBranch        *b_jr_fUniqueID;   //!
   TBranch        *b_jr_fBits;   //!
   TBranch        *b_jr_fP_fUniqueID;   //!
   TBranch        *b_jr_fP_fBits;   //!
   TBranch        *b_jr_fP_fX;   //!
   TBranch        *b_jr_fP_fY;   //!
   TBranch        *b_jr_fP_fZ;   //!
   TBranch        *b_jr_fE;   //!
   TBranch        *b_jEr_;   //!
   TBranch        *b_jEr_fUniqueID;   //!
   TBranch        *b_jEr_fBits;   //!
   TBranch        *b_jEr_fP_fUniqueID;   //!
   TBranch        *b_jEr_fP_fBits;   //!
   TBranch        *b_jEr_fP_fX;   //!
   TBranch        *b_jEr_fP_fY;   //!
   TBranch        *b_jEr_fP_fZ;   //!
   TBranch        *b_jEr_fE;   //!
   TBranch        *b_jDr_;   //!
   TBranch        *b_jDr_fUniqueID;   //!
   TBranch        *b_jDr_fBits;   //!
   TBranch        *b_jDr_fP_fUniqueID;   //!
   TBranch        *b_jDr_fP_fBits;   //!
   TBranch        *b_jDr_fP_fX;   //!
   TBranch        *b_jDr_fP_fY;   //!
   TBranch        *b_jDr_fP_fZ;   //!
   TBranch        *b_jDr_fE;   //!
   TBranch        *b_g_;   //!
   TBranch        *b_g_fUniqueID;   //!
   TBranch        *b_g_fBits;   //!
   TBranch        *b_g_fP_fUniqueID;   //!
   TBranch        *b_g_fP_fBits;   //!
   TBranch        *b_g_fP_fX;   //!
   TBranch        *b_g_fP_fY;   //!
   TBranch        *b_g_fP_fZ;   //!
   TBranch        *b_g_fE;   //!
   TBranch        *b_gE_;   //!
   TBranch        *b_gE_fUniqueID;   //!
   TBranch        *b_gE_fBits;   //!
   TBranch        *b_gE_fP_fUniqueID;   //!
   TBranch        *b_gE_fP_fBits;   //!
   TBranch        *b_gE_fP_fX;   //!
   TBranch        *b_gE_fP_fY;   //!
   TBranch        *b_gE_fP_fZ;   //!
   TBranch        *b_gE_fE;   //!
   TBranch        *b_gD_;   //!
   TBranch        *b_gD_fUniqueID;   //!
   TBranch        *b_gD_fBits;   //!
   TBranch        *b_gD_fP_fUniqueID;   //!
   TBranch        *b_gD_fP_fBits;   //!
   TBranch        *b_gD_fP_fX;   //!
   TBranch        *b_gD_fP_fY;   //!
   TBranch        *b_gD_fP_fZ;   //!
   TBranch        *b_gD_fE;   //!

   ReadTree(TTree *tree=0);
   virtual ~ReadTree();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);

   ClassDef(ReadTree, 1)
};

#endif

#ifdef ReadTree_cxx
ReadTree::ReadTree(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/Volumes/SAMSUNG/data/run2/trigger/2015-10-29/hardQCD/default_emctrig_out_R_0.4_femcpar.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/Volumes/SAMSUNG/data/run2/trigger/2015-10-29/hardQCD/default_emctrig_out_R_0.4_femcpar.root");
      }
      f->GetObject("t",tree);

   }
   Init(tree);
}

ReadTree::~ReadTree()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t ReadTree::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t ReadTree::LoadTree(Long64_t entry)
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

void ReadTree::Init(TTree *tree)
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

   fChain->SetBranchAddress("hd", &hd_xsec, &b_hd);
   fChain->SetBranchAddress("p", &p_, &b_p_);
   fChain->SetBranchAddress("p.fUniqueID", p_fUniqueID, &b_p_fUniqueID);
   fChain->SetBranchAddress("p.fBits", p_fBits, &b_p_fBits);
   fChain->SetBranchAddress("p.fP.fUniqueID", p_fP_fUniqueID, &b_p_fP_fUniqueID);
   fChain->SetBranchAddress("p.fP.fBits", p_fP_fBits, &b_p_fP_fBits);
   fChain->SetBranchAddress("p.fP.fX", p_fP_fX, &b_p_fP_fX);
   fChain->SetBranchAddress("p.fP.fY", p_fP_fY, &b_p_fP_fY);
   fChain->SetBranchAddress("p.fP.fZ", p_fP_fZ, &b_p_fP_fZ);
   fChain->SetBranchAddress("p.fE", p_fE, &b_p_fE);
   fChain->SetBranchAddress("bgcl", &bgcl_, &b_bgcl_);
   fChain->SetBranchAddress("bgcl.fUniqueID", bgcl_fUniqueID, &b_bgcl_fUniqueID);
   fChain->SetBranchAddress("bgcl.fBits", bgcl_fBits, &b_bgcl_fBits);
   fChain->SetBranchAddress("bgcl.fP.fUniqueID", bgcl_fP_fUniqueID, &b_bgcl_fP_fUniqueID);
   fChain->SetBranchAddress("bgcl.fP.fBits", bgcl_fP_fBits, &b_bgcl_fP_fBits);
   fChain->SetBranchAddress("bgcl.fP.fX", bgcl_fP_fX, &b_bgcl_fP_fX);
   fChain->SetBranchAddress("bgcl.fP.fY", bgcl_fP_fY, &b_bgcl_fP_fY);
   fChain->SetBranchAddress("bgcl.fP.fZ", bgcl_fP_fZ, &b_bgcl_fP_fZ);
   fChain->SetBranchAddress("bgcl.fE", bgcl_fE, &b_bgcl_fE);
   fChain->SetBranchAddress("bgtrk", &bgtrk_, &b_bgtrk_);
   fChain->SetBranchAddress("bgtrk.fUniqueID", bgtrk_fUniqueID, &b_bgtrk_fUniqueID);
   fChain->SetBranchAddress("bgtrk.fBits", bgtrk_fBits, &b_bgtrk_fBits);
   fChain->SetBranchAddress("bgtrk.fP.fUniqueID", bgtrk_fP_fUniqueID, &b_bgtrk_fP_fUniqueID);
   fChain->SetBranchAddress("bgtrk.fP.fBits", bgtrk_fP_fBits, &b_bgtrk_fP_fBits);
   fChain->SetBranchAddress("bgtrk.fP.fX", bgtrk_fP_fX, &b_bgtrk_fP_fX);
   fChain->SetBranchAddress("bgtrk.fP.fY", bgtrk_fP_fY, &b_bgtrk_fP_fY);
   fChain->SetBranchAddress("bgtrk.fP.fZ", bgtrk_fP_fZ, &b_bgtrk_fP_fZ);
   fChain->SetBranchAddress("bgtrk.fE", bgtrk_fE, &b_bgtrk_fE);
   fChain->SetBranchAddress("tg", &tg_maxjECAL, &b_tg);
   fChain->SetBranchAddress("tgEJE", &tgEJE_, &b_tgEJE_);
   fChain->SetBranchAddress("tgEJE.fUniqueID", tgEJE_fUniqueID, &b_tgEJE_fUniqueID);
   fChain->SetBranchAddress("tgEJE.fBits", tgEJE_fBits, &b_tgEJE_fBits);
   fChain->SetBranchAddress("tgEJE.fP.fUniqueID", tgEJE_fP_fUniqueID, &b_tgEJE_fP_fUniqueID);
   fChain->SetBranchAddress("tgEJE.fP.fBits", tgEJE_fP_fBits, &b_tgEJE_fP_fBits);
   fChain->SetBranchAddress("tgEJE.fP.fX", tgEJE_fP_fX, &b_tgEJE_fP_fX);
   fChain->SetBranchAddress("tgEJE.fP.fY", tgEJE_fP_fY, &b_tgEJE_fP_fY);
   fChain->SetBranchAddress("tgEJE.fP.fZ", tgEJE_fP_fZ, &b_tgEJE_fP_fZ);
   fChain->SetBranchAddress("tgEJE.fE", tgEJE_fE, &b_tgEJE_fE);
   fChain->SetBranchAddress("tgEGA", &tgEGA_, &b_tgEGA_);
   fChain->SetBranchAddress("tgEGA.fUniqueID", tgEGA_fUniqueID, &b_tgEGA_fUniqueID);
   fChain->SetBranchAddress("tgEGA.fBits", tgEGA_fBits, &b_tgEGA_fBits);
   fChain->SetBranchAddress("tgEGA.fP.fUniqueID", tgEGA_fP_fUniqueID, &b_tgEGA_fP_fUniqueID);
   fChain->SetBranchAddress("tgEGA.fP.fBits", tgEGA_fP_fBits, &b_tgEGA_fP_fBits);
   fChain->SetBranchAddress("tgEGA.fP.fX", tgEGA_fP_fX, &b_tgEGA_fP_fX);
   fChain->SetBranchAddress("tgEGA.fP.fY", tgEGA_fP_fY, &b_tgEGA_fP_fY);
   fChain->SetBranchAddress("tgEGA.fP.fZ", tgEGA_fP_fZ, &b_tgEGA_fP_fZ);
   fChain->SetBranchAddress("tgEGA.fE", tgEGA_fE, &b_tgEGA_fE);
   fChain->SetBranchAddress("tgDJE", &tgDJE_, &b_tgDJE_);
   fChain->SetBranchAddress("tgDJE.fUniqueID", tgDJE_fUniqueID, &b_tgDJE_fUniqueID);
   fChain->SetBranchAddress("tgDJE.fBits", tgDJE_fBits, &b_tgDJE_fBits);
   fChain->SetBranchAddress("tgDJE.fP.fUniqueID", tgDJE_fP_fUniqueID, &b_tgDJE_fP_fUniqueID);
   fChain->SetBranchAddress("tgDJE.fP.fBits", tgDJE_fP_fBits, &b_tgDJE_fP_fBits);
   fChain->SetBranchAddress("tgDJE.fP.fX", tgDJE_fP_fX, &b_tgDJE_fP_fX);
   fChain->SetBranchAddress("tgDJE.fP.fY", tgDJE_fP_fY, &b_tgDJE_fP_fY);
   fChain->SetBranchAddress("tgDJE.fP.fZ", tgDJE_fP_fZ, &b_tgDJE_fP_fZ);
   fChain->SetBranchAddress("tgDJE.fE", tgDJE_fE, &b_tgDJE_fE);
   fChain->SetBranchAddress("tgDGA", &tgDGA_, &b_tgDGA_);
   fChain->SetBranchAddress("tgDGA.fUniqueID", tgDGA_fUniqueID, &b_tgDGA_fUniqueID);
   fChain->SetBranchAddress("tgDGA.fBits", tgDGA_fBits, &b_tgDGA_fBits);
   fChain->SetBranchAddress("tgDGA.fP.fUniqueID", tgDGA_fP_fUniqueID, &b_tgDGA_fP_fUniqueID);
   fChain->SetBranchAddress("tgDGA.fP.fBits", tgDGA_fP_fBits, &b_tgDGA_fP_fBits);
   fChain->SetBranchAddress("tgDGA.fP.fX", tgDGA_fP_fX, &b_tgDGA_fP_fX);
   fChain->SetBranchAddress("tgDGA.fP.fY", tgDGA_fP_fY, &b_tgDGA_fP_fY);
   fChain->SetBranchAddress("tgDGA.fP.fZ", tgDGA_fP_fZ, &b_tgDGA_fP_fZ);
   fChain->SetBranchAddress("tgDGA.fE", tgDGA_fE, &b_tgDGA_fE);
   fChain->SetBranchAddress("tgbg", &tgbg_maxjECAL, &b_tgbg);
   fChain->SetBranchAddress("tgbgEJE", &tgbgEJE_, &b_tgbgEJE_);
   fChain->SetBranchAddress("tgbgEJE.fUniqueID", tgbgEJE_fUniqueID, &b_tgbgEJE_fUniqueID);
   fChain->SetBranchAddress("tgbgEJE.fBits", tgbgEJE_fBits, &b_tgbgEJE_fBits);
   fChain->SetBranchAddress("tgbgEJE.fP.fUniqueID", tgbgEJE_fP_fUniqueID, &b_tgbgEJE_fP_fUniqueID);
   fChain->SetBranchAddress("tgbgEJE.fP.fBits", tgbgEJE_fP_fBits, &b_tgbgEJE_fP_fBits);
   fChain->SetBranchAddress("tgbgEJE.fP.fX", tgbgEJE_fP_fX, &b_tgbgEJE_fP_fX);
   fChain->SetBranchAddress("tgbgEJE.fP.fY", tgbgEJE_fP_fY, &b_tgbgEJE_fP_fY);
   fChain->SetBranchAddress("tgbgEJE.fP.fZ", tgbgEJE_fP_fZ, &b_tgbgEJE_fP_fZ);
   fChain->SetBranchAddress("tgbgEJE.fE", tgbgEJE_fE, &b_tgbgEJE_fE);
   fChain->SetBranchAddress("tgbgEGA", &tgbgEGA_, &b_tgbgEGA_);
   fChain->SetBranchAddress("tgbgEGA.fUniqueID", tgbgEGA_fUniqueID, &b_tgbgEGA_fUniqueID);
   fChain->SetBranchAddress("tgbgEGA.fBits", tgbgEGA_fBits, &b_tgbgEGA_fBits);
   fChain->SetBranchAddress("tgbgEGA.fP.fUniqueID", tgbgEGA_fP_fUniqueID, &b_tgbgEGA_fP_fUniqueID);
   fChain->SetBranchAddress("tgbgEGA.fP.fBits", tgbgEGA_fP_fBits, &b_tgbgEGA_fP_fBits);
   fChain->SetBranchAddress("tgbgEGA.fP.fX", tgbgEGA_fP_fX, &b_tgbgEGA_fP_fX);
   fChain->SetBranchAddress("tgbgEGA.fP.fY", tgbgEGA_fP_fY, &b_tgbgEGA_fP_fY);
   fChain->SetBranchAddress("tgbgEGA.fP.fZ", tgbgEGA_fP_fZ, &b_tgbgEGA_fP_fZ);
   fChain->SetBranchAddress("tgbgEGA.fE", tgbgEGA_fE, &b_tgbgEGA_fE);
   fChain->SetBranchAddress("tgbgDJE", &tgbgDJE_, &b_tgbgDJE_);
   fChain->SetBranchAddress("tgbgDJE.fUniqueID", tgbgDJE_fUniqueID, &b_tgbgDJE_fUniqueID);
   fChain->SetBranchAddress("tgbgDJE.fBits", tgbgDJE_fBits, &b_tgbgDJE_fBits);
   fChain->SetBranchAddress("tgbgDJE.fP.fUniqueID", tgbgDJE_fP_fUniqueID, &b_tgbgDJE_fP_fUniqueID);
   fChain->SetBranchAddress("tgbgDJE.fP.fBits", tgbgDJE_fP_fBits, &b_tgbgDJE_fP_fBits);
   fChain->SetBranchAddress("tgbgDJE.fP.fX", tgbgDJE_fP_fX, &b_tgbgDJE_fP_fX);
   fChain->SetBranchAddress("tgbgDJE.fP.fY", tgbgDJE_fP_fY, &b_tgbgDJE_fP_fY);
   fChain->SetBranchAddress("tgbgDJE.fP.fZ", tgbgDJE_fP_fZ, &b_tgbgDJE_fP_fZ);
   fChain->SetBranchAddress("tgbgDJE.fE", tgbgDJE_fE, &b_tgbgDJE_fE);
   fChain->SetBranchAddress("tgbgDGA", &tgbgDGA_, &b_tgbgDGA_);
   fChain->SetBranchAddress("tgbgDGA.fUniqueID", tgbgDGA_fUniqueID, &b_tgbgDGA_fUniqueID);
   fChain->SetBranchAddress("tgbgDGA.fBits", tgbgDGA_fBits, &b_tgbgDGA_fBits);
   fChain->SetBranchAddress("tgbgDGA.fP.fUniqueID", tgbgDGA_fP_fUniqueID, &b_tgbgDGA_fP_fUniqueID);
   fChain->SetBranchAddress("tgbgDGA.fP.fBits", tgbgDGA_fP_fBits, &b_tgbgDGA_fP_fBits);
   fChain->SetBranchAddress("tgbgDGA.fP.fX", tgbgDGA_fP_fX, &b_tgbgDGA_fP_fX);
   fChain->SetBranchAddress("tgbgDGA.fP.fY", tgbgDGA_fP_fY, &b_tgbgDGA_fP_fY);
   fChain->SetBranchAddress("tgbgDGA.fP.fZ", tgbgDGA_fP_fZ, &b_tgbgDGA_fP_fZ);
   fChain->SetBranchAddress("tgbgDGA.fE", tgbgDGA_fE, &b_tgbgDGA_fE);
   fChain->SetBranchAddress("j", &j_, &b_j_);
   fChain->SetBranchAddress("j.fUniqueID", j_fUniqueID, &b_j_fUniqueID);
   fChain->SetBranchAddress("j.fBits", j_fBits, &b_j_fBits);
   fChain->SetBranchAddress("j.fP.fUniqueID", j_fP_fUniqueID, &b_j_fP_fUniqueID);
   fChain->SetBranchAddress("j.fP.fBits", j_fP_fBits, &b_j_fP_fBits);
   fChain->SetBranchAddress("j.fP.fX", j_fP_fX, &b_j_fP_fX);
   fChain->SetBranchAddress("j.fP.fY", j_fP_fY, &b_j_fP_fY);
   fChain->SetBranchAddress("j.fP.fZ", j_fP_fZ, &b_j_fP_fZ);
   fChain->SetBranchAddress("j.fE", j_fE, &b_j_fE);
   fChain->SetBranchAddress("jf", &jf_, &b_jf_);
   fChain->SetBranchAddress("jf.fUniqueID", jf_fUniqueID, &b_jf_fUniqueID);
   fChain->SetBranchAddress("jf.fBits", jf_fBits, &b_jf_fBits);
   fChain->SetBranchAddress("jf.fP.fUniqueID", jf_fP_fUniqueID, &b_jf_fP_fUniqueID);
   fChain->SetBranchAddress("jf.fP.fBits", jf_fP_fBits, &b_jf_fP_fBits);
   fChain->SetBranchAddress("jf.fP.fX", jf_fP_fX, &b_jf_fP_fX);
   fChain->SetBranchAddress("jf.fP.fY", jf_fP_fY, &b_jf_fP_fY);
   fChain->SetBranchAddress("jf.fP.fZ", jf_fP_fZ, &b_jf_fP_fZ);
   fChain->SetBranchAddress("jf.fE", jf_fE, &b_jf_fE);
   fChain->SetBranchAddress("jE", &jE_, &b_jE_);
   fChain->SetBranchAddress("jE.fUniqueID", jE_fUniqueID, &b_jE_fUniqueID);
   fChain->SetBranchAddress("jE.fBits", jE_fBits, &b_jE_fBits);
   fChain->SetBranchAddress("jE.fP.fUniqueID", jE_fP_fUniqueID, &b_jE_fP_fUniqueID);
   fChain->SetBranchAddress("jE.fP.fBits", jE_fP_fBits, &b_jE_fP_fBits);
   fChain->SetBranchAddress("jE.fP.fX", jE_fP_fX, &b_jE_fP_fX);
   fChain->SetBranchAddress("jE.fP.fY", jE_fP_fY, &b_jE_fP_fY);
   fChain->SetBranchAddress("jE.fP.fZ", jE_fP_fZ, &b_jE_fP_fZ);
   fChain->SetBranchAddress("jE.fE", jE_fE, &b_jE_fE);
   fChain->SetBranchAddress("jD", &jD_, &b_jD_);
   fChain->SetBranchAddress("jD.fUniqueID", jD_fUniqueID, &b_jD_fUniqueID);
   fChain->SetBranchAddress("jD.fBits", jD_fBits, &b_jD_fBits);
   fChain->SetBranchAddress("jD.fP.fUniqueID", jD_fP_fUniqueID, &b_jD_fP_fUniqueID);
   fChain->SetBranchAddress("jD.fP.fBits", jD_fP_fBits, &b_jD_fP_fBits);
   fChain->SetBranchAddress("jD.fP.fX", jD_fP_fX, &b_jD_fP_fX);
   fChain->SetBranchAddress("jD.fP.fY", jD_fP_fY, &b_jD_fP_fY);
   fChain->SetBranchAddress("jD.fP.fZ", jD_fP_fZ, &b_jD_fP_fZ);
   fChain->SetBranchAddress("jD.fE", jD_fE, &b_jD_fE);
   fChain->SetBranchAddress("jr", &jr_, &b_jr_);
   fChain->SetBranchAddress("jr.fUniqueID", jr_fUniqueID, &b_jr_fUniqueID);
   fChain->SetBranchAddress("jr.fBits", jr_fBits, &b_jr_fBits);
   fChain->SetBranchAddress("jr.fP.fUniqueID", jr_fP_fUniqueID, &b_jr_fP_fUniqueID);
   fChain->SetBranchAddress("jr.fP.fBits", jr_fP_fBits, &b_jr_fP_fBits);
   fChain->SetBranchAddress("jr.fP.fX", jr_fP_fX, &b_jr_fP_fX);
   fChain->SetBranchAddress("jr.fP.fY", jr_fP_fY, &b_jr_fP_fY);
   fChain->SetBranchAddress("jr.fP.fZ", jr_fP_fZ, &b_jr_fP_fZ);
   fChain->SetBranchAddress("jr.fE", jr_fE, &b_jr_fE);
   fChain->SetBranchAddress("jEr", &jEr_, &b_jEr_);
   fChain->SetBranchAddress("jEr.fUniqueID", jEr_fUniqueID, &b_jEr_fUniqueID);
   fChain->SetBranchAddress("jEr.fBits", jEr_fBits, &b_jEr_fBits);
   fChain->SetBranchAddress("jEr.fP.fUniqueID", jEr_fP_fUniqueID, &b_jEr_fP_fUniqueID);
   fChain->SetBranchAddress("jEr.fP.fBits", jEr_fP_fBits, &b_jEr_fP_fBits);
   fChain->SetBranchAddress("jEr.fP.fX", jEr_fP_fX, &b_jEr_fP_fX);
   fChain->SetBranchAddress("jEr.fP.fY", jEr_fP_fY, &b_jEr_fP_fY);
   fChain->SetBranchAddress("jEr.fP.fZ", jEr_fP_fZ, &b_jEr_fP_fZ);
   fChain->SetBranchAddress("jEr.fE", jEr_fE, &b_jEr_fE);
   fChain->SetBranchAddress("jDr", &jDr_, &b_jDr_);
   fChain->SetBranchAddress("jDr.fUniqueID", jDr_fUniqueID, &b_jDr_fUniqueID);
   fChain->SetBranchAddress("jDr.fBits", jDr_fBits, &b_jDr_fBits);
   fChain->SetBranchAddress("jDr.fP.fUniqueID", jDr_fP_fUniqueID, &b_jDr_fP_fUniqueID);
   fChain->SetBranchAddress("jDr.fP.fBits", jDr_fP_fBits, &b_jDr_fP_fBits);
   fChain->SetBranchAddress("jDr.fP.fX", jDr_fP_fX, &b_jDr_fP_fX);
   fChain->SetBranchAddress("jDr.fP.fY", jDr_fP_fY, &b_jDr_fP_fY);
   fChain->SetBranchAddress("jDr.fP.fZ", jDr_fP_fZ, &b_jDr_fP_fZ);
   fChain->SetBranchAddress("jDr.fE", jDr_fE, &b_jDr_fE);
   fChain->SetBranchAddress("g", &g_, &b_g_);
   fChain->SetBranchAddress("g.fUniqueID", g_fUniqueID, &b_g_fUniqueID);
   fChain->SetBranchAddress("g.fBits", g_fBits, &b_g_fBits);
   fChain->SetBranchAddress("g.fP.fUniqueID", g_fP_fUniqueID, &b_g_fP_fUniqueID);
   fChain->SetBranchAddress("g.fP.fBits", g_fP_fBits, &b_g_fP_fBits);
   fChain->SetBranchAddress("g.fP.fX", g_fP_fX, &b_g_fP_fX);
   fChain->SetBranchAddress("g.fP.fY", g_fP_fY, &b_g_fP_fY);
   fChain->SetBranchAddress("g.fP.fZ", g_fP_fZ, &b_g_fP_fZ);
   fChain->SetBranchAddress("g.fE", g_fE, &b_g_fE);
   fChain->SetBranchAddress("gE", &gE_, &b_gE_);
   fChain->SetBranchAddress("gE.fUniqueID", gE_fUniqueID, &b_gE_fUniqueID);
   fChain->SetBranchAddress("gE.fBits", gE_fBits, &b_gE_fBits);
   fChain->SetBranchAddress("gE.fP.fUniqueID", gE_fP_fUniqueID, &b_gE_fP_fUniqueID);
   fChain->SetBranchAddress("gE.fP.fBits", gE_fP_fBits, &b_gE_fP_fBits);
   fChain->SetBranchAddress("gE.fP.fX", gE_fP_fX, &b_gE_fP_fX);
   fChain->SetBranchAddress("gE.fP.fY", gE_fP_fY, &b_gE_fP_fY);
   fChain->SetBranchAddress("gE.fP.fZ", gE_fP_fZ, &b_gE_fP_fZ);
   fChain->SetBranchAddress("gE.fE", gE_fE, &b_gE_fE);
   fChain->SetBranchAddress("gD", &gD_, &b_gD_);
   fChain->SetBranchAddress("gD.fUniqueID", gD_fUniqueID, &b_gD_fUniqueID);
   fChain->SetBranchAddress("gD.fBits", gD_fBits, &b_gD_fBits);
   fChain->SetBranchAddress("gD.fP.fUniqueID", gD_fP_fUniqueID, &b_gD_fP_fUniqueID);
   fChain->SetBranchAddress("gD.fP.fBits", gD_fP_fBits, &b_gD_fP_fBits);
   fChain->SetBranchAddress("gD.fP.fX", gD_fP_fX, &b_gD_fP_fX);
   fChain->SetBranchAddress("gD.fP.fY", gD_fP_fY, &b_gD_fP_fY);
   fChain->SetBranchAddress("gD.fP.fZ", gD_fP_fZ, &b_gD_fP_fZ);
   fChain->SetBranchAddress("gD.fE", gD_fE, &b_gD_fE);
   Notify();
}

Bool_t ReadTree::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void ReadTree::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t ReadTree::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef ReadTree_cxx
