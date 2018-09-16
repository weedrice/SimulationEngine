#pragma once
#include "DEVSim.h"
#include "Info.h"

class HH_General_Manage : public CAtomic
{
public:
	HH_General_Manage();
	~HH_General_Manage();

public:
	virtual bool ExtTransFn(const CDEVSimMessage &msg);
	virtual bool IntTransFn();
	virtual bool OutputFn(CDEVSimMessage &msg);
	virtual TimeType TimeAdvanceFn();

	static std::string from_sort;
	static std::string to_X_ray;
	static std::string to_Clinic;
	static std::string to_CT;
	static std::string to_manage_surgery;
	static std::string from_CT;
	static std::string from_X_ray;
	static std::string from_Clinic;
	static std::string to_no_surgery;

public:
	bool check_patient(sPatient_info Patient);

public:
	enum mState { IDLE, SEND };
	mState _mState;

	std::vector<sPatient_info> pVector;
	sPatient_info m_PI;
	int X_ray_room;
	int CT_room;
	int Clinic_room;
};

