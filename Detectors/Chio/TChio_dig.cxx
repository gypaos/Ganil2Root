/*****************************************************************************
 * Copyright (C) 2008   this file is part of the Ganil2Root Project          *
 *                                                                           *
 * For the licensing terms see $GANIL2ROOT/Licence                           *
 * For the list of contributors see $GANIL2ROOT/README/CREDITS               *
 *****************************************************************************/

/*****************************************************************************
 * Original Author: M. Niikura      contact address: niikura@ipno.in2p3.fr   *
 *                                                                           *
 * Creation Date  : March 2011                                               *
 * Last update    :                                                          *
 *---------------------------------------------------------------------------*
 * Decription: This class is in charged of converting raw data from GANIL    *
 *             format to a ROOT format for the Chio detector                 *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Comment:                                                                  *
 *                                                                           *
 *****************************************************************************/
#include "TChio_dig.h"

#include <string>
#include <cstdlib>
using namespace std;



ClassImp(TChio_dig)

TChio_dig::TChio_dig()
{
	// Default constructor
	fChio_digData    = new TChio_digData();
}

TChio_dig::~TChio_dig()  
{
	delete fChio_digData;
}

bool TChio_dig::Clear()
{
	fChio_digData->Clear();
	return true;
}

bool TChio_dig::Init(DataParameters *params)
{
	bool status = false;

	Int_t nbParams = params->GetNbParameters();
	for (Int_t index = 0; index < nbParams; index++) 
	{
		Int_t lbl    = params->GetLabel(index);
		string label = params->GetParNameFromIndex(index);
		//cout << index << "  " << lbl << "  " << label  << endl;
       
		if (label.compare(0,10,"CHIO_DIGIT") == 0 ) 
		{
			fLabelMap[lbl] = label;
			status = true;
			fTypeMap[lbl] = CHIO_DIG_E;
			//cout << fTypeMap[lbl] << endl;
		}
	
	}

	return status;
} 

bool TChio_dig::Is(UShort_t lbl,Short_t val)
{
  bool status = false;
  
  switch (fTypeMap[lbl]) 
    {
    case CHIO_DIG_E :
      {  
	//cout<<  "- ---------< Chio_dig E >------------------!\n";
	fChio_digData->SetEnergy(val);
	fChio_digData->SetSum(val);
	status = true; 
	break;
      }
      
    default:
      {
	//cout<<"TChio_dig::Is --> not a good label"<<endl;
	status = false;
      }
    }
  
  return status; 
}

bool TChio_dig::Treat()
{
  return true;
}

void TChio_dig::InitBranch(TTree *tree)
{
	tree->Branch("CHIO_DIG", "TChio_digData", &fChio_digData);
}
