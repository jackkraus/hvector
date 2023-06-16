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
//#include "TTreePerfStats.h"

//Originally authored by the ROOT Team: https://root.cern/doc/master/hvector_8C.html

Int_t N = 1000000; // Number of events


void read()
{
 
   TFile *f = TFile::Open("hvector_unmodified.root","READ");
   if (!f) { return; }
 
   TTree *t; f->GetObject("tvec",t);
   std::vector<float> *vpx = 0;

 // TTreePerfStats* myIOStats = new TTreePerfStats("IOPerfStats", t);
 
   TBranch *bvpx = 0;
   t->SetBranchAddress("vpx",&vpx,&bvpx);
 
   for (Int_t i = 0; i < N; i++) {
      Long64_t tentry = t->LoadTree(i);
      bvpx->GetEntry(tentry);
 
   }
   
   // Since we passed the address of a local variable we need
   // to remove it.
   t->ResetBranchAddresses();

//   myIOStats->SaveAs("iostats.root");
//   f->Close();

}
 

void readModified()
{
 
   TFile *f = TFile::Open("hvector_modified.root","READ");
   if (!f) { return; }
	printf("1\n"); 
   TTree *t; f->GetObject("tvec",t);
   std::vector<float> *vpx_modified = 0; 
	printf("2\n"); 
   TBranch *bvpx_modified = 0;
   t->SetBranchAddress("vpx_modified",&vpx_modified,&bvpx_modified);
 
	printf("3\n"); 
   for (Int_t i = 0; i < N; i++) {
      Long64_t tentry = t->LoadTree(i);
      bvpx_modified->GetEntry(tentry);
 
   }

	printf("4\n"); 
   // Since we passed the address of a local variable we need
   // to remove it.
   t->ResetBranchAddresses();
}

 
int main()
{   
   gBenchmark = new TBenchmark();
 	printf("-2\n"); 
   // Timed read()
   gBenchmark->Start("read_hvector");
   read();  
	printf("-1\n");
   gBenchmark->Show("read_hvector");
 

	printf("0\n"); 
   // Timed readModified();
   gBenchmark->Start("read_hvector_modified");
   
	printf("0.1\n"); 
   readModified();
   gBenchmark->Show("read_hvector_modified");
   

   return 0;
}
