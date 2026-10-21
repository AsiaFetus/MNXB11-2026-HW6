#include <TFile.h>
#include <TTree.h>
#include <TRandom.h>
#include "MovingObject.h"

void write() {
    Tfile *file = new TFile("treefile.root", "RECREATE");

    TTree *tree = new TTree("tree", "MovingObject Velocity Tree")
}