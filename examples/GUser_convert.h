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
#include "GParaCaliXml.h"
#include "GNetServerRoot.h"

#include "TDetector.h"
#include "TMust2.h"
#include "TCATS.h"
#include "TSSSD.h"
#include "TExogam.h"
#include "TMaya.h"
#include "TTrigger.h"
#include "TTac.h"
#include "TPlastic.h"
#include "TChio_an.h"
#include "TChio_dig.h"
#include "TLise.h"
#include "TVamosFinger.h"
#include "TVamosPlastic.h"
#include "TVamosCHIO.h"
#include "TVamosDC.h"

using namespace std;


class GUser : public  GAcq
{
 protected:
	int fMyLabel;
	TString fMyParameterName;
  
	GSpectra*         MySpectraList;
	GNetServerRoot*   MySpectraServer;
    
 private:
	TMust2        *fMust2;
	TCATS	        *fCATS;
	TSSSD	        *fSSSD;
   TExogam       *fExogam;
	TTrigger      *fTrigger;
	TTac          *fTac;
	TPlastic      *fPlastic;
	TChio_an      *fChio_an;
	TChio_dig     *fChio_dig;
	TLise         *fLise;
   TVamosFinger  *fVamosFinger;
   TVamosPlastic *fVamosPlastic;
   TVamosCHIO    *fVamosCHIO;
   TVamosDC      *fVamosDC;
   TMaya         *fMaya;

 public:
   GUser(GDevice* _fDevIn= NULL, GDevice* _fDevOut= NULL);  // default constructor of GUser object 
   ~GUser();                                                // destructor of GUser object 

   virtual void InitUser();
   virtual void InitUserRun();
   virtual void User();
   virtual void EndUserRun();
   virtual void EndUser();
   virtual void InitTTreeUser(); 

   ClassDef (GUser ,1); // User Treatment of Data
};

#endif

