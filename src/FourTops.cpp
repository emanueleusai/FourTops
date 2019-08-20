#include "include/FourTops.h"

int main(int argc, char** argv) {
  cout << "Hello." << endl;

  if(argc==1) {
  	cout << "No config file" << endl;
  	return 1;
  } 
  ptree config;
  read_json(argv[1], config);
  EnableImplicitMT();
  auto folder=config.get<std::string>("folder");

  auto lumi=config.get<float>("lumi");

  for (const auto & v: config.get_child("samples") ){
  	cout<<"Processing "<<v.first<<endl;
  	auto nevts=v.second.get<float>("nevts");
  	auto xsec=v.second.get<float>("xsec");


  	RDataFrame d("ljmet",folder+v.second.get<std::string>("files"));
  	TFile outfile((config.get<std::string>("outfile")+"_"+v.first+".root").c_str(), "RECREATE");
  	auto doWeight= [&](double x) { return x * lumi * xsec / nevts > 4.; };
  	auto d2 = d
  	.Filter("\
  	(corr_met_MultiLepCalc > 50.0) && \
  	( (isMuon && NJets_JetSubCalc >= 7) || (isElectron && NJets_JetSubCalc >= 8) ) && \
  	( NJetsCSV_JetSubCalc >=2 ) && \
  	( AK4HT > 500.0 ) \
  	")
  	.Define("base_evt_weight",doWeight,{"MCWeight_MultiLepCalc"});
  	
  	for (const auto & var: config.get_child("vars") ){
  		auto histo = d2.Histo1D({var.first.c_str(),"",var.second.get<int>("nbin"),
  								var.second.get<float>("xmin"),var.second.get<float>("xmax")},
  								var.first.c_str(),"base_evt_weight");
  		histo->Write();

  	}

  	outfile.Close();
  }

  

  

  
  
  cout << "Goodbye." << endl;
  return 0;
}

