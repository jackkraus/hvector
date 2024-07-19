#include <vector>
#include <cstdio>
#include <iostream>

#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TFrame.h"
#include "TH1F.h"
#include "TBenchmark.h"
#include "TRandom.h"
#include "TSystem.h"
#include "TTreePerfStats.h"

// authored: Jack Kraus, 24/07/19

int n = 1e2; // Number of events


void read()
{

   TFile *f = TFile::Open("dummyE_test_write.root","READ");

   if (!f) {
        std::cout<<"Error: dummyE_test_write: file error"<<std::endl;
        return;
   }


   TTree *t = f->Get<TTree>("t_electrons");

   // simple
   // =======
   for (int i = 0; i < n; i++){ t->Show( i ); }
   // =======
}

int readROOTFile_dummyElectron()
{
   gBenchmark = new TBenchmark();
   // Timed read()
   gBenchmark->Start("read_dummyElectron");
   read();
   gBenchmark->Show("read_dummyElectron");

   return 0;
}