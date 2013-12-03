/*****************************************************************************
 * Copyright (C) 2008   this file is part of the Ganil2Root Project          *
 *                                                                           *
 * For the licensing terms see $GANIL2ROOT/Licence                           *
 * For the list of contributors see $GANIL2ROOT/README/CREDITS               *
 *****************************************************************************/

/*****************************************************************************
 * Original Author: M. Niikura      contact address: niikura@ipno.in2p3.fr   *
 *                                                                           *
 * Creation Date  : March 2011                                               *
 * Last update    :                                                          *
 *---------------------------------------------------------------------------*
 * Decription: This class is in charged of converting raw data from GANIL    *
 *             format to a ROOT format for the Chio detector                 *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Comment:                                                                  *
 *                                                                           *
 *****************************************************************************/
#ifndef __CHIO_DIG__
#define __CHIO_DIG__

#include <string>
#include <map>

#ifndef __DETECTOR__
#include "TDetector.h"
#endif

#ifndef __CHIO_DIGDATA__
#include "TChio_digData.h"
#endif

#include "GDataParameters.h"
#include "TTree.h"


#define	CHIO_DIG_E	1


class TChio_dig : public TDetector {
  public:
   TChio_dig();
   virtual ~TChio_dig();

   // virtual methods from TDetector
   virtual bool Init(GDataParameters*);
   virtual bool Clear();
   virtual bool Is(UShort_t, Short_t);
   virtual bool Treat();
   virtual void InitBranch(TTree*);

   void Clear(const Option_t*) {};

   // getters and setters
   TChio_digData*	   GetChio_digData()    const {return fChio_digData;}
   
  private:
   // Data class for Chio_dig
   TChio_digData    *fChio_digData;
 
   ClassDef(TChio_dig,2)  // Ionisation Chamber with digitizer detector structure
};

#endif
