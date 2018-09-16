#pragma once
#include "DEVSim.h"
#include <vector>
#include "Info.h"



class CTimeDelay : public CAtomic
{
public:
	CTimeDelay(TimeDelay_init _timedelay);
	~CTimeDelay();

public:
	virtual bool ExtTransFn(const CDEVSimMessage &);
	virtual bool IntTransFn();
	virtual bool OutputFn(CDEVSimMessage &);
	virtual TimeType TimeAdvanceFn();

public:
	enum mState { VECTOR };
	mState _mState;

	static std::string inA_incoming;
	static std::string outA_outcoming;

	TimeDelay_init m_TD;

private:
	std::vector<sPatient_info> delayVector;
	
};

