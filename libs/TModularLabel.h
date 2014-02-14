/*****************************************************************************
 * Copyright (C) 2014   this file is part of the Ganil2Root Project          *
 *                                                                           *
 * For the licensing terms see $GANIL2ROOT/Licence                           *
 * For the list of contributors see $GANIL2ROOT/README/CREDITS               *
 *****************************************************************************/

/*****************************************************************************
 * Original Author: A.Matta  contact address: a.matta@surrey.ac.uk           *
 *                                                                           *
 * Creation Date  : Feb 2014                                                 *
 * Last update    :                                                          *
 *---------------------------------------------------------------------------*
 * Decription: This class is designed to manage the conversion of dynamicly  *
 * given label to single leaf in the output tree                             *
 *---------------------------------------------------------------------------*
 * Comment:                                                                  *
 *****************************************************************************/
#ifndef __MODULARLABEL__
#define __MODULARLABEL__

// GANIL2ROOT
#include "TDetector.h"

// GRU
#include "GDataParameters.h"

// ROOT 
#include "TTree.h"

// STL
#include <map>
#include <set>
#include <string>
using namespace std;

class TModularLabel : public TDetector {
 public:
	TModularLabel();
	virtual ~TModularLabel();

	// virtual methods from TDetector
	virtual bool Init(GDataParameters*);
	virtual bool Clear();
	virtual bool Is(UShort_t, Short_t);
	virtual bool Treat();
	virtual void InitBranch(TTree*);

  void Clear(const Option_t*) {};

  private:
    // Label ask to be followed by the user
    set<string>           fRequestedLabel;
    // Label found in the list
    set<string>           fFollowedLabel;
    // Map of Numeric label and associate Value
    map<UShort_t,Short_t> fMapOfLabelValue; 
  
  public:
    // Read the user input file to find which label to follow
    void LoadLabel(string path);
    inline map<UShort_t,Short_t>  GetMapOfLabelValue()    {return fMapOfLabelValue;} 
	  inline set<string>            GetFollowedLabel()      {return fFollowedLabel;}
    Short_t GetValue(string label);
  
  ClassDef(TModularLabel,1)  // MUST2 detector structure
};

#endif
