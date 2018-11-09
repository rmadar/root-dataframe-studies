#include <iostream>
#include <ctime>

#include <ROOT/RDataFrame.hxx>
#include "TStopwatch.h"

using namespace std;


void RunTDF(){

  TStopwatch timer;
  
  clock_t start_clk = clock();
  auto start_chrono = chrono::high_resolution_clock::now();
  timer.Start();
  
  //ROOT::EnableImplicitMT();
  ROOT::RDataFrame df = ROOT::RDataFrame("nominal_Loose", "input.root");
  
  auto df_output = df.Define("SSee", [](int flag1, int flag2){return flag1+flag2;}, {"SSee_2015","SSee_2016"})
    .Define("SSem", [](int flag1, int flag2){return flag1+flag2;}, {"SSem_2015","SSem_2016"})
    .Define("SSmm", [](int flag1, int flag2){return flag1+flag2;}, {"SSmm_2015","SSmm_2016"})
    .Define("eee",  [](int flag1, int flag2){return flag1+flag2;}, {"eee_Zveto_2015","eee_Zveto_2016"})
    .Define("eem",  [](int flag1, int flag2){return flag1+flag2;}, {"eem_Zveto_2015","eem_Zveto_2016"})
    .Define("emm",  [](int flag1, int flag2){return flag1+flag2;}, {"emm_Zveto_2015","emm_Zveto_2016"})
    .Define("mmm",  [](int flag1, int flag2){return flag1+flag2;}, {"mmm_Zveto_2015","mmm_Zveto_2016"})
    .Define("SS",   [](int flag1, int flag2, int flag3){return flag1+flag2+flag3;}, {"SSee","SSem","SSmm"})
    .Define("LLL",  [](int flag1, int flag2, int flag3, int flag4){return flag1+flag2+flag3+flag4;}, {"eee","eem","emm","mmm"})
    .Define("iChan",[](int flag1, int flag2, int flag3, int flag4, int flag5, int flag6, int flag7){return flag1*1 + flag2*2 + flag3*3 + flag4*4 + flag5*5 + flag6*6 + flag7*7;}, {"SSee","SSem","SSmm","eee","eem","emm","mmm"})
    .Filter("iChan>0")
    .Snapshot("tree","output.root", {"el_pt","mu_pt","HT_all","met_met","met_phi","jet_truthflav","nElectrons","nMuons","nJets","nBTags_60","nBTags_70","nBTags_77","nBTags_85","jet_pt","jet_eta","jet_phi","jet_mv2c10","weight_bTagSF_MV2c10_Continuous","jet_DL1","jet_DL1_pu","jet_DL1_pc","jet_DL1_pb","weight_bTagSF_DL1_Continuous","jet_tagWeightBin_MV2c10_Continuous","jet_tagWeightBin_DL1_Continuous","jet_isbtagged_MV2c10_60","jet_isbtagged_MV2c10_70","jet_isbtagged_MV2c10_77","jet_isbtagged_MV2c10_85","jet_isbtagged_DL1_60","jet_isbtagged_DL1_70","jet_isbtagged_DL1_77","jet_isbtagged_DL1_85","mu","mcChannelNumber","eventNumber","runNumber","weight_bTagSF_MV2c10_60","weight_bTagSF_MV2c10_70","weight_bTagSF_MV2c10_77","weight_bTagSF_MV2c10_85","weight_bTagSF_DL1_60","weight_bTagSF_DL1_70","weight_bTagSF_DL1_77","weight_bTagSF_DL1_85","weight_mc","weight_pileup","weight_leptonSF","weight_bTagSF_MV2c10_77","weight_jvt"});

  clock_t stop_clk = clock();
  auto stop_chrono = chrono::high_resolution_clock::now();
  timer.Stop();
  
  double dt_clk = double(stop_clk-start_clk)/CLOCKS_PER_SEC;
  double dt_chrono = chrono::duration<double>(stop_chrono-start_chrono).count();
  double dt_twatch_CPU = timer.CpuTime();
  double dt_twatch_Real = timer.RealTime();
    
  cout << dt_clk << "/" << dt_chrono << "/" << dt_twatch_CPU << "/" << dt_twatch_Real
       << " (clk/chrono/twatch_CPU/twatch_Real) seconds for " << df.Count().GetValue()
       << " input events." << endl;
  
  TFile *f = TFile::Open("output.root");
  TTree *t = (TTree*) f->Get("tree");
  int Ntree = t->GetEntries();
  int Ntdf  = df_output->Count().GetValue();
  cout << "Selected events:" << endl;
  cout << "  - df.Count(): " << Ntdf << endl;
  cout << "  - TTree.GetEntries(): " << Ntree << endl;

  return;
}




