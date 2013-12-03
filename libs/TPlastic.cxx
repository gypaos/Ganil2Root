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
 * Last update    : March 2011                                               *
 *---------------------------------------------------------------------------*
 * Decription: This class is in charged of converting raw data from GANIL    *
 *             format to a ROOT format for the plastic detector              *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Comment:                                                                  *
 *    + march 2011: Add support for TPlasticPhysics from NPTool              *
 *                                                                           *
 *****************************************************************************/
#include "TPlastic.h"

#include <string>
#include <cstdlib>
using namespace std;


ClassImp(TPlastic)

TPlastic::TPlastic()
{
	// Default constructor
	fPlasticData    = new TPlasticData();
}

TPlastic::~TPlastic()
{
	delete fPlasticData;
}

bool TPlastic::Clear()
{
	fPlasticData->Clear();
	return true;
}

bool TPlastic::Init(GDataParameters *params)
{
	bool status = false;

	Int_t nbParams = params->GetNbParameters();
	for (Int_t index = 0; index < nbParams; index++) 
	{
		Int_t lbl    = params->GetLabel(index);
		string label = params->GetParName(index);
		// cout << index << "  " << lbl << "  " << label <<  endl;
       
		if (label.compare(0,5,"PLAST") == 0 ) 
		{  
			fLabelMap[lbl] = label;
			status = true;

			if (label.compare(5,2,"_E") == 0 ) 
			{
				// cout << fTypeMap[lbl] << endl;
				fTypeMap[lbl] = PL_E;
			} 
			else 
			{
				cout << "TPlastic::Init() : problem reading Plastic's label -> " << label << endl;
				status = false;
			}
		}
	}
   
	return status;
}

bool TPlastic::Is(UShort_t lbl, Short_t val)
{
	bool status = false;

	switch (fTypeMap[lbl]) 
	{
		case PL_E :
		{  
			//cout<<  "- ---------< Plastic E >------------------!\n";
			fPlasticData->SetPlasticNumber(1);
			fPlasticData->SetEnergy(val);
			status = true;
			break;
		}
    
		default:
		{
			//cout<<"TPlastic::Is --> not a good label"<<endl;
			status = false;
		}
	} // end of switch

  return status;
}

bool TPlastic::Treat()
{ 
   return true;
}

void TPlastic::InitBranch(TTree *tree)
{
	tree->Branch("PLASTIC", "TPlasticData", &fPlasticData);
}

