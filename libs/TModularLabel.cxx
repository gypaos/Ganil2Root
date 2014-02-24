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
#include "TModularLabel.h"

#include <iostream>
#include <fstream>
using namespace std;

////////////////////////////////////////////////////
ClassImp(TModularLabel)
  ////////////////////////////////////////////////////
  TModularLabel::TModularLabel(){
    // Default constructor
  }
////////////////////////////////////////////////////
TModularLabel::~TModularLabel(){
}
////////////////////////////////////////////////////
bool TModularLabel::Clear(){
  map<UShort_t,Short_t>::iterator it;

  // Loop over the map and set all value to -1000
  for(it = fMapOfLabelValue.begin() ; it!=fMapOfLabelValue.end() ; it++)
    it->second = -1000;

  return true;
}

////////////////////////////////////////////////////
void TModularLabel::LoadLabel(string path){
  fstream file(path.c_str());

  if(!file.is_open()){
    cout << "ERROR : The requested list of Modular Label " << path << " can not be found " << endl ; 
    exit(1);
  } 

  string DataBuffer;
  while(file>>DataBuffer){
    fRequestedLabel.insert(DataBuffer); 
  }

}

////////////////////////////////////////////////////
bool TModularLabel::Init(GDataParameters *params){
  if(fFollowedLabel.size()==0){
    cout << "WARNING : List of Modular label is empty" << endl; 
  }

  Int_t channum;
  Int_t nbParams = params->GetNbParameters();
  bool status = false;

  for (Int_t index = 0; index < nbParams; index++) {
    Int_t lbl      = params->GetLabel(index);
    string label   = params->GetParName(index);
    // Check if label is in the list of Requested Label
    if(fRequestedLabel.find(label)!=fRequestedLabel.end()){
      fFollowedLabel.insert(label);
      fMapOfLabelValue[lbl]=-1000;
    }
  } 

  if(fFollowedLabel.size()!=fMapOfLabelValue.size()){
    cout << "ERROR : List of followed label differ from the Map of label" << endl ;
    exit(1); 
  }

  return status;
}
////////////////////////////////////////////////////
bool TModularLabel::Is(UShort_t lbl, Short_t val){
  bool result = false;

  // Find lbl in the map
  if(fMapOfLabelValue.find(lbl)!=fMapOfLabelValue.end()){
    fMapOfLabelValue[lbl] = val;
    result=true;
  }
  // if found assigned val to the map entry


  return result;
}

////////////////////////////////////////////////////
bool TModularLabel::Treat(){
  return true;
}

////////////////////////////////////////////////////
void TModularLabel::InitBranch(TTree *tree){
  set<string>::iterator it; 
  map<UShort_t,Short_t>::iterator it2 ;

  // Sync loop over set and map
  for(it=fFollowedLabel.begin(), it2=fMapOfLabelValue.begin(); it!=fFollowedLabel.end() || it2!=fMapOfLabelValue.end(); it++,it2++){
    string BranchName = (*it);
    string VariableName = BranchName+"/S";

    tree->Branch(BranchName.c_str(), &it2->second);
  }
}

////////////////////////////////////////////////////
Short_t TModularLabel::GetValue(string label){
  set<string>::iterator it;
  map<UShort_t,Short_t>::iterator it2 ;

  // Sync loop over set and map
  for(it=fFollowedLabel.begin(), it2=fMapOfLabelValue.begin(); it!=fFollowedLabel.end() || it2!=fMapOfLabelValue.end(); it++,it2++){
    if(*it == label )
      return it2->second;
  }

return -1000;

}

