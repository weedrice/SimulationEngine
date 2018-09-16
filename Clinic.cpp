#include "Clinic.h"
#include "GlobalVar.h"

std::string Clinic::to_Manager = "to_Manager";
std::string Clinic::from_Manager = "from_Manager";


Clinic::Clinic()
{

}

Clinic::Clinic(int _id)
{
	char buf[100];
	sprintf(buf, "Clinic_room_[%d]", _id);
	SetName(buf);
	AddInPorts(1, from_Manager.c_str());
	AddOutPorts(1, to_Manager.c_str());
	_mState = IDLE;
	id = _id;


}


Clinic::~Clinic()
{
}

bool Clinic::ExtTransFn(const CDEVSimMessage &msg)
{
	
	if (_mState == IDLE)
	{
		if (msg.GetPort().compare(from_Manager.c_str()) == 0)
		{
			CInfo* received_patient_msg = (CInfo*)msg.GetArg(0);
			if (received_patient_msg->get_hh_room() == id)
			{
				/*COUT << "임상병리검사실 " << id+1 << "에서 환자 받음" << ENDL;*/
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

bool Clinic::IntTransFn()
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

bool Clinic::OutputFn(CDEVSimMessage &msg)
{
	if (_mState == CURE)
	{
		m_PI.Clinic = true;
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

TimeType Clinic::TimeAdvanceFn()
{
	if (_mState == IDLE)
	{
		return Infinity;
	}
	else if (_mState == CURE)
	{
		return (GLOBAL_VARIABLE->GenRand() % 20) + 40;
	}
}
