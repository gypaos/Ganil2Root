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
 * Last update    : March 2011                                               *
 *---------------------------------------------------------------------------*
 * Decription: This class is in charged of converting raw data from GANIL    *
 *             format to a ROOT format for the Must2 detector                *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Comment:                                                                  *
 *    + march 2011: Add support for TMust2Physics from NPTool                *
 *                                                                           *
 *****************************************************************************/
#ifndef G2RMUST2
#define G2RMUST2

#ifndef __DETECTOR__
#include "G2RVDetector.h"
#endif

#ifndef __MUST2DATA__
#include "TMust2Data.h"
#endif

#include "DataParameters.h"
#include "TTree.h"

#define MUST2STR_XE	1
#define MUST2STR_XT	2
#define MUST2STR_YE	3
#define MUST2STR_YT	4
#define MUST2SILI_E	5
#define MUST2SILI_T	6
#define MUST2CSI_E	7
#define MUST2CSI_T	8
namespace G2R{
  class Must2 : public G2R::VDetector {
    public:
      Must2();
      virtual ~Must2();

      // virtual methods from TDetector
      virtual bool Init(DataParameters*);
      virtual bool Clear();
      virtual bool Is(unsigned short, unsigned short);
      virtual bool Treat();
      virtual void InitBranch(TTree*);

      void Clear(const Option_t*) {};

      // getters and setters
      TMust2Data*	GetMust2Data() const {return fMust2Data;}

    private:
      // Data class for Must2
      TMust2Data  *fMust2Data;

    public: // Static constructor to be passed to the Detector Factory
      static G2R::VDetector* Construct();

      ClassDef(G2R::Must2,2)  // MUST2 detector structure
  };
}
#endif
