#include "Diagnosis.h"
#include <stdlib.h>

std::string Diagnosis::from_surgery_manager = "from_surgery_manager";
std::string Diagnosis::to_surgery_manager = "to_surgery_manager";

Diagnosis::Diagnosis()
{

}

Diagnosis::Diagnosis(int _id)
{
	SetName("Diagnosis");
	AddInPorts(1, from_surgery_manager.c_str());
	AddOutPorts(1, to_surgery_manager.c_str());
	_mState = IDLE;
	id = _id;


}


Diagnosis::~Diagnosis()
{
}

bool Diagnosis::ExtTransFn(const CDEVSimMessage &msg)
{
	if (_mState == IDLE)
	{
		if (msg.GetPort().compare(from_surgery_manager.c_str()) == 0)
		{
			CInfo* received_patient_msg = (CInfo*)msg.GetArg(0);
			m_PI = received_patient_msg->data;
			m_PI.delayTime = 1;/*GLOBAL_VARIABLE->GenRand() % 5 + 6;*/
			patient_list.push_back(m_PI);
		}
	}

	return true;
}

bool Diagnosis::IntTransFn()
{
	return true;
}

bool Diagnosis::OutputFn(CDEVSimMessage &msg)
{
	if (_mState == IDLE)
	{
		for (std::vector<sPatient_info>::iterator it = patient_list.begin(); it != patient_list.end(); it++)
		{
			it->delayTime--;
			if (it->delayTime <= 0)
			{
				msg.SetPortValue(to_surgery_manager.c_str(), new CInfo(*it));
				patient_list.erase(it);
				/*COUT << "ÇùÁø Á¾·á" << ENDL;*/
				break;
			}
		}
	}
	return true;
}

TimeType Diagnosis::TimeAdvanceFn()
{
	if (_mState == IDLE)
	{
		return 1;
	}
}
