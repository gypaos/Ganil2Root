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
#ifndef __TRIGGER__
#define __TRIGGER__

#ifndef __DETECTOR__
#include "TDetector.h"
#endif

#ifndef __TRIGGERDATA__
#include "TTriggerData.h"
#endif

#include "GDataParameters.h"
#include "TTree.h"


#define	TRIG_1	1
#define	TRIG_2	2
#define	TRIG_3	3
#define	TRIG_4	4
#define	TRIG_5	5

class TTrigger : public TDetector 
{
 public:
	TTrigger();
	virtual ~TTrigger();
	// virtual methods from TDetector
	virtual bool Init(GDataParameters*);
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

	ClassDef(TTrigger,1)  // Trigger structure
};

#endif
