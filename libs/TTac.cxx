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
 *             format to a ROOT format for the TAC modules                   *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Comment:                                                                  *
 *   + The name of the variables (e.g. TAC_CATS1_HF) should be defined for   *
 *     each experiment in a consistent way with the ACTION file.             *
 *                                                                           *
 *****************************************************************************/
#include "TTac.h"

#include <string>
#include <cstdlib>
using namespace std;


ClassImp(TTac)

TTac::TTac()
{
	// Default constructor
	fTacData    = new TTacData();
}

// Destructeur
TTac::~TTac()
{
	delete fTacData;
}

bool TTac::Clear()
{
	fTacData->Clear();
	return true;
}

bool TTac::Init(GDataParameters *params)
{
	bool status = false;
	Int_t nbParams = params->GetNbParameters();
	for (Int_t index = 0; index < nbParams; index++) 
	{
		Int_t lbl    = params->GetLabel(index);
		string label = params->GetParName(index);
		//      cout << index << "  " << lbl << "  " << label <<  endl;
	  
	  if (label.compare(0,2,"T_") == 0 ) 
		{  
			fLabelMap[lbl] = label;
			status = true;
			if (label.compare(2,8,"MM_CATS1") == 0 ) 
			{
				fTypeMap[lbl] = TAC_MM_CATS1;
				// cout << fTypeMap[lbl] << endl;
			} 
			else if (label.compare(2,8,"MM_CATS2") == 0 ) 
			{
				fTypeMap[lbl] = TAC_MM_CATS2;
				// cout << fTypeMap[lbl] << endl;
			} 
			else if (label.compare(2,8,"PL_CATS1") == 0 ) 
			{
				fTypeMap[lbl] = TAC_PL_CATS1;
	    	                // cout << fTypeMap[lbl] << endl;
			} 
			else if (label.compare(2,8,"PL_CATS2") == 0 ) 
			{
				fTypeMap[lbl] = TAC_PL_CATS2;
				// cout << fTypeMap[lbl] << endl;
			} 
			else if (label.compare(2,6,"CATS12") == 0 ) 
			{
				fTypeMap[lbl] = TAC_CATS12;
				// cout << fTypeMap[lbl] << endl;
			} 
			else if (label.compare(2,6,"PL_GAL") == 0 ) 
			{
				fTypeMap[lbl] = TAC_PL_GAL;
				// cout << fTypeMap[lbl] << endl;
			} 
			else if (label.compare(2,8,"CATS1_HF") == 0 ) 
			{
				fTypeMap[lbl] = TAC_CATS1_HF;
				// cout << fTypeMap[lbl] << endl;
			} 
			else if (label.compare(2,8,"CATS2_HF") == 0 ) 
			{
				fTypeMap[lbl] = TAC_CATS2_HF;
				// cout << fTypeMap[lbl] << endl;
			} 
			else if (label.compare(2,5,"MM_HF") == 0 ) 
			{
				fTypeMap[lbl] = TAC_MM_HF;
				// cout << fTypeMap[lbl] << endl;
			} 
			else 
			{
				cout << "TTac::Init() : problem reading Tac's label -> " << label << endl;
				status = false;
			}
		}
	}
  
  return status;
}



bool TTac::Is(UShort_t lbl, Short_t val)
{
	bool status = false;
	switch (fTypeMap[lbl])
	{
    
		case TAC_MM_CATS1 :
		{  
    	//cout<<  "- ---------< Tac 1 >------------------!\n";
    	fTacData->SetTAC_MM_CATS1(val);
    	status = true;
    	break;
  	}
  	case TAC_MM_CATS2 :
		{  
    	//cout<<  "- ---------< Tac 2 >------------------!\n";
    	fTacData->SetTAC_MM_CATS2(val);
    	status = true;
    	break;
  	}
  	case TAC_PL_CATS1 :
		{  
    	//cout<<  "- ---------< Tac 3 >------------------!\n";
    	fTacData->SetTAC_PL_CATS1(val);
    	status = true;
    	break;
		}
		case TAC_PL_CATS2 :
		{  
    	//cout<<  "- ---------< Tac 4 >------------------!\n";
    	fTacData->SetTAC_PL_CATS2(val);
    	status = true;
    	break;
		}
		case TAC_CATS12 :
		{  
			//cout<<  "- ---------< Tac 5 >------------------!\n";
			fTacData->SetTAC_CATS12(val);
			status = true;
			break;
		}
		case TAC_PL_GAL :
		{  
    	//cout<<  "- ---------< Tac 6 >------------------!\n";
    	fTacData->SetTAC_PL_GAL(val);
    	status = true;
    	break;
		}
		case TAC_CATS1_HF :
		{  
			//cout<<  "- ---------< Tac 7 >------------------!\n";
			fTacData->SetTAC_CATS1_HF(val);
			status = true;
			break;
		}
		case TAC_CATS2_HF :
		{  
			//cout<<  "- ---------< Tac 8 >------------------!\n";
			fTacData->SetTAC_CATS2_HF(val);
			status = true;
			break;
		}
		case TAC_MM_HF :
		{  
			//cout<<  "- ---------< Tac 9 >------------------!\n";
			fTacData->SetTAC_MM_HF(val);
			status = true;
			break;
		}
		default:
		{
			//cout<<"TTac::Is --> not a good label"<<endl;
			status = false;
		}
	}
  
	return status;
}

bool TTac::Treat()
{
	return true;
}

void TTac::InitBranch(TTree *tree)
{
	tree->Branch("TAC", "TTacData", &fTacData);
}

