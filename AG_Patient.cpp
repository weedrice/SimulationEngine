#include "AG_Patient.h"
#include "GlobalVar.h"

std::string CAG_Patient::inA_AmbulanceG_to_Patient_p = "AG to P(P)";
std::string CAG_Patient::inA_AmbulanceG_to_Patient_a = "AG to P(A)";
std::string CAG_Patient::outA_Patient_to_AmbulanceG = "P to AG";
std::string CAG_Patient::outA_Patient_to_AmbulanceG_direct = "Patient to AG_direct";


CAG_Patient::CAG_Patient(std::queue<CInfo>* pq)
	:m_pQ(pq)
{
	SetName("AG_Patient");

	AddInPorts(2, inA_AmbulanceG_to_Patient_a.c_str(), inA_AmbulanceG_to_Patient_p.c_str());
	AddOutPorts(2, outA_Patient_to_AmbulanceG.c_str(), outA_Patient_to_AmbulanceG_direct.c_str());

	_mState = INIT;

	startPatient = 0;
	howmanytimes = 0;

}


CAG_Patient::~CAG_Patient()
{
}

bool CAG_Patient::ExtTransFn(const CDEVSimMessage &msg)
{
	if (msg.GetPort().compare(inA_AmbulanceG_to_Patient_p.c_str()) == 0 && GLOBAL_VARIABLE->GetAmulanceNum() > 0)
	{
		temp_info = (CInfo *)msg.GetArg(0);

		m_pQ->push(*temp_info);

		_mState = ACTIVE;

		howmanytimes++;

		COUT << " 환자가 들어온 시간 : " << DEVSINTERFACE_PTR->GetCurrentSimulationTime().GetValue() << ENDL;
		COUT << " 남은 소방차 수 : " << GLOBAL_VARIABLE->GetAmulanceNum() << ENDL;
	}
	else if (msg.GetPort().compare(inA_AmbulanceG_to_Patient_p.c_str()) == 0 && GLOBAL_VARIABLE->GetAmulanceNum() <= 0)
	{
		temp_info = (CInfo *)msg.GetArg(0);

		m_pQ->push(*temp_info);

		_mState = QUEUE;

		howmanytimes++;
	}
	else if (msg.GetPort().compare(inA_AmbulanceG_to_Patient_a.c_str()) == 0 && !m_pQ->empty())
	{
		_mState = ACTIVE;
	}
	

	
	return true;
}

bool CAG_Patient::IntTransFn()
{
	if (GLOBAL_VARIABLE->GetAmulanceNum() > 0 && !m_pQ->empty())
		_mState = ACTIVE;
	else if (!m_pQ->empty())
		_mState = QUEUE;
	else
		_mState = INIT;
	return true;
}

bool CAG_Patient::OutputFn(CDEVSimMessage &msg)
{
	if (_mState == ACTIVE)
	{
		//std::cout << "\n 현재 QUEUE SIZE : " <<  m_pQ->size() << std::endl;
		CInfo qtemp = m_pQ->front();


		if (!m_pQ->empty())
		{
			

			/*COUT << "\n-------------------------------" << ENDL;
			COUT << "\n Patient Generate \n Patient Id : " << qtemp.data.id << ENDL;
			COUT << " Patient state : " << (qtemp.data._Pstate == DISASTER ? "DISASTER" : "GENERAL") << ENDL;
			COUT << " Patient Severity : " << qtemp.data.severity << ENDL;
			COUT << " Patient Injury Part : " << qtemp.data.injury_part << ENDL;
			COUT << "\n-------------------------------" << ENDL;*/

			if (qtemp.data.severity != 5)
			{
				if (qtemp.data.huge_h == HH1)
				{
					if (qtemp.data.severity < 3 && GLOBAL_VARIABLE->GetHHDoctorNum(0) > 0)
					{
						GLOBAL_VARIABLE->DecreaseHHDoctorNum(0);
					}
					else if ((qtemp.data.severity >= 3) && (qtemp.data.severity < 5))
					{
						if (GLOBAL_VARIABLE->GetHHNurseNum(0) > 0)
						{
							GLOBAL_VARIABLE->DecreaseHHNurseNum(0);
						}
						else if (GLOBAL_VARIABLE->GetHHNurseNum(0) <= 0 && GLOBAL_VARIABLE->GetHHDoctorNum(0) > 0)
						{
							GLOBAL_VARIABLE->DecreaseHHDoctorNum(0);
						}
					}

				}
				else if (qtemp.data.huge_h == HH2)
				{
					if (qtemp.data.severity < 3 && GLOBAL_VARIABLE->GetHHDoctorNum(1) > 0)
					{
						GLOBAL_VARIABLE->DecreaseHHDoctorNum(1);
					}
					else if ((qtemp.data.severity >= 3) && (qtemp.data.severity < 5))
					{
						if (GLOBAL_VARIABLE->GetHHNurseNum(1) > 0)
						{
							GLOBAL_VARIABLE->DecreaseHHNurseNum(1);
						}
						else if (GLOBAL_VARIABLE->GetHHNurseNum(1) <= 0 && GLOBAL_VARIABLE->GetHHDoctorNum(1) > 0)
						{
							GLOBAL_VARIABLE->DecreaseHHDoctorNum(1);
						}
					}

				}
				else if (qtemp.data.huge_h == HH3)
				{
					if (qtemp.data.severity < 3 && GLOBAL_VARIABLE->GetHHDoctorNum(2) > 0)
					{
						GLOBAL_VARIABLE->DecreaseHHDoctorNum(2);

					}
					else if ((qtemp.data.severity >= 3) && (qtemp.data.severity < 5))
					{
						if (GLOBAL_VARIABLE->GetHHNurseNum(2) > 0)
						{
							GLOBAL_VARIABLE->DecreaseHHNurseNum(2);
						}
						else if (GLOBAL_VARIABLE->GetHHNurseNum(2) <= 0 && GLOBAL_VARIABLE->GetHHDoctorNum(2) > 0)
						{
							GLOBAL_VARIABLE->DecreaseHHDoctorNum(2);
						}
					}
				}
			}

			if (qtemp.data.small_h == NOT)
			{
				qtemp.data.pPosition = AG_H;
				msg.SetPortValue(outA_Patient_to_AmbulanceG_direct.c_str(), new CInfo(qtemp.data));
			}
			else if (qtemp.data.small_h != NOT)
			{
				qtemp.data.pPosition = AG_S;
				msg.SetPortValue(outA_Patient_to_AmbulanceG.c_str(), new CInfo(qtemp.data));

				std::cout << "****  재난지역에서 SH로 환자 출발, 환자 아이디 : " << qtemp.data.id << std::endl;
			}
		
			m_pQ->pop();
			GLOBAL_VARIABLE->DecreaseAmbulanceNum();
			
		}
		
		

	}
 	return true;
}

TimeType CAG_Patient::TimeAdvanceFn()
{
	if (_mState == QUEUE)
		return Infinity;
	else if (_mState == ACTIVE)
		return 0;
	else
		return Infinity;

}


