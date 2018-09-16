#include "CT_room.h"
#include "GlobalVar.h"

#include <stdlib.h>

std::string CT_room::to_Manager = "to_Manager";
std::string CT_room::from_Manager = "from_Manager";


CT_room::CT_room()
{
}

CT_room::CT_room(int _id)
{
	char buf[100];
	sprintf(buf, "CT_room_[%d]", _id);
	SetName(buf);
	AddInPorts(1, from_Manager.c_str());
	AddOutPorts(1, to_Manager.c_str());
	_mState = IDLE;
	id = _id;


}


CT_room::~CT_room()
{
}

bool CT_room::ExtTransFn(const CDEVSimMessage &msg)
{
	if (_mState == IDLE)
	{
		if (msg.GetPort().compare(from_Manager.c_str()) == 0)
		{
			CInfo* received_patient_msg = (CInfo*)msg.GetArg(0);
			if (received_patient_msg->get_hh_room() == id)
			{
			/*	COUT << "CT�˻�� " << id+1 << "���� ȯ�� ����" << ENDL;*/
				m_PI = received_patient_msg->data;
				_mState = CURE;
			}
			
		}






	}
	else if (_mState == CURE)
	{
		Continue();
	}

	return true;
}

bool CT_room::IntTransFn()
{
	if (_mState == IDLE)
	{
		_mState = IDLE;
	}
	else if (_mState == CURE)
	{
		_mState = IDLE;
	}

	return true;
}

bool CT_room::OutputFn(CDEVSimMessage &msg)
{
	if (_mState == CURE)
	{
		m_PI.CT = true;
		CInfo* _msg = new CInfo(m_PI);
		_msg->set_hh_room(id);
		msg.SetPortValue(to_Manager.c_str(), _msg);

		
	}
	else if (_mState == IDLE)
	{
		return true;
	}

	return true;
}

TimeType CT_room::TimeAdvanceFn()
{
	if (_mState == IDLE)
	{
		return Infinity;
	}
	else if (_mState == CURE)
	{
		return (GLOBAL_VARIABLE->GenRand() % 20) + 15;
	}
}