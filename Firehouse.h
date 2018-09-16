#pragma once
#include "DEVSim.h"
#include "TimeDelay.h"
#include "Info.h"



class CFirehouse : public CAtomic
{
public:
	CFirehouse(int i, TimeDelay_init _temp);
	~CFirehouse();

public:
	virtual bool ExtTransFn(const CDEVSimMessage &);
	virtual bool IntTransFn();
	virtual bool OutputFn(CDEVSimMessage &);
	virtual TimeType TimeAdvanceFn();
	int getInitAmbulanceNum(){ return initAmbulanceNum; }


public:
	enum mState { IDLE };
	mState _mState;

	static std::string outA_Firehouse_to_AG;
	static std::string inA_PG_to_Firehouse;

	TimeDelay_init m_TD;
	int initAmbulanceNum;

private:
	std::vector<sPatient_info> delayVector;

};

