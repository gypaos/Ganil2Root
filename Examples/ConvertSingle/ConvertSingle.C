void ConvertSingle(){  
  // specify good include dir!
  gROOT->Reset(); 

  char command[100];
  gROOT->ProcessLine(command);
  gROOT->ProcessLine(".L ./GUser.C+"); //load and compile GUser class

  GTape *file = new GTape("/data/tiara/e628/run/run_1231.dat.25Feb14_23h37m42s.1.gz");
  file->Open();                          // Open Device
  GUser * a= new GUser(file);            // creat user treatement environement
  GNetServerRoot *serv = new GNetServerRoot(9090, a);
  a->EventInit();                        // event initialisation
  a->SetSpectraMode(0);                  // Declare all raw parameters as histograms
  a->SetTTreeMode (TREE_USER,"./runstd.root");   // Do a standart TTree ( one leaf  for each parameter) of events
  serv->StartServer();
  a->InitUser();     // Do Init User()

  file->Rewind();        // rewind run
  a->DoRun();
  file->Close();

  a->EndUser();              // must be explicitly called , if it needs
  a->SpeSave("histo.root"); // save all declared histogram 
  delete (a);   // finish 
  gROOT->ProcessLine(".q");
}


