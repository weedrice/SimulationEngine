#pragma once
#include "DEVSim.h"
#include "Info.h"

class CPG_coupled : public CCoupled
{
public:
	CPG_coupled();
	~CPG_coupled();

	static std::string outC_PG_to_AG;
	static std::string outC_PG_to_HH_G;
	static std::string outC_PG_to_FH;

};

