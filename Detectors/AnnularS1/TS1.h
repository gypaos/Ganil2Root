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
 *             format to a ROOT format for the S1 detector                   *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Comment:                                                                  *
 *   + WARNING: the label names are the one corresponding to MM5 (exp. e530) *
 *              This should be changed.                                      * 
 *                                                                           *
 *****************************************************************************/
#ifndef __S1__
#define __S1__

#ifndef __DETECTOR__
#include "TDetector.h"
#endif

#ifndef __RINGDATA__
#include "TS1Data.h"
#endif

#include "DataParameters.h"
#include "TTree.h"


#define	S1_ThE	1
#define	S1_ThT	2
#define	S1_PhE	3
#define	S1_PhT	4


class TS1 : public TDetector {
  public:
   TS1();
   virtual ~TS1();

   // virtual methods from TDetector
   virtual bool Init(DataParameters*);
   virtual bool Clear();
   virtual bool Is(unsigned short, unsigned short);
   virtual bool Treat();
   virtual void InitBranch(TTree*);

   void Clear(const Option_t*) {};

   // getters and setters
   TS1Data*	GetS1Data() const {return fS1Data;}

  private:
   // Data class for S1
   TS1Data  *fS1Data;

   // internal maps to map the MM5 naming convention of DAS with the strip
   // numbering of the S1 detector
   // This is specific to exp. e530 and should be useless for other exp.
   map<int,int> real_channelTh;
   map<int,int> real_channelPh;

   ClassDef(TS1,1)  // S1 detector structure
};

#endif
