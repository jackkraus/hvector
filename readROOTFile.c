#include <vector>
#include <cstdio> 

#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TFrame.h"
#include "TH1F.h"
#include "TBenchmark.h"
#include "TRandom.h"
#include "TSystem.h"
#include "TTreePerfStats.h"

//Originally authored by the ROOT Team: https://root.cern/doc/master/hvector_8C.html

Int_t N = 1000000; // Number of events


void read()
{
 
   TFile *f = TFile::Open("hvector_unmodified.root","READ");
   if (!f) { return; }
 
   TTree *t; f->GetObject("tvec",t);
   std::vector<float> *vpx = 0;

   TTreePerfStats* myIOStats = new TTreePerfStats("IOPerfStats", t);
 
   TBranch *bvpx = 0;
   t->SetBranchAddress("vpx",&vpx,&bvpx);
 
   for (Int_t i = 0; i < N; i++) {
      Long64_t tentry = t->LoadTree(i);
      bvpx->GetEntry(tentry);
 
   }
   // Since we passed the address of a local variable we need
   // to remove it.
   t->ResetBranchAddresses();

   myIOStats->SaveAs("iostats.root");
   f->Close();

}
 

void readModified()
{
 
   TFile *f = TFile::Open("hvector_modified.root","READ");
   if (!f) { return; }
   TTree *t; f->GetObject("tvec",t);
   std::vector<float> *vpx_modified = 0; 
   
   TTreePerfStats* myIOStats = new TTreePerfStats("IOPerfStats", t);
   
   TBranch *bvpx_modified = 0;
   t->SetBranchAddress("vpx_modified",&vpx_modified,&bvpx_modified);
 
   for (Int_t i = 0; i < N; i++) {
      Long64_t tentry = t->LoadTree(i);
      bvpx_modified->GetEntry(tentry);
 
   }
   

   
   // Since we passed the address of a local variable we need
   // to remove it.
   t->ResetBranchAddresses();


   myIOStats->SaveAs("iostats_modified.root");
   f->Close();
}

 
int main()
{   
   gBenchmark = new TBenchmark();
   // Timed read()
   gBenchmark->Start("read_hvector");
   read();  
   gBenchmark->Show("read_hvector");
 

   // Timed readModified();
   gBenchmark->Start("read_hvector_modified");
   readModified();
   gBenchmark->Show("read_hvector_modified");
   

   return 0;
}
