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
#ifndef __LABR3__
#define __LABR3__

#ifndef __DETECTOR__
#include "TDetector.h"
#endif

#ifndef __LABR3DATA__
#include "TLaBr3Data.h"
#endif

#include "DataParameters.h"
#include "TTree.h"

#define	LABR3_E	1
#define	LABR3_T	2

class TLaBr3 : public TDetector 
{
 
 public:
	TLaBr3();
	virtual ~TLaBr3();

	// virtual methods from TDetector
	virtual bool Init(DataParameters*);
	virtual bool Clear();
	virtual bool Is(UShort_t, Short_t);
	virtual bool Treat();
	virtual void InitBranch(TTree*);

   void Clear(const Option_t*) {};

	// getters and setters
	TLaBr3Data*    GetLaBr3Data() const {return fLaBr3Data;}
	
 private:

	// Data class for LaBr3
	TLaBr3Data  *fLaBr3Data;

	ClassDef(TLaBr3,1)  // LaBr3 detector structure
};

#endif
