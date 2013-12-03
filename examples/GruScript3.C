//------------------------------------------//
//-------- CONVERSION BOUCLE ---------------//
//------------------------------------------//

void GruScript3(char* runname)
{
	string infile = runname;
	int start_run = infile.find("run_");
	int start_dat = infile.find(".dat");
	int len = start_dat - (start_run+4);

	if( start_run == string::npos || start_dat == string::npos || len < 2 ) {
		cerr << "Cannot understand input filename '" << runname << "'. Stop." << endl;
	} else {
			string rnum = infile.substr(start_run+4, len);
			string outname = string("$(E551)/raw_trees/rawdata_")+rnum+string(".root");
			string sclname = string("$(E551)/raw_trees/scalers_")+rnum+string(".root");

			if(gSystem->FindFile("",outname.c_str())==NULL) {
				//gROOT->ProcessLine(".L $(E551)/dat2raw/GUser.C++"); //!!!!!!!!!!comment for Treatement() !!!!!!!!!!!!!!
				//gROOT->ProcessLine(".L $(E551)/raw_libs/libComplete.so"); //!!!!!!!!!!comment for Treatement() !!!!!!!!!!!!!!

				GTape *file = new GTape(runname);
				file->Open();
				GUser * a= new GUser(file);

				a->EventInit();
				//a->SetSpectraMode(0);
				a->SetUserMode(1);
				file->Rewind();

				a->SetTTreeMode(3, outname.c_str());
				a->SetScalerMode(0, sclname.c_str());

				//a->DoRun(1000);
				a->DoRun();


				file->Close();
				delete (a);
			} else {
				cout << gSystem->FindFile("",outname.c_str()) << " already exists. Skip." << endl ;
			}
		}
	gROOT->Reset();
	//gROOT->ProcessLine(".q");
}

//------------------------------------------//
//-------- CONVERSION SINGLE ---------------//
//------------------------------------------//

void Single(char* runname)
{
	string infile = runname;
	int start_run = infile.find("run_");
	int start_dat = infile.find(".dat");
	int len = start_dat - (start_run+4);

	if( start_run == string::npos || start_dat == string::npos || len < 2 ) {
		cerr << "Cannot understand input filename '" << runname << "'. Stop." << endl;
	} else {
			string rnum = infile.substr(start_run+4, len);
			string outname = string("$(E551)/raw_trees/rawdata_")+rnum+string(".root");
			string sclname = string("$(E551)/raw_trees/scalers_")+rnum+string(".root");

			if(gSystem->FindFile("",outname.c_str())==NULL) {
				gROOT->ProcessLine(".L $(E551)/dat2raw/GUser_convert.C++"); //!!!!!!!!!!comment for Treatement() !!!!!!!!!!!!!!
				gROOT->ProcessLine(".L $(E551)/raw_libs/libComplete.so"); //!!!!!!!!!!comment for Treatement() !!!!!!!!!!!!!!

				GTape *file = new GTape(runname);
				file->Open();
				GUser * a= new GUser(file);

				a->EventInit();
				//a->SetSpectraMode(0);
				a->SetUserMode(1);
				file->Rewind();

				a->SetTTreeMode(3, outname.c_str());
				a->SetScalerMode(0, sclname.c_str());

				//a->DoRun(1000);
				a->DoRun();


				file->Close();
				delete (a);
			} else {
				cout << gSystem->FindFile("",outname.c_str()) << " already exists. Skip." << endl ;
			}
		}
	gROOT->Reset();
	//gROOT->ProcessLine(".q");
}

//------------------------------------------//
//------------- START LOOP   ---------------//
//------------------------------------------//

void Treatment(const char* input_dir)
{
	int i;
	gROOT->Reset();
	gROOT->ProcessLine(".L $(E551)/dat2raw/GUser_convert.C++O"); //load and compile GUser class
	gROOT->ProcessLine(".L $(E551)/raw_libs/libComplete.so");

	string input_file;       //input file name
	string input_file_wp;    //input file name with path

	TSystemDirectory inputdir ("mydir", input_dir);

	TList* listfile;
	listfile = inputdir.GetListOfFiles();
				//gROOT->ProcessLine(".L ../dat2raw/GUser.C++");

	while (listfile->At(i)) {
		input_file.clear();
		input_file_wp.clear();
		input_file.append((listfile->At(i++)->GetName()));
    	input_file_wp = input_dir + input_file;
		GruScript3(input_file_wp.c_str());
	}

}

//------------------------------------------//
//--------- CONVERSION SCALE ---------------//
//------------------------------------------//

void Scale(char* runname)
{


	string infile = runname;
	int start_run = infile.find("run_");
	int start_dat = infile.find(".dat");
	int len = start_dat - (start_run+4);

	if( start_run == string::npos || start_dat == string::npos || len < 2 ) {
		cerr << "Cannot understand input filename '" << runname << "'. Stop." << endl;
	} else {
			string rnum = infile.substr(start_run+4, len);
			string outname = string("$(E551)/raw_scal/rawdata_")+rnum+string(".root");
			string sclname = string("$(E551)/raw_scal/scalers_")+rnum+string(".root");

			if(gSystem->FindFile("",outname.c_str())==NULL) {
				gROOT->ProcessLine(".L $(E551)/dat2raw/GUser_convert.C++");
				gROOT->ProcessLine(".L $(E551)/raw_libs/libComplete.so");

				GTape *file = new GTape(runname);
				file->Open();
				GUser * a= new GUser(file);

				a->EventInit();
				//a->SetSpectraMode(0);
				a->SetUserMode(1);
				file->Rewind();

				a->SetTTreeMode(0, outname.c_str());
				a->SetScalerMode(1, sclname.c_str());

				//a->DoRun(1000);
				a->DoRun();


				file->Close();
				delete (a);
			} else {
				cout << gSystem->FindFile("",outname.c_str()) << " already exists. Skip." << endl ;
			}
		}
	gROOT->Reset();
	//gROOT->ProcessLine(".q");
}


//------------------------------------------//
//-------- CONVERSION CONTROL --------------//
//------------------------------------------//

void Control(char* runname)
{
	string infile = runname;
	int start_run = infile.find("run_");
	int start_dat = infile.find(".dat");
	int len = start_dat - (start_run+4);

	if( start_run == string::npos || start_dat == string::npos || len < 2 ) {
		cerr << "Cannot understand input filename '" << runname << "'. Stop." << endl;
	} else {
			string rnum = infile.substr(start_run+4, len);
			string outname = string("$(E551)/data_")+rnum+string(".root");
			string sclname = string("$(E551)/scalers_")+rnum+string(".root");

			if(gSystem->FindFile("",outname.c_str())==NULL) {
				gROOT->ProcessLine(".L $(E551)/GUser_convert.C++"); //!!!!!!!!!!comment for Treatement() !!!!!!!!!!!!!!
				gROOT->ProcessLine(".L $(E551)/../raw_libs/libComplete.so"); //!!!!!!!!!!comment for Treatement() !!!!!!!!!!!!!!

				GTape *file = new GTape(runname);
				file->Open();
				GUser * a= new GUser(file);

				a->EventInit();
				//a->SetSpectraMode(0);
				a->SetUserMode(1);
				file->Rewind();

				a->SetTTreeMode(1, outname.c_str());
				a->SetScalerMode(0, sclname.c_str());

				//a->DoRun(1000);
				a->DoRun();


				file->Close();
				delete (a);
			} else {
				cout << gSystem->FindFile("",outname.c_str()) << " already exists. Skip." << endl ;
			}
		}
	gROOT->Reset();
	//gROOT->ProcessLine(".q");
}
