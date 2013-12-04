{
   gROOT->Reset();

   // load GUser
   TString GRUpath = gSystem->Getenv("GRUDIR");
   gROOT->ProcessLine(Form(".include %s/include", GRUpath.Data()));
   gROOT->ProcessLine(".L ./GUser_onlineLC14_C.so"); // load and compile GUser class 

   // open data file to read
//   GTape *file = new GTape("/scratch/gypaos/GanilData/e628/run_0005.dat.03Dec13_11h11m11s");    // Tiara/Hyball gene run
   GTape *file = new GTape("/scratch/gypaos/GanilData/e628/run_0075.dat.04Dec13_17h57m55s");    // Must2 3-alpha run
   file->Open();

   // define GUser
   GUser *a = new GUser(file);
   // define GNetServerRoot to be able to connect vigru
   GNetServerRoot *serv = new GNetServerRoot(9090, a);
   a->EventInit();
   a->SetSpectraMode(1);
   a->SetUserMode(1);
   // start spectra server for vigru
   serv->StartServer();
   file->Rewind();

   // convert run
   a->SetTTreeMode(3, "/scratch/gypaos/GanilData/e628/run_0005_test.root");
   cout << "======== Debug START DoRun() =========" << endl;
   a->DoRun();
   cout << "======== Debug END DoRun() =========" << endl;


//   file->Close();
   a->EndUser();                       // must be explicitly called , if it needs
   a->SpeSave("histo.root");   // save all declared histogram 
//   delete (a);                         // finish 

   // gROOT->ProcessLine(".q");
}
