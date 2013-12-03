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


#include "./GUser_convert.h"

#include "TROOT.h"

#include <iostream>

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
   fSSSD     = new TSSSD();
   fExogam   = new TExogam();
   fTrigger	 = new TTrigger();
   fTac      = new TTac();
   fPlastic  = new TPlastic();
   fChio_an  = new TChio_an();
   fChio_dig = new TChio_dig();
   fLise     = new TLise();
   fVamosFinger  = new TVamosFinger();
   fVamosPlastic = new TVamosPlastic();
   fVamosCHIO    = new TVamosCHIO();
   fVamosDC      = new TVamosDC();
   fMaya         = new TMaya();

   MySpectraList = GetSpectra();
	cout << "Spectra done" << endl;  
}



GUser::~GUser()  
{
   // Destructor of class GUser
   delete fMust2;
   delete fCATS;
   delete fSSSD;
   delete fExogam;
   delete fTrigger;
	delete fTac;
	delete fPlastic;
	delete fChio_an;
	delete fChio_dig;
   delete fLise;
   delete fVamosFinger;
   delete fVamosPlastic;
   delete fVamosCHIO;
   delete fVamosDC;
   delete fMaya;

	gROOT->cd();
}



void GUser::InitUser()
{
  // Initialisation for global  user treatement
 
	cout<<  "- ---------< Init User  >------------------!\n";
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

	fSSSD->Init(GetEvent()->GetDataParameters());
	cout << "End Init SSSD"<<endl;

	fExogam->Init(GetEvent()->GetDataParameters());
	cout << "End Init Exogam"<<endl;

	fTrigger->Init(GetEvent()->GetDataParameters());
	cout << "End Init Trigg"<<endl;

	fPlastic->Init(GetEvent()->GetDataParameters());
	cout << "End Init Plastic"<<endl;

	fChio_an->Init(GetEvent()->GetDataParameters());
	cout << "End Init Chio_an"<<endl;

	fChio_dig->Init(GetEvent()->GetDataParameters());
	cout << "End Init Chio_dig"<<endl;

	fLise->Init(GetEvent()->GetDataParameters());
	cout << "End Init Lise"<<endl;

	fTac->Init(GetEvent()->GetDataParameters());
	cout << "End Init Tac"<<endl;

	fVamosFinger->Init(GetEvent()->GetDataParameters());
	cout << "End Init Vamos Finger"<<endl;

	fVamosPlastic->Init(GetEvent()->GetDataParameters());
	cout << "End Init Vamos Plastic"<<endl;

	fVamosCHIO->Init(GetEvent()->GetDataParameters());
	cout << "End Init Vamos CHIO"<<endl;

	fVamosDC->Init(GetEvent()->GetDataParameters());
	cout << "End Init Vamos DC"<<endl;

	fMaya->Init(GetEvent()->GetDataParameters());
   cout << "End Init Maya"<<endl;

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
      else if (fSSSD->GetLabelMap(GetDataParameters()->GetLabel(i)) == GetDataParameters()->GetParName(i)) {
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
      else if(fChio_an->GetLabelMap(GetDataParameters()->GetLabel(i)) == GetDataParameters()->GetParName(i)) {
         included = true;
      }
      else if(fChio_dig->GetLabelMap(GetDataParameters()->GetLabel(i)) == GetDataParameters()->GetParName(i)) {
         included = true;
      }
      else if(fPlastic->GetLabelMap(GetDataParameters()->GetLabel(i)) == GetDataParameters()->GetParName(i)) {
         included = true;
      }
      else if(fVamosFinger->GetLabelMap(GetDataParameters()->GetLabel(i)) == GetDataParameters()->GetParName(i)) {
         included = true;
      }
      else if(fVamosPlastic->GetLabelMap(GetDataParameters()->GetLabel(i)) == GetDataParameters()->GetParName(i)) {
         included = true;
      }
      else if(fVamosCHIO->GetLabelMap(GetDataParameters()->GetLabel(i)) == GetDataParameters()->GetParName(i)) {
         included = true;
      }
      else if(fVamosDC->GetLabelMap(GetDataParameters()->GetLabel(i)) == GetDataParameters()->GetParName(i)) {
         included = true;
      }
      else if(fMaya->GetLabelMap(GetDataParameters()->GetLabel(i)) == GetDataParameters()->GetParName(i)) {
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
	// the event is presented on two way ( user  can use one or other )
	// 1  - event is a vector of UShor_t* GetEventArray() of fixed size  (GetEventArraySize())
	//      '0's have been included in vector where parameter were not present
	//      GetEventArray_Value(i) return value index i in vector GetEventArray()
	// 2  - event is a vector of a serie of couples  UShor_t/Short_t Label/Value ( GetEventArrayLabelValue()) 
	//      of variable size   GetEventArrayLabelValueSize() and  with a max size of GetEventArrayLabelValueSizeMax()
	//      This vector is often called control event.
	//      The numebers of couple  Label/Value is GetEventArrayLabelValueSize()/2
	//      GetEventArrayLabelValue_Label(i)  return  Label number i in  vector GetEventArrayLabelValue()
	//      GetEventArrayLabelValue_Value(i)  return  Value number  i in  vector GetEventArrayLabelValue()
	//     
	//      Exemple of use of manage index,label,name
	//      GetEvent()->GetDataParameters()->GetLabel("NAME")  return label of parameter with name "NAME"
	//      GetEvent()->GetDataParameters()->GetLabel(index)   return label of parameter with index i (in GetEventArray() vector)
	//      GetEvent()->GetDataParameters()->GetParName(label) return name of parameter with label 'label'
	//      GetEvent()->GetDataParameters()->GetIndex(label)   return index(in GetEventArray() vector) of parameter with label 'label
	//      GetEvent()->GetDataParameters()->GetIndex("NAME")  return index(in GetEventArray() vector) of parameter with name "NAME"

	//The number of sub event is  given byGetEvent()->GetNbofSubEvt()*
	// and timestamps are reacheable with a vector of time stamps given by  GetEvent()->GetTimeStamps();

	
   // define boolean variables
	bool bMust2    = false;
	bool bCATS     = false;
	bool bSSSD     = false;
   bool bExogam   = false;
	bool bTrigger  = false;
	bool bPlastic  = false;
	bool bChio_an  = false;
	bool bChio_dig = false;
	bool bLise     = false;
	bool bTac      = false;
   bool bVamosFinger  = false;
   bool bVamosPlastic = false;
   bool bVamosCHIO    = false;
   bool bVamosDC      = false;
   bool bMaya         = false;

   // clear objects
	fMust2    -> Clear();
	fCATS     -> Clear();
	fSSSD     -> Clear();
   fExogam   -> Clear();
   fTrigger  -> Clear();
   fTac      -> Clear();
   fChio_an  -> Clear();
   fChio_dig -> Clear();
   fPlastic  -> Clear();
   fLise     -> Clear();
   fVamosFinger  -> Clear();
   fVamosPlastic -> Clear();
   fVamosCHIO    -> Clear();
   fVamosDC      -> Clear();
   fMaya         -> Clear();

   ///////////////////////////
	//     Unpack events     //
   ///////////////////////////
	int size =  GetEventArrayLabelValueSize()/2;
	for (Int_t i = 0; i < size; i++) {
		if (fMust2->Is(GetEventArrayLabelValue_Label(i),GetEventArrayLabelValue_Value(i))) {
		  bMust2 = true;  // indicate that physical treatment should be performed
		}
      else if (fCATS->Is(GetEventArrayLabelValue_Label(i),GetEventArrayLabelValue_Value(i))) {
		  bCATS = true;  // indicate that physical treatment should be performed
		}
      else if (fSSSD->Is(GetEventArrayLabelValue_Label(i),GetEventArrayLabelValue_Value(i))) {
		  bSSSD = true;  // indicate that physical treatment should be performed
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
      else if (fChio_an->Is(GetEventArrayLabelValue_Label(i),GetEventArrayLabelValue_Value(i))) {
		  bChio_an = true;
	   }
      else if (fChio_dig->Is(GetEventArrayLabelValue_Label(i),GetEventArrayLabelValue_Value(i))) {
		  bChio_dig = true;
	   }
      else if (fLise->Is(GetEventArrayLabelValue_Label(i),GetEventArrayLabelValue_Value(i))) {
		  bLise = true;
	   }
      else if (fTac->Is(GetEventArrayLabelValue_Label(i),GetEventArrayLabelValue_Value(i))) {
		  bTac = true;
	   }
      else if (fVamosFinger->Is(GetEventArrayLabelValue_Label(i),GetEventArrayLabelValue_Value(i))) {
		  bVamosFinger = true;
	   }
      else if (fVamosPlastic->Is(GetEventArrayLabelValue_Label(i),GetEventArrayLabelValue_Value(i))) {
		  bVamosPlastic = true;
	   }
      else if (fVamosCHIO->Is(GetEventArrayLabelValue_Label(i),GetEventArrayLabelValue_Value(i))) {
		  bVamosCHIO = true;
	   }
      else if (fVamosDC->Is(GetEventArrayLabelValue_Label(i),GetEventArrayLabelValue_Value(i))) {
		  bVamosDC = true;
	   }
      else if (fMaya->Is(GetEventArrayLabelValue_Label(i),GetEventArrayLabelValue_Value(i))) {
		  bMaya = true;
	   }
      else {
            //cout << "not a good label: "<<GetEventArrayLabelValue_Label(i)<<" value: "<<GetEventArrayLabelValue_Value(i)<<endl;
      }
   }
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
	// User method for specfic initialisation of TTree
  // It can be usefull for example multi-hit detections
  // or to have a TTree with only few parameters ( for low compute)
  // to run this method , you have to slect mode 3 in  SetTTreeMode
  // ex : a->SetTTreeMode(3,"/space/MyTTree.root");

	cout<<"GUser::InitTTreeUser()"<<endl;

	cout << "GUser::InitTTreeUser() -> fTheTree " << fTheTree << endl;

	fMust2        -> InitBranch(fTheTree);
	fCATS         -> InitBranch(fTheTree);
	fSSSD         -> InitBranch(fTheTree);
   fExogam       -> InitBranch(fTheTree);
	fTrigger      -> InitBranch(fTheTree);
	fTac          -> InitBranch(fTheTree);
	fChio_an      -> InitBranch(fTheTree);
	fChio_dig     -> InitBranch(fTheTree);
	fPlastic      -> InitBranch(fTheTree);
	fLise         -> InitBranch(fTheTree);
   fVamosFinger  -> InitBranch(fTheTree);
   fVamosPlastic -> InitBranch(fTheTree);
   fVamosCHIO    -> InitBranch(fTheTree);
   fVamosDC      -> InitBranch(fTheTree);
   fMaya         -> InitBranch(fTheTree);

  cout<<"End GUser::InitTTreeUser()"<<endl;
}
