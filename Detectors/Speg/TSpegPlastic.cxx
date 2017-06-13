/*****************************************************************************
 * Copyright (C) 2008   this file is part of the Ganil2Root Project          *
 *                                                                           *
 * For the licensing terms see $GANIL2ROOT/Licence                           *
 * For the list of contributors see $GANIL2ROOT/README/CREDITS               *
 *****************************************************************************/

/*****************************************************************************
 * Original Author: L. Lefebvre  contact address: lefebvrl@ipno.in2p3.fr     *
 *                                                                           *
 *                                                                           *
 * Creation Date  : June 2011                                                *
 * Last update    :                                                          *
 *---------------------------------------------------------------------------*
 * Decription: This class is in charged of converting raw data from GANIL    *
 *             format to a ROOT format for the Speg plastic                 *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Comment:                                                                  *
 *                                                                           *
 *****************************************************************************/
#include "TSpegPlastic.h"

#include <string>
#include <cstdlib>
using namespace std;


ClassImp(TSpegPlastic)

TSpegPlastic::TSpegPlastic()
{
   // Default constructor
   fSpegPlasticData    = new TSpegPlasticData();
}



TSpegPlastic::~TSpegPlastic()
{
   delete fSpegPlasticData;
}



bool TSpegPlastic::Clear()
{
   fSpegPlasticData->Clear();

   return true;
}



bool TSpegPlastic::Init(DataParameters *params)
{
   bool status = false;

   Int_t nbParams = params->GetNbParameters();
   for (Int_t index = 0; index < nbParams; index++) {
      Int_t lbl    = params->GetLabel(index);
      string label = params->GetParNameFromIndex(index);
//      cout << index << "  " << lbl << "  " << label <<  endl;
       
      if (label.compare(0,3,"EPL") == 0) {  
	 fLabelMap[lbl] = label;
	 status = true;

	 if (label.compare(3,1,"G") == 0 ) {
//	    cout << fTypeMap[lbl] << endl;
	    fTypeMap[lbl] = EPLG;
	 } 
         else if (label.compare(3,1,"D") == 0) {
            fTypeMap[lbl] = EPLD;
         }
	 else {
	    cout << "TSpegPlastic::Init() : problem reading Plastic's label -> " << label << endl;
	    status = false;
	 }
      }
      else if (label.compare(0,3,"TPL") == 0 && label.compare(0,4,"TPLF") != 0) {
	 fLabelMap[lbl] = label;
	 status = true;

	 if (label.compare(3,1,"G") == 0 ) {
//	    cout << fTypeMap[lbl] << endl;
	    fTypeMap[lbl] = TPLG;
	 } 
         else if (label.compare(3,1,"D") == 0) {
            fTypeMap[lbl] = TPLD;
         }

        else {
	    cout << "TSpegPlastic::Init() : problem reading Plastic's label -> " << label << endl;
	    status = false;
	 }

      }
   }
   
   return status;
}



bool TSpegPlastic::Is(UShort_t lbl, Short_t val)
{
   bool status = false;

   switch (fTypeMap[lbl]) {
     case EPLG :{  
       //cout<<  "- ---------< Plastic E >------------------!\n";
       fSpegPlasticData->SetEnergyLeft(val);
       status = true;
       break;
     }
    
     case EPLD :{  
       //cout<<  "- ---------< Plastic E >------------------!\n";
       fSpegPlasticData->SetEnergyRight(val);
       status = true;
       break;
     }
    
     case TPLG :{  
       //cout<<  "- ---------< Plastic E >------------------!\n";
       fSpegPlasticData->SetTimeLeft(val);
       status = true;
       break;
     }

     case TPLD :{  
       //cout<<  "- ---------< Plastic E >------------------!\n";
       fSpegPlasticData->SetTimeRight(val);
       status = true;
       break;
     }
    
     default:{
      //cout<<"TSpegPlastic::Is --> not a good label"<<lbl<<" "<<fTypeMap[lbl]<<" "<<fLabelMap[lbl]<<endl;
       status = false;
     }
   } // end of switch

  return status;
}



bool TSpegPlastic::Treat()
{
   return true;
}



void TSpegPlastic::InitBranch(TTree *tree)
{
   tree->Branch("Speg_PLASTIC", "TSpegPlasticData", &fSpegPlasticData);
}

