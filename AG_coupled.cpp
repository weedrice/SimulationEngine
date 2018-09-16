#include "AG_coupled.h"
#include "AG_Ambulance.h"
#include "AG_Patient.h"
#include "GlobalVar.h"


std::string CAG_coupled::inC_PatientG_to_AmbulanceG = "PG to AG";
std::string CAG_coupled::inC_HugeH_to_AmbulanceG = "HH to AG";
std::string CAG_coupled::outC_AmbulanceG_to_SmallH = "AG to SH";
std::string CAG_coupled::inC_Firehouse_to_AmbulanceG = "FH to AG";
std::string CAG_coupled::outC_AmbulanceG_to_HugeH = "AG to HH";



CAG_coupled::CAG_coupled()
{
	q = new std::queue < CInfo >;


	SetName("CAG_coupled");

	AddInPorts(3, inC_HugeH_to_AmbulanceG.c_str(), inC_PatientG_to_AmbulanceG.c_str(), inC_Firehouse_to_AmbulanceG.c_str());
	AddOutPorts(2, outC_AmbulanceG_to_SmallH.c_str(), outC_AmbulanceG_to_HugeH.c_str());

	CModel *pAG_Ambulance = new CAG_Ambulance();
	CModel *pAG_Patient = new CAG_Patient(q);


	AddComponent(2, pAG_Ambulance, pAG_Patient);



	AddCoupling(this, inC_HugeH_to_AmbulanceG.c_str(), pAG_Ambulance, CAG_Ambulance::inA_HugeH_to_Ambulance.c_str());
	AddCoupling(this, inC_HugeH_to_AmbulanceG.c_str(), pAG_Patient, CAG_Patient::inA_AmbulanceG_to_Patient_a.c_str());
	AddCoupling(this, inC_PatientG_to_AmbulanceG.c_str(), pAG_Patient, CAG_Patient::inA_AmbulanceG_to_Patient_p.c_str());
	AddCoupling(pAG_Patient, CAG_Patient::outA_Patient_to_AmbulanceG.c_str(), this, outC_AmbulanceG_to_SmallH.c_str());
	AddCoupling(this, inC_Firehouse_to_AmbulanceG.c_str(), pAG_Ambulance, CAG_Ambulance::inC_AmbulanceG_to_Ambulance.c_str());
	AddCoupling(this, inC_Firehouse_to_AmbulanceG.c_str(), pAG_Patient, CAG_Patient::inA_AmbulanceG_to_Patient_a.c_str());
	AddCoupling(pAG_Patient, CAG_Patient::outA_Patient_to_AmbulanceG_direct.c_str(), this, outC_AmbulanceG_to_HugeH.c_str());

}


CAG_coupled::~CAG_coupled()
{
	delete q;
}