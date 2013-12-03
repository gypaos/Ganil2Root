/*****************************************************************************
 * Copyright (C) 2008   this file is part of the Ganil2Root Project          *
 *                                                                           *
 * For the licensing terms see $GANIL2ROOT/Licence                           *
 * For the list of contributors see $GANIL2ROOT/README/CREDITS               *
 *****************************************************************************/

/*****************************************************************************
 * Original Author: N. de Sereville  contact address: deserevi@ipno.in2p3.fr *
 *                                                                           *
 * Creation Date  : March 2011                                               *
 * Last update    :                                                          *
 *---------------------------------------------------------------------------*
 * Decription: This class is in charged of converting raw data from GANIL    *
 *             format to a ROOT format for the SSSD detector (20 microns)    *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Comment:                                                                  *
 *                                                                           *
 *****************************************************************************/
#ifndef __SSSD__
#define __SSSD__

#ifndef __DETECTOR__
#include "TDetector.h"
#endif

#ifndef __SSSDDATA__
#include "TSSSDData.h"
#endif

#include "GDataParameters.h"
#include "TTree.h"

#define SSSD_E	1
#define SSSD_T	2


class TSSSD : public TDetector 
{
 
 public:
	
	TSSSD();
	virtual ~TSSSD();
	// virtual methods from TDetector
	virtual bool Init(GDataParameters*);
	virtual bool Clear();
	virtual bool Is(UShort_t, Short_t);
	virtual bool Treat();
	virtual void InitBranch(TTree*);

   void Clear(const Option_t*) {};

	// getters and setters
	TSSSDData*	   GetSSSDData()    const {return fSSSDData;}

 private:
	// Data class for SSSD
	TSSSDData      *fSSSDData;

	ClassDef(TSSSD,2)  // SSSD detector structure
};

#endif
