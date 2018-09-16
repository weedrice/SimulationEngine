#pragma once
#include "DEVSim.h"
#define NERVE 1
#define CHEST 2
#define SPINE 3
#define BURN 4
#define FRACTURE 5

enum Pstate { DISASTER, GENERAL };
enum PatientPosition { AG_S, AG_H, SH, HH };
enum SmallTarget {SH1, SH2,	SH3, SH4, SH5, NOT };
enum HugeTarget {HH1, HH2, HH3};

typedef struct {
	double survivalRate;
	int id;
	int severity;
	int injury_part;
	double consumeTime;
	double rescueTime;
	double entireTime;

	SmallTarget small_h;
	HugeTarget huge_h;
	PatientPosition pPosition;
	int delayTime;
	int hospitalTime; // 병원에서 소비하게 될 시간
	int sRate;
	Pstate _Pstate;
	bool X_ray;
	bool CT;
	bool Clinic;
	int LastPatient;
	int generalTime;
	bool BypassSH;
}sPatient_info;


typedef struct {
	int HugeH;
	int id;
	double init_time;
	int min_time;  //종료조건을 위하여
	int gap_time;
	int next_time;//종료조건
	TimeType kill_time;
	int severity1_min;
	int severity1_max;
	int severity2_min;
	int severity2_max;
	int severity3_min;
	int severity3_max;
	int severity4_min;
	int severity4_max;
	int severity5_min;
	int severity5_max;
	int severity6_min;
	int severity6_max;

	int injury_part;
	int injury_part_nerveMin;
	int injury_part_nerveMax;
	int injury_part_chestMin;
	int injury_part_chestMax;
	int injury_part_spineMin;
	int injury_part_spineMax;
	int injury_part_burnMin;
	int injury_part_burnMax;
	int injury_part_fractureMin;
	int injury_part_fractureMax;
	int general_disaster;
}PG_init;


typedef struct 
{
	int FirehouseAndHugeH1;
	int FirehouseAndHugeH2; 
	int FirehouseAndHugeH3;
	int DisasterAndHugeH1;
	int DisasterAndHugeH2;
	int DisasterAndHugeH3;
	int DisasterAndSmallH1;
	int DisasterAndSmallH2;
	int DisasterAndSmallH3;
	int DisasterAndSmallH4;
	int DisasterAndSmallH5;
	int SmallH1AndHugeH1;
	int SmallH2AndHugeH1;
	int SmallH3AndHugeH1;
	int SmallH4AndHugeH1;
	int SmallH5AndHugeH1;
	int SmallH1AndHugeH2;
	int SmallH2AndHugeH2;
	int SmallH3AndHugeH2;
	int SmallH4AndHugeH2;
	int SmallH5AndHugeH2;
	int SmallH1AndHugeH3;
	int SmallH2AndHugeH3;
	int SmallH3AndHugeH3;
	int SmallH4AndHugeH3;
	int SmallH5AndHugeH3;

}TimeDelay_init;


typedef struct {
	int surgery_room;
	int num_nurse;
	int num_doctor;
	int num_burn;
	int num_nerve;
	int num_spine;
	int num_fracture;
	int num_chest;
	int x_ray_room;
	int clinic_room;
	int ct_room;
}HH_init; // 1차진료 변수


typedef struct 
{
	int id;
	int doctorId;
	int minTime; 
	int gapTime;
	int minTimeId;
	int gapTimeId;
	

}SH_init;

/*
typedef struct 
{
	int mintime1;
	int mintime2;
	int mintime3;
	int mintime4;
	int mintime5;
	int gaptime1;
	int gaptime2;
	int gaptime3;
	int gaptime4;
	int gaptime5;
}Part_init;*/


class SHInfo : public SMSL::CObject
{
public:
	SHInfo(SH_init _data) : data(_data) {}
	~SHInfo(){}

public:
	SH_init data;
};


class CInfo :public SMSL::CObject
{
public:
	CInfo(sPatient_info _data) : data(_data){}
	~CInfo(){}

public:
	void set_sh_doctor(int _num)
	{
		sh_doctor_num = _num;
	}
	int get_sh_doctor()
	{
		return sh_doctor_num;
	}
	void set_hh_room(int _num)
	{
		hh_room = _num;
	}
	int get_hh_room()
	{
		return hh_room;
	}

public:
	sPatient_info data;
	int sh_doctor_num;
	int hh_num;
	int hh_room;
};