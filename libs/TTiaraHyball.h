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
 *             format to a ROOT format for the Tiara/Hyball detector         *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Comment:                                                                  *
 *                                                                           *
 *****************************************************************************/
#ifndef __TIARAHYBALL__
#define __TIARAHYBALL__

#ifndef __DETECTOR__
#include "TDetector.h"
#endif

#ifndef __TIARAHYBALLDATA__
#include "TTiaraHyballData.h"
#endif

#include "GDataParameters.h"
#include "TTree.h"

#define HYB_RING_E	1
#define HYB_RING_T	2
#define HYB_SECT_E	3
#define HYB_SECT_T	4

class TTiaraHyball : public TDetector 
{
 public:
	TTiaraHyball();
	virtual ~TTiaraHyball();

	// virtual methods from TDetector
	virtual bool Init(GDataParameters*);
	virtual bool Clear();
	virtual bool Is(UShort_t, Short_t);
	virtual bool Treat();
	virtual void InitBranch(TTree*);

   void Clear(const Option_t*) {};

	// getters and setters
	TTiaraHyballData*	   GetTiaraHyballData()    const {return fTiaraHyballData;}

 private:
	// Data class for TiaraHyball
	TTiaraHyballData  *fTiaraHyballData;

	ClassDef(TTiaraHyball,1)  // TIARAHYBALL detector structure
};

#endif
