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
#include "TChio_an.h"

#include <string>
#include <cstdlib>
using namespace std;


ClassImp(TChio_an)

TChio_an::TChio_an()
{
	// Default constructor
	fChio_anData    = new TChio_anData();
}

TChio_an::~TChio_an()
{
	delete fChio_anData;
}

bool TChio_an::Clear()
{
	fChio_anData->Clear();
	return true;
}

bool TChio_an::Init(DataParameters *params)
{
	bool status = false;

	Int_t nbParams = params->GetNbParameters();
	for (Int_t index = 0; index < nbParams; index++) 
	{
		Int_t lbl    = params->GetLabel(index);
		string label = params->GetParNameFromIndex(index);
		// cout << index << "  " << lbl << "  " << label << endl;
		if ((label.compare(0,7,"CHIO_AN") == 0))
		{  
			fLabelMap[lbl] = label;
			status = true;

			if (label.compare(7,2,"_E") ==0)
			{
				fTypeMap[lbl] = CHIO_AN_E;
	                } 
			else if (label.compare(7,7,"_pileup") == 0 )
			{
				fTypeMap[lbl] = CHIO_AN_E_PILEUP;
			} 
			else 
			{
				cout << "TChio_an::Init() : problem reading Chio_an's label -> " << label << endl;
				status = false;
			}
		}
	}
   
	return status;
}

bool TChio_an::Is(UShort_t lbl, Short_t val)
{
	bool status = false;

	switch (fTypeMap[lbl]) 
	{
    
		case CHIO_AN_E :
		{  
			//     cout<<  "- ---------< Chio_an E >------------------!\n";
			fChio_anData->SetEnergy(val);
			status = true;
			break;
		}
		case CHIO_AN_E_PILEUP :
		{  
			//     cout<<  "- ---------< Chio_an E PILEUP >------------------!\n";
			fChio_anData->SetEnergy_pileup(val);
			status = true;
			break;
		}
   
		default:
		{
			//cout<< "TChio_an::Is --> not a good label"<<endl; 
			status = false;
			break;
		}
	} // end of switch

	return status;
}

bool TChio_an::Treat()
{
   return true;
}

void TChio_an::InitBranch(TTree *tree)
{
	tree->Branch("CHIO_AN", "TChio_anData", &fChio_anData);
}

