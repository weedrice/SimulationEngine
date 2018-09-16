#pragma once
#include "DEVSim.h"
#include "Info.h"
#include <vector>
#include "GlobalVar.h"
#include "InitManager.h"

class HH_check_severity : public CAtomic
{
public:
	HH_check_severity();
	HH_check_severity(int _id);
	~HH_check_severity();

public:
	virtual bool ExtTransFn(const CDEVSimMessage &msg);
	virtual bool IntTransFn();
	virtual bool OutputFn(CDEVSimMessage &msg);
	virtual TimeType TimeAdvanceFn();

public:
	enum mState { IDLE };
	int id;
	mState _mState;
	sPatient_info m_PI;
	CInitManager _init;
	/*HH_CS_init init;*/
	std::vector<sPatient_info> wait_list;
	std::vector<sPatient_info> waiting;

	static std::string from_receiver;
	static std::string to_desk;

};

