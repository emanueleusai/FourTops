#include "include/FourTops.h"

int main(int argc, char** argv) {
  // //TCanvas c("a");
  // TFile input_file("/mnt/hadoop/store/group/bruxljm/FWLJMET102X_1lep2017_4t_081019_step1/nominal/TTTT_TuneCP5_13TeV-amcatnlo-pythia8/TTTT_TuneCP5_13TeV-amcatnlo-pythia8_1.root","READ");
  // // unique_ptr<TObject> input_file.Get("ljmet");

  // auto tree= unique_ptr<TTree>(static_cast<TTree*>(input_file.Get("ljmet")));

  // // auto tree = unique_ptr<TTree>(static_cast<TTree*>(move(input_file.Get("ljmet"))));
  // TTreeReader reader("ljmet",&input_file);
  // TTreeReaderValue<std::any> nTracksRV(reader, "AK4HT");

  // auto leaves = tree->GetListOfLeaves();
  // auto nleaves = leaves->GetEntriesFast();
  // for (int l=0;l<nleaves;l++)
  // {
  // 	TLeaf *leaf = (TLeaf*)leaves->UncheckedAt(l);
  // 	cout<<leaf->GetName()<<" "<<leaf->GetTypeName()<<endl;
  // }

  // while(reader.Next())
  // {
  // 	cout<<*any_cast<float*>(nTracksRV)<<endl;

  //     // if (*nTracksRV < 587) {
  //     //    continue; // Check if we don't have too many tracks
  //     // }
  //     // auto event = eventRV.Get();      //Read complete accepted event
  //     //                                  //in memory.
  //     // hnseg->Fill(event->GetNseg());   //Fill histogram with number of
  //     //                                  //segments.
  // }

  //  // TTreeReaderValue<Event> eventRV(theReader, "event");
  //  // TTreeReaderValue<Int_t> nTracksRV(theReader, "fNtrack");

  TFile outfile("outfile.root", "RECREATE");

  EnableImplicitMT(); // Tell ROOT you want to go parallel
  RDataFrame d("ljmet", "/mnt/hadoop/store/group/bruxljm/FWLJMET102X_1lep2017_4t_081019_step1/nominal/TTTT_TuneCP5_13TeV-amcatnlo-pythia8/TTTT_TuneCP5_13TeV-amcatnlo-pythia8_*.root"); // Interface to TTree and TChain

  map<string,vector<float> > interesting_variables;

   ptree tree;

    // Parse the XML into the property tree.
    read_xml(filename, tree);

  auto d2 = d.Filter("\
  	(corr_met_MultiLepCalc > 50.0) && \
  	( (isMuon && NJets_JetSubCalc >= 7) || (isElectron && NJets_JetSubCalc >= 8) ) && \
  	( NJetsCSV_JetSubCalc >=2 ) && \
  	( AK4HT > 500.0 ) \
  	");
  auto myHisto = d2.Histo1D("AK4HT");
  // auto myHisto = d.Histo1D("Branch_A"); // This happens in parallel!
  // myHisto->Draw();

  myHisto->Write();

  outfile.Close();
  cout << "greeting" << endl;
  return 0;
}

