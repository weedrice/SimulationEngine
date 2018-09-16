#include "Surgery_room.h"
#include <stdlib.h>
#include "GlobalVar.h"


std::string Surgery_room::to_surgery_manager = "to_surgery_manager";
std::string Surgery_room::from_surgery_manager = "from_surgery_manager";
std::string Surgery_room::to_CC = "to_CC";


Surgery_room::Surgery_room()
{
}

Surgery_room::Surgery_room(int _id)
{
	char buf[100];
	sprintf(buf, "Surgery_room[%d]", _id);
	SetName(buf);

	AddInPorts(1, from_surgery_manager.c_str());
	AddOutPorts(2, to_surgery_manager.c_str(), to_CC.c_str());
	id = _id;
	_mState = IDLE;
}


Surgery_room::~Surgery_room()
{
}

bool Surgery_room::ExtTransFn(const CDEVSimMessage &msg)
{
	if (_mState == IDLE)
	{
		if (msg.GetPort().compare(from_surgery_manager.c_str()) == 0)
		{
			CInfo* received_patient_msg = (CInfo*)msg.GetArg(0);
			if (received_patient_msg->get_hh_room() == id)
			{
				starttime = DEVSINTERFACE_PTR->GetCurrentSimulationTime().GetValue();
				m_PI = received_patient_msg->data;
				/*std::cout << "수술실 " << id + 1 << " 수술 시작" << std::endl;*/
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

bool Surgery_room::IntTransFn()
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

bool Surgery_room::OutputFn(CDEVSimMessage &msg)
{
	if (_mState == CURE)
	{

		CInfo* _msg = new CInfo(m_PI);
		if (_msg->data._Pstate == DISASTER)
		{
			GLOBAL_VARIABLE->IncreaseHHSurgeryNum_for_PG(id);
		}
		_msg->set_hh_room(id);
		msg.SetPortValue(to_surgery_manager.c_str(), _msg);
		CInfo* _msg1 = new CInfo(m_PI);
		msg.SetPortValue(to_CC.c_str(), _msg1);
/*

		std::cout << m_PI.id << "번 환자가 수술을 시작한 시간은 " << starttime << "입니다." << std::endl;;
		std::cout << "수술을 마친 시각은 " << DEVSINTERFACE_PTR->GetCurrentSimulationTime().GetValue() << "입니다." << std::endl;*/
		//std::cout << "재난/일반 : " << ((m_PI._Pstate == GENERAL) ? "General" : "Disaster") << std::endl;
		//std::cout << "환자 " << m_PI.id << " 수술 완료" << std::endl;
	}
	else if (_mState == IDLE)
	{
		return true;
	}


	return true;
}

TimeType Surgery_room::TimeAdvanceFn()
{
	if (_mState == IDLE)
	{
		return Infinity;
	}
	else if (_mState == CURE)
	{
		
		/*return 1;*/
		 
		surgery_time = cal_surgery_time(m_PI);
		return surgery_time; // 각 환자별 중증도, 손상 부위를 고려하여 결정
	}
}

int Surgery_room::cal_surgery_time(sPatient_info _data)
{
	// 중증도와 손상 부위를 고려하여 정해진 수술 시간을 return
	if (_data.injury_part == NERVE)
	{
		int i = _data.severity;
		if (i == 1)
		{
			return (GLOBAL_VARIABLE->GenRand() % 30) + 150;
		}
		else if (i == 2)
		{
			return (GLOBAL_VARIABLE->GenRand() % 24) + 120;
		}
		else if (i == 3)
		{
			return (GLOBAL_VARIABLE->GenRand() % 18) + 90;
		}
		else if (i == 4)
		{
			return (GLOBAL_VARIABLE->GenRand() % 15) + 75;
		}
		else if (i == 5)
		{
			return (GLOBAL_VARIABLE->GenRand() % 12) + 60;
		}
	}
	else if (_data.injury_part == CHEST)
	{
		int i = _data.severity;
		if (i == 1)
		{
			return (GLOBAL_VARIABLE->GenRand() % 30) + 120;
		}
		else if (i == 2)
		{
			return (GLOBAL_VARIABLE->GenRand() % 24) + 96;
		}
		else if (i == 3)
		{
			return (GLOBAL_VARIABLE->GenRand() % 18) + 72;
		}
		else if (i == 4)
		{
			return (GLOBAL_VARIABLE->GenRand() % 15) + 60;
		}
		else if (i == 5)
		{
			return (GLOBAL_VARIABLE->GenRand() % 12) + 48;
		}
	}
	else if (_data.injury_part == SPINE)
	{
		int i = _data.severity;
		if (i == 1)
		{
			return (GLOBAL_VARIABLE->GenRand() % 50) + 100;
		}
		else if (i == 2)
		{
			return (GLOBAL_VARIABLE->GenRand() % 50) + 80;
		}
		else if (i == 3)
		{
			return (GLOBAL_VARIABLE->GenRand() % 30) + 60;
		}
		else if (i == 4)
		{
			return (GLOBAL_VARIABLE->GenRand() % 25) + 50;
		}
		else if (i == 5)
		{
			return (GLOBAL_VARIABLE->GenRand() % 20) + 40;
		}

	}
	else if (_data.injury_part == BURN)
	{
		int i = _data.severity;
		if (i == 1)
		{
			return (GLOBAL_VARIABLE->GenRand() % 20) + 100;
		}
		else if (i == 2)
		{
			return (GLOBAL_VARIABLE->GenRand() % 16) + 80;
		}
		else if (i == 3)
		{
			return (GLOBAL_VARIABLE->GenRand() % 12) + 60;
		}
		else if (i == 4)
		{
			return (GLOBAL_VARIABLE->GenRand() % 10) + 50;
		}
		else if (i == 5)
		{
			return (GLOBAL_VARIABLE->GenRand() % 8) + 40;
		}

	}
	else if (_data.injury_part == FRACTURE)
	{
		int i = _data.severity;
		if (i == 1)
		{
			return (GLOBAL_VARIABLE->GenRand() % 20) + 100;
		}
		else if (i == 2)
		{
			return (GLOBAL_VARIABLE->GenRand() % 16) + 64;
		}
		else if (i == 3)
		{
			return (GLOBAL_VARIABLE->GenRand() % 12) + 48;
		}
		else if (i == 4)
		{
			return (GLOBAL_VARIABLE->GenRand() % 10) + 40;
		}
		else if (i == 5)
		{
			return (GLOBAL_VARIABLE->GenRand() % 8) + 32;
		}
	}

}
