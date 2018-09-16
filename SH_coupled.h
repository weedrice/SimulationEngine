#pragma once
#include "DEVSim.h"
#include "Info.h"

class SH_coupled: public CCoupled
{
public:
	SH_coupled();
	~SH_coupled();
	static std::string outC_SH_to_Receiver;
	static std::string outC_SH_to_HH;
	static std::string inC_from_AG_coupled;
	bool** doctorTable;
};

