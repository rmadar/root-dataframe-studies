#include <iostream>
#include <ctime>

#include "TFile.h"
#include "TTree.h"

using namespace std;


void RunEvtLoop(){

  clock_t start = clock();

  
  // Input file/Trees
  // ----------------
  TFile *fin = TFile::Open("input_small.root");
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

  
  int SSee_2015(false), SSem_2015(false), SSmm_2015(false);
  int SSee_2016(false), SSem_2016(false), SSmm_2016(false);
  int eee_2015(false), eem_2015(false), emm_2015(false), mmm_2015(false);
  int eee_2016(false), eem_2016(false), emm_2016(false), mmm_2016(false);
  tin->SetBranchAddress("SSee_2015", &SSee_2015);
  tin->SetBranchAddress("SSem_2015", &SSem_2015);
  tin->SetBranchAddress("SSmm_2015", &SSmm_2015);
  tin->SetBranchAddress("SSee_2016", &SSee_2016);
  tin->SetBranchAddress("SSem_2016", &SSem_2016);
  tin->SetBranchAddress("SSmm_2016", &SSmm_2016);
  tin->SetBranchAddress("eee_2015", &eee_2015);
  tin->SetBranchAddress("eem_2015", &eem_2015);
  tin->SetBranchAddress("emm_2015", &emm_2015);
  tin->SetBranchAddress("mmm_2015", &mmm_2015);
  tin->SetBranchAddress("eee_2016", &eee_2016);
  tin->SetBranchAddress("eem_2016", &eem_2016);
  tin->SetBranchAddress("emm_2016", &emm_2016);
  tin->SetBranchAddress("mmm_2016", &mmm_2016);

  

  // Preparing the ouput
  // -------------------
  TFile *fout = new TFile("output.root","RECREATE");
  TTree *tout = tin->CloneTree(0);
  int SSee(false), SSem(false), SSmm(false);
  int eee(false), eem(false), emm(false), mmm(false);
  int SS(false), LLL(false);
  int iChan(-1);
  tout->Branch("SSee", &SSee, "I");
  tout->Branch("SSem", &SSem, "I");
  tout->Branch("SSmm", &SSmm, "I");
  tout->Branch("eee", &eee, "I");
  tout->Branch("eem", &eem, "I");
  tout->Branch("emm", &emm, "I");
  tout->Branch("mmm", &mmm, "I");
  tout->Branch("SS", &SS, "I");
  tout->Branch("LLL", &LLL, "I");
  tout->Branch("iChan", &iChan, "I");

  
  
  // Event loop
  // ----------
  int Nentries = tin->GetEntries();
  for (int i=0; i<Nentries ; i++){

    // Load the event
    tin->GetEntry(i);

    // Compute some new variables (to be implemented)
    SSee = SSee_2015 || SSee_2016;
    SSem = SSem_2015 || SSem_2016;
    SSmm = SSmm_2015 || SSmm_2016;
    eee = eee_2015 || eee_2016;
    eem = eem_2015 || eem_2016;
    emm = emm_2015 || emm_2016;
    mmm = mmm_2015 || mmm_2016;
    SS = SSee || SSem || SSmm;
    LLL = eee || eem || emm || mmm;
    iChan = SSee*1 + SSem*2 + SSmm*3 + eee*4 + eem*5 + emm*6 + mmm*7;

    
    // Applying some selections
    if (iChan<=0)
      continue;
    
    // Filling the output tree	
    tout->Fill();

  }
  

  // Saving ouput
  // ------------
  fout->cd();
  tout->Write();
  fout->Close();

  clock_t stop = clock();
  double dt = double(stop - start) / CLOCKS_PER_SEC;
  cout << dt << " seconds for " << Nentries << " input events." << endl;

  return;
}
