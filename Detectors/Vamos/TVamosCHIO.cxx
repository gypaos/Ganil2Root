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
 *             format to a ROOT format for the Vamos chio detector           *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Comment:                                                                  *
 *                                                                           *
 *****************************************************************************/
#include "TVamosCHIO.h"

#include <string>
#include <cstdlib>
using namespace std;


ClassImp(TVamosCHIO)

TVamosCHIO::TVamosCHIO()
{
   // Default constructor
   fVamosCHIOData    = new TVamosCHIOData();
}



TVamosCHIO::~TVamosCHIO()
{
   delete fVamosCHIOData;
}



bool TVamosCHIO::Clear()
{
   fVamosCHIOData->Clear();

   return true;
}



bool TVamosCHIO::Init(DataParameters *params)
{
   Int_t channum;
   Int_t nbParams = params->GetNbParameters();
   bool status = false;

   for (Int_t index = 0; index < nbParams; index++) {
       Int_t lbl    = params->GetLabel(index);
       string label = params->GetParNameFromIndex(index);
       //      cout << index << "  " << lbl << "  " << label << "  " << fLabelMap[lbl] << endl;
       
       if (label.compare(0,4,"ECHI") == 0 ) { 
	 fLabelMap[lbl] = label;
	 status = true;

	 if (label.compare(5,1,"A") == 0 ) {
	     fTypeMap[lbl] = VAMOS_A;
	     channum = atoi(label.substr(7).c_str());
	     fParameterMap[lbl] = channum;                 // CHIO A signals 1-7
	       //	    cout << fTypeMap[lbl] << "  " << fParameterMap[lbl] << endl;
	  } 
	  else if (label.compare(5,1,"B") == 0 ) {
	     fTypeMap[lbl] = VAMOS_B;
	     channum = atoi(label.substr(7).c_str());
	     fParameterMap[lbl] = channum;                 // CHIO B signals 1-7
	       //	    cout << fTypeMap[lbl] << "  " << fParameterMap[lbl] << endl;
	  }
	  else if (label.compare(5,1,"C") == 0 ) {
	     fTypeMap[lbl] = VAMOS_C;
	     channum = atoi(label.substr(7).c_str());
	     fParameterMap[lbl] = channum;                 // CHIO C signals 1-7
	       //	    cout << fTypeMap[lbl] << "  " << fParameterMap[lbl] << endl;
	  }
	  else {
	    cout << "TVamosCHIO::Init() : problem reading VamosCHIO label -> " << label << endl;
	     status = false;
	  }
       }
   }   
   
   return status;
}



bool TVamosCHIO::Is(UShort_t lbl, Short_t val)
{
   bool result = false;

  switch (fTypeMap[lbl]) {
    
    case VAMOS_A :{  
      //cout<<  "- ---------< CHIO A >------------------!\n";
      fVamosCHIOData->SetVamosCHIOPadNbrA(fParameterMap[lbl]);
      fVamosCHIOData->SetVamosCHIOEnergyA(val);
      result = true;
      break;
    }
    
    case VAMOS_B :{  
      //cout<<  "- ---------< CHIO B >------------------!\n";
      fVamosCHIOData->SetVamosCHIOPadNbrB(fParameterMap[lbl]);
      fVamosCHIOData->SetVamosCHIOEnergyB(val);
      result = true;
      break;
    }

    case VAMOS_C :{  
      //cout<<  "- ---------< CHIO C >------------------!\n";
      fVamosCHIOData->SetVamosCHIOPadNbrC(fParameterMap[lbl]);
      fVamosCHIOData->SetVamosCHIOEnergyC(val);
      result = true;
      break;
    }

    default: {
      //cout<<"TVamosCHIO::Is --> not a good label"<<lbl<<" "<<fTypeMap[lbl]<<" "<<fLabelMap[lbl]<<endl;
      result = false;
      break;
    }
    
  } // end of switch

  return result;
}



bool TVamosCHIO::Treat()
{
   return true;
}




void TVamosCHIO::InitBranch(TTree *tree)
{
   tree->Branch("VAMOS_CHIO", "TVamosCHIOData", &fVamosCHIOData);
}

