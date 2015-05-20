#ifndef LARLITE_NEUTRALPION_CXX
#define LARLITE_NEUTRALPION_CXX

#include "neutralpion.h"

namespace larlite {

  bool neutralpion::initialize() {

        InitializeAnaTree();



    return true;
  }
  bool neutralpion::analyze(storage_manager* storage) {
	// Bring in the info for the event
        auto mctruth = storage->get_data<event_mctruth>("generator");
        auto mcnu = mctruth->at(0).GetNeutrino();
        auto mcpart = mctruth->at(0).GetParticles();
        auto mcshower = storage->get_data<event_mcshower>("mcreco");

	//Fill out the neutrino interaction information
        ccnc = mcnu.CCNC();
        mode = mcnu.Mode();
        interaction = mcnu.InteractionType();
        w = mcnu.W();
        qsqr = mcnu.QSqr();

	// pi0count pair<(int) how many fsi pi0, (vector<int>) the track ID>
	auto pi0count = fBO.pi0count(mcpart);
	fsipi0 = pi0count.first;
	auto cmeson = fBO.cmesoncounter(mcpart);
	// protoncounter pair<(int) how many fsi protons, (vector<int>) the track ID>
	auto protoninfo = fBO.protoncounter(mcpart,ProtThresh);
	protoncount = protoninfo.first;

	if(pi0count.first==1 && cmeson==0){
		for(auto const mcp : mcpart){
			//find the particle info
			if(mcp.TrackId()==pi0count.second[0])
			{
			status = mcp.StatusCode();
                        auto traj = mcp.Trajectory();
			_spenergy = traj[0].E();
                        P_x = traj[0].X();
                        P_y = traj[0].Y();
                        P_z = traj[0].Z();
                        P_px = traj[0].Px();
                        P_py = traj[0].Py();
                        P_pz = traj[0].Pz();
			P_pmag = sqrt(P_px*P_px+P_py*P_py+ P_pz*P_pz);
			}// if we have the particle
		}//for loop over mcp
	}//if pi0 is single


	// See if it is a dalitz decay? 
	bool DalitzDecay = false; 
	  contain_shower_a = -999;
	  contain_shower_b = -999;


	  shower_a_E = -999;
	  shower_a_x = -999;
	  shower_a_y = -999;
	  shower_a_z = -999;
	  shower_a_px = -999;
	  shower_a_py = -999;
	  shower_a_pz = -999;
	  shower_b_E = -999;
	  shower_b_x = -999;
	  shower_b_y = -999;
	  shower_b_z = -999;
	  shower_b_px = -999;
	  shower_b_py = -999;
	  shower_b_pz = -999;

	  sprof_a_E = -999;
	  sprof_a_x = -999;
	  sprof_a_y = -999;
	  sprof_a_z = -999;
	  sprof_a_px = -999;
	  sprof_a_py = -999;
	  sprof_a_pz = -999;
	  sprof_b_E = -999;
	  sprof_b_x = -999;
	  sprof_b_y = -999;
	  sprof_b_z = -999;
	  sprof_b_px = -999;
	  sprof_b_py = -999;
	  sprof_b_pz = -999;


	// True signal events will only have 2 mcshower. 
	if(mcshower->size()!=2){  DalitzDecay=true;}
                        for(auto const& mcs : *mcshower){
				auto SP = mcs.Start();
                                auto ShowerDetProf =  mcs.DetProfile();
                                double mccontained = ShowerDetProf.E()/SP.E();
				if(contain_shower_b == -999 && contain_shower_a!=-999 ){ 
				contain_shower_b = mccontained;  
				auto pos = SP.Position();
				auto mom = SP.Momentum();
				auto dpos = ShowerDetProf.Position();
				auto dmom = ShowerDetProf.Momentum();
				// truth info
				shower_b_E = SP.E();
				shower_b_x = pos.X();
				shower_b_y = pos.Y();
				shower_b_z = pos.Z();
				shower_b_px = mom.Px();
				shower_b_py = mom.Py();
				shower_b_pz = mom.Pz();
				//for detprof
				sprof_b_E = ShowerDetProf.E();
				sprof_b_x = dpos.X();
				sprof_b_y = dpos.Y();
				sprof_b_z = dpos.Z();
				sprof_b_px = dmom.Px();
				sprof_b_py = dmom.Py();
				sprof_b_pz = dmom.Pz();

				}// shower b
				if(contain_shower_a == -999){  
				contain_shower_a = mccontained;  
				auto pos = SP.Position();
				auto mom = SP.Momentum();
				auto dpos = ShowerDetProf.Position();
				auto dmom = ShowerDetProf.Momentum();
				// truth info
				shower_a_E = SP.E();
				shower_a_x = pos.X();
				shower_a_y = pos.Y();
				shower_a_z = pos.Z();
				shower_a_px = mom.Px();
				shower_a_py = mom.Py();
				shower_a_pz = mom.Pz();
				// for detprof
				sprof_a_E = ShowerDetProf.E();
				sprof_a_x = dpos.X();
				sprof_a_y = dpos.Y();
				sprof_a_z = dpos.Z();
				sprof_a_px = dmom.Px();
				sprof_a_py = dmom.Py();
				sprof_a_pz = dmom.Pz();
				}// shower a

				}// loop over the mcshower
	if(pi0count.first==1 && cmeson==0 && !DalitzDecay){
	std::cout<<"This should always be true  2 = "<<mcshower->size()<<std::endl;
	std::cout<<"Contain A "<<contain_shower_a<<std::endl;
	std::cout<<"Contain B "<<contain_shower_b<<std::endl;
	}	



	// Fill the FullTree

	FullTree->Fill();
//	if(pi0count.first==1) SPTree->Fill();
	if(pi0count.first==1 && cmeson==0) SPTree->Fill();
	if(pi0count.first==1 && cmeson==0 && !DalitzDecay) SP_Gamma_Tree->Fill();
	
    return true;
  }

  bool neutralpion::finalize() {
     if(_fout){
		FullTree->Write();
		SPTree->Write();
		SP_Gamma_Tree->Write();
	      }
    return true;
  }

  void neutralpion::InitializeAnaTree()
        {
        FullTree = new TTree("FullTree","FullTree");
                FullTree->Branch("ccnc",&ccnc,"ccnc/I");
                FullTree->Branch("mode",&mode,"mode/I");
                FullTree->Branch("interaction",&interaction,"interaction/I");
                FullTree->Branch("w",&w,"w/D");
                FullTree->Branch("qsqr",&qsqr,"qsqr/D");
                FullTree->Branch("fsipi0",&fsipi0,"fsipi0/I");

        SPTree = new TTree("SPTree","SPTree");
                SPTree->Branch("ccnc",&ccnc,"ccnc/I");
                SPTree->Branch("mode",&mode,"mode/I");
                SPTree->Branch("interaction",&interaction,"interaction/I");
                SPTree->Branch("status",&status,"status/I");
                SPTree->Branch("w",&w,"w/D");
                SPTree->Branch("qsqr",&qsqr,"qsqr/D");
                SPTree->Branch("fsipi0",&fsipi0,"fsipi0/I");
                SPTree->Branch("energy",&_spenergy,"spenergy/D");
                SPTree->Branch("PposX",&P_x,"P_x/D");
                SPTree->Branch("PposY",&P_y,"P_y/D");
                SPTree->Branch("PposZ",&P_z,"P_z/D");
                SPTree->Branch("PdirX",&P_px,"P_px/D");
                SPTree->Branch("PdirY",&P_py,"P_py/D");
                SPTree->Branch("PdirZ",&P_pz,"P_pz/D");
                SPTree->Branch("Ppmag",&P_pmag,"P_pmag/D");
                SPTree->Branch("protoncount",&protoncount,"protoncount/I");

        SP_Gamma_Tree = new TTree("SP_Gamma_Tree","SP_Gamma_Tree");
                SP_Gamma_Tree->Branch("ccnc",&ccnc,"ccnc/I");
                SP_Gamma_Tree->Branch("mode",&mode,"mode/I");
                SP_Gamma_Tree->Branch("interaction",&interaction,"interaction/I");
                SP_Gamma_Tree->Branch("status",&status,"status/I");
                SP_Gamma_Tree->Branch("w",&w,"w/D");
                SP_Gamma_Tree->Branch("qsqr",&qsqr,"qsqr/D");
                SP_Gamma_Tree->Branch("fsipi0",&fsipi0,"fsipi0/I");
                SP_Gamma_Tree->Branch("energy",&_spenergy,"spenergy/D");
                SP_Gamma_Tree->Branch("PposX",&P_x,"P_x/D");
                SP_Gamma_Tree->Branch("PposY",&P_y,"P_y/D");
                SP_Gamma_Tree->Branch("PposZ",&P_z,"P_z/D");
                SP_Gamma_Tree->Branch("PdirX",&P_px,"P_px/D");
                SP_Gamma_Tree->Branch("PdirY",&P_py,"P_py/D");
                SP_Gamma_Tree->Branch("PdirZ",&P_pz,"P_pz/D");
                SP_Gamma_Tree->Branch("Ppmag",&P_pmag,"P_pmag/D");
                SP_Gamma_Tree->Branch("protoncount",&protoncount,"protoncount/I");
                SP_Gamma_Tree->Branch("contain_shower_a",&contain_shower_a,"contain_shower_a/D");
                SP_Gamma_Tree->Branch("contain_shower_b",&contain_shower_b,"contain_shower_b/D");
                SP_Gamma_Tree->Branch("shower_a_E",&shower_a_E,"shower_a_E/D");
                SP_Gamma_Tree->Branch("shower_a_x",&shower_a_x,"shower_a_x/D");
                SP_Gamma_Tree->Branch("shower_a_y",&shower_a_y,"shower_a_y/D");
                SP_Gamma_Tree->Branch("shower_a_z",&shower_a_z,"shower_a_z/D");
                SP_Gamma_Tree->Branch("shower_a_px",&shower_a_px,"shower_a_px/D");
                SP_Gamma_Tree->Branch("shower_a_py",&shower_a_py,"shower_a_py/D");
                SP_Gamma_Tree->Branch("shower_a_pz",&shower_a_pz,"shower_a_pz/D");
                SP_Gamma_Tree->Branch("shower_b_E",&shower_b_E,"shower_b_E/D");
                SP_Gamma_Tree->Branch("shower_b_x",&shower_b_x,"shower_b_x/D");
                SP_Gamma_Tree->Branch("shower_b_y",&shower_b_y,"shower_b_y/D");
                SP_Gamma_Tree->Branch("shower_b_z",&shower_b_z,"shower_b_z/D");
                SP_Gamma_Tree->Branch("shower_b_px",&shower_b_px,"shower_b_px/D");
                SP_Gamma_Tree->Branch("shower_b_py",&shower_b_py,"shower_b_py/D");
                SP_Gamma_Tree->Branch("shower_b_pz",&shower_b_pz,"shower_b_pz/D");
                SP_Gamma_Tree->Branch("sprof_a_E",&sprof_a_E,"sprof_a_E/D");
                SP_Gamma_Tree->Branch("sprof_a_x",&sprof_a_x,"sprof_a_x/D");
                SP_Gamma_Tree->Branch("sprof_a_y",&sprof_a_y,"sprof_a_y/D");
                SP_Gamma_Tree->Branch("sprof_a_z",&sprof_a_z,"sprof_a_z/D");
                SP_Gamma_Tree->Branch("sprof_a_px",&sprof_a_px,"sprof_a_px/D");
                SP_Gamma_Tree->Branch("sprof_a_py",&sprof_a_py,"sprof_a_py/D");
                SP_Gamma_Tree->Branch("sprof_a_pz",&sprof_a_pz,"sprof_a_pz/D");
                SP_Gamma_Tree->Branch("sprof_b_E",&sprof_b_E,"sprof_b_E/D");
                SP_Gamma_Tree->Branch("sprof_b_x",&sprof_b_x,"sprof_b_x/D");
                SP_Gamma_Tree->Branch("sprof_b_y",&sprof_b_y,"sprof_b_y/D");
                SP_Gamma_Tree->Branch("sprof_b_z",&sprof_b_z,"sprof_b_z/D");
                SP_Gamma_Tree->Branch("sprof_b_px",&sprof_b_px,"sprof_b_px/D");
                SP_Gamma_Tree->Branch("sprof_b_py",&sprof_b_py,"sprof_b_py/D");
                SP_Gamma_Tree->Branch("sprof_b_pz",&sprof_b_pz,"sprof_b_pz/D");


	}

}
#endif
