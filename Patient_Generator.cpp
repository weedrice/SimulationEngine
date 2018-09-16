#include "Patient_Generator.h"
#include "Info.h"
#include <vector>
#include "GlobalVar.h"
#include "Firehouse.h"

std::string CPatient_Generator::outA_PG_to_AG = "PG to AG";
std::string CPatient_Generator::outA_PG_to_HH = "PG_to_HH(G)";
std::string CPatient_Generator::outA_PG_to_FH = "PG_to_FH";
std::string CPatient_Generator::inA_CC_to_PG = "CC to PG";


CPatient_Generator::CPatient_Generator(PG_init _pg)
	:m_PGi(_pg)
{
	char buf[100];
	sprintf(buf, "PG_%d", m_PGi.id);

	SetName(buf);

	AddOutPorts(3, outA_PG_to_AG.c_str(), outA_PG_to_HH.c_str(), outA_PG_to_FH.c_str());

	_mState = INIT;

	calSeverity(m_PGi, severityTable, injuryPartTable);

	count = 0;
	
	GeneralLoof = 0;
}


CPatient_Generator::~CPatient_Generator()
{
}

bool CPatient_Generator::ExtTransFn(const CDEVSimMessage &msg)
{
	return true;
}

bool CPatient_Generator::IntTransFn()
{
	if (_mState == INIT)
		_mState = GENERATE;
	else if (_mState == GENERATE && DEVSINTERFACE_PTR->GetCurrentSimulationTime().GetValue() + m_PGi.min_time > m_PGi.next_time) // 생성상태이면서 현재시간이 넥스트 타임을 넘었음
		_mState = KILL;
	else if (_mState == GENERATE)
		_mState = GENERATE;
	else if (_mState == KILL && DEVSINTERFACE_PTR->GetCurrentSimulationTime().GetValue() > m_PGi.kill_time*(GeneralLoof+1))
	{
		_mState = GENERATE;
		GeneralLoof++;
	}
	return true;
}

bool CPatient_Generator::OutputFn(CDEVSimMessage &msg)
{

	if (_mState == GENERATE)
	{
		sPatient_info temp_info;
		

		if (m_PGi.general_disaster == 0)
		{
			temp_info.generalTime = -1;

			temp_info.id = GLOBAL_VARIABLE->IncreasePatientId_D();
			temp_info._Pstate = DISASTER;
			temp_info.injury_part = m_PGi.injury_part;
			//여기에 모든걸 넣어준다.

			/*if (!GLOBAL_VARIABLE->isEmpty())
			{
				
				// All VectorPG are occupied

			}
			else
			{


			}*/

			/*int count_for_SH = 0;
			int min_SH = GLOBAL_VARIABLE->GetDoctorNUm(0);
			int max_HH = GLOBAL_VARIABLE->GetHHSurgeryNum_for_PG(0);

			int max_HH_N = 0;

			for (int i = 0; i < 5; i++)
			{
				if (GLOBAL_VARIABLE->GetDoctorNUm(i) == 0)
				{
					count_for_SH++;
				}

			}

			int count_for_HH = 0;
			for (int i = 0; i < 3; i++)
			{
				if (GLOBAL_VARIABLE->GetHHSurgeryNum(i) == 0) //현재 병원의 가용 의사가 0명인지 확인한다.
					count_for_HH++;

				if (max_HH < GLOBAL_VARIABLE->GetHHSurgeryNum_for_PG(i))
				{
					max_HH_N = i;
				}
			}


			//모두 다 비어있을 때 
			if (count_for_HH == 0 && count_for_SH == 0)
			{

				temp_info.small_h = NOT;
				temp_info.huge_h = HH1;
				GLOBAL_VARIABLE->DecreaseHHSurgeryNum_for_PG(0);
			}
			// 대형 차고 중소 일때      ---여기서 경유시 거리에 따라 가는 곳을 정하는 것과 실시간 정보를 받아 가는 것 중 어느 것이 더 좋은지를 시뮬레이션을 통해 확인한다. 
			else if (count_for_SH == 0 && count_for_HH == 3)
			{
				if (temp_info.injury_part == CHEST)
				{
					temp_info.small_h = SH1;
					temp_info.huge_h = HH2;
					GLOBAL_VARIABLE->DecreaseHHSurgeryNum_for_PG(1);
				}
				else if (temp_info.injury_part == BURN)
				{
					temp_info.small_h = SH3;
					temp_info.huge_h = HH3; //HH2 로 가도 상관없다. 
					GLOBAL_VARIABLE->DecreaseHHSurgeryNum_for_PG(2);
				}
				else if (temp_info.injury_part == NERVE)
				{
					temp_info.small_h = SH4;
					temp_info.huge_h = HH1;
					GLOBAL_VARIABLE->DecreaseHHSurgeryNum_for_PG(0);
				}
				else if (temp_info.injury_part == SPINE || temp_info.injury_part == FRACTURE)
				{
					if (GLOBAL_VARIABLE->GetDoctorNUm(4) != 0)
					{
						temp_info.small_h = SH5;
						temp_info.huge_h = HH1;
						GLOBAL_VARIABLE->DecreaseHHSurgeryNum_for_PG(0);
					}
					else if (GLOBAL_VARIABLE->GetDoctorNUm(1) != 0)
					{
						temp_info.small_h = SH2;
						temp_info.huge_h = HH3;
						GLOBAL_VARIABLE->DecreaseHHSurgeryNum_for_PG(2);
					}
					else
					{
						temp_info.small_h = SH5;
						temp_info.huge_h = HH1;
						GLOBAL_VARIABLE->DecreaseHHSurgeryNum_for_PG(0);
					}
				}
			}

			else 	//대형 비고 중소형 찼을때 
			{
				temp_info.small_h = NOT;

				if (max_HH_N == 0)
				{
					temp_info.huge_h = HH1;
					GLOBAL_VARIABLE->DecreaseHHSurgeryNum_for_PG(0);
				}
				else if (max_HH_N == 1)
				{
					temp_info.huge_h = HH2;
					GLOBAL_VARIABLE->DecreaseHHSurgeryNum_for_PG(1);
				}
				else
				{
					temp_info.huge_h = HH3;
					GLOBAL_VARIABLE->DecreaseHHSurgeryNum_for_PG(2);

				}
			}*/
				
/*

			if (GLOBAL_VARIABLE->GenRand()%20 == 0)
			{
				if (temp_info.injury_part == NERVE)
					temp_info.small_h = SH4;
				else if (temp_info.injury_part == CHEST)
					temp_info.small_h = SH1;
				else if (temp_info.injury_part == BURN)
					temp_info.small_h = SH3;
				else if (temp_info.injury_part == FRACTURE || temp_info.injury_part == SPINE)
				{
					if (GLOBAL_VARIABLE->GenRand() % 100 > 50)
						temp_info.small_h = SH2;
					else
						temp_info.small_h = SH5;
				}
			}
			else*/
				temp_info.small_h = NOT;
			
			if (temp_info.id % 8 == 0 || temp_info.id % 8 == 1||temp_info.id % 8 == 2)
			{
				temp_info.huge_h = HH1;
			}
			else if (temp_info.id % 8 == 3 || temp_info.id % 8 == 4)
			{
				temp_info.huge_h = HH2;
			}
			else 
			{
				temp_info.huge_h = HH3;
			}


		}
		else if (m_PGi.general_disaster == 1)
		{
			temp_info.id = GLOBAL_VARIABLE->IncreasePatientId_G();
			temp_info._Pstate = GENERAL;
			temp_info.small_h = NOT;
			
			temp_info.generalTime = DEVSINTERFACE_PTR->GetCurrentSimulationTime().GetValue();

			int _injuryIndex = GLOBAL_VARIABLE->GenRand() % injuryPartTable.size();

			if (m_PGi.HugeH == 1)
				temp_info.huge_h = HH1;
			else if (m_PGi.HugeH == 2)
				temp_info.huge_h = HH2;
			else if (m_PGi.HugeH == 3)
				temp_info.huge_h = HH3;



			if (injuryPartTable[_injuryIndex] == NERVE)
				temp_info.injury_part = NERVE;
			else if (injuryPartTable[_injuryIndex] == CHEST)
				temp_info.injury_part = CHEST;
			else if (injuryPartTable[_injuryIndex] == BURN)
				temp_info.injury_part = BURN;
			else if (injuryPartTable[_injuryIndex] == FRACTURE)
				temp_info.injury_part = FRACTURE;
			else if (injuryPartTable[_injuryIndex] == SPINE)
				temp_info.injury_part = SPINE;
		}

		int _severityIndex = GLOBAL_VARIABLE->GenRand() % severityTable.size();

		if (severityTable[_severityIndex] == 1)
			temp_info.severity = 1;
		else if (severityTable[_severityIndex] == 2)
			temp_info.severity = 2;
		else if (severityTable[_severityIndex] == 3)
			temp_info.severity = 3;
		else if (severityTable[_severityIndex] == 4)
			temp_info.severity = 4;
		else if (severityTable[_severityIndex] == 5)
			temp_info.severity = 5;
		else if (severityTable[_severityIndex] == 6)
			temp_info.severity = 6;

		temp_info.rescueTime = DEVSINTERFACE_PTR->GetCurrentSimulationTime().GetValue();
		temp_info.consumeTime = 0;
		temp_info.entireTime = 0;
		temp_info.LastPatient = -1;

	


		if (m_PGi.general_disaster == 0)
		{
			msg.SetPortValue(outA_PG_to_AG.c_str(), new CInfo(temp_info));

			GLOBAL_VARIABLE->IncreasePGpatient();


			COUT << " 재난 지역에서 환자 구조한 시간 : " << DEVSINTERFACE_PTR->GetCurrentSimulationTime() << ENDL;
			COUT << " 재난 지역에서 환자 구조 : " << GLOBAL_VARIABLE->GetPGpatientNum() << ENDL;

			if (GLOBAL_VARIABLE->GetAmulanceNum_FH() > 0)
			{
				msg.SetPortValue(outA_PG_to_FH.c_str(), new CInfo(temp_info));
// 				std::cout << "\n   재난 환자 발생, 소방서에 정보 보냄" << std::endl;
// 				std::cout << "   남은 소방차 수 : " << GLOBAL_VARIABLE->GetAmulanceNum_FH() << std::endl;
			}

// 			std::cout << "\n   재난 환자 발생" << std::endl;
// 			std::cout << "   재난 환자 ID : " << temp_info.id << std::endl;

		}
		else if (m_PGi.general_disaster == 1)
		{
			msg.SetPortValue(outA_PG_to_HH.c_str(), new CInfo(temp_info));
// 			std::cout << "\n 일반 내원환자 보냄" << std::endl;
 			//std::cout << " 일반 내원환자 ID : " << temp_info.id << std::endl;
//			std::cout << "내원 환자 발생 시점 : " << DEVSINTERFACE_PTR->GetCurrentSimulationTime().GetValue() << std::endl;
		}


		if (DEVSINTERFACE_PTR->GetCurrentSimulationTime().GetValue() + m_PGi.min_time >= (m_PGi.next_time + m_PGi.kill_time * GeneralLoof)) // 다음 시간까지 시간이 있을때 또 객체가 생성할 수 있는것을 방지하기위해 
		{
			_mState = KILL;
		}
	}
	return true;
}

TimeType CPatient_Generator::TimeAdvanceFn()
{
	if (_mState == INIT)
	{
		if (m_PGi.general_disaster == 1)
			return m_PGi.init_time + m_PGi.kill_time*GeneralLoof;
		else if (m_PGi.general_disaster == 0)
			return m_PGi.init_time;
	}
	else if (_mState == GENERATE)
	{
		int _randValue = GLOBAL_VARIABLE->GenRand();
		//std::cout << "Rand:" << _randValue << std::endl;
		return _randValue % m_PGi.gap_time + m_PGi.min_time;
	}
	else
		return m_PGi.kill_time;
}

void CPatient_Generator::calSeverity(PG_init& _temp, std::vector<int> &severityTable, std::vector<int> &injuryPartTable)
{
	std::vector<int> tempSeverity_vector(6,0);
	std::vector<int> tempInjury_vector(5, 0);


	for (int i = _temp.severity1_min; i != _temp.severity1_max; i++)
	{
		tempSeverity_vector[0] += i;
	}
	for (int i = _temp.severity2_min; i != _temp.severity2_max; i++)
	{
		tempSeverity_vector[1] += i;
	}
	for (int i = _temp.severity3_min; i != _temp.severity3_max; i++)
	{
		tempSeverity_vector[2] += i;
	}
	for (int i = _temp.severity4_min; i != _temp.severity4_max; i++)
	{
		tempSeverity_vector[3] += i;
	}
	for (int i = _temp.severity5_min; i != _temp.severity5_max; i++)
	{
		tempSeverity_vector[4] += i;
	}
	for (int i = _temp.severity6_min; i != _temp.severity6_max; i++)
	{
		tempSeverity_vector[5] += i;
	}
	

	for (int j = 0; j < 6; j++)
	{
		for (int i = 1; i < tempSeverity_vector[j]; i++)
		{
			if (j + 1 == 1)
				severityTable.push_back(1);
			else if (j + 1 == 2)
				severityTable.push_back(2);
			else if (j + 1 == 3)
				severityTable.push_back(3);
			else if (j + 1 == 4)
				severityTable.push_back(4);
			else if (j + 1 == 5)
				severityTable.push_back(5);
			else if (j + 1 == 6)
				severityTable.push_back(6);
		}
	}

	if (_temp.general_disaster == GENERAL)
	{
		for (int i = _temp.injury_part_nerveMin; i != _temp.injury_part_nerveMin; i++)
		{
			tempInjury_vector[0] += i;
		}
		for (int i = _temp.injury_part_chestMin; i != _temp.injury_part_chestMax; i++)
		{
			tempInjury_vector[1] += i;
		}
		for (int i = _temp.injury_part_spineMin; i != _temp.injury_part_spineMax; i++)
		{
			tempInjury_vector[2] += i;
		}
		for (int i = _temp.injury_part_burnMin; i != _temp.injury_part_burnMax; i++)
		{
			tempInjury_vector[3] += i;
		}
		for (int i = _temp.injury_part_fractureMin; i != _temp.injury_part_fractureMax; i++)
		{
			tempInjury_vector[4] += i;
		}


		for (int j = 0; j < 5; j++)
		{
			for (int i = 1; i < tempInjury_vector[j]; i++)
			{
				if (j + 1 == NERVE)
					injuryPartTable.push_back(NERVE);
				else if (j + 1 == CHEST)
					injuryPartTable.push_back(CHEST);
				else if (j + 1 == SPINE)
					injuryPartTable.push_back(SPINE);
				else if (j + 1 == BURN)
					injuryPartTable.push_back(BURN);
				else if (j + 1 == FRACTURE)
					injuryPartTable.push_back(FRACTURE);
			}
		}
	}

}