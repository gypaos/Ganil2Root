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
 * Last update    : Dec 2013                                                 *
 *---------------------------------------------------------------------------*
 * Decription: This class is in charged of converting raw data from GANIL    *
 *             format to a ROOT format for the Cats detector                 *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Comment:                                                                  *
 *    + march 2011: Add support for TCATSPhysics from NPTool                 *
 *    + decem 2013: Remove support for TCATSPhysics from NPTool              *
 *                                                                           *
 *****************************************************************************/
#ifndef G2RCATS_H
#define G2RCATS_H

#ifndef __DETECTOR__
#include "G2RVDetector.h"
#endif

#ifndef __CATSDATA__
#include "TCATSData.h"
#endif

//  #include "TCATSData.h"
#include "DataParameters.h"
#include "TTree.h"

#define CATS_X		1
#define CATS_Y		2
#define CATS_Q		3
namespace G2R{
  class CATS : public G2R::VDetector 
  {
    public:
      CATS();
      virtual ~CATS();
      // virtual methods from TDetector
      virtual bool Init(DataParameters*);
      virtual bool Clear();
      virtual bool Is(unsigned short, unsigned short);
      virtual bool Treat();
      virtual void InitBranch(TTree*);

      void Clear(const Option_t*) {};

      // getters and setters
      TCATSData*     GetCATSData()     const {return fCATSData;}

    private:
      // Data class for TCATSData
      TCATSData    *fCATSData;

    public: // Static constructor to be passed to the Detector Factory 
      static G2R::VDetector* Construct();

      ClassDef(G2R::CATS,2)  // CATS detector structure
  };
}
#endif
