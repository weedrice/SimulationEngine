#pragma once
#include "DEVSim.h"
#include <queue>
#include "Info.h"

class CAG_Ambulance : public CAtomic
{
public:
	CAG_Ambulance();
	~CAG_Ambulance();

public:
	virtual bool ExtTransFn(const CDEVSimMessage &msg);
	virtual bool IntTransFn();
	virtual bool OutputFn(CDEVSimMessage &msg);
	virtual TimeType TimeAdvanceFn();

public:
	enum mState { INIT };
	mState _mState;

	//std::queue<CInfo>* m_pQ;
	static std::string inC_AmbulanceG_to_Ambulance;
	static std::string inA_HugeH_to_Ambulance;
	int am;
	int fromFH;
	int fromHH;
};

