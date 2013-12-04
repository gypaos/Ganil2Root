{  
   gROOT->Reset(); 

   TString GRUpath = gSystem->Getenv("GRUDIR");
   gROOT->ProcessLine(Form(".include %s/include", GRUpath.Data()));
   gROOT->ProcessLine(".L ./GUser_onlineLC14_C.so");   //load and compile GUser class 

//   GNetClientNarval *net = new GNetClientNarval("193.48.111.163"); //
   GNetClientNarval *net = new GNetClientNarval("localhost"); //
   net->SetPort(10202);  
   net->SetBufferSize(65536);

   GUser *a = new GUser(net);  // create user treatement environement 
   GNetServerRoot *serv = new GNetServerRoot(9090, a);

   a->EventInit("e644");       // event initialisation 
   a->SetSpectraMode(1);       // Declare all raw parameters as histograms 
   a->SetUserMode(1);	         // execute GUser::InitUser()

   serv->StartServer();
   a->DoRun();                 // a->DoRun(2000); do treaments on 2000 first events ( 0 = all);

   net->Close();                       

   a->EndUser();               // must be explicitly called , if it needs
   a->SpeSave("histo.root");   // save all declared histogram 
   delete (a);                 // finish 

   gROOT->ProcessLine(".q");
}


