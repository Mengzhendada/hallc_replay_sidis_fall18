#include "ROOT/RDataFrame.hxx"
#include "TCanvas.h"
#include <iostream>
#include <TH1.h>
#include "TMath.h"
#include <TF1.h>

#include <fstream>
#include <vector>
#include <string>

//to read in data in .json file and assign to vector data. use data[linenum][worknum] to call. CAUTION::data[0][i]saves run number, data[1][i]saves momentum, data[2][i]saves angle,etc.  
void readjson(std::ifstream& ifs, std::vector<std::vector<double>>& data){
 ifs.ignore(1000,'\n');
 std::string temps;
 int tempi;
 ifs >>temps;
 if(!ifs.good() or temps.size()<3) return;
 tempi = temps.size()-3;
 std::cout<<temps.substr(1,tempi) <<std::endl;
 data[0].push_back(std::stod(temps.substr(1,tempi)));
 ifs.ignore(1000,'\n');
 for(auto it = data.begin() +1; it!=data.end()-1;++it){
 ifs >>temps>>temps;
 tempi = temps.size()-1;
 std::cout <<temps.substr(0,tempi) << std::endl;
 it->push_back(std::stod(temps.substr(0,tempi)));
 ifs.ignore(1000,'\n');
 }
 ifs>>temps>>temps;
 std::cout<<temps<<std::endl;
 data[data.size()-1].push_back(std::stod(temps));
 ifs.ignore(1000,'\n');
}

//main function
void csvelas(){
 double Eb = 10.5965;
 double Mp = 0.93825;
 std::ifstream in("elasrunlist.json");
  //data[j] how many lines(j) in one unit
  std::vector<std::vector<double>> data(10);
  while(in.good()){
    readjson(in,data);
  }
TH2F *h_Ep_diff = new TH2F("Ee_diff","difference of hms momentum and hms calculated momentum",10,6008,6018,100,-0.5,0.7);
  //cout json file
/*for(auto& line: data){
for(auto& word: line){
  std::cout<<word<<'\t';}
std::cout<<'\n';}*/
  //int nruns = data[0].size();
  //ROOT::RDataFrame d(nruns);
  //  int i(0);
  //d.Define("runnumber",[&i,&data](){return data[0][i++];});
  /* .Define("Ep_measure",[&i,&data](){return data[1][i];})
   .Define("Thp_measure",[&i,&data](){return data[2][i++];})
   .Define("Ep_calculated",[&Eb,&Mp](double thp_measure){return Eb/(1.0+((2.0*Eb/Mp)*(sin(thp_measure*3.1415926/360))*(sin(thp_measure* 3.1415926/360))));},{"Thp_measure"})
   .Define("Ep_diff",[](double epmeasure,double epcalculated){return epmeasure-epcalculated;},{"Ep_measure","Ep_calculated"});
*/
  //auto h_momdiff = d.Histo2D({"Difference between calculated momentum and real momentum","momentum difference",8,6009,6017,10,-1,1},"runnumber","Ep_diff");
//auto h_momdiff = d.Histo1D({"Ep","Ep",100,-1,1},"runnumber");
  //auto c1 = new TCanvas;
//h_momdiff->DrawCopy();

  //loop over different runs. how many rows(i) in one(0) line
for(int i = 0; i<data[0].size(); ++i){
double Ep = Eb/(1.0+((2.0*Eb/Mp)*(sin(data[2][i]*3.1415926/360))*(sin(data[2][i]* 3.1415926/360))));
double Ep_diff = Ep-data[1][i];
int runnumber = data[0][i];
h_Ep_diff->Fill(runnumber,Ep_diff);
//find correct root file with correct runnumber. 
  std::string rootfile_data = std::string("/group/c-csv/shuo/replay/ROOTfiles/coin_replay_production_");
std::string rootfile_sim = std::string("/u/home/shuojia/simc_gfortran/worksim/csv");
std::cout<<data[0][i]<<" data run check" <<std::to_string(data[0][i])<<std::endl;
rootfile_data += std::to_string((int)data[0][i]) + "_-1.root";
rootfile_sim += std::to_string((int)data[0][i])+".root";
std::cout<<rootfile_sim<<std::endl;
ROOT::RDataFrame ddata("T",rootfile_data);
ROOT::RDataFrame dsim("h666",rootfile_sim);
//building dataframe for data
auto d0data = ddata.Define("shms_e_EoverP",[](double& EOverP){return EOverP>0.8;},{"P.cal.etottracknorm"})
.Filter([](double emiss){return  emiss<0.1 && emiss>-0.1;},{"P.kin.secondary.emiss"})
//.Filter([](double etottracknorm){return etottracknorm>0.8;},{"P.cal.etottracknorm"})
.Filter([](double hindex){return hindex>-1;},{"H.gtr.index"})
.Filter([](double pindex){return pindex>-1;},{"P.gtr.index"})
.Define("Ep_cal",[&Eb,&Mp](double th){return  Eb/(1.0+((2.0*Eb/Mp)*(sin(th*3.1415926/360))*(sin(th* 3.1415926/360))));},{"H.kin.primary.scat_ang_deg"})
.Define("Ep_diff",[](double Ee,double hmom){return Ee-hmom;},{"Ep_cal","H.gtr.p"});
//building dataframe for simulation
double charge = 1.0; //mC
double dcharge = data[5][i]; //mC read from /REPORT_OUTPUT/COIN/PRODUCTION/replay_coin_production_num_-1.root
//std::cout<<"dcharge check"<<dcharge<<std::endl;
double shmsTE = data[7][i];//as last
//std::cout<<"shmsTE check"<<shmsTE<<std::endl;
double hmsTE = data[8][i];//as last
//std::cout<<"hmsTE check"<<hmsTE<<std::endl;
double coinlive = data[6][i];//as last
//std::cout<<"coinlive check "<<coinlive<<std::endl;
double normfac = data[9][i];//from /simc/outfiles/csvnum.hist
auto nentries = dsim.Count();
double wfac = (normfac / *nentries) *(dcharge /charge);
//double wfac = dcharge/charge;
std::cout<<"wfac "<<wfac<<std::endl;
auto weightcalculate = [wfac,coinlive,shmsTE,hmsTE](float weight){return wfac*coinlive*shmsTE*hmsTE*weight;};
auto d0sim_withoutweight = dsim.Define("emiss",[](float emiss){return emiss<0.1 && emiss>-0.1;},{"Em"});
auto d0sim = dsim.Define("weight",weightcalculate,{"Weight"})
.Filter([](float emiss){return emiss<0.1 && emiss>-0.1;},{"Em"});
//.Filter([](float EOVerP){return EOverP>0.8},{""});

std::cout<<*d0sim_withoutweight.Count()<<" "<<*d0sim.Count()<<std::endl;
//auto h_Q2_without = ddata.Histo1D({"Q2 data","Q2 data",100,7,12},"H.kin.primary.Q2");

//building histo for data
auto h_Q2_data = d0data.Histo1D({"Q2 data","Q2 data",100,7,12},"H.kin.primary.Q2");
auto h_W_data = d0data.Histo1D({"W data","W d",100,0.4,1.6},"H.kin.primary.W");
h_W_data->Fit("gaus","O","",0.4,1.6);
TF1 *h_W_data_fit= h_W_data->GetFunction("gaus");
h_W_data_fit->SetLineColor(3);
double h_W_data_mean = h_W_data_fit->GetParameter(1);
double h_W_data_sigm = h_W_data_fit->GetParameter(2);
//std::cout<<"data mean "<<h_W_data_mean<<std::endl;
auto h_Emiss_d = d0data.Histo1D({"Missing Energy data","Missing E data",100,-0.2,0.2},"P.kin.secondary.emiss");
auto h_Pmiss_d = d0data.Histo1D({"Missing Momentum data","Missing P data",100,-0.2,0.2},"P.kin.secondary.pmiss");
auto h_om_d = d0data.Histo1D({"Omega data","Om d",100,4.0,6.4},"H.kin.primary.omega");

//focal plane data
auto h_sx_fp_data = d0data.Histo1D({"shms fp x data","shms fp x data",100,-30,15},"P.dc.x_fp");
auto h_sxp_fp_data = d0data.Histo1D({"shms fp xp data","shms fp xp data",100,-0.08,0.06},"P.dc.xp_fp");
auto h_sy_fp_data = d0data.Histo1D({"shms fp y data","shms fp y data",100,-20,10},"P.dc.y_fp");
auto h_syp_fp_data = d0data.Histo1D({"shms fp yp data","shms fp yp data",100,-0.04,0.03},"P.dc.yp_fp");
auto h_hx_fp_data = d0data.Histo1D({"hms fp x data","hms fp x data",100,-30,30},"H.dc.x_fp");
auto h_hxp_fp_data = d0data.Histo1D({"hms fp xp data","hms fp xp data",100,-0.04,0.04},"H.dc.xp_fp");
auto h_hy_fp_data = d0data.Histo1D({"hms fp y data","hms fp y data",100,-20,30},"H.dc.y_fp");
auto h_hyp_fp_data = d0data.Histo1D({"hms fp yp data","hms fp yp data",100,-0.03,0.03},"H.dc.yp_fp");


//good track
auto h_htarxpd = d0data.Histo1D({"hms xp_tar","htarxpd",100,-0.1,0.1},"H.gtr.th");
auto h_htarypd = d0data.Histo1D({"hms yp_tar","htarypd",100,-0.1,0.1},"H.gtr.ph");
auto h_hdeltad = d0data.Histo1D({"hms dp","hdeltad",100,-14,4.0},"H.gtr.dp");
auto h_ptarxpd = d0data.Histo1D({"shms xp_tar","ptarxpd",100,-0.1,0.1},"P.gtr.th");
auto h_ptarypd = d0data.Histo1D({"shms yp_tar","ptarxpd",100,-0.1,0.1},"P.gtr.ph");
auto h_pdeltad = d0data.Histo1D({"shms dp","ptarxpd",100,-14,4},"P.gtr.dp");

//
auto h_Wvsxfp_data = d0data.Histo2D({"W vs. x focal plane","W:x",100,-2,2,100,0.4,1.6},"H.dc.x_fp","H.kin.primary.W");
auto h_Wvsptardp_data = d0data.Histo2D({"W vs. ptardp","W:ptardp",100,-0.2,0.2,100,0.4,1.6},"P.gtr.dp","H.kin.primary.W");
auto h_Wvsptarth_data = d0data.Histo2D({"W vs. ptarth","W:ptarth",100,-0.2,0.2,100,0.4,1.6},"P.gtr.th","H.kin.primary.W");
auto h_Wvsptarph_data = d0data.Histo2D({"W vs. ptarph","W:ptarph",100,-0.2,0.2,100,0.4,1.6},"P.gtr.ph","H.kin.primary.W");
auto h_Ep_diff = d0data.Histo1D({"hms momentum difference","hms mom diff",100,-1,1},"Ep_diff");
auto h_Wvshmsmomdiff_data = d0data.Histo2D({"W vs. hms momentum difference","W vs. hms_mom_diff",100,-1,1,100,0.4,1.6},"H.kin.primary.W","Ep_diff");
auto diff_mom_vs_theta = d0data.Histo2D({"difference momentum vs. hms theta","Mom_diff vs. hms th",100,-0.5,0.7,100,17,22},"Ep_diff","H.kin.primary.scat_ang_deg");
auto h_fpxvsmomdiff_data = d0data.Histo2D({"fp x vs. momentum difference","fp x vs. mom_diff",100,-1,1,100,-30,30},"Ep_diff","H.dc.x_fp");
auto h_fpxpvsmomdiff_data = d0data.Histo2D({"fp xp vs. momentum difference","fp xp vs. mom_diff",100,-1,1,100,-0.06,0.06},"Ep_diff","H.dc.xp_fp");
auto h_fpyvsmomdiff_data = d0data.Histo2D({"fp y vs. momentum difference","fp y vs. mom_diff",100,-1,1,100,20,40},"Ep_diff","H.dc.y_fp");
auto h_fpxpvsmomdiff_data = d0data.Histo2D({"fp yp vs. momentum difference","fp yp vs. mom_diff",100,-1,1,100,-0.02,0.03},"Ep_diff","H.dc.yp_fp");


//building histo for simulation
auto h_Q2_sim = d0sim.Histo1D({"Q2 simulation","Q2 sim",100,7,12},"Q2","weight");
auto h_W_sim = d0sim.Histo1D({"W simulation","W sim",100,0.4,1.6},"W","weight");
h_W_sim->Fit("gaus","O","",0.4,1.6);
TF1 *h_W_sim_fit = h_W_sim->GetFunction("gaus");
double h_W_sim_mean = h_W_sim_fit->GetParameter(1);
std::cout<<"sim mean "<<h_W_sim_mean<< std::endl;
auto h_Q2_sim_without = d0sim_withoutweight.Histo1D({"Q2 simulation","Q2 sim",100,7,12},"Q2");
auto h_weight = d0sim_withoutweight.Histo1D({"Weight","Weight",100,0,0.00001},"Weight");

//auto h_W_x_fp_data = d

//auto n = d0data.Count();
//std::cout<<"n"<<*n<<std::endl;

auto h_sx_fp_sim = d0sim.Histo1D({"shms fp x sim","shms fp x sim",100,-30,15},"ssxfp");
auto h_sxp_fp_sim = d0sim.Histo1D({"shms fp xp sim","shms fp xp sim",100,-0.08,0.06},"ssxpfp");
auto h_sy_fp_sim = d0sim.Histo1D({"shms fp y sim","shms fp y sim",100,-20,10},"ssyfp");
auto h_syp_fp_sim = d0sim.Histo1D({"shms fp yp sim","shms fp yp sim",100,-0.04,0.03},"ssypfp");
auto h_hx_fp_sim = d0sim.Histo1D({"hms fp x sim","hms fp x sim",100,-30,30},"hsxfp");
auto h_hxp_fp_sim = d0sim.Histo1D({"hms fp xp sim","hms fp xp sim",100,-0.04,0.04},"hsxpfp");
auto h_hy_fp_sim = d0sim.Histo1D({"hms fp y sim","hms fp y sim",100,-20,30},"hsyfp");
auto h_hyp_fp_sim = d0sim.Histo1D({"hms fp yp sim","hms fp yp sim",100,-0.03,0.03},"hsypfp");

TCanvas *c_fp = new TCanvas;
c_fp->Divide(2,4);
c_fp->cd(1);
h_sx_fp_data->DrawCopy();
h_sx_fp_sim->DrawCopy("same");
c_fp->cd(2);
h_sxp_fp_data->DrawCopy();
h_sxp_fp_sim->DrawCopy("same");
c_fp->cd(3);
h_sy_fp_data->DrawCopy();
h_sy_fp_sim->DrawCopy("same");
c_fp->cd(4);
h_syp_fp_data->DrawCopy();
h_syp_fp_sim->DrawCopy("same");
c_fp->cd(5);
h_hx_fp_data->DrawCopy();
h_hx_fp_sim->DrawCopy("same");
c_fp->cd(6);
h_hxp_fp_data->DrawCopy();
h_hxp_fp_sim->DrawCopy("same");
c_fp->cd(7);
h_hy_fp_data->DrawCopy();
h_hy_fp_sim->DrawCopy("same");
c_fp->cd(8);
h_hyp_fp_data->DrawCopy();
h_hyp_fp_sim->DrawCopy("same");
c_fp->SaveAs((std::string("csvresult/c_fp_")+std::to_string((int)data[0][i])+".pdf").c_str());

TCanvas *c_kin= new TCanvas;
c_kin->Divide(2,3);
c_kin->cd(1);
//h_Q2_data->DrawCopy();
h_Q2_sim->SetLineColor(2);
h_Q2_sim->DrawCopy();
h_Q2_data->DrawCopy("same");
//h_Q2_sim_without->SetLineColor(3);
//h_Q2_sim_without->DrawCopy("same");
c_kin->Print("Q2");
c_kin->cd(2);
//h_weight->DrawCopy();
//TLegend *leg2 = new TLegend(0.55,0.65,0.76,0.82);
h_W_data->SetFillColor(kBlue-9);
h_W_data->SetFillStyle(3008);
h_W_data->DrawCopy("hist");
h_W_sim->SetLineColor(2);
h_W_sim->SetFillColor(kRed+2);
h_W_sim->SetFillStyle(3008);

h_W_sim->DrawCopy("hist same");
//leg2->AddEntry(h_W_data,"data mean &h_W_data_mean","f");
//leg2->AddEntry(h_W_sim,"sim mean &h_W_sim_mean","f");
c_kin->cd(3);
h_Emiss_d->DrawCopy();
c_kin->cd(4);
h_Pmiss_d->DrawCopy();
c_kin->cd(5);
h_om_d->DrawCopy();

TCanvas *c_hist2 = new TCanvas;
c_hist2->Divide(3,3);
c_hist2->cd(1);
h_Wvshmsmomdiff_data->DrawCopy();
c_hist2->cd(3);
h_Wvsptardp_data->DrawCopy();
c_hist2->cd(4);
h_Wvsptardp_data->DrawCopy();
c_hist2->cd(5);
h_Wvsptarth_data->DrawCopy();
c_hist2->cd(6);
h_Wvsptarph_data->DrawCopy();
c_hist2->cd(7);
h_Ep_diff->DrawCopy();

c_kin->SaveAs((std::string("csvresult/c_kin_")+std::to_string((int)data[0][i])+".pdf").c_str());
c_hist2->SaveAs((std::string("csvresult/c_hist2_")+std::to_string((int)data[0][i])+".pdf").c_str());          
           }
auto c2 = new TCanvas;
h_Ep_diff->Draw();
h_Ep_diff->SetMarkerStyle(20);
c2->SaveAs(std::string("csvresult/Epdiff.pdf").c_str());
return 0;

}
