#include "X_ray.h"
#include "GlobalVar.h"
#include <stdlib.h>


std::string X_ray::to_Manager = "to_Manager";
std::string X_ray::from_Manager = "from_Manager";



X_ray::X_ray(int _id)
{
	char buf[100];
	sprintf(buf, "X_ray_[%d]", _id);
	SetName(buf);
	
	AddInPorts(1, from_Manager.c_str());
	AddOutPorts(1, to_Manager.c_str());
	id = _id;
	_mState = IDLE;
}

X_ray::X_ray()
{

}


X_ray::~X_ray()
{
}

bool X_ray::ExtTransFn(const CDEVSimMessage &msg)
{
	if (_mState == IDLE)
	{
		if (msg.GetPort().compare(from_Manager.c_str()) == 0)
		{
			CInfo* received_patient_msg = (CInfo*)msg.GetArg(0);
			if (received_patient_msg->get_hh_room() == id)
			{
				/*COUT << "X-ray 검사실 " << id+1 << "에서 환자 받음" << ENDL;*/
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

bool X_ray::IntTransFn()
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

bool X_ray::OutputFn(CDEVSimMessage &msg)
{
	if (_mState == CURE)
	{
		m_PI.X_ray = true;
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

TimeType X_ray::TimeAdvanceFn()
{
	if (_mState == IDLE)
	{
		return Infinity;
	}
	else if (_mState == CURE)
	{
		return (GLOBAL_VARIABLE->GenRand() % 5) + 5;
	}
}
