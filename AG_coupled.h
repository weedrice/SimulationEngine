#pragma once
#include "DEVSim.h"
#include <queue>
#include "Info.h"


class CAG_coupled: public CCoupled
{
public:
	CAG_coupled();
	~CAG_coupled();

	static std::string inC_HugeH_to_AmbulanceG;
	static std::string inC_PatientG_to_AmbulanceG;
	static std::string outC_AmbulanceG_to_SmallH;
	static std::string inC_Firehouse_to_AmbulanceG;
	static std::string outC_AmbulanceG_to_HugeH;

private:
	std::queue<CInfo>* q;
};