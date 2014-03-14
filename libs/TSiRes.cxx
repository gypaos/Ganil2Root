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
#include "TSiRes.h"

#include <string>
#include <cstdlib>
using namespace std;


ClassImp(TSiRes)

TSiRes::TSiRes()
{
	// Default constructor
	fSiResData    = new TSiResData();
}



TSiRes::~TSiRes()
{
	delete fSiResData;
}



bool TSiRes::Clear()
{
	fSiResData->Clear();
	return true;
}



bool TSiRes::Init(GDataParameters *params)
{
	bool status = false;

	Int_t nbParams = params->GetNbParameters();
	for (Int_t index = 0; index < nbParams; index++) 
	{
		Int_t lbl    = params->GetLabel(index);
		string label = params->GetParName(index);
		// cout << index << "  " << lbl << "  " << label <<  endl;
       
		if (label.compare(0,5,"SIRES") == 0 ) 
		{  
			fLabelMap[lbl] = label;
			status = true;

			if (label.compare(5,2,"_E") == 0 ) 
			{
				// cout << fTypeMap[lbl] << endl;
				if(label.compare(7,4,"BACK") == 0 ) fTypeMap[lbl] = SIRES_EBACK;
				else fTypeMap[lbl] = SIRES_E;
			} 
		else if (label.compare(5,2,"_T") == 0) 
         		{
				fTypeMap[lbl] = SIRES_T;
         		}
         		else
			{
				cout << "TSiRes::Init() : problem reading SiRes's label -> " << label << endl;
				status = false;
			}
		}
	}
   
	return status;
}



bool TSiRes::Is(UShort_t lbl, Short_t val)
{
   	int det,cha;
	bool status = false;

	switch (fTypeMap[lbl]) 
	{
		case SIRES_E :
		{  
			//cout<<  "- ---------< SiRes E >------------------!\n";
			cha = atoi(fLabelMap[lbl].substr(8,1).c_str());
         		fSiResData->SetEChannelNumber(cha);
         		fSiResData->SetEDetectorNumber(1);
			fSiResData->SetEEnergy(val);
			status = true;
			break;
		}
    
		case SIRES_EBACK :
		{  
			//cout<<  "- ---------< SiRes EBack >------------------!\n";
			//det = atoi(fLabelMap[lbl].substr(6,1).c_str());
 			fSiResData->SetEEnergyBack(val);
         		fSiResData->SetEEnergyBackDetectorNumber(1);
			status = true;
			break;
		}
		
		case SIRES_T :
		{  
			//cout<<  "- ---------< SiRes E >------------------!\n";
			//det = atoi(fLabelMap[lbl].substr(6,1).c_str());
			fSiResData->SetTDetectorNumber(1);
			fSiResData->SetTTime(val);
			status = true;
			break;
		}
    
		default:
		{
			//cout<<"TSiRes::Is --> not a good label"<<endl;
			status = false;
		}
	} // end of switch

  return status;
}



bool TSiRes::Treat()
{ 
   return true;
}



void TSiRes::InitBranch(TTree *tree)
{
	tree->Branch("SiRes", "TSiResData", &fSiResData);
}

