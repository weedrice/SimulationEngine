#include "HH_Coupled.h"
#include "GlobalVar.h"
#include "HH_check_severity.h"
#include "HH_Desk.h"
#include <vector>


std::string HH_Coupled::from_SH = "from_SH";
std::string HH_Coupled::from_AG = "from_AG";
std::string HH_Coupled::to_AG = "to_AG";
std::string HH_Coupled::to_CC = "to_CC";


HH_Coupled::HH_Coupled()
{
}

HH_Coupled::HH_Coupled(HH_init _init, int _id)
{
	char buf[100];
	sprintf(buf, "HH%d", _id);
	id = _id;
	m_HH = _init;
	SetName(buf);
	HH_receive* receiver = new HH_receive(_id);
	HH_check_severity* severity = new HH_check_severity(_id);
	First_check* checker = new First_check(_id);
	HH_Desk* desk = new HH_Desk();
	HH_Patience_Coupled* coupled = new HH_Patience_Coupled(_id, _init.x_ray_room, _init.ct_room, _init.clinic_room);
	Surgery_Manager* S_manager = new Surgery_Manager(_id);
	Diagnosis* _Diagnosis = new Diagnosis(_id);

	AddInPorts(2, from_AG.c_str(), from_SH.c_str());
	AddOutPorts(2, to_AG.c_str(), to_CC.c_str());
	AddComponent(7, receiver, coupled, S_manager, _Diagnosis, checker, severity, desk);


	AddCoupling(this, from_SH.c_str(), receiver, HH_receive::from_SH.c_str());
	AddCoupling(this, from_AG.c_str(), receiver, HH_receive::from_AG.c_str());
	AddCoupling(receiver, HH_receive::to_AG.c_str(), this, to_AG.c_str());
	AddCoupling(receiver, HH_receive::to_severity.c_str(), severity, HH_check_severity::from_receiver.c_str());
	AddCoupling(receiver, HH_receive::to_coupled.c_str(), coupled, HH_Patience_Coupled::from_receive.c_str());
	AddCoupling(severity, HH_check_severity::to_desk.c_str(), desk, HH_Desk::from_severity.c_str());
	AddCoupling(desk, HH_Desk::to_first_check.c_str(), checker, First_check::from_desk.c_str());
	AddCoupling(checker, First_check::to_manager.c_str(), coupled, HH_Patience_Coupled::from_receive.c_str());
	AddCoupling(coupled, HH_Patience_Coupled::from_Manager_to_Surgery.c_str(), S_manager, Surgery_Manager::from_coupled.c_str());
	AddCoupling(S_manager, Surgery_Manager::to_diagonosis.c_str(), _Diagnosis, Diagnosis::from_surgery_manager.c_str());
	AddCoupling(_Diagnosis, Diagnosis::to_surgery_manager.c_str(), S_manager, Surgery_Manager::from_diagonosis.c_str());


	std::vector<CModel*> Surgery_list;
	for (int i = 0; i < GLOBAL_VARIABLE->GetHHSurgeryNum(_id);i++)
	{
		CModel* temp = new Surgery_room(i);
		AddComponent(1, temp);
		AddCoupling(S_manager, Surgery_Manager::to_surgery.c_str(), temp, Surgery_room::from_surgery_manager.c_str());
		AddCoupling(temp, Surgery_room::to_surgery_manager.c_str(), S_manager, Surgery_Manager::from_surgery.c_str());
		AddCoupling(temp, Surgery_room::to_CC.c_str(), this, this->to_CC.c_str());
		Surgery_list.push_back(temp);

	}
	
}


HH_Coupled::~HH_Coupled()
{
}
