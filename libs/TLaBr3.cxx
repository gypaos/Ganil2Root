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
#include "TLaBr3.h"

#include <string>
#include <cstdlib>
using namespace std;


ClassImp(TLaBr3)

TLaBr3::TLaBr3()
{
	// Default constructor
	fLaBr3Data    = new TLaBr3Data();
}



TLaBr3::~TLaBr3()
{
	delete fLaBr3Data;
}



bool TLaBr3::Clear()
{
	fLaBr3Data->Clear();
	return true;
}



bool TLaBr3::Init(GDataParameters *params)
{
	bool status = false;

	Int_t nbParams = params->GetNbParameters();
	for (Int_t index = 0; index < nbParams; index++) 
	{
		Int_t lbl    = params->GetLabel(index);
		string label = params->GetParName(index);
		// cout << index << "  " << lbl << "  " << label <<  endl;
       
		if (label.compare(0,5,"LABR3") == 0 ) 
		{  
			fLabelMap[lbl] = label;
			status = true;

			if (label.compare(5,2,"_E") == 0 ) 
			{
				// cout << fTypeMap[lbl] << endl;
				fTypeMap[lbl] = LABR3_E;
			} 
			else if (label.compare(5,2,"_T") == 0) 
         {
				fTypeMap[lbl] = LABR3_T;
         }
         else
			{
				cout << "TLaBr3::Init() : problem reading LaBr3's label -> " << label << endl;
				status = false;
			}
		}
	}
   
	return status;
}



bool TLaBr3::Is(UShort_t lbl, Short_t val)
{
   int det;
	bool status = false;

	switch (fTypeMap[lbl]) 
	{
		case LABR3_E :
		{  
			//cout<<  "- ---------< LaBr3 E >------------------!\n";
			det = atoi(fLabelMap[lbl].substr(7,1).c_str());
         fLaBr3Data->SetENumber(det);
			fLaBr3Data->SetEEnergy(val);
			status = true;
			break;
		}
    
		case LABR3_T :
		{  
			//cout<<  "- ---------< LaBr3 E >------------------!\n";
			det = atoi(fLabelMap[lbl].substr(7,1).c_str());
			fLaBr3Data->SetTNumber(det);
			fLaBr3Data->SetTTime(val);
			status = true;
			break;
		}
    
		default:
		{
			//cout<<"TLaBr3::Is --> not a good label"<<endl;
			status = false;
		}
	} // end of switch

  return status;
}



bool TLaBr3::Treat()
{ 
   return true;
}



void TLaBr3::InitBranch(TTree *tree)
{
	tree->Branch("LABR3", "TLaBr3Data", &fLaBr3Data);
}

