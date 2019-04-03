#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include <iostream>
#include <fstream>
#include "TMath.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TGraph2DErrors.h"
#include "TLegend.h"
#include <TStyle.h>
#include <TROOT.h>



void coinAcc(){

//TString inputroot, replayroot;
//inputroot = mcfile + ".root";
//replayroot = datfile + ".root";
//TFile *f1 = new TFile("csv6009.root");
//TTree *t1 = (TTree*) f1->Get("h666");
//TFile* f = new TFile("coin_play_production_6017_-1.root");
//TTree *t = (TTree*) f->Get("T");
auto *f1 = TFile::Open("/u/home/shuojia/simc_gfortran/worksim/csv6009.root");
TTree *t1 = (TTree*) f1->Get("h666");
auto *f = TFile::Open("/group/c-csv/shuo/replay/ROOTfiles/coin_replay_production_6009_-1.root");
TTree *t = (TTree*) f->Get("T");

float ssxptar; //SIMC SHMS reconstructed target dx/dz vertical slope
float ssyptar; //SIMC SHMS reconstructed target dy/dz vertical slope
float ssytar; //SIMC SHMS reconstructed target y
float ssdelta; //SIMC SHMS reconstructed 100*(p - pc)/pc with pc = central SHMS momentum
float hsxptar; //SIMC HMS reconstructed target dx/dz vertical slope
float hsyptar; //SIMC HMS reconstructed target dy/dz vertical slope
float hsdelta; //SIMC HMS reconstructed 100*(p - pc)/pc with pc = central SHMS momentum
float hsytar; //SIMC HMS reconstructed target y
float om;
float Q2;
float W;
float Emiss_sim; //missing energy simc
float Pmiss_sim; //missing momentum simc
float theta_e;
float Weight;
double htardp; //DATA HMS reconstructed 100*(p - pc)/pc with pc = central SHMS momentum
double htarth; //DATA HMS reconstructed target dx/dz vertical slope
double htarph; //DATA HMS reconstructed target dy/dz vertical slope
double ptardp; //DATA SHMS reconstructed 100*(p - pc)/pc with pc = central SHMS momentum
double ptarth; //DATA SHMS reconstructed target dx/dz vertical slope
double ptarph; //DATA SHMS reconstructed target dy/dz vertical slope
double dataW;
double dataQ2;
double dataom;
double etottracknorm;
double pindex;
double hindex;
double Emiss_d;
double Pmiss_d;
double weight_hist;
float hx_fp_simc; //SIMC HMS fp x
float hxp_fp_simc; //SIMC HMS fp dx/dz
float hy_fp_simc; //SIMC HMS fp y
float hyp_fp_simc; //SIMC HMS fp dy/dz
double hx_fp_data; //DATA HMS fp x
double hxp_fp_data; //DATA HMS fp dx/dz
double hy_fp_data; //DATA HMS fp y
double hyp_fp_data; //DATA HMS fp dy/dz
float sx_fp_simc; //SIMC SHMS fp x
float sxp_fp_simc; //SIMC SHMS fp dx/dz
float sy_fp_simc; //SIMC SHMS fp y
float syp_fp_simc; //SIMC SHMS fp dy/dz
double sx_fp_data; //DATA SHMS fp x
double sxp_fp_data; //DATA SHMS fp dx/dz
double sy_fp_data; //DATA SHMS fp y
double syp_fp_data; //DATA SHMS fp dy/dz
double h_spec = 5.27;
double p_spec = 6.19;
double Mp = 0.93825;
double Eb = 10.5965; //GeV
double deg2rad = 3.14159/180.;
double ts = 21.07; //central spectrometer angle //deg
double cos_ts = cos(ts * deg2rad);
double sin_ts = sin(ts * deg2rad);
double datath;
double smom;
double hmom;
double htary;
float sigma_simc;
double Ep;
double shms_mom;
double diff_pmom;
double diff_emom;
double delta_cal;
double delta_meas;
double delta_diff_cal;
double delta_diff_meas;


t1->SetBranchAddress("hsxfp",&hx_fp_simc);
t1->SetBranchAddress("hsxpfp",&hxp_fp_simc);
t1->SetBranchAddress("hsyfp",&hy_fp_simc);
t1->SetBranchAddress("hsypfp",&hyp_fp_simc);
t1->SetBranchAddress("ssxfp",&sx_fp_simc);
t1->SetBranchAddress("ssxpfp",&sxp_fp_simc);
t1->SetBranchAddress("ssyfp",&sy_fp_simc);
t1->SetBranchAddress("ssypfp",&syp_fp_simc);
t1->SetBranchAddress("ssdelta",&ssdelta);
t1->SetBranchAddress("ssxptar",&ssxptar);
t1->SetBranchAddress("ssyptar",&ssyptar);
t1->SetBranchAddress("hsdelta",&hsdelta);
t1->SetBranchAddress("hsxptar",&hsxptar);
t1->SetBranchAddress("hsyptar",&hsyptar);
t1->SetBranchAddress("hsytar",&hsytar);
t1->SetBranchAddress("Q2",&Q2);
t1->SetBranchAddress("W",&W);
t1->SetBranchAddress("nu",&om);
t1->SetBranchAddress("Em",&Emiss_sim);
t1->SetBranchAddress("Pm",&Pmiss_sim);
t1->SetBranchAddress("Weight",&Weight);
 t1->SetBranchAddress("sigcc",&sigma_simc);
t->SetBranchAddress("P.dc.x_fp",&sx_fp_data);
t->SetBranchAddress("P.dc.xp_fp",&sxp_fp_data);
t->SetBranchAddress("P.dc.y_fp",&sy_fp_data);
t->SetBranchAddress("P.dc.yp_fp",&syp_fp_data);
t->SetBranchAddress("H.dc.x_fp",&hx_fp_data);
t->SetBranchAddress("H.dc.xp_fp",&hxp_fp_data);
t->SetBranchAddress("H.dc.y_fp",&hy_fp_data);
t->SetBranchAddress("H.dc.yp_fp",&hyp_fp_data);
t->SetBranchAddress("P.kin.secondary.emiss",&Emiss_d);
t->SetBranchAddress("P.kin.secondary.pmiss",&Pmiss_d);
t->SetBranchAddress("H.cal.etottracknorm",&etottracknorm);
t->SetBranchAddress("P.gtr.dp", &ptardp);
t->SetBranchAddress("P.gtr.th", &ptarth);
t->SetBranchAddress("P.gtr.ph", &ptarph);
t->SetBranchAddress("H.gtr.dp", &htardp);
t->SetBranchAddress("H.gtr.th", &htarth);
t->SetBranchAddress("H.gtr.ph", &htarph);
t->SetBranchAddress("H.gtr.y", &htary);
t->SetBranchAddress("H.kin.primary.W", &dataW);
t->SetBranchAddress("H.kin.primary.Q2", &dataQ2);
t->SetBranchAddress("H.kin.primary.omega", &dataom);
t->SetBranchAddress("H.kin.primary.scat_ang_deg", &datath);
t->SetBranchAddress("H.gtr.index", &hindex);
t->SetBranchAddress("P.gtr.index", &pindex);
t->SetBranchAddress("P.gtr.p", &smom);
t->SetBranchAddress("H.gtr.p", &hmom);


    //SIMC
    //TH1F *hQ2 = new TH1F("Q2 ", "Q2", 100, 5.0, 9.0);
    //TH1F *hQ2d = new TH1F("Q2d ", "Q2 ", 100, 5.0, 9.0);
    TH1F *hQ2 = new TH1F("Q2 ", "Q2", 100, 7.0, 12.0);
    TH1F *hQ2d = new TH1F("Q2d ", "Q2 ", 100, 7.0, 12.0);
    hQ2d->GetXaxis()->SetTitle("Q^{2} [GeV^{2}]");
    hQ2d->GetYaxis()->SetTitle("counts");
    TH1F *hQ2_sim = new TH1F("Q2","Q2",100,7.0,12.0);    
//TH1F *hom = new TH1F("om ", "om ", 100, 2.0, 4.5);
    //TH1F *homd = new TH1F("omd ", "#omega ", 100, 2.0, 4.5);
    TH1F *hom = new TH1F("om ", "om ", 100, 4.0, 6.4);
    TH1F *homd = new TH1F("omd ", "#omega ", 100, 4.0, 6.4);
    //TH1F *hom = new TH1F("om ", "om ", 100, 2.0, 4.5);
    //TH1F *homd = new TH1F("omd ", "#omega ", 100, 2.0, 4.5);
    homd->GetXaxis()->SetTitle("#omega [GeV]");
    homd->GetYaxis()->SetTitle("counts");
    TH1F *misse = new TH1F("misse ", "missing energy ", 100, -0.2, 0.2);
    misse->GetXaxis()->SetTitle("Emiss [GeV]");
    misse->GetYaxis()->SetTitle("counts");
    TH1F *missp = new TH1F("missp ", "missing momentum ", 100, -0.2, 0.2);
    TH1F *misse_d = new TH1F("misse data", "missing energy", 100, -0.2, 0.2);
    missp->GetXaxis()->SetTitle("Pmiss [GeV]");
    missp->GetYaxis()->SetTitle("counts");
    TH1F *missp_d = new TH1F("missp data", "missing momentum", 100, -0.2, 0.2);
    TH1F *hptaryp = new TH1F("hptaryp", "hptaryp",100, -0.1, 0.1);
    hptaryp->SetTitle("SHMS yp_tar");
    hptaryp->GetXaxis()->SetTitle("SHMS yp_tar(rad)");
    hptaryp->GetYaxis()->SetTitle("counts");
    TH1F *hptarxp = new TH1F("hptarxp", "hptarxp",100, -0.1, 0.1);
    hptarxp->SetTitle("SHMS xp_tar");
    hptarxp->GetXaxis()->SetTitle("SHMS xp_tar(rad)");
    hptarxp->GetYaxis()->SetTitle("counts");
    TH1F *hhtaryp = new TH1F("hhtaryp", "hhtaryp",100, -0.1, 0.1);
    hhtaryp->SetTitle("HMS yp_tar");
    hhtaryp->GetXaxis()->SetTitle("HMS yp_tar(rad)");
    hhtaryp->GetYaxis()->SetTitle("counts");
    TH1F *hhtarxp = new TH1F("hhtarxp", "hhtarxp",100, -0.1, 0.1);
    hhtarxp->SetTitle("HMS xp_tar");
    hhtarxp->GetXaxis()->SetTitle("HMS xp_tar(rad)");
    hhtarxp->GetYaxis()->SetTitle("counts");
    //TH1F *hhdelta = new TH1F("hhdelta", "hhdelta",100, -10, 10);
    TH1F *hhdelta = new TH1F("hhdelta", "hhdelta",100, -14, 4);
    hhdelta->SetTitle("HMS delta");
    hhdelta->GetXaxis()->SetTitle("HMS delta(%)");
    hhdelta->GetYaxis()->SetTitle("counts");
    TH1F *hpdelta = new TH1F("hpdelta", "hpdelta",100, -10, 10);
    hpdelta->SetTitle("SHMS delta");
    hpdelta->GetXaxis()->SetTitle("SHMS delta(%)");
    hpdelta->GetYaxis()->SetTitle("counts");
    TH1F *pmom = new TH1F("pmom", "hms momentum diff ", 200, - 0.5 , 0.5);
    TH2F *diff_mom_vs_theta = new TH2F("diff_mom_vs_theta", "difference in SHMS momentum vs HMS theta", 100, 17.0, 22.0, 100, -0.5, 0.7 );
    
    //TH1F *h_fp_x_s = new TH1F("hms fp x ", "hms fp x ", 100, -40, 40);
    //TH1F *h_fp_x_d = new TH1F("hms fp x data", "hms fp x data", 100, -40, 40);
    TH1F *h_fp_x_s = new TH1F("hms fp x ", "hms fp x ", 100, -30, 30);
    TH1F *h_fp_x_d = new TH1F("hms fp x data", "hms fp x ", 100, -30, 30);
    //TH1F *h_fp_xp_s = new TH1F("hms fp xp ", "hms fp xp ", 100, -0.04, 0.05);
    //TH1F *h_fp_xp_d = new TH1F("hms fp xp data", "hms fp xp data", 100, -0.04, 0.05);
    TH1F *h_fp_xp_s = new TH1F("hms fp xp ", "hms fp xp ", 100, -0.04, 0.04);
    TH1F *h_fp_xp_d = new TH1F("hms fp xp data", "hms fp xp ", 100, -0.04, 0.04);
    TH1F *h_fp_y_s = new TH1F("hms fp y ", "hms fp y ", 100, -20, 30);
    TH1F *h_fp_y_d = new TH1F("hms fp y data", "hms fp y ", 100, -20, 30);
    TH1F *h_fp_yp_s = new TH1F("hms fp yp ", "hms fp yp ", 100, -0.03, 0.03);
    TH1F *h_fp_yp_d = new TH1F("hms fp yp data", "hms fp yp ", 100, -0.03, 0.03);
    
    TH1F *s_fp_x_s = new TH1F("shms fp x ", "shms fp x ", 100, -30, 15);
    TH1F *s_fp_x_d = new TH1F("shms fp x data", "shms fp x ", 100, -30, 15);
    TH1F *s_fp_xp_s = new TH1F("shms fp xp ", "shms fp xp ", 100, -0.08, 0.06);
    TH1F *s_fp_xp_d = new TH1F("shms fp xp data", "shms fp xp ", 100, -0.08, 0.06);
    TH1F *s_fp_y_s = new TH1F("shms fp y ", "shms fp y ", 100, -20, 10);
    TH1F *s_fp_y_d = new TH1F("shms fp y data", "shms fp y ", 100, -20, 10);
    TH1F *s_fp_yp_s = new TH1F("shms fp yp ", "shms fp yp ", 100, -0.04, 0.03);
    TH1F *s_fp_yp_d = new TH1F("shms fp yp data", "shms fp yp ", 100, -0.04, 0.03);
    
    //DATA
    TH1F *ptarypd = new TH1F("ptarypd", "ptarypd",100, -0.1, 0.1);
    ptarypd->SetTitle("SHMS yp_tar");
    ptarypd->GetXaxis()->SetTitle("SHMS yp_tar(rad)");
    ptarypd->GetYaxis()->SetTitle("counts");
    TH1F *ptarxpd = new TH1F("ptarxpd", "ptarxpd",100, -0.1, 0.1);
    ptarxpd->SetTitle("SHMS xp_tar");
    ptarxpd->GetXaxis()->SetTitle("SHMS xp_tar(rad)");
    ptarxpd->GetYaxis()->SetTitle("counts");
    TH1F *htarypd = new TH1F("htarypd", "htarypd",100, -0.1, 0.1);
    htarypd->SetTitle("HMS yp_tar");
    htarypd->GetXaxis()->SetTitle("HMS yp_tar(rad)");
    htarypd->GetYaxis()->SetTitle("counts");
    TH1F *htarxpd = new TH1F("htarxpd", "htarxpd",100, -0.1, 0.1);
    htarxpd->SetTitle("HMS xp_tar");
    htarxpd->GetXaxis()->SetTitle("HMS xp_tar(rad)");
    htarxpd->GetYaxis()->SetTitle("counts");
    TH1F *hdeltad = new TH1F("hdeltad", "hdeltad",100, -14, 4.0);
    //TH1F *hdeltad = new TH1F("hdeltad", "hdeltad",100, -10, 10);
    hdeltad->SetTitle("HMS dp");
    hdeltad->GetXaxis()->SetTitle("HMS delta(%)");
    hdeltad->GetYaxis()->SetTitle("counts");
    TH1F *pdeltad = new TH1F("pdeltad", "pdeltad",100, -10, 10);
    pdeltad->SetTitle("SHMS dp");
    pdeltad->GetXaxis()->SetTitle("SHMS delta(%)");
    pdeltad->GetYaxis()->SetTitle("counts");
    TH1F *ytar = new TH1F("ytar", "HMS y_tar",100, -6, 6);
    TH1F *ytard = new TH1F("ytard", "HMS y_tar",100, -6, 6);
    TH1F *hdelta_cal = new TH1F("hdelta_cal", "delta cal",100, -2.0, 14.0);
    TH1F *hdelta_meas = new TH1F("hdelta_meas", "delta meas",100, -2.0, 14.0);
    TH1F *hdelta_diff = new TH1F("hdelta_diff", "delta cal. - delta meas. run 6017 ",100, -4.0, 4.0);
    hdelta_diff->GetYaxis()->SetTitle("counts");
    hdelta_diff->GetXaxis()->SetTitle("delta cal. - delta meas.");
    TH2F *delta_fp_xp = new TH2F("delta vs fp xp", "delta diff vs fp xp run 6017", 100, -0.06, 0.06, 40, -2.0, 2.0);
    delta_fp_xp->GetXaxis()->SetTitle("focal plane xp");
    delta_fp_xp->GetYaxis()->SetTitle("delta cal. - delta meas.");
    TH2F *delta_fp_yp = new TH2F("delta vs fp yp", "delta diff vs fp yp run 6017", 100, -0.02, 0.03, 40, -2.0, 2.0);
    delta_fp_yp->GetXaxis()->SetTitle("focal plane yp");
    delta_fp_yp->GetYaxis()->SetTitle("delta cal. - delta meas.");
    TH2F *delta_fp_y = new TH2F("delta vs fp y", "delta diff vs fp y run 6017", 100, -15, 20, 40, -2.0, 2.0);
    delta_fp_y->GetXaxis()->SetTitle("focal plane y");
    delta_fp_y->GetYaxis()->SetTitle("delta cal. - delta meas.");
    TH2F *delta_fp_x = new TH2F("delta vs fp x", "delta diff vs fp x run 6017", 100, -50, 50, 40, -2.0, 2.0);
    delta_fp_x->GetXaxis()->SetTitle("focal plane x");
    delta_fp_x->GetYaxis()->SetTitle("delta cal. - delta meas.");
    
    //HMS Target simulation 2D plots
    TH2F *tarphvsys = new TH2F("tarphvsys", "tarphvsys", 100, -0.05, 0.05, 100, -4, 4);
    tarphvsys->GetXaxis()->SetNdivisions(4);
    tarphvsys->GetYaxis()->SetTitle("HMS Ytar(cm)");
    tarphvsys->GetXaxis()->SetTitle("HMS #phi(rad)");
    TH2F *tarthvsys = new TH2F("tarthvsys", "tarthvsys", 100, -0.1, 0.1, 100, -4, 4);
    tarthvsys->GetYaxis()->SetTitle("HMS Ytar(cm)");
    tarthvsys->GetXaxis()->SetTitle("HMS #theta(rad)");
    TH2F *tarphvsths = new TH2F("tarphvsths", "tarphvsths", 100, -0.05, 0.05, 100, -0.1, 0.1);
    tarphvsths->GetYaxis()->SetTitle("HMS #theta(rad)");
    tarphvsths->GetXaxis()->SetTitle("HMS #phi(rad)");
    TH2F *tarphvsdps = new TH2F("tarphvsdps", "tarphvsdps", 100, -0.05, 0.05, 100, -15, 12);
    tarphvsdps->GetYaxis()->SetTitle("HMS dp(%)");
    tarphvsdps->GetXaxis()->SetTitle("HMS #phi(rad)");
    TH2F *tarthvsdps = new TH2F("tarthvsdps", "tarthvsdps", 100, -0.1, 0.1, 100, -15, 12);
    tarthvsdps->GetYaxis()->SetTitle("HMS dp(%)");
    tarthvsdps->GetXaxis()->SetTitle("HMS #theta(rad)");
    TH2F *taryvsdps = new TH2F("taryvsdps", "taryvsdps", 100, -4, 4, 100, -15, 12);
    taryvsdps->GetYaxis()->SetTitle("HMS dp(%)");
    taryvsdps->GetXaxis()->SetTitle("HMS Ytar(cm)");
    
    //SHMS Target simulation 2D plots
    TH2F *tarphvsyps = new TH2F("tarphvsyps", "tarphvsyps", 100, -0.04, 0.04, 100, -2, 2);
    tarphvsyps->GetYaxis()->SetTitle("SHMS Ytar(cm)");
    tarphvsyps->GetXaxis()->SetTitle("SHMS #phi(rad)");
    TH2F *tarthvsyps = new TH2F("tarthvsyps", "tarthvsyps", 100, -0.05, 0.05, 100, -2, 2);
    tarthvsyps->GetYaxis()->SetTitle("SHMS Ytar(cm)");
    tarthvsyps->GetXaxis()->SetTitle("SHMS #theta(rad)");
    TH2F *tarphvsthps = new TH2F("tarphvsthps", "tarphvsthps", 100, -0.04, 0.04, 100, -0.05, 0.05);
    tarphvsthps->GetYaxis()->SetTitle("SHMS #theta(rad)");
    tarphvsthps->GetXaxis()->SetTitle("SHMS #phi(rad)");
    TH2F *tarphvsdpps = new TH2F("tarphvsdpps", "tarphvsdpps", 100, -0.04, 0.04, 100, -18, 5);
    tarphvsdpps->GetYaxis()->SetTitle("SHMS dp(%)");
    tarphvsdpps->GetXaxis()->SetTitle("SHMS #phi(rad)");
    TH2F *tarthvsdpps = new TH2F("tarthvsdpps", "tarthvsdpps", 100, -0.05, 0.05, 100, -18, 5);
    tarthvsdpps->GetYaxis()->SetTitle("SHMS dp(%)");
    tarthvsdpps->GetXaxis()->SetTitle("SHMS #theta(rad)");
    TH2F *taryvsdpps = new TH2F("taryvsdpps", "taryvsdpps", 100, -2, 2, 100, -15, 12);
    taryvsdpps->GetYaxis()->SetTitle("SHMS dp(%)");
    taryvsdpps->GetXaxis()->SetTitle("SHMS Ytar(cm)");
    
    TH2F *Wvsdelta = new TH2F("Wvsdelta", "W vs delta", 100, -14, 14, 100, 0.4, 1.6);
    Wvsdelta->GetYaxis()->SetTitle("W(GeV)");
    Wvsdelta->GetXaxis()->SetTitle("delta(%)");

    TH2F *Wvsdeltas = new TH2F("Wvsdeltas", "W vs delta simc", 100, -14, 14, 100, 0.4, 1.6);
    Wvsdeltas->GetYaxis()->SetTitle("W(GeV)");
    Wvsdeltas->GetXaxis()->SetTitle("delta(%)");
    
    //Whats weight
    TH1F *hWeight = new TH1F("Weight","Weight",100,0,0.00001);
    //kinematic variables SIMC
    TH1F *hW = new TH1F("hW", "W", 100, 0.4, 1.6);
    hW->GetXaxis()->SetTitle("W [GeV]");
    hW->GetYaxis()->SetTitle("counts");
    TH1F *hth = new TH1F("hth", "scattering angle theta", 100, 18.5, 23.5);
    //TH1F *hth = new TH1F("hth", "scattering angle theta", 100, 19.0, 25.0);
    //TH1F *hth = new TH1F("hth", "scattering angle theta", 100, 21.0, 28.0);
    hth->GetXaxis()->SetTitle("#theta [degree]");
    hth->GetYaxis()->SetTitle("counts");

    //kinematic variables DATA
    TH1F *hWd = new TH1F("hWd", "hWd", 100, 0.4, 1.6);
    hWd->GetXaxis()->SetTitle("W [GeV]");
    hWd->GetYaxis()->SetTitle("counts");
    TH1F *hthd = new TH1F("hthd", "scattering angle theta", 100, 18.5, 23.5);
    //TH1F *hthd = new TH1F("hthd", "scattering angle theta", 100, 21.0, 28.0);
    hthd->GetXaxis()->SetTitle("#theta [degree]");
    hthd->GetYaxis()->SetTitle("counts");

    Long64_t nentries1 = t->GetEntries();
    std::cout<<"data "<<nentries1<<std::endl;
    for (int j = 0; j < nentries1; j++) {
        t->GetEntry(j);
        if(abs(Emiss_d) < 0.1 && pindex > -1 && hindex > -1 && etottracknorm > 0.8 ){
        hWd->Fill(dataW);
        htarxpd->Fill(htarth);
        htarypd->Fill(htarph);
        ptarxpd->Fill(ptarth);
        ptarypd->Fill(ptarph);
        hdeltad->Fill(htardp);
        pdeltad->Fill(ptardp);
        misse_d->Fill(Emiss_d);
        missp_d->Fill(Pmiss_d);
        h_fp_x_d->Fill(hx_fp_data);
        h_fp_xp_d->Fill(hxp_fp_data);
        h_fp_y_d->Fill(hy_fp_data);
        h_fp_yp_d->Fill(hyp_fp_data);
        s_fp_x_d->Fill(sx_fp_data);
        s_fp_xp_d->Fill(sxp_fp_data);
        s_fp_y_d->Fill(sy_fp_data);
        s_fp_yp_d->Fill(syp_fp_data);
        hQ2d->Fill(dataQ2);
        homd->Fill(dataom);
        hthd->Fill(datath);
        Wvsdelta->Fill(htardp, dataW);
            ytard->Fill(htary);
            Ep = Eb/(1.0+((2.0*Eb/Mp)*(sin(datath* deg2rad/2.0))*(sin(datath* deg2rad/2.0))));
            shms_mom = sqrt((Mp+Eb-Ep)*(Mp+Eb-Ep)-Mp*Mp);
            diff_pmom = smom-shms_mom;
            diff_emom = hmom - Ep; //difference between calculated and central mom.
            delta_cal = (h_spec - Ep)/h_spec*100.0; //calculated delta
            delta_meas = (h_spec - hmom)/h_spec*100.0; //measured delta
            delta_diff_cal = delta_cal - delta_meas;
            hdelta_diff->Fill(delta_diff_cal);
            hdelta_cal->Fill(delta_cal);
            hdelta_meas->Fill(delta_meas);
            delta_fp_x->Fill(hx_fp_data, delta_diff_cal);
            delta_fp_y->Fill(hy_fp_data, delta_diff_cal);
            delta_fp_xp->Fill(hxp_fp_data, delta_diff_cal);
            delta_fp_yp->Fill(hyp_fp_data, delta_diff_cal);
            pmom->Fill(diff_emom);
            diff_mom_vs_theta->Fill(datath, diff_pmom);
            
            //cout<<hmom<<" "<<Ep<<" "<<diff_emom<<" "<<htardp<<" "<<delta_cal<<endl;
            
       }
       
    }

 
    Long64_t nentries = t1->GetEntries();
    std::cout<<"sim "<<nentries<<std::endl;
	for (int i = 0; i < nentries; i++) {
        t1->GetEntry(i);
        if(abs(Emiss_sim) < 0.1){
        double Ef = h_spec * (1.0 + 0.01*hsdelta);
        //omega = Ei - Ef;
        //Q2 = Mp * Mp + 2 * omega * Mp - W * W;
        double theta = TMath::ACos(cos_ts + hsyptar * sin_ts) / TMath::Sqrt( 1. + hsyptar * hsyptar + hsxptar * hsxptar);  // polar scattering angle relative to the beam line //rad
        double thetaDeg = theta / deg2rad;
        double charge = 1.0; //mC
        double dcharge = 5.902; //mC
        double normfac = 0.155477e+8;
        double shmsTE = 0.9974;
        double hmsTE = 0.9464;
        double coinlive = 1.00;
        double wfac = (normfac / nentries) * (dcharge / charge);
        weight_hist = Weight * wfac * coinlive * shmsTE * hmsTE;
      //std::cout<<"weight"<<weight_hist<<std::endl;
            hWeight->Fill(Weight);
       
        //hWd->Fill(dataW, Weight);
        hhtarxp->Fill(hsxptar, weight_hist);
        hhtaryp->Fill(hsyptar, weight_hist);
        ytar->Fill(hsytar, weight_hist);
        hptarxp->Fill(ssxptar, weight_hist);
        hptaryp->Fill(ssyptar, weight_hist);
        hpdelta->Fill(ssdelta, weight_hist);
        hhdelta->Fill(hsdelta, weight_hist);
		hW->Fill(W, weight_hist);
        hom->Fill(om, weight_hist);
        hQ2->Fill(Q2, weight_hist);
        hQ2_sim->Fill(Q2);
        hth->Fill(thetaDeg, weight_hist);
        misse->Fill(Emiss_sim, weight_hist);
        missp->Fill(Pmiss_sim, weight_hist);
        h_fp_x_s->Fill(hx_fp_simc, weight_hist);
        h_fp_xp_s->Fill(hxp_fp_simc, weight_hist);
        h_fp_y_s->Fill(hy_fp_simc, weight_hist);
        h_fp_yp_s->Fill(hyp_fp_simc, weight_hist);
        s_fp_x_s->Fill(sx_fp_simc, weight_hist);
        s_fp_xp_s->Fill(sxp_fp_simc, weight_hist);
        s_fp_y_s->Fill(sy_fp_simc, weight_hist);
        s_fp_yp_s->Fill(syp_fp_simc, weight_hist);
        Wvsdeltas->Fill(hsdelta,W);
       // hist->Fill(weight_hist);
    }
    }
    
    
    
    
/*    TCanvas *c4 = new TCanvas("c4", "W vs delta for run 6009", 1200, 600);
    pmom->Draw();
    c4->SaveAs("run6009.pdf");
    diff_mom_vs_theta->Draw("colz");
    TCanvas *c44 = new TCanvas("c44", "W vs delta for run 6009", 1200, 600);
    Wvsdelta->SetTitle("run 6009");
    Wvsdelta->Draw("colz");
     c44->SaveAs("Wvsdelta6009.pdf");
        TCanvas *c1 = new TCanvas("c1", "target variables", 1200, 600);
        c1->Divide(4,2);
        c1->cd(1);
        TLegend *leg1 = new TLegend(0.1,0.7,0.2,0.9);
        leg1->SetFillColor(0);
        leg1->SetBorderSize(0);
        leg1->SetTextSize(0.045);
        hhtarxp->SetMinimum(0);
        htarxpd->SetMinimum(0);
        leg1->AddEntry(hhtarxp ,"simc","f");
        leg1->AddEntry(htarxpd,"data" ,"f");
    hhtarxp->SetFillColor(kOrange+1);
    hhtarxp->SetLineColor(kOrange+1);
    hhtarxp->SetFillStyle(3008);
    htarxpd->SetFillColor(kBlue-9);
    htarxpd->SetLineColor(kBlue-9);
    htarxpd->SetFillStyle(3008);
        htarxpd->Draw();
        hhtarxp->Draw("hist same");
        leg1->Draw();
        c1->cd(2);
    TLegend *leg2 = new TLegend(0.1,0.7,0.2,0.9);
    leg2->SetFillColor(0);
    leg2->SetBorderSize(0);
    leg2->SetTextSize(0.045);
    leg2->AddEntry(hhtaryp ,"simc","f");
    leg2->AddEntry(htarypd,"data" ,"f");
    hhtaryp->SetFillColor(kOrange+1);
    hhtaryp->SetLineColor(kOrange+1);
    hhtaryp->SetFillStyle(3008);
    htarypd->SetFillColor(kBlue-9);
    htarypd->SetLineColor(kBlue-9);
    htarypd->SetFillStyle(3008);
        htarypd->Draw();
        hhtaryp->Draw("hist same");
    leg2->Draw();
        c1->cd(3);
    TLegend *leg3 = new TLegend(0.1,0.7,0.2,0.9);
    leg3->SetFillColor(0);
    leg3->SetBorderSize(0);
    leg3->SetTextSize(0.045);
    hhdelta->SetMinimum(0);
    hdeltad->SetMinimum(0);
    leg3->AddEntry(hhdelta ,"simc","f");
    leg3->AddEntry(hdeltad,"data" ,"f");
    hhdelta->SetFillColor(kOrange+1);
    hhdelta->SetLineColor(kOrange+1);
    hhdelta->SetFillStyle(3008);
    hdeltad->SetFillColor(kBlue-9);
    hdeltad->SetLineColor(kBlue-9);
    hdeltad->SetFillStyle(3008);
        hdeltad->Draw();
        hhdelta->Draw("hist same");
    leg3->Draw();
        c1->cd(4);
    TLegend *leg21 = new TLegend(0.1,0.7,0.2,0.9);
    leg21->SetFillColor(0);
    leg21->SetBorderSize(0);
    leg21->SetTextSize(0.045);
    ytar->SetMinimum(0);
    ytard->SetMinimum(0);
    leg21->AddEntry(ytar ,"simc","f");
    leg21->AddEntry(ytard,"data" ,"f");
    ytar->SetFillColor(kOrange+1);
    ytar->SetLineColor(kOrange+1);
    ytar->SetFillStyle(3008);
    ytard->SetFillColor(kBlue-9);
    ytard->SetLineColor(kBlue-9);
    ytard->SetFillStyle(3008);
    ytard->Draw();
    ytar->Draw("hist same");
    leg21->Draw();
    c1->cd(5);
    TLegend *leg4 = new TLegend(0.1,0.7,0.2,0.9);
    leg4->SetFillColor(0);
    leg4->SetBorderSize(0);
    leg4->SetTextSize(0.045);
    leg4->AddEntry(hptarxp ,"simc","f");
    leg4->AddEntry(ptarxpd,"data" ,"f");
    hptarxp->SetFillColor(kOrange+1);
    hptarxp->SetLineColor(kOrange+1);
    hptarxp->SetFillStyle(3008);
    ptarxpd->SetFillColor(kBlue-9);
    ptarxpd->SetLineColor(kBlue-9);
    ptarxpd->SetFillStyle(3008);
    ptarxpd->Draw();
        hptarxp->Draw("hist same");
    leg4->Draw();
        c1->cd(6);
    TLegend *leg5 = new TLegend(0.1,0.7,0.2,0.9);
    leg5->SetFillColor(0);
    leg5->SetBorderSize(0);
    leg5->SetTextSize(0.045);
    leg5->AddEntry(hptaryp ,"simc","f");
    leg5->AddEntry(ptarypd,"data" ,"f");
    hptaryp->SetFillColor(kOrange+1);
    hptaryp->SetLineColor(kOrange+1);
    hptaryp->SetFillStyle(3008);
    ptarypd->SetFillColor(kBlue-9);
    ptarypd->SetLineColor(kBlue-9);
    ptarypd->SetFillStyle(3008);
        ptarypd->Draw();
        hptaryp->Draw("hist same");
    leg5->Draw();
        c1->cd(7);
    TLegend *leg6 = new TLegend(0.1,0.7,0.2,0.9);
    leg6->SetFillColor(0);
    leg6->SetBorderSize(0);
    leg6->SetTextSize(0.045);
    leg6->AddEntry(hpdelta ,"simc","f");
    leg6->AddEntry(pdeltad,"data" ,"f");
    hpdelta->SetFillColor(kOrange+1);
    hpdelta->SetLineColor(kOrange+1);
    hpdelta->SetFillStyle(3008);
    pdeltad->SetFillColor(kBlue-9);
    pdeltad->SetLineColor(kBlue-9);
    pdeltad->SetFillStyle(3008);
        pdeltad->Draw();
    hpdelta->Draw("hist same");
    leg6->Draw();
        TCanvas *c2 = new TCanvas("c2", "kinematics", 1200, 800);
        c2->Divide(3,2);
        c2->cd(1);
    TLegend *leg7 = new TLegend(0.1,0.7,0.2,0.9);
    leg7->SetFillColor(0);
    leg7->SetBorderSize(0);
    leg7->SetTextSize(0.045);
    leg7->AddEntry(hW ,"simc","f");
    leg7->AddEntry(hWd,"data" ,"f");
    hW->SetFillColor(kOrange+1);
    hW->SetLineColor(kOrange+1);
    hW->SetFillStyle(3008);
    hWd->SetFillColor(kBlue-9);
    hWd->SetLineColor(kBlue-9);
    hWd->SetFillStyle(3008);
    hW->Draw("hist");
        hWd->Draw("hist same");
    leg7->Draw();
        c2->cd(2);
    TLegend *leg8 = new TLegend(0.1,0.7,0.2,0.9);
    leg8->SetFillColor(0);
    leg8->SetBorderSize(0);
    leg8->SetTextSize(0.045);
    leg8->AddEntry(misse ,"simc","f");
    leg8->AddEntry(misse_d,"data" ,"f");
    misse->SetFillColor(kOrange+1);
    misse->SetLineColor(kOrange+1);
    misse->SetFillStyle(3008);
    misse_d->SetFillColor(kBlue-9);
    misse_d->SetLineColor(kBlue-9);
    misse_d->SetFillStyle(3008);
        misse->Draw("hist");
        misse_d->Draw("hist same");
    leg8->Draw();
        c2->cd(3);
    TLegend *leg9 = new TLegend(0.1,0.7,0.2,0.9);
    leg9->SetFillColor(0);
    leg9->SetBorderSize(0);
    leg9->SetTextSize(0.045);
    missp->SetMinimum(0);
    missp_d->SetMinimum(0);
    leg9->AddEntry(missp ,"simc","f");
    leg9->AddEntry(missp_d,"data" ,"f");
    missp->SetFillColor(kOrange+1);
    missp->SetLineColor(kOrange+1);
    missp->SetFillStyle(3008);
    missp_d->SetFillColor(kBlue-9);
    missp_d->SetLineColor(kBlue-9);
    missp_d->SetFillStyle(3008);
        missp->Draw("hist");
        missp_d->Draw("hist same");
    leg9->Draw();
    c2->cd(4);
    TLegend *leg18 = new TLegend(0.1,0.7,0.2,0.9);
    leg18->SetFillColor(0);
    leg18->SetBorderSize(0);
    leg18->SetTextSize(0.045);
    leg18->AddEntry(hom ,"simc","f");
    leg18->AddEntry(homd,"data" ,"f");
    hom->SetFillColor(kOrange+1);
    hom->SetLineColor(kOrange+1);
    hom->SetFillStyle(3008);
    homd->SetFillColor(kBlue-9);
    homd->SetLineColor(kBlue-9);
    homd->SetFillStyle(3008);
    homd->Draw();
    hom->Draw("hist same");
    leg18->Draw();
    c2->cd(5);
    
    auto *c11 = new TCanvas;
    c11->Divide(2);
    c11->cd(1);
    TLegend *leg19 = new TLegend(0.1,0.7,0.2,0.9);
    leg19->SetFillColor(0);
    leg19->SetBorderSize(0);
    leg19->SetTextSize(0.045);
    hQ2->SetMinimum(0);
    hQ2d->SetMinimum(0);
    leg19->AddEntry(hQ2 ,"simc","f");
    leg19->AddEntry(hQ2d,"data" ,"f");
    hQ2->SetFillColor(kOrange+1);
    hQ2->SetLineColor(kOrange+1);
    hQ2->SetFillStyle(3008);
    hQ2d->SetFillColor(kBlue-9);
    hQ2d->SetLineColor(kBlue-9);
    hQ2d->SetFillStyle(3008);
    hQ2d->Draw();
    hQ2->Draw("hist same");
    hQ2_sim->SetLineColor(2);
    hQ2_sim->Draw("hist same");
    leg19->Draw();
    c11->cd(2);
    hWeight->Draw();
  */
    /*c2->cd(6);
    TLegend *leg20 = new TLegend(0.1,0.7,0.2,0.9);
    leg20->SetFillColor(0);
    leg20->SetBorderSize(0);
    leg20->SetTextSize(0.045);
    hth->SetMinimum(0);
    hthd->SetMinimum(0);
    leg20->AddEntry(hth ,"simc","f");
    leg20->AddEntry(hthd,"data" ,"f");
    hth->SetFillColor(kOrange+1);
    hth->SetLineColor(kOrange+1);
    hth->SetFillStyle(3008);
    hthd->SetFillColor(kBlue-9);
    hthd->SetLineColor(kBlue-9);
    hthd->SetFillStyle(3008);
    hthd->Draw();
    hth->Draw("hist same");
    leg19->Draw();
        TCanvas *c3 = new TCanvas("c3", "focal plane variables", 1200, 600);
        c3->Divide(4,2);
        c3->cd(1);
    TLegend *leg10 = new TLegend(0.1,0.7,0.2,0.9);
    leg10->SetFillColor(0);
    leg10->SetBorderSize(0);
    leg10->SetTextSize(0.045);
    leg10->AddEntry(h_fp_x_s ,"simc","f");
    leg10->AddEntry(h_fp_x_d,"data" ,"f");
    h_fp_x_s->SetFillColor(kOrange+1);
    h_fp_x_s->SetLineColor(kOrange+1);
    h_fp_x_s->SetFillStyle(3008);
    h_fp_x_d->SetFillColor(kBlue-9);
    h_fp_x_d->SetLineColor(kBlue-9);
    h_fp_x_d->SetFillStyle(3008);
        h_fp_x_d->Draw();
      h_fp_x_s->Draw("hist same");
    leg10->Draw();
        c3->cd(2);
    TLegend *leg11 = new TLegend(0.1,0.7,0.2,0.9);
    leg11->SetFillColor(0);
    leg11->SetBorderSize(0);
    leg11->SetTextSize(0.045);
    leg11->AddEntry(h_fp_xp_s ,"simc","f");
    leg11->AddEntry(h_fp_xp_d,"data" ,"f");
    h_fp_xp_s->SetFillColor(kOrange+1);
    h_fp_xp_s->SetLineColor(kOrange+1);
    h_fp_xp_s->SetFillStyle(3008);
    h_fp_xp_d->SetFillColor(kBlue-9);
    h_fp_xp_d->SetLineColor(kBlue-9);
    h_fp_xp_d->SetFillStyle(3008);
        h_fp_xp_d->Draw();
        h_fp_xp_s->Draw("hist same");
    leg11->Draw();
        c3->cd(3);
    TLegend *leg12 = new TLegend(0.1,0.7,0.2,0.9);
    leg12->SetFillColor(0);
    leg12->SetBorderSize(0);
    leg12->SetTextSize(0.045);
    leg12->AddEntry(h_fp_y_s ,"simc","f");
    leg12->AddEntry(h_fp_y_d,"data" ,"f");
    h_fp_y_s->SetFillColor(kOrange+1);
    h_fp_y_s->SetLineColor(kOrange+1);
    h_fp_y_s->SetFillStyle(3008);
    h_fp_y_d->SetFillColor(kBlue-9);
    h_fp_y_d->SetLineColor(kBlue-9);
    h_fp_y_d->SetFillStyle(3008);
        h_fp_y_d->Draw();
        h_fp_y_s->Draw("hist same");
    leg12->Draw();
        c3->cd(4);
    TLegend *leg13 = new TLegend(0.1,0.7,0.2,0.9);
    leg13->SetFillColor(0);
    leg13->SetBorderSize(0);
    leg13->SetTextSize(0.045);
    h_fp_yp_s->SetMinimum(0);
    h_fp_yp_d->SetMinimum(0);
    leg13->AddEntry(h_fp_yp_s ,"simc","f");
    leg13->AddEntry(h_fp_yp_d,"data" ,"f");
    h_fp_yp_s->SetFillColor(kOrange+1);
    h_fp_yp_s->SetLineColor(kOrange+1);
    h_fp_yp_s->SetFillStyle(3008);
    h_fp_yp_d->SetFillColor(kBlue-9);
    h_fp_yp_d->SetLineColor(kBlue-9);
    h_fp_yp_d->SetFillStyle(3008);
        h_fp_yp_d->Draw();
        h_fp_yp_s->Draw("hist same");
    leg13->Draw();
        c3->cd(5);
    TLegend *leg14 = new TLegend(0.1,0.7,0.2,0.9);
    leg14->SetFillColor(0);
    leg14->SetBorderSize(0);
    leg14->SetTextSize(0.045);
    leg14->AddEntry(s_fp_x_s ,"simc","f");
    leg14->AddEntry(s_fp_x_d,"data" ,"f");
    s_fp_x_s->SetFillColor(kOrange+1);
    s_fp_x_s->SetLineColor(kOrange+1);
    s_fp_x_s->SetFillStyle(3008);
    s_fp_x_d->SetFillColor(kBlue-9);
    s_fp_x_d->SetLineColor(kBlue-9);
    s_fp_x_d->SetFillStyle(3008);
        s_fp_x_d->Draw();
        s_fp_x_s->Draw("hist same");
    leg14->Draw();
        c3->cd(6);
    TLegend *leg15 = new TLegend(0.1,0.7,0.2,0.9);
    leg15->SetFillColor(0);
    leg15->SetBorderSize(0);
    leg15->SetTextSize(0.045);
    leg15->AddEntry(s_fp_xp_s ,"simc","f");
    leg15->AddEntry(s_fp_xp_d,"data" ,"f");
    s_fp_xp_s->SetFillColor(kOrange+1);
    s_fp_xp_s->SetLineColor(kOrange+1);
    s_fp_xp_s->SetFillStyle(3008);
    s_fp_xp_d->SetFillColor(kBlue-9);
    s_fp_xp_d->SetLineColor(kBlue-9);
    s_fp_xp_d->SetFillStyle(3008);
        s_fp_xp_d->Draw();
        s_fp_xp_s->Draw("hist same");
    leg15->Draw();
        c3->cd(7);
    TLegend *leg16 = new TLegend(0.1,0.7,0.2,0.9);
    leg16->SetFillColor(0);
    leg16->SetBorderSize(0);
    leg16->SetTextSize(0.045);
    s_fp_y_s->SetMinimum(0);
    s_fp_y_d->SetMinimum(0);
    leg16->AddEntry(s_fp_y_s ,"simc","f");
    leg16->AddEntry(s_fp_y_d,"data" ,"f");
    s_fp_y_s->SetFillColor(kOrange+1);
    s_fp_y_s->SetLineColor(kOrange+1);
    s_fp_y_s->SetFillStyle(3008);
    s_fp_y_d->SetFillColor(kBlue-9);
    s_fp_y_d->SetLineColor(kBlue-9);
    s_fp_y_d->SetFillStyle(3008);
        s_fp_y_d->Draw();
              s_fp_y_s->Draw("hist same");
    leg16->Draw();
        c3->cd(8);
    TLegend *leg17 = new TLegend(0.1,0.7,0.2,0.9);
    leg17->SetFillColor(0);
    leg17->SetBorderSize(0);
    leg17->SetTextSize(0.045);
    leg17->AddEntry(s_fp_yp_s,"simc","f");
    leg17->AddEntry(s_fp_yp_d,"data" ,"f");
    s_fp_yp_s->SetFillColor(kOrange+1);
    s_fp_yp_s->SetLineColor(kOrange+1);
    s_fp_yp_s->SetFillStyle(3008);
    s_fp_yp_d->SetFillColor(kBlue-9);
    s_fp_yp_d->SetLineColor(kBlue-9);
    s_fp_yp_d->SetFillStyle(3008);
        s_fp_yp_d->Draw();
            s_fp_yp_s->Draw("hist same");
    leg17->Draw();
    
    //c1->SaveAs("targetvariables_6009_old.pdf");
    //c2->SaveAs("kinematics_6009_old.pdf");
    //c3->SaveAs("fpvariables_6009_old.pdf");
    //TCanvas *c1 = new TCanvas("c1", "delta", 1200, 600);
    //c1->cd();
    //hdelta_cal->Draw();
    //hdeltad->SetLineColor(kRed);
    //hdeltad->Draw();*/
    
    }





