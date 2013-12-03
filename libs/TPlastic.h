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
#ifndef __PLASTIC__
#define __PLASTIC__

#ifndef __DETECTOR__
#include "TDetector.h"
#endif

#ifndef __PLASTICDATA__
#include "TPlasticData.h"
#endif

#include "GDataParameters.h"
#include "TTree.h"

#define	PL_E	1

class TPlastic : public TDetector 
{
 
 public:
	TPlastic();
	virtual ~TPlastic();

	// virtual methods from TDetector
	virtual bool Init(GDataParameters*);
	virtual bool Clear();
	virtual bool Is(UShort_t, Short_t);
	virtual bool Treat();
	virtual void InitBranch(TTree*);

   void Clear(const Option_t*) {};

	// getters and setters
	TPlasticData*    GetPlasticData() const {return fPlasticData;}
	
 private:

	// Data class for Plastic
	TPlasticData  *fPlasticData;

	ClassDef(TPlastic,2)  // Plastic detector structure
};

#endif
