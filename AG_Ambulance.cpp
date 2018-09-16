#include "AG_Ambulance.h"
#include "GlobalVar.h"

std::string CAG_Ambulance::inC_AmbulanceG_to_Ambulance = "AG to A";
std::string CAG_Ambulance::inA_HugeH_to_Ambulance = "HH to A";

CAG_Ambulance::CAG_Ambulance()
{
	SetName("AG_Ambulance");

	AddInPorts(2, inC_AmbulanceG_to_Ambulance.c_str(), inA_HugeH_to_Ambulance.c_str());

	_mState = INIT;

	am = 0;
	fromFH = 0;
	fromHH = 0;
}


CAG_Ambulance::~CAG_Ambulance()
{
}

bool CAG_Ambulance::ExtTransFn(const CDEVSimMessage &msg)
{

	if (msg.GetPort().compare(inC_AmbulanceG_to_Ambulance.c_str()) == 0)
	{
		GLOBAL_VARIABLE->IncreaseAmbulanceNum();
	}
	else if (msg.GetPort().compare(inA_HugeH_to_Ambulance.c_str()) == 0)
	{
		GLOBAL_VARIABLE->IncreaseAmbulanceNum();
	}

	return true;
}

bool CAG_Ambulance::IntTransFn()
{
	return true;
}

bool CAG_Ambulance::OutputFn(CDEVSimMessage &msg)
{
	return true;
}

TimeType CAG_Ambulance::TimeAdvanceFn()
{
	return Infinity;
}


