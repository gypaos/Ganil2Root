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
 *             format to a ROOT format for the TAC modules                   *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Comment:                                                                  *
 *   + The name of the variables (e.g. TAC_CATS1_HF) should be defined for   *
 *     each experiment in a consistent way with the ACTION file.             *
 *                                                                           *
 *****************************************************************************/
#ifndef __TAC__
#define __TAC__

#ifndef __DETECTOR__
#include "TDetector.h"
#endif

#ifndef __TACDATA__
#include "TTacData.h"
#endif

#include "GDataParameters.h"
#include "TTree.h"

#define TAC_CATS1_HF   1
#define TAC_CATS2_HF   2
#define TAC_CATS12   3
#define TAC_MM_HF    4
#define TAC_PL_CATS1     5
#define TAC_PL_CATS2     6
#define TAC_PL_GAL   7
#define TAC_MM_CATS1   8
#define TAC_MM_CATS2      9

class TTac : public TDetector 
{
 public:
	TTac();
	virtual ~TTac();

	// virtual methods from TDetector
	virtual bool Init(GDataParameters*);
	virtual bool Clear();
	virtual bool Is(UShort_t, Short_t);
	virtual bool Treat();
	virtual void InitBranch(TTree*);

   void Clear(const Option_t*) {};

	// getters and setters
	TTacData*	GetTacData() const {return fTacData;}

 private:
	// Data class for Tac
	TTacData  *fTacData;

	ClassDef(TTac,1)  // TAC structure
};

#endif
