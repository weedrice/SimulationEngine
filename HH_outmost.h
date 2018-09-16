#pragma once
#include "DEVSim.h"
#include "InitManager.h"
#include "Info.h"
#include "HH_Coupled.h"
#include <vector>

class HH_outmost : public CCoupled
{
public:
	HH_outmost();
	~HH_outmost();

public:
	static std::string to_AG;
	static std::string from_SH;
	static std::string from_AG;
	static std::string to_CC;
};

