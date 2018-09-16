#pragma once
#include "DEVSim.h"
#include "Info.h"

class HH_Patience_Manage : public CAtomic
{
public:
	HH_Patience_Manage();
	HH_Patience_Manage(int x_ray, int ct, int clinic, int _id);
	~HH_Patience_Manage();

public:
	virtual bool ExtTransFn(const CDEVSimMessage &msg);
	virtual bool IntTransFn();
	virtual bool OutputFn(CDEVSimMessage &msg);
	virtual TimeType TimeAdvanceFn();

	static std::string to_X_ray;
	static std::string to_Clinic;
	static std::string to_CT;
	static std::string to_manage_surgery;
	static std::string from_CT;
	static std::string from_X_ray;
	static std::string from_Clinic;
	static std::string from_receive;

public:
	bool check_patient(sPatient_info Patient);

public:
	enum mState { IDLE, SEND };
	mState _mState;

	/*std::vector<sPatient_info> X_ray_P;
	std::vector<sPatient_info> CT_P;
	std::vector<sPatient_info> Clinic_P;*/
	std::vector<sPatient_info> All_done;
	std::list<sPatient_info> X_ray_P;
	std::list<sPatient_info> CT_P;
	std::list<sPatient_info> Clinic_P;
	sPatient_info m_PI;
	int id;
	int X_ray_room;
	int CT_room;
	int Clinic_room;
	int av_X_ray;
	int av_CT;
	int av_Clinic;
	bool* available_x_ray;
	bool* available_ct;
	bool* available_clinic;
};