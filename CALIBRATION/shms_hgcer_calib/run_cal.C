#include <TProof.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>

void run_cal(Int_t RunNumber = 0, Int_t NumEvents = 0, Int_t coin = 0)
{
  if (RunNumber == 0)
    {
      cout << "Enter a Run Number (-1 to exit): ";
      cin >> RunNumber;
      if (RunNumber <= 0) return;
    }
  if (NumEvents == 0)
    {
      cout << "\nNumber of Events to analyze: ";
      cin >> NumEvents;
      }
  if (coin == 0)
    {
      cout << "\nIf this is a coincident run enter 1: ";
      cin >> coin;
    }

  cin.ignore(numeric_limits<streamsize>::max(), '\n');

  string calib_raw;
  cout << "\nEnter options for calibration  (enter NA to skip): ";
  getline(std::cin, calib_raw);
  TString calib_option = calib_raw;
  
  string eff_raw;
  cout << "\nEnter options for efficiency (enter NA to skip): ";
  getline(std::cin, eff_raw);
  TString eff_option = eff_raw;

  cout << "\n\n";

  TChain ch("T");
  if (coin == 1) ch.Add(Form("../../ROOTfiles/shms_coin_replay_production_all_%d_%d.root", RunNumber, NumEvents));
  else ch.Add(Form("../../ROOTfiles/shms_replay_production_all_%d_%d.root", RunNumber, NumEvents));
  TProof *proof = TProof::Open("workers=4");
  proof->SetProgressDialog(0);  
  ch.SetProof();

  if (calib_option != "NA")
    {
      //Perform a "preprocess" of replay to extact timing information
      /*
      ch.Process("preprocess.C+",calib_option);
      if (calib_option.Contains("showall"))
	{
	  TString preprocessing_input;
	  cout << "\n\nPlease verify if timing cuts are correct (y/n): ";
	  cin >> preprocessing_input;
	  if (preprocessing_input != "y") return;	  
	}
      
      //Obtain cut information from preprocessing
      TFile preprocess_file("Timing_Cuts.root");
      TNtuple *input_data = new TNtuple("input_data","Storage for Client Timing Information","Mean:Std");
      preprocess_file.GetObject("timing_data",input_data);
      float *timing_row_content;
      for (Int_t irow = 0; irow < input_data->GetEntries(); irow++)
	{
	  input_data->GetEntry(irow);
	  timing_row_content = input_data->GetArgs();
	  calib_option.Append(Form(" %f %f",timing_row_content[0],timing_row_content[1]));
	}
      preprocess_file.Close();
      */
      //Start calibration process
      ch.Process("calibration.C+",calib_option);

      cout << "\n\nUpdate calibration constants with the better estimate (y/n)? ";
      
      TString user_input;
      cin >> user_input;
      if (user_input == "y")
	{
	  ifstream temp;
	  temp.open("calibration_temp.txt", ios::in);
	  if (temp.is_open())
	    {
	      if (calib_option.Contains("NGC")) rename("calibration_temp.txt", Form("../../PARAM/SHMS/NGCER/CALIB/pngcer_calib_%d.param", RunNumber));

	      else rename("calibration_temp.txt", Form("../../PARAM/SHMS/HGCER/CALIB/phgcer_calib_%d.param", RunNumber));
	    }

	  else cout << "Error opening calibration constants, may have to update constants manually!" << endl;
	   
	}

      else
	{
	  remove("calibration_temp.txt"); 
	}
    }

  //if (eff_option != "NA") ch.Process("efficiencies.C+",eff_option);
}
