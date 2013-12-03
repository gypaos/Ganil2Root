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
 * Decription: This class is in charged of converting raw data from GANIL    *
 *             format to a ROOT format for the Exogam detector               *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Comment:                                                                  *
 *                                                                           *
 *****************************************************************************/
#include "TExogam.h"

#include <string>
#include <cstdlib>
using namespace std;


ClassImp(TExogam)

TExogam::TExogam()
{
   // Default constructor
   fExogamData    = new TExogamData();
}



TExogam::~TExogam()
{
   delete fExogamData;
}



bool TExogam::Clear()
{
   fExogamData->Clear();

   return true;
}



bool TExogam::Init(GDataParameters *params)
{
   Int_t channum, segnum;
   Int_t Xtalnum = -1;
   string crystal, sigtype;

   bool status = false;

   Int_t nbParams = params->GetNbParameters();
   for (Int_t index = 0; index < nbParams; index++) {
      Int_t lbl      = params->GetLabel(index);
      string label   = params->GetParName(index);
       
      // Inner contacts
      if (label.compare(0,3,"ECC") == 0) {
         fLabelMap[lbl] = label;
	 status = true;

         // clover number
         channum = atoi(label.substr(3,label.find_first_of("_")).c_str());
	 // crystal name
	 crystal = label.substr(label.find_first_of("_")+1,1);

         // crystal number
         if (crystal == "A")      Xtalnum = 0;
	 else if (crystal == "B") Xtalnum = 1;
	 else if (crystal == "C") Xtalnum = 2;
	 else if (crystal == "D") Xtalnum = 3;
	 if (Xtalnum < 0) cout << "TExogam::Init() : problem with ECC/Xtalnum" << endl;

         // signal type (Energy or Time)
         if (label.find_last_of("_") != string::npos) 
	    sigtype = label.substr(label.find_last_of("_")+1);
	 else sigtype = "";

         if (sigtype == "6MEV") {
	    fTypeMap[lbl] = ECCE;
	    fParameterMap[lbl] = channum*4 + Xtalnum;
	 }
	 else if (sigtype == "TAC") {
	    fTypeMap[lbl] = ECCT;
	    fParameterMap[lbl] = channum*4 + Xtalnum;
//            cout << label << " " << fTypeMap[lbl] << "  " << fParameterMap[lbl] << endl;
	 }
	 else {
	   cout << "TExogam::Init() : problem reading EXOGAM/ECC label" << endl;
	    status = false;
	 }
      }

      // Segments
      if (label.compare(0,5,"GOCCE") == 0) {  
	 fLabelMap[lbl] = label;
	 status =true;

         // clover number
         channum = atoi(label.substr(5,label.find_first_of("_")).c_str());
	 // crystal name
	 crystal = label.substr(label.find_first_of("_")+1,1);

         // crystal number
         if (crystal == "A")      Xtalnum = 0;
	 else if (crystal == "B") Xtalnum = 1;
	 else if (crystal == "C") Xtalnum = 2;
	 else if (crystal == "D") Xtalnum = 3;
	 if (Xtalnum < 0) cout << "TExogam::Init() : problem with GOCCE/Xtalnum" << endl;

         // segment number
         segnum = atoi(label.substr(label.find_first_of("_")+3,1).c_str());

//         cout << label << endl;
//         cout << "clo " << channum << " cris " << Xtalnum << " seg " << segnum << endl;

         // signal type (Energy or Time)
         if (label.find_last_of("_") != string::npos) 
	    sigtype = label.substr(label.find_last_of("_")+1);
	 else sigtype = "";

         if (sigtype == "E") {
	    fTypeMap[lbl] = GOCCEE;
	    fParameterMap[lbl] = channum*16 + Xtalnum*4 + segnum;
	 }
	 else if (sigtype == "T") {	// never used in E530 exp.
	    fTypeMap[lbl] = GOCCET;
	    fParameterMap[lbl] = channum*16 + Xtalnum*4 + segnum;
	 }
	 else {
	    cout << "TExogam::Init() : problem reading EXOGAM/GOCCE label" << endl;
	    status = false;
	 }
      }

      // TTL signal when Ge filling is occuring
      if (label.compare(0,7,"GE_FILL") == 0) {
	 fLabelMap[lbl] = label;
	 status =true;
	 fTypeMap[lbl] = GEFILL;
      }
   }
   
   return status;
}



bool TExogam::Is(UShort_t lbl, Short_t val)
{
   Int_t clo, cri, seg;

   bool result = false;

   switch (fTypeMap[lbl]) {
     case ECCE : {  
//       cout<<  "- ---------< EXOGAM/ECC E >------------------!\n";
       clo = (Int_t) fParameterMap[lbl] / 4;
       cri = (Int_t) (fParameterMap[lbl]- clo*4) % 4;
       fExogamData->SetECCEClover(clo);
       fExogamData->SetECCECristal(cri);
       fExogamData->SetECCEEnergy(val);
       result = true;
       break;
     }
    
     case ECCT : {
//       cout<<  " ----------< EXOGAM/ECC T >------------------!\n"; 
       clo = (Int_t) fParameterMap[lbl] / 4;
       cri = (Int_t) (fParameterMap[lbl]- clo*4) % 4;
//       cout << clo << "  " << cri << endl;
       fExogamData->SetECCTClover(clo);
       fExogamData->SetECCTCristal(cri);
       fExogamData->SetECCTTime(val);
       result = true;;
       break;
     }

     case GOCCEE : {  
       //cout<<  "- ---------< EXOGAM/GOCCE E >------------------!\n";
       clo = (Int_t) fParameterMap[lbl]/16;
       cri = (Int_t) (fParameterMap[lbl]- clo*16) / 4;
       seg = (Int_t) (fParameterMap[lbl]- clo*16) % 4;
       fExogamData->SetGOCCEEClover(clo);
       fExogamData->SetGOCCEECristal(cri);
       fExogamData->SetGOCCEESegment(seg);
       fExogamData->SetGOCCEEEnergy(val);
       result = true;
       break;
     }
    
     case GOCCET : {	// never used in E530 exp.
       //cout<<  " ----------< EXOGAM/GOCCE T >------------------!\n"; 
       clo = (Int_t) fParameterMap[lbl] / 16;
       cri = (Int_t) (fParameterMap[lbl]- clo*16) / 4;
       seg = (Int_t) (fParameterMap[lbl]- clo*16) % 4;
       fExogamData->SetGOCCETClover(clo);
       fExogamData->SetGOCCETCristal(cri);
       fExogamData->SetGOCCETSegment(seg);
       fExogamData->SetGOCCETTime(val);
       result = true;;
       break;
     }

     case GEFILL : {	
       //cout<<  " ----------< EXOGAM/GEFILL  >------------------!\n"; 
       //cout<<"Exo--> "<<fTypeMap[lbl]<<" "<<val<<" | "<<fLabelMap[lbl]<<endl;
       fExogamData->SetGeFill(val);
       result = true;;
       break;
     }

     default : {
       result = false;
       break;
     }
   }

   return result;
}



bool TExogam::Treat()
{
   return true;
}



void TExogam::InitBranch(TTree *tree)
{
   tree->Branch("EXOGAM", "TExogamData", &fExogamData);
}

