/*****************************************************************************
 * Copyright (C) 2008   this file is part of the Ganil2Root Project          *
 *                                                                           *
 * For the licensing terms see $GANIL2ROOT/Licence                           *
 * For the list of contributors see $GANIL2ROOT/README/CREDITS               *
 *****************************************************************************/

/*****************************************************************************
 * Original Author: L. Lefebvre  contact address: lefebvrl@ipno.in2p3.fr     *
 *  Update        : M. Moukaddam                                             *
 *                                                                           *
 * Creation Date  : June 2011                                                *
 * Last update    : June 2017                                                *
 *---------------------------------------------------------------------------*
 * Decription: This class is in charged of converting raw data from GANIL    *
 *             format to a ROOT format for the Exl detector                  *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Comment:                                                                  *
 *                                                                           *
 *                                                                           *
 *****************************************************************************/
#ifndef G2REXL
#define G2REXL

#ifndef __DETECTOR__
#include "G2RVDetector.h"
#endif

#ifndef __EXLDATA__
#include "TExlData.h"
#endif

#include "DataParameters.h"
#include "TTree.h"

#define	EXL_E	1
#define	EXL_T	2

namespace G2R{

  class Exl : public G2R::VDetector {
    public:
 
      Exl();
      virtual ~Exl();

			// virtual methods from TDetector
			virtual bool Init(DataParameters*);
			virtual bool Clear();
			virtual bool Is(UShort_t, Short_t);
			virtual bool Treat();
			virtual void InitBranch(TTree*);

   		void Clear(const Option_t*) {};

			// getters and setters
			TExlData*    GetExlData() const {return fExlData;}
	
 private:
      // Data class for Exl
      TExlData  *fExlData;

 public: // Static constructor to be passed to the Detector Factory
      static G2R::VDetector* Construct();
      ClassDef(G2R::Exl,1)  // Exl detector structure

  };
}
#endif


