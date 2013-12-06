//example convertion of mutiple runs
// 2 directories must be created for this conversion
// 
//the 2 informations need to run this root script are input_dir and output_dir
//
// input_dir must contain only input ganil runs to convert.
// the runs must be sorted in aphanumeric order in their directory
// and will contains the resutl of conversion
void ConvertDirectory(Int_t run_nbr_max = 411, Int_t  run_nbr_min =  1)
{
  gROOT->Reset();
//  gROOT->ProcessLine(".include /vol0/sandra/These/Analyse/e530/GRU/include");
  gROOT->ProcessLine(".L ./GUser_convert.C++O"); //load and compile GUser class 
  
  //  string acquis_dir = gSystem->Getenv("E530") ;
  string acquis_dir = "/media/e530/" ;
  
  // input_dir must contain input ganil runs.
  //the runs must be sorted in aphanumeric order in their directory
  string  input_dir = acquis_dir + "data/";
  
  
  // output_dir must be empty
  // will contains the resutl of conversion
  acquis_dir = gSystem->Getenv("E530") ;
  string output_dir = acquis_dir + "/root/";
  
  //_____________________________________________________________________________________
  string input_file;       //input file name
  string input_file_wp;    //input file name with path
  string output_file;      //output file name
  string output_file_wp;   //output file name with path 
  string scaler_file_wp;
  
  int i;
  
  GTape* file = new GTape(input_dir.c_str());
  TSystemDirectory inputdir ("mydir", input_dir.c_str());
  
  TList* listfile; 
  listfile = inputdir.GetListOfFiles();
  
  if(run_nbr_min>run_nbr_max){
    Int_t tmprunn = run_nbr_max ;
    run_nbr_max = run_nbr_min ;
    run_nbr_min = tmprunn ;
  }

  i=0;
  while (listfile->At(i)) {
    input_file.clear();
    input_file_wp.clear();
    output_file.clear();
    output_file_wp.clear();
    scaler_file_wp.clear();
    
    input_file.append((listfile->At(i++)->GetName()));
    cout<<input_file<<endl;
    input_file_wp = input_dir + input_file;
    
    cout << input_file << endl;
    cout <<  input_file_wp << endl;
    
    file->SetDevice (input_file_wp.c_str()); 
    file->SetBufferSize(32768);
    
 
    //  cout <<input_file<<" is a run = "<<file->IsARun() <<"\n";
    
    if (file->IsARun() ){ 
    
      string number = input_file.substr(input_file.find("_")+1,input_file.find(".dat.") - input_file.find("_")-1);
      //cout<<number<<" "<<atoi(number.c_str())<<endl;
      
      if(atoi(number.c_str()) <= run_nbr_max &&
	 atoi(number.c_str()) >= run_nbr_min){
	
	string condition = "lsof -Fn +d /media/e530/data | grep ";
	condition += input_file;
	cout << "condition " << condition << endl;

	if(gSystem->Exec(condition.c_str())!=0) {
	  //cout<<"file " << input_file << "is not running in the acquisition "<<endl;
	  
	  output_file = input_file.substr(0,input_file.find(".dat."));
	  scaler_file = input_file.substr(0,input_file.find(".dat."));
	  scaler_file.append("_scaler.root");
	  output_file.append(".root");
	  output_file_wp = output_dir + output_file;
	  scaler_file_wp = output_dir + "scaler_" + output_file;

	 	  
	  if(gSystem->FindFile(output_dir.c_str(),scaler_file.c_str())==NULL || gSystem->FindFile(output_dir.c_str(),output_file.c_str()) == NULL) {
	    cout << "Generating file: " << output_file_wp << endl ;
	    cout << "Generating file: " << scaler_file_wp << endl ;
	    
	    gSystem->Chmod(input_file_wp.c_str(),256); // this is ROOT definition for "chmod 400", make the read only for the user only
	    
	    system("rm -f $E530/run/ACTIONS_local.CHC_PAR; rm -f $E530/run/ACTIONS_local.CHC_STR;");
	    
	    file->Open();                                     
	    GUser * a= new GUser(file); 
	    
	    a->EventInit();     
	    
	    a->SetUserMode(1);     // Do the event treatment no choice of GUser           				 
	    
	    file->Rewind(); 
	    
	    a->SetTTreeMode (3,output_file_wp.c_str());     
	    
	    a->SetScalerMode(1,scaler_file_wp.c_str());   // mettre a 1 pour avoir les echelles
	    
	    a->DoRun();
	    
	    file->Close();
	    	    
	    cout << "try to delete a" << endl;
	    // delete (a);
	    cout << "a deleted" << endl;
	  } 
	  else {
	    cout << gSystem->FindFile(output_dir.c_str(),scaler_file.c_str()) << " already exists. Skip." << endl ;
	    cout << gSystem->FindFile(output_dir.c_str(),output_file.c_str()) << " already exists. Skip." << endl ;
	  }
	}
	else {
	  cout<<"the run is probably opened by the acquisition " << input_file<<endl;
	}
      }
      else
	{
	  // cout<<"run's is greater than "<<run_nbr_max<<endl;
	  // cout<<"run's is smaller than "<<run_nbr_min<<endl;
	}
      //	cout<<"--------------------------"<<endl;
      
      
      cout << "end of IsARun " << endl;
    }// end of if file->IsARun()
    
    cout << "end of while" << endl;

  } // end of while 
  
  gROOT->ProcessLine(".q"); //finish
}
