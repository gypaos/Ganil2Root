/*****************************************************************************
 * Copyright (C) 2008   this file is part of the Ganil2Root Project          *
 *                                                                           *
 * For the licensing terms see $GANIL2ROOT/Licence                           *
 * For the list of contributors see $GANIL2ROOT/README/CREDITS               *
 *****************************************************************************/

/*****************************************************************************
 * Original Author: L. Lefebvre  contact address: lefebvrl@ipno.in2p3.fr     *
 *                    							     *
 *                                                                           *
 * Creation Date  : June 2011                                                *
 * Last update    :                                                          *
 *---------------------------------------------------------------------------*
 * Decription: This class is in charged of converting raw data from GANIL    *
 *             format to a ROOT format for the Exl detector                  *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Comment:                                                                  *
 *                                                                           *
 *                                                                           *
 *****************************************************************************/
#include "TExl.h"

#include <string>
#include <cstdlib>
using namespace std;


ClassImp(TExl)

TExl::TExl()
{
	// Default constructor
	fExlData    = new TExlData();
}

TExl::~TExl()
{
	delete fExlData;
}

bool TExl::Clear()
{
	fExlData->Clear();
	return true;
}

bool TExl::Init(DataParameters *params)
{
        Int_t channum;
        Int_t nbParams = params->GetNbParameters();
	bool status = false;

for (Int_t index = 0; index < nbParams; index++) 
{
	Int_t lbl    = params->GetLabel(index);
	string label = params->GetParNameFromIndex(index);
	// cout << index << "  " << lbl << "  " << label <<  endl;
        if(label.compare(0,5,"EXL_E") == 0 )
	{
		fLabelMap[lbl] = label;
		status = true;
		if(label.compare(0,5,"EXL_E") == 0 )
		{
			fTypeMap[lbl] = EXL_E;
			channum = atoi(label.substr(6).c_str());
			fParameterMap[lbl] = channum;                 //EXL signals 1-18 
		}

		else 
		{
			cout << "TExl::Init() : problem reading Exl's label -> " << label << endl;
			status = false;
		}

	}

        else if(label.compare(0,5,"EXL_T") == 0 )
	{
		fLabelMap[lbl] = label;
		status = true;
		if(label.compare(0,5,"EXL_T") == 0 )
		{
			fTypeMap[lbl] = EXL_T;
		}

		else 
		{
			cout << "TExl::Init() : problem reading Exl's label -> " << label << endl;
			status = false;
		}
	}
 
}
   
	return status;
}

bool TExl::Is(UShort_t lbl, Short_t val)
{
        Int_t det;
	bool status = false;

	switch (fTypeMap[lbl]) 
	{
		case EXL_E :
		{  
			//cout<<  "- ---------< Exl E >------------------!\n";
      			det = atoi(fLabelMap[lbl].substr(6).c_str());
			fExlData->SetExlNumber(det);
			fExlData->SetEnergy(val);
			status = true;
			break;
		}

		case EXL_T :
		{  
			//cout<<  "- ---------< Exl T >------------------!\n";
			fExlData->SetTime(val);
			status = true;
			break;
		}
    
		default:
		{
			//cout<<"TExl::Is --> not a good label"<<endl;
			status = false;
		}
	} // end of switch

  return status;
}

bool TExl::Treat()
{ 
   return true;
}

void TExl::InitBranch(TTree *tree)
{
	tree->Branch("Exl", "TExlData", &fExlData);
}

