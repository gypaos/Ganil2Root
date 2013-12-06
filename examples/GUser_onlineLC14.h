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

// ROOT headers
#include <TObject.h>
#include <TRint.h>
#include <TString.h>

// GRU headers
#include "General.h"
#include "GAcq.h"
#include "GDevice.h"
#include "GParaCaliXml.h"
#include "GNetServerRoot.h"

// NPTool header
#include "DetectorManager.h"

// Ganil2Root headers
#include "TDetector.h"
#include "TMust2.h"
#include "TCATS.h"
#include "TExogam.h"
#include "TTrigger.h"
#include "TTac.h"
#include "TPlastic.h"
#include "TLise.h"
#include "TTiaraHyball.h"
#include "TTiaraBarrel.h"


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
   TExogam       *fExogam;
	TTrigger      *fTrigger;
	TTac          *fTac;
	TPlastic      *fPlastic;
	TLise         *fLise;
   TTiaraHyball  *fTiaraHyball;
   TTiaraBarrel  *fTiaraBarrel;

 private:
   DetectorManager   *fMyDetector;

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

