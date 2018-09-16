#include "HH_outmost.h"
#include "InitManager.h"
#include "DEVSim.h"
#include "Info.h"
#include "HH_Coupled.h"
#include <vector>
#include "GlobalVar.h"


std::string HH_outmost::to_AG = "to_AG";
std::string HH_outmost::to_CC = "to_CC";
std::string HH_outmost::from_AG = "from_AG";
std::string HH_outmost::from_SH = "from_SH";

HH_outmost::HH_outmost()
{
	SetName("HH_outmost");
	CInitManager InitManager;
	AddInPorts(2, from_SH.c_str(), from_AG.c_str());
	AddOutPorts(2, to_AG.c_str(), to_CC.c_str());

	std::vector<CCoupled*> HH_list;
	for (int i = 0; i < 3; i++)
	{
		for (std::vector<HH_init>::iterator it = InitManager.initVectorHH[i].begin(); it != InitManager.initVectorHH[i].end(); it++)
		{
			GLOBAL_VARIABLE->SetHH(*it, i);
			GLOBAL_VARIABLE->SetHH_for_PG(*it, i);
			CCoupled* temp = new HH_Coupled(*it, i);
			AddComponent(1, temp);
			AddCoupling(this, from_AG.c_str(), temp, HH_Coupled::from_AG.c_str());
			AddCoupling(this, from_SH.c_str(), temp, HH_Coupled::from_SH.c_str());
			AddCoupling(temp, HH_Coupled::to_AG.c_str(), this, to_AG.c_str());
			AddCoupling(temp, HH_Coupled::to_CC.c_str(), this, to_CC.c_str());
			HH_list.push_back(temp);
					
		}
	}
	
}


HH_outmost::~HH_outmost()
{
}
