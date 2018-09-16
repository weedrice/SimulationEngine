#pragma once
#include "DEVSim.h"
#include "Info.h"
// �� �������� 5���� ����������

class X_ray : public CAtomic
{
public:
	X_ray();
	X_ray(int _id);
	~X_ray();

public:
	virtual bool ExtTransFn(const CDEVSimMessage &msg);
	virtual bool IntTransFn();
	virtual bool OutputFn(CDEVSimMessage &msg);
	virtual TimeType TimeAdvanceFn();
	enum mState {IDLE, CURE};
	mState _mState;
	sPatient_info m_PI;

	static std::string from_Manager;
	static std::string to_Manager;

public:
	int id;
};

