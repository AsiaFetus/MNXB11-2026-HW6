#include <TFile.h>
#include <TTree.h>
#include <TH2D.h>
#include <TCanvas.h>
#include "MovingObject.h"


void read() {
    TH1::AddDirectory(kFALSE);
    TFile *file = new TFile("tree_file.root", "READ");
    if (!file || file->IsZombie()) {
        Error("read", "Could not open tree_file.root");
        return;
    }
    TTree *tree = (TTree*)file-> Get("tree");

    MovingObject *obj = nullptr;
    tree->SetBranchAddress("object", &obj);

    Long64_t entrycount = tree->GetEntries();

    TH2D *hist = new TH2D("hist", "Velocity Components, V_y vs V_x", 100, -1.5, 1.5, 100, -1.5, 1.5);

    for(Long64_t i = 0; i < entrycount; i++) {
        tree->GetEntry(i);
        hist->Fill(obj->Vx(), obj->Vy());

    hist->Fill(obj->Vx(), obj->Vy());
    }

    TCanvas *canvas1 = new TCanvas("canvas1", "Velocity Components", 800, 600);
    hist->Draw("COLZ");
    canvas1->SaveAs("velocity_components.pdf");

    TCanvas *canvas2 = new TCanvas("canvas2", "Scatter Plot", 800, 600);
    tree->Draw("object.HorizontalSpeed():object.Vz()", "object.Speed() > 0.50", "COLZ");
    canvas2->SaveAs("speed_scatter.pdf");

    file->Close();
    delete file;
}