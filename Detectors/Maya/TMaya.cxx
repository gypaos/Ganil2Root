/*****************************************************************************
 * Copyright (C) 2008   this file is part of the Ganil2Root Project          *
 *                                                                           *
 * For the licensing terms see $GANIL2ROOT/Licence                           *
 * For the list of contributors see $GANIL2ROOT/README/CREDITS               *
 *****************************************************************************/

/*****************************************************************************
 * Original Author: M. Vandebrouck   contact address: vandebro@ipno.in2p3.fr *
 *                  J. Gibelin                      gibelin@lpccaen.in2p3.fr *
 *                                                                           *
 * Creation Date  : November 2011                                            *
 * Last update    :                                                          *
 *---------------------------------------------------------------------------*
 * Decription: This class is in charged of converting raw data from GANIL    *
 *             format to a ROOT format for the Maya detector                 *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Comment:                                                                  *
 *                                                                           *
 *****************************************************************************/
#include <cstdlib>

#include "TMaya.h"


ClassImp(TMaya)

TMaya::TMaya()
{
   // Default constructor
   fMayaData    = new TMayaData();
}



TMaya::~TMaya()  
{
   delete fMayaData;
}



bool TMaya::Clear()
{
   fMayaData->Clear();
   return true;
}



bool TMaya::Init(DataParameters *params)
{
   bool status = false;

   Int_t nbParams = params->GetNbParameters();

   cout << "nbParams =" << nbParams << endl;

   for (Int_t index = 0; index < nbParams; index++) {
      Int_t lbl    = params->GetLabel(index);
      //     cout << "## " << index << "  " << lbl << endl;
      //Int_t lbl2   = params->GetLabel(index);
      //cout << "## " << index << "  " << lbl2 << endl;
      string label = params->GetParNameFromIndex(index);
      //      cout << "## " << index << "  " << lbl << "  " << label  << endl;
      Int_t channum = -1 ;
       
      if (label.compare(0,5,"EFIL_") == 0) {  
	 fLabelMap[lbl] = label;
	 status = true;
	 fTypeMap[lbl] = MAYA_QFIL_E;
	 channum = atoi(label.substr(5).c_str()) ;
	 fParameterMap[lbl] = channum ;
      } 

      if (label.compare(0,5,"TFIL_") == 0) {  
	 fLabelMap[lbl] = label;
	 status = true;
	 fTypeMap[lbl] = MAYA_QFIL_T;
	 channum = atoi(label.substr(5).c_str()) ;
	 fParameterMap[lbl] = channum ;
      } 

      if (label.compare(0,3,"SI_") == 0 ||
	  label.compare(0,3,"Si_") == 0) {  
	fLabelMap[lbl] = label;
	status = true;
	fTypeMap[lbl] = MAYA_SI_E;
	channum = atoi(label.substr(3).c_str()) ;
	fParameterMap[lbl] = channum ;
      } 

      if (label.compare(0,4,"TSI_") == 0) {  
	fLabelMap[lbl] = label;
	status = true;
	fTypeMap[lbl] = MAYA_SI_T;
	channum = atoi(label.substr(4).c_str()) ;
	fParameterMap[lbl] = channum ;
      } 

      if (label.compare(0,4,"PAD_") == 0 ) { 

	fLabelMap[lbl] = label;
	Int_t r = atoi(label.substr(4,2).c_str()) ;
	Int_t c = atoi(label.substr(7).c_str()) ;
	
	channum =  fMayaData->GetPadIdx(c,r);
	fParameterMap[lbl] =  channum ;

	if((r>=5 && r<=8)||(r>=13 && r<=16)||(r>=29 && r<=32)){
	  fTypeMap[lbl] = MAYA_PAD_E_CORR; // CRAMS w/ 11 et 12th bits swaped
	} else {
	  fTypeMap[lbl] = MAYA_PAD_E; // normal CRAMS
	}
	//	 cout << "## " << label << " " << c 
	//	<< " " << r << " ->" << channum << endl ;
      }

      if (label.compare(0,10,"FADC_VOIE_") == 0 ) { // Flash ADC
	fLabelMap[lbl] = label;
	Int_t ch = atoi(label.substr(10,1).c_str()) ;
	fParameterMap[lbl] =  ch ;
	fTypeMap[lbl] = MAYA_FADC ;
      }

      if ((label.compare(0,11,"TAC_TGAL_HF") == 0) || 
	  (label.compare(0,7,"TX2_PCD")==0)) { // TAC
	cout << label << endl ;
	fLabelMap[lbl] = label ;
	fParameterMap[lbl] =  1 ;
	fTypeMap[lbl] = MAYA_TOF ;
      }
      
      if (label.compare(0,13,"TAC_TDIAM_GAL") == 0){ // TAC
	cout << label << endl ;
	fLabelMap[lbl] = label ;
	fParameterMap[lbl] =  2 ;
	fTypeMap[lbl] = MAYA_TOF ;
      }
      
      if (label.compare(0,11,"TAC_TM_TRIG") == 0){ // TAC
	cout << label << endl ;
	fLabelMap[lbl] = label ;
	fParameterMap[lbl] =  3 ;
	fTypeMap[lbl] = MAYA_TOF ;
      }
   }

   return status;
} 



bool TMaya::Is(UShort_t lbl,Short_t val)
{
   bool status = false;

   switch (fTypeMap[lbl]) {

   case MAYA_PAD_E :{  
     //  cout <<  "- ---------< Maya PAD E >------------------!\n";

     //cout << fParameterMap[lbl] << " " << val << endl ;

     fMayaData->SetEnergyPad(fParameterMap[lbl],(UShort_t)val);

     fMayaData->SetPADSum((UShort_t)val);
     status = true; 
     break;
   }

   case MAYA_PAD_E_CORR :{  
     //cout<<  "- ---------< Maya PAD E w/ 11,12 bits inversion>------------------!\n";
      
     UShort_t tmpval = val & 5119 ; // remove bits 12 and 11 (2048 and 1024) : 5119 = (1001111111111)
     tmpval = tmpval + (2*(val & 1024)) + ((val & 2048)/2) ; // swap 1024 and 2048 values
     fMayaData->SetEnergyPad(fParameterMap[lbl],(UShort_t)tmpval);
     fMayaData->SetPADSum((UShort_t)tmpval);
     status = true; 
     break;
   }
     
   case MAYA_QFIL_E :{
     //cout<<  "- ---------< Maya QFIL E >------------------!\n";
     fMayaData->SetQfil(fParameterMap[lbl],(UShort_t)val);
     status = true; 
     break;
   }

   case MAYA_QFIL_T :{
     //cout<<  "- ---------< Maya QFIL E >------------------!\n";
     fMayaData->SetTfil(fParameterMap[lbl],(UShort_t)val);
     status = true; 
     break;
   }

   case MAYA_SI_E :{
     //cout<<  "- ---------< Maya SI E >------------------!\n";
     fMayaData->SetEnergySi(fParameterMap[lbl],(UShort_t)val);
     status = true; 
     break;
   }

   case MAYA_SI_T :{
     //cout<<  "- ---------< Maya SI T >------------------!\n";
     fMayaData->SetTimeSi(fParameterMap[lbl],(UShort_t)val);
     status = true; 
     break;
   }

   case MAYA_FADC :{
     //     cout<<  "- ---------< Maya FADC >------------------!\n";
     fMayaData->SetQFilPulse(fParameterMap[lbl],(UShort_t)val);
     status = true; 
     break;
   }
 
   case MAYA_TOF :{
     //     cout<<  "- ---------< Maya TOF >------------------!\n";
     fMayaData->SetTOF(fParameterMap[lbl],(UShort_t)val);
     status = true; 
     break;
   }
  
   case 0 :{
     // empty label ??
     //cout<<"TMaya::Is " << fLabelMap[lbl] << " " << fTypeMap[lbl] << "--> is an empty label"<<endl;
     status = false;
     break ;
   }

   default:{
     //cout<<"TMaya::Is " << fLabelMap[lbl] << " " << fTypeMap[lbl] << "--> not a good label"<<endl;
     status = false;
   }
   } // end of switch
   
   return status; 
}



bool TMaya::Treat()
{
  // fMayaData->Dump();
 return true;
}

bool TMaya::InitCalibrate( std::vector<string> &l){
  if(l.size()>0)  return fMayaData->InitCalibrate(l);
  return kFALSE ;
}

bool TMaya::Calibrate()
{
  return fMayaData->Calibrate();
}


void TMaya::InitBranch(TTree *tree)
{
  tree->Branch("MAYA", "TMayaData", &fMayaData);
}
