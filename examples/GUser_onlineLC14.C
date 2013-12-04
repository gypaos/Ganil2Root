// File : GUser.C
// Author: Luc Legeard
//////////////////////////////////////////////////////////////////////////////
//
// Class GUser
//
// Class for User treatment
//
////////////////////////////////////////////////////////////////////////////

// ---------------------------------------------------------------------------
// ***************************************************************************
// *                                                                         *
// *   This program is free software; you can redistribute it and/or modify  *
// *   it under the terms of the GNU General Public License as published by  *
// *   the Free Software Foundation; either version 2 of the License, or     *
// *   (at your option) any later version.                                   *
// *                                                                         *
// **************************************************************************/


#include "./GUser_onlineLC14.h"

// ROOT headers
#include "TROOT.h"
#include "TH1F.h"
#include "TString.h"

// NPTOOL headers
#include "NPOptionManager.h"
#include "TTiaraHyballPhysics.h"
#include "TMust2Physics.h"

// C++ headers
#include <iostream>
#include <fstream>
#include <string>
using namespace std;


ClassImp (GUser); 

GUser::GUser (GDevice* _fDevIn, GDevice* _fDevOut)
{ 
	// Constructor/initialisator of Acquisition object 
   // entry:
   // - Input Device
   // - Output Device
   fDevIn   = _fDevIn;
   fDevOut  = _fDevOut;

   // instantiate detector objects
   fMust2    = new TMust2();
   fCATS     = new TCATS();
   fExogam   = new TExogam();
   fTrigger	 = new TTrigger();
   fTac      = new TTac();
   fPlastic  = new TPlastic();
   fLise     = new TLise();
   fTiaraHyball  = new TTiaraHyball();
   fTiaraBarrel  = new TTiaraBarrel();

   MySpectraList = GetSpectra();
	cout << "Spectra done" << endl;  
}



GUser::~GUser()  
{
   // Destructor of class GUser
   delete fMust2;
   delete fCATS;
   delete fExogam;
   delete fTrigger;
	delete fTac;
	delete fPlastic;
   delete fLise;
   delete fTiaraHyball;
   delete fTiaraBarrel;

	gROOT->cd();
}



void GUser::InitUser()
{
   // Initialisation for global  user treatement

   cout<<  "- ---------< Init User  >------------------!\n";
   cout << "+++++ Init NPOption Manager" << endl;
   // -GH for generating histos
   // -CH for checking histos
   // -C for calibration files
   string argument = "-D ./e628.detector -GH -CH -C e628.calib";
   NPOptionManager *myOptionManager = NPOptionManager::getInstance(argument);
   string detectorFile = myOptionManager->GetDetectorFile();

   cout << "+++++ Init Detector Manager" << endl;
   fMyDetector = new DetectorManager();
   fMyDetector->ReadConfigurationFile(detectorFile);

   cout << "+++++ Register detector spectra to viGru" << endl;
   vector < map < vector <TString>, TH1* > > mySpectra = fMyDetector->GetSpectra();
   for (unsigned int i = 0; i < mySpectra.size(); ++i) {   // loop on nySpectra
      map<vector <TString>, TH1*>::iterator it;
      for (it = mySpectra[i].begin(); it != mySpectra[i].end(); ++it) {   // loop on map
         GetSpectra()->AddSpectrum(it->second, it->first[0]);
      } // end loop on map
   } // end loop on nySpectra


   // connect data objects to the physics
   // need to be done detector by detector
   ((TMust2Physics*)       fMyDetector->GetDetector("MUST2"))       -> SetRawDataPointer(fMust2       -> GetMust2Data());
   ((TTiaraHyballPhysics*) fMyDetector->GetDetector("TiaraHyball")) -> SetRawDataPointer(fTiaraHyball -> GetTiaraHyballData());
}



void GUser::InitUserRun()
{
   // Initialisation for user treatemeant for each  run  
   // For specific user treatement

   cout << "Init run" << endl;

	fMust2->Init(GetEvent()->GetDataParameters());
	cout << "End Init Must2"<<endl;

	fCATS->Init(GetEvent()->GetDataParameters());
	cout << "End Init CATS"<<endl;

	fExogam->Init(GetEvent()->GetDataParameters());
	cout << "End Init Exogam"<<endl;

	fTrigger->Init(GetEvent()->GetDataParameters());
	cout << "End Init Trigg"<<endl;

	fPlastic->Init(GetEvent()->GetDataParameters());
	cout << "End Init Plastic"<<endl;

	fLise->Init(GetEvent()->GetDataParameters());
	cout << "End Init Lise"<<endl;

	fTac->Init(GetEvent()->GetDataParameters());
	cout << "End Init Tac"<<endl;

	fTiaraHyball->Init(GetEvent()->GetDataParameters());
   cout << "End Init Tiara/Hyball"<<endl;

	fTiaraBarrel->Init(GetEvent()->GetDataParameters());
   cout << "End Init Tiara/Barrel"<<endl;

   cout << "End Init run"<<endl;



   // keep track of read labels
   ofstream out_rej,out_acc;
   out_acc.open("label_accepted.dat");
   out_rej.open("label_rejected.dat");

   for (Int_t i = 0; i < GetEventArraySize(); i++) {
      bool included = false;

      if (fMust2->GetLabelMap(GetDataParameters()->GetLabel(i)) == GetDataParameters()->GetParName(i)){
         included = true;
      }
      else if (fCATS->GetLabelMap(GetDataParameters()->GetLabel(i)) == GetDataParameters()->GetParName(i)) {
         included = true;
      }
      else if (fExogam->GetLabelMap(GetDataParameters()->GetLabel(i)) == GetDataParameters()->GetParName(i)) {
         included = true;
      }
      else if(fTac->GetLabelMap(GetDataParameters()->GetLabel(i)) == GetDataParameters()->GetParName(i)) {
         included = true;
      }
      else if(fTrigger->GetLabelMap(GetDataParameters()->GetLabel(i)) == GetDataParameters()->GetParName(i)) {
         included = true;
      }
      else if(fLise->GetLabelMap(GetDataParameters()->GetLabel(i)) == GetDataParameters()->GetParName(i)) {
         included = true;
      }
      else if(fPlastic->GetLabelMap(GetDataParameters()->GetLabel(i)) == GetDataParameters()->GetParName(i)) {
         included = true;
      }
      else if(fTiaraHyball->GetLabelMap(GetDataParameters()->GetLabel(i)) == GetDataParameters()->GetParName(i)) {
         included = true;
      }
      else if(fTiaraBarrel->GetLabelMap(GetDataParameters()->GetLabel(i)) == GetDataParameters()->GetParName(i)) {
         included = true;
      }

      if (!included) {
         out_rej << i <<" "<<GetDataParameters()->GetParName(i)<<endl;
      }
      else {
         out_acc << i <<" "<<GetDataParameters()->GetParName(i)<<endl;
      }
   }
   out_rej.close();
   out_acc.close();
}



void GUser::User()
{
   // define boolean variables
	bool bMust2        = false;
	bool bCATS         = false;
   bool bExogam       = false;
	bool bTrigger      = false;
	bool bPlastic      = false;
	bool bLise         = false;
	bool bTac          = false;
   bool bTiaraHyball  = false;
   bool bTiaraBarrel  = false;

   // clear objects
	fMust2        -> Clear();
	fCATS         -> Clear();
   fExogam       -> Clear();
   fTrigger      -> Clear();
   fTac          -> Clear();
   fPlastic      -> Clear();
   fLise         -> Clear();
   fTiaraHyball  -> Clear();
   fTiaraBarrel  -> Clear();

   //////////////////////////////////////////////////
	//     Unpack events & fill raw data objects    //
   //////////////////////////////////////////////////
	int size =  GetEventArrayLabelValueSize()/2;
	for (Int_t i = 0; i < size; i++) {
		if (fMust2->Is(GetEventArrayLabelValue_Label(i),GetEventArrayLabelValue_Value(i))) {
		  bMust2 = true;  // indicate that physical treatment should be performed
		}
      else if (fCATS->Is(GetEventArrayLabelValue_Label(i),GetEventArrayLabelValue_Value(i))) {
		  bCATS = true;  // indicate that physical treatment should be performed
		}
      else if (fExogam->Is(GetEventArrayLabelValue_Label(i),GetEventArrayLabelValue_Value(i))) {
		  bExogam = true;  // indicate that physical treatment should be performed
		}
      else if (fTrigger->Is(GetEventArrayLabelValue_Label(i),GetEventArrayLabelValue_Value(i))) {
		  bTrigger = true;
	   }
      else if (fPlastic->Is(GetEventArrayLabelValue_Label(i),GetEventArrayLabelValue_Value(i))) {
		  bPlastic = true;
	   }
      else if (fLise->Is(GetEventArrayLabelValue_Label(i),GetEventArrayLabelValue_Value(i))) {
		  bLise = true;
	   }
      else if (fTac->Is(GetEventArrayLabelValue_Label(i),GetEventArrayLabelValue_Value(i))) {
		  bTac = true;
	   }
      else if (fTiaraHyball->Is(GetEventArrayLabelValue_Label(i),GetEventArrayLabelValue_Value(i))) {
		  bTiaraHyball = true;
	   }
      else if (fTiaraBarrel->Is(GetEventArrayLabelValue_Label(i),GetEventArrayLabelValue_Value(i))) {
		  bTiaraBarrel = true;
	   }
      else {
            //cout << "not a good label: "<<GetEventArrayLabelValue_Label(i)<<" value: "<<GetEventArrayLabelValue_Value(i)<<endl;
      }
   }

   //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//        Call BuildPhysicalEvent (physical treatment) for each declared detector in the e628.detector file     //
   //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   fMyDetector->BuildSimplePhysicalEvent();
}



void GUser::EndUserRun()
{
	//  end of run ,  executed a end of each run

	cout <<"--------------< End User Run >------------------\n";
    
}

//______________________________________________________________
void GUser::EndUser()
{
  // globlal final end executed a end of runs
  // must be explicitly called! 

	
	cout <<"--------------< End User 1> ------------------\n";
   
	//cout << "End save spectra " << endl;    
    
}
//______________________________________________________________________________

void GUser::InitTTreeUser()
{
	cout << "GUser::InitTTreeUser()" << endl;
	cout << "GUser::InitTTreeUser() -> fTheTree " << fTheTree << endl;

	fMust2        -> InitBranch(fTheTree);
	fCATS         -> InitBranch(fTheTree);
   fExogam       -> InitBranch(fTheTree);
	fTrigger      -> InitBranch(fTheTree);
	fTac          -> InitBranch(fTheTree);
	fPlastic      -> InitBranch(fTheTree);
	fLise         -> InitBranch(fTheTree);
   fTiaraHyball  -> InitBranch(fTheTree);
   fTiaraBarrel  -> InitBranch(fTheTree);

   cout << "End GUser::InitTTreeUser()" << endl;
}
