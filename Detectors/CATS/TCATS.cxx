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
 *             format to a ROOT format for the Cats detector                 *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Comment:                                                                  *
 *    + march 2011: Add support for TCATSPhysics from NPTool                 *
 *                                                                           *
 *****************************************************************************/
#include "TCATS.h"

#include <cstdlib>
#include <string>
using namespace std;


ClassImp(TCATS)


TCATS::TCATS()
{
	// Default constructor
	fCATSData    = new TCATSData();
}



TCATS::~TCATS()
{
	delete fCATSData;
}



bool TCATS::Clear()
{
	fCATSData->Clear();
	return true;
}



bool TCATS::Init(DataParameters *params)
{
	Int_t channum;
	Int_t nbParams = params->GetNbParameters();
	bool status = false;

	for (Int_t index = 0; index < nbParams; index++) 
	{
		Int_t lbl    = params->GetLabel(index);
		string label = params->GetParNameFromIndex(index);
		//cout << index << "  " << lbl << "  " << label << "  " << fLabelMap[lbl] << endl;

		if (label.compare(0,4,"CATS") == 0 ) 
		{ 
			fLabelMap[lbl] = label;
			status = true;

			if (label.compare(6,1,"X") == 0 ) 
			{
				fTypeMap[lbl] = CATS_X;
				channum = atoi(label.substr(7).c_str());
				fParameterMap[lbl] = channum;					// CATS X signals 1-28
				//cout << fTypeMap[lbl] << "  " << fParameterMap[lbl] << endl;
			} 
			else if (label.compare(6,1,"Y") == 0 ) 
			{
				fTypeMap[lbl] = CATS_Y;
				channum = atoi(label.substr(7).c_str());
				fParameterMap[lbl] = channum;                 // CATS Y signals 1-28
				//cout << fTypeMap[lbl] << "  " << fParameterMap[lbl] << endl;
			}
                        else if(label.compare(6,4,"QFIL") == 0 )
                        {
                                fLabelMap[lbl] = label;
                                fTypeMap[lbl] = CATS_Q;
                        }			
			else 
			{
				cout << "TCATS::Init() : problem reading CATS label -> " << label << endl;
				status = false;
			}
		}

                // old version removed 9.3.11
		//else if(label.compare(0,4,"QFIL") == 0 ) 
		//{
		//	fLabelMap[lbl] = label;
		//	status = true;
		//	fTypeMap[lbl] = CATS_Q;
		//} 
	}   
   
	return status;
}

bool TCATS::Is(UShort_t lbl, Short_t val)
{
	Int_t det;
	bool result = false;

	switch (fTypeMap[lbl]) 
	{
    
		case CATS_X :
		{  
			//cout<<  "- ---------< CATS X E >------------------!\n";
			det = atoi(fLabelMap[lbl].substr(4,1).c_str());
			fCATSData->SetCATSDetX(det);
			fCATSData->SetCATSStripX(fParameterMap[lbl]);
			fCATSData->SetCATSChargeX(val);
			result = true;
			break;
		}
    
		case CATS_Y :
		{  
			//cout<<  "- ---------< CATS Y E >------------------!\n";
			det = atoi(fLabelMap[lbl].substr(4,1).c_str());
      fCATSData->SetCATSDetY(det);
      fCATSData->SetCATSStripY(fParameterMap[lbl]);
      fCATSData->SetCATSChargeY(val);
      result = true;
      break;
    }

    case CATS_Q :
		{  
      //cout<<  "- ---------<  CATS Q >------------------!\n";
      det = atoi(fLabelMap[lbl].substr(4,1).c_str());
      fCATSData->SetCATSDetQ(det);
      fCATSData->SetCATSCharge(val);
      result = true;
    }

		default: 
		{
			//cout<<"TCATS::Is --> not a good label"<<lbl<<" "<<fTypeMap[lbl]<<" "<<fLabelMap[lbl]<<endl;
      result = false;
      break;
		}
    
	} // end of switch

	return result;
}

bool TCATS::Treat()
{
   return true;
}

void TCATS::InitBranch(TTree *tree)
{
   tree->Branch("CATS", "TCATSData", &fCATSData);
}

