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
 * Last update    :                                                          *
 *---------------------------------------------------------------------------*
 * Decription: This class is in charged of converting raw data from GANIL    *
 *             format to a ROOT format for the GMT module                    *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Comment:                                                                  *
 *                                                                           *
 *****************************************************************************/
#ifndef G2RTRIGGER
#define G2RTRIGGER

#include "G2RVDetector.h"
#include "TTriggerData.h"

#include "DataParameters.h"
#include "TTree.h"


#define	TRIG_1	1
#define	TRIG_2	2
#define	TRIG_3	3
#define	TRIG_4	4
#define	TRIG_5	5

namespace G2R{
class Trigger : public G2R::VDetector 
{
 public:
	Trigger();
	virtual ~Trigger();
	// virtual methods from TDetector
	virtual bool Init(DataParameters*);
	virtual bool Clear();
	virtual bool Is(UShort_t, Short_t);
	virtual bool Treat();
	virtual void InitBranch(TTree*);

   void Clear(const Option_t*) {};

	// getters and setters
	TTriggerData*  GetTriggerData() const {return fTriggerData;}

 private:
	// Data class for Trigger
	TTriggerData  *fTriggerData;

	ClassDef(G2R::Trigger,1)  // Trigger structure
};
}
#endif
