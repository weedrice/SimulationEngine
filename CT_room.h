#pragma once
#include "DEVSim.h"
#include "Info.h"

class CT_room : public CAtomic
{
public:
	CT_room();
	CT_room(int _id);
	~CT_room();

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

