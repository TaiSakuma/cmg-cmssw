#include "common_stuff.h"
#include <TLorentzVector.h>
#include <THStack.h>
#include <TLatex.h>
#include <TPad.h>
#include <TLegend.h>
#include <TLine.h>
#include <TCanvas.h>


///////////////////////////////////////////////////////////////

// TO LET SPECIFY ALSO THE AXIS TITLES IN THE STRING AND THEN KEEP THE HISTO NAME AND TITLE WITHOUT THEM
TString common_stuff::getCompleteTitleReturnName(std::string title){

  TString completeTitle=Form("%s",title.c_str());
  
  TObjArray* completeTitleTokenized = completeTitle.Tokenize(";");
  
  // int completeTitleTokenized = completeTitleTokenized->GetEntries();
  int ncol = completeTitleTokenized->GetEntries();
  // for(int icol=1; icol<ncol;icol++){
    TString OnlyTitle = ((TObjString *)completeTitleTokenized->At(0))->GetString(); // first tokenized object, i.e. the title
  // }
  
  return OnlyTitle;


}

///////////////////////////////////////////////////////////////

void common_stuff::cloneHisto1D(std::string title_old, std::string title_new, std::map<std::string, TH1D*> &allhistos){
  
  std::map<std::string, TH1D*>::iterator iter_old= allhistos.find(title_old);
  std::map<std::string, TH1D*>::iterator iter_new= allhistos.find(title_new);
  if( !(iter_old == allhistos.end()) && (iter_new == allhistos.end()) ) 
    {
      TH1D* newHisto= (TH1D*)(*iter_old).second->Clone(title_new.c_str());
      newHisto->SetMarkerStyle(20);
      newHisto->SetMarkerSize(0.7);
      newHisto->SetName(title_new.c_str());
      newHisto->SetTitle(title_new.c_str());
      allhistos.insert(std::pair<std::string, TH1D*> (title_new,newHisto) );
    }
    // else{
      // if(iter_old == allhistos.end())
        // std::cout << "histo " << title_old << " NOT FOUND, can't be cloned" << std::endl;
      // else
        // std::cout << "histo " << title_new << " ALREADY EXISTING, not cloning" << std::endl;
    // }

}


///////////////////////////////////////////////////////////////

void common_stuff::plot1D(std::string title, double xval, double weight, std::map<std::string, TH1D*> &allhistos, int numbinsx, double xmin, double xmax)
{

  std::map<std::string, TH1D*>::iterator iter= allhistos.find(title);
  if(iter == allhistos.end()) //no histo for this yet, so make a new  one
    {
      std::string histoName = (std::string) (common_stuff::getCompleteTitleReturnName(title)).Data();
      TH1D* currentHisto= new TH1D(histoName.c_str(), title.c_str(), numbinsx, xmin, xmax);
      currentHisto->SetMarkerStyle(20);
      currentHisto->SetMarkerSize(0.7);
      currentHisto->Sumw2();
      currentHisto->Fill(xval, weight);
      allhistos.insert(std::pair<std::string, TH1D*> (histoName,currentHisto) );
    }
  else // exists already, so just fill it                                                                            
    {
      (*iter).second->Fill(xval, weight);
    }
}

///////////////////////////////////////////////////////////////

void common_stuff::plot1D(std::string title, double xval, double weight, std::map<std::string, TH1D*> &allhistos, int numbinsx, double *xarray)
{

  std::map<std::string, TH1D*>::iterator iter= allhistos.find(title);
  if(iter == allhistos.end()) //no histo for this yet, so make a new  one
    {
      std::string histoName = (std::string) (common_stuff::getCompleteTitleReturnName(title)).Data();
      TH1D* currentHisto= new TH1D(histoName.c_str(), title.c_str(), numbinsx, xarray);
      currentHisto->SetMarkerStyle(20);
      currentHisto->SetMarkerSize(0.7);
      currentHisto->Sumw2();
      currentHisto->Fill(xval, weight);
      allhistos.insert(std::pair<std::string, TH1D*> (histoName,currentHisto) );
    }
  else // exists already, so just fill it                                                                            
    {
      (*iter).second->Fill(xval, weight);
    }
}

///////////////////////////////////////////////////////////////

void common_stuff::plot2D(std::string title, double xval, double yval, double weight, std::map<std::string, TH2D*> &allhistos, int numbinsx, double xmin, double xmax, int numbinsy, double ymin, double ymax)
{

  std::map<std::string, TH2D*>::iterator iter= allhistos.find(title);
  if(iter == allhistos.end()) //no histo for this yet, so make a new one
    {
      TH2D* currentHisto= new TH2D(((TString)common_stuff::getCompleteTitleReturnName(title)).Data(), title.c_str(), numbinsx, xmin, xmax, numbinsy, ymin, ymax);
      currentHisto->Sumw2();
      currentHisto->Fill(xval, yval, weight);
      allhistos.insert(std::pair<std::string, TH2D*> (title,currentHisto) );
    }
  else // exists already, so just fill it
    {
      (*iter).second->Fill(xval, yval, weight);
    }

  return;

}

///////////////////////////////////////////////////////////////

void common_stuff::plot2D(std::string title, double xval, double yval, double weight, std::map<std::string, TH2D*> &allhistos, int numbinsx, double *xarray, int numbinsy, double *yarray)
{

  std::map<std::string, TH2D*>::iterator iter= allhistos.find(title);
  if(iter == allhistos.end()) //no histo for this yet, so make a new one
    {
      TH2D* currentHisto= new TH2D(((TString)common_stuff::getCompleteTitleReturnName(title)).Data(), title.c_str(), numbinsx, xarray, numbinsy, yarray);
      currentHisto->Sumw2();
      currentHisto->Fill(xval, yval, weight);
      allhistos.insert(std::pair<std::string, TH2D*> (title,currentHisto) );
    }
  else // exists already, so just fill it
    {
      (*iter).second->Fill(xval, yval, weight);
    }

  return;

}

///////////////////////////////////////////////////////////////

void common_stuff::writeOutHistos(TFile *fout, std::map<std::string, TH1D*> h_1d, std::map<std::string, TH2D*> h_2d)
{

  fout->cd();
  
  std::map<std::string, TH1D*>::iterator it1d;
  for(it1d=h_1d.begin(); it1d!=h_1d.end(); it1d++) {
    it1d->second->Write(); 
    delete it1d->second;
  }

  std::map<std::string, TH2D*>::iterator it2d;
  for(it2d=h_2d.begin(); it2d!=h_2d.end(); it2d++) {
    it2d->second->Write(); 
    delete it2d->second;
  }
 

}

///////////////////////////////////////////////////////////////

std::pair<double,double> common_stuff::getPhiCorrMET( double met, double metphi, int nvtx, bool ismc ) {

  //using met phi corrections from C. Veelken (revision 1.6)
  //functions are available here:                                                                                                            
  //http://cmssw.cvs.cern.ch/cgi-bin/cmssw.cgi/CMSSW/JetMETCorrections/Type1MET/python/pfMETsysShiftCorrections_cfi.py                               
  double metx = met * cos( metphi );
  double mety = met * sin( metphi );

  //use correction for data vs. mc // these numbers are documented in AN2012_333_v5
  double shiftx = ismc ? (0.1166 + 0.0200*nvtx) : (0.2661 + 0.3217*nvtx);
  double shifty = ismc ? (0.2764 - 0.1280*nvtx) : (-0.2251 - 0.1747*nvtx);

  metx -= shiftx;
  mety -= shifty;

  std::pair<double, double> phicorrmet = std::make_pair( sqrt( metx*metx + mety*mety ), atan2( mety , metx ) );
  return phicorrmet;
}

///////////////////////////////////////////////////////////////

void common_stuff::makeRatioHisto1D(std::string title1, std::string title2, std::string title_ratio, std::map<std::string, TH1D*> &allhistos){

  std::map<std::string, TH1D*>::iterator iter1= allhistos.find(title1);
  std::map<std::string, TH1D*>::iterator iter2= allhistos.find(title2);
  std::map<std::string, TH1D*>::iterator iter_ratio= allhistos.find(title_ratio);
  
  if(iter_ratio == allhistos.end() && iter1 != allhistos.end() && iter2 != allhistos.end()) //no histo for this yet, so make a new  one
  {
    std::string histoName = (std::string) (common_stuff::getCompleteTitleReturnName(title_ratio)).Data();
    TH1D* currentHisto= (TH1D*)(*iter1).second->Clone(histoName.c_str());
    currentHisto->SetName(histoName.c_str());
    currentHisto->SetTitle(histoName.c_str());
    TH1D* denominator= (*iter2).second;
    currentHisto->Divide(denominator);
    
    // TH1D* currentHisto= new TH1D(histoName.c_str(), title.c_str(), numbinsx, xmin, xmax);
    // currentHisto->Sumw2();
    // currentHisto->Fill(xval, weight);
    allhistos.insert(std::pair<std::string, TH1D*> (histoName,currentHisto) );
  }else{
    
    std::cout << "Can't create histo " << title_ratio << " as " << title1 << " and/or " << title2 << " don't exist and/or the ratio of 2 histos already exists!" << std::endl;
    
  }

  
  // std::map<std::string, TH1D*>::iterator numerator= h_1d.find(Form("logPhiStarEta_gen_MCEffWeighted_ATLASbin_pdf%d_eta%s",WMass::PDF_sets<0?generated_PDF_set:WMass::PDF_sets,eta_str.Data()));
  // std::map<std::string, TH1D*>::iterator denominator= h_1d.find(Form("logPhiStarEta_NoEffWeights_ATLASbin_pdf%d_%d%s_eta%s",WMass::PDF_sets<0?generated_PDF_set:WMass::PDF_sets,h,toys_str.Data(),eta_str.Data()));  
  // TH1D currentHistolog= (*(*numerator).second)/(*(*denominator).second);
  // currentHistolog.SetName("test_logratio_PhiStarEta");
  // currentHistolog.SetTitle("test_logratio_PhiStarEta");

  // numerator= h_1d.find(Form("PhiStarEta_gen_MCEffWeighted_ATLASbin_pdf%d_eta%s",WMass::PDF_sets<0?generated_PDF_set:WMass::PDF_sets,eta_str.Data()));
  // denominator= h_1d.find(Form("PhiStarEta_NoEffWeights_ATLASbin_pdf%d_%d%s_eta%s",WMass::PDF_sets<0?generated_PDF_set:WMass::PDF_sets,h,toys_str.Data(),eta_str.Data()));  
  // TH1D currentHisto= (*(*numerator).second)/(*(*denominator).second);
  // currentHisto.SetName("test_ratio_PhiStarEta");
  // currentHisto.SetTitle("test_ratio_PhiStarEta");

  // fout->cd();
  // currentHistolog.Write();
  // currentHisto.Write();



}

///////////////////////////////////////////////////////////////


void common_stuff::plotAndSaveHisto1D_stack(TString LegendEvTypeTeX, TFile*fMCsig, TFile*fMCEWK, TFile*fMCTT, TFile*fMCQCD, TFile*fDATA, TString HistoName_st, int logx, int logy, int logz, int scaleMCtoDATA, TString title,double xmin, double xmax, int rebinfactor, int PullOrRatio){

  std::cout << "retrieving hMCsig= " << HistoName_st.Data() << std::endl;
  TH1D*hMCsig=(TH1D*)fMCsig->Get(HistoName_st.Data());
  fMCsig->Print();
  hMCsig->Rebin(rebinfactor);
  // std::cout << "hMCsig= " << hMCsig->Print() << std::endl;
  hMCsig->SetLineColor(kOrange-3);
  TH1D*hMCsig2=(TH1D*)hMCsig->Clone("hMCsig2");
  hMCsig2->SetFillColor(kOrange-2);
  hMCsig2->SetLineStyle(2);
  hMCsig2->SetLineWidth(2);
  TH1D*hMCEWK=(TH1D*)fMCEWK->Get(HistoName_st.Data());
  // std::cout << "hMCEWK= " << hMCEWK->Print() << std::endl;
  hMCEWK->SetFillColor(kOrange+7);
  hMCEWK->SetLineColor(kOrange+10);
  hMCEWK->Rebin(rebinfactor);
  TH1D*hMCTT=(TH1D*)fMCTT->Get(HistoName_st.Data());
  // std::cout << "hMCTT= " << hMCTT->Print() << std::endl;
  hMCTT->SetFillColor(kGreen);
  hMCTT->SetLineColor(kGreen+2);
  hMCTT->Rebin(rebinfactor);
  TH1D*hMCQCD=(TH1D*)fMCQCD->Get(HistoName_st.Data());
  // std::cout << "hMCQCD= " << hMCQCD->Print() << std::endl;
  hMCQCD->SetFillColor(kViolet-5);
  hMCQCD->SetLineColor(kViolet+2);
  hMCQCD->Rebin(rebinfactor);
  TH1D*hDATA=(TH1D*)fDATA->Get(HistoName_st.Data());
  hDATA->SetMarkerColor(1);
  hDATA->SetLineColor(1);
  hDATA->SetMarkerStyle(20);
  hDATA->SetMarkerSize(0.7);
  hDATA->Rebin(rebinfactor);

  TH1D MCsum=(*hMCsig)+(*hMCEWK)+(*hMCTT)+(*hMCQCD);
  
  std::cout << "Total DATA/MC scaling factor = " << hDATA->Integral()/MCsum.Integral() << std::endl;
  if(scaleMCtoDATA){
    hMCsig2->Scale(hDATA->Integral()/MCsum.Integral());
    hMCsig->Scale(hDATA->Integral()/MCsum.Integral());
    hMCEWK->Scale(hDATA->Integral()/MCsum.Integral());
    hMCTT->Scale(hDATA->Integral()/MCsum.Integral());
    hMCQCD->Scale(hDATA->Integral()/MCsum.Integral());
    MCsum.Scale(hDATA->Integral()/MCsum.Integral());
  }
  
  double fsig = hMCsig->Integral()/MCsum.Integral()*100;
  double fewk = hMCEWK->Integral()/MCsum.Integral()*100;
  double ftt = hMCTT->Integral()/MCsum.Integral()*100;
  double fqcd = hMCQCD->Integral()/MCsum.Integral()*100;

  THStack *hs= new THStack("hs","test stacked histograms");
  hs->Add(hMCTT);
  hs->Add(hMCQCD);
  hs->Add(hMCEWK);
  hs->Add(hMCsig);

  std::cout << "Integral hDATA= " << hDATA->Integral() << " hMCsig= " << hMCsig->Integral() << " hMCEWK= " << hMCEWK->Integral() << " hMCTT= " << hMCTT->Integral() << " hMCQCD= " << hMCQCD->Integral() << " MCsum= " << MCsum.Integral() << std::endl;
  // std::cout << "Entries hDATA= " << hDATA->GetEntries() << " hMCsig= " << hMCsig->GetEntries() << " hMCEWK= " << hMCEWK->GetEntries() << " hMCTT= " << hMCTT->GetEntries() << " MCsum= " << MCsum.GetEntries() << std::endl;
  // Double_t TH1::Chi2TestX(const TH1* h2,  Double_t &chi2, Int_t &ndf, Int_t &igood, Option_t *option,  Double_t *res) const
  Double_t chi2; Int_t ndf; Int_t igood;
  std::cout << "DATA-MC chi2: " << hDATA->Chi2TestX((TH1D*)&MCsum,chi2,ndf,igood,"") << std::endl;
  std::cout << "chi2= " << chi2 << " ndf= " << ndf << " norm chi2= " << (chi2/ndf) << " prob= " << TMath::Prob(chi2,ndf) << " igood= " << igood << std::endl;
  std::cout << std::endl;
  TLatex *t = new TLatex();
  t->SetNDC();
  // t->SetTextAlign(22);
  t->SetTextFont(63);
  t->SetTextSizePixels(17);

  // h1->SetLineColor(2);
  
  TCanvas *c1 = new TCanvas("c"+HistoName_st,"c"+HistoName_st,800,800);
  TPad *pad1 = new TPad("pad1", "",0,0.25,1,1);
  pad1->SetLogx(logx);
  pad1->SetLogy(logy);
  pad1->SetLogz(logz);
  pad1->SetTickx(1);
  pad1->SetTicky(1);
  pad1->SetBottomMargin(0);
  pad1->SetTopMargin(0.075);
  pad1->Draw();
  TPad *pad2 = new TPad("pad2", "",0,0,1,0.25);
  pad2->SetLogx(logx);
  pad2->SetTickx(1);
  pad2->SetTicky(1);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.35);
  pad2->Draw();

  pad1->cd();  
  if(logy!=1)
    hDATA->GetYaxis()->SetRangeUser(0.11,hDATA->GetMaximum()*1.2);
  else
    hDATA->GetYaxis()->SetRangeUser(1,hDATA->GetMaximum()*10);
  
  hDATA->SetTitle(title.Data());
  hDATA->GetXaxis()->SetRangeUser(xmin==-1?hDATA->GetXaxis()->GetBinLowEdge(1):xmin,xmax==-1?hDATA->GetXaxis()->GetBinCenter(hDATA->GetNbinsX()):xmax);
  hDATA->GetYaxis()->SetTitle(Form("Counts / %.2f",hDATA->GetBinWidth(1)));
  hDATA->Draw("pe");
  hs->Draw("same");
  hMCsig2->Draw("same");
  hDATA->Draw("same pe");
  pad1->RedrawAxis();
  
  TLegend *leg = new TLegend(0.6,0.7,0.85,0.9,"4.75 fb^{-1} at #sqrt{7} TeV","brNDC");
  leg->SetBorderSize(0);
  leg->SetTextFont(62);
  leg->SetLineColor(1);
  leg->SetLineStyle(1);
  leg->SetLineWidth(1);
  leg->SetFillColor(0);
  leg->SetFillStyle(1001);
  leg->AddEntry(hDATA,"DATA","pl");
  leg->AddEntry(hMCsig,Form("%s (%.1f \%%)",LegendEvTypeTeX.Data(), fsig),"f");
  leg->AddEntry(hMCEWK,Form("EWK (%.1f \%%)",fewk),"f");
  leg->AddEntry(hMCQCD,Form("QCD (%.1f \%%)",fqcd),"f");
  leg->AddEntry(hMCTT,Form("TT (%.1f \%%)",ftt),"f");
  leg->Draw();
  
  t->DrawLatex(0.15,0.85,Form("norm chi2= %.2f, prob %.3e",(chi2/ndf),TMath::Prob(chi2,ndf)));
  
  pad2->cd();
  TH1D*hPullOrRatio=(TH1D*)hDATA->Clone("hPullOrRatio");
  if(PullOrRatio==0){
    for(int i=1;i<hPullOrRatio->GetNbinsX()+1;i++){
      hPullOrRatio->SetBinContent(i,hDATA->GetBinError(i)>0?(hDATA->GetBinContent(i)-MCsum.GetBinContent(i))/hDATA->GetBinError(i):0);
      // std::cout << Form("%f",hDATA->GetBinError(i)>0?(hDATA->GetBinContent(i)-MCsum.GetBinContent(i))/hDATA->GetBinError(i):0) << std::endl;
    }  
  }else{
    hPullOrRatio->Divide(((TH1D*)&MCsum));
  }
    
  hPullOrRatio->GetXaxis()->SetLabelSize(0.04*0.75/0.25);
  hPullOrRatio->GetXaxis()->SetTitleOffset(1);
  hPullOrRatio->GetXaxis()->SetTitleSize(0.04*0.75/0.25);
  hPullOrRatio->GetYaxis()->SetTitle(PullOrRatio==0?"Pull":"Ratio");
  hPullOrRatio->GetYaxis()->SetLabelSize(0.04*0.75/0.25);
  hPullOrRatio->GetYaxis()->SetTitleOffset(0.35);
  hPullOrRatio->GetYaxis()->SetTitleSize(0.04*0.75/0.25);
  hPullOrRatio->GetYaxis()->SetNdivisions(410);
  // hPullOrRatio->GetYaxis()->SetRangeUser(-14.9,14.9);
  if(PullOrRatio==0)
    hPullOrRatio->GetYaxis()->SetRangeUser(-5.9,5.9);
  else
    hPullOrRatio->GetYaxis()->SetRangeUser(0.8,1.2);
  
  hPullOrRatio->Draw("p");
  TLine*l0=new TLine(xmin==-1?hDATA->GetXaxis()->GetBinLowEdge(1):xmin,0,xmax==-1?hDATA->GetXaxis()->GetBinCenter(hDATA->GetNbinsX()):xmax,0);l0->SetLineColor(kGray);
  TLine*lp5=new TLine(xmin==-1?hDATA->GetXaxis()->GetBinLowEdge(1):xmin,5,xmax==-1?hDATA->GetXaxis()->GetBinCenter(hDATA->GetNbinsX()):xmax,5);lp5->SetLineColor(kGray);
  TLine*lm5=new TLine(xmin==-1?hDATA->GetXaxis()->GetBinLowEdge(1):xmin,-5,xmax==-1?hDATA->GetXaxis()->GetBinCenter(hDATA->GetNbinsX()):xmax,-5);lm5->SetLineColor(kGray);
  l0->Draw("same");
  lp5->Draw("same");
  lm5->Draw("same");
  hPullOrRatio->Draw("p same");
  
  TString extra_ouput_str = "";
  if(logx)extra_ouput_str+="_logx";
  if(logy)extra_ouput_str+="_logy";
  if(logz)extra_ouput_str+="_logz";
  if(scaleMCtoDATA)extra_ouput_str+="_norm";
  if(xmin!=-1)extra_ouput_str+=Form("_xmin%.f",xmin);
  if(xmax!=-1)extra_ouput_str+=Form("_xmax%.f",xmax);
  c1->SaveAs(HistoName_st+extra_ouput_str+".png");
}


