{
	TFile *fin = TFile::Open("MeanPtVersusV0MMult_collisionSystems.root");
	TCanvas *tc = (TCanvas*)fin->Get("cMeanPt_V0M");
	TGraphErrors* gr=(TGraphErrors*)tc->GetListOfPrimitives()->FindObject("MeanPt_ResultsforPionSum_stat");
	TArrayD number(gr->GetN(), [1,1,1,1,1, 1,1,1,1,1, 0.1]);
	cout << "number of points:" << gr->GetN() << endl;
	for (int i=0;i<gr->GetN();i++)
	{
		Double_t x,y;
		gr->GetPoint(i,x,y);
		//gr->SetPoint(i,x * number[i],y);
		//cout << x << "\t" << y << endl;
	}	
	//cout << gr << endl;
	tc->Draw();
	//gr->Draw("AP");

	TFile *fout = TFile::Open("graphs_pk_meanpt.root", "recreate");
	TList *l = (TList*)tc->GetListOfPrimitives();
	for (int i=0; i < l->GetSize();i++)
	{
		if (l->At(i)->InheritsFrom("TGraph"))
		{
			TGraphErrors* gr=(TGraphErrors*)l->At(i);
			cout << i << "\t" << gr->GetName() << "\t" << gr->GetTitle() << "\t" << gr->GetN() << endl;
			fout->cd();
			gr->Write();
		}
	}
	fout->Close();
}