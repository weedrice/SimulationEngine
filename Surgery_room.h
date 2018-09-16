#pragma once
#include "DEVSim.h"
#include "Info.h"
#include "InitManager.h"
#include <vector>

class Surgery_room : public CAtomic
{
public:
	Surgery_room();
	Surgery_room(int _id);
	~Surgery_room();

public:
	virtual bool ExtTransFn(const CDEVSimMessage &msg);
	virtual bool IntTransFn();
	virtual bool OutputFn(CDEVSimMessage &msg);
	virtual TimeType TimeAdvanceFn();
	enum mState { IDLE, CURE };
	mState _mState;
	sPatient_info m_PI;

	static std::string from_surgery_manager;
	static std::string to_surgery_manager;
	static std::string to_CC;


public:
	int cal_surgery_time(sPatient_info _data);

public:
	int starttime;
	int surgery_time;
	int id;
	/*Part_init time[5]*/
};

