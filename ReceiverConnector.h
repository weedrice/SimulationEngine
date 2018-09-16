#pragma once
#include "DEVSim.h"
#include "Info.h"


class ReceiverConnector : public CAtomic
{
public:
	ReceiverConnector();
	~ReceiverConnector();

public:
	virtual bool ExtTransFn(CDEVSimMessage & _msg);
	virtual bool IntTransFn();
	virtual bool OutputFn(CDEVSimMessage &_msg);
	virtual TimeType TimeAdvanceFn();
	
	enum mState{ IDLE, SEND };
	mState _mState;

	static std::string in_connect_to_doctor;
	static std::string from_vector;

	sPatient_info arrived_patient;


};


