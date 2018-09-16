#include "Surgery_Manager.h"
#include "GlobalVar.h"
#include "Info.h"


std::string Surgery_Manager::to_diagonosis = "to_diagonosis";
std::string Surgery_Manager::to_surgery = "to_surgery";
std::string Surgery_Manager::from_coupled = "from_coupled";
std::string Surgery_Manager::from_surgery = "from_surgery";
std::string Surgery_Manager::from_diagonosis = "from_diagonosis";

Surgery_Manager::Surgery_Manager()
{

}

Surgery_Manager::Surgery_Manager(int _id)
{
	SetName("Surgery_Manager");
	id = _id;
	AddInPorts(3, from_coupled.c_str(), from_surgery.c_str(), from_diagonosis.c_str());
	AddOutPorts(2, to_surgery.c_str(), to_diagonosis.c_str());
	_mState = IDLE;
	surgery_room = GLOBAL_VARIABLE->GetHHSurgeryNum(id);
	GLOBAL_VARIABLE->SetPL(id, 0);
	available_surgery = new bool[surgery_room];
	for (int i = 0; i < surgery_room; i++)
	{
		available_surgery[i] = false;
	}
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			count_severity[i][j] = 0;
		}
	}
	GLOBAL_VARIABLE->setDiagnosisNum(id);
}


Surgery_Manager::~Surgery_Manager()
{
}

bool Surgery_Manager::ExtTransFn(const CDEVSimMessage & _msg)
{

	/*if (DEVSINTERFACE_PTR->GetCurrentSimulationTime().GetValue() > 720)
	{

		/ *std::cout << "마지막 환자 넘버 : " << GLOBAL_VARIABLE->GetDisasterPatientLast() << std::endl;* /

		//system("PAUSE");
		//std::cout << "출력 " << std::endl;
	}*/

	if (_msg.GetPort().compare(from_coupled.c_str()) == 0)
	{
		CInfo* received_patient_msg = (CInfo*)_msg.GetArg(0);
		m_PI = received_patient_msg->data;
		
		//////////////////////////////////////////////////////////////////////////
		// 2014.02.09 modified by yjkim
		// In order to track patient
		GLOBAL_VARIABLE->InsertToPatientList(id, m_PI);
		//////////////////////////////////////////////////////////////////////////

		/*if (m_PI._Pstate == DISASTER)
			Disaster.push_back(m_PI);*/

		if (m_PI.injury_part == NERVE)
		{
			if (m_PI.severity == 6)
			{
				pDiagnosis.push_back(m_PI);
			}
			else
			{
				pNERVE.push_back(m_PI);
			}
		}
		else if (m_PI.injury_part == CHEST)
		{
			if (m_PI.severity == 6)
			{
				pDiagnosis.push_back(m_PI);
			}
			else
			{
				pCHEST.push_back(m_PI);
			}
		}
		else if (m_PI.injury_part == SPINE)
		{
			if (m_PI.severity == 6)
			{
				pDiagnosis.push_back(m_PI);
			}
			else
			{
				pSPINE.push_back(m_PI);
			}
		}
		else if (m_PI.injury_part == BURN)
		{
			if (m_PI.severity == 6)
			{
				pDiagnosis.push_back(m_PI);
			}
			else
			{
				pBURN.push_back(m_PI);
			}
		}
		else if (m_PI.injury_part == FRACTURE)
		{
			if (m_PI.severity == 6)
			{
				pDiagnosis.push_back(m_PI);
			}
			else
			{
				pFRACTURE.push_back(m_PI);
			}
		}
		GLOBAL_VARIABLE->IncreasePL(id);

		_mState = SEND;
	}
	else if (_msg.GetPort().compare(from_surgery.c_str()) == 0)
	{

		CInfo* temp = (CInfo*)_msg.GetArg(0);
		available_surgery[temp->get_hh_room()] = false;
		GLOBAL_VARIABLE->IncreaseHHNurseNum(id);
		GLOBAL_VARIABLE->IncreaseHHNurseNum(id);
		/*std::cout << temp->data.id << "번 환자의 수술이 완료되었습니다." << std::endl;*/
		if (temp->data.injury_part == NERVE)
		{
			GLOBAL_VARIABLE->IncreaseHHNERVENum(id);
			GLOBAL_VARIABLE->IncreaseHHSurgeryNum(id);

		}
		else if (temp->data.injury_part == SPINE)
		{
			GLOBAL_VARIABLE->IncreaseHHSPINENum(id);
			GLOBAL_VARIABLE->IncreaseHHSurgeryNum(id);

		}
		else if (temp->data.injury_part == FRACTURE)
		{
			GLOBAL_VARIABLE->IncreaseHHFRACTURENum(id);
			GLOBAL_VARIABLE->IncreaseHHSurgeryNum(id);

		}
		else if (temp->data.injury_part == BURN)
		{
			GLOBAL_VARIABLE->IncreaseHHBURNNum(id);
			GLOBAL_VARIABLE->IncreaseHHSurgeryNum(id);

		}
		else
		{
			GLOBAL_VARIABLE->IncreaseHHCHESTNum(id);
			GLOBAL_VARIABLE->IncreaseHHSurgeryNum(id);

		}
		_mState = SEND;
	}
	else if (_msg.GetPort().compare(from_diagonosis.c_str()) == 0)
	{
		CInfo* temp = (CInfo*)_msg.GetArg(0);
		GLOBAL_VARIABLE->IncreaseDiagnosis(id);
		/*std::cout << temp->data.id << "번 환자의 협진 완료" << std::endl;*/
		if (temp->data.injury_part == NERVE)
		{
			GLOBAL_VARIABLE->IncreaseHHNERVENum(id);
		}
		else if (temp->data.injury_part == SPINE)
		{
			GLOBAL_VARIABLE->IncreaseHHSPINENum(id);
		}
		else if (temp->data.injury_part == FRACTURE)
		{
			GLOBAL_VARIABLE->IncreaseHHFRACTURENum(id);
		}
		else if (temp->data.injury_part == BURN)
		{
			GLOBAL_VARIABLE->IncreaseHHBURNNum(id);
		}
		else
		{
			GLOBAL_VARIABLE->IncreaseHHCHESTNum(id);
		}
		GLOBAL_VARIABLE->IncreaseHHNurseNum(id);
		GLOBAL_VARIABLE->IncreaseHHDoctorNum(id);
		_mState = SEND;
	}
	return true;
}

bool Surgery_Manager::IntTransFn()
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

bool Surgery_Manager::OutputFn(CDEVSimMessage &_msg)
{
	if (_mState == IDLE)
	{
		return true;
	}
	if (_mState == SEND)
	{
		if (pFRACTURE.size() != 0)
		{
			sPatient_info temp = pFRACTURE.front();

			if (GLOBAL_VARIABLE->GetHHFRACTURENum(id) > 0 && GLOBAL_VARIABLE->GetHHNurseNum(id) > 1
				&& GLOBAL_VARIABLE->GetHHSurgeryNum(id) > 0)
			{
				for (int i = 0; i < surgery_room; i++)
				{
					if (available_surgery[i] == false)
					{
						CInfo* msg = new CInfo(temp);
						msg->set_hh_room(i);
						_msg.SetPortValue(to_surgery.c_str(), msg);
						/*std::cout << "수술실 " << i + 1 << "이 수술중" << std::endl; */
						GLOBAL_VARIABLE->DecreasePL(id);
						available_surgery[i] = true;
						GLOBAL_VARIABLE->DecreaseHHFRACTURENum(id);
						GLOBAL_VARIABLE->DecreaseHHNurseNum(id);
						GLOBAL_VARIABLE->DecreaseHHNurseNum(id);
						GLOBAL_VARIABLE->DecreaseHHSurgeryNum(id);
						pFRACTURE.erase(pFRACTURE.begin());

						//////////////////////////////////////////////////////////////////////////
						// 2014.02.09 modified by yjkim
						// In order to track patient
						GLOBAL_VARIABLE->RemoveFromPatientList(id, temp.id);
						//////////////////////////////////////////////////////////////////////////
						break;
					}
				}
			}
		}
		if (pBURN.size() != 0)
		{
			sPatient_info temp = pBURN.front();
			if (GLOBAL_VARIABLE->GetHHBURNNum(id) > 0 && GLOBAL_VARIABLE->GetHHNurseNum(id) > 1
				&& GLOBAL_VARIABLE->GetHHSurgeryNum(id) > 0)
			{
				for (int i = 0; i < surgery_room; i++)
				{
					if (available_surgery[i] == false)
					{
						CInfo* msg = new CInfo(temp);
						msg->set_hh_room(i);
						_msg.SetPortValue(to_surgery.c_str(), msg);
						/*std::cout << "수술실 " << i + 1 << "이 수술중" << std::endl; */
						GLOBAL_VARIABLE->DecreasePL(id);
						available_surgery[i] = true;
						GLOBAL_VARIABLE->DecreaseHHBURNNum(id);
						GLOBAL_VARIABLE->DecreaseHHNurseNum(id);
						GLOBAL_VARIABLE->DecreaseHHNurseNum(id);
						GLOBAL_VARIABLE->DecreaseHHSurgeryNum(id);
						pBURN.erase(pBURN.begin());

						//////////////////////////////////////////////////////////////////////////
						// 2014.02.09 modified by yjkim
						// In order to track patient
						GLOBAL_VARIABLE->RemoveFromPatientList(id, temp.id);
						//////////////////////////////////////////////////////////////////////////
						break;
					}
				}
			}
		}
		if (pSPINE.size() != 0)
		{
			sPatient_info temp = pSPINE.front();

			if (GLOBAL_VARIABLE->GetHHSPINENum(id) > 0 && GLOBAL_VARIABLE->GetHHNurseNum(id) > 1
				&& GLOBAL_VARIABLE->GetHHSurgeryNum(id) > 0)
			{

				for (int i = 0; i < surgery_room; i++)
				{
					if (available_surgery[i] == false)
					{
						CInfo* msg = new CInfo(temp);
						msg->set_hh_room(i);
						_msg.SetPortValue(to_surgery.c_str(), msg);
						/*std::cout << "수술실 " << i + 1 << "이 수술중" << std::endl; */
						GLOBAL_VARIABLE->DecreasePL(id);
						available_surgery[i] = true;
						GLOBAL_VARIABLE->DecreaseHHSPINENum(id);
						GLOBAL_VARIABLE->DecreaseHHNurseNum(id);
						GLOBAL_VARIABLE->DecreaseHHNurseNum(id);
						GLOBAL_VARIABLE->DecreaseHHSurgeryNum(id);
						pSPINE.erase(pSPINE.begin());

						//////////////////////////////////////////////////////////////////////////
						// 2014.02.09 modified by yjkim
						// In order to track patient
						GLOBAL_VARIABLE->RemoveFromPatientList(id, temp.id);
						//////////////////////////////////////////////////////////////////////////
						break;
					}
				}
			}
		}
		if (pCHEST.size() != 0)
		{
			sPatient_info temp = pCHEST.front();

			if (GLOBAL_VARIABLE->GetHHCHESTNum(id) > 0 && GLOBAL_VARIABLE->GetHHNurseNum(id) > 1
				&& GLOBAL_VARIABLE->GetHHSurgeryNum(id) > 0)
			{

				for (int i = 0; i < surgery_room; i++)
				{
					if (available_surgery[i] == false)
					{
						CInfo* msg = new CInfo(temp);
						msg->set_hh_room(i);
						_msg.SetPortValue(to_surgery.c_str(), msg);
						/*std::cout << "수술실 " << i + 1 << "이 수술중" << std::endl; */
						GLOBAL_VARIABLE->DecreasePL(id);
						available_surgery[i] = true;
						GLOBAL_VARIABLE->DecreaseHHCHESTNum(id);
						GLOBAL_VARIABLE->DecreaseHHNurseNum(id);
						GLOBAL_VARIABLE->DecreaseHHNurseNum(id);
						GLOBAL_VARIABLE->DecreaseHHSurgeryNum(id);
						pCHEST.erase(pCHEST.begin());

						//////////////////////////////////////////////////////////////////////////
						// 2014.02.09 modified by yjkim
						// In order to track patient
						GLOBAL_VARIABLE->RemoveFromPatientList(id, temp.id);
						//////////////////////////////////////////////////////////////////////////
						break;
					}
				}
			}
		}
		if (pNERVE.size() != 0)
		{
			sPatient_info temp = pNERVE.front();

			if (GLOBAL_VARIABLE->GetHHNERVENum(id) > 0 && GLOBAL_VARIABLE->GetHHNurseNum(id) > 1
				&& GLOBAL_VARIABLE->GetHHSurgeryNum(id) > 0)
			{
				for (int i = 0; i < surgery_room; i++)
				{
					if (available_surgery[i] == false)
					{
						CInfo* msg = new CInfo(temp);
						msg->set_hh_room(i);
						_msg.SetPortValue(to_surgery.c_str(), msg);
						/*std::cout << "수술실 " << i + 1 << "이 수술중" << std::endl; */
						GLOBAL_VARIABLE->DecreasePL(id);
						available_surgery[i] = true;
						GLOBAL_VARIABLE->DecreaseHHNERVENum(id);
						GLOBAL_VARIABLE->DecreaseHHNurseNum(id);
						GLOBAL_VARIABLE->DecreaseHHNurseNum(id);
						GLOBAL_VARIABLE->DecreaseHHSurgeryNum(id);
						pNERVE.erase(pNERVE.begin());

						//////////////////////////////////////////////////////////////////////////
						// 2014.02.09 modified by yjkim
						// In order to track patient
						GLOBAL_VARIABLE->RemoveFromPatientList(id, temp.id);
						//////////////////////////////////////////////////////////////////////////
						break;
					}
				}
			}
		}
		if (pDiagnosis.size() != 0)
		{
			CInfo temp = CInfo(pDiagnosis.front());
			if (temp.data.injury_part == NERVE)
			{
				if (GLOBAL_VARIABLE->GetHHNERVENum(id) > 0 && GLOBAL_VARIABLE->GetHHDoctorNum(id) > 0 &&
					GLOBAL_VARIABLE->GetHHNurseNum(id) > 0)
				{
					GLOBAL_VARIABLE->DecreaseHHNERVENum(id);
					GLOBAL_VARIABLE->DecreaseHHDoctorNum(id);
					GLOBAL_VARIABLE->DecreaseHHNurseNum(id);

					_msg.SetPortValue(to_diagonosis.c_str(), new CInfo(temp));
					/*std::cout << "환자가 협진을 받으러 출발" << std::endl;*/
					GLOBAL_VARIABLE->DecreasePL(id);
					pDiagnosis.erase(pDiagnosis.begin());
				}
			}
			else if (temp.data.injury_part == SPINE)
			{
				if (GLOBAL_VARIABLE->GetHHSPINENum(id) > 0 && GLOBAL_VARIABLE->GetHHDoctorNum(id) > 0 &&
					GLOBAL_VARIABLE->GetHHNurseNum(id) > 0)
				{
					GLOBAL_VARIABLE->DecreaseHHSPINENum(id);
					GLOBAL_VARIABLE->DecreaseHHDoctorNum(id);
					GLOBAL_VARIABLE->DecreaseHHNurseNum(id);

					_msg.SetPortValue(to_diagonosis.c_str(), new CInfo(temp));
					/*std::cout << "환자가 협진을 받으러 출발" << std::endl;*/
					GLOBAL_VARIABLE->DecreasePL(id);
					pDiagnosis.erase(pDiagnosis.begin());
				}
			}
			else if (temp.data.injury_part == BURN)
			{
				if (GLOBAL_VARIABLE->GetHHBURNNum(id) > 0 && GLOBAL_VARIABLE->GetHHDoctorNum(id) > 0 &&
					GLOBAL_VARIABLE->GetHHNurseNum(id) > 0)
				{
					GLOBAL_VARIABLE->DecreaseHHBURNNum(id);
					GLOBAL_VARIABLE->DecreaseHHDoctorNum(id);
					GLOBAL_VARIABLE->DecreaseHHNurseNum(id);

					_msg.SetPortValue(to_diagonosis.c_str(), new CInfo(temp));
					/*std::cout << "환자가 협진을 받으러 출발" << std::endl;*/
					GLOBAL_VARIABLE->DecreasePL(id);
					pDiagnosis.erase(pDiagnosis.begin());
				}
			}
			else if (temp.data.injury_part == CHEST)
			{
				if (GLOBAL_VARIABLE->GetHHCHESTNum(id) > 0 && GLOBAL_VARIABLE->GetHHDoctorNum(id) > 0 &&
					GLOBAL_VARIABLE->GetHHNurseNum(id) > 0)
				{
					GLOBAL_VARIABLE->DecreaseHHCHESTNum(id);
					GLOBAL_VARIABLE->DecreaseHHDoctorNum(id);
					GLOBAL_VARIABLE->DecreaseHHNurseNum(id);

					_msg.SetPortValue(to_diagonosis.c_str(), new CInfo(temp));
					/*std::cout << "환자가 협진을 받으러 출발" << std::endl;*/
					GLOBAL_VARIABLE->DecreasePL(id);
					pDiagnosis.erase(pDiagnosis.begin());
				}
			}
			else if (temp.data.injury_part == FRACTURE)
			{
				if (GLOBAL_VARIABLE->GetHHFRACTURENum(id) > 0 && GLOBAL_VARIABLE->GetHHDoctorNum(id) > 0 &&
					GLOBAL_VARIABLE->GetHHNurseNum(id) > 0)
				{
					GLOBAL_VARIABLE->DecreaseHHFRACTURENum(id);
					GLOBAL_VARIABLE->DecreaseHHDoctorNum(id);
					GLOBAL_VARIABLE->DecreaseHHNurseNum(id);
					_msg.SetPortValue(to_diagonosis.c_str(), new CInfo(temp));
					/*std::cout << "환자가 협진을 받으러 출발" << std::endl;*/
					GLOBAL_VARIABLE->DecreasePL(id);
					pDiagnosis.erase(pDiagnosis.begin());
				}
			}

			//////////////////////////////////////////////////////////////////////////
			// 2014.02.09 modified by yjkim
			// In order to track patient
			GLOBAL_VARIABLE->RemoveFromPatientList(id, temp.data.id);
			//////////////////////////////////////////////////////////////////////////
		}

		// 	std::cout << " 재난 환자 수술 전 대기자 : " << Disaster.size() << std::endl;
		// 	std::cout << id << "병원 응급 의사 수 : " << GLOBAL_VARIABLE->GetHHDoctorNum(id) << std::endl;
		// 	std::cout << id << "병원 간호사 수 : " << GLOBAL_VARIABLE->GetHHNurseNum(id) << std::endl;
		/*std::cout << id << "병원 수술 대기자 수 " << pBURN.size() + pCHEST.size() + pFRACTURE.size() + pSPINE.size() + pNERVE.size() << "명" << std::endl;
		std::cout << id << "병원 협진 대기자 수 " << pDiagnosis.size() << std::endl;*/

		/*for (int i = 0; i < 5; i++)
		{
			std::cout << "신경이 중증도 " << i << "로 아픈 환자 수 : " << count_severity[0][i] << std::endl;
			std::cout << "흉부가 중증도 " << i << "로 아픈 환자 수 : " << count_severity[1][i] << std::endl;
			std::cout << "척추가 중증도 " << i << "로 아픈 환자 수 : " << count_severity[2][i] << std::endl;
			std::cout << "화상이 중증도 " << i << "로 아픈 환자 수 : " << count_severity[3][i] << std::endl;
			std::cout << "골절이 중증도 " << i << "로 아픈 환자 수 : " << count_severity[4][i] << std::endl;
		}*/
		return true;
	}

	return false;
}

TimeType Surgery_Manager::TimeAdvanceFn()
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

/*
if (pVector.size() != 0)
{
sPatient_info temp = pVector.front();

if (temp.injury_part == NERVE)
{
if (temp.severity == 6)
{
if (GLOBAL_VARIABLE->GetHHNERVENum(id) > 0 && GLOBAL_VARIABLE->GetHHDoctorNum(id) > 0 &&
GLOBAL_VARIABLE->GetHHNurseNum(id) > 0)
{
GLOBAL_VARIABLE->DecreaseHHNERVENum(id);
GLOBAL_VARIABLE->DecreaseHHDoctorNum(id);
GLOBAL_VARIABLE->DecreaseHHNurseNum(id);

_msg.SetPortValue(to_diagonosis.c_str(), new CInfo(temp));
//		std::cout << "환자가 협진을 받으러 출발" << std::endl;
GLOBAL_VARIABLE->DecreasePL(id);
pVector.erase(pVector.begin());
}
}
else
{
if (GLOBAL_VARIABLE->GetHHNERVENum(id) > 0 && GLOBAL_VARIABLE->GetHHNurseNum(id) > 1
&& GLOBAL_VARIABLE->GetHHSurgeryNum(id) > 0)
{
GLOBAL_VARIABLE->DecreaseHHNERVENum(id);
GLOBAL_VARIABLE->DecreaseHHNurseNum(id);
GLOBAL_VARIABLE->DecreaseHHNurseNum(id);

for (int i = 0; i < surgery_room; i++)
{
if (available_surgery[i] == false)
{
CInfo* msg = new CInfo(temp);
msg->set_hh_room(i);
_msg.SetPortValue(to_surgery.c_str(), msg);
/ *std::cout << "수술실 " << i + 1 << "이 수술중" << std::endl; * /
GLOBAL_VARIABLE->DecreasePL(id);
available_surgery[i] = true;
GLOBAL_VARIABLE->DecreaseHHSurgeryNum(id);
pVector.erase(pVector.begin());
break;
}
}
}
}
}
else if (temp.injury_part == CHEST)
{
if (temp.severity == 6)
{
if (GLOBAL_VARIABLE->GetHHCHESTNum(id) > 0 && GLOBAL_VARIABLE->GetHHDoctorNum(id) > 0 &&
GLOBAL_VARIABLE->GetHHNurseNum(id) > 0)
{
GLOBAL_VARIABLE->DecreaseHHCHESTNum(id);
GLOBAL_VARIABLE->DecreaseHHDoctorNum(id);
GLOBAL_VARIABLE->DecreaseHHNurseNum(id);

_msg.SetPortValue(to_diagonosis.c_str(), new CInfo(temp));
//		std::cout << "환자가 협진을 받으러 출발" << std::endl;
GLOBAL_VARIABLE->DecreasePL(id);
pVector.erase(pVector.begin());
}
}
else
{
if (GLOBAL_VARIABLE->GetHHCHESTNum(id) > 0 && GLOBAL_VARIABLE->GetHHNurseNum(id) > 1
&& GLOBAL_VARIABLE->GetHHSurgeryNum(id) > 0)
{
GLOBAL_VARIABLE->DecreaseHHCHESTNum(id);
GLOBAL_VARIABLE->DecreaseHHNurseNum(id);
GLOBAL_VARIABLE->DecreaseHHNurseNum(id);

for (int i = 0; i < surgery_room; i++)
{
if (available_surgery[i] == false)
{
CInfo* msg = new CInfo(temp);
msg->set_hh_room(i);
_msg.SetPortValue(to_surgery.c_str(), msg);
/ *std::cout << "수술실 " << i + 1 << "이 수술중" << std::endl; * /
GLOBAL_VARIABLE->DecreasePL(id);
available_surgery[i] = true;
GLOBAL_VARIABLE->DecreaseHHSurgeryNum(id);
pVector.erase(pVector.begin());
break;
}
}
}
}
}
else if (temp.injury_part == SPINE)
{
if (temp.severity == 6)
{
if (GLOBAL_VARIABLE->GetHHSPINENum(id) > 0 && GLOBAL_VARIABLE->GetHHDoctorNum(id) > 0 &&
GLOBAL_VARIABLE->GetHHNurseNum(id) > 0)
{
GLOBAL_VARIABLE->DecreaseHHSPINENum(id);
GLOBAL_VARIABLE->DecreaseHHDoctorNum(id);
GLOBAL_VARIABLE->DecreaseHHNurseNum(id);

_msg.SetPortValue(to_diagonosis.c_str(), new CInfo(temp));
//		std::cout << "환자가 협진을 받으러 출발" << std::endl;
GLOBAL_VARIABLE->DecreasePL(id);
pVector.erase(pVector.begin());
}
}
else
{
if (GLOBAL_VARIABLE->GetHHSPINENum(id) > 0 && GLOBAL_VARIABLE->GetHHNurseNum(id) > 1
&& GLOBAL_VARIABLE->GetHHSurgeryNum(id) > 0)
{
GLOBAL_VARIABLE->DecreaseHHSPINENum(id);
GLOBAL_VARIABLE->DecreaseHHNurseNum(id);
GLOBAL_VARIABLE->DecreaseHHNurseNum(id);

for (int i = 0; i < surgery_room; i++)
{
if (available_surgery[i] == false)
{
CInfo* msg = new CInfo(temp);
msg->set_hh_room(i);
_msg.SetPortValue(to_surgery.c_str(), msg);
/ *std::cout << "수술실 " << i + 1 << "이 수술중" << std::endl; * /
GLOBAL_VARIABLE->DecreasePL(id);
available_surgery[i] = true;
GLOBAL_VARIABLE->DecreaseHHSurgeryNum(id);
pVector.erase(pVector.begin());
break;
}
}
}
}
}
else if (temp.injury_part == BURN)
{
if (temp.severity == 6)
{
if (GLOBAL_VARIABLE->GetHHBURNNum(id) > 0 && GLOBAL_VARIABLE->GetHHDoctorNum(id) > 0 &&
GLOBAL_VARIABLE->GetHHNurseNum(id) > 0)
{
GLOBAL_VARIABLE->DecreaseHHBURNNum(id);
GLOBAL_VARIABLE->DecreaseHHDoctorNum(id);
GLOBAL_VARIABLE->DecreaseHHNurseNum(id);

_msg.SetPortValue(to_diagonosis.c_str(), new CInfo(temp));
//		std::cout << "환자가 협진을 받으러 출발" << std::endl;
GLOBAL_VARIABLE->DecreasePL(id);
pVector.erase(pVector.begin());
}
}
else
{
if (GLOBAL_VARIABLE->GetHHBURNNum(id) > 0 && GLOBAL_VARIABLE->GetHHNurseNum(id) > 1
&& GLOBAL_VARIABLE->GetHHSurgeryNum(id) > 0)
{
GLOBAL_VARIABLE->DecreaseHHBURNNum(id);
GLOBAL_VARIABLE->DecreaseHHNurseNum(id);
GLOBAL_VARIABLE->DecreaseHHNurseNum(id);

for (int i = 0; i < surgery_room; i++)
{
if (available_surgery[i] == false)
{
CInfo* msg = new CInfo(temp);
msg->set_hh_room(i);
_msg.SetPortValue(to_surgery.c_str(), msg);
/ *std::cout << "수술실 " << i + 1 << "이 수술중" << std::endl; * /
GLOBAL_VARIABLE->DecreasePL(id);
available_surgery[i] = true;
GLOBAL_VARIABLE->DecreaseHHSurgeryNum(id);
pVector.erase(pVector.begin());
break;
}
}
}
}
}
else if (temp.injury_part == FRACTURE)
{
if (temp.severity == 6)
{
if (GLOBAL_VARIABLE->GetHHFRACTURENum(id) > 0 && GLOBAL_VARIABLE->GetHHDoctorNum(id) > 0 &&
GLOBAL_VARIABLE->GetHHNurseNum(id) > 0)
{
GLOBAL_VARIABLE->DecreaseHHFRACTURENum(id);
GLOBAL_VARIABLE->DecreaseHHDoctorNum(id);
GLOBAL_VARIABLE->DecreaseHHNurseNum(id);

_msg.SetPortValue(to_diagonosis.c_str(), new CInfo(temp));
//		std::cout << "환자가 협진을 받으러 출발" << std::endl;
GLOBAL_VARIABLE->DecreasePL(id);
pVector.erase(pVector.begin());
}
}
else
{
if (GLOBAL_VARIABLE->GetHHFRACTURENum(id) > 0 && GLOBAL_VARIABLE->GetHHNurseNum(id) > 1
&& GLOBAL_VARIABLE->GetHHSurgeryNum(id) > 0)
{
GLOBAL_VARIABLE->DecreaseHHFRACTURENum(id);
GLOBAL_VARIABLE->DecreaseHHNurseNum(id);
GLOBAL_VARIABLE->DecreaseHHNurseNum(id);

for (int i = 0; i < surgery_room; i++)
{
if (available_surgery[i] == false)
{
CInfo* msg = new CInfo(temp);
msg->set_hh_room(i);
_msg.SetPortValue(to_surgery.c_str(), msg);
/ *std::cout << "수술실 " << i + 1 << "이 수술중" << std::endl; * /
GLOBAL_VARIABLE->DecreasePL(id);
available_surgery[i] = true;
GLOBAL_VARIABLE->DecreaseHHSurgeryNum(id);
pVector.erase(pVector.begin());
break;
}
}
}
}
}
}
}
return true;*/

// 환자의 중증도가 6이면 협진으로 보내고 5이상이면 수술실로 보낸다
/*CInfo* temp = new CInfo(PI_list.front());*/
/*if (temp->data.severity == 6)
{
if (temp->data.injury_part == NERVE)
{
if (GLOBAL_VARIABLE->GetHHNERVENum(id) > 0 && GLOBAL_VARIABLE->GetHHDoctorNum(id) > 0 &&
GLOBAL_VARIABLE->GetHHNurseNum(id) > 0)
{
GLOBAL_VARIABLE->DecreaseHHNERVENum(id);
GLOBAL_VARIABLE->DecreaseHHDoctorNum(id);
GLOBAL_VARIABLE->DecreaseHHNurseNum(id);

_msg.SetPortValue(to_diagonosis.c_str(), temp);
//		std::cout << "환자가 협진을 받으러 출발" << std::endl;
PI_list.erase(PI_list.begin());
GLOBAL_VARIABLE->DecreasePL(id);
}
}
else if (temp->data.injury_part == SPINE)
{
if (GLOBAL_VARIABLE->GetHHSPINENum(id) > 0 && GLOBAL_VARIABLE->GetHHDoctorNum(id) > 0 &&
GLOBAL_VARIABLE->GetHHNurseNum(id) > 0)
{
GLOBAL_VARIABLE->DecreaseHHSPINENum(id);
GLOBAL_VARIABLE->DecreaseHHDoctorNum(id);
GLOBAL_VARIABLE->DecreaseHHNurseNum(id);

_msg.SetPortValue(to_diagonosis.c_str(), temp);
//			std::cout << "환자가 협진을 받으러 출발" << std::endl;
PI_list.erase(PI_list.begin());
GLOBAL_VARIABLE->DecreasePL(id);
}
}
else if (temp->data.injury_part == FRACTURE)
{
if (GLOBAL_VARIABLE->GetHHFRACTURENum(id) > 0 && GLOBAL_VARIABLE->GetHHDoctorNum(id) > 0 &&
GLOBAL_VARIABLE->GetHHNurseNum(id) > 0)
{
GLOBAL_VARIABLE->DecreaseHHFRACTURENum(id);
GLOBAL_VARIABLE->DecreaseHHDoctorNum(id);
GLOBAL_VARIABLE->DecreaseHHNurseNum(id);

_msg.SetPortValue(to_diagonosis.c_str(), temp);
//		std::cout << "환자가 협진을 받으러 출발" << std::endl;
PI_list.erase(PI_list.begin());
GLOBAL_VARIABLE->DecreasePL(id);
}
}
else if (temp->data.injury_part == BURN)
{
if (GLOBAL_VARIABLE->GetHHBURNNum(id) > 0 && GLOBAL_VARIABLE->GetHHDoctorNum(id) > 0 &&
GLOBAL_VARIABLE->GetHHNurseNum(id) > 0)
{
GLOBAL_VARIABLE->DecreaseHHBURNNum(id);
GLOBAL_VARIABLE->DecreaseHHDoctorNum(id);
GLOBAL_VARIABLE->DecreaseHHNurseNum(id);

_msg.SetPortValue(to_diagonosis.c_str(), temp);
//		std::cout << "환자가 협진을 받으러 출발" << std::endl;
PI_list.erase(PI_list.begin());
GLOBAL_VARIABLE->DecreasePL(id);
}
}
else
{
if (GLOBAL_VARIABLE->GetHHCHESTNum(id) > 0 && GLOBAL_VARIABLE->GetHHDoctorNum(id) > 0 &&
GLOBAL_VARIABLE->GetHHNurseNum(id) > 0)
{
GLOBAL_VARIABLE->DecreaseHHCHESTNum(id);
GLOBAL_VARIABLE->DecreaseHHDoctorNum(id);
GLOBAL_VARIABLE->DecreaseHHNurseNum(id);

_msg.SetPortValue(to_diagonosis.c_str(), temp);
//		std::cout << "환자가 협진을 받으러 출발" << std::endl;
PI_list.erase(PI_list.begin());
GLOBAL_VARIABLE->DecreasePL(id);
}
}
}
else if (temp->data.injury_part == NERVE)
{
if (GLOBAL_VARIABLE->GetHHNERVENum(id) > 0 && GLOBAL_VARIABLE->GetHHNurseNum(id) > 1
&& GLOBAL_VARIABLE->GetHHSurgeryNum(id) > 0)
{
GLOBAL_VARIABLE->DecreaseHHNERVENum(id);
GLOBAL_VARIABLE->DecreaseHHNurseNum(id);
GLOBAL_VARIABLE->DecreaseHHNurseNum(id);

for (int i = 0; i < surgery_room; i++)
{
if (available_surgery[i] == false)
{
temp->set_hh_room(i);
_msg.SetPortValue(to_surgery.c_str(), temp);
/ *std::cout << "수술실 " << i+1 << "이 수술중" << std::endl;* /
PI_list.erase(PI_list.begin());
GLOBAL_VARIABLE->DecreasePL(id);
available_surgery[i] = true;
GLOBAL_VARIABLE->DecreaseHHSurgeryNum(id);
break;
}
}
}
}
else if (temp->data.injury_part == SPINE)
{
if (GLOBAL_VARIABLE->GetHHSPINENum(id) > 0 && GLOBAL_VARIABLE->GetHHNurseNum(id) > 1
&& GLOBAL_VARIABLE->GetHHSurgeryNum(id) > 0)
{
GLOBAL_VARIABLE->DecreaseHHSPINENum(id);
GLOBAL_VARIABLE->DecreaseHHNurseNum(id);
GLOBAL_VARIABLE->DecreaseHHNurseNum(id);

for (int i = 0; i < surgery_room; i++)
{
if (available_surgery[i] == false)
{
temp->set_hh_room(i);
_msg.SetPortValue(to_surgery.c_str(), temp);
/ *std::cout << "수술실 " << i+1 << "이 수술중" << std::endl;* /
PI_list.erase(PI_list.begin());
GLOBAL_VARIABLE->DecreasePL(id);
available_surgery[i] = true;
GLOBAL_VARIABLE->DecreaseHHSurgeryNum(id);
break;
}
}
}
}
else if (temp->data.injury_part == FRACTURE)
{
if (GLOBAL_VARIABLE->GetHHFRACTURENum(id) > 0 && GLOBAL_VARIABLE->GetHHNurseNum(id) > 1
&& GLOBAL_VARIABLE->GetHHSurgeryNum(id) > 0)
{
GLOBAL_VARIABLE->DecreaseHHFRACTURENum(id);
GLOBAL_VARIABLE->DecreaseHHNurseNum(id);
GLOBAL_VARIABLE->DecreaseHHNurseNum(id);

for (int i = 0; i < surgery_room; i++)
{
if (available_surgery[i] == false)
{
temp->set_hh_room(i);
_msg.SetPortValue(to_surgery.c_str(), temp);
/ *std::cout << "수술실" << i+1 << "이 수술중" << std::endl;* /
PI_list.erase(PI_list.begin());
GLOBAL_VARIABLE->DecreasePL(id);
available_surgery[i] = true;
GLOBAL_VARIABLE->DecreaseHHSurgeryNum(id);
break;
}
}
}
}
else if (temp->data.injury_part == BURN)
{
if (GLOBAL_VARIABLE->GetHHBURNNum(id) > 0 && GLOBAL_VARIABLE->GetHHNurseNum(id) > 1
&& GLOBAL_VARIABLE->GetHHSurgeryNum(id) > 0)
{
GLOBAL_VARIABLE->DecreaseHHBURNNum(id);
GLOBAL_VARIABLE->DecreaseHHNurseNum(id);
GLOBAL_VARIABLE->DecreaseHHNurseNum(id);

for (int i = 0; i < surgery_room; i++)
{
if (available_surgery[i] == false)
{
temp->set_hh_room(i);
_msg.SetPortValue(to_surgery.c_str(), temp);
/ *std::cout << "수술실" << i+1 << "이 수술중" << std::endl;* /
PI_list.erase(PI_list.begin());
GLOBAL_VARIABLE->DecreasePL(id);
available_surgery[i] = true;
GLOBAL_VARIABLE->DecreaseHHSurgeryNum(id);
break;
}
}
}
}
else if (temp->data.injury_part == CHEST)
{
if (GLOBAL_VARIABLE->GetHHCHESTNum(id) > 0 && GLOBAL_VARIABLE->GetHHNurseNum(id) > 1
&& GLOBAL_VARIABLE->GetHHSurgeryNum(id) > 0)
{
GLOBAL_VARIABLE->DecreaseHHCHESTNum(id);
GLOBAL_VARIABLE->DecreaseHHNurseNum(id);
GLOBAL_VARIABLE->DecreaseHHNurseNum(id);

for (int i = 0; i < surgery_room; i++)
{
if (available_surgery[i] == false)
{
temp->set_hh_room(i);
_msg.SetPortValue(to_surgery.c_str(), temp);
/ *std::cout << "수술실" << i+1 << "이 수술중" << std::endl;* /
PI_list.erase(PI_list.begin());
GLOBAL_VARIABLE->DecreasePL(id);
available_surgery[i] = true;
GLOBAL_VARIABLE->DecreaseHHSurgeryNum(id);
break;
}
}
}
}
else
{
std::cout << "빈 수술실이 없거나 간호사, 전문의의 수가 부족합니다" << std::endl;
}*/
