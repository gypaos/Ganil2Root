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
 *             format to a ROOT format for the Speg plastic                 *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Comment:                                                                  *
 *                                                                           *
 *****************************************************************************/
#ifndef __SPEGPLASTIC__
#define __SPEGPLASTIC__

#ifndef __DETECTOR__
#include "TDetector.h"
#endif

#ifndef __SPEGPLASTICDATA__
#include "TSpegPlasticData.h"
#endif

#include "GDataParameters.h"
#include "TTree.h"


#define	EPLD		1
#define	EPLG		2
#define	TPLD		3
#define	TPLG		4



class TSpegPlastic : public TDetector {
  public:
   TSpegPlastic();
   virtual ~TSpegPlastic();

   // virtual methods from TDetector
   virtual bool Init(GDataParameters*);
   virtual bool Clear();
   virtual bool Is(UShort_t, Short_t);
   virtual bool Treat();
   virtual void InitBranch(TTree*);

   void Clear(const Option_t*) {};

   // getters and setters
   TSpegPlasticData*	GetSpegPlasticData() const {return fSpegPlasticData;}

  private:
   // Data class for Plastic
   TSpegPlasticData  *fSpegPlasticData;

   ClassDef(TSpegPlastic,1)  // Plastic detector structure
};

#endif
