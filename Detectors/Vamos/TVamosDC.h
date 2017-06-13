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
 *             format to a ROOT format for the Vamos drift chamber detector  *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Comment:                                                                  *
 *                                                                           *
 *****************************************************************************/
#ifndef __VAMOSDC__
#define __VAMOSDC__

#ifndef __DETECTOR__
#include "TDetector.h"
#endif

#ifndef __VAMOSDCDATA__
#include "TVamosDCData.h"
#endif

#include "DataParameters.h"
#include "TTree.h"


#define DC_Strip1	1
#define DC_Strip2	2
#define DC_E		3
#define DC_E_PU	4
#define DC_T		5


class TVamosDC : public TDetector {
  public:
   TVamosDC();
   virtual ~TVamosDC();

   // virtual methods from TDetector
   virtual bool Init(DataParameters*);
   virtual bool Clear();
   virtual bool Is(UShort_t, Short_t);
   virtual bool Treat();
   virtual void InitBranch(TTree*);

   void Clear(const Option_t*) {};

   // getters and setters
   TVamosDCData*	GetVamosDCData() const {return fVamosDCData;}

  private:
   // Data class for Must2
   TVamosDCData  *fVamosDCData;

   ClassDef(TVamosDC,1)  // VamosDC detector structure
};

#endif
