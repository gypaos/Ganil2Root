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
 *             format to a ROOT format for the Vamos finger                  *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Comment:                                                                  *
 *                                                                           *
 *****************************************************************************/
#include "TVamosFinger.h"

#include <string>
#include <cstdlib>
using namespace std;


ClassImp(TVamosFinger)

TVamosFinger::TVamosFinger()
{
   // Default constructor
   fVamosFingerData    = new TVamosFingerData();
}



TVamosFinger::~TVamosFinger()
{
   delete fVamosFingerData;
}



bool TVamosFinger::Clear()
{
   fVamosFingerData->Clear();

   return true;
}



bool TVamosFinger::Init(GDataParameters *params)
{
   bool status = false;

   Int_t nbParams = params->GetNbParameters();
   for (Int_t index = 0; index < nbParams; index++) {
      Int_t lbl    = params->GetLabel(index);
      string label = params->GetParName(index);
//      cout << index << "  " << lbl << "  " << label <<  endl;
       
      if (label.compare(0,6,"FINGER") == 0 ) {  
	 fLabelMap[lbl] = label;
	 status = true;
         fTypeMap[lbl] = FINGER;
      }
   }
   
   return status;
}



bool TVamosFinger::Is(UShort_t lbl, Short_t val)
{
   bool status = false;

   switch (fTypeMap[lbl]) {
     case FINGER :{  
       //cout<<  "- ---------< VamosFinger E >------------------!\n";
       fVamosFingerData->SetFingerEnergy(val);
       status = true;
       break;
     }
    
     default:{
       //cout<<"TVamosFinger::Is --> not a good label"<<endl;
       status = false;
     }
   } // end of switch

  return status;
}



bool TVamosFinger::Treat()
{
   return true;
}



void TVamosFinger::InitBranch(TTree *tree)
{
   tree->Branch("VAMOS_FINGER", "TVamosFingerData", &fVamosFingerData);
}

