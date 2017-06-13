/*****************************************************************************
 * Copyright (C) 2008   this file is part of the Ganil2Root Project          *
 *                                                                           *
 * For the licensing terms see $GANIL2ROOT/Licence                           *
 * For the list of contributors see $GANIL2ROOT/README/CREDITS               *
 *****************************************************************************/

/*****************************************************************************
 * Original Author: N. de Sereville  contact address: deserevi@ipno.in2p3.fr *
 *                                                                           *
 * Creation Date  : Nov 2013                                                 *
 * Last update    :                                                          *
 *---------------------------------------------------------------------------*
 * Decription: This class is in charged of converting raw data from GANIL    *
 *             format to a ROOT format for the Tiara/Barrel detector         *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Comment:                                                                  *
 *                                                                           *
 *****************************************************************************/
#ifndef __TIARABARREL__
#define __TIARABARREL__

#ifndef __DETECTOR__
#include "TDetector.h"
#endif

#ifndef __TIARABARRELDATA__
#include "TTiaraBarrelData.h"
#endif

#include "DataParameters.h"
#include "TTree.h"

#define IBAR_UP_STRIP_E	1
#define IBAR_DO_STRIP_E	2
#define IBAR_BACK_E	    3  
#define OBAR_E	        4  

class TTiaraBarrel : public TDetector 
{
 public:
	TTiaraBarrel();
	virtual ~TTiaraBarrel();

	// virtual methods from TDetector
	virtual bool Init(DataParameters*);
	virtual bool Clear();
	virtual bool Is(UShort_t, Short_t);
	virtual bool Treat();
	virtual void InitBranch(TTree*);

   void Clear(const Option_t*) {};

	// getters and setters
	TTiaraBarrelData*	   GetTiaraBarrelData()    const {return fTiaraBarrelData;}

 private:
	// Data class for TiaraBarrel
	TTiaraBarrelData  *fTiaraBarrelData;

	ClassDef(TTiaraBarrel,1)  // TIARABARREL detector structure
};

#endif
