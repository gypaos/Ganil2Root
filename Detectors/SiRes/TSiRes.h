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
 *             format to a ROOT format for the plastic detector              *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Comment:                                                                  *
 *    + march 2011: Add support for TPlasticPhysics from NPTool              *
 *                                                                           *
 *****************************************************************************/
#ifndef __SiRes__
#define __SiRes__

#ifndef __DETECTOR__
#include "TDetector.h"
#endif

#ifndef __SiResDATA__
#include "TSiResData.h"
#endif

#include "DataParameters.h"
#include "TTree.h"

#define	SIRES_E	1
#define	SIRES_T	2
#define	SIRES_EBACK 3

class TSiRes : public TDetector 
{
 
 public:
	TSiRes();
	virtual ~TSiRes();

	// virtual methods from TDetector
	virtual bool Init(DataParameters*);
	virtual bool Clear();
	virtual bool Is(UShort_t, Short_t);
	virtual bool Treat();
	virtual void InitBranch(TTree*);

   void Clear(const Option_t*) {};

	// getters and setters
	TSiResData*    GetSiResData() const {return fSiResData;}
	
 private:

	// Data class for SiRes
	TSiResData  *fSiResData;

	ClassDef(TSiRes,1)  // SiRes detector structure
};

#endif
