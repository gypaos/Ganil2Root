/*****************************************************************************
 * Copyright (C) 2008   this file is part of the Ganil2Root Project          *
 *                                                                           *
 * For the licensing terms see $GANIL2ROOT/Licence                           *
 * For the list of contributors see $GANIL2ROOT/README/CREDITS               *
 *****************************************************************************/

/*****************************************************************************
 * Original Author: L. Lefebvre  contact address: lefebvrl@ipno.in2p3.fr     *
 *                    							     *
 *                                                                           *
 * Creation Date  : June 2011                                                *
 * Last update    :                                                          *
 *---------------------------------------------------------------------------*
 * Decription: This class is in charged of converting raw data from GANIL    *
 *             format to a ROOT format for the Exl detector                  *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Comment:                                                                  *
 *                                                                           *
 *                                                                           *
 *****************************************************************************/
#ifndef __EXL__
#define __EXL__

#ifndef __DETECTOR__
#include "TDetector.h"
#endif

#ifndef __EXLDATA__
#include "TExlData.h"
#endif

#include "GDataParameters.h"
#include "TTree.h"

#define	EXL_E	1
#define	EXL_T	2

class TExl : public TDetector 
{
 
 public:
	TExl();
	virtual ~TExl();

	// virtual methods from TDetector
	virtual bool Init(GDataParameters*);
	virtual bool Clear();
	virtual bool Is(UShort_t, Short_t);
	virtual bool Treat();
	virtual void InitBranch(TTree*);

   void Clear(const Option_t*) {};

	// getters and setters
	TExlData*    GetExlData() const {return fExlData;}
	
 private:

	// Data class for Exl
	TExlData  *fExlData;
	ClassDef(TExl,1)  // Exl detector structure
};

#endif
