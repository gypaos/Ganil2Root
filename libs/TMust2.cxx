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
 *             format to a ROOT format for the Must2 detector                *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Comment:                                                                  *
 *    + march 2011: Add support for TMust2Physics from NPTool                *
 *                                                                           *
 *****************************************************************************/
#include "TMust2.h"

#include <string>
#include <cstdlib>
using namespace std;


ClassImp(TMust2)

TMust2::TMust2()
{
	// Default constructor
	fMust2Data    = new TMust2Data();
}

TMust2::~TMust2()
{
	delete fMust2Data;
}

bool TMust2::Clear()
{
	fMust2Data->Clear();
	return true;
}

bool TMust2::Init(GDataParameters *params)
{
	Int_t channum;
	Int_t nbParams = params->GetNbParameters();
	bool status = false;

	for (Int_t index = 0; index < nbParams; index++) 
	{
		Int_t lbl      = params->GetLabel(index);
		string label   = params->GetParName(index);

		if (label.compare(0,2,"MM") == 0 ) 
		{
			status = true;
			fLabelMap[lbl]	 = label;
	     
			if (label.compare(4,6,"STRX_E") == 0 ) 
			{
				fTypeMap[lbl] = MUST2STR_XE;
				channum = atoi(label.substr(10).c_str());
				fParameterMap[lbl] = channum;                 //MM STR X-E signals 1-128 
			} 
			else if (label.compare(4,6,"STRX_T") == 0 ) 
			{
				fTypeMap[lbl] = MUST2STR_XT;
				channum = atoi(label.substr(10).c_str());
				fParameterMap[lbl] = channum;                 //MM STR X-T signals 1-128
			}
			else if (label.compare(4,6,"STRY_E") == 0 ) 
			{
				fTypeMap[lbl] = MUST2STR_YE;
				channum = atoi(label.substr(10).c_str());
				fParameterMap[lbl] = channum;                 //MM STR Y-E signals 1-128 
			} 
			else if (label.compare(4,6,"STRY_T") == 0 ) 
			{
				fTypeMap[lbl] = MUST2STR_YT;
				channum = atoi(label.substr(10).c_str());
				fParameterMap[lbl] = channum;                 //MM STR Y-T signals 1-128 
			}
			else if (label.compare(4,6,"SILI_E") == 0 ) 
			{
				fTypeMap[lbl] = MUST2SILI_E;
				channum = atoi(label.substr(10).c_str());
				fParameterMap[lbl] = channum;                 //MM SILI E signals 1-16
			} 
			else if (label.compare(4,6,"SILI_T") == 0 ) 
			{
				fTypeMap[lbl] = MUST2SILI_T;
				channum = atoi(label.substr(10).c_str());
				fParameterMap[lbl] = channum;                 //MM SILI T signals 1-16
			}
			else if (label.compare(4,5,"CSI_E") == 0 ) 
			{
				fTypeMap[lbl] = MUST2CSI_E;
				channum = atoi(label.substr(9).c_str());
				fParameterMap[lbl] = channum;                 //MM CsI E signals 1-16
			} 
			else if (label.compare(4,5,"CSI_T") == 0 ) 
			{
				fTypeMap[lbl] = MUST2CSI_T;
				channum = atoi(label.substr(9).c_str());
				fParameterMap[lbl] = channum;                 //MM CsI T signals 1-16 
			} 
			else 
			{
				cout << "TMust2::Init() : problem reading MUST2 label -> " << label << endl;
				status = false;
			}
		}
	} 
	
	return status;
}

bool TMust2::Is(UShort_t lbl, Short_t val)
{
	Int_t det;
	bool result = false;

	switch (fTypeMap[lbl]) 
	{
    
		case MUST2STR_XE :
		{  
			//cout<<  "- ---------< STR X E >------------------!\n";
			det = atoi(fLabelMap[lbl].substr(2,1).c_str());
			fMust2Data->SetMMStripXEDetectorNbr(det);
			fMust2Data->SetMMStripXEStripNbr(fParameterMap[lbl]);
			fMust2Data->SetMMStripXEEnergy(val);
			result = true;
			break;
		}
    
		case MUST2STR_XT :
		{
			//cout<<  " ----------< STR X T >------------------!\n"; 
			det = atoi(fLabelMap[lbl].substr(2,1).c_str());
			fMust2Data->SetMMStripXTDetectorNbr(det);
			fMust2Data->SetMMStripXTStripNbr(fParameterMap[lbl]);
			fMust2Data->SetMMStripXTTime(val);
			result = true;
			break;
		}

		case MUST2STR_YE :
		{  
			//cout<<  "- ---------< STR Y E >------------------!\n";
			det = atoi(fLabelMap[lbl].substr(2,1).c_str());
			fMust2Data->SetMMStripYEDetectorNbr(det);
			fMust2Data->SetMMStripYEStripNbr(fParameterMap[lbl]);
			fMust2Data->SetMMStripYEEnergy(val);
			result = true;
			break;
		}
    
		case MUST2STR_YT :
		{
			//cout<<  " ----------< STR Y T >------------------!\n"; 
			det = atoi(fLabelMap[lbl].substr(2,1).c_str());
			fMust2Data->SetMMStripYTDetectorNbr(det);
			fMust2Data->SetMMStripYTStripNbr(fParameterMap[lbl]);
			fMust2Data->SetMMStripYTTime(val);
			result = true;
			break;
		}

		case MUST2SILI_E :
		{  
			//cout<<  "- ---------<  SILI E >------------------!\n";
			det = atoi(fLabelMap[lbl].substr(2,1).c_str());
			if (fLabelMap[lbl].compare(0,9,"SILIORSAY") == 0) det = 4;
			fMust2Data->SetMMSiLiEDetectorNbr(det);
			fMust2Data->SetMMSiLiEPadNbr(fParameterMap[lbl]);
			fMust2Data->SetMMSiLiEEnergy(val);
			result = true;
			break;
		}
    
		case MUST2SILI_T :
		{
			//cout<<  " ----------<  SILI T >------------------!\n"; 
			det = atoi(fLabelMap[lbl].substr(2,1).c_str());
			if (fLabelMap[lbl].compare(0,9,"SILIORSAY") == 0) det = 4;
			fMust2Data->SetMMSiLiTDetectorNbr(det);
			fMust2Data->SetMMSiLiTPadNbr(fParameterMap[lbl]);
			fMust2Data->SetMMSiLiTTime(val);
			result = true;
			break;
		}

		case MUST2CSI_E :
		{  
			//cout<<  "- ---------<  CSI E  >------------------!\n";
			det = atoi(fLabelMap[lbl].substr(2,1).c_str());
			fMust2Data->SetMMCsIEDetectorNbr(det);
			fMust2Data->SetMMCsIECristalNbr(fParameterMap[lbl]);
			fMust2Data->SetMMCsIEEnergy(val);
			result = true;
			break;
		}
    
		case MUST2CSI_T :
		{
			//cout<<  " ----------<  CSI T  >------------------!\n"; 
			det = atoi(fLabelMap[lbl].substr(2,1).c_str());
			fMust2Data->SetMMCsITDetectorNbr(det);
			fMust2Data->SetMMCsITCristalNbr(fParameterMap[lbl]);
			fMust2Data->SetMMCsITTime(val);
			result = true;
			break;
		}

		default: 
		{
			result = false;
			break;
		}

	} // end switch
  
	return result;
}

bool TMust2::Treat()
{
	return true;
}

void TMust2::InitBranch(TTree *tree)
{
   tree->Branch("MUST2", "TMust2Data", &fMust2Data);
}

