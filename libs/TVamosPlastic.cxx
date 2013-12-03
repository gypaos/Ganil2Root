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
 *             format to a ROOT format for the Vamos plastic                 *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Comment:                                                                  *
 *                                                                           *
 *****************************************************************************/
#include "TVamosPlastic.h"

#include <string>
#include <cstdlib>
using namespace std;


ClassImp(TVamosPlastic)

TVamosPlastic::TVamosPlastic()
{
   // Default constructor
   fVamosPlasticData    = new TVamosPlasticData();
}



TVamosPlastic::~TVamosPlastic()
{
   delete fVamosPlasticData;
}



bool TVamosPlastic::Clear()
{
   fVamosPlasticData->Clear();

   return true;
}



bool TVamosPlastic::Init(GDataParameters *params)
{
   bool status = false;

   Int_t nbParams = params->GetNbParameters();
   for (Int_t index = 0; index < nbParams; index++) {
      Int_t lbl    = params->GetLabel(index);
      string label = params->GetParName(index);
//      cout << index << "  " << lbl << "  " << label <<  endl;
       
      if (label.compare(0,3,"QPL") == 0) {  
	 fLabelMap[lbl] = label;
	 status = true;

	 if (label.compare(3,2,"_G") == 0 ) {
//	    cout << fTypeMap[lbl] << endl;
	    fTypeMap[lbl] = PL_G;
	 } 
         else if (label.compare(3,2,"_D") == 0) {
            fTypeMap[lbl] = PL_D;
         }
	 else {
	    cout << "TVamosPlastic::Init() : problem reading Plastic's label -> " << label << endl;
	    status = false;
	 }
      }
      else if (label.compare(0,8,"TPLG_PLD") == 0) {
         fTypeMap[lbl]  = TPLG_PLD;
         fLabelMap[lbl] = label;
         status = true;
      }
   }
   
   return status;
}



bool TVamosPlastic::Is(UShort_t lbl, Short_t val)
{
   bool status = false;

   switch (fTypeMap[lbl]) {
     case PL_G :{  
       //cout<<  "- ---------< Plastic E >------------------!\n";
       fVamosPlasticData->SetEnergyLeft(val);
       status = true;
       break;
     }
    
     case PL_D :{  
       //cout<<  "- ---------< Plastic E >------------------!\n";
       fVamosPlasticData->SetEnergyRight(val);
       status = true;
       break;
     }
    
     case TPLG_PLD :{  
       //cout<<  "- ---------< Plastic E >------------------!\n";
       fVamosPlasticData->SetTimeLeftRight(val);
       status = true;
       break;
     }
    
     default:{
       //cout<<"TVamosPlastic::Is --> not a good label"<<endl;
       status = false;
     }
   } // end of switch

  return status;
}



bool TVamosPlastic::Treat()
{
   return true;
}



void TVamosPlastic::InitBranch(TTree *tree)
{
   tree->Branch("VAMOS_PLASTIC", "TVamosPlasticData", &fVamosPlasticData);
}

