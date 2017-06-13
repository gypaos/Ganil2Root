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
 *             format to a ROOT format for the Vamos finger                  *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Comment:                                                                  *
 *                                                                           *
 *****************************************************************************/
#ifndef __VAMOSFINGER__
#define __VAMOSFINGER__

#ifndef __DETECTOR__
#include "TDetector.h"
#endif

#ifndef __VAMOSFINGERDATA__
#include "TVamosFingerData.h"
#endif

#include "DataParameters.h"
#include "TTree.h"


#define	FINGER	1



class TVamosFinger : public TDetector {
  public:
   TVamosFinger();
   virtual ~TVamosFinger();

   // virtual methods from TDetector
   virtual bool Init(DataParameters*);
   virtual bool Clear();
   virtual bool Is(UShort_t, Short_t);
   virtual bool Treat();
   virtual void InitBranch(TTree*);

   void Clear(const Option_t*) {};

   // getters and setters
   TVamosFingerData*	GetVamosFingerData() const {return fVamosFingerData;}

  private:
   // Data class for VamosFinger
   TVamosFingerData  *fVamosFingerData;

   ClassDef(TVamosFinger,1)  // VamosFinger detector structure
};

#endif
