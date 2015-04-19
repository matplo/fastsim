Bool_t LoadLibs(char *_clibs[], 
		Bool_t silent,
		Int_t imax)
{
  Int_t _ierr = 0;
  Int_t _i = 0;
  while (_clibs[_i++] != 0)
    {
      if (imax > 0 && _i > imax)
	break;
      // do not print errors if no CGAL
      Bool_t _envNotSet = kFALSE;
      const char* _entry = _clibs[_i-1];
      TString _slib = _entry;
      TString _dirnametmp = gSystem->DirName(_entry);	
      if (_dirnametmp == ".")
	_dirnametmp = "";
      if (_dirnametmp.Length() > 0)
	{
	  if (_dirnametmp.Contains("$"))
	    {
	      //cout << entry << " Dir: " << dirnametmp.Data() << endl;
	      TObjArray *_arr = _dirnametmp.Tokenize(TString("/"));
	      //cout << "N tokens " << arr->GetEntries() << endl;
	      for (Int_t _j = 0; _j < _arr->GetEntries(); _j++)
		{
		  TObjString* _str = (TObjString*)_arr->At(_j);
		  TString _sx = _str->GetString();
		  //cout << "Checking " << j << " " << s.Data() << endl;
		  if (_sx.Contains("$") && _sx.Length() > 0)
		    {
		      _sx.ReplaceAll("$","");
		      if (gSystem->Getenv(_sx.Data()) == 0)
			{
			  _envNotSet = kTRUE;
			  break;
			}
		    }
		}
	    }

	  if (_envNotSet)
	    {
	      cout << "[i] Ignoring:  " << _entry << endl;
	      continue;
	    }

	  TString _dirname = gSystem->ExpandPathName(_dirnametmp.Data());
	  if (_dirnametmp == _dirname)
	    continue;
	  _slib = Form("%s/%s", _dirname.Data(), gSystem->BaseName(_entry));

	  if (gSystem->FindFile("/", _slib) == 0)
	    {
	      cout << "[i] Not found: " << _entry << endl;
	      continue;
	    }
	}

      _ierr = gSystem->Load(_slib.Data());
      if (_ierr != 0)
	{
	  if (_ierr > 0)
	    {
	      if (silent == kFALSE)
		{
		  cout <<  "[i] Already loaded: " << _slib.Data() << endl;
		}
	    }
	  else
	    {
	      cerr <<  "[e] Unable to load: " << _slib.Data() << endl;
	    }
	}
      else
	{
	  if (silent == kFALSE)
	    {
	      cout << "[i] Loaded: " << _slib.Data() << endl;
	    }
	}
    }
  
  return kTRUE;
}
