#include <iostream>
#include <ctime>

#include "TFile.h"
#include "TTree.h"

using namespace std;


void RunEvtLoop(){

  clock_t start = clock();
  
  TFile *fin = TFile::Open("input.root");
  TTree *tin = (TTree*) fin->Get("nominal_Loose");
  tin->SetBranchStatus("*",0);
  tin->SetBranchStatus("el_pt",1);
  tin->SetBranchStatus("mu_pt",1);
  tin->SetBranchStatus("HT_all",1);
  tin->SetBranchStatus("met_met",1);
  tin->SetBranchStatus("met_phi",1);
  tin->SetBranchStatus("jet_truthflav",1);
  tin->SetBranchStatus("nElectrons",1);
  tin->SetBranchStatus("nMuons",1);
  tin->SetBranchStatus("nJets",1);
  tin->SetBranchStatus("nBTags_60",1);
  tin->SetBranchStatus("nBTags_70",1);
  tin->SetBranchStatus("nBTags_77",1);
  tin->SetBranchStatus("nBTags_85",1);
  tin->SetBranchStatus("jet_pt",1);
  tin->SetBranchStatus("jet_eta",1);
  tin->SetBranchStatus("jet_phi",1);
  tin->SetBranchStatus("jet_mv2c10",1);
  tin->SetBranchStatus("weight_bTagSF_MV2c10_Continuous",1);
  tin->SetBranchStatus("jet_DL1",1);
  tin->SetBranchStatus("jet_DL1_pu",1);
  tin->SetBranchStatus("jet_DL1_pc",1);
  tin->SetBranchStatus("jet_DL1_pb",1);
  tin->SetBranchStatus("weight_bTagSF_DL1_Continuous",1);
  tin->SetBranchStatus("jet_tagWeightBin_MV2c10_Continuous",1);
  tin->SetBranchStatus("jet_tagWeightBin_DL1_Continuous",1);
  tin->SetBranchStatus("jet_isbtagged_MV2c10_60",1);
  tin->SetBranchStatus("jet_isbtagged_MV2c10_70",1);
  tin->SetBranchStatus("jet_isbtagged_MV2c10_77",1);
  tin->SetBranchStatus("jet_isbtagged_MV2c10_85",1);
  tin->SetBranchStatus("jet_isbtagged_DL1_60",1);
  tin->SetBranchStatus("jet_isbtagged_DL1_70",1);
  tin->SetBranchStatus("jet_isbtagged_DL1_77",1);
  tin->SetBranchStatus("jet_isbtagged_DL1_85",1);
  tin->SetBranchStatus("mu",1);
  tin->SetBranchStatus("mcChannelNumber",1);
  tin->SetBranchStatus("eventNumber",1);
  tin->SetBranchStatus("runNumber",1);
  tin->SetBranchStatus("weight_bTagSF_MV2c10_60",1);
  tin->SetBranchStatus("weight_bTagSF_MV2c10_70",1);
  tin->SetBranchStatus("weight_bTagSF_MV2c10_77",1);
  tin->SetBranchStatus("weight_bTagSF_MV2c10_85",1);
  tin->SetBranchStatus("weight_bTagSF_DL1_60",1);
  tin->SetBranchStatus("weight_bTagSF_DL1_70",1);
  tin->SetBranchStatus("weight_bTagSF_DL1_77",1);
  tin->SetBranchStatus("weight_bTagSF_DL1_85",1);
  tin->SetBranchStatus("weight_mc",1);
  tin->SetBranchStatus("weight_pileup",1);
  tin->SetBranchStatus("weight_leptonSF",1);
  tin->SetBranchStatus("weight_bTagSF_MV2c10_77",1);
  tin->SetBranchStatus("weight_jvt",1);
  tin->SetBranchStatus("SSee*",1);
  tin->SetBranchStatus("SSem*",1);
  tin->SetBranchStatus("SSmm*",1);
  tin->SetBranchStatus("eee*",1);
  tin->SetBranchStatus("eem*",1);
  tin->SetBranchStatus("emm*",1);
  tin->SetBranchStatus("mmm*",1);
    
  TFile *fout = new TFile("output.root","RECREATE");
  TTree *tout = tin->CloneTree(0);
  int Nentries = tin->GetEntries();

  for (int i=0; i<Nentries ; i++){

    // Load the event
    tin->GetEntry(i);

    // Compute some new variables (to be implemented)
    
    // Applying some selections
    if (i%2==0) // emulate an efficiency selection of 0.5
      continue;

    // Filling the output tree	
    tout->Fill();

  }
  
  fout->cd();
  tout->Write();
  fout->Close();

  clock_t stop = clock();
  double dt = double(stop - start) / CLOCKS_PER_SEC;
  cout << dt << " seconds for " << Nentries << " input events." << endl;

  return;
}
