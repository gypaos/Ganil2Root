/*****************************************************************************
 * Copyright (C) 2008   this file is part of the Ganil2Root Project          *
 *                                                                           *
 * For the licensing terms see $GANIL2ROOT/Licence                           *
 * For the list of contributors see $GANIL2ROOT/README/CREDITS               *
 *****************************************************************************/

/*****************************************************************************
 * Original Author: M. Niikura      contact address: niikura@ipno.in2p3.fr   *
 *                                                                           *
 * Creation Date  : March 2011                                               *
 * Last update    :                                                          *
 *---------------------------------------------------------------------------*
 * Decription: This class is in charged of converting raw data from GANIL    *
 *             format to a ROOT format for the Chio detector                 *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Comment:                                                                  *
 *                                                                           *
 *****************************************************************************/
#ifndef __CHIO_AN__
#define __CHIO_AN__

#ifndef __DETECTOR__
#include "TDetector.h"
#endif

#ifndef __CHIO_ANDATA__
#include "TChio_anData.h"
#endif

#include "GDataParameters.h"
#include "TTree.h"

#define	CHIO_AN_E	1
#define	CHIO_AN_E_PILEUP	2

class TChio_an : public TDetector 
{
 public:
	TChio_an();
	virtual ~TChio_an();

	// virtual methods from TDetector
	virtual bool Init(GDataParameters*);
	virtual bool Clear();
	virtual bool Is(UShort_t, Short_t);
	virtual bool Treat();
	virtual void InitBranch(TTree*);

   void Clear(const Option_t*) {};

	// getters and setters
	TChio_anData*    GetChio_anData()    const {return fChio_anData;}
	
 private:
	// Data and Physics class for Chio_an
	TChio_anData    *fChio_anData;
	
	ClassDef(TChio_an,2)  // Ionisation Chamber with std electronics detector structure
};

#endif
