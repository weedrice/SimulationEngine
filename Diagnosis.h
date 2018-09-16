#pragma once
#include "DEVSim.h"
#include "Info.h"

class Diagnosis : public CAtomic
{
public:
	Diagnosis();
	Diagnosis(int _id);
	~Diagnosis();

public:
	virtual bool ExtTransFn(const CDEVSimMessage &msg);
	virtual bool IntTransFn();
	virtual bool OutputFn(CDEVSimMessage &msg);
	virtual TimeType TimeAdvanceFn();

public:
	enum mState { IDLE };
	mState _mState;
	sPatient_info m_PI;
	int id;


	static std::string from_surgery_manager;
	static std::string to_surgery_manager;
	std::vector<sPatient_info> patient_list;

};

