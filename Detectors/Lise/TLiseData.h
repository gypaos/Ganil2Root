/*modified by Iulian 25/02/2011 finished tested */

#ifndef __LISEDATA__
#define __LISEDATA__

//#include <vector>

#include "TObject.h"


// default parameters values used for the validity of the corners in D4 and D6
// if you change the values, use "make" in GRULib library directory to activate the change

#define GHD4min 500
#define GBD4min 500
#define DHD4min 500
#define DBD4min 500

#define GHD4max 15000
#define GBD4max 15000
#define DHD4max 15000
#define DBD4max 15000

#define GHD6min 500                 
#define GBD6min 500
#define DHD6min 500
#define DBD6min 500

#define GHD6max 15000
#define GBD6max 15000
#define DHD6max 15000
#define DBD6max 15000


class TLiseData : public TObject {
 private:

	/* LISE parameter list */
   UShort_t	fE_D4  		;
   UShort_t	fTD4_HF		;
   UShort_t	fGAL41_X	;
   UShort_t	fGAL41_Y	;
   UShort_t	fTGAL1_D4	;
   UShort_t	fGH_D4		;
   UShort_t	fGB_D4		;
   UShort_t	fDH_D4		;
   UShort_t	fDB_D4		;
   UShort_t	fE_D6		;
   UShort_t	fTD6_HF		;
   UShort_t	fGH_D6		;
   UShort_t	fGB_D6		;
   UShort_t	fDH_D6		;
   UShort_t	fDB_D6		;
   UShort_t	fE_GAMMA	;


 public:
   TLiseData();
   virtual ~TLiseData();

   void	Clear();
   void Clear(const Option_t*) {};   
   void Dump() const;

   /////////////////////           GETTERS           ////////////////////////
   // (E)
 
   UShort_t	GetE_D4    ()        {return fE_D4    ;}
   UShort_t	GetTD4_HF  ()        {return fTD4_HF  ;}
   UShort_t	GetGAL41_X ()        {return fGAL41_X ;}
   UShort_t	GetGAL41_Y ()        {return fGAL41_Y ;}
   UShort_t	GetTGAL1_D4()        {return fTGAL1_D4;}
   UShort_t	GetGH_D4   ()        {return fGH_D4   ;}
   UShort_t	GetGB_D4   ()        {return fGB_D4   ;}
   UShort_t	GetDH_D4   ()        {return fDH_D4   ;}
   UShort_t	GetDB_D4   ()        {return fDB_D4   ;}
   UShort_t	GetE_D6    ()        {return fE_D6    ;}
   UShort_t	GetTD6_HF  ()        {return fTD6_HF  ;}
   UShort_t	GetGH_D6   ()        {return fGH_D6   ;}
   UShort_t	GetGB_D6   ()        {return fGB_D6   ;}
   UShort_t	GetDH_D6   ()        {return fDH_D6   ;}
   UShort_t	GetDB_D6   ()        {return fDB_D6   ;}
   UShort_t	GetE_GAMMA ()        {return fE_GAMMA ;}

				/* Calibrate the lise parameters */
				/*  */
   Float_t	GetE_D4_c			(Float_t a, Float_t b) { return a*Float_t(fE_D4    )+b;}     
   Float_t	GetTD4_HF_c		(Float_t a, Float_t b) { return a*Float_t(fTD4_HF  )+b;}     
   Float_t	GetGAL41_X_c	(Float_t a, Float_t b) { return a*Float_t(fGAL41_X )+b;}
   Float_t	GetGAL41_Y_c	(Float_t a, Float_t b) { return a*Float_t(fGAL41_Y )+b;}
   Float_t	GetTGAL1_D4_c	(Float_t a, Float_t b) { return a*Float_t(fTGAL1_D4)+b;}
   Float_t	GetGH_D4_c		(Float_t a, Float_t b) { return a*Float_t(fGH_D4   )+b;}
   Float_t	GetGB_D4_c		(Float_t a, Float_t b) { return a*Float_t(fGB_D4   )+b;}
   Float_t	GetDH_D4_c		(Float_t a, Float_t b) { return a*Float_t(fDH_D4   )+b;}
   Float_t	GetDB_D4_c		(Float_t a, Float_t b) { return a*Float_t(fDB_D4   )+b;}
   Float_t	GetE_D6_c			(Float_t a, Float_t b) { return a*Float_t(fE_D6    )+b;}
   Float_t	GetTD6_HF_c		(Float_t a, Float_t b) { return a*Float_t(fTD6_HF  )+b;}
   Float_t	GetGH_D6_c		(Float_t a, Float_t b) { return a*Float_t(fGH_D6   )+b;}
   Float_t	GetGB_D6_c		(Float_t a, Float_t b) { return a*Float_t(fGB_D6   )+b;}
   Float_t	GetDH_D6_c		(Float_t a, Float_t b) { return a*Float_t(fDH_D6   )+b;}
   Float_t	GetDB_D6_c		(Float_t a, Float_t b) { return a*Float_t(fDB_D6   )+b;}
   Float_t	GetE_GAMMA_c	(Float_t a, Float_t b) { return a*Float_t(fE_GAMMA )+b;}

   /////////////////////           SETTERS           ////////////////////////
   // (E)
   void	SetE_D4    (UShort_t E)     {fE_D4    = E;}
   void	SetTD4_HF  (UShort_t E)     {fTD4_HF  = E;}
   void	SetGAL41_X (UShort_t E)     {fGAL41_X = E;}
   void	SetGAL41_Y (UShort_t E)     {fGAL41_Y = E;}
   void	SetTGAL1_D4(UShort_t E)     {fTGAL1_D4= E;}
   void	SetGH_D4   (UShort_t E)     {fGH_D4   = E;}
   void	SetGB_D4   (UShort_t E)     {fGB_D4   = E;}
   void	SetDH_D4   (UShort_t E)     {fDH_D4   = E;}
   void	SetDB_D4   (UShort_t E)     {fDB_D4   = E;}
   void	SetE_D6    (UShort_t E)     {fE_D6    = E;}
   void	SetTD6_HF  (UShort_t E)     {fTD6_HF  = E;}
   void	SetGH_D6   (UShort_t E)     {fGH_D6   = E;}
   void	SetGB_D6   (UShort_t E)     {fGB_D6   = E;}
   void	SetDH_D6   (UShort_t E)     {fDH_D6   = E;}
   void	SetDB_D6   (UShort_t E)     {fDB_D6   = E;}
   void	SetE_GAMMA (UShort_t E)     {fE_GAMMA = E;}
   

	/* Global Setters for the D4 and D6 parameters*/
   void SetD4(UShort_t E_D4,
	 						UShort_t T_D4_HF,
							UShort_t E_GAL_X,
							UShort_t E_GAL_Y,
							UShort_t T_GAL_HF,
							UShort_t E_XYD4_GH,
							UShort_t E_XYD4_GB,
							UShort_t E_XYD4_DH,
							UShort_t E_XYD4_DB, 
							UShort_t E_GAMMA);
   void SetD6(UShort_t E_D6,
	 						UShort_t T_D6_HF,
							UShort_t E_XYD6_GH,
							UShort_t E_XYD6_GB,
							UShort_t E_XYD6_DH,
							UShort_t E_XYD6_DB);


		/* more complex functions */

		/* test the validity for the corners of D4 XY detector. Return 0 if event is not valid, returns the sum of the corners if the event is valid. Generally not relevant for the end user */
		Int_t TestXY_D4(UShort_t d4_dh_min=GHD4min, 
										UShort_t d4_db_min=GBD4min, 
										UShort_t d4_gh_min=DHD4min, 
										UShort_t d4_gb_min=DBD4min, 
										UShort_t d4_dh_max=GHD4max, 
										UShort_t d4_db_max=GBD4max, 
										UShort_t d4_gh_max=DHD4max, 
										UShort_t d4_gb_max=DBD4max);    

		/* test the validity for the corners of D6 XY detector. Return 0 if event is not valid, returns the sum of the corners if the event is valid. Generally not relevant for the end user */
		Int_t TestXY_D6(UShort_t d6_dh_min=GHD6min, 
										UShort_t d6_db_min=GBD6min, 
										UShort_t d6_gh_min=DHD6min, 
										UShort_t d6_gb_min=DBD6min,
										UShort_t d6_dh_max=GHD6max, 
										UShort_t d6_db_max=GBD6max, 
										UShort_t d6_gh_max=DHD6max, 
										UShort_t d6_gb_max=DBD6max);  	

		/* Returns the X from the XY detector in D4 (DH+DB-GH-GB)/sum+1.  The valid events have this parameter between 0 and 2. Invalid events will be at 2  */
		Float_t GetX_D4(UShort_t d4_dh_min=GHD4min, 
										UShort_t d4_db_min=GBD4min, 
										UShort_t d4_gh_min=DHD4min, 
										UShort_t d4_gb_min=DBD4min,
										UShort_t d4_dh_max=GHD4max, 
										UShort_t d4_db_max=GBD4max, 
										UShort_t d4_gh_max=DHD4max, 
										UShort_t d4_gb_max=DBD4max);

		/* Returns the Y from the XY detector in D4 (DH+GH-DB-GB)/sum+1.  The valid events have this parameter between 0 and 2. Invalid events will be at 2  */
		Float_t GetY_D4(UShort_t d4_dh_min=GHD4min, 
										UShort_t d4_db_min=GBD4min, 
										UShort_t d4_gh_min=DHD4min, 
										UShort_t d4_gb_min=DBD4min,
										UShort_t d4_dh_max=GHD4max, 
										UShort_t d4_db_max=GBD4max, 
										UShort_t d4_gh_max=DHD4max, 
										UShort_t d4_gb_max=DBD4max);

		/* Returns the X from the XY detector in D6 (DH+DB-GH-GB)/sum+1.  The valid events have this parameter between 0 and 2. Invalid events will be at 2  */			
		Float_t GetX_D6(UShort_t d6_dh_min=GHD6min, 
										UShort_t d6_db_min=GBD6min, 
										UShort_t d6_gh_min=DHD6min, 
										UShort_t d6_gb_min=DBD6min,
										UShort_t d6_dh_max=GHD6max, 
										UShort_t d6_db_max=GBD6max, 
										UShort_t d6_gh_max=DHD6max, 
										UShort_t d6_gb_max=DBD6max); 		
		
		/* Returns the Y from the XY detector in D6 (DH+GH-DB-GB)/sum+1.  The valid events have this parameter between 0 and 2. Invalid events will be at 2  */
		Float_t GetY_D6(UShort_t d6_dh_min=GHD6min,
										UShort_t d6_db_min=GBD6min, 
										UShort_t d6_gh_min=DHD6min, 
										UShort_t d6_gb_min=DBD6min,
										UShort_t d6_dh_max=GHD6max, 
										UShort_t d6_db_max=GBD6max, 
										UShort_t d6_gh_max=DHD6max, 
										UShort_t d6_gb_max=DBD6max); 		

   ClassDef(TLiseData,1)  // TLiseData structure
};

#endif
