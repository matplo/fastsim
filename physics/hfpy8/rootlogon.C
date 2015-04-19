{
  Int_t ierr = 0;

  char *cmacros[] = 
    {
      0
    };

  Int_t i = 0;
  while (cmacros[i++] != 0)
    {
      TString cmacro;
      cmacro += cmacros[i-1];
      ierr = gROOT->LoadMacro(cmacro.Data());
      if (ierr != 0)
	{
	  cerr <<  "Unable to load macro " << cmacro.Data() << endl;
	}
    }

  char *clibs[] =
    {
      "$PYTHIA8LOCATION/lib/liblhapdfdummy",
      "$PYTHIA8LOCATION/lib/libpythia8",      
      "./libhfpy8.dylib",
      0
    };

  i = 0;
  while (clibs[i] != 0)
    {
      ierr = gSystem->Load(clibs[i]);
      if (ierr != 0)
	{
	  cerr << "Unable to load lib:" << clibs[i] << endl;
	}
      else
	{
	  cerr << "Loaded: " << clibs[i] << endl;
	}
      i++;
    }
  
  //gStyle->SetFrameFillColor(10);
  //gStyle->SetTitleColor(1);
  //gStyle->SetAxisColor(1, "X");
  //gStyle->SetAxisColor(1, "Y");
  //gStyle->SetAxisColor(1, "Z");
  
  //gStyle->SetTitleTextColor(1);

  gStyle->SetPalette(1);
  //gStyle->SetPadColor(10);
  //gStyle->SetFillColor(10);
  gStyle->SetFrameFillColor(10);
  gStyle->SetTitleFillColor(10);
  gStyle->SetStatColor(10);
}
