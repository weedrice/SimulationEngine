#pragma once
#include "DEVSim.h"
#include "Info.h"
#include "GlobalVar.h"
#include "InitManager.h"
#include "Surgery_room.h"
#include "Diagnosis.h"
#include "HH_Patience_Manage.h"
#include "HH_Patience_Coupled.h"
#include "HH_receive.h"
#include "Surgery_Manager.h"
#include "First_check.h"

class HH_Coupled : public CCoupled
{
public:
	HH_Coupled();
	HH_Coupled(HH_init _init, int _id);
	~HH_Coupled();

public:
	static std::string from_AG;
	static std::string from_SH;
	static std::string to_AG;
	static std::string to_CC;


public:
	HH_init m_HH;
	int id;

};

