#pragma once
#include "DEVSim.h"
#include <vector>
#include "Info.h"

class CCommand_Center : public CAtomic
{
public:
	CCommand_Center();
	~CCommand_Center();

public:
	virtual bool ExtTransFn(const CDEVSimMessage &msg);
	virtual bool IntTransFn();
	virtual bool OutputFn(CDEVSimMessage &msg);
	virtual TimeType TimeAdvanceFn();
	virtual int GetSurvivorRate(int num);
public:
	enum mState { INIT, KILL, INFO };
	mState _mState;

	std::vector<sPatient_info> AllPatientInfo;

	static std::string inA_HH_to_CC;
	static std::string outA_CC_to_PG;

	int lastPatient;
};

