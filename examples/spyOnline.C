{  
   gROOT->Reset(); 

   TString GRUpath = gSystem->Getenv("GRUDIR");
   gROOT->ProcessLine(Form(".include %s/include", GRUpath.Data()));
   gROOT->ProcessLine(".L ./GUser.C++O");   //load and compile GUser class 

   GNetClientNarval *net = new GNetClientNarval("193.48.111.163"); //
   net->SetPort(10201);  
   net->SetBufferSize(65536);

   GUser * a= new GUser(net);  // creat user treatement environement 
   a->EventInit("e552");       // event initialisation 
   a->SetSpectraMode(1);       // Declare all raw parameters as histograms 
   a->SetUserMode(1);	         // execute GUser::InitUser()
   a->SetNetMode(1);           // start spectra server
   a->DoRun();                 // a->DoRun(2000); do treaments on 2000 first events ( 0 = all);

   net->Close();                       

   a->EndUser();               // must be explicitly called , if it needs
   a->SpeSave("histo.root");   // save all declared histogram 
   delete (a);                 // finish 

   gROOT->ProcessLine(".q");
}


