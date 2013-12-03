/*****************************************************************************
 * Copyright (C) 2008   this file is part of the Ganil2Root Project          *
 *                                                                           *
 * For the licensing terms see $GANIL2ROOT/Licence                           *
 * For the list of contributors see $GANIL2ROOT/README/CREDITS               *
 *****************************************************************************/

/*****************************************************************************
 * Original Author: L. Lefebvre  contact address: lefebvrl@ipno.in2p3.fr     *
 *                                                                           *
 *                                                                           *
 * Creation Date  : June 2011                                                *
 * Last update    :                                                          *
 *---------------------------------------------------------------------------*
 * Decription: This class is in charged of converting raw data from GANIL    *
 *             format to a ROOT format for the SPEG drift chamber detector   *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Comment:                                                                  *
 *                                                                           *
 *****************************************************************************/
#include "TSpegDC.h"

#include <string>
#include <cstdlib>
using namespace std;


ClassImp(TSpegDC)

TSpegDC::TSpegDC()
{
   // Default constructor
   fSpegDCData    = new TSpegDCData();
}



TSpegDC::~TSpegDC()
{
   delete fSpegDCData;
}



bool TSpegDC::Clear()
{
   fSpegDCData->Clear();

   return true;
}



bool TSpegDC::Init(GDataParameters *params){
   Int_t channum;
   Int_t nbParams = params->GetNbParameters();
   bool status = false;

   for (Int_t index = 0; index < nbParams; index++) {
       Int_t lbl    = params->GetLabel(index);
       string label = params->GetParName(index);
         //    cout << index << "  " << lbl << "  " << label << "  " << fLabelMap[lbl] << endl;
       
	if (label.compare(0,1,"S") == 0 ) 
	{ 
		status = true;
		fLabelMap[lbl]	 = label;
		if (label.compare(1,3,"11_") == 0 ) 
		{
			fTypeMap[lbl] = DC_Strip11;
			channum = atoi(label.substr(4).c_str());
			fParameterMap[lbl] = channum;                 //CDM 11 signals 1-128 
        	}
		else if (label.compare(1,3,"12_") == 0)
		{
			fTypeMap[lbl] = DC_Strip12;
			channum = atoi(label.substr(4).c_str());
			fParameterMap[lbl] = channum;                 //CDM 12 signals 1-128 		
		} 

		else if (label.compare(1,3,"21_") == 0)
		{
			fTypeMap[lbl] = DC_Strip21;
			channum = atoi(label.substr(4).c_str());
			fParameterMap[lbl] = channum;                 //CDM 21 signals 1-128 		
		} 

		else if (label.compare(1,3,"22_") == 0)
		{
			fTypeMap[lbl] = DC_Strip22;
			channum = atoi(label.substr(4).c_str());
			fParameterMap[lbl] = channum;                 //CDM 22 signals 1-128 		
		}

		else 
		{
			cout << "TSpeg::Init() : problem reading SPEG label -> " << label << endl;
			status = false;
		} 
	}
       else if(label.compare(0,4,"EFIL") == 0 ) {
          if (label.compare(4,2,"11") == 0) {
             fTypeMap[lbl]  = DC_efil11;
             fLabelMap[lbl] = label;
             status = true;
          }
          else if (label.compare(4,2,"12") == 0) {
             fTypeMap[lbl]  = DC_efil12;
             fLabelMap[lbl] = label;
             status = true;
          }
          else if (label.compare(4,2,"21") == 0) {
             fTypeMap[lbl]  = DC_efil21;
             fLabelMap[lbl] = label;
             status = true;
          }
          else if (label.compare(4,2,"22") == 0) {
             fTypeMap[lbl]  = DC_efil22;
             fLabelMap[lbl] = label;
             status = true;
          }
	  else 
	  {
		cout << "TSpeg::Init() : problem reading SPEG label -> " << label << endl;
		status = false;
	   }
       } 
       else if(label.compare(0,6,"TPLFIL") == 0 ) {
if (label.compare(6,2,"11") == 0) {
             fTypeMap[lbl]  = DC_tplfil11;
             fLabelMap[lbl] = label;
             status = true;
          }
          else if (label.compare(6,2,"12") == 0) {
             fTypeMap[lbl]  = DC_tplfil12;
             fLabelMap[lbl] = label;
             status = true;
          }
          else if (label.compare(6,2,"21") == 0) {
             fTypeMap[lbl]  = DC_tplfil21;
             fLabelMap[lbl] = label;
             status = true;
          }
          else if (label.compare(6,2,"22") == 0) {
             fTypeMap[lbl]  = DC_tplfil22;
             fLabelMap[lbl] = label;
             status = true;
          }
	  else 
	  {
		cout << "TSpeg::Init() : problem reading SPEG label -> " << label << endl;
		status = false;
	   }
       } 

       else if(label.compare(0,5,"TEMPS") == 0 ) {
if (label.compare(5,2,"11") == 0) {
             fTypeMap[lbl]  = DC_TEMPS11;
             fLabelMap[lbl] = label;
             status = true;
          }
          else if (label.compare(5,2,"12") == 0) {
             fTypeMap[lbl]  = DC_TEMPS12;
             fLabelMap[lbl] = label;
             status = true;
          }
          else if (label.compare(5,2,"21") == 0) {
             fTypeMap[lbl]  = DC_TEMPS21;
             fLabelMap[lbl] = label;
             status = true;
          }
          else if (label.compare(5,2,"22") == 0) {
             fTypeMap[lbl]  = DC_TEMPS22;
             fLabelMap[lbl] = label;
             status = true;
          }
	  else 
	  {
		cout << "TSpeg::Init() : problem reading SPEG label -> " << label << endl;
		status = false;
	   }
       }
   }   
   
   return status;
}

bool TSpegDC::Is(UShort_t lbl, Short_t val)
{
   Int_t det;
   bool result = false;

  switch (fTypeMap[lbl]) {
    
    case DC_Strip11 :{  
     // cout<<  "- ---------< SpegDC 11 >------------------!\n";
      det = atoi(fLabelMap[lbl].substr(1,2).c_str());
      fSpegDCData->SetSpegDCDetNbr11(det);
      fSpegDCData->SetSpegDCStripNbr11(fParameterMap[lbl]);
      fSpegDCData->SetSpegDCEnergy11(val);
      result = true;
      break;
    }

    case DC_Strip12 :{  
     // cout<<  "- ---------< SpegDC 12 >------------------!\n";
      det = atoi(fLabelMap[lbl].substr(1,2).c_str());
      fSpegDCData->SetSpegDCDetNbr12(det);
      fSpegDCData->SetSpegDCStripNbr12(fParameterMap[lbl]);
      fSpegDCData->SetSpegDCEnergy12(val);
      result = true;
      break;
    }

    case DC_Strip21 :{  
    // cout<<  "- ---------< SpegDC 21 >------------------!\n";
      det = atoi(fLabelMap[lbl].substr(1,2).c_str());
      fSpegDCData->SetSpegDCDetNbr21(det);
      fSpegDCData->SetSpegDCStripNbr21(fParameterMap[lbl]);
      fSpegDCData->SetSpegDCEnergy21(val);
      result = true;
      break;
    }

    case DC_Strip22 :{  
     // cout<<  "- ---------< SpegDC 22 >------------------!\n";
      det = atoi(fLabelMap[lbl].substr(1,2).c_str());
      fSpegDCData->SetSpegDCDetNbr22(det);
      fSpegDCData->SetSpegDCStripNbr22(fParameterMap[lbl]);
      fSpegDCData->SetSpegDCEnergy22(val);
      result = true;
      break;
    }

    case DC_efil11 :{  
     // cout<<  "- ---------< Speg efil 11 >------------------!\n";
      det = atoi(fLabelMap[lbl].substr(4,2).c_str());
      fSpegDCData->SetSpegDCEfilDetNbr11(det);
      fSpegDCData->SetSpegDCEfilEnergy11(val);
      result = true;
      break;
    }

    case DC_efil12 :{  
     // cout<<  "- ---------< Speg efil 12 >------------------!\n";
      det = atoi(fLabelMap[lbl].substr(4,2).c_str());
      fSpegDCData->SetSpegDCEfilDetNbr12(det);
      fSpegDCData->SetSpegDCEfilEnergy12(val);
      result = true;
      break;
    }

    case DC_efil21 :{  
     // cout<<  "- ---------< Speg efil 21 >------------------!\n";
      det = atoi(fLabelMap[lbl].substr(4,2).c_str());
      fSpegDCData->SetSpegDCEfilDetNbr21(det);
      fSpegDCData->SetSpegDCEfilEnergy21(val);
      result = true;
      break;
    }

    case DC_efil22 :{  
    //  cout<<  "- ---------< Speg efil 22 >------------------!\n";
      det = atoi(fLabelMap[lbl].substr(4,2).c_str());
      fSpegDCData->SetSpegDCEfilDetNbr22(det);
      fSpegDCData->SetSpegDCEfilEnergy22(val);
      result = true;
      break;
    }

    case DC_tplfil11 :{  
    //  cout<<  "- ---------< Speg tplfil 11 >------------------!\n";
      det = atoi(fLabelMap[lbl].substr(6,2).c_str());
      fSpegDCData->SetSpegDCTplfilDetNbr11(det);
      fSpegDCData->SetSpegDCTplfilTime11(val);
      result = true;
      break;
    }

    case DC_tplfil12 :{  
    //  cout<<  "- ---------< Speg tplfil 12 >------------------!\n";
      det = atoi(fLabelMap[lbl].substr(6,2).c_str());
      fSpegDCData->SetSpegDCTplfilDetNbr12(det);
      fSpegDCData->SetSpegDCTplfilTime12(val);
      result = true;
      break;
    }

    case DC_tplfil21 :{  
    //  cout<<  "- ---------< Speg tplfil 21 >------------------!\n";
      det = atoi(fLabelMap[lbl].substr(6,2).c_str());
      fSpegDCData->SetSpegDCTplfilDetNbr21(det);
      fSpegDCData->SetSpegDCTplfilTime21(val);
      result = true;
      break;
    }

    case DC_tplfil22 :{  
    //  cout<<  "- ---------< Speg tplfil 22 >------------------!\n";
      det = atoi(fLabelMap[lbl].substr(6,2).c_str());
      fSpegDCData->SetSpegDCTplfilDetNbr22(det);
      fSpegDCData->SetSpegDCTplfilTime22(val);
      result = true;
      break;
    }

    case DC_TEMPS11 :{  
    //  cout<<  "- ---------< Speg TEMPS 11 >------------------!\n";
      det = atoi(fLabelMap[lbl].substr(5,2).c_str());
      fSpegDCData->SetSpegDCTfilDetNbr11(det);
      fSpegDCData->SetSpegDCTfilTime11(val);
      result = true;
      break;
    }

    case DC_TEMPS12 :{  
    //  cout<<  "- ---------< Speg TEMPS 12 >------------------!\n";
      det = atoi(fLabelMap[lbl].substr(5,2).c_str());
      fSpegDCData->SetSpegDCTfilDetNbr12(det);
      fSpegDCData->SetSpegDCTfilTime12(val);
      result = true;
      break;
    }

    case DC_TEMPS21 :{  
    //  cout<<  "- ---------< Speg TEMPS 21 >------------------!\n";
      det = atoi(fLabelMap[lbl].substr(5,2).c_str());
      fSpegDCData->SetSpegDCTfilDetNbr21(det);
      fSpegDCData->SetSpegDCTfilTime21(val);
      result = true;
      break;
    }

    case DC_TEMPS22 :{  
    //  cout<<  "- ---------< Speg TEMPS 22 >------------------!\n";
      det = atoi(fLabelMap[lbl].substr(5,2).c_str());
      fSpegDCData->SetSpegDCTfilDetNbr22(det);
      fSpegDCData->SetSpegDCTfilTime22(val);
      result = true;
      break;
    }

    default: {
      //cout<<"TSpegDC::Is --> not a good label"<<lbl<<" "<<fTypeMap[lbl]<<" "<<fLabelMap[lbl]<<endl;
      result = false;
      break;
    }
    
  } // end of switch

  return result;
}



bool TSpegDC::Treat()
{
   return true;
}




void TSpegDC::InitBranch(TTree *tree)
{
   tree->Branch("Speg_DC", "TSpegDCData", &fSpegDCData);
}

