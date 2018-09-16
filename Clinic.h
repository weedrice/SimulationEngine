#pragma once
#include "DEVSim.h"
#include "Info.h"

class Clinic : public CAtomic
{
public:
	Clinic();
	Clinic(int _id);
	~Clinic();

public:
	virtual bool ExtTransFn(const CDEVSimMessage &msg);
	virtual bool IntTransFn();
	virtual bool OutputFn(CDEVSimMessage &msg);
	virtual TimeType TimeAdvanceFn();
	enum mState { IDLE, CURE };
	mState _mState;
	sPatient_info m_PI;

	static std::string from_Manager;
	static std::string to_Manager;

public:
	int id;
};

