/*****************************************************************************
 * Copyright (C) 2008   this file is part of the Ganil2Root Project          *
 *                                                                           *
 * For the licensing terms see $GANIL2ROOT/Licence                           *
 * For the list of contributors see $GANIL2ROOT/README/CREDITS               *
 *****************************************************************************/

/*****************************************************************************
 * Original Author: N. de Sereville  contact address: deserevi@ipno.in2p3.fr *
 *                                                                           *
 * Creation Date  : Dec 2013                                                 *
 * Last update    :                                                          *
 *---------------------------------------------------------------------------*
 * Decription: This class is in charged of converting raw data from GANIL    *
 *             format to a ROOT format for the Charissa detector             *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Comment:                                                                  *
 *                                                                           *
 *****************************************************************************/
#include "TCharissa.h"

#include <string>
#include <cstdlib>
using namespace std;


ClassImp(TCharissa)



TCharissa::TCharissa()
{
	// Default constructor
	fCharissaData    = new TCharissaData();
}



TCharissa::~TCharissa()
{
	delete fCharissaData;
}



bool TCharissa::Clear()
{
	fCharissaData->Clear();
	return true;
}



bool TCharissa::Init(GDataParameters *params)
{
	Int_t channum;
	Int_t nbParams = params->GetNbParameters();
	bool status = false;

	for (Int_t index = 0; index < nbParams; index++) 
	{
		Int_t lbl      = params->GetLabel(index);
		string label   = params->GetParName(index);

		if (label.compare(0,3,"CHA") == 0 ) 
		{
			status = true;
			fLabelMap[lbl]	 = label;
	     
         if (label.compare(5,2,"L1") == 0) {
            if (label.compare(8,6,"STRX_E") == 0 ) 
            {
               fTypeMap[lbl] = CHA_L1_STR_XE;
               channum = atoi(label.substr(14).c_str());
               fParameterMap[lbl] = channum;                 // Charissa strip number 0 - 15
            } 
            else if (label.compare(8,6,"STRX_T") == 0 ) 
            {
               fTypeMap[lbl] = CHA_L1_STR_XT;
               channum = atoi(label.substr(14).c_str());
               fParameterMap[lbl] = channum;                 // Charissa strip number 0 - 15
            }
            else if (label.compare(4,6,"STRY_E") == 0 ) 
            {
               fTypeMap[lbl] = CHA_L1_STR_YE;
               channum = atoi(label.substr(14).c_str());
               fParameterMap[lbl] = channum;                 // Charissa strip number 0 - 15
            } 
            else if (label.compare(4,6,"STRY_T") == 0 ) 
            {
               fTypeMap[lbl] = CHA_L1_STR_YT;
               channum = atoi(label.substr(14).c_str());
               fParameterMap[lbl] = channum;                 // Charissa strip number 0 - 15
            }
         }
         else if (label.compare(5,2,"L2") == 0) {
            if (label.compare(8,6,"STRX_E") == 0 ) 
            {
               fTypeMap[lbl] = CHA_L2_STR_XE;
               channum = atoi(label.substr(14).c_str());
               fParameterMap[lbl] = channum;                 // Charissa strip number 0 - 15
            } 
            else if (label.compare(8,6,"STRX_T") == 0 ) 
            {
               fTypeMap[lbl] = CHA_L2_STR_XT;
               channum = atoi(label.substr(14).c_str());
               fParameterMap[lbl] = channum;                 // Charissa strip number 0 - 15
            }
            else if (label.compare(4,6,"STRY_E") == 0 ) 
            {
               fTypeMap[lbl] = CHA_L2_STR_YE;
               channum = atoi(label.substr(14).c_str());
               fParameterMap[lbl] = channum;                 // Charissa strip number 0 - 15
            } 
            else if (label.compare(4,6,"STRY_T") == 0 ) 
            {
               fTypeMap[lbl] = CHA_L2_STR_YT;
               channum = atoi(label.substr(14).c_str());
               fParameterMap[lbl] = channum;                 // Charissa strip number 0 - 15
            }
         }
			else if (label.compare(5,5,"CSI_E") == 0 ) 
			{
				fTypeMap[lbl] = CHA_CSI_E;
				fParameterMap[lbl] = 1;                          // Charissa CsI number 1
			} 
			else if (label.compare(5,5,"CSI_T") == 0 ) 
			{
				fTypeMap[lbl] = CHA_CSI_T;
				fParameterMap[lbl] = 1;                          // Charissa CsI number 1
			} 
			else 
			{
				cout << "TCharissa::Init() : problem reading Charissa label -> " << label << endl;
				status = false;
			}
		}
	} 

	return status;
}



bool TCharissa::Is(UShort_t lbl, Short_t val)
{
	Int_t det;
	bool result = false;

	switch (fTypeMap[lbl]) 
	{
    
		case CHA_L1_STR_XE :
		{  
			//cout<<  "- ---------< STR X E >------------------!\n";
			det = atoi(fLabelMap[lbl].substr(3,1).c_str());
			fCharissaData->SetCharissaLayer1StripXEDetectorNbr(det);
			fCharissaData->SetCharissaLayer1StripXEStripNbr(fParameterMap[lbl]);
			fCharissaData->SetCharissaLayer1StripXEEnergy(val);
			fCharissaData->SetCharissaLayer1StripXTDetectorNbr(det);
			fCharissaData->SetCharissaLayer1StripXTStripNbr(fParameterMap[lbl]);
			fCharissaData->SetCharissaLayer1StripXTTime(0);
			result = true;
			break;
		}
     
		case CHA_L1_STR_YE :
		{  
			//cout<<  "- ---------< STR X E >------------------!\n";
			det = atoi(fLabelMap[lbl].substr(3,1).c_str());
			fCharissaData->SetCharissaLayer1StripYEDetectorNbr(det);
			fCharissaData->SetCharissaLayer1StripYEStripNbr(fParameterMap[lbl]);
			fCharissaData->SetCharissaLayer1StripYEEnergy(val);
			fCharissaData->SetCharissaLayer1StripYTDetectorNbr(det);
			fCharissaData->SetCharissaLayer1StripYTStripNbr(fParameterMap[lbl]);
			fCharissaData->SetCharissaLayer1StripYTTime(0);
			result = true;
			break;
		}
     
		case CHA_L2_STR_XE :
		{  
			//cout<<  "- ---------< STR X E >------------------!\n";
			det = atoi(fLabelMap[lbl].substr(3,1).c_str());
			fCharissaData->SetCharissaLayer2StripXEDetectorNbr(det);
			fCharissaData->SetCharissaLayer2StripXEStripNbr(fParameterMap[lbl]);
			fCharissaData->SetCharissaLayer2StripXEEnergy(val);
			fCharissaData->SetCharissaLayer2StripXTDetectorNbr(det);
			fCharissaData->SetCharissaLayer2StripXTStripNbr(fParameterMap[lbl]);
			fCharissaData->SetCharissaLayer2StripXTTime(0);
			result = true;
			break;
		}
     
		case CHA_L2_STR_YE :
		{  
			//cout<<  "- ---------< STR X E >------------------!\n";
			det = atoi(fLabelMap[lbl].substr(3,1).c_str());
			fCharissaData->SetCharissaLayer2StripYEDetectorNbr(det);
			fCharissaData->SetCharissaLayer2StripYEStripNbr(fParameterMap[lbl]);
			fCharissaData->SetCharissaLayer2StripYEEnergy(val);
			fCharissaData->SetCharissaLayer2StripYTDetectorNbr(det);
			fCharissaData->SetCharissaLayer2StripYTStripNbr(fParameterMap[lbl]);
			fCharissaData->SetCharissaLayer2StripYTTime(0);
			result = true;
			break;
		}
    
		case CHA_CSI_E :
		{  
			//cout<<  "- ---------<  CSI E  >------------------!\n";
			det = atoi(fLabelMap[lbl].substr(3,1).c_str());
			fCharissaData->SetCharissaCsIEDetectorNbr(det);
			fCharissaData->SetCharissaCsIECristalNbr(fParameterMap[lbl]);
			fCharissaData->SetCharissaCsIEEnergy(val);
			fCharissaData->SetCharissaCsITDetectorNbr(det);
			fCharissaData->SetCharissaCsITCristalNbr(fParameterMap[lbl]);
			fCharissaData->SetCharissaCsITTime(0);
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



bool TCharissa::Treat()
{
	return true;
}



void TCharissa::InitBranch(TTree *tree)
{
   tree->Branch("Charissa", "TCharissaData", &fCharissaData);
}

