#include <vector>
#include <iostream>

#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TFrame.h"
#include "TH1F.h"
#include "TBenchmark.h"
#include "TRandom.h"
#include "TSystem.h"

// include DummyElectron
#include "xAODDummyElectron/DummyElectron.h"

// authored: Jack Kraus, 2024/07/19

int N = 1e5; // Number of events


void write()
{

   TFile *f = TFile::Open("dummyE_test_write.root","RECREATE");

   if (!f) {
           std::cout<< "Error: dummyE_test_write: file error"<<std::endl;
        return;
   }

   // simple
   // =======
   xAOD::DummyElectron e;
   // =======


   // complex
   // =======
   // std::vector<xAOD::DummyElectron> electrons; // vector momentum(p) electron 1
   // =======

   // Create a TTree
   TTree *t = new TTree("t_electrons","Tree with dummyElectrons");
   t->Branch("electrons",&e); // creates a branch in TTree t, called electrons


   gRandom->SetSeed();
   for (int i = 0; i < N; i++) {
     // simple
     // =======
     float p;
     p = 115.;
     e.setPt( p );

     float c;
     c = -1.0;
     e.setCharge( c );
     // =======

     // complex
     // =======
     //  int np_elec_1 = (int) (gRandom->Rndm(1)*15); // select a random number(n) of momenta for electron 1
     //  electrons.clear();
     //  for (int  j = 0; j < np_elec_1; ++j) { // loop over the random number of momenta
     //     float p; // one momentum
     //     float random = gRandom->Rndm(1); // one random number
     //     // insert: vectors of DummyElectrons here with random pt's
     //     electrons.emplace_back(p);

     //  }
     // =======

     t->Fill();
   }

   t->Print();
   f->Write();

   delete f;
}

int writeROOTFile_dummyElectron()
{
        gBenchmark = new TBenchmark();

        // Timed write()
        gBenchmark->Start("write_hvector");
        write();
        gBenchmark->Show("write_hvector");

   return 0;
}