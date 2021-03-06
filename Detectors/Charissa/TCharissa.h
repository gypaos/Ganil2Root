/*****************************************************************************
 * Copyright (C) 2008   this file is part of the Ganil2Root Project          *
 *                                                                           *
 * For the licensing terms see $GANIL2ROOT/Licence                           *
 * For the list of contributors see $GANIL2ROOT/README/CREDITS               *
 *****************************************************************************/

/*****************************************************************************
 * Original Author: N. de Sereville  contact address: deserevi@ipno.in2p3.fr *
 *                                                                           *
 * Creation Date  : Dec 2013                                                 *
 * Last update    :                                                          *
 *---------------------------------------------------------------------------*
 * Decription: This class is in charged of converting raw data from GANIL    *
 *             format to a ROOT format for the Charissa detector             *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Comment:                                                                  *
 *                                                                           *
 *****************************************************************************/
#ifndef __CHARISSA__
#define __CHARISSA__

#ifndef __DETECTOR__
#include "TDetector.h"
#endif

#ifndef __CHARISSADATA__
#include "TCharissaData.h"
#endif

#include "DataParameters.h"
#include "TTree.h"

#define CHA_DE_X_E	1
#define CHA_DE_X_T	2
#define CHA_DE_Y_E	3
#define CHA_DE_Y_T	4
#define CHA_E_X_E	5
#define CHA_E_X_T	6
#define CHA_E_Y_E	7
#define CHA_E_Y_T	8
#define CHA_CSI_E	      9
//#define ECsI	        9
#define CHA_CSI_T       10

class TCharissa : public TDetector 
{
 public:
	TCharissa();
	virtual ~TCharissa();

	// virtual methods from TDetector
	virtual bool Init(DataParameters*);
	virtual bool Clear();
	virtual bool Is(UShort_t, Short_t);
	virtual bool Treat();
	virtual void InitBranch(TTree*);

   void Clear(const Option_t*) {};

	// getters and setters
	TCharissaData*	   GetCharissaData()    const {return fCharissaData;}

 private:
	// Data class for Charissa
	TCharissaData  *fCharissaData;

	ClassDef(TCharissa, 1)  // Charissa detector structure
};

#endif
