#include "PG_coupled.h"
#include "Patient_Generator.h"
#include "Info.h"
#include <vector>
#include "InitManager.h"


std::string CPG_coupled::outC_PG_to_AG = "PG to AG";
std::string CPG_coupled::outC_PG_to_FH = "PG to FH";
std::string CPG_coupled::outC_PG_to_HH_G = "PG to HH(G)";


 

CPG_coupled::CPG_coupled()
{
	SetName("Patient_Generator");
	
	CInitManager initManager;
	
	AddOutPorts(3, outC_PG_to_AG.c_str(), outC_PG_to_HH_G.c_str(), outC_PG_to_FH.c_str());
	

	std::vector<CModel*> compoList_DP;
	for (std::vector<PG_init>::iterator it = initManager.GetInitVectorDP().begin(); it != initManager.GetInitVectorDP().end(); it++)
	{
		CModel *pPN = new CPatient_Generator(*it);
		AddComponent(1, pPN);
		compoList_DP.push_back(pPN);
		
	}


	for (std::vector<CModel*>::iterator it = compoList_DP.begin(); it != compoList_DP.end(); it++){
		
		AddCoupling(*it, CPatient_Generator::outA_PG_to_AG.c_str(), this, outC_PG_to_AG.c_str());
		AddCoupling(*it, CPatient_Generator::outA_PG_to_FH.c_str(), this, outC_PG_to_FH.c_str());
		
	}


	std::vector<CModel*> compoList_GP;

	for (std::vector<PG_init>::iterator it = initManager.GetInitVectorGP().begin(); it != initManager.GetInitVectorGP().end(); it++)
	{
		CModel *pPN = new CPatient_Generator(*it);
		AddComponent(1, pPN);
		compoList_GP.push_back(pPN);
		
	}

	for (std::vector<CModel*>::iterator it = compoList_GP.begin(); it != compoList_GP.end(); it++){

		AddCoupling(*it, CPatient_Generator::outA_PG_to_HH.c_str(), this, outC_PG_to_HH_G.c_str());
	}



}


CPG_coupled::~CPG_coupled()
{
}






