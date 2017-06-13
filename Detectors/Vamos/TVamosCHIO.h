#ifndef __VAMOSCHIO__
#define __VAMOSCHIO__
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
 *             format to a ROOT format for the Vamos chio detector           *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Comment:                                                                  *
 *                                                                           *
 *****************************************************************************/
#ifndef __DETECTOR__
#include "TDetector.h"
#endif

#ifndef __VAMOSCHIODATA__
#include "TVamosCHIOData.h"
#endif

#include "DataParameters.h"
#include "TTree.h"

#define VAMOS_A	1
#define VAMOS_B	2
#define VAMOS_C	3

class TVamosCHIO : public TDetector {
  public:
   TVamosCHIO();
   virtual ~TVamosCHIO();

   // virtual methods from TDetector
   virtual bool Init(DataParameters*);
   virtual bool Clear();
   virtual bool Is(UShort_t, Short_t);
   virtual bool Treat();
   virtual void InitBranch(TTree*);

   void Clear(const Option_t*) {};

   // getters and setters
   TVamosCHIOData*	GetVamosCHIOData() const {return fVamosCHIOData;}

  private:
   // Data class
   TVamosCHIOData  *fVamosCHIOData;

   ClassDef(TVamosCHIO,1)  // VamosCHIO detector structure
};

#endif
