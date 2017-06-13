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
 *             format to a ROOT format for the Exogam detector               *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Comment:                                                                  *
 *                                                                           *
 *****************************************************************************/
#ifndef __EXOGAM__
#define __EXOGAM__

#ifndef __DETECTOR__
#include "TDetector.h"
#endif

#ifndef __EXOGAMDATA__
#include "TExogamData.h"
#endif

#include "DataParameters.h"
#include "TTree.h"


#define ECCE	1
#define ECCT	2
#define GOCCEE	3
#define GOCCET	4
#define GEFILL 5


class TExogam : public TDetector {
  public:
   TExogam();
   virtual ~TExogam();

   // virtual methods from TDetector
   virtual bool Init(DataParameters*);
   virtual bool Clear();
   virtual bool Is(UShort_t, Short_t);
   virtual bool Treat();
   virtual void InitBranch(TTree*);

   void Clear(const Option_t*) {};

   // getters and setters
   TExogamData*	GetExogamData() const {return fExogamData;}

  private:
   // Data class for Exogam
   TExogamData  *fExogamData;

   ClassDef(TExogam,1)  // Exogam detector structure
};

#endif
