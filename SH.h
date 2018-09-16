#pragma once
#include "DEVSim.h"
#include "Info.h"

class CSH : public CAtomic
{
public:
	CSH(SH_init);
	~CSH();


public:
	virtual bool ExtTransFn(const CDEVSimMessage &msg);
	virtual bool IntTransFn();
	virtual bool OutputFn(CDEVSimMessage &msg);
	virtual TimeType TimeAdvanceFn();


public:
	enum mState { IDLE, CURE };
	mState _mState;

	static std::string outSH_to_HH;
	static std::string from_Receiver;
	static std::string cureDone;

private :
	SH_init m_SH;
	sPatient_info m_PI;
};