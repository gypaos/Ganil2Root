/*****************************************************************************
 * Copyright (C) 2008   this file is part of the Ganil2Root Project          *
 *                                                                           *
 * For the licensing terms see $GANIL2ROOT/Licence                           *
 * For the list of contributors see $GANIL2ROOT/README/CREDITS               *
 *****************************************************************************/

/*****************************************************************************
 * Original Author: N. de Sereville  contact address: deserevi@ipno.in2p3.fr *
 *                  J. Burgunder                    burgunder@ganil.in2p3.fr *
 *                                                                           *
 * Creation Date  : May 2009                                                 *
 * Last update    : March 2011                                               *
 *---------------------------------------------------------------------------*
 * Decription: This class is in charged of converting raw data from GANIL    *
 *             format to a ROOT format for the Must2 detector                *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Comment:                                                                  *
 *    + march 2011: Add support for TMust2Physics from NPTool                *
 *                                                                           *
 *****************************************************************************/
#ifndef __MUST2__
#define __MUST2__

#ifndef __DETECTOR__
#include "TDetector.h"
#endif

#ifndef __MUST2DATA__
#include "TMust2Data.h"
#endif

#include "GDataParameters.h"
#include "TTree.h"

#define MUST2STR_XE	1
#define MUST2STR_XT	2
#define MUST2STR_YE	3
#define MUST2STR_YT	4
#define MUST2SILI_E	5
#define MUST2SILI_T	6
#define MUST2CSI_E	7
#define MUST2CSI_T	8

class TMust2 : public TDetector 
{
 public:
	TMust2();
	virtual ~TMust2();

	// virtual methods from TDetector
	virtual bool Init(GDataParameters*);
	virtual bool Clear();
	virtual bool Is(UShort_t, Short_t);
	virtual bool Treat();
	virtual void InitBranch(TTree*);

   void Clear(const Option_t*) {};

	// getters and setters
	TMust2Data*	   GetMust2Data()    const {return fMust2Data;}

 private:
	// Data class for Must2
	TMust2Data  *fMust2Data;

	ClassDef(TMust2,2)  // MUST2 detector structure
};

#endif
