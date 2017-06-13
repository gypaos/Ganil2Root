/*****************************************************************************
 * Copyright (C) 2008   this file is part of the Ganil2Root Project          *
 *                                                                           *
 * For the licensing terms see $GANIL2ROOT/Licence                           *
 * For the list of contributors see $GANIL2ROOT/README/CREDITS               *
 *****************************************************************************/

/*****************************************************************************
 * Original Author: L. Lefebvre  contact address: lefebvrl@ipno.in2p3.fr     *
 *                                                                           *
 *                                                                           *
 * Creation Date  : June 2011                                                *
 * Last update    :                                                          *
 *---------------------------------------------------------------------------*
 * Decription: This class is in charged of converting raw data from GANIL    *
 *             format to a ROOT format for the SPEG drift chamber detector   *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Comment:                                                                  *
 *                                                                           *
 *****************************************************************************/
#ifndef __SPEGDC__
#define __SPEGDC__

#ifndef __DETECTOR__
#include "TDetector.h"
#endif

#ifndef __SPEGDCDATA__
#include "TSpegDCData.h"
#endif

#include "DataParameters.h"
#include "TTree.h"


#define DC_Strip11	1
#define DC_Strip12	2
#define DC_Strip21	3
#define DC_Strip22	4
#define DC_efil11	5
#define DC_efil12	6
#define DC_efil21	7
#define DC_efil22	8
#define DC_tplfil11	9
#define DC_tplfil12	10
#define DC_tplfil21	11
#define DC_tplfil22	12
#define DC_TEMPS11	13
#define DC_TEMPS12	14
#define DC_TEMPS21	15
#define DC_TEMPS22	16

class TSpegDC : public TDetector {
  public:
   TSpegDC();
   virtual ~TSpegDC();

   // virtual methods from TDetector
   virtual bool Init(DataParameters*);
   virtual bool Clear();
   virtual bool Is(UShort_t, Short_t);
   virtual bool Treat();
   virtual void InitBranch(TTree*);

   void Clear(const Option_t*) {};

   // getters and setters
   TSpegDCData*	GetSpegDCData() const {return fSpegDCData;}

  private:
   // Data class for Must2
   TSpegDCData  *fSpegDCData;

   ClassDef(TSpegDC,1)  // SpegDC detector structure
};

#endif
