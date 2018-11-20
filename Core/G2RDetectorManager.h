#ifndef G2RDETECTORMANAGER
#define G2RDETECTORMANAGER
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
 * Decription: Abstract Base Class for all detectors                         *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Comment:                                                                  *
 *   + This class holds the maps which are used in the daughter classes      *
 *   + The absolute path for DataParameters.h should be given explicitely   *
 *     (this should be changed in the future)                                *
 *                                                                           *
 *****************************************************************************/
// STL
#include <map>
#include <string>
using namespace std;

// ROOT
#include "TTree.h"
#include "TH1S.h"
// GANIL2ROOT
#include "G2RVDetector.h"
#include "G2RModularLabel.h"

//GRU
#include "DataParameters.h"

// nptool
#include "NPDetectorManager.h"
#include "TModularLeafPhysics.h"

namespace G2R{
  class DetectorManager{
    public:
      DetectorManager();
      ~DetectorManager();

    private:
      map<string,G2R::VDetector*> fDetectorMap;

    public: // G2R framework

      G2R::ModularLabel* fModularLabel;
      G2R::VDetector* GetDetector(string);
      void AddDetector(string);
      bool Init(DataParameters*);
      bool Clear();
      bool Is(UShort_t,Short_t);
      bool Treat();
      void InitBranch(TTree*);
    
    public: // For nptool compatibility
      void SetRawDataPointer(NPL::DetectorManager*);
      void SetModularLeafPointer(TModularLeafPhysics* ptr){fModularLabel->SetModularLeafPointer(ptr);}; 

    public: // for GRU spectra compatibility
      std::map<std::string,TH1S*> GetModularLabelSpectra(){return fModularLabel->GetSpectra();};
      double GetModularLabelValue(string label){return fModularLabel->GetValue(label);};

      
  };
}
#endif
