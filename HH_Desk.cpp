#include "HH_Desk.h"


std::string HH_Desk::to_first_check = "to_first_check";
std::string HH_Desk::from_severity = "from_severity";


HH_Desk::HH_Desk()
{
	SetName("HH_Dest");
	AddInPorts(1, from_severity.c_str());
	AddOutPorts(1, to_first_check.c_str());
	_mState = IDLE;
}


HH_Desk::~HH_Desk()
{
}


bool HH_Desk::ExtTransFn(const CDEVSimMessage &msg)
{
	if (msg.GetPort().compare(from_severity.c_str()) == 0)
	{
		/*COUT << "HH_desk" << ENDL;*/
		CInfo* received_patient_msg = (CInfo*)msg.GetArg(0);
		m_PI = received_patient_msg->data;
		m_PI.delayTime = get_in();
		wait_list.push_back(m_PI);
	}
	return true;
}

bool HH_Desk::IntTransFn()
{
	return true;
}

bool HH_Desk::OutputFn(CDEVSimMessage &msg)
{
	for (std::vector<sPatient_info>::iterator it = wait_list.begin(); it != wait_list.end();)
	{
		it->delayTime--;
		if (it->delayTime <= 0)
		{
			msg.SetPortValue(to_first_check.c_str(), new CInfo(*it));
			it = wait_list.erase(it);
		}
		else
			++it;
	}
	return true;
}

TimeType HH_Desk::TimeAdvanceFn()
{
	return 1;
}

int HH_Desk::get_in()
{
	int i = GLOBAL_VARIABLE->GenRand() % 1000;
	if (i < 673)
	{
		return GLOBAL_VARIABLE->GenRand() % 10;
	}
	else if (i > 672 && i < 866)
	{
		return GLOBAL_VARIABLE->GenRand() % 10 + 10;
	}
	else if (i > 865 && i < 916)
	{
		return GLOBAL_VARIABLE->GenRand() % 10 + 20;
	}
	else if (i > 915 && i < 939)
	{
		return GLOBAL_VARIABLE->GenRand() % 10 + 30;
	}
	else if (i>938 && i < 953)
	{
		return GLOBAL_VARIABLE->GenRand() % 10 + 40;
	}
	else if (i > 952 && i < 962)
	{
		return GLOBAL_VARIABLE->GenRand() % 10 + 50;
	}
	else if (i > 961)
	{
		return GLOBAL_VARIABLE->GenRand() % 20 + 60;
	}
}
