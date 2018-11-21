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
#include "G2RModularLabel.h"

#include <iostream>
#include <fstream>
using namespace std;
#include "TH1S.h"

////////////////////////////////////////////////////
ClassImp(G2R::ModularLabel)
  ////////////////////////////////////////////////////
  G2R::ModularLabel::ModularLabel(){
    // Default constructor
    fModularLeafPhysics =NULL;
  }
////////////////////////////////////////////////////
G2R::ModularLabel::~ModularLabel(){
}
////////////////////////////////////////////////////
bool G2R::ModularLabel::Clear(){
  map<UShort_t,Short_t>::iterator it;

  // Loop over the map and set all value to -1000
  for(it = fMapOfLabelValue.begin() ; it!=fMapOfLabelValue.end() ; it++)
    it->second = -1000;

  fModularLeafPhysics->ClearEventData();
  return true;
}

////////////////////////////////////////////////////
void G2R::ModularLabel::LoadLabel(string path){
  fstream file(path.c_str());

  if(!file.is_open()){
    cout << "ERROR : The requested list of Modular Label " << path << " can not be found " << endl ; 
    exit(1);
  } 
   
  string DataBuffer;
  while(file>>DataBuffer){
    fRequestedLabel.insert(DataBuffer);
  }

  return;
}

////////////////////////////////////////////////////
bool G2R::ModularLabel::Init(DataParameters *params){
  if(fRequestedLabel.size()==0){
    cout << "WARNING : List of Modular label is empty" << endl; 
  }

  Int_t channum;
  Int_t nbParams = params->GetNbParameters();
  bool status = false;
  for (Int_t index = 0; index < nbParams; index++) {
    Int_t lbl      = params->GetLabel(index);
    string label   = params->GetParNameFromIndex(index);
    // Check if label is in the list of Requested Label
    if(fRequestedLabel.find(label)!=fRequestedLabel.end()){
      fFollowedLabel[label]=lbl;
      fMapOfLabelValue[lbl]=-1000;
     /* string FamilyName = "ModularLabel/"+label;
      TH1S* h = new TH1S(label.c_str(),label.c_str(),16536,0,16536); 
      fSpectra[FamilyName] = h;
      fSpectraByLbl[lbl] = h;*/
    }
  }
  
  if(fFollowedLabel.size()!=fRequestedLabel.size()){
    cout << endl << "ERROR : Requested labels in ModularLabel.txt : "  ;
    std::set<string>::iterator itR;
    for( itR = fRequestedLabel.begin() ; itR!= fRequestedLabel.end() ; itR++){
        if(fFollowedLabel.find(*itR)==fFollowedLabel.end())
            cout << *itR << " , " ;
    }
    cout << " are missing in action file" << endl << endl;
    exit(-1);
  }

  return status;
}
////////////////////////////////////////////////////
bool G2R::ModularLabel::Is(unsigned short lbl, unsigned short val){
  bool result = false;

  // Find lbl in the map
  if(fMapOfLabelValue.find(lbl)!=fMapOfLabelValue.end()){
    fMapOfLabelValue[lbl] = val;
    //fSpectraByLbl[lbl]->Fill(val);
    result=true;
  }

  return result;
}

////////////////////////////////////////////////////
bool G2R::ModularLabel::Treat(){

  map<string,UShort_t>::iterator it; 
  for(it=fFollowedLabel.begin(); it!=fFollowedLabel.end(); it++){
      string label = it->first;
      fModularLeafPhysics->SetModularData(label, GetValue(label));
    }

  return true;
}

////////////////////////////////////////////////////
void G2R::ModularLabel::InitBranch(TTree *tree){
  map<string,UShort_t>::iterator it; 
  // Sync loop over set and map
  for(it=fFollowedLabel.begin(); it!=fFollowedLabel.end(); it++){
    string BranchName = it->first;
    string VariableName = BranchName+"/S";
    tree->Branch(BranchName.c_str(), &fMapOfLabelValue[it->second]);
  }
}

////////////////////////////////////////////////////
Short_t G2R::ModularLabel::GetValue(string label){
    // Sync loop over set and map
    if(fFollowedLabel.find(label) != fFollowedLabel.end())
        return fMapOfLabelValue[fFollowedLabel[label]];
    else
    {
        cout << "Could not find Label " << label << " in G2R::ModularLabel::GetValue(string label) " << endl;
        return -2000;
    }
}

