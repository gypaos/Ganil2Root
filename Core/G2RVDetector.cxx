/*****************************************************************************
 * Copyright (C) 2008-2017   this file is part of the Ganil2Root Project     *
 *                                                                           *
 * For the licensing terms see $GANIL2ROOT/Licence                           *
 * For the list of contributors see $GANIL2ROOT/README/CREDITS               *
 *****************************************************************************/

/*****************************************************************************
 * Original Author: A. Matta  contact address: matta@lpccaen.in2p3.fr        *
 *                                                                           *
 * Creation Date  : April 2015                                               *
 * Last update    :                                                          *
 *---------------------------------------------------------------------------*
 * Decription: Abstract Base Class for all detectors                         *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Comment:                                                                  *
 *                                                                           *
 *****************************************************************************/
#include "G2RVDetector.h"

#include <iostream>
using namespace std;


ClassImp(G2R::VDetector)
////////////////////////////////////////////////////////////////////////////////
G2R::VDetector::VDetector(){
   // Default constructor
   fLabelMap.clear();
   fTypeMap.clear();
   fParameterMap.clear();	 
   m_Data=NULL;
}
////////////////////////////////////////////////////////////////////////////////
G2R::VDetector::~VDetector(){
}
////////////////////////////////////////////////////////////////////////////////
void G2R::VDetector::DumpLabelMap(){
   map<int, string>::iterator it;
   for (it=fLabelMap.begin(); it!=fLabelMap.end(); ++it){
      cout << it->first << "  => " << it->second << endl;
   }
}
