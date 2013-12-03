/*****************************************************************************
 * Copyright (C) 2008   this file is part of the Ganil2Root Project          *
 *                                                                           *
 * For the licensing terms see $GANIL2ROOT/Licence                           *
 * For the list of contributors see $GANIL2ROOT/README/CREDITS               *
 *****************************************************************************/

/*****************************************************************************
 * Original Author: L. Lefebvre      contact address: lefebvrl@ipno.in2p3.fr *
 *                                                                           *
 *                                                                           *
 * Creation Date  : June 2011                                                *
 * Last update    :                                                          *
 *---------------------------------------------------------------------------*
 * Decription: This class is in charged of converting raw data from GANIL    *
 *             format to a ROOT format for the Speg chio detector            *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Comment:                                                                  *
 *                                                                           *
 *****************************************************************************/
#include "TSpegCHIO.h"

#include <string>
#include <cstdlib>
using namespace std;


ClassImp(TSpegCHIO)

TSpegCHIO::TSpegCHIO()
{
   // Default constructor
   fSpegCHIOData    = new TSpegCHIOData();
}



TSpegCHIO::~TSpegCHIO()
{
   delete fSpegCHIOData;
}



bool TSpegCHIO::Clear()
{
   fSpegCHIOData->Clear();

   return true;
}



bool TSpegCHIO::Init(GDataParameters *params)
{
   Int_t nbParams = params->GetNbParameters();
   bool status = false;

   for (Int_t index = 0; index < nbParams; index++) {
       Int_t lbl    = params->GetLabel(index);
       string label = params->GetParName(index);
       //      cout << index << "  " << lbl << "  " << label << "  " << fLabelMap[lbl] << endl;
       
       if (label.compare(0,2,"AN") == 0 ) { 
	 fLabelMap[lbl] = label;
	 status = true;
         if (label.compare(0,2,"AN") == 0 ) { 
         fTypeMap[lbl] = AN;
	 }
	 else {
	    cout << "TSpegCHIO::Init() : problem reading SpegCHIO label -> " << label << endl;
	     status = false;
	  }
	}
       }   
   
   return status;
}

bool TSpegCHIO::Is(UShort_t lbl, Short_t val)
{
   bool result = false;

  switch (fTypeMap[lbl]) {
    
    case AN :{  
      //cout<<  "- ---------< CHIO ANODE >------------------!\n";
      fSpegCHIOData->SetSpegCHIOEnergy(val);
      result = true;
      break;    
    }

    default: {
     // cout<<"TSpegCHIO::Is --> not a good label"<<lbl<<" "<<fTypeMap[lbl]<<" "<<fLabelMap[lbl]<<endl;
      result = false;
      break;
    }
    
  } // end of switch

  return result;
}



bool TSpegCHIO::Treat()
{
   return true;
}




void TSpegCHIO::InitBranch(TTree *tree)
{
   tree->Branch("Speg_CHIO", "TSpegCHIOData", &fSpegCHIOData);
}

