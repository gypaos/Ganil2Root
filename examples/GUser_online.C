// File : GUser.C
// Author: Luc Legeard
//////////////////////////////////////////////////////////////////////////////
//
// Class GUser
//
// Class for User treatment
//
////////////////////////////////////////////////////////////////////////////

// ---------------------------------------------------------------------------
// ***************************************************************************
// *                                                                         *
// *   This program is free softare; you can redistribute it and/or modify  *
// *   it under the terms of the GNU General Public License as published by  *
// *   the Free Software Foundation; either version 2 of the License, or     *
// *   (at your option) any later version.                                   *
// *                                                                         *
// ***************************************************************************/


#include "./GUser_online.h"

#include "TROOT.h"
#include <TProfile.h> 
#include <TRandom.h>

#include "/home/e552/NPTool/NPLib/include/CalibrationManager.h"

#include <iostream>

ClassImp (GUser); 

GUser::GUser (GDevice* _fDevIn, GDevice* _fDevOut)
{ 
  // Constructor/initialisator of Acquisition object 
  // entry:
  // - Input Device
  // - Output Device
  fDevIn   = _fDevIn;
  fDevOut  = _fDevOut;

  // instantiate detector objects
  fMust2        = new TMust2();
  fCATS         = new TCATS();
  fSSSD         = new TSSSD();
  fTrigger	= new TTrigger();
  fTac		= new TTac();
  fPlastic	= new TPlastic();
  fChio_an	= new TChio_an();
  fChio_dig	= new TChio_dig();
  fLise	        = new TLise();

  MySpectraList = GetSpectra();
  cout << "Spectra done" << endl;  
}


GUser::~GUser()  
{
  // Destructor of class GUser
  delete fMust2;
  delete fCATS;
  delete fSSSD;
  delete fTrigger;
  delete fTac;
  delete fPlastic;
  delete fChio_an;
  delete fChio_dig;
  delete fLise;

  gROOT->cd();
}


void GUser::InitUser()
{
  // Initialisation for global  user treatement
 
  cout<<  "- ---------< Init User  >------------------!\n";
		
  ////////////////////////////////////
  //       Read geometry file       //
  ////////////////////////////////////
  fMust2 -> GetMust2Physics() -> ReadConfiguration("/home/e552/NPTool/Inputs/DetectorConfiguration/e552.detector");
  fCATS  -> GetCATSPhysics()  -> ReadConfiguration("/home/e552/NPTool/Inputs/DetectorConfiguration/e552.detector");
  fSSSD  -> GetSSSDPhysics()  -> ReadConfiguration("/home/e552/NPTool/Inputs/DetectorConfiguration/e552.detector");
  fChio_an -> GetChio_anPhysics()  -> ReadConfiguration("/home/e552/NPTool/Inputs/DetectorConfiguration/e552.detector");
  fChio_dig -> GetChio_digPhysics()  -> ReadConfiguration("/home/e552/NPTool/Inputs/DetectorConfiguration/e552.detector");
  fPlastic -> GetPlasticPhysics() -> ReadConfiguration("/home/e552/NPTool/Inputs/DetectorConfiguration/e552.detector");
   
  ////////////////////////////////////
  // instantiate CalibrationManager //
  ////////////////////////////////////
  CalibrationManager::getInstance("Calibrations.txt");

  ////////////////////////////////////////////////////
  // register calibration parameters from detectors //
  ////////////////////////////////////////////////////
  fMust2 -> GetMust2Physics() -> AddParameterToCalibrationManager();
  fCATS  -> GetCATSPhysics()  -> AddParameterToCalibrationManager();
  fSSSD  -> GetSSSDPhysics()  -> AddParameterToCalibrationManager();
  // fChio_an -> GetChio_anPhysics()  -> AddParameterToCalibrationManager();
   
  ///////////////////////////////////
  // read calibration coefficients //
  ///////////////////////////////////
  CalibrationManager::getInstance()->LoadParameterFromFile();

  cout << "Start Loading Spectra"<< endl;
  TString name;
 
  
	hTRIGGER		= new TH1I("Trigger","Trigger on GMT", 17, -0.5, 16.5);
	GetSpectra()->AddSpectrum(hTRIGGER);

	
  //////////////////////////////
  //instantiate CATS  MONODIMs//
  //////////////////////////////
  for (Int_t i = 0; i < numberCats; i++) {
    // STRX_MULT
    name = Form("CATS%d_STRX_MULT", i+1);
    CATS_STRX_MULT[i] = new TH1I(name, name, 28, 1, 29);
    GetSpectra()->AddSpectrum(CATS_STRX_MULT[i],(char *)"CATS/BRUT/CTRL");

    // STRY_MULT
    name = Form("CATS%d_STRY_MULT", i+1);
    CATS_STRY_MULT[i] = new TH1I(name, name, 28, 1, 29);
    GetSpectra()->AddSpectrum(CATS_STRY_MULT[i],(char *)"CATS/BRUT/CTRL");

    // STRX_MAX
    name = Form("CATS%d_STRX_MAX", i+1);
    CATS_STRX_MAX[i] = new TH1I(name, name, 28, 1, 29);
    GetSpectra()->AddSpectrum(CATS_STRX_MAX[i],(char *)"CATS/CAL/CTRL");

    // STRY_MAX
    name = Form("CATS%d_STRY_MAX", i+1);
    CATS_STRY_MAX[i] = new TH1I(name, name, 28, 1, 29);
    GetSpectra()->AddSpectrum(CATS_STRY_MAX[i],(char *)"CATS/CAL/CTRL");

    // STRX_Q3
    name = Form("CATS%d_STRX_Q3", i+1);
    CATS_STRX_Q3[i] = new TH1F(name, name, 512, 0, 16384);
    GetSpectra()->AddSpectrum(CATS_STRX_Q3[i],(char *)"CATS/CAL/CTRL");

    // STRY_Q3
    name = Form("CATS%d_STRY_Q3", i+1);
    CATS_STRY_Q3[i] = new TH1F(name, name, 512, 0, 16384);
    GetSpectra()->AddSpectrum(CATS_STRY_Q3[i],(char *)"CATS/CAL/CTRL");
      
  }

  //////////////////////////////
  // instantiate CATS  BIDIMs //
  //////////////////////////////
  for (Int_t i = 0; i < numberCats; i++) {
    // STRX_Q_BRU
    name = Form("CATS%d_STRX_Q_BRU", i+1);
    CATS_STRX_Q_BRU[i] = new TH2I(name, name, 28, 1, 29, 512, 0, 16384);
    GetSpectra()->AddSpectrum(CATS_STRX_Q_BRU[i],(char *)"CATS/BRUT/STRQ");

    // STRY_Q_BRU
    name = Form("CATS%d_STRY_Q_BRU", i+1);
    CATS_STRY_Q_BRU[i] = new TH2I(name, name, 28, 1, 29, 512, 0, 16384);
    GetSpectra()->AddSpectrum(CATS_STRY_Q_BRU[i],(char *)"CATS/BRUT/STRQ");

    // STRX_Q_CAL //no idea what scale should be!
    name = Form("CATS%d_STRX_Q_CAL", i+1);
    CATS_STRX_Q_CAL[i] = new TH2I(name, name, 28, 1, 29, 600, 0, 15000);  
    GetSpectra()->AddSpectrum(CATS_STRX_Q_CAL[i],(char *)"CATS/CAL/STRQ");

    // STRY_Q_CAL //no idea what scale should be!
    name = Form("CATS%d_STRY_Q_CAL", i+1);
    CATS_STRY_Q_CAL[i] = new TH2I(name, name, 28, 1, 29, 600, 0, 15000);
    GetSpectra()->AddSpectrum(CATS_STRY_Q_CAL[i],(char *)"CATS/CAL/STRQ");

    // CHARGE_XY
    name = Form("CATS%d_CHARGE_XY", i+1);
    CATS_CHARGE_XY[i] = new TH2I(name, name, 600, 0, 15000, 600, 0, 15000);
    GetSpectra()->AddSpectrum(CATS_CHARGE_XY[i],(char *)"CATS/CAL/CTRL");
      
    // XY_MAX
    name = Form("CATS%d_XY_MAX", i+1);
    CATS_XY_MAX[i] = new TH2I(name, name, 28, 1, 29, 28, 1, 29);
    GetSpectra()->AddSpectrum(CATS_XY_MAX[i],(char *)"CATS/CAL/CTRL");
  
    // XY_POS
    name = Form("CATS%d_XY_POS", i+1);
    CATS_XY_POS[i] = new TH2I(name, name, 700, -35, 35, 700, -35, 35);
    GetSpectra()->AddSpectrum(CATS_XY_POS[i],(char *)"CATS/CAL/CTRL");

  }
  // XY_TARGET
  // bad reconstructions end up in channel 100 or 110 cf TCATSPhysics.cxx
  CATS_XY_TARGET = new TH2I("CATS_XY_TARGET","CATS_XY_TARGET", 600, -30, 30, 600, -30, 30);
  GetSpectra()->AddSpectrum(CATS_XY_TARGET,(char *)"CATS/CAL/CTRL");
   
	
  //////////////////////////////
  //instantiate MUST2 MONODIMs//
  //////////////////////////////
 
  // MULT_TEL
  MULT_TEL = new TH1I("MULT_TEL","MULT_TEL", 8, 1, 9);
  GetSpectra()->AddSpectrum(MULT_TEL,(char *)"MUST2/BRUT/MULT");
     
  // MM_HITXE
  MM_HITXE = new TH1I("MM_HITXE","MM_HITXE", 8, 1, 9);
  GetSpectra()->AddSpectrum(MM_HITXE,(char *)"MUST2/BRUT/MULT");
      
  // MM_HITYE
  MM_HITYE = new TH1I("MM_HITYE","MM_HITYE", 8, 1, 9);
  GetSpectra()->AddSpectrum(MM_HITYE,(char *)"MUST2/BRUT/MULT");

  // HIT PATTERNS CSI & SILI
  MM1_CSI_HIT = new TH1I("MM1_CSI_HIT","MM1_CSI_HIT", 16, 1, 17);
  GetSpectra()->AddSpectrum(MM1_CSI_HIT,(char *)"MUST2/BRUT/MULT");

  MM2_CSI_HIT = new TH1I("MM2_CSI_HIT","MM2_CSI_HIT", 16, 1, 17);
  GetSpectra()->AddSpectrum(MM2_CSI_HIT,(char *)"MUST2/BRUT/MULT");

  MM3_CSI_HIT = new TH1I("MM3_CSI_HIT","MM3_CSI_HIT", 16, 1, 17);
  GetSpectra()->AddSpectrum(MM3_CSI_HIT,(char *)"MUST2/BRUT/MULT");

  MM4_CSI_HIT = new TH1I("MM4_CSI_HIT","MM4_CSI_HIT", 16, 1, 17);
  GetSpectra()->AddSpectrum(MM4_CSI_HIT,(char *)"MUST2/BRUT/MULT");

  MM5_SILI_HIT = new TH1I("MM5_SILI_HIT","MM5_SILI_HIT", 16, 1, 17);
  GetSpectra()->AddSpectrum(MM5_SILI_HIT,(char *)"MUST2/BRUT/MULT");

  MM6_CSI_HIT = new TH1I("MM6_CSI_HIT","MM6_CSI_HIT", 16, 1, 17);
  GetSpectra()->AddSpectrum(MM6_CSI_HIT,(char *)"MUST2/BRUT/MULT");

  MM7_CSI_HIT = new TH1I("MM7_CSI_HIT","MM7_CSI_HIT", 16, 1, 17);
  GetSpectra()->AddSpectrum(MM7_CSI_HIT,(char *)"MUST2/BRUT/MULT");

  MM8_SILI_HIT = new TH1I("MM8_SILI_HIT","MM8_SILI_HIT", 16, 1, 17);
  GetSpectra()->AddSpectrum(MM8_SILI_HIT,(char *)"MUST2/BRUT/MULT");
    
  for (Int_t i = 0; i < numberMust2; i++) {

    // STRX_MULT
    name = Form("MM%d_STRX_MULT", i+1);
    MM_STRX_MULT[i] = new TH1I(name, name, 128, 1, 129);
    GetSpectra()->AddSpectrum(MM_STRX_MULT[i],(char *)"MUST2/BRUT/MULT");

    // STRY_MULT
    name = Form("MM%d_STRY_MULT", i+1);
    MM_STRY_MULT[i] = new TH1I(name, name, 128, 1, 129);
    GetSpectra()->AddSpectrum(MM_STRY_MULT[i],(char *)"MUST2/BRUT/MULT");

    // no piedestal suppression for Sili & Csi so mult is always 16 unless detector is dead!
    // SILI_MULT
    //name = Form("MM%d_SILI_MULT", i+1);
    //MM_SILI_MULT[i] = new TH1I(name, name, 128, 1, 17);
    //GetSpectra()->AddSpectrum(MM_SILI_MULT[i],(char *)"MUST2/BRUT/MULT");
    // CSI_MULT
    //name = Form("MM%d_CSI_MULT", i+1);
    //MM_CSI_MULT[i] = new TH1I(name, name, 128, 1, 17);
    //GetSpectra()->AddSpectrum(MM_CSI_MULT[i],(char *)"MUST2/BRUT/MULT");     
      
  }

  //////////////////////////////
  // instantiate MUST2 BIDIMs //
  //////////////////////////////
  for (Int_t i = 0; i < numberMust2; i++) {
    // STRX_E_BRU
    name = Form("MM%d_STRX_E_BRU", i+1);
    MM_STRX_E_BRU[i] = new TH2I(name, name, 128, 1, 129, 512, 0, 8192);
    GetSpectra()->AddSpectrum(MM_STRX_E_BRU[i],(char *)"MUST2/BRUT/STRXE");

    // STRY_E_BRU
    name = Form("MM%d_STRY_E_BRU", i+1);
    MM_STRY_E_BRU[i] = new TH2I(name, name, 128, 1, 129, 512, 0, 8192);
    GetSpectra()->AddSpectrum(MM_STRY_E_BRU[i],(char *)"MUST2/BRUT/STRYE");

    // STRX_T_BRU
    name = Form("MM%d_STRX_T_BRU", i+1);
    MM_STRX_T_BRU[i] = new TH2I(name, name, 128, 1, 129, 256, 0, 8192);
    GetSpectra()->AddSpectrum(MM_STRX_T_BRU[i],(char *)"MUST2/BRUT/STRXT");

    // STRY_T_BRU
    name = Form("MM%d_STRY_T_BRU", i+1);
    MM_STRY_T_BRU[i] = new TH2I(name, name, 128, 1, 129, 256, 0, 8192);
    GetSpectra()->AddSpectrum(MM_STRY_T_BRU[i],(char *)"MUST2/BRUT/STRYT");

    // SILI_E_BRU
    name = Form("MM%d_SILI_E_BRU", i+1);
    MM_SILI_E_BRU[i] = new TH2I(name, name, 16, 1, 17, 512, 0, 8192);
    GetSpectra()->AddSpectrum(MM_SILI_E_BRU[i],(char *)"MUST2/BRUT/SILIE");

    // SILI_T_BRU
    name = Form("MM%d_SILI_T_BRU", i+1);
    MM_SILI_T_BRU[i] = new TH2I(name, name, 16, 1, 17, 256, 0, 8192);
    GetSpectra()->AddSpectrum(MM_SILI_T_BRU[i],(char *)"MUST2/BRUT/SILIT");

    // CSI_E_BRU
    name = Form("MM%d_CSI_E_BRU", i+1);
    MM_CSI_E_BRU[i] = new TH2I(name, name, 16, 1, 17, 512, 0, 8192);
    GetSpectra()->AddSpectrum(MM_CSI_E_BRU[i],(char *)"MUST2/BRUT/CSIE");

    // CSI_T_BRU
    name = Form("MM%d_CSI_T_BRU", i+1);
    MM_CSI_T_BRU[i] = new TH2I(name, name, 16, 1, 17, 256, 0, 8192);
    GetSpectra()->AddSpectrum(MM_CSI_T_BRU[i],(char *)"MUST2/BRUT/CSIT");

    // STRXY RAW IMPACT MAPS						    
    name = Form("MM%d_STRXY_IMPACT", i+1);
    MM_STRXY_IMPACT[i] = new TH2I(name,name, 128, 0, 129, 128, 0, 129);
    GetSpectra()->AddSpectrum(MM_STRXY_IMPACT[i],(char *)"MUST2/BRUT/IMPACT");
      
    // STRX_E_CAL
    name = Form("MM%d_STRX_E_CAL", i+1);
    MM_STRX_E_CAL[i] = new TH2I(name, name, 128, 1, 129, 500, 0, 50);
    GetSpectra()->AddSpectrum(MM_STRX_E_CAL[i],(char *)"MUST2/CAL/STRXE");

    // STRY_E_CAL
    name = Form("MM%d_STRY_E_CAL", i+1);
    MM_STRY_E_CAL[i] = new TH2I(name, name, 128, 1, 129, 500, 0, 50);
    GetSpectra()->AddSpectrum(MM_STRY_E_CAL[i],(char *)"MUST2/CAL/STRYE");

    // STRX_T_CAL
    name = Form("MM%d_STRX_T_CAL", i+1);
    MM_STRX_T_CAL[i] = new TH2I(name, name, 128, 1, 129, 500, 0, 500);
    GetSpectra()->AddSpectrum(MM_STRX_T_CAL[i],(char *)"MUST2/CAL/STRXT");

    // STRY_T_CAL
    name = Form("MM%d_STRY_T_CAL", i+1);
    MM_STRY_T_CAL[i] = new TH2I(name, name, 128, 1, 129, 500, 0, 500);
    GetSpectra()->AddSpectrum(MM_STRY_T_CAL[i],(char *)"MUST2/CAL/STRYT");

    // SILI_E_CAL
    name = Form("MM%d_SILI_E_CAL", i+1);
    MM_SILI_E_CAL[i] = new TH2I(name, name, 16, 1, 17, 500, 0, 50);
    GetSpectra()->AddSpectrum(MM_SILI_E_CAL[i],(char *)"MUST2/CAL/SILIE");

    // SILI_T_CAL
    name = Form("MM%d_SILI_T_CAL", i+1);
    MM_SILI_T_CAL[i] = new TH2I(name, name, 16, 1, 17, 500, 0, 50);
    GetSpectra()->AddSpectrum(MM_SILI_T_CAL[i],(char *)"MUST2/CAL/SILIT");

    // CSI_E_CAL
    name = Form("MM%d_CSI_E_CAL", i+1);
    MM_CSI_E_CAL[i] = new TH2I(name, name, 16, 1, 17, 500, 0, 50);
    GetSpectra()->AddSpectrum(MM_CSI_E_CAL[i],(char *)"MUST2/CAL/CSIE");

    // CSI_T_CAL
    name = Form("MM%d_CSI_T_CAL", i+1);
    MM_CSI_T_CAL[i] = new TH2I(name, name, 16, 1, 17, 500, 0, 50);
    GetSpectra()->AddSpectrum(MM_CSI_T_CAL[i],(char *)"MUST2/CAL/CSIT");

    // STRXY CALIBRATED ENERGY CORRELATION
    name = Form("MM%d_STRXY_E_CAL", i+1);
    MM_STRXY_E_CAL[i] = new TH2I(name,name, 500, 0, 50, 500, 0, 50);
    GetSpectra()->AddSpectrum(MM_STRXY_E_CAL[i],(char *)"MUST2/CAL/CORRELATION");

  }

  // STRX-CSI/SILI DE-E

  MM1_STRX_CSI = new TH2I("MM1_STRX_CSI","MM1_STRX_CSI",500,0,50,500,0,50);
  GetSpectra()->AddSpectrum(MM1_STRX_CSI,(char *)"MUST2/CAL/DEE");
  MM2_STRX_CSI = new TH2I("MM2_STRX_CSI","MM2_STRX_CSI",500,0,50,500,0,50);
  GetSpectra()->AddSpectrum(MM2_STRX_CSI,(char *)"MUST2/CAL/DEE");
  MM3_STRX_CSI = new TH2I("MM3_STRX_CSI","MM3_STRX_CSI",500,0,50,500,0,50);
  GetSpectra()->AddSpectrum(MM3_STRX_CSI,(char *)"MUST2/CAL/DEE");
  MM4_STRX_CSI = new TH2I("MM4_STRX_CSI","MM4_STRX_CSI",500,0,50,500,0,50);
  GetSpectra()->AddSpectrum(MM4_STRX_CSI,(char *)"MUST2/CAL/DEE");
  MM5_STRX_SILI = new TH2I("MM5_STRX_SILI","MM5_STRX_SILI",500,0,50,500,0,50);
  GetSpectra()->AddSpectrum(MM5_STRX_SILI,(char *)"MUST2/CAL/DEE");
  MM6_STRX_CSI = new TH2I("MM6_STRX_CSI","MM6_STRX_CSI",500,0,50,500,0,50);
  GetSpectra()->AddSpectrum(MM6_STRX_CSI,(char *)"MUST2/CAL/DEE");
  MM7_STRX_CSI = new TH2I("MM7_STRX_CSI","MM7_STRX_CSI",500,0,50,500,0,50);
  GetSpectra()->AddSpectrum(MM7_STRX_CSI,(char *)"MUST2/CAL/DEE");
  MM8_STRX_SILI = new TH2I("MM8_STRX_SILI","MM8_STRX_SILI",500,0,50,500,0,50);
  GetSpectra()->AddSpectrum(MM8_STRX_SILI,(char *)"MUST2/CAL/DEE");
   
  //////////////////////////////
  // instantiate SSSD         //
  //////////////////////////////
  for (Int_t i = 0; i < numberSSSD; i++) {

    // STR_E_BRU
    name = Form("SSSD%d_STR_E_BRU", i+1);
    SSSD_E_BRU[i] = new TH2I(name, name, 16, 1, 17, 512, 0, 16384);
    GetSpectra()->AddSpectrum(SSSD_E_BRU[i],(char *)"SSSD/BRUT");

    // STR_E_CAL
    name = Form("SSSD%d_STR_E_CAL", i+1);
    SSSD_E_CAL[i] = new TH2I(name, name, 16, 1, 17, 500, 0, 10);
    GetSpectra()->AddSpectrum(SSSD_E_CAL[i],(char *)"SSSD/CAL");

    // SSSD-STRX DE-E 
    name = Form("MM%d_SSSD_DEE", i+1);
    MM_SSSD_STRX[i] = new TH2I(name,name,500,0,50,500,0,10);
    GetSpectra()->AddSpectrum(MM_SSSD_STRX[i],(char *)"SSSD/DEE");

    // Angle vs Etotal
    name = Form("MM%d_SSSD_Angle_Etotal", i+1);
    ANGLE_ETOTAL[i] = new TH2I(name,name,180,0,180,1000,0,10);
    GetSpectra()->AddSpectrum(ANGLE_ETOTAL[i],(char *)"SSSD/DEE");    
    
  }
    
  //////////////////////////////
  // Chio & plastic spectra   //
  //////////////////////////////

  CHIO_AN = new TH1I("Chio_analog", "Chio_analog", 512, 0, 16384);
  GetSpectra()->AddSpectrum(CHIO_AN,(char *)"CHIO/ANALOG");
  CHIO_AN_PILEUP = new TH1I("Chio_analog_pileup", "Chio_analog_pileup", 512, 0, 16384);
  GetSpectra()->AddSpectrum(CHIO_AN_PILEUP,(char *)"CHIO/ANALOG");
  TOF_PLGAL_CHIO_AN = new TH2I("TOF_PlGal_Chio_an","TOF_PlGal_Chio_an",1024,0,16384,512,0,16384);
  GetSpectra()->AddSpectrum(TOF_PLGAL_CHIO_AN,(char *)"CHIO/ANALOG");
  //TOF_PLGAL_CHIO_AN_CondD6 = new TH2I("TOF_PlGal_Chio_an_CondD6","TOF_PlGal_Chio_an_CondD6",512,0,16384,512,0,16384);
  //GetSpectra()->AddSpectrum(TOF_PLGAL_CHIO_AN_CondD6,(char *)"CHIO/ANALOG");
  TOF_PLCATS2_CHIO_AN = new TH2I("TOF_PlCats2_Chio_an","TOF_PlCats2_Chio_an",1024,0,16384,512,0,16384);
  GetSpectra()->AddSpectrum(TOF_PLCATS2_CHIO_AN,(char *)"CHIO/ANALOG");
  DE_E_PL_CHIO_AN= new TH2I("DE_E_Pl_Chio_an","DE_E_Pl_Chio_an",512,0,16384,512,0,16384);
  GetSpectra()->AddSpectrum(DE_E_PL_CHIO_AN,(char *)"CHIO/ANALOG");
   
  CHIO_DIG = new TH2I("Chio_digital","Chio_digital",350,0,350,512,0,4096);
  GetSpectra()->AddSpectrum(CHIO_DIG,(char *)"CHIO/DIGITAL");
  TOF_PLGAL_CHIO_DIG = new TH2I("TOF_PlGal_Chio_dig","TOF_PlGal_Chio_dig",1024,0,16384,512,0,4096);
  GetSpectra()->AddSpectrum(TOF_PLGAL_CHIO_DIG,(char *)"CHIO/DIGITAL");
  TOF_PLCATS2_CHIO_DIG = new TH2I("TOF_PlCats2_Chio_dig","TOF_PlCats2_Chio_dig",1024,0,16384,512,0,4096);
  GetSpectra()->AddSpectrum(TOF_PLCATS2_CHIO_DIG,(char *)"CHIO/DIGITAL");
  DE_E_PL_CHIO_DIG= new TH2I("DE_E_Pl_Chio_dig","DE_E_Pl_Chio_dig",512,0,16384,512,0,16384);
  GetSpectra()->AddSpectrum(DE_E_PL_CHIO_DIG,(char *)"CHIO/DIGITAL");
  

  //////////////////////////////
  // TAC spectra             //
  //////////////////////////////

  hTAC_MM_CATS1 = new TH1I("TAC_MM_CATS1", "TAC_MM_CATS1", 8192, 0,16384 );
  GetSpectra()->AddSpectrum(hTAC_MM_CATS1,(char *)"TAC/BRUT");
  hTAC_MM_CATS2 = new TH1I("TAC_MM_CATS2", "TAC_MM_CATS2", 8192, 0, 16384);
  GetSpectra()->AddSpectrum(hTAC_MM_CATS2,(char *)"TAC/BRUT");
  hTAC_PL_CATS1 = new TH1I("TAC_PL_CATS1", "TAC_PL_CATS1", 8192, 0, 16384);
  GetSpectra()->AddSpectrum(hTAC_PL_CATS1,(char *)"TAC/BRUT");
  hTAC_PL_CATS2 = new TH1I("TAC_PL_CATS2", "TAC_PL_CATS2", 8192, 0, 16384);
  GetSpectra()->AddSpectrum(hTAC_PL_CATS2,(char *)"TAC/BRUT");
  hTAC_CATS12 = new TH1I("TAC_CATS12", "TAC_CATS12", 8192, 0, 16384);
  GetSpectra()->AddSpectrum(hTAC_CATS12,(char *)"TAC/BRUT");
  hTAC_PL_GAL = new TH1I("TAC_PL_GAL", "TAC_PL_GAL", 8192, 0, 16384);
  GetSpectra()->AddSpectrum(hTAC_PL_GAL,(char *)"TAC/BRUT");
  hTAC_CATS1_HF = new TH1I("TAC_CATS1_HF", "TAC_CATS1_HF", 8192, 0, 16384);
  GetSpectra()->AddSpectrum(hTAC_CATS1_HF,(char *)"TAC/BRUT");
  hTAC_CATS2_HF = new TH1I("TAC_CATS2_HF", "TAC_CATS2_HF", 8192, 0, 16384);
  GetSpectra()->AddSpectrum(hTAC_CATS2_HF,(char *)"TAC/BRUT");
  hTAC_MM_HF = new TH1I("TAC_MM_HF", "TAC_MM_HF", 8192, 0, 16384);
  GetSpectra()->AddSpectrum(hTAC_MM_HF,(char *)"TAC/BRUT");

  //////////////////////////////
  // LISE spectra             //
  //////////////////////////////
	hDED6_TOF = new TH2I("DED6_TOF","DED6_TOF",512, 0, 16384, 512, 0, 16384);
	hXY_SID6			= new TH2F("XY_SID6","XY_SID6",  512, 0, 16384, 512, 0, 16384);
	GetSpectra()->AddSpectrum(hDED6_TOF,(char *)"LISE");
	GetSpectra()->AddSpectrum(hXY_SID6,(char *)"LISE");

  cout << "End Loading Spectra " << endl;

  //////////////////////////////
  // contours                 //
  //////////////////////////////
 
  cout << "Start Loading TCutG"<< endl;
  pipo_cutg_iolanda = new TCutG("pipo_cutg_iolanda", 0);
  GetSpectra()->AddCut(pipo_cutg_iolanda,(char *)"MUST2");


	for(Int_t i = 0; i < numberCutLise; i++)
	{
		name = Form("CutIdentLise%d", i+1);
		CutIdentLise[i] = new TCutG(name,0);
		GetSpectra()->AddCut(CutIdentLise[i],(char *)"LISE");
	}
	
	   
  cout << "End Loading TCutG"<< endl;

	
}



void GUser::InitUserRun()
{ 
  // Initialisation for user treatment for each run  
  // For specific user treatment

  cout << "Init run" << endl;

  fMust2->Init(GetEvent()->GetDataParameters());
  cout << "End Init Must2"<<endl;

  fCATS->Init(GetEvent()->GetDataParameters());
  cout << "End Init CATS"<<endl;

  fSSSD->Init(GetEvent()->GetDataParameters());
  cout << "End Init SSSD"<<endl;

  fChio_an->Init( GetEvent()->GetDataParameters() );
  cout << "End Init Analog Chio"<<endl;

  fChio_dig->Init( GetEvent()->GetDataParameters() );
  cout << "End Init Digital Chio"<<endl;
	
  fPlastic->Init( GetEvent()->GetDataParameters() );
  cout << "End Init Plastic"<<endl;
       
  fTrigger->Init(GetEvent()->GetDataParameters());
  cout << "End Init Trigger"<<endl;

  fTac->Init( GetEvent()->GetDataParameters() );
  cout << "End Init Tac"<<endl;

  fLise->Init( GetEvent()->GetDataParameters() );
  cout << "End Init LISE"<<endl;

  cout << "End init run"<<endl;


  // keep track of read labels
  ofstream out_rej,out_acc;
  out_acc.open("label_accepted.dat");
  out_rej.open("label_rejected.dat");

  for (Int_t i = 0; i < GetEventArraySize(); i++) {
    bool included = false;

    if (fMust2->GetLabelMap(GetDataParameters()->GetLabel(i)) == GetDataParameters()->GetParName(i)){
      included = true;
    }
    else if (fCATS->GetLabelMap(GetDataParameters()->GetLabel(i)) == GetDataParameters()->GetParName(i)) {
      included = true;
    }
    else if (fSSSD->GetLabelMap(GetDataParameters()->GetLabel(i)) == GetDataParameters()->GetParName(i)) {
      included = true;
    }
    else if(fChio_an->GetLabelMap(GetDataParameters()->GetLabel(i)) == GetDataParameters()->GetParName(i)) {
      included = true;
    }
    else if(fChio_dig->GetLabelMap(GetDataParameters()->GetLabel(i)) == GetDataParameters()->GetParName(i)) {
      included = true;
    }	
    else if(fPlastic->GetLabelMap(GetDataParameters()->GetLabel(i)) == GetDataParameters()->GetParName(i)) {
      included = true;
    }
    else if(fTac->GetLabelMap(GetDataParameters()->GetLabel(i)) == GetDataParameters()->GetParName(i)) {
      included = true;
    }
    else if(fTrigger->GetLabelMap(GetDataParameters()->GetLabel(i)) == GetDataParameters()->GetParName(i)) {
      included = true;
    }
    else if(fLise->GetLabelMap(GetDataParameters()->GetLabel(i)) == GetDataParameters()->GetParName(i)) {
      included = true;
    }

    if (!included) {
      out_rej << i <<" "<<GetDataParameters()->GetParName(i)<<endl;
    }
    else {
      out_acc << i <<" "<<GetDataParameters()->GetParName(i)<<endl;
    }
  }
  out_rej.close();
  out_acc.close();


}



void GUser::User()
{
  // the event is presented on two way ( user  can use one or other )
  // 1  - event is a vector of UShor_t* GetEventArray() of fixed size  (GetEventArraySize())
  //      '0's have been included in vector where parameter were not present
  //      GetEventArray_Value(i) return value index i in vector GetEventArray()
  // 2  - event is a vector of a serie of couples  UShor_t/Short_t Label/Value ( GetEventArrayLabelValue()) 
  //      of variable size   GetEventArrayLabelValueSize() and  with a max size of GetEventArrayLabelValueSizeMax()
  //      This vector is often called control event.
  //      The numebers of couple  Label/Value is GetEventArrayLabelValueSize()/2
  //      GetEventArrayLabelValue_Label(i)  return  Label number i in  vector GetEventArrayLabelValue()
  //      GetEventArrayLabelValue_Value(i)  return  Value number  i in  vector GetEventArrayLabelValue()
  //     
  //      Exemple of use of manage index,label,name
  //      GetEvent()->GetDataParameters()->GetLabel("NAME")  return label of parameter with name "NAME"
  //      GetEvent()->GetDataParameters()->GetLabel(index)   return label of parameter with index i (in GetEventArray() vector)
  //      GetEvent()->GetDataParameters()->GetParName(label) return name of parameter with label 'label'
  //      GetEvent()->GetDataParameters()->GetIndex(label)   return index(in GetEventArray() vector) of parameter with label 'label
  //      GetEvent()->GetDataParameters()->GetIndex("NAME")  return index(in GetEventArray() vector) of parameter with name "NAME"

  //The number of sub event is  given byGetEvent()->GetNbofSubEvt()*
  // and timestamps are reacheable with a vector of time stamps given by  GetEvent()->GetTimeStamps();

  	
  // define boolean variables
  bool bCATS   = false;
  bool bMust2    = false;
  bool bSSSD    = false;
  bool bChio_an  = false;
  bool bChio_dig = false;
  bool bPlastic  = false;
  bool bLise     = false;  
  bool bTac      = false;
  bool bTrigger = false;
  bool bTrigLise = false;
  // clear objects
  fCATS     -> Clear();
  fMust2    -> Clear();
  fSSSD     -> Clear();
  fChio_an  -> Clear(); 
  fChio_dig -> Clear();
  fPlastic  -> Clear();
  fLise     -> Clear();
  fTac      -> Clear();
  fTrigger  -> Clear();
   
  ///////////////////////////
  //     Unpack events     //
  ///////////////////////////
  int size =  GetEventArrayLabelValueSize()/2;
  for (Int_t i = 0; i < size; i++) {  
    if (fCATS->Is(GetEventArrayLabelValue_Label(i),GetEventArrayLabelValue_Value(i))) {
      bCATS = true;  // indicate that physical treatment should be performed
    }
    else if (fMust2->Is(GetEventArrayLabelValue_Label(i),GetEventArrayLabelValue_Value(i))) {
       bMust2 = true;  // indicate that physical treatment should be performed
     }   
    else if (fSSSD->Is(GetEventArrayLabelValue_Label(i),GetEventArrayLabelValue_Value(i))) {
      bSSSD = true;  // indicate that physical treatment should be performed
    }
    else if (fChio_an->Is(GetEventArrayLabelValue_Label(i),GetEventArrayLabelValue_Value(i))) {
      bChio_an = true;
    }  
    else if (fChio_dig->Is(GetEventArrayLabelValue_Label(i),GetEventArrayLabelValue_Value(i))) {
      bChio_dig = true;
    }  
    else if (fPlastic->Is(GetEventArrayLabelValue_Label(i),GetEventArrayLabelValue_Value(i))) {
       bPlastic = true;
    }
    else if (fTac->Is(GetEventArrayLabelValue_Label(i),GetEventArrayLabelValue_Value(i))) {
      bTac = true;
    }
    else if (fTrigger->Is(GetEventArrayLabelValue_Label(i),GetEventArrayLabelValue_Value(i))) {
      bTrigger = true;
    }
    else if (fLise->Is(GetEventArrayLabelValue_Label(i),GetEventArrayLabelValue_Value(i))) {
      bLise = true;
    }
    else {
      // cout << "not a good label: "<<GetEventArrayLabelValue_Label(i);
      // cout << " value: "<<GetEventArrayLabelValue_Value(i)<<endl;
    }
  }
	
	if(bTrigger)
	{
		ushort pow2 = 0;
		for( Int_t i = 0; i < 16; i++)
		{
			pow2 = (ushort)TMath::Power(2,i);
			if ((fTrigger->GetTriggerData()->GetTRIG1() & pow2) == pow2)
			{
				hTRIGGER -> Fill(i+1);
				if (i + 1 == 16) {bTrigLise = true;}
			}
		}
	}

  ///////////////////////////
  //   Treat CATS events   //
  ///////////////////////////
  if (bCATS) {
    Int_t CATS_x_mult[numberCats], CATS_y_mult[numberCats];
    for (Int_t i = 0; i < numberCats; i++) {
      CATS_x_mult[i] = 0;
      CATS_y_mult[i] = 0;
    }
		
    // STRX_Q
    for (Int_t i = 0; i < fCATS->GetCATSData()->GetCATSMultX(); i++) {
      // X multiplicity
      CATS_x_mult[fCATS->GetCATSData()->GetCATSDetX(i) - 1] += 1;
      // fill spectra
      CATS_STRX_Q_BRU[fCATS->GetCATSData()->GetCATSDetX(i) - 1] -> Fill(fCATS->GetCATSData()->GetCATSStripX(i), fCATS->GetCATSData()->GetCATSChargeX(i));
    }

    // STRY_Q
    for (Int_t i = 0; i < fCATS->GetCATSData()->GetCATSMultY(); i++) {
      // Y multiplicity 
      CATS_y_mult[fCATS->GetCATSData()->GetCATSDetY(i) - 1] += 1;
      // fill spectra
      CATS_STRY_Q_BRU[fCATS->GetCATSData()->GetCATSDetY(i) - 1] -> Fill(fCATS->GetCATSData()->GetCATSStripY(i), fCATS->GetCATSData()->GetCATSChargeY(i));
    }
 
    // CATS mult X and mult Y
    for (Int_t i = 0; i < numberCats; i++) {
      CATS_STRX_MULT[i] -> Fill(CATS_x_mult[i]);
      CATS_STRY_MULT[i] -> Fill(CATS_y_mult[i]);		
    }
				
    // make analysis
    fCATS->Treat();		
    //cout << fCATS->GetCATSPhysics()->GetCATSMultOverThreshX(1)<< " "; 
    //cout << fCATS->GetCATSPhysics()->GetCATSMultOverThreshX(2)<<endl;
    //so the index of these methods should be 1 and 2 ie i+1 !!!!!!

      
    // STRX_Q_CAL	
    for (Int_t i = 0; i < fCATS->GetCATSPhysics()->GetCATSMultX(); i++) {
      CATS_STRX_Q_CAL[fCATS->GetCATSPhysics()->GetCATSDetNumberX(i)-1] -> Fill(fCATS->GetCATSPhysics()->GetCATSStripX(i), fCATS->GetCATSPhysics()->GetCATSChargeX(i));
    }
      
    // STRY_Q_CAL
    for (Int_t i = 0; i < fCATS->GetCATSPhysics()->GetCATSMultY(); i++) {
      CATS_STRY_Q_CAL[fCATS->GetCATSPhysics()->GetCATSDetNumberY(i)-1] -> Fill(fCATS->GetCATSPhysics()->GetCATSStripY(i), fCATS->GetCATSPhysics()->GetCATSChargeY(i));
    }
      
    // fill these spectra iff there are 2 X and 2 Y values
    if( fCATS->GetCATSPhysics()->DetNumberX_Position.size() == 2 && fCATS->GetCATSPhysics()->DetNumberY_Position.size()==2){

       for (Int_t i = 0; i < fCATS->GetCATSPhysics()->DetNumberX_Position.size(); i++) {

	 if (  fCATS->GetCATSPhysics()->DetNumberX_Position.at(i) ==  fCATS->GetCATSPhysics()->DetNumberY_Position.at(i)){
	 // STRX_MAX & STRY_MAX 
    	 CATS_STRX_MAX[fCATS->GetCATSPhysics()->DetNumberX_Position.at(i)-1] -> Fill(fCATS->GetCATSPhysics()->GetCATSStripMaxX(i+1));
    	 CATS_STRY_MAX[fCATS->GetCATSPhysics()->DetNumberY_Position.at(i)-1] -> Fill(fCATS->GetCATSPhysics()->GetCATSStripMaxY(i+1));
	 // CHARGE_XY & XY_MAX
	 CATS_CHARGE_XY[fCATS->GetCATSPhysics()->DetNumberX_Position.at(i)-1] -> Fill(fCATS->GetCATSPhysics()->GetCATSChargeSumX(i+1), fCATS->GetCATSPhysics()->GetCATSChargeSumY(i+1));
	 CATS_XY_MAX[fCATS->GetCATSPhysics()->DetNumberX_Position.at(i)-1] -> Fill(fCATS->GetCATSPhysics()->GetCATSStripMaxX(i+1), fCATS->GetCATSPhysics()->GetCATSStripMaxY(i+1));
	 CATS_XY_POS[fCATS->GetCATSPhysics()->DetNumberX_Position.at(i)-1] -> Fill(fCATS->GetCATSPhysics()->PositionX.at(i), fCATS->GetCATSPhysics()->PositionY.at(i));
	
         }
	 else {
	   cout << "Warning: X vs Y mismatch for Cats " << endl;
	 }
       }
       
       //XY_TARGET
       CATS_XY_TARGET -> Fill(fCATS->GetCATSPhysics()->PositionOnTargetX, fCATS->GetCATSPhysics()->PositionOnTargetY);
    }
			
  }
	
  ///////////////////////////
  //   Treat MUST2 events  //
  ///////////////////////////
  if (bMust2) {

    Int_t MM_XE_mult[numberMust2], MM_YE_mult[numberMust2];
    for (Int_t i = 0; i < numberMust2; i++) {
      MM_XE_mult[i] = 0;
      MM_YE_mult[i] = 0;
    }

    // raw spectra: uncalibrated & hit patterns	
    // MULT_TEL simplified procedure of TMust2Physics::Match_X_Y()
    int telescope_is_hit =0 ;          
    for(int i = 0 ; i < fMust2->GetMust2Data()->GetMMStripXEMult(); ++i)
      {
    	for(int j = 0 ; j < fMust2->GetMust2Data()->GetMMStripYEMult(); j++)
    	  {
    	    //  counter +1 if X and Y in same detector
    	    if ( fMust2->GetMust2Data()->GetMMStripXEDetectorNbr(i) == fMust2->GetMust2Data()->GetMMStripYEDetectorNbr(j) )
    	      {
    		telescope_is_hit += 1;
    		// no check on energy matching since not yet calibrated here
    	      }
    	  }
      }
    MULT_TEL -> Fill(telescope_is_hit);
      
    // STRX_E & MM_HITXE & STRXY IMPACT MAP
    if ( fMust2->GetMust2Data()->GetMMStripXEMult() ==  fMust2->GetMust2Data()->GetMMStripYEMult()){
      for (Int_t i = 0; i < fMust2->GetMust2Data()->GetMMStripXEMult(); i++)
      {
    	//if (pipo_cutg_iolanda->IsInside(fMust2->GetMust2Data()->GetMMStripXEStripNbr(i), fMust2->GetMust2Data()->GetMMStripXEEnergy(i) - 8192)) {
    	MM_STRX_E_BRU[fMust2->GetMust2Data()->GetMMStripXEDetectorNbr(i) - 1] -> Fill(fMust2->GetMust2Data()->GetMMStripXEStripNbr(i), fMust2->GetMust2Data()->GetMMStripXEEnergy(i) - 8192);

    	MM_HITXE -> Fill(fMust2->GetMust2Data()->GetMMStripXEDetectorNbr(i));
    	MM_XE_mult[fMust2->GetMust2Data()->GetMMStripXEDetectorNbr(i) - 1] += 1;

    	if (fMust2->GetMust2Data()->GetMMStripXEDetectorNbr(i) == 1) {
          MM_STRXY_IMPACT[fMust2->GetMust2Data()->GetMMStripXEDetectorNbr(i) - 1] -> Fill(129-fMust2->GetMust2Data()->GetMMStripXEStripNbr(i), 129-fMust2->GetMust2Data()->GetMMStripYEStripNbr(i));
        }
        else if (fMust2->GetMust2Data()->GetMMStripXEDetectorNbr(i) == 2) {
          MM_STRXY_IMPACT[fMust2->GetMust2Data()->GetMMStripXEDetectorNbr(i) - 1] -> Fill(129-fMust2->GetMust2Data()->GetMMStripYEStripNbr(i), fMust2->GetMust2Data()->GetMMStripXEStripNbr(i));
        }
        else if (fMust2->GetMust2Data()->GetMMStripXEDetectorNbr(i) == 3) {
          MM_STRXY_IMPACT[fMust2->GetMust2Data()->GetMMStripXEDetectorNbr(i) - 1] -> Fill(fMust2->GetMust2Data()->GetMMStripXEStripNbr(i), fMust2->GetMust2Data()->GetMMStripYEStripNbr(i));
        }
        else if (fMust2->GetMust2Data()->GetMMStripXEDetectorNbr(i) == 4) {
          MM_STRXY_IMPACT[fMust2->GetMust2Data()->GetMMStripXEDetectorNbr(i) - 1] -> Fill(fMust2->GetMust2Data()->GetMMStripYEStripNbr(i), 129-fMust2->GetMust2Data()->GetMMStripXEStripNbr(i));
        }
        else if (fMust2->GetMust2Data()->GetMMStripXEDetectorNbr(i) == 5) {
          MM_STRXY_IMPACT[fMust2->GetMust2Data()->GetMMStripXEDetectorNbr(i) - 1] -> Fill(129-fMust2->GetMust2Data()->GetMMStripYEStripNbr(i), fMust2->GetMust2Data()->GetMMStripXEStripNbr(i));
        }
        else if (fMust2->GetMust2Data()->GetMMStripXEDetectorNbr(i) == 6) {
          MM_STRXY_IMPACT[fMust2->GetMust2Data()->GetMMStripXEDetectorNbr(i) - 1] -> Fill(129-fMust2->GetMust2Data()->GetMMStripXEStripNbr(i), 129-fMust2->GetMust2Data()->GetMMStripYEStripNbr(i));
        }
        else if (fMust2->GetMust2Data()->GetMMStripXEDetectorNbr(i) == 7) {
          MM_STRXY_IMPACT[fMust2->GetMust2Data()->GetMMStripXEDetectorNbr(i) - 1] -> Fill(fMust2->GetMust2Data()->GetMMStripYEStripNbr(i), 129-fMust2->GetMust2Data()->GetMMStripXEStripNbr(i));
        }
        else if (fMust2->GetMust2Data()->GetMMStripXEDetectorNbr(i) == 8) {
          MM_STRXY_IMPACT[fMust2->GetMust2Data()->GetMMStripXEDetectorNbr(i) - 1] -> Fill(fMust2->GetMust2Data()->GetMMStripXEStripNbr(i), fMust2->GetMust2Data()->GetMMStripYEStripNbr(i));
        }
	
    // 	//}
      }
    }
      
    // STRY_E & MM_HITYE
    for (Int_t i = 0; i < fMust2->GetMust2Data()->GetMMStripYEMult(); i++)
      {
    	MM_STRY_E_BRU[fMust2->GetMust2Data()->GetMMStripYEDetectorNbr(i) - 1] -> Fill(fMust2->GetMust2Data()->GetMMStripYEStripNbr(i), 8192 - fMust2->GetMust2Data()->GetMMStripYEEnergy(i));
    	MM_HITYE -> Fill(fMust2->GetMust2Data()->GetMMStripYEDetectorNbr(i));	 
    	MM_YE_mult[fMust2->GetMust2Data()->GetMMStripYEDetectorNbr(i) - 1] += 1;

      }

    for (Int_t i = 0; i < numberMust2; i++)
      {
    	MM_STRX_MULT[i] -> Fill(MM_XE_mult[i]);
    	MM_STRY_MULT[i] -> Fill(MM_YE_mult[i]);		
      }
		       
    // STRX_T
    for (Int_t i = 0; i < fMust2->GetMust2Data()->GetMMStripXTMult(); i++) {
      MM_STRX_T_BRU[fMust2->GetMust2Data()->GetMMStripXTDetectorNbr(i) - 1] -> Fill(fMust2->GetMust2Data()->GetMMStripXTStripNbr(i), 8192 - fMust2->GetMust2Data()->GetMMStripXTTime(i));
    }
    // STRY_T
    for (Int_t i = 0; i < fMust2->GetMust2Data()->GetMMStripYTMult(); i++) {
      MM_STRY_T_BRU[fMust2->GetMust2Data()->GetMMStripYTDetectorNbr(i) - 1] -> Fill(fMust2->GetMust2Data()->GetMMStripYTStripNbr(i), 8192 - fMust2->GetMust2Data()->GetMMStripYTTime(i));
    }
      
    // SILI_E
    for (Int_t i = 0; i < fMust2->GetMust2Data()->GetMMSiLiEMult(); i++) {
      MM_SILI_E_BRU[fMust2->GetMust2Data()->GetMMSiLiEDetectorNbr(i) - 1] -> Fill(fMust2->GetMust2Data()->GetMMSiLiEPadNbr(i), fMust2->GetMust2Data()->GetMMSiLiEEnergy(i));

      if (fMust2->GetMust2Data()->GetMMSiLiEDetectorNbr(i) == 5) {
    	MM5_SILI_HIT->Fill(fMust2->GetMust2Data()->GetMMSiLiEPadNbr(i));
      }
      else if (fMust2->GetMust2Data()->GetMMSiLiEDetectorNbr(i) == 8) {
    	MM8_SILI_HIT->Fill(fMust2->GetMust2Data()->GetMMSiLiEPadNbr(i));
      }	 
    }
      
    // SILI_T
    for (Int_t i = 0; i < fMust2->GetMust2Data()->GetMMSiLiTMult(); i++) {
      MM_SILI_T_BRU[fMust2->GetMust2Data()->GetMMSiLiTDetectorNbr(i) - 1] -> Fill(fMust2->GetMust2Data()->GetMMSiLiTPadNbr(i), fMust2->GetMust2Data()->GetMMSiLiTTime(i));
    }
	  
    // CSI_E
    for (Int_t i = 0; i < fMust2->GetMust2Data()->GetMMCsIEMult(); i++) {
      MM_CSI_E_BRU[fMust2->GetMust2Data()->GetMMCsIEDetectorNbr(i) - 1] -> Fill(fMust2->GetMust2Data()->GetMMCsIECristalNbr(i), fMust2->GetMust2Data()->GetMMCsIEEnergy(i));
      
      if (fMust2->GetMust2Data()->GetMMCsIEDetectorNbr(i) == 1) {
    	MM1_CSI_HIT->Fill(fMust2->GetMust2Data()->GetMMCsIECristalNbr(i));
      }
      else if (fMust2->GetMust2Data()->GetMMCsIEDetectorNbr(i) == 2) {
    	MM2_CSI_HIT->Fill(fMust2->GetMust2Data()->GetMMCsIECristalNbr(i));
      }
      else if (fMust2->GetMust2Data()->GetMMCsIEDetectorNbr(i) == 3) {
    	MM3_CSI_HIT->Fill(fMust2->GetMust2Data()->GetMMCsIECristalNbr(i));
      }
      else if (fMust2->GetMust2Data()->GetMMCsIEDetectorNbr(i) == 4) {
    	MM4_CSI_HIT->Fill(fMust2->GetMust2Data()->GetMMCsIECristalNbr(i));
      }
      else if (fMust2->GetMust2Data()->GetMMCsIEDetectorNbr(i) == 6) {
    	MM6_CSI_HIT->Fill(fMust2->GetMust2Data()->GetMMCsIECristalNbr(i));
      }
      else if (fMust2->GetMust2Data()->GetMMCsIEDetectorNbr(i) == 7) {
    	MM7_CSI_HIT->Fill(fMust2->GetMust2Data()->GetMMCsIECristalNbr(i));
      }
	   
    }
      
    // CSI_T
    for (Int_t i = 0; i < fMust2->GetMust2Data()->GetMMCsITMult(); i++) {
      MM_CSI_T_BRU[fMust2->GetMust2Data()->GetMMCsITDetectorNbr(i) - 1] -> Fill(fMust2->GetMust2Data()->GetMMCsITCristalNbr(i), fMust2->GetMust2Data()->GetMMCsITTime(i));
    }

    // make analysis 
    fMust2->Treat();

    // fill calibrated user spectra
    // STRX_E & Energy correlation
    if ( fMust2->GetMust2Data()->GetMMStripXEMult() ==  fMust2->GetMust2Data()->GetMMStripYEMult()){
      for (Int_t i = 0; i < fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMStripXEMult(); i++) {
        MM_STRX_E_CAL[fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMStripXEDetectorNbr(i) - 1] -> Fill(fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMStripXEStripNbr(i), fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMStripXEEnergy(i));
        MM_STRXY_E_CAL[fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMStripXEDetectorNbr(i) - 1] -> Fill(fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMStripXEEnergy(i),fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMStripYEEnergy(i));	 
      }
    }   
    // STRY_E
    for (Int_t i = 0; i < fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMStripYEMult(); i++) {
      MM_STRY_E_CAL[fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMStripYEDetectorNbr(i) - 1] -> Fill(fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMStripYEStripNbr(i), fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMStripYEEnergy(i));
    }
    // STRX_T
    for (Int_t i = 0; i < fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMStripXTMult(); i++) {
      MM_STRX_T_CAL[fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMStripXTDetectorNbr(i) - 1] -> Fill(fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMStripXTStripNbr(i), fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMStripXTTime(i));
    }
    // STRY_T
    for (Int_t i = 0; i < fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMStripYTMult(); i++) {
      MM_STRY_T_CAL[fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMStripYTDetectorNbr(i) - 1] -> Fill(fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMStripYTStripNbr(i), fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMStripYTTime(i));
    }
    // SILI_E
    for (Int_t i = 0; i < fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMSiLiEMult(); i++) {
      MM_SILI_E_CAL[fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMSiLiEDetectorNbr(i) - 1] -> Fill(fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMSiLiEPadNbr(i), fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMSiLiEEnergy(i));
    }
    // SILI_T
    for (Int_t i = 0; i < fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMSiLiTMult(); i++) {
      MM_SILI_T_CAL[fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMSiLiTDetectorNbr(i) - 1] -> Fill(fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMSiLiTPadNbr(i), fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMSiLiTTime(i));
    }
    // CSI_E
    for (Int_t i = 0; i < fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMCsIEMult(); i++) {
      MM_CSI_E_CAL[fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMCsIEDetectorNbr(i) - 1] -> Fill(fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMCsIECristalNbr(i), fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMCsIEEnergy(i));
    }
    // CSI_T
    for (Int_t i = 0; i < fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMCsITMult(); i++) {
      MM_CSI_T_CAL[fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMCsITDetectorNbr(i) - 1] -> Fill(fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMCsITCristalNbr(i), fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMCsITTime(i));
    }

    // DE-E between strips & SiLi for telescopes 6-7
    // we look only at events with multiplicity =1
    if ( (fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMStripXEMult()==1) && (fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMSiLiEMult() >0)) {
      if ( fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMStripXEDetectorNbr(0) == 5)  {
	//LN: Find the pad carrying out the maximum charge
	      Int_t padmax = 0;
	 			for (Int_t i = 0; i < fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMSiLiEMult(); i++) {
//				   if (fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMSiLiEDetectorNbr(i) == 5 && fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMSiLiEEnergy(i) > fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMSiLiEEnergy(padmax)) padmax=i;
				   if ( fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMSiLiEEnergy(i) > fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMSiLiEEnergy(padmax)) padmax=i;
				}
    	  MM5_STRX_SILI->Fill(fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMSiLiEEnergy(padmax), fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMStripXEEnergy(0));
//	MM5_STRX_SILI->Fill(fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMStripXEEnergy(0), (fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMSiLiEEnergy(0)-8192)*.02);
    	}  
      else if ( fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMStripXEDetectorNbr(0) == 8)  {
// LN: Find the pad carrying out the maximum charge
	      Int_t padmax = 0;
	 			for (Int_t i = 0; i < fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMSiLiEMult(); i++) {
//				   if (fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMSiLiEDetectorNbr(i) == 8 && fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMSiLiEEnergy(i) > fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMSiLiEEnergy(padmax)) padmax=i;
				   if (fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMSiLiEEnergy(i) > fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMSiLiEEnergy(padmax)) padmax=i;
				}
    	  MM8_STRX_SILI->Fill(fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMSiLiEEnergy(padmax), fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMStripXEEnergy(0));
// 	MM8_STRX_SILI->Fill(fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMStripXEEnergy(0), (fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMSiLiEEnergy(0)-8192)*.02);
    	}
    }

  // DE-E between strips & CsI 
    
    if ( (fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMStripXEMult()==1) && (fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMCsIEMult()==1)) {     

      if ( fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMStripXEDetectorNbr(0) == 1)  	   {
	MM1_STRX_CSI->Fill( fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMCsIEEnergy(0), fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMStripXEEnergy(0));
      }
      else if ( fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMStripXEDetectorNbr(0) == 2)   {
	MM2_STRX_CSI->Fill( fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMCsIEEnergy(0), fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMStripXEEnergy(0));
      }
      else if ( fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMStripXEDetectorNbr(0) == 3)   {
	MM3_STRX_CSI->Fill(fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMCsIEEnergy(0), fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMStripXEEnergy(0));
      }
      else if ( fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMStripXEDetectorNbr(0) == 4)   {
	MM4_STRX_CSI->Fill(fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMCsIEEnergy(0), fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMStripXEEnergy(0));			   
      }
      else if ( fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMStripXEDetectorNbr(0) == 6)   {
	MM6_STRX_CSI->Fill(   (fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMCsIEEnergy(0)-8192)*.02, fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMStripXEEnergy(0)  );
      }
      else if ( fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMStripXEDetectorNbr(0) == 7)   {
	MM7_STRX_CSI->Fill(   (fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMCsIEEnergy(0)-8192)*.02,  fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMStripXEEnergy(0));
      }
    }
         
  }


  ///////////////////////////
  //   Treat SSSD events   //
  ///////////////////////////
  if (bSSSD) {
    
    // STR_E
    for (Int_t i = 0; i < fSSSD->GetSSSDData()->GetEnergyMult(); i++) {
      SSSD_E_BRU[fSSSD->GetSSSDData()->GetEnergyDetectorNbr(i) - 1] -> Fill(fSSSD->GetSSSDData()->GetEnergyStripNbr(i), fSSSD->GetSSSDData()->GetEnergy(i));
    }
    
    // STR_T
    //for (Int_t i = 0; i < fSSSD->GetSSSDData()->GetTimeMult(); i++) {
    //       SSSD_T_BRU[fSSSD->GetSSSDData()->GetTimeDetectorNbr(i) - 1] -> Fill(fSSSD->GetSSSDData()->GetTimeStripNbr(i), fSSSD->GetSSSDData()->GetTime(i));
    //}
	   
    // make analysis
    fSSSD->Treat();
    
    // STR_E CAL
    for (Int_t i = 0; i < fSSSD->GetSSSDPhysics()->GetPreTreatedData()->GetEnergyMult(); i++) {
      SSSD_E_CAL[fSSSD->GetSSSDPhysics()->GetPreTreatedData()->GetEnergyDetectorNbr(i) - 1] -> Fill(fSSSD->GetSSSDPhysics()->GetPreTreatedData()->GetEnergyStripNbr(i), fSSSD->GetSSSDPhysics()->GetPreTreatedData()->GetEnergy(i));
    }
    
    // STR_T
    //for (Int_t i = 0; i < fSSSD->GetSSSDPhysics()->GetPreTreatedData()->GetTimeMult(); i++) {
    //       SSSD_T_CAL[fSSSD->GetSSSDPhysics()->GetPreTreatedData()->GetTimeDetectorNbr(i) - 1] -> Fill(fSSSD->GetSSSDPhysics()->GetPreTreatedData()->GetTimeStripNbr(i), fSSSD->GetSSSDPhysics()->GetPreTreatedData()->GetTime(i));
    //}

    // DE-E between SSSD & strips for telescopes 1-4 iff mult=1 in both MUST2 and 20mu
    if (bMust2){
      if(fSSSD->GetSSSDPhysics()->GetPreTreatedData()->GetEnergyMult()==1 && fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMStripXEMult()==1){
    	TVector3 Vbeam(0,0,1);
    	TVector3 Vinteraction = fMust2->GetMust2Physics()->GetPositionOfInteraction(0);
    	Double_t Angle = Vinteraction.Angle(Vbeam) * 180./TMath::Pi();
    	Double_t Etotal = fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMStripXEEnergy(0) + fSSSD->GetSSSDPhysics()->GetPreTreatedData()->GetEnergy(0);
	
    	for (Int_t i = 0; i < 4; i++) {
    	    if (fSSSD->GetSSSDPhysics()->GetPreTreatedData()->GetEnergyDetectorNbr(0) == (i+1) && fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMStripXEDetectorNbr(0) == (i+1)) {
    		   MM_SSSD_STRX[i] -> Fill(fMust2->GetMust2Physics()->GetPreTreatedData()->GetMMStripXEEnergy(0), fSSSD->GetSSSDPhysics()->GetPreTreatedData()->GetEnergy(0));
    	     	   ANGLE_ETOTAL[i]->Fill(Angle,Etotal);
    	    }
    	}		
      }
    }

    
  }

  
  ////////////////////////////
  //   Treat CHIO & PLASTIC //
  ////////////////////////////

  if(bChio_an)
    {
	  // arriving here we dont know if either Energy or Energy_pileup is present
	  if (fChio_an->GetChio_anData()->GetMultE()>0)
	  {
			CHIO_AN->Fill(fChio_an->GetChio_anData()->GetEnergy(0));
			TOF_PLGAL_CHIO_AN->Fill( fTac->GetTacData()->GetTAC_PL_GAL(),	fChio_an->GetChio_anData()->GetEnergy(0));
			TOF_PLCATS2_CHIO_AN->Fill(fTac->GetTacData()->GetTAC_PL_CATS2(),  fChio_an->GetChio_anData()->GetEnergy(0));
			// Spectrum DeltaE-E (Pl-Chio)
			if(bPlastic)
			{
				DE_E_PL_CHIO_AN->Fill(fPlastic->GetPlasticData()->GetEnergy(0),fChio_an->GetChio_anData()->GetEnergy(0));
			}  
         }
		
       if (fChio_an->GetChio_anData()->GetMultE_pileup()>0){
          CHIO_AN_PILEUP->Fill(fChio_an->GetChio_anData()->GetEnergy_pileup(0));
		}

    	if(bChio_dig){
	      	for (Int_t i=0;i< fChio_dig->GetChio_digData()->GetEsize();i++)
			{
				CHIO_DIG -> Fill(i, fChio_dig->GetChio_digData()->GetEnergy(i));
			}
			// select only events for which there is no pile up
			if(fChio_dig->GetChio_digPhysics()->rawAmplitude.size()==1)
			{
			  TOF_PLGAL_CHIO_DIG->Fill( fTac->GetTacData()->GetTAC_PL_GAL(), fChio_dig->GetChio_digPhysics()->rawAmplitude.at(0));
			  TOF_PLCATS2_CHIO_DIG->Fill(fTac->GetTacData()->GetTAC_PL_CATS2(), fChio_dig->GetChio_digPhysics()->rawAmplitude.at(0));
			  // Spectrum DeltaE-E (Pl-Chio)
			  if(bPlastic)
			  {
			    DE_E_PL_CHIO_DIG->Fill( fPlastic->GetPlasticData()->GetEnergy(0),   fChio_dig->GetChio_digPhysics()->rawAmplitude.at(0));
			  }  
			}
    }
  }  

  ///////////////////////////
  //   Treat TAC           //
  ///////////////////////////
  
  if(bTac){
    hTAC_MM_CATS1->Fill(fTac->GetTacData()->GetTAC_MM_CATS1());
    hTAC_MM_CATS2->Fill(fTac->GetTacData()->GetTAC_MM_CATS2());
    hTAC_PL_CATS1->Fill(fTac->GetTacData()->GetTAC_PL_CATS1());
    hTAC_PL_CATS2->Fill(fTac->GetTacData()->GetTAC_PL_CATS2());
    hTAC_CATS12  ->Fill(fTac->GetTacData()->GetTAC_CATS12());  
    hTAC_PL_GAL  ->Fill(fTac->GetTacData()->GetTAC_PL_GAL());  
    hTAC_CATS1_HF->Fill(fTac->GetTacData()->GetTAC_CATS1_HF());
    hTAC_CATS2_HF->Fill(fTac->GetTacData()->GetTAC_CATS2_HF());
    hTAC_MM_HF   ->Fill(fTac->GetTacData()->GetTAC_MM_HF());
  }
  
  ///////////////////////////////////////////
  //   Treat LISE when LISE trigger present //
  ///////////////////////////////////////////

  if(bTrigLise && bLise)
	{
		Float_t XXD6 = 8192.*fLise->GetLiseData()->GetX_D6();
		Float_t YYD6 = 8192.*fLise->GetLiseData()->GetY_D6();
		// if(pipo_cutg_iolanda->IsInside(XXD6, YYD6))
		// {
		// 	//cout << "coucou, je suis la" << endl;
		// }
		hXY_SID6-> Fill(XXD6, YYD6);
		hDED6_TOF->Fill(fLise->GetLiseData()->GetTD6_HF(),fLise->GetLiseData()->GetE_D6());

	}

  /////////////////////////////////////////////////////
  //   Treat LISE without obligatory a LISE trigger  //
  /////////////////////////////////////////////////////
	
  // use D6 cut
   // if (bLise && bChio_an && fChio_an->GetChio_anData()->GetMultE()>0) {
   //    if (CutIdentLise[0]->IsInside(fLise->GetLiseData()->GetTD6_HF(),fLise->GetLiseData()->GetE_D6())) {
   //       TOF_PLGAL_CHIO_AN_CondD6->Fill(fTac->GetTacData()->GetTAC_PL_GAL(), fChio_an->GetChio_anData()->GetEnergy(0));
   //    }
   // }



}


void GUser::EndUserRun()
{
  //  end of run ,  executed a end of each run

  cout <<"--------------< End User Run >------------------\n";
    
}

//______________________________________________________________
void GUser::EndUser()
{
  // global final end executed a end of runs
  // must be explicitly called! 

	
  cout <<"--------------< End User 1> ------------------\n";
   
  //cout << "End save spectra " << endl;    
    
}
//______________________________________________________________________________

void GUser::InitTTreeUser()
{
  // User method for specific initialisation of TTree
  // It can be useful for example multi-hit detections
  // or to have a TTree with only few parameters ( for low compute)
  // to run this method , you have to slect mode 3 in  SetTTreeMode
  // ex : a->SetTTreeMode(3,"/space/MyTTree.root");

  cout<<"GUser::InitTTreeUser()"<<endl;
  
  cout << "GUser::InitTTreeUser() -> fTheTree " << fTheTree << endl;
  
  fMust2->InitBranch(fTheTree);
  fCATS->InitBranch(fTheTree);
  fSSSD->InitBranch(fTheTree);
  fTrigger->InitBranch(fTheTree);
  fTac->InitBranch(fTheTree);
  fChio_an->InitBranch(fTheTree);
  fChio_dig->InitBranch(fTheTree);
  fPlastic->InitBranch(fTheTree);
  fLise->InitBranch(fTheTree);
  
  cout<<"End GUser::InitTTreeUser()"<<endl;
  
}
