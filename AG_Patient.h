#pragma once
#include "DEVSim.h"
#include <queue>
#include "Info.h"
#include <vector>


class CAG_Patient : public CAtomic
{
public:
	CAG_Patient(std::queue<CInfo>* pq);
	~CAG_Patient();

public:
	virtual bool ExtTransFn(const CDEVSimMessage &);
	virtual bool IntTransFn();
	virtual bool OutputFn(CDEVSimMessage &);
	virtual TimeType TimeAdvanceFn();

public:
	enum mState { INIT, QUEUE, ACTIVE, CHECK };
	mState _mState;
	
	sPatient_info temp_PatinetInfo;
	CInfo* temp_info;
	std::queue<CInfo>* m_pQ;

	int startPatient;
	int howmanytimes;

	static std::string inA_AmbulanceG_to_Patient_a;
	static std::string inA_AmbulanceG_to_Patient_p;
	static std::string outA_Patient_to_AmbulanceG;
	static std::string outA_Patient_to_AmbulanceG_direct;
};