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
 * Last update    : Dec 2013                                                 *
 *---------------------------------------------------------------------------*
 * Decription: This class is in charged of converting raw data from GANIL    *
 *             format to a ROOT format for the Cats detector                 *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Comment:                                                                  *
 *    + march 2011: Add support for TCATSPhysics from NPTool                 *
 *    + decem 2013: Remove support for TCATSPhysics from NPTool              *
 *                                                                           *
 *****************************************************************************/
#ifndef __CATS__
#define __CATS__

#ifndef __DETECTOR__
#include "TDetector.h"
#endif

#ifndef __CATSDATA__
#include "TCATSData.h"
#endif

#include "DataParameters.h"
#include "TTree.h"

#define CATS_X		1
#define CATS_Y		2
#define CATS_Q		3
namespace G2R{
class CATS : public TDetector 
{
 public:
	CATS();
	virtual ~CATS();
	// virtual methods from TDetector
	virtual bool Init(DataParameters*);
	virtual bool Clear();
	virtual bool Is(UShort_t, Short_t);
	virtual bool Treat();
	virtual void InitBranch(TTree*);

   void Clear(const Option_t*) {};

	// getters and setters
	TCATSData*     GetCATSData()     const {return fCATSData;}
  static G2R::VDetector* G2R::CATS::Construct();

 private:
	// Data class for TCATSData
	TCATSData    *fCATSData;

	ClassDef(CATS,2)  // CATS detector structure
};
}
#endif
