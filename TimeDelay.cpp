#include "TimeDelay.h"
#include "GlobalVar.h"

std::string CTimeDelay::outA_outcoming = "out delay";
std::string CTimeDelay::inA_incoming = "in delay";


CTimeDelay::CTimeDelay(TimeDelay_init _timedelay)
	:m_TD(_timedelay)
{
	SetName("Time Delay");

	AddInPorts(1, inA_incoming.c_str());
	AddOutPorts(1, outA_outcoming.c_str());
}


CTimeDelay::~CTimeDelay()
{
}

bool CTimeDelay::ExtTransFn(const CDEVSimMessage &msg)
{
	CInfo* temp = (CInfo *)msg.GetArg(0);

	
	if (temp->data.pPosition == AG_S && temp->data.small_h == SH1 && temp->data.huge_h == HH1)
		temp->data.delayTime = m_TD.DisasterAndSmallH1 + m_TD.DisasterAndHugeH1;
	else if (temp->data.pPosition == AG_S && temp->data.small_h == SH1 && temp->data.huge_h == HH2)
		temp->data.delayTime = m_TD.DisasterAndSmallH1 + m_TD.DisasterAndHugeH2;
	else if (temp->data.pPosition == AG_S && temp->data.small_h == SH1 && temp->data.huge_h == HH3)
		temp->data.delayTime = m_TD.DisasterAndSmallH1 + m_TD.DisasterAndHugeH3;


	else if (temp->data.pPosition == AG_S && temp->data.small_h == SH2 && temp->data.huge_h == HH1)
		temp->data.delayTime = m_TD.DisasterAndSmallH2 + m_TD.DisasterAndHugeH1;
	else if (temp->data.pPosition == AG_S && temp->data.small_h == SH2 && temp->data.huge_h == HH2)
		temp->data.delayTime = m_TD.DisasterAndSmallH2 + m_TD.DisasterAndHugeH2;
	else if (temp->data.pPosition == AG_S && temp->data.small_h == SH2 && temp->data.huge_h == HH3)
		temp->data.delayTime = m_TD.DisasterAndSmallH2 + m_TD.DisasterAndHugeH3;


	else if (temp->data.pPosition == AG_S && temp->data.small_h == SH3 && temp->data.huge_h == HH1)
		temp->data.delayTime = m_TD.DisasterAndSmallH3 + m_TD.DisasterAndHugeH1;
	else if (temp->data.pPosition == AG_S && temp->data.small_h == SH3 && temp->data.huge_h == HH2)
		temp->data.delayTime = m_TD.DisasterAndSmallH3 + m_TD.DisasterAndHugeH2;
	else if (temp->data.pPosition == AG_S && temp->data.small_h == SH3 && temp->data.huge_h == HH3)
		temp->data.delayTime = m_TD.DisasterAndSmallH3 + m_TD.DisasterAndHugeH3;



	else if (temp->data.pPosition == AG_S && temp->data.small_h == SH4 && temp->data.huge_h == HH1)
		temp->data.delayTime = m_TD.DisasterAndSmallH4 + m_TD.DisasterAndHugeH1;
	else if (temp->data.pPosition == AG_S && temp->data.small_h == SH4 && temp->data.huge_h == HH2)
		temp->data.delayTime = m_TD.DisasterAndSmallH4 + m_TD.DisasterAndHugeH2;
	else if (temp->data.pPosition == AG_S && temp->data.small_h == SH4 && temp->data.huge_h == HH3)
		temp->data.delayTime = m_TD.DisasterAndSmallH4 + m_TD.DisasterAndHugeH3;

	else if (temp->data.pPosition == AG_S && temp->data.small_h == SH5 && temp->data.huge_h == HH1)
		temp->data.delayTime = m_TD.DisasterAndSmallH5 + m_TD.DisasterAndHugeH1;
	else if (temp->data.pPosition == AG_S && temp->data.small_h == SH5 && temp->data.huge_h == HH2)
		temp->data.delayTime = m_TD.DisasterAndSmallH5 + m_TD.DisasterAndHugeH2;
	else if (temp->data.pPosition == AG_S && temp->data.small_h == SH5 && temp->data.huge_h == HH3)
		temp->data.delayTime = m_TD.DisasterAndSmallH5 + m_TD.DisasterAndHugeH3;


	else if (temp->data.pPosition == AG_H && temp->data.huge_h == HH1 && temp->data.small_h == NOT && temp->data.severity == 5)
		temp->data.delayTime = m_TD.DisasterAndHugeH1 + 10;
	else if (temp->data.pPosition == AG_H && temp->data.huge_h == HH2 && temp->data.small_h == NOT && temp->data.severity == 5)
		temp->data.delayTime = m_TD.DisasterAndHugeH2 + 10;
	else if (temp->data.pPosition == AG_H && temp->data.huge_h == HH3 && temp->data.small_h == NOT && temp->data.severity == 5)
		temp->data.delayTime = m_TD.DisasterAndHugeH3 + 10;


	else if (temp->data.pPosition == AG_H && temp->data.huge_h == HH1 && temp->data.small_h == NOT)
		temp->data.delayTime = m_TD.DisasterAndHugeH1 * 2;
	else if (temp->data.pPosition == AG_H && temp->data.huge_h == HH2 && temp->data.small_h == NOT)
		temp->data.delayTime = m_TD.DisasterAndHugeH2 * 2;
	else if (temp->data.pPosition == AG_H && temp->data.huge_h == HH3 && temp->data.small_h == NOT)
		temp->data.delayTime = m_TD.DisasterAndHugeH3 * 2;


	else if (temp->data.pPosition == SH && temp->data.small_h == SH1 && temp->data.huge_h == HH1)
		temp->data.delayTime = m_TD.SmallH1AndHugeH1;
	else if (temp->data.pPosition == SH && temp->data.small_h == SH1 && temp->data.huge_h == HH2)
		temp->data.delayTime = m_TD.SmallH1AndHugeH2;
	else if (temp->data.pPosition == SH && temp->data.small_h == SH1 && temp->data.huge_h == HH3)
		temp->data.delayTime = m_TD.SmallH1AndHugeH3;

	else if (temp->data.pPosition == SH && temp->data.small_h == SH2 && temp->data.huge_h == HH1)
		temp->data.delayTime = m_TD.SmallH2AndHugeH1;
	else if (temp->data.pPosition == SH && temp->data.small_h == SH2 && temp->data.huge_h == HH2)
		temp->data.delayTime = m_TD.SmallH2AndHugeH2;
	else if (temp->data.pPosition == SH && temp->data.small_h == SH2 && temp->data.huge_h == HH3)
		temp->data.delayTime = m_TD.SmallH2AndHugeH3;

	else if (temp->data.pPosition == SH && temp->data.small_h == SH3 && temp->data.huge_h == HH1)
		temp->data.delayTime = m_TD.SmallH3AndHugeH1;
	else if (temp->data.pPosition == SH && temp->data.small_h == SH3 && temp->data.huge_h == HH2)
		temp->data.delayTime = m_TD.SmallH3AndHugeH2;
	else if (temp->data.pPosition == SH && temp->data.small_h == SH3 && temp->data.huge_h == HH3)
		temp->data.delayTime = m_TD.SmallH3AndHugeH3;

	else if (temp->data.pPosition == SH && temp->data.small_h == SH4 && temp->data.huge_h == HH1)
		temp->data.delayTime = m_TD.SmallH4AndHugeH1;
	else if (temp->data.pPosition == SH && temp->data.small_h == SH4 && temp->data.huge_h == HH2)
		temp->data.delayTime = m_TD.SmallH4AndHugeH2;
	else if (temp->data.pPosition == SH && temp->data.small_h == SH4 && temp->data.huge_h == HH3)
		temp->data.delayTime = m_TD.SmallH4AndHugeH3;

	else if (temp->data.pPosition == SH && temp->data.small_h == SH5 && temp->data.huge_h == HH1)
		temp->data.delayTime = m_TD.SmallH5AndHugeH1;
	else if (temp->data.pPosition == SH && temp->data.small_h == SH5 && temp->data.huge_h == HH2)
		temp->data.delayTime = m_TD.SmallH5AndHugeH2;
	else if (temp->data.pPosition == SH && temp->data.small_h == SH5 && temp->data.huge_h == HH3)
		temp->data.delayTime = m_TD.SmallH5AndHugeH3;

	else if (temp->data.pPosition == HH && temp->data.huge_h == HH1)
		temp->data.delayTime = m_TD.DisasterAndHugeH1;
	else if (temp->data.pPosition == HH && temp->data.huge_h == HH2)
		temp->data.delayTime = m_TD.DisasterAndHugeH2;
	else if (temp->data.pPosition == HH && temp->data.huge_h == HH3)
		temp->data.delayTime = m_TD.DisasterAndHugeH3;
	

	if (DEVSINTERFACE_PTR->GetCurrentSimulationTime().GetValue() > 30 && DEVSINTERFACE_PTR->GetCurrentSimulationTime().GetValue() <= 180)
	{
		temp->data.delayTime = temp->data.delayTime + temp->data.delayTime*0.15;
	}
	else if (DEVSINTERFACE_PTR->GetCurrentSimulationTime().GetValue() > 180 && DEVSINTERFACE_PTR->GetCurrentSimulationTime().GetValue() <= 360)
	{
		temp->data.delayTime = temp->data.delayTime + temp->data.delayTime*0.3;
	}
	else if (DEVSINTERFACE_PTR->GetCurrentSimulationTime().GetValue() > 360 && DEVSINTERFACE_PTR->GetCurrentSimulationTime().GetValue() <= 720)
	{
		temp->data.delayTime = temp->data.delayTime + temp->data.delayTime*0.15;
	}

/*
	if (temp->data.pPosition == AG_H)
	{
		COUT << "\n ---------- 출발" << ENDL;
		COUT << "| 재난지역에서 HH로 " << ENDL;
		COUT << "| 환자 ID : " << temp->data.id << ENDL;
		COUT << "| 환자 delaytime : " << temp->data.delayTime << ENDL;
		COUT << " ----------" << ENDL;
	}
	else if (temp->data.pPosition == AG_S)
	{
		COUT << "\n ---------- 출발" << ENDL;
		COUT << "| 재난지역에서 SH로 " << ENDL;
		COUT << "| 환자 ID : " << temp->data.id << ENDL;
		COUT << "| 환자 delaytime : " << temp->data.delayTime << ENDL;
		COUT << " ----------" << ENDL;
	}
	else if (temp->data.pPosition == SH)
	{
		COUT << "\n ---------- 출발" << ENDL;
		COUT << "| SH 에서 HH로 " << ENDL;
		COUT << "| 환자 ID : " << temp->data.id << ENDL;
		COUT << "| 환자 delaytime : " << temp->data.delayTime << ENDL;
		COUT << " ----------" << ENDL;
	}*/

	delayVector.push_back(temp->data);

	if (temp->data.pPosition == AG_S && temp->data.small_h == SH4)
	{
		std::cout << " *--------------------- ";
		std::cout << "HH: " << temp->data.huge_h << ", SH:" << temp->data.small_h << std::endl;
		std::cout << "\n" << temp->data.id << " 환자가 얻는 시간 : " << temp->data.delayTime << std::endl;
		std::cout << " | 환자가 delaytime에 도착 시간 : " << DEVSINTERFACE_PTR->GetCurrentSimulationTime().GetValue() << std::endl;
		std::cout << " *--------------------- ";

	}

	this->Continue();
	return true;
}

bool CTimeDelay::IntTransFn()
{
	return true;
}

bool CTimeDelay::OutputFn(CDEVSimMessage &msg)
{
	
	for (std::vector<sPatient_info>::iterator it = delayVector.begin(); it != delayVector.end();)
	{
		it->delayTime--;
		if (it->delayTime <= 0)
		{
			int _id = (*it).id;
			msg.SetPortValue(outA_outcoming.c_str(), new CInfo(*it));
			if (it->small_h == SH4)
			{
				std::cout << " *--------------------- " << std::endl;
				std::cout << "HH: " << it->huge_h << ", SH:" << it->small_h << std::endl;
				std::cout << "환자:" << _id << std::endl;
				std::cout << "설마 나 호출되니?" << DEVSINTERFACE_PTR->GetCurrentSimulationTime().GetValue() << std::endl;
				std::cout << " *--------------------- ";
			}
			it = delayVector.erase(it);
		}
		else
			++it;
	}



	return true;
}

TimeType CTimeDelay::TimeAdvanceFn()
{
	return 1;
}