#include <iostream>
#include <ctime>

#include <ROOT/RDataFrame.hxx>

using namespace std;


void RunTDF(){

  clock_t start = clock();
  
  ROOT::EnableImplicitMT();
  ROOT::RDataFrame df = ROOT::RDataFrame("nominal_Loose", "input.root");

  // Option 1
  auto df_output = df.Define("SSee","SSee_2015 || SSee_2016")
    .Define("SSem","SSem_2015 || SSem_2016")
    .Define("SSmm","SSmm_2015 || SSmm_2016")
    .Define("eee","eee_Zveto_2015  || eee_Zveto_2016")
    .Define("eem","eem_Zveto_2015  || eem_Zveto_2016")
    .Define("emm","emm_Zveto_2015  || emm_Zveto_2016")
    .Define("mmm","mmm_Zveto_2015  || mmm_Zveto_2016")
    .Define("SS","SSee||SSem||SSmm")
    .Define("LLL","eee || eem || emm || mmm")
    .Define("iChan","SSee*1 + SSem*2 + SSmm*3 + eee*4 + eem*5 + emm*6 + mmm*7")
    .Filter("iChan>0")
    .Snapshot("tree","ouput.root",{"el_pt","mu_pt","HT_all","met_met","met_phi","jet_truthflav","nElectrons","nMuons","nJets","nBTags_60","nBTags_70","nBTags_77","nBTags_85","jet_pt","jet_eta","jet_phi","jet_mv2c10","weight_bTagSF_MV2c10_Continuous","jet_DL1","jet_DL1_pu","jet_DL1_pc","jet_DL1_pb","weight_bTagSF_DL1_Continuous","jet_tagWeightBin_MV2c10_Continuous","jet_tagWeightBin_DL1_Continuous","jet_isbtagged_MV2c10_60","jet_isbtagged_MV2c10_70","jet_isbtagged_MV2c10_77","jet_isbtagged_MV2c10_85","jet_isbtagged_DL1_60","jet_isbtagged_DL1_70","jet_isbtagged_DL1_77","jet_isbtagged_DL1_85","mu","mcChannelNumber","eventNumber","runNumber","weight_bTagSF_MV2c10_60","weight_bTagSF_MV2c10_70","weight_bTagSF_MV2c10_77","weight_bTagSF_MV2c10_85","weight_bTagSF_DL1_60","weight_bTagSF_DL1_70","weight_bTagSF_DL1_77","weight_bTagSF_DL1_85","weight_mc","weight_pileup","weight_leptonSF","weight_bTagSF_MV2c10_77","weight_jvt"});

  clock_t stop = clock();
  double dt = double(stop - start) / CLOCKS_PER_SEC;
  cout << dt << " seconds for " << df.Count().GetValue() << " input events." << endl;
  
  TFile *f = TFile::Open("test.root");
  TTree *t = (TTree*) f->Get("test_tree");
  int Ntree = t->GetEntries();
  int Ntdf  = df_output->Count().GetValue();
  cout << "Selected events:" << endl;
  cout << "  - df.Count(): " << Ntdf << endl;
  cout << "  - TTree.GetEntries(): " << Ntree << endl;

  return;
}




