import ROOT
ROOT.ROOT.EnableImplicitMT()
ROOT.gROOT.ProcessLine('gErrorIgnoreLevel = 2001;')
from timeit import default_timer
    
def list2ROOTvec(alist, dt='string'):
    res = ROOT.vector(dt)()
    for l in alist:
        res.push_back(l)
    return res


def print_cols(df):
    '''
    Print the columns of ROOT.Experimental.TDataFrame
    '''
    print(ROOTvec2list(df.GetColumnNames()))

    
def ROOTvec2list(root_vec):
    '''
    Convert a ROOT.vector into a python list
    '''
    return [v for v in root_vec]
    
    
branch_to_save = ['el_pt', 'mu_pt', 'HT_all', 'met_met', 'met_phi', 'jet_truthflav',
                  'nElectrons', 'nMuons', 'nJets', 'nBTags_60', 'nBTags_70', 'nBTags_77', 'nBTags_85',
                  'jet_pt', 'jet_eta', 'jet_phi', 'jet_mv2c10', 'weight_bTagSF_MV2c10_Continuous',
                  'jet_DL1', 'jet_DL1_pu', 'jet_DL1_pc', 'jet_DL1_pb', 'weight_bTagSF_DL1_Continuous',
                  'jet_tagWeightBin_MV2c10_Continuous', 'jet_tagWeightBin_DL1_Continuous',
                  'jet_isbtagged_MV2c10_60', 'jet_isbtagged_MV2c10_70', 'jet_isbtagged_MV2c10_77',
                  'jet_isbtagged_MV2c10_85', 'jet_isbtagged_DL1_60', 'jet_isbtagged_DL1_70',
                  'jet_isbtagged_DL1_77', 'jet_isbtagged_DL1_85', 'mu', 'mcChannelNumber', 'eventNumber', 'runNumber',
                  'weight_bTagSF_MV2c10_60', 'weight_bTagSF_MV2c10_70', 'weight_bTagSF_MV2c10_77', 'weight_bTagSF_MV2c10_85',
                  'weight_bTagSF_DL1_60', 'weight_bTagSF_DL1_70', 'weight_bTagSF_DL1_77', 'weight_bTagSF_DL1_85',
                  'weight_mc', 'weight_pileup', 'weight_leptonSF', 'weight_bTagSF_MV2c10_77', 'weight_jvt']

t_start = default_timer()
df2 = ROOT.ROOT.RDataFrame("nominal_Loose", "/home/rmadar/cernbox/ATLAS/Analysis/data/r21/tag212380/mc16a/SS3L/group.phys-top.364253.Sherpa.DAOD_TOPQ1.e5916_s3126_r9364_p3404.SM4t-212380_mc16a_SS3L_v1_output_root/*.root")

t1 = default_timer()
df2 = df2.Define("SSee","SSee_2015 || SSee_2016");
df2 = df2.Define("SSem","SSem_2015 || SSem_2016");
df2 = df2.Define("SSmm","SSmm_2015 || SSmm_2016");
df2 = df2.Define("eee","eee_Zveto_2015  || eee_Zveto_2016");
df2 = df2.Define("eem","eem_Zveto_2015  || eem_Zveto_2016");
df2 = df2.Define("emm","emm_Zveto_2015  || emm_Zveto_2016");
df2 = df2.Define("mmm","mmm_Zveto_2015  || mmm_Zveto_2016");
df2 = df2.Define("SS","SSee||SSem||SSmm");
df2 = df2.Define("LLL","eee || eem || emm || mmm");
df2 = df2.Define("iChan","SSee*1 + SSem*2 + SSmm*3 + eee*4 + eem*5 + emm*6 + mmm*7");
t2 = default_timer()
df3 = df2.Filter("iChan>0")
t3 = default_timer()
dfouput = df3.Snapshot('test_tree', 'test.root', list2ROOTvec(branch_to_save)) 
t_end = default_timer()

print('Loading   -> {:.2f}s'.format(t1 - t_start))
print('Defining  -> {:.2f}s'.format(t2 - t1))
print('Filtering -> {:.2f}s'.format(t3 - t2))
print('Snap      -> {:.2f}s'.format(t_end - t3))
print('TOTAL     -> {:.2f}s ({} input events)'.format(t_end - t_start, df2.Count().GetValue()))

fout = ROOT.TFile.Open('test.root')
tree = fout.Get('test_tree')
print('Selected events:')
print('  - df.Count(): {}'.format(dfouput.Count().GetValue()))
print('  - TTree.GetEntries(): {}'.format(tree.GetEntries()))

