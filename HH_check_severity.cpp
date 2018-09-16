#include "HH_check_severity.h"



std::string HH_check_severity::to_desk = "to_desk";
std::string HH_check_severity::from_receiver = "from_receiver";


HH_check_severity::HH_check_severity()
{
}

HH_check_severity::HH_check_severity(int _id)
{
	SetName("HH_check_severity");
	AddInPorts(1, from_receiver.c_str());
	AddOutPorts(1, to_desk.c_str());
	id = _id;
	_mState = IDLE;
}


HH_check_severity::~HH_check_severity()
{
}

bool HH_check_severity::ExtTransFn(const CDEVSimMessage &msg)
{
	if (msg.GetPort().compare(from_receiver.c_str()) == 0)
	{
		/*COUT << "Check_severity" << ENDL;*/
		CInfo* received_patient_msg = (CInfo*) msg.GetArg(0);
		m_PI = received_patient_msg->data;
		/*m_PI.delayTime = init.time;*/
		if (GLOBAL_VARIABLE->GetHHDoctorNum(id) > 0)
		{
			wait_list.push_back(m_PI);
			GLOBAL_VARIABLE->DecreaseHHDoctorNum(id);
		}
		else
		{
			waiting.push_back(m_PI);
		}
	}
	return true;
}

bool HH_check_severity::IntTransFn()
{
	return true;
}

bool HH_check_severity::OutputFn(CDEVSimMessage &msg)
{
	for (std::vector<sPatient_info>::iterator it = waiting.begin(); it != waiting.end(); it++)
	{
		if (GLOBAL_VARIABLE->GetHHDoctorNum(id) > 0 && GLOBAL_VARIABLE->GetHHNurseNum(id) > 0)
		{
			GLOBAL_VARIABLE->DecreaseHHDoctorNum(id);
			wait_list.push_back(*it);
			waiting.erase(it);
			break;
		}

	}
	for (std::vector<sPatient_info>::iterator it = wait_list.begin(); it != wait_list.end(); it++)
	{
		it->delayTime--;
		if (it->delayTime <= 0)
		{
			msg.SetPortValue(to_desk.c_str(), new CInfo(*it));
			GLOBAL_VARIABLE->IncreaseHHDoctorNum(id);
			wait_list.erase(it);
			break;
		}
	}
	return true;
}

TimeType HH_check_severity::TimeAdvanceFn()
{
	return 1;
}