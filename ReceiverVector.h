#pragma once
#include<DEVSim.h>
#include <string>
#include <vector>
#include "Info.h"
class ReceiverVector:public CAtomic
{public:
	ReceiverVector(int _id, bool* doctor_table,int doctorNum);
	~ReceiverVector();

public:
				 
	virtual bool ExtTransFn(const CDEVSimMessage & _msg);
	virtual bool IntTransFn();
	virtual bool OutputFn(CDEVSimMessage &_msg);
	virtual TimeType TimeAdvanceFn();


public:
	enum mState{ IDLE, SEND };
	mState _mState;
	
	static std::string in_vector_to_doctor;
	static std::string out_vector_to_doctor;
	static std::string from_doctor_to_vector;
	std::vector<sPatient_info> pVector;
	sPatient_info arrived_patient;
	int doctorNum;
	bool* doctor_table;
	int id;
	int totalDocNum;
	
};

