/*****************************************************************************
 * Copyright (C) 2008   this file is part of the Ganil2Root Project          *
 *                                                                           *
 * For the licensing terms see $GANIL2ROOT/Licence                           *
 * For the list of contributors see $GANIL2ROOT/README/CREDITS               *
 *****************************************************************************/

/*****************************************************************************
 * Original Author: L. Lefebvre      contact address: lefebvrl@ipno.in2p3.fr *
 *                                                                           *
 *                                                                           *
 * Creation Date  : June 2011                                                *
 * Last update    :                                                          *
 *---------------------------------------------------------------------------*
 * Decription: This class is in charged of converting raw data from GANIL    *
 *             format to a ROOT format for the Speg chio detector            *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Comment:                                                                  *
 *                                                                           *
 *****************************************************************************/
#ifndef __SPEGCHIO__
#define __SPEGCHIO__

#ifndef __DETECTOR__
#include "TDetector.h"
#endif

#ifndef __SPEGCHIODATA__
#include "TSpegCHIOData.h"
#endif

#include "DataParameters.h"
#include "TTree.h"


#define AN	1



class TSpegCHIO : public TDetector {
  public:
   TSpegCHIO();
   virtual ~TSpegCHIO();

   // virtual methods from TDetector
   virtual bool Init(DataParameters*);
   virtual bool Clear();
   virtual bool Is(UShort_t, Short_t);
   virtual bool Treat();
   virtual void InitBranch(TTree*);

   void Clear(const Option_t*) {};

   // getters and setters
   TSpegCHIOData*	GetSpegCHIOData() const {return fSpegCHIOData;}

  private:
   // Data class for SPEG
   TSpegCHIOData  *fSpegCHIOData;

   ClassDef(TSpegCHIO,1)  // SpegCHIO detector structure
};

#endif
