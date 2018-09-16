#include "Firehouse.h"
#include "GlobalVar.h"

std::string CFirehouse::outA_Firehouse_to_AG = "Firehouse to AG";
std::string CFirehouse::inA_PG_to_Firehouse = "PG to Firehouse";

CFirehouse::CFirehouse(int num, TimeDelay_init _temp)
	:m_TD(_temp), initAmbulanceNum(num)
{

	GLOBAL_VARIABLE->SetAmbulanceNum(0);
	GLOBAL_VARIABLE->SetAmbulanceNum_FH(num);


	SetName("Firehouse");


	AddOutPorts(1, outA_Firehouse_to_AG.c_str());
	AddInPorts(1, inA_PG_to_Firehouse.c_str());

	
}


CFirehouse::~CFirehouse()
{
}

bool CFirehouse::ExtTransFn(const CDEVSimMessage &msg)
{

	COUT << "소방서가 값을 받는 시간 : " << DEVSINTERFACE_PTR->GetCurrentSimulationTime().GetValue() << ENDL;

	if ( initAmbulanceNum > 0 )
	{
		GLOBAL_VARIABLE->DecreaseAmbulanceNum_FH();

		CInfo* temp = (CInfo *)msg.GetArg(0);

		if (temp->data.huge_h == HH1)
			temp->data.delayTime = m_TD.FirehouseAndHugeH1;
		else if (temp->data.huge_h == HH2)
			temp->data.delayTime = m_TD.FirehouseAndHugeH2;
		else if (temp->data.huge_h == HH3)
			temp->data.delayTime = m_TD.FirehouseAndHugeH3;

		delayVector.push_back(temp->data);

		initAmbulanceNum--;

	}

	
	return true;
}

bool CFirehouse::IntTransFn()
{

	return true;
}

bool CFirehouse::OutputFn(CDEVSimMessage &msg)
{
	for (std::vector<sPatient_info>::iterator it = delayVector.begin(); it != delayVector.end();)
	{
		it->delayTime--;
		if (it->delayTime <= 0)
		{

			msg.SetPortValue(outA_Firehouse_to_AG.c_str(), NULL);

			it = delayVector.erase(it);
		}
		else
		{
			++it;
		}
	}
	return true;
}

TimeType CFirehouse::TimeAdvanceFn()
{
	return 1;
}



