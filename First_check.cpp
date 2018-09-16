#include "First_check.h"
#include "GlobalVar.h"
#include <stdlib.h>


std::string First_check::to_manager = "to_manager";
std::string First_check::from_desk = "from_desk";

First_check::First_check()
{

}

First_check::First_check(int _id)
{
	SetName("First_check");
	AddInPorts(1, from_desk.c_str());
	AddOutPorts(1, to_manager.c_str());
	_mState = IDLE;
	id = _id;

	
}


First_check::~First_check()
{
}

bool First_check::ExtTransFn(const CDEVSimMessage &msg)
{
	if (msg.GetPort().compare(from_desk.c_str()) == 0)
	{
		CInfo* received_patient_msg = (CInfo*)msg.GetArg(0);
		m_PI = received_patient_msg->data;
		m_PI.delayTime = 18;
	/*	COUT << "����ȯ�� " << m_PI.id << " �� ���� �� 1�� ���Ḧ ������ �Խ��ϴ�." << ENDL;*/

		if (GLOBAL_VARIABLE->GetHHDoctorNum(id) > 0 && GLOBAL_VARIABLE->GetHHNurseNum(id) > 0)
		{
			GLOBAL_VARIABLE->DecreaseHHDoctorNum(id);
			GLOBAL_VARIABLE->DecreaseHHNurseNum(id);
			wait_list.push_back(received_patient_msg->data);
		}
		else
		{
			waiting.push_back(received_patient_msg->data);
		}

	}
	return true;
}

bool First_check::IntTransFn()
{
	return true;
}

bool First_check::OutputFn(CDEVSimMessage &msg)
{
	for (std::vector<sPatient_info>::iterator it = waiting.begin(); it != waiting.end(); it++)
	{
		if (GLOBAL_VARIABLE->GetHHDoctorNum(id) > 0 && GLOBAL_VARIABLE->GetHHNurseNum(id) > 0)
		{
			GLOBAL_VARIABLE->DecreaseHHDoctorNum(id);
			GLOBAL_VARIABLE->DecreaseHHNurseNum(id);
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
			msg.SetPortValue(to_manager.c_str(), new CInfo(*it));

	/*		COUT << "����ȯ�� " << m_PI.id << " �� 1������� ������ ���ƽ��ϴ�." << ENDL;*/
			wait_list.erase(it);
			break;
		}
	}
	return true;
}

TimeType First_check::TimeAdvanceFn()
{
	if (_mState == IDLE)
	{
		return 1;
	}
}

