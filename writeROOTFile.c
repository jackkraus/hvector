#include <vector>
 
#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TFrame.h"
#include "TH1F.h"
#include "TBenchmark.h"
#include "TRandom.h"
#include "TSystem.h"

//Originally authored by the ROOT Team: https://root.cern/doc/master/hvector_8C.html

Int_t N = 1000000; // Number of events


void write() 
{
 
   TFile *f = TFile::Open("hvector_unmodified.root","RECREATE");
 
   if (!f) { return; }
 
   std::vector<float> vpx;
   std::vector<float> vpy;
   std::vector<float> vpz;
   std::vector<float> vrand;
 
   // Create a TTree
   TTree *t = new TTree("tvec","Tree with vectors");
   t->Branch("vpx",&vpx);
   t->Branch("vpy",&vpy);
   t->Branch("vpz",&vpz);
   t->Branch("vrand",&vrand);
 
 
   gRandom->SetSeed();
   for (Int_t i = 0; i < N; i++) {
      Int_t npx = (Int_t)(gRandom->Rndm(1)*15);
 
      vpx.clear();
      vpy.clear();
      vpz.clear();
      vrand.clear();
 
      for (Int_t j = 0; j < npx; ++j) {
 
         Float_t px,py,pz;
         gRandom->Rannor(px,py);
         pz = px*px + py*py;
         Float_t random = gRandom->Rndm(1);
 
         vpx.emplace_back(px);
         vpy.emplace_back(py);
         vpz.emplace_back(pz);
         vrand.emplace_back(random);
 
      }
      t->Fill();
   }
   
   t->Print();
   f->Write();
   
   delete f;
}
 
 
void writeModified() 
{
 
   TFile *f = TFile::Open("hvector_modified.root","RECREATE");
 
   if (!f) { return; }
 
   std::vector<float> vpx_modified;
   std::vector<float> vpy_modified;
   std::vector<float> vpz_modified;
   std::vector<float> vrand_modified;
 
   // Create a TTree
   TTree *t = new TTree("tvec","Tree with vectors");
   t->Branch("vpx_modified",&vpx_modified);
   t->Branch("vpy_modified",&vpy_modified);
   t->Branch("vpz_modified",&vpz_modified);
   t->Branch("vrand_modified",&vrand_modified);

   t->SetMaxBasketSize(128000); // The modification
 
   gRandom->SetSeed();
   for (Int_t i = 0; i < N; i++) {
      Int_t npx = (Int_t)(gRandom->Rndm(1)*15);
 
      vpx_modified.clear();
      vpy_modified.clear();
      vpz_modified.clear();
      vrand_modified.clear();
 
      for (Int_t j = 0; j < npx; ++j) {
 
         Float_t px,py,pz;
         gRandom->Rannor(px,py);
         pz = px*px + py*py;
         Float_t random = gRandom->Rndm(1);
 
         vpx_modified.emplace_back(px);
         vpy_modified.emplace_back(py);
         vpz_modified.emplace_back(pz);
         vrand_modified.emplace_back(random);
 
      }
      t->Fill();
   }
   
   t->Print();
   f->Write();
 
   delete f;
}
 
 
int main()
{   
	gBenchmark = new TBenchmark();

	   // Timed write()
   	gBenchmark->Start("write_hvector");
   	write();  
   	gBenchmark->Show("write_hvector");

  	   // Timed writeModified();
   	gBenchmark->Start("write_hvector_modified");
   	writeModified();
  	gBenchmark->Show("write_hvector_modified");

   return 0;
}
