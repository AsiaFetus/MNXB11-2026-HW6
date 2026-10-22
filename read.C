#include <TFile.h>
#include <TTree.h>
#include <TH2D.h>
#include <TCanvas.h>
#include "MovingObject.h"


void read() {
    TH1::AddDirectory(kFALSE); //so first histogram doesnt print blank
    
    TFile *file = new TFile("tree_file.root", "READ");
    if (!file || file->IsZombie()) {
        Error("read", "Could not open tree_file.root");
        return;
    }
    TTree *tree = (TTree*)file-> Get("tree");

    MovingObject *obj = nullptr;
    tree->SetBranchAddress("object", &obj);

    Long64_t entrycount = tree->GetEntries();

    TH2D *hist = new TH2D("hist", "Velocity Components, V_{y}(m/s) vs V_{x}(m/s) ", 100, -1.5, 1.5, 100, -1.5, 1.5);
    hist->GetXaxis()->SetTitle("V_{x} (m/s)");
    hist->GetYaxis()->SetTitle("V_{y} (m/s)");

    for(Long64_t i = 0; i < entrycount; i++) {
        tree->GetEntry(i);
        hist->Fill(obj->Vx(), obj->Vy());
    }

    TCanvas *canvas1 = new TCanvas("canvas1", "Velocity Components", 800, 600);
    hist->Draw("COLZ");
    canvas1->SaveAs("velocity_components.pdf");
    TCanvas *canvas2 = new TCanvas("canvas2", "Scatter Plot", 800, 600);
    
    //tree->Draw("object.HorizontalSpeed():object.Vz()", "object.Speed() > 0.50", "COLZ");
    
    tree->Draw("object.HorizontalSpeed():object.Vz() >> h_scatter(100, -1.5, 1.5, 100, 0, 1.5)", "object.Speed() > 0.50", "COLZ");
    
    TH2 *h_scatter = (TH2*)gPad->GetPrimitive("h_scatter"); 
    if (h_scatter) {
        h_scatter->SetTitle("Horizontal Speed V_{xy} vs V_{z} for (v > 0.50 m/s)");
        h_scatter->GetXaxis()->SetTitle("V_{z} (m/s)");
        h_scatter->GetYaxis()->SetTitle("v_{xy} (m/s)");
        h_scatter->Draw("COLZ");
    }

    canvas2->SaveAs("speed_scatter.pdf");

    file->Close();
    delete file;
}