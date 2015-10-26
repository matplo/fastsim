TChain *buildRndChainFromFileList(const char *clist,
                                  const char *treeName,
                                  Int_t nFiles,
                                  TChain *chain = 0,
                                  Double_t tolerance = 0.8, //load min 80% of files
                                  Bool_t silent = kFALSE)
{
	//
	// Return TChain build from files in the filelist.
	// Reuse TChain if "chain" specified - add files to it.
	// Search for "treeName" trees in the files.
	// Add "nFiles" to the chain starting after skipping "nSkipFiles" in the filelist "clist".
	//

	if (chain == 0)
	{
		chain = new TChain(treeName);
	}

	Int_t i = 0;
	Int_t iactualFiles = 0;
	ifstream input_list;//(clist, ifstream::in);
	input_list.open(clist);

	cout << Form("[i] File : %s", clist) << endl;

	char listfile[512];

	vector<string> vfiles;
	if (!input_list.is_open())
	{
		cerr << Form("Unable to open file %s", clist) << endl;
		return chain;
	}
	else
	{
		while (input_list.good())
		{
			input_list.getline(listfile, 512);
			if (input_list.good())
			{
				string tmp(listfile);
				vfiles.push_back(tmp);
			}
		}
		if (silent == kFALSE)
			cout << "[i] File lines read: " << vfiles.size() << endl;
	}

	input_list.close();

	gRandom->SetSeed(0);
	if (vfiles.size() > 1)
	{
		for (unsigned int ic = 0; ic < vfiles.size(); ic++)
		{
			if (silent == kFALSE)
				cout << "\r[i] Randomizing order..." << ic + 1 << "/" << vfiles.size();
			cout.flush();
			int idx1 = (int)gRandom->Uniform(0, vfiles.size());
			int idx2 = (int)gRandom->Uniform(0, vfiles.size());
			while (idx1 == idx2)
				idx2 = (int)gRandom->Uniform(0, vfiles.size());
			string tmp = vfiles[idx1];
			vfiles[idx1] = vfiles[idx2];
			vfiles[idx2] = tmp;
		}
		if (silent == kFALSE)
			cout << endl;
	}

	TMessageHandler mh(TFile::Class());
	Int_t oldCountW = mh.GetMessageCount(1001); // count the warnings!
	Int_t oldCountE = mh.GetMessageCount(1002); // count the errors!
	//__INFOF(Form("File : %d", input_list.good()));

	Int_t nmaxfiles = vfiles.size();
	if (nFiles > nmaxfiles)
		nFiles = nmaxfiles;
	for (unsigned int ic = 0; ic < nFiles; ic++)
	{
		if (silent == kFALSE)
			cout << "[i] Load: " << vfiles[ic].c_str() << endl;
		TFile ftmp(vfiles[ic].c_str());
		ftmp.Close();
		if (oldCountW < mh.GetMessageCount(1001) ||
		        oldCountE < mh.GetMessageCount(1002))
		{
			if (silent == kFALSE)
				cout << Form("[w] File skipped W/E!: %s", vfiles[ic].c_str())
				     << endl;
		}
		else
		{
			if (silent == kFALSE)
				cout << Form("[i] Adding file : %s", vfiles[ic].c_str())
				     << endl;
			chain->AddFile(vfiles[ic].c_str());
			iactualFiles++;
		}
		i++; //count files/lines independent if the file was loaded!
		oldCountW = mh.GetMessageCount(1001);
		oldCountE = mh.GetMessageCount(1002);
	}

	if ( i > 0)
	{
		if (silent == kFALSE)
			cout << Form("[i] Chained %d (Now ok/tried : %1.1f(%d/%d) - tolerate %1.1f) trees ",
			             chain->GetNtrees(), iactualFiles / (i * 1.0), iactualFiles, i, tolerance) << endl;
	}
	else
	{
		if (silent == kFALSE)
			cout << Form("[w] Tried : %d ", i) << endl;
	}

	// check if 80% loaded
	if (chain->GetNtrees() < nFiles * tolerance && nFiles > 3)
	{
		if (silent == kFALSE)
			cout << "[w] Respin..." << endl;
		chain = buildRndChainFromFileList(clist,
		                                  treeName,
		                                  nFiles - iactualFiles,
		                                  chain,
		                                  tolerance * 0.9);
		// decrease tolerance each time
	}
	else
	{
		cout << Form("[i] Chain has %d trees.", chain->GetNtrees()) << endl;
	}
	return chain;
}

TChain *buildChainFromFileList(const char *clist,
                               const char *treeName,
                               Int_t nFiles,
                               Int_t nSkipFiles,
                               TChain *chain = 0,
                               const char *replaceTo = "",
                               const char *replaceFrom = "",
                               Bool_t silent = kFALSE,
                               Bool_t ignoreWarnings = kTRUE)
{
	//
	// Return TChain build from files in the filelist.
	// Reuse TChain if "chain" specified - add files to it.
	// Search for "treeName" trees in the files.
	// Add "nFiles" to the chain starting after skipping "nSkipFiles" in the filelist "clist".
	//

	if (chain == 0)
	{
		chain = new TChain(treeName);
	}

	Int_t i = 0;
	Int_t iactualFiles = 0;
	ifstream input_list;//(clist, ifstream::in);
	input_list.open(clist);
	if (!input_list.is_open())
	{
		cerr << Form("Unable to open file %s", clist) << endl;
		return chain;
	}

	TMessageHandler mh(TFile::Class());
	Int_t oldCountW = mh.GetMessageCount(1001); // count the warnings!
	Int_t oldCountE = mh.GetMessageCount(1002); // count the errors!
	char listfile[512];
	cout << Form("File : %s", clist) << endl;
	//__INFOF(Form("File : %d", input_list.good()));
	while (input_list.good())
	{
		if (i >= nFiles && nFiles > 0)
		{
			break;
		}
		input_list.getline(listfile, 512);
		//__INFOF(Form("line : %s", listfile));
		if (input_list.good()) {
			if (nSkipFiles > 0)
			{
				//__INFOF("Skipped.");
				nSkipFiles--;
			}
			else
			{
				TString slistfile = listfile;
				slistfile.ReplaceAll(replaceFrom, replaceTo);
				TFile ftmp(slistfile.Data());
				ftmp.Close();
				Bool_t skip = kFALSE;
				if (ignoreWarnings == kFALSE && oldCountW < mh.GetMessageCount(1001))
					skip = kTRUE;
				if (oldCountE < mh.GetMessageCount(1002))
					skip = kTRUE;
				if (skip == kTRUE)
				{
					if (silent == kFALSE)
						cout << Form("File skipped W/E!: %s", slistfile.Data()) << endl;
				}
				else
				{
					if (silent == kFALSE)
						cout << Form("Adding file : %s", slistfile.Data()) << endl;
					chain->AddFile(slistfile.Data());
					iactualFiles++;
				}
				i++; //count files/lines independent if the file was loaded!
				oldCountW = mh.GetMessageCount(1001);
				oldCountE = mh.GetMessageCount(1002);
			}
		}
	}
	input_list.close();

	cout << Form("buildChainFromFileList - chained %d files from %d lines read",
	             iactualFiles, i) << endl;

	return chain;
}

void runEMCpid(const char *clist = "./filelist.txt", Int_t nFiles = 5000, Int_t nSkipFiles = 0)
{
	TString treeName = "EMCalTree";

	//TChain *ch       = buildChainFromFileList(clist, treeName.Data(), nFiles, nSkipFiles);
	TChain *ch       = buildRndChainFromFileList(clist, treeName.Data(), nFiles);
	TString spath    = gSystem->ExpandPathName("$RUN2EMCTRIGGER/analyze/EMCpid");
	//TString execline = TString::Format(".L %s/EMCpid.C+", spath.Data());
	//gROOT->ProcessLine(execline.Data());
	gSystem->Load("libEG");
	gSystem->Load("libEMCpidPar");
	EMCpid a(ch);
	a.Loop();
}
