// modified by Iulian 25/02/2011 finished tested
#include <iostream>
using namespace std;

#include "TLiseData.h"


ClassImp(TLiseData)

TLiseData::TLiseData()
{
   // Default constructor

   // (E)
  Clear();


}



TLiseData::~TLiseData()
{
}



void TLiseData::Clear()
{
  fE_D4		 = 0;
  fTD4_HF	 = 0;
  fGAL41_X = 0;
  fGAL41_Y = 0;
  fTGAL1_D4= 0;
  fGH_D4	 = 0;
  fGB_D4	 = 0;
  fDH_D4	 = 0;
  fDB_D4	 = 0;
  fE_D6		 = 0;
  fTD6_HF	 = 0;
  fGH_D6	 = 0;
  fGB_D6	 = 0;
  fDH_D6	 = 0;
  fDB_D6	 = 0;
  fE_GAMMA = 0;
}



void TLiseData::Dump() const
{
   cout << "XXXXXXXXXXXXXXXXXXXXXXXX Dumping Lise Event XXXXXXXXXXXXXXXXX" << endl;
   cout << " D4 parameter values : \n" ;
   cout << " TD4_HF		= " << fTD4_HF  ;
   cout << " E_D4			= " << fE_D4		;
   cout << " GH_D4		= " << fGH_D4		;
   cout << " GB_D4		= " << fGB_D4		;
   cout << " DH_D4		= " << fDH_D4		;
   cout << " DB_D4		= " << fDB_D4		;
   cout << " GAL41_X	= " << fGAL41_X	;
   cout << " GAL41_Y	= " << fGAL41_Y	;
   cout << " E_GAMMA	= " << fE_GAMMA	;

   cout<<" D6 parameter values: \n"  ;
   cout << " TD6_HF=  "		<< fTD6_HF;
   cout << " E_D6  =  "		<< fE_D6	;
   cout << " GH_D6 =  "		<< fGH_D6	;
   cout << " GB_D6 =  "		<< fGB_D6	;
   cout << " DH_D6 =  "		<< fDH_D6	;
   cout << " DB_D6 =  "		<< fDB_D6	;


}

Int_t TLiseData::TestXY_D4 (UShort_t d4_dh_min, 
														UShort_t d4_db_min, 
														UShort_t d4_gh_min, 
														UShort_t d4_gb_min, 
														UShort_t d4_dh_max, 
														UShort_t d4_db_max, 
														UShort_t d4_gh_max, 
														UShort_t d4_gb_max)
{
  if(  (fGH_D4<d4_gh_min) || 
       (fGB_D4<d4_gb_min) || 
       (fDH_D4<d4_dh_min) || 
       (fDB_D4<d4_db_min) ){
    return 0;
  }

  if(  (fGH_D6>d4_gh_max) || 
       (fGB_D6>d4_gb_max) || 
       (fDH_D6>d4_dh_max) || 
       (fDB_D6>d4_db_max) ){
    return 0;
  }

  return Int_t(fDH_D4)+Int_t(fGH_D4)+Int_t(fDB_D4)+Int_t(fGB_D4);
}

Int_t TLiseData::TestXY_D6 (UShort_t d6_dh_min, 
														UShort_t d6_db_min, 
														UShort_t d6_gh_min, 
														UShort_t d6_gb_min, 
														UShort_t d6_dh_max, 
														UShort_t d6_db_max, 
														UShort_t d6_gh_max, 
														UShort_t d6_gb_max)
{
  if(  (fGH_D6<d6_gh_min) || 
       (fGB_D6<d6_gb_min) || 
       (fDH_D6<d6_dh_min) || 
       (fDB_D6<d6_db_min) ){
    return 0;	            
  }		            
		            
  if(  (fGH_D6>d6_gh_max) || 
       (fGB_D6>d6_gb_max) || 
       (fDH_D6>d6_dh_max) || 
       (fDB_D6>d6_db_max) ){
    return 0;
  }

  return Int_t(fDH_D6)+Int_t(fGH_D6)+Int_t(fDB_D6)+Int_t(fGB_D6);
}


Float_t TLiseData::GetX_D4 (UShort_t d4_dh_min, 
														UShort_t d4_db_min, 
														UShort_t d4_gh_min, 
														UShort_t d4_gb_min, 
														UShort_t d4_dh_max, 
														UShort_t d4_db_max, 
														UShort_t d4_gh_max, 
														UShort_t d4_gb_max)
{
  Int_t sum=TestXY_D4( d4_dh_min,  d4_db_min,  d4_gh_min,  d4_gb_min,  d4_dh_max,  d4_db_max,  d4_gh_max,  d4_gb_max);
  if(sum>0){
    return 1.+(Float_t(fDH_D4)+Float_t(fDB_D4)-Float_t(fGH_D4)-Float_t(fGB_D4))/Float_t(sum);
  }
  return 2.;
}



Float_t TLiseData::GetY_D4 (UShort_t d4_dh_min, 
														UShort_t d4_db_min, 
														UShort_t d4_gh_min, 
														UShort_t d4_gb_min, 
														UShort_t d4_dh_max, 
														UShort_t d4_db_max, 
														UShort_t d4_gh_max, 
														UShort_t d4_gb_max)
{
  Int_t sum=TestXY_D4( d4_dh_min,  d4_db_min,  d4_gh_min,  d4_gb_min,  d4_dh_max,  d4_db_max,  d4_gh_max,  d4_gb_max);
  if(sum>0){
    return 1.+(Float_t(fDH_D4)+Float_t(fGH_D4)-Float_t(fDB_D4)-Float_t(fGB_D4))/Float_t(sum);
  }
  return 2.;
}


Float_t TLiseData::GetX_D6 (UShort_t d6_dh_min, 
														UShort_t d6_db_min, 
														UShort_t d6_gh_min, 
														UShort_t d6_gb_min, 
														UShort_t d6_dh_max, 
														UShort_t d6_db_max, 
														UShort_t d6_gh_max, 
														UShort_t d6_gb_max)
{
  Int_t sum=TestXY_D6( d6_dh_min,  d6_db_min,  d6_gh_min,  d6_gb_min,  d6_dh_max,  d6_db_max,  d6_gh_max,  d6_gb_max);
  if(sum>0){
    return 1.+(Float_t(fDH_D6)+Float_t(fDB_D6)-Float_t(fGH_D6)-Float_t(fGB_D6))/Float_t(sum);
  }
  return 2.;
}

Float_t TLiseData::GetY_D6 (UShort_t d6_dh_min, 
														UShort_t d6_db_min, 
														UShort_t d6_gh_min, 
														UShort_t d6_gb_min, 
														UShort_t d6_dh_max, 
														UShort_t d6_db_max, 
														UShort_t d6_gh_max, 
														UShort_t d6_gb_max)
{
  Int_t sum=TestXY_D6( d6_dh_min,  d6_db_min,  d6_gh_min,  d6_gb_min,  d6_dh_max,  d6_db_max,  d6_gh_max,  d6_gb_max);
  if(sum>0){
    return 1.+(Float_t(fDH_D6)+Float_t(fGH_D6)-Float_t(fDB_D6)-Float_t(fGB_D6))/Float_t(sum);
  }
  return 2.;

}

 // setter for all D4 parameters
void TLiseData::SetD4(UShort_t E_D4,
											UShort_t TD4_HF,
											UShort_t GAL41_X,
											UShort_t GAL41_Y,
											UShort_t TGAL1_D4,
											UShort_t GH_D4,
											UShort_t GB_D4,
											UShort_t DH_D4,
											UShort_t DB_D4, 
											UShort_t E_GAMMA) 
{
  
  fE_D4			=	E_D4   ;
  fTD4_HF		=	TD4_HF ;
  fGAL41_X	=	GAL41_X;
  fGAL41_Y	=	GAL41_Y;
  fTGAL1_D4	=	TGAL1_D4;
  fGH_D4		=	GH_D4  ;
  fGB_D4		=	GB_D4  ;
  fDH_D4		=	DH_D4  ;
  fDB_D4		=	DB_D4  ;
  fE_GAMMA	=	E_GAMMA;
}


 // setter for all D6 parameters
void TLiseData::SetD6(UShort_t E_D6,
											UShort_t TD6_HF,
											UShort_t GH_D6,
											UShort_t GB_D6,
											UShort_t DH_D6,
											UShort_t DB_D6)
{
  fE_D6			= E_D6		;
  fTD6_HF		= TD6_HF	;
  fGH_D6		= GH_D6		;
  fGB_D6		= GB_D6		;
  fDH_D6		= DH_D6		;
  fDB_D6		= DB_D6		;
}

