#include <TFile.h>
#include <TTree.h>
#include <TRandom.h>
#include "MovingObject.h"

void write() {
    MovingObject *obj = new MovingObject();
    
    TFile *file = new TFile("tree_file.root", "RECREATE");

    TTree *tree = new TTree("tree", "MovingObject Velocity Tree");

    tree->Branch("object", &obj); 

    gRandom->SetSeed(12345);

    const Int_t nEvents = 10000;

    for(Int_t i{0}; i<nEvents; i++) {
        Double_t vx = gRandom->Gaus(0.0, 0.30);
        Double_t vy = gRandom->Gaus(0.0, 0.30);
        Double_t vz = gRandom->Gaus(0.0, 0.30);

        obj->SetVelocity(vx, vy, vz); 

        tree->Fill();
    }

    tree->Write();

    delete obj;
    delete file;
}