#pragma once
#include "DEVSim.h"
#include "Info.h"
#include <vector>
#include "InitManager.h"

class HH_receive : public CAtomic
{
public:
	HH_receive();
	HH_receive(int id);
	~HH_receive();

public:
	virtual bool ExtTransFn(const CDEVSimMessage &msg);
	virtual bool IntTransFn();
	virtual bool OutputFn(CDEVSimMessage &msg);
	virtual TimeType TimeAdvanceFn();

public:
	enum mState { IDLE, SEND };
	mState _mState;

	static std::string from_SH; //중소형병원에서 받는 환자
	static std::string from_AG; //재난지역에서 바로 받는 환자
	static std::string to_coupled; //환자분류로 보내기
	static std::string to_severity;
	static std::string to_AG;
	CInitManager _init;
	
	std::vector<sPatient_info> pVector;

	void set_P_state();

private:
	sPatient_info m_PI;
	int _id;
};

