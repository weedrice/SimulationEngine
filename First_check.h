#pragma once
#include "DEVSim.h"
#include "Info.h"
#include <vector>

class First_check : public CAtomic
{
public:
	First_check();
	First_check(int _id);
	~First_check();

public:
	virtual bool ExtTransFn(const CDEVSimMessage &msg);
	virtual bool IntTransFn();
	virtual bool OutputFn(CDEVSimMessage &msg);
	virtual TimeType TimeAdvanceFn();

public:
	enum mState {IDLE};
	mState _mState;
	sPatient_info m_PI;
	std::vector<sPatient_info> wait_list;
	std::vector<sPatient_info> waiting;
	int id;

public:
	static std::string from_desk;
	static std::string to_manager;


};

