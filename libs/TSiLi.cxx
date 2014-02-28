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
#include "TSiLi.h"

#include <string>
#include <cstdlib>
using namespace std;


ClassImp(TSiLi)

TSiLi::TSiLi()
{
	// Default constructor
	fSiLiData    = new TSiLiData();
}



TSiLi::~TSiLi()
{
	delete fSiLiData;
}



bool TSiLi::Clear()
{
	fSiLiData->Clear();
	return true;
}



bool TSiLi::Init(GDataParameters *params)
{
	bool status = false;

	Int_t nbParams = params->GetNbParameters();
	for (Int_t index = 0; index < nbParams; index++) 
	{
		Int_t lbl    = params->GetLabel(index);
		string label = params->GetParName(index);
		// cout << index << "  " << lbl << "  " << label <<  endl;
       
		if (label.compare(0,4,"SILI") == 0 ) 
		{  
			fLabelMap[lbl] = label;
			status = true;

			if (label.compare(4,2,"_E") == 0 ) 
			{
				// cout << fTypeMap[lbl] << endl;
				fTypeMap[lbl] = SILI_E;
			} 
			else if (label.compare(4,2,"_T") == 0) 
         {
				fTypeMap[lbl] = SILI_T;
         }
         else
			{
				cout << "TSiLi::Init() : problem reading SiLi's label -> " << label << endl;
				status = false;
			}
		}
	}
   
	return status;
}



bool TSiLi::Is(UShort_t lbl, Short_t val)
{
   int det;
	bool status = false;

	switch (fTypeMap[lbl]) 
	{
		case SILI_E :
		{  
			//cout<<  "- ---------< SiLi E >------------------!\n";
			det = atoi(fLabelMap[lbl].substr(6,1).c_str());
         fSiLiData->SetENumber(det);
			fSiLiData->SetEEnergy(val);
			status = true;
			break;
		}
    
		case SILI_T :
		{  
			//cout<<  "- ---------< SiLi E >------------------!\n";
			det = atoi(fLabelMap[lbl].substr(6,1).c_str());
			fSiLiData->SetTNumber(det);
			fSiLiData->SetTTime(val);
			status = true;
			break;
		}
    
		default:
		{
			//cout<<"TSiLi::Is --> not a good label"<<endl;
			status = false;
		}
	} // end of switch

  return status;
}



bool TSiLi::Treat()
{ 
   return true;
}



void TSiLi::InitBranch(TTree *tree)
{
	tree->Branch("SILI3", "TSiLiData", &fSiLiData);
}

