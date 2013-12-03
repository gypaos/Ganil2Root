// File :  GUser.h
// Author: Luc Legeard
//////////////////////////////////////////////////////////////////////////////
//
// Class GUser
//
// This class mange user methodes
//
/////////////////////////////////////////////////////////////////////////////

// ---------------------------------------------------------------------------
// ***************************************************************************
// *                                                                         *
// *   This program is free software; you can redistribute it and/or modify  *
// *   it under the terms of the GNU General Public License as published by  *
// *   the Free Software Foundation; either version 2 of the License, or     *
// *   (at your option) any later version.                                   *
// *                                                                         *
// ***************************************************************************/


#ifndef __GUser__
#define __GUser__

#include <sstream>
using std::ostream;

#include <TObject.h>
#include "General.h"
#include "GAcq.h"
#include "GDevice.h"

#include <TRint.h>
#include <TObject.h>
#include <TString.h>
#include <TH1.h>
#include "GParaCaliXml.h"
#include "GNetServerRoot.h"

#include "TDetector.h"
#include "TMust2.h"
#include "TCATS.h"
#include "TSSSD.h"
#include "TTrigger.h"
#include "TTac.h"
#include "TPlastic.h"
#include "TChio_an.h"
#include "TChio_dig.h"
#include "TLise.h"
//#include "TTiaraHyball.h"
//#include "TTiaraBarrel.h"

using namespace std;


class GUser : public  GAcq
{
 protected:
	int fMyLabel;
	TString fMyParameterName;
  
	GSpectra*         MySpectraList;
	GNetServerRoot*   MySpectraServer;
    
 private:
	TMust2			   *fMust2;
	TCATS			   *fCATS;
	TSSSD			   *fSSSD;
	TTrigger                   *fTrigger;
	TTac			   *fTac;
	TPlastic		   *fPlastic;
	TChio_an		   *fChio_an;
	TChio_dig		   *fChio_dig;
	TLise			   *fLise;
//   TTiaraHyball   *fTiaraHyball;
//   TTiaraBarrle   *fTiaraBarrel;
	    
 public:
	GUser(GDevice* _fDevIn= NULL, GDevice* _fDevOut= NULL);  // default constructor of GUser object 
	~GUser();                                                // destructor of GUser object 

  virtual void InitUser();
  virtual void InitUserRun();
  virtual void User();
  virtual void EndUserRun();
  virtual void EndUser();
  virtual void InitTTreeUser(); 

 private:
  TCutG *pipo_cutg_iolanda;

  static const Int_t numberCutLise = 10;
  TCutG *CutIdentLise[numberCutLise];
  
   ///////////////////////////////////////////////
   //            SPECTRA DEFINITION             //
   ///////////////////////////////////////////////

   ///////////////////////////////////////////////
   //           TRIGGER                         //
   ///////////////////////////////////////////////
		TH1I *hTRIGGER;
   ///////////////////////////////////////////////
   //              CATS MONODIM                 //
   ///////////////////////////////////////////////
   // Number of Telescopes
   static const Int_t numberCats = 2;

	TH1I *CATS_STRX_MULT[numberCats]; // dim = 28
	TH1I *CATS_STRY_MULT[numberCats]; // dim = 28
        TH1I *CATS_STRX_MAX[numberCats];  // dim = 28 X strip with max charge
        TH1I *CATS_STRY_MAX[numberCats];  // dim = 28 Y strip with max charge
        TH1F *CATS_STRX_Q3[numberCats];   // Charge of 3 strips around max normalised by total charge of all strips: Q3 > 50%
        TH1F *CATS_STRY_Q3[numberCats];   // Charge of 3 strips around max normalised by total charge of all strips: Q3 > 50%
	
   ///////////////////////////////////////////////
   //              CATS BIDIM                   //
   ///////////////////////////////////////////////

	TH2I *CATS_STRX_Q_BRU[numberCats];  // dim = 28 x 512
	TH2I *CATS_STRY_Q_BRU[numberCats];  // dim = 28 x 512
        TH2I *CATS_STRX_Q_CAL[numberCats];  // dim = 28 x 512 
        TH2I *CATS_STRY_Q_CAL[numberCats];  // dim = 28 x 512
	
        TH2I *CATS_CHARGE_X[numberCats];    // Correlation induced charge X vs anode charge 
        TH2I *CATS_CHARGE_Y[numberCats];    // Correlation induced charge Y vs anode charge 
        TH2I *CATS_CHARGE_XY[numberCats];   // Correlation total charge X vs Y strips
        TH2I *CATS_12_X;		    // Correlation between position X obtained from CATS1 & CATS2
        TH2I *CATS_12_Y;		    // Correlation between position Y obtained from CATS1 & CATS2
	TH2I *CATS_XY_MAX[numberCats];      // max X vs Y strip for each CATS
	TH2I *CATS_XY_POS[numberCats];      // Position reconstruction X vs Y w/method TCATSPhysics.cxx
        //TH2I *CATS_XY_SEC[numberCats];    // Position reconstruction X vs Y w/hyperbolic secant 
        //TH2I *CATS_XY_COG[numberCats];    // Position reconstruction X vs Y w/the weighted average	
        TH2I *CATS_XY_TARGET;		    // Position reconstruction X vs Y in mm at target position
	
	
   ///////////////////////////////////////////////
   //              MUST2 MONODIM                //
   ///////////////////////////////////////////////
   // Number of Telescopes
   static const Int_t numberMust2 = 8;

   TH1I *MULT_TEL;		// dim = 8 nbr of telescopes that is hit
   TH1I *MM_HITXE; 		// dim = 8 hit pattern for MM from XE
   TH1I *MM_HITYE;		// dim = 8 hit pattern for MM from YE
   TH1I *MM1_CSI_HIT;		// dim = 16 hit pattern for CsI of MM1
   TH1I *MM2_CSI_HIT;		// dim = 16
   TH1I *MM3_CSI_HIT;		// dim = 16
   TH1I *MM4_CSI_HIT;		// dim = 16
   TH1I *MM5_SILI_HIT;	        // dim = 16
   TH1I *MM6_CSI_HIT;		// dim = 16
   TH1I *MM7_CSI_HIT;		// dim = 16
   TH1I *MM8_SILI_HIT;	        // dim = 16

   TH1I *MM_STRX_MULT[numberMust2]; // dim = 128
   TH1I *MM_STRY_MULT[numberMust2]; // dim = 128
	
   ///////////////////////////////////////////////
   //               MUST2 BIDIM                 //
   ///////////////////////////////////////////////
   // Strips (X,Y) (E,T)
   TH2I *MM_STRX_E_BRU[numberMust2];   // dim = 128 x 512
   TH2I *MM_STRY_E_BRU[numberMust2];
   TH2I *MM_STRX_T_BRU[numberMust2];
   TH2I *MM_STRY_T_BRU[numberMust2];
   // SiLi & CsI E
   TH2I *MM_SILI_E_BRU[numberMust2];   // dim = 16 x 512
   TH2I *MM_SILI_T_BRU[numberMust2];   // dim = 16 x 512
   TH2I *MM_CSI_E_BRU[numberMust2];    // dim = 16 x 512
   TH2I *MM_CSI_T_BRU[numberMust2];    // dim = 16 x 512
   // Strips (X,Y) (E,T) cal
   TH2I *MM_STRX_E_CAL[numberMust2];   // dim = 128 x 500 (50 MeV range)
   TH2I *MM_STRY_E_CAL[numberMust2];
   TH2I *MM_STRX_T_CAL[numberMust2];   // dim = 128 x 500 (500 ns range)
   TH2I *MM_STRY_T_CAL[numberMust2];
   // SiLi & CsI E cal
   TH2I *MM_SILI_E_CAL[numberMust2];   // dim = 16 x 512
   TH2I *MM_SILI_T_CAL[numberMust2];   // dim = 16 x 512
   TH2I *MM_CSI_E_CAL[numberMust2];    // dim = 16 x 512
   TH2I *MM_CSI_T_CAL[numberMust2];    // dim = 16 x 512

   // impact map & energy correlation
   TH2I *MM_STRXY_IMPACT[numberMust2];  // dim = 128 x 128 
   TH2I *MM_STRXY_E_CAL[numberMust2];   // dim = 500 x 500 

   // calibrated DE-E
   TH2I *MM1_STRX_CSI;   // dim = 500 x 500 (50 MeV range)   
   TH2I *MM2_STRX_CSI;
   TH2I *MM3_STRX_CSI;
   TH2I *MM4_STRX_CSI;
   TH2I *MM5_STRX_SILI;                   
   TH2I *MM6_STRX_CSI;
   TH2I *MM7_STRX_CSI;
   TH2I *MM8_STRX_SILI;
 
   ///////////////////////////////////////////////
   //              SSSD                //
   ///////////////////////////////////////////////
   // Number of SSSDs
   static const Int_t numberSSSD = 4;

   TH2I *SSSD_E_BRU[numberSSSD];
   TH2I *SSSD_E_CAL[numberSSSD];

   TH2I *MM_SSSD_STRX[numberSSSD];
   TH2I *ANGLE_ETOTAL[numberSSSD];

   ///////////////////////////////////////////////
   //              CHIO               //
   ///////////////////////////////////////////////
   TH1I *CHIO_AN;
   TH1I *CHIO_AN_PILEUP;
   TH2I *CHIO_DIG;
   // DeltaE-ToF
   TH2I *TOF_PLGAL_CHIO_AN;
   //TH2I *TOF_PLGAL_CHIO_AN_CondD6;
   TH2I *TOF_PLCATS2_CHIO_AN;
   TH2I *TOF_PLGAL_CHIO_DIG;
   TH2I *TOF_PLCATS2_CHIO_DIG;
   // DeltaE-E
   TH2I *DE_E_PL_CHIO_AN;
   TH2I *DE_E_PL_CHIO_DIG;

   ///////////////////////////////////////////////
   //              TAC                 //
   ///////////////////////////////////////////////
   TH1I *hTAC_MM_CATS1;
   TH1I *hTAC_MM_CATS2;
   TH1I *hTAC_PL_CATS1;
   TH1I *hTAC_PL_CATS2;
   TH1I *hTAC_CATS12;
   TH1I *hTAC_PL_GAL;
   TH1I *hTAC_CATS1_HF;
   TH1I *hTAC_CATS2_HF;
   TH1I *hTAC_MM_HF;

   ///////////////////////////////////////////////
   //			Identification with LISE							//
   ///////////////////////////////////////////////
	
	TH2I *hDED6_TOF;
	TH2F	*hXY_SID6;

   ClassDef (GUser ,1); // User Treatment of Data
  
};

#endif
 
