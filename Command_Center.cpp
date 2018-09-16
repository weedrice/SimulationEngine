#include "Command_Center.h"
#include "Info.h"
#include "math.h"
#include "GlobalVar.h"
std::string CCommand_Center::inA_HH_to_CC = "HH to CC";
std::string CCommand_Center::outA_CC_to_PG = "CC to PG";

CCommand_Center::CCommand_Center()
{
	SetName("Command Center");
	// 나중에 지울 것임

	AddInPorts(1, inA_HH_to_CC.c_str());
	GLOBAL_VARIABLE->SetAfterNum(0);
	_mState = INIT;
	
}


CCommand_Center::~CCommand_Center()
{
}

bool CCommand_Center::ExtTransFn(const CDEVSimMessage &msg)
{
	
	if (_mState == INIT && msg.GetPort().compare(inA_HH_to_CC.c_str())==0)
	{ 

		if (DEVSINTERFACE_PTR->GetCurrentSimulationTime().GetValue() > 720)
		{
			lastPatient = GLOBAL_VARIABLE->GetDisasterPatientLast();
		}

		CInfo * temp_info = (CInfo*)msg.GetArg(0);
		if (temp_info->data._Pstate == DISASTER)
		{
			GLOBAL_VARIABLE->IncreaseAfter();
			/*std::cout << " 커맨드센터에 들어온 재난환자수 : "<<GLOBAL_VARIABLE->GetAfterNum() << std::endl;*/
			temp_info->data.consumeTime = (DEVSINTERFACE_PTR->GetCurrentSimulationTime().GetValue());

			temp_info->data.entireTime = (DEVSINTERFACE_PTR->GetCurrentSimulationTime().GetValue() - temp_info->data.rescueTime);
		}
		if (temp_info->data._Pstate == GENERAL)
		{
			temp_info->data.consumeTime = (DEVSINTERFACE_PTR->GetCurrentSimulationTime().GetValue()) - temp_info->data.generalTime;
		}
		

	



		AllPatientInfo.push_back(temp_info->data);
		/* 	std::cout << "\n Receive Patient \n Patient Id : "<< temp_info->data.id << std::endl;
		 	std::cout << " Patient state : " << (temp_info->data._Pstate == DISASTER ? "DISASTER" : "GENERAL") << std::endl;*/
		// 	std::cout << " Patient Severity : " << temp_info->data.severity << std::endl;
		// 	std::cout << " Patient Injury Part : " << temp_info->data.injury_part << std::endl;
		// 	std::cout << " Patient Huge Target : " << temp_info->data.huge_h << std::endl;
		// 	std::cout << " Patient Small Target : " << temp_info->data.small_h << std::endl;
		/*std::cout << "커맨드 센터에서 값을 저장합니다. 환자가 들어왔습니다." << std::endl;*/

		if ((lastPatient == GLOBAL_VARIABLE->GetAfterNum()) || (DEVSINTERFACE_PTR->GetCurrentSimulationTime().GetValue() > 4320))
		{
			//std::cout << "마지막에 들어온 재난환자 " << GLOBAL_VARIABLE->GetAfterNum() << std::endl;
			//std::cout << "병원에 들어온 환자 수 " << GLOBAL_VARIABLE->GetGetHHNum() << std::endl;

			char buf[1000];
			sprintf(buf, "마지막에 들어온 재난환자 %d", GLOBAL_VARIABLE->GetAfterNum());
			COUT << buf << ENDL;
			sprintf(buf, "병원에 들어온 환자 수 %d", GLOBAL_VARIABLE->GetGetHHNum());
			COUT << buf << ENDL;
			_mState = INFO;
		}
	}

	return true;

}

bool CCommand_Center::IntTransFn()
{
	if (_mState == INIT)
	{
		_mState =INIT;
	}
	else if (_mState == INFO)
	{
		_mState = KILL;
	}
	return true;
}
int CCommand_Center::GetSurvivorRate(int Severity)
{
	if (Severity == 1)
	{
		return (15 + GLOBAL_VARIABLE->GenRand() % 6) / 100;
	}
	else if (Severity == 2)
	{
		return (15 + GLOBAL_VARIABLE->GenRand() % 11) / 100;
	}
	else if (Severity == 3)
	{
		return (10 + GLOBAL_VARIABLE->GenRand() % 11) / 100;
	}
	else if (Severity == 4)
	{
		return (10 + GLOBAL_VARIABLE->GenRand() % 11) / 100;
	}
	else if (Severity == 5)
	{
		return (5 + GLOBAL_VARIABLE->GenRand() % 11) / 100;
	}
}

bool CCommand_Center::OutputFn(CDEVSimMessage &msg)
{
	if (_mState == INFO)
	{
		int AllpatientNum = 0;
		int TotalconsumeTime = 0;
		double TotalSurvivalRate = 0;
		double AllPatientEntireTime = 0;

		for (std::vector<sPatient_info>::iterator itM = AllPatientInfo.begin(); itM != AllPatientInfo.end(); itM++)
		{
			AllpatientNum++;
			//TotalconsumeTime+=itM->환자가 소비한시간
			if (itM->severity == 1)
			{	
				if (itM->small_h == NOT)
				{
					TotalSurvivalRate += 59.2*exp(-0.155*itM->consumeTime / 60);
				}
				else
				{
					TotalSurvivalRate += 59.2*exp(-0.155*itM->consumeTime * GetSurvivorRate(itM->severity) / 60);
				}
			}
			else if (itM->severity == 2)
			{
				if (itM->small_h == NOT)
				{
					TotalSurvivalRate += 82.4*exp(-0.159*itM->consumeTime / 60);
				}
				else
				{
					TotalSurvivalRate += 82.4*exp(-0.159*itM->consumeTime  * GetSurvivorRate(itM->severity) / 60);
				}
				
			}
			else if (itM->severity == 3)
			{
				if (itM->small_h == NOT)
				{
					TotalSurvivalRate += 92.1*exp(-0.161*itM->consumeTime / 60);
				}
				else
				{
					TotalSurvivalRate += 92.1*exp(-0.161*itM->consumeTime * GetSurvivorRate(itM->severity) / 60);
				}
				
			}
			else if (itM->severity == 4)
			{
				if (itM->small_h == NOT)
				{
					TotalSurvivalRate += 95.7*exp(-0.161*itM->consumeTime / 60);
				}
				else
				{
					TotalSurvivalRate += 95.7*exp(-0.161*itM->consumeTime * GetSurvivorRate(itM->severity) / 60);
				}
				
			}
			else if (itM->severity == 5)
			{
				if (itM->small_h == NOT)
				{
					TotalSurvivalRate += 97.1*exp(-0.162*itM->consumeTime / 60);
				}
				else
				{
					TotalSurvivalRate += 97.1*exp(-0.162*itM->consumeTime * GetSurvivorRate(itM->severity) / 60);
				}
				
			}

			if (itM->_Pstate == DISASTER)
			{
				AllPatientEntireTime += itM->entireTime;
			}

			

		}

		std::cout << "총 환자의 수는 " << AllpatientNum << " 명 입니다. " << std::endl;
		
		std::cout << "재난 환자의 수술 종료까지 평균 소요 시간은 : " << AllPatientEntireTime/(double)AllpatientNum << std::endl;

		std::cout << "평균 환자의 생존률은 " << TotalSurvivalRate / (double)AllpatientNum << " 입니다." << std::endl;
		
		std::cout << "시뮬레이션 종료 시간 : " << DEVSINTERFACE_PTR->GetCurrentSimulationTime().GetValue() << std::endl;

		for (int i = 0; i < 3; i++)
		{
			std::cout << "병원 " << i+1 <<"의 총 협진 환자 수 : " << GLOBAL_VARIABLE->GetDiagnosisNum(i) << std::endl;
		}
		
		exit(0);

		//msg.SetPortValue(outA_CC_to_PG.c_str(), NULL);

	}


	return true;
}



TimeType CCommand_Center::TimeAdvanceFn()
{
	if (_mState == INFO)
	{
		return 0;
	}
	else
	{
		return Infinity;
	}
}


