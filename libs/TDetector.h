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
 *   + The absolute path for GDataParameters.h should be given explicitely   *
 *     (this should be changed in the future)                                *
 *                                                                           *
 *****************************************************************************/
#ifndef __DETECTOR__
#define __DETECTOR__

// GRU headers
#include "GDataParameters.h"

// ROOT headers
#include "TObject.h"
#include "TTree.h"

// C++ headers
#include <string>
#include <map>
using namespace std;


class TDetector : public TObject 
{
 public:
	TDetector();
	virtual ~TDetector();

	virtual bool Init(GDataParameters*)        = 0;
	virtual bool Clear()                       = 0;
  	virtual bool Is(UShort_t, Short_t)         = 0; 
	virtual bool Treat()                       = 0;
	virtual void InitBranch(TTree*)            = 0;

   void Clear(const Option_t*) {};

 public:
	string GetLabelMap(int i)	{return fLabelMap[i];}
   void   DumpLabelMap();

 protected:
	map<int, string> fLabelMap;
	map<int, int>	  fTypeMap;
	map<int, int>	  fParameterMap;

	ClassDef(TDetector,1)  // Detector abstract class
};

#endif
