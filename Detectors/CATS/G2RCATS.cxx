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
 *    + march 2011: Add support for G2R::CATSPhysics from NPTool                 *
 *                                                                           *
 *****************************************************************************/
#include "G2RCATS.h"
#include "G2RDetectorManager.h"
#include "G2RDetectorFactory.h"

#include <cstdlib>
#include <string>
using namespace std;


ClassImp(G2R::CATS)

////////////////////////////////////////////////////////////////////////////////
G2R::CATS::CATS(){
	// Default constructor
	fCATSData    = new TCATSData();
  // Initialise the generic pointer from base class
  m_Data = fCATSData;
}


////////////////////////////////////////////////////////////////////////////////]
G2R::CATS::~CATS(){
	delete fCATSData;
}


////////////////////////////////////////////////////////////////////////////////
bool G2R::CATS::Clear(){
	fCATSData->Clear();
	return true;
}


////////////////////////////////////////////////////////////////////////////////
bool G2R::CATS::Init(DataParameters *params){
  cout << "INIT CATS ?????????? ???????????????????? "<< endl;
	vector<int> channum;
	int nbParams = params->GetNbParameters();
	bool status = false;
  int det;
	for (Int_t index = 0; index < nbParams; index++) {
		Int_t lbl    = params->GetLabel(index);
    string label = params->GetParNameFromIndex(index);

		if (label.compare(0,4,"CATS") == 0 ) { 
			fLabelMap[lbl] = label;
			status = true;
      // fDetectorManager->RegisterLabelToDetector(lbl,"CATS");
      fDetectorManager->RegisterLabelToDetector(lbl,"CATSDetector");
			det = atoi(fLabelMap[lbl].substr(4,1).c_str());
      channum.push_back(det);

      // if (label.compare(6,1,"X") == 0 ) {
      if (label.compare(5,1,"X") == 0 ) {
				fTypeMap[lbl] = CATS_X;
				channum.push_back(atoi(label.substr(7).c_str()));
				fParameterMap[lbl] = channum;					// CATS X signals 1-28
				//cout << fTypeMap[lbl] << "  " << fParameterMap[lbl] << endl;
			} 
			//else if (label.compare(6,1,"Y") == 0 ) {
		else if (label.compare(5,1,"Y") == 0 ) {
				fTypeMap[lbl] = CATS_Y;
				channum.push_back(atoi(label.substr(7).c_str()));
				fParameterMap[lbl] = channum;                 // CATS Y signals 1-28
				//cout << fTypeMap[lbl] << "  " << fParameterMap[lbl] << endl;
			}
      else if(label.compare(6,4,"QFIL") == 0 ){
        fLabelMap[lbl] = label;
        fTypeMap[lbl] = CATS_Q;
      }			
			else {
				cout << "G2R::CATS::Init() : problem reading CATS label -> " << label << endl;
				status = false;
			}
		}
	}   
	return status;
}
////////////////////////////////////////////////////////////////////////////////
bool G2R::CATS::Is(unsigned short lbl, unsigned short val){
	Int_t det;
	bool result = false;

	switch (fTypeMap[lbl]) {
    
		case CATS_X :{  
			//cout<<  "- ---------< CATS X E >------------------!\n";
			fCATSData->SetStripX(fParameterMap[lbl][0],fParameterMap[lbl][1],val);
			result = true;
			break;
		}
    
		case CATS_Y :{  
			//cout<<  "- ---------< CATS Y E >------------------!\n";
      fCATSData->SetStripY(fParameterMap[lbl][0],fParameterMap[lbl][1],val);
      result = true;
      break;
    }

    case CATS_Q :{  
      //cout<<  "- ---------<  CATS Q >------------------!\n";
      fCATSData->SetQ(fParameterMap[lbl][0],val);
      result = true;
    }

		default: {
			//cout<<"G2R::CATS::Is --> not a good label"<<lbl<<" "<<fTypeMap[lbl]<<" "<<fLabelMap[lbl]<<endl;
      result = false;
      break;
		}
    
	} // end of switch

	return result;
}
////////////////////////////////////////////////////////////////////////////////
bool G2R::CATS::Treat(){
   return true;
}
////////////////////////////////////////////////////////////////////////////////
void G2R::CATS::InitBranch(TTree *tree){
   tree->Branch("CATS", "TCATSData", &fCATSData);
   }

////////////////////////////////////////////////////////////////////////////////
//            Construct Method to be pass to the DetectorFactory              //
////////////////////////////////////////////////////////////////////////////////
G2R::VDetector* G2R::CATS::Construct(){
  return (G2R::VDetector*) new G2R::CATS();
}

////////////////////////////////////////////////////////////////////////////////
//            Registering the construct method to the factory                 //
////////////////////////////////////////////////////////////////////////////////
extern "C"{
class proxy_g2r_cats{
  public:
    proxy_g2r_cats(){
      //  G2R::DetectorFactory::getInstance()->AddToken("CATS","CATS");
      //  G2R::DetectorFactory::getInstance()->AddDetector("CATS",G2R::CATS::Construct);
      G2R::DetectorFactory::getInstance()->AddToken("CATSDetector","CATS");
      G2R::DetectorFactory::getInstance()->AddDetector("CATSDetector",G2R::CATS::Construct);
    }
};

proxy_g2r_cats p_g2r_cats;
}

