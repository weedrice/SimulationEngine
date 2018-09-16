#include "HH_receive.h"
#include <time.h>
#include "GlobalVar.h"

std::string HH_receive::to_coupled = "to_coupled";
std::string HH_receive::from_AG = "from_AG";
std::string HH_receive::from_SH = "from_SH";
std::string HH_receive::to_severity = "to_severity";
std::string HH_receive::to_AG = "to_AG";

HH_receive::HH_receive()
{
	
}

HH_receive::HH_receive(int id)
{
	SetName("HH_receive");
	AddInPorts(2, from_SH.c_str(), from_AG.c_str());
	AddOutPorts(3, to_coupled.c_str(), to_severity.c_str(), to_AG.c_str());
	_mState = IDLE;
	_id = id;
}

HH_receive::~HH_receive()
{

}

bool HH_receive::ExtTransFn(const CDEVSimMessage &msg)
{
	if (msg.GetPort().compare(from_AG.c_str()) == 0)
	{
		CInfo* arrived_patient_msg = (CInfo*)msg.GetArg(0);
				
		if (arrived_patient_msg->data.huge_h == _id)
		{
			if (arrived_patient_msg->data.severity < 3)
			{
				GLOBAL_VARIABLE->IncreaseHHDoctorNum(_id);
			}
			else if (arrived_patient_msg->data.severity >= 3 && arrived_patient_msg->data.severity < 5)
			{
				GLOBAL_VARIABLE->IncreaseHHNurseNum(_id);
			}


			m_PI = arrived_patient_msg->data;
			pVector.push_back(m_PI);
			_mState = SEND;
			/*if (m_PI._Pstate == DISASTER)
			{
				GLOBAL_VARIABLE->IncreaseHHnum();
				COUT << "환자가 병원에 도착한 시각 : " << DEVSINTERFACE_PTR->GetCurrentSimulationTime().GetValue() << ENDL;
				COUT << "재난지역에서 환자 " << m_PI.id<<"가 "<<_id<< "에 도착" << ENDL;
				COUT << "대형병원에서 받은 환자수" << GLOBAL_VARIABLE->GetGetHHNum() << "대형병원에서 받았습니다" << ENDL;
			}
			else if (m_PI._Pstate == GENERAL)
			{
				;/ *COUT << "내원환자 "<<m_PI.id<<" 도착" << ENDL;* /
			}*/
		}
	}
	else if (msg.GetPort().compare(from_SH.c_str()) == 0)
	{
		CInfo* arrived_patient_msg = (CInfo*)msg.GetArg(0);

		std::cout << " SH로부터 HH에 환자가 도착하였습니다.  환자 아이디 : " << arrived_patient_msg->data.id << std::endl;
		
		if (arrived_patient_msg->data.huge_h == _id)
		{
			if (arrived_patient_msg->data.severity < 3)
			{
				GLOBAL_VARIABLE->IncreaseHHDoctorNum(_id);
			}
			else if (arrived_patient_msg->data.severity >= 3 && arrived_patient_msg->data.severity < 5)
			{
				GLOBAL_VARIABLE->IncreaseHHNurseNum(_id);
			}


			m_PI = arrived_patient_msg->data;
			pVector.push_back(m_PI);
			_mState = SEND;
			std::cout << "중소형 병원에서 환자 "<<m_PI.id<<" 도착" << std::endl;
			std::cout << "대형병원에서 받은 환자수" << GLOBAL_VARIABLE->GetGetHHNum() << "대형병원에서 받았습니다" << std::endl;
			GLOBAL_VARIABLE->IncreaseHHnum();
		}
	}
	


	return true;
}

bool HH_receive::IntTransFn()
{
	if (_mState == IDLE)
	{
		_mState = IDLE;
	}
	else if (_mState == SEND)
	{
		_mState = IDLE;
	}

	return true;
}

bool HH_receive::OutputFn(CDEVSimMessage &msg)
{
	if (_mState == SEND)
	{
		if (pVector.size() > 1)
		{

			for (std::vector<sPatient_info>::iterator it = pVector.begin(); it != pVector.end(); it++)
			{
				if (it->_Pstate == DISASTER)
				{
					set_P_state();
					msg.SetPortValue(to_coupled.c_str(), new CInfo(*it));
					msg.SetPortValue(to_AG.c_str(), NULL);
					/*COUT << "Coupled로 환자 보냄" << ENDL;*/
				}
				else if (it->_Pstate == GENERAL)
				{
					set_P_state();
					msg.SetPortValue(to_severity.c_str(), new CInfo(*it));
					/*COUT << "Check로 환자 보냄" << ENDL;*/
				}
			}
			pVector.clear();
		}
		else
		{
			m_PI = pVector.front();
			if (m_PI._Pstate == DISASTER)
			{
				set_P_state();
				msg.SetPortValue(to_coupled.c_str(), new CInfo(m_PI));
				msg.SetPortValue(to_AG.c_str(), NULL);
				/*COUT << "Coupled로 환자 보냄" << ENDL;*/
			}
			else if (m_PI._Pstate == GENERAL)
			{
				set_P_state();
				msg.SetPortValue(to_severity.c_str(), new CInfo(m_PI));
				/*COUT << "Check로 환자 보냄" << ENDL;*/
			}
			pVector.erase(pVector.begin());
		}
	}
	return true;
}

TimeType HH_receive::TimeAdvanceFn()
{
	if (_mState == IDLE)
	{
		return Infinity;
	}
	else if (_mState == SEND)
	{
		return 0;
	}
}

void HH_receive::set_P_state()
{


	if (GLOBAL_VARIABLE->GenRand() % 10000 > 7000)
	{
		m_PI.X_ray = true;
	}
	else
	{
		m_PI.X_ray = false;
	}

	if (GLOBAL_VARIABLE->GenRand() % 10000 > 4000)
	{
		m_PI.CT = true;
	}
	else
	{
		m_PI.CT = false;
	}

	if (GLOBAL_VARIABLE->GenRand() % 10000 > 2000)
	{
		m_PI.Clinic = true;
	}
	else
	{
		m_PI.Clinic = false;
	}
}