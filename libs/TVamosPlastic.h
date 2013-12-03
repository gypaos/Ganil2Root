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
 *             format to a ROOT format for the Vamos plastic                 *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Comment:                                                                  *
 *                                                                           *
 *****************************************************************************/
#ifndef __VAMOSPLASTIC__
#define __VAMOSPLASTIC__

#ifndef __DETECTOR__
#include "TDetector.h"
#endif

#ifndef __VAMOSPLASTICDATA__
#include "TVamosPlasticData.h"
#endif

#include "GDataParameters.h"
#include "TTree.h"


#define	PL_G		1
#define	PL_D		2
#define TPLG_PLD	3



class TVamosPlastic : public TDetector {
  public:
   TVamosPlastic();
   virtual ~TVamosPlastic();

   // virtual methods from TDetector
   virtual bool Init(GDataParameters*);
   virtual bool Clear();
   virtual bool Is(UShort_t, Short_t);
   virtual bool Treat();
   virtual void InitBranch(TTree*);

   void Clear(const Option_t*) {};

   // getters and setters
   TVamosPlasticData*	GetVamosPlasticData() const {return fVamosPlasticData;}

  private:
   // Data class for Plastic
   TVamosPlasticData  *fVamosPlasticData;

   ClassDef(TVamosPlastic,1)  // Plastic detector structure
};

#endif
