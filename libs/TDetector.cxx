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
 *                                                                           *
 *****************************************************************************/
#include "TDetector.h"

#include <iostream>
using namespace std;


ClassImp(TDetector)

TDetector::TDetector()
{
   // Default constructor
   fLabelMap.clear();
   fTypeMap.clear();
   fParameterMap.clear();	 
}

TDetector::~TDetector()
{
}

void TDetector::DumpLabelMap()
{
   for (map<int, string>::iterator it=fLabelMap.begin(); it!=fLabelMap.end(); ++it){
      cout << it->first << "  => " << it->second << endl;
   }
}
