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

void runEMCpid(const char *clist = "./filelist.txt", Int_t nFiles = 1000, Int_t nSkipFiles = 0)
{
	TString treeName = "EMCalTree";
	TChain *ch       = buildChainFromFileList(clist, treeName.Data(), nFiles, nSkipFiles);
	TString spath    = gSystem->ExpandPathName("$RUN2EMCTRIGGER/analyze/EMCpid");
	TString execline = TString::Format(".L %s/EMCpid.C+", spath.Data());
	gROOT->ProcessLine(execline.Data());
	EMCpid a(ch);
	a.Loop();
}