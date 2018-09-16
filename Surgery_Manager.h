#pragma once
#include "DEVSim.h"
#include "Info.h"
#include <vector>
#include <stdlib.h>

class Surgery_Manager : public CAtomic
{
public:
	Surgery_Manager();
	Surgery_Manager(int _id);
	~Surgery_Manager();

public:
	virtual bool ExtTransFn(const CDEVSimMessage & _msg);
	virtual bool IntTransFn();
	virtual bool OutputFn(CDEVSimMessage &_msg);
	virtual TimeType TimeAdvanceFn();

	static std::string from_coupled;
	static std::string to_surgery;
	static std::string to_diagonosis;
	static std::string from_surgery;
	static std::string from_diagonosis;

	enum mState	{ IDLE, SEND };
	mState _mState;

	int id;
	sPatient_info m_PI;
	int count_severity[5][5];
	int surgery_room;
	bool* available_surgery;
	std::list<sPatient_info> pNERVE;
	std::list<sPatient_info> pCHEST;
	std::list<sPatient_info> pSPINE;
	std::list<sPatient_info> pBURN;
	std::list<sPatient_info> pFRACTURE;
	std::list<sPatient_info> pDiagnosis;

	std::vector<sPatient_info> Disaster;
	
};

