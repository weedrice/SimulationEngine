#pragma once
#include "DEVSim.h"
#include "Info.h"
#include "GlobalVar.h"
#include <vector>
#include "InitManager.h"

class HH_Desk : public CAtomic
{
public:
	HH_Desk();
	~HH_Desk();

public:
	virtual bool ExtTransFn(const CDEVSimMessage &msg);
	virtual bool IntTransFn();
	virtual bool OutputFn(CDEVSimMessage &msg);
	virtual TimeType TimeAdvanceFn();

public:
	enum mState { IDLE };
	mState _mState;
	sPatient_info m_PI;
	/*HH_D_init init;*/
	CInitManager _init;
	std::vector<sPatient_info> wait_list;

	static std::string from_severity;
	static std::string to_first_check;

	int get_in();
};

