#pragma once
#include "DEVSim.h"
#include "Info.h"
#include <vector>

class CPatient_Generator : public CAtomic
{
public:
	CPatient_Generator(PG_init);
	~CPatient_Generator();

public:
	void calSeverity(PG_init& _temp, std::vector<int>& severityTable, std::vector<int>& injuryPartTable);

	virtual bool ExtTransFn(const CDEVSimMessage &msg);
	virtual bool IntTransFn();
	virtual bool OutputFn(CDEVSimMessage &msg);
	virtual TimeType TimeAdvanceFn();


public:
	enum mState { INIT, GENERATE, KILL };
	mState _mState;

	static std::string outA_PG_to_AG;
	static std::string outA_PG_to_HH;
	static std::string outA_PG_to_FH;
	static std::string inA_CC_to_PG;

	int GeneralLoof;

	int PGpatient;

	int count;


private:
	PG_init m_PGi;
	std::vector<int> severityTable;
	std::vector<int> injuryPartTable;
};

