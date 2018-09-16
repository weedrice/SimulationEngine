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

	static std::string from_SH; //�߼����������� �޴� ȯ��
	static std::string from_AG; //�糭�������� �ٷ� �޴� ȯ��
	static std::string to_coupled; //ȯ�ںз��� ������
	static std::string to_severity;
	static std::string to_AG;
	CInitManager _init;
	
	std::vector<sPatient_info> pVector;

	void set_P_state();

private:
	sPatient_info m_PI;
	int _id;
};

