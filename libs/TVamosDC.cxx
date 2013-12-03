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
 *             format to a ROOT format for the Vamos drift chamber detector  *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Comment:                                                                  *
 *                                                                           *
 *****************************************************************************/
#include "TVamosDC.h"

#include <string>
#include <cstdlib>
using namespace std;


ClassImp(TVamosDC)

TVamosDC::TVamosDC()
{
   // Default constructor
   fVamosDCData    = new TVamosDCData();
}



TVamosDC::~TVamosDC()
{
   delete fVamosDCData;
}



bool TVamosDC::Clear()
{
   fVamosDCData->Clear();

   return true;
}



bool TVamosDC::Init(GDataParameters *params)
{
   Int_t channum;
   Int_t nbParams = params->GetNbParameters();
   bool status = false;

   for (Int_t index = 0; index < nbParams; index++) {
       Int_t lbl    = params->GetLabel(index);
       string label = params->GetParName(index);
       //      cout << index << "  " << lbl << "  " << label << "  " << fLabelMap[lbl] << endl;
       
       if (label.compare(0,3,"STR") == 0 ) { 
	 fLabelMap[lbl] = label;
	 status = true;

	 if (label.compare(5,1,"1") == 0 ) {
	     fTypeMap[lbl] = DC_Strip1;
	     channum = atoi(label.substr(7).c_str());
	     fParameterMap[lbl] = channum;                 // VamosDC X signals 1-28
	       //	    cout << fTypeMap[lbl] << "  " << fParameterMap[lbl] << endl;
	  } 
	  else if (label.compare(5,1,"2") == 0 ) {
	     fTypeMap[lbl] = DC_Strip2;
	     channum = atoi(label.substr(7).c_str());
	     fParameterMap[lbl] = channum;                 // VamosDC Y signals 1-28
	       //	    cout << fTypeMap[lbl] << "  " << fParameterMap[lbl] << endl;
	  }
	  else {
	    cout << "TVamosDC::Init() : problem reading VamosDC label -> " << label << endl;
	     status = false;
	  }
       }
       else if(label.compare(0,4,"EFIL") == 0 ) {
          if (label.compare(6,6,"PILEUP") == 0) {
             fTypeMap[lbl]  = DC_E_PU;
             fLabelMap[lbl] = label;
             status = true;
          }
          else if (label.compare(4,1,"_") == 0) {
	     fTypeMap[lbl] = DC_E;
	     fLabelMap[lbl] = label;
	     status = true;
          }
       } 
       else if(label.compare(0,5,"TFIL_") == 0 ) {
	 fTypeMap[lbl] = DC_T;
	 fLabelMap[lbl] = label;
	 status = true;
       } 
   }   
   
   return status;
}



bool TVamosDC::Is(UShort_t lbl, Short_t val)
{
   Int_t det;
   bool result = false;

  switch (fTypeMap[lbl]) {
    
    case DC_Strip1 :{  
      //cout<<  "- ---------< VamosDC Strip 1 >------------------!\n";
      det = atoi(fLabelMap[lbl].substr(4,1).c_str());
      fVamosDCData->SetVamosDCDetNbr1(det);
      fVamosDCData->SetVamosDCStripNbr1(fParameterMap[lbl]);
      fVamosDCData->SetVamosDCEnergy1(val);
      result = true;
      break;
    }
    
    case DC_Strip2 :{  
      //cout<<  "- ---------< VamosDC Strip 2 >------------------!\n";
      det = atoi(fLabelMap[lbl].substr(4,1).c_str());
      fVamosDCData->SetVamosDCDetNbr2(det);
      fVamosDCData->SetVamosDCStripNbr2(fParameterMap[lbl]);
      fVamosDCData->SetVamosDCEnergy2(val);
      result = true;
      break;
    }
    
    case DC_E :{  
      //cout<<  "- ---------<  VamosDC Q >------------------!\n";
      det = atoi(fLabelMap[lbl].substr(5,1).c_str());
      fVamosDCData->SetVamosDCEfilDetNbr(det);
      fVamosDCData->SetVamosDCEfilEnergy(val);
      result = true;
      break;
    }

    case DC_E_PU :{  
      //cout<<  "- ---------<  VamosDC Q PileUp >------------------!\n";
      det = atoi(fLabelMap[lbl].substr(4,1).c_str());
      fVamosDCData->SetVamosDCEfilPileUpDetNbr(det);
      fVamosDCData->SetVamosDCEfilPileUpEnergy(val);
      result = true;
      break;
    }

    case DC_T :{  
      //cout<<  "- ---------<  VamosDC Q >------------------!\n";
      det = atoi(fLabelMap[lbl].substr(5,1).c_str());
      fVamosDCData->SetVamosDCTfilDetNbr(det);
      fVamosDCData->SetVamosDCTfilTime(val);
      result = true;
      break;
    }

    default: {
      //cout<<"TVamosDC::Is --> not a good label"<<lbl<<" "<<fTypeMap[lbl]<<" "<<fLabelMap[lbl]<<endl;
      result = false;
      break;
    }
    
  } // end of switch

  return result;
}



bool TVamosDC::Treat()
{
   return true;
}




void TVamosDC::InitBranch(TTree *tree)
{
   tree->Branch("VAMOS_DC", "TVamosDCData", &fVamosDCData);
}

