#pragma once
#include "DEVSim.h"
#include "Info.h"

class HH_Patience_Coupled : public CCoupled
{
public:
	HH_Patience_Coupled();
	HH_Patience_Coupled(int _id, int _X_ray, int _ct, int _clinic);
	~HH_Patience_Coupled();

public:
	static std::string from_receive;
	static std::string from_Manager_to_Surgery;

public:
	int X_ray_room;
	int _CT_room;
	int Clinic_room;

};

