#include "InitManager.h"
#include <fstream>


CInitManager::CInitManager()
{
	for (int i = 0; i < 5; i++)
	{
		char name[][40] = { "init_nerve.txt", "init_spine.txt", "init_chest.txt", "init_fracture.txt", "init_burn.txt" };

		std::ifstream _inStream;
		_inStream.open(name[i]);

		char buf[100];
		PG_init temp;


		while (!_inStream.eof())
		{
			_inStream.getline(buf, 100);
			if (parseDPInit(buf, temp))
			{
				initVectorDP.push_back(temp);
			}
		}
	}

	//SH병원 넣기 
	for (int i = 0; i < 5; i++)
	{
		char name[][40] = { "init_sh1.txt", "init_sh2.txt", "init_sh3.txt", "init_sh4.txt", "init_sh5.txt" };


		std::ifstream _inStream;
		_inStream.open(name[i]);

		char buf[100];
		SH_init temp;



		while (!_inStream.eof())
		{
			_inStream.getline(buf, 100);
			if (parseSHInit(buf, temp))
			{
				initVectorSH[i].push_back(temp);
			}
		}
	}

	for (int i = 0; i < 3;i++)
	{
		char general_name[][40] = { "init_general.txt", "init_general2.txt", "init_general3.txt" };

		std::ifstream _inStream;
		_inStream.open(general_name[i]);

		char buf[100];
		PG_init temp;

		while (!_inStream.eof())
		{
			_inStream.getline(buf, 100);
			if (parseGPInit(buf, temp))
			{
				initVectorGP.push_back(temp);
			}
		}
	}



	{
		char time_name[40] = { "init_time.txt" };

		std::ifstream _inStream;
		_inStream.open(time_name);

		char buf[100];
		TimeDelay_init time_temp;


		while (!_inStream.eof())
		{
			_inStream.getline(buf, 100);
			if (parseDTInit(buf, time_temp))
			{
				initVectorTD.push_back(time_temp);
			}
		}
	}

	{
		char time_name[40] = { "InitAmbulanceNum.txt" };

		std::ifstream _inStream;
		_inStream.open(time_name);

		char buf[100];
		int ambulanceNum;


		while (!_inStream.eof())
		{
			_inStream.getline(buf, 100);
			if (parseANInit(buf, ambulanceNum))
			{
				initVectorAmbulNum.push_back(ambulanceNum);
			}
		}
	}



	for (int i = 0; i < 3; i++)
	{
		char name[][40] = { "init_hh1.txt", "init_hh2.txt", "init_hh3.txt" };

		std::ifstream _inStream;
		_inStream.open(name[i]);

		char buf[100];
		HH_init temp;



		while (!_inStream.eof())
		{

			_inStream.getline(buf, 100);
			if (parseHHInit(buf, temp))
			{
				initVectorHH[i].push_back(temp);
			}
		}
	}
/*

	{
		char name[] = { "init_R.txt" };

		std::ifstream _inStream;
		_inStream.open(name);

		char buf[100];
		HH_R_init temp;


		while (!_inStream.eof())
		{

			_inStream.getline(buf, 100);
			if (parseRInit(buf, temp))
			{
				initVectorR.push_back(temp);
			}
		}
	}

	{
		char name[] = { "init_CS.txt" };

		std::ifstream _inStream;
		_inStream.open(name);

		char buf[100];
		HH_CS_init temp;


		while (!_inStream.eof())
		{

			_inStream.getline(buf, 100);
			if (parseCSInit(buf, temp))
			{
				initVectorCS.push_back(temp);
			}
		}
	}
	{
		char name[] = { "init_D.txt" };

		std::ifstream _inStream;
		_inStream.open(name);

		char buf[100];
		HH_D_init temp;


		while (!_inStream.eof())
		{

			_inStream.getline(buf, 100);
			if (parseDInit(buf, temp))
			{
				initVectorD.push_back(temp);
			}
		}
	}
	{
		char name[] = { "init_FC.txt" };

		std::ifstream _inStream;
		_inStream.open(name);

		char buf[100];
		HH_FC_init temp;


		while (!_inStream.eof())
		{

			_inStream.getline(buf, 100);
			if (parseFCInit(buf, temp))
			{
				initVectorFC.push_back(temp);
			}
		}
	}
	{
		char name[] = { "init_PM.txt" };

		std::ifstream _inStream;
		_inStream.open(name);

		char buf[100];
		HH_PM_init temp;


		while (!_inStream.eof())
		{

			_inStream.getline(buf, 100);
			if (parsePMInit(buf, temp))
			{
				initVectorPM.push_back(temp);
			}
		}
	}
	{
		char name[] = { "init_S.txt" };

		std::ifstream _inStream;
		_inStream.open(name);

		char buf[100];
		HH_S_init temp;


		while (!_inStream.eof())
		{

			_inStream.getline(buf, 100);
			if (parseSInit(buf, temp))
			{
				initVectorS.push_back(temp);
			}
		}
	}*/
}

CInitManager::~CInitManager()
{
}

bool CInitManager::parseDPInit(char* buf, PG_init& temp)
{
	char *tok = strtok(buf, ": ");

	if (tok == NULL)
		return false;


	temp.injury_part_burnMax = -1;
	temp.injury_part_burnMin = -1;
	temp.injury_part_chestMax = -1;
	temp.injury_part_chestMin = -1;
	temp.injury_part_fractureMax = -1;
	temp.injury_part_fractureMin = -1;
	temp.injury_part_nerveMax = -1;
	temp.injury_part_nerveMin = -1;
	temp.injury_part_spineMax = -1;
	temp.injury_part_spineMin = -1;
	temp.severity6_max = -1;
	temp.severity6_min = -1;



	if (strcmp(tok, "generalDisaster") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.general_disaster = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "id") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.id = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "initTime") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.init_time = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "minTime") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.min_time = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "gapTime") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.gap_time = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "nextTime") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.next_time = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "injuryPart") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.injury_part = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "severity1Min") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.severity1_min = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "severity1Max") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.severity1_max = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "severity2Min") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.severity2_min = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "severity2Max") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.severity2_max = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "severity3Min") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.severity3_min = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "severity3Max") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.severity3_max = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "severity4Min") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.severity4_min = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "severity4Max") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.severity4_max = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "severity5Min") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.severity5_min = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "severity5Max") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.severity5_max = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "killTime") == 0)
	{
		tok = strtok(NULL, ": ");
		if (strcmp(tok, "Infinity") == 0)
			temp.kill_time = Infinity;
		else if (strcmp(tok, "Infinity") != 0)
			temp.kill_time = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "-") == 0)
	{
		return true;
	}
}

bool CInitManager::parseSHInit(char* buf, SH_init& temp)
{
	char *tok = strtok(buf, ": ");

	if (tok == NULL)
		return false;

	if (strcmp(tok, "id") == 0)
	{
		tok = strtok(NULL, ": "); // 자른 것 이후
		temp.id = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "doctorId") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.doctorId = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "gapTime") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.gapTime = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "minTime") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.minTime = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "gapTimeID") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.gapTimeId = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "minTimeID") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.gapTimeId = atoi(tok);
		return false;
	}
	
	else if (strcmp(tok, "-") == 0)
	{
		return true;
	}
}

bool CInitManager::parseGPInit(char* buf, PG_init& temp)
{
	char *tok = strtok(buf, ": ");

	if (tok == NULL)
		return false;

	temp.injury_part = -1;

	if (strcmp(tok, "HugeH") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.HugeH = atoi(tok);
		return false;
	}

	else if (strcmp(tok, "generalDisaster") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.general_disaster = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "id") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.id = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "initTime") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.init_time = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "minTime") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.min_time = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "gapTime") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.gap_time = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "nextTime") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.next_time = atoi(tok);
		return false;
	}





	else if (strcmp(tok, "injuryPart_nerveMin") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.injury_part_nerveMin = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "injuryPart_nerveMax") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.injury_part_nerveMax = atoi(tok);
		return false;
	}

	else if (strcmp(tok, "injuryPart_chestMin") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.injury_part_chestMin = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "injuryPart_chestMax") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.injury_part_chestMax = atoi(tok);
		return false;
	}

	else if (strcmp(tok, "injuryPart_spineMin") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.injury_part_spineMin = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "injuryPart_spineMax") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.injury_part_spineMax = atoi(tok);
		return false;
	}

	else if (strcmp(tok, "injuryPart_burnMin") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.injury_part_burnMin = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "injuryPart_burnMax") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.injury_part_burnMax = atoi(tok);
		return false;
	}

	else if (strcmp(tok, "injuryPart_fractureMin") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.injury_part_fractureMin = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "injuryPart_fractureMax") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.injury_part_fractureMax = atoi(tok);
		return false;
	}



	else if (strcmp(tok, "severity1Min") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.severity1_min = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "severity1Max") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.severity1_max = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "severity2Min") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.severity2_min = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "severity2Max") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.severity2_max = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "severity3Min") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.severity3_min = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "severity3Max") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.severity3_max = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "severity4Min") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.severity4_min = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "severity4Max") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.severity4_max = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "severity5Min") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.severity5_min = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "severity5Max") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.severity5_max = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "severity6Min") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.severity6_min = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "severity6Max") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.severity6_max = atoi(tok);
		return false;
	}


	else if (strcmp(tok, "killTime") == 0)
	{
		tok = strtok(NULL, ": ");
		if (strcmp(tok, "Infinity") == 0)
			temp.kill_time = Infinity;
		else if (strcmp(tok, "Infinity") != 0)
			temp.kill_time = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "-") == 0)
	{
		return true;
	}
}

bool CInitManager::parseDTInit(char* buf, TimeDelay_init& temp)
{
	char *tok = strtok(buf, ": ");

	if (tok == NULL)
		return false;

	if (strcmp(tok, "FirehouseAndHugeH1") == 0)
	{
		tok = strtok(NULL, ": "); // 자른 것 이후
		temp.FirehouseAndHugeH1 = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "FirehouseAndHugeH2") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.FirehouseAndHugeH2 = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "FirehouseAndHugeH3") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.FirehouseAndHugeH3 = atoi(tok);
		return false;
	}


	else if (strcmp(tok, "DisasterAndHugeH1") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.DisasterAndHugeH1 = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "DisasterAndHugeH2") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.DisasterAndHugeH2 = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "DisasterAndHugeH3") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.DisasterAndHugeH3 = atoi(tok);
		return false;
	}


	else if (strcmp(tok, "DisasterAndSmallH1") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.DisasterAndSmallH1 = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "DisasterAndSmallH2") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.DisasterAndSmallH2 = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "DisasterAndSmallH3") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.DisasterAndSmallH3 = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "DisasterAndSmallH4") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.DisasterAndSmallH4 = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "DisasterAndSmallH5") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.DisasterAndSmallH5 = atoi(tok);
		return false;
	}


	else if (strcmp(tok, "SmallH1AndHugeH1") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.SmallH1AndHugeH1 = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "SmallH2AndHugeH1") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.SmallH2AndHugeH1 = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "SmallH3AndHugeH1") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.SmallH3AndHugeH1 = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "SmallH4AndHugeH1") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.SmallH4AndHugeH1 = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "SmallH5AndHugeH1") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.SmallH5AndHugeH1 = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "SmallH1AndHugeH2") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.SmallH1AndHugeH2 = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "SmallH2AndHugeH2") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.SmallH2AndHugeH2 = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "SmallH3AndHugeH2") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.SmallH3AndHugeH2 = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "SmallH4AndHugeH2") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.SmallH4AndHugeH2 = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "SmallH5AndHugeH2") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.SmallH5AndHugeH2 = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "SmallH1AndHugeH3") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.SmallH1AndHugeH3 = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "SmallH2AndHugeH3") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.SmallH2AndHugeH3 = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "SmallH3AndHugeH3") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.SmallH3AndHugeH3 = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "SmallH4AndHugeH3") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.SmallH4AndHugeH3 = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "SmallH5AndHugeH3") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.SmallH5AndHugeH3 = atoi(tok);
		return false;
	}


	else if (strcmp(tok, "-") == 0)
	{
		return true;
	}
}

bool CInitManager::parseHHInit(char* buf, HH_init& temp)
{
	char *tok = strtok(buf, ": ");

	if (tok == NULL)
		return false;

	if (strcmp(tok, "surgery_room") == 0)
	{
		tok = strtok(NULL, ": "); // 자른 것 이후
		temp.surgery_room = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "num_nurse") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.num_nurse = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "num_doctor") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.num_doctor = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "num_burn") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.num_burn = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "num_nerve") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.num_nerve = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "num_spine") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.num_spine = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "num_fracture") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.num_fracture = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "num_chest") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.num_chest = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "x_ray_room") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.x_ray_room = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "clinic_room") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.clinic_room = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "ct_room") == 0)
	{
		tok = strtok(NULL, ": ");
		temp.ct_room = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "-") == 0)
	{
		return true;
	}
}


bool CInitManager::parseANInit(char* buf, int &num)
{
	char *tok = strtok(buf, ": ");

	if (tok == NULL)
		return false;

	if (strcmp(tok, "initAmbulanceNum") == 0)
	{
		tok = strtok(NULL, ": "); // 자른 것 이후
		num = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "-") == 0)
	{
		return true;
	}
}
/*
bool CInitManager::parseRInit(char* buf, HH_R_init& temp)
{
	char *tok = strtok(buf, ": ");

	if (tok == NULL)
		return false;

	if (strcmp(tok, "XrayPercent") == 0)
	{
		tok = strtok(NULL, ": "); // 자른 것 이후
		temp.XrayPercent = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "CTPercent") == 0)
	{
		tok = strtok(NULL, ": "); // 자른 것 이후
		temp.CTPercent = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "ClinicPercent") == 0)
	{
		tok = strtok(NULL, ": "); // 자른 것 이후
		temp.ClinicPercent = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "-----") == 0)
	{
		return true;
	}
}

bool CInitManager::parseCSInit(char* buf, HH_CS_init& temp)
{
	char *tok = strtok(buf, ": ");

	if (tok == NULL)
		return false;

	if (strcmp(tok, "SeverityTime") == 0)
	{
		tok = strtok(NULL, ": "); // 자른 것 이후
		temp.time = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "-----") == 0)
	{
		return true;
	}
}

bool CInitManager::parseDInit(char* buf, HH_D_init& temp)
{
	char *tok = strtok(buf, ": ");

	if (tok == NULL)
		return false;

	if (strcmp(tok, "0to10") == 0)
	{
		tok = strtok(NULL, ": "); // 자른 것 이후
		temp.zero = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "10to20") == 0)
	{
		tok = strtok(NULL, ": "); // 자른 것 이후
		temp.ten = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "20to30") == 0)
	{
		tok = strtok(NULL, ": "); // 자른 것 이후
		temp.twenty = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "30to40") == 0)
	{
		tok = strtok(NULL, ": "); // 자른 것 이후
		temp.thirty = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "40to50") == 0)
	{
		tok = strtok(NULL, ": "); // 자른 것 이후
		temp.fourty = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "50to60") == 0)
	{
		tok = strtok(NULL, ": "); // 자른 것 이후
		temp.fifty = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "60to80") == 0)
	{
		tok = strtok(NULL, ": "); // 자른 것 이후
		temp.sixty = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "-----") == 0)
	{
		return true;
	}
}

bool CInitManager::parseFCInit(char* buf, HH_FC_init& temp)
{
	char *tok = strtok(buf, ": ");

	if (tok == NULL)
		return false;

	if (strcmp(tok, "FirstAid") == 0)
	{
		tok = strtok(NULL, ": "); // 자른 것 이후
		temp.time = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "-----") == 0)
	{
		return true;
	}
}

bool CInitManager::parsePMInit(char* buf, HH_PM_init& temp)
{
	char *tok = strtok(buf, ": ");

	if (tok == NULL)
		return false;

	if (strcmp(tok, "Xray_Min") == 0)
	{
		tok = strtok(NULL, ": "); // 자른 것 이후
		temp.Xraymin = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "Xray_Max") == 0)
	{
		tok = strtok(NULL, ": "); // 자른 것 이후
		temp.Xraymax = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "CT_Min") == 0)
	{
		tok = strtok(NULL, ": "); // 자른 것 이후
		temp.CTmin = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "CT_Max") == 0)
	{
		tok = strtok(NULL, ": "); // 자른 것 이후
		temp.CTmax = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "Clinic_Min") == 0)
	{
		tok = strtok(NULL, ": "); // 자른 것 이후
		temp.Clinicmin = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "Clinic_Max") == 0)
	{
		tok = strtok(NULL, ": "); // 자른 것 이후
		temp.Clinicmax = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "-----") == 0)
	{
		return true;
	}
}

bool CInitManager::parseSInit(char * buf, HH_S_init& temp)
{
	char *tok = strtok(buf, ": ");

	if (tok == NULL)
		return false;

	if (strcmp(tok, "NerveSeverity1_Min") == 0)
	{
		tok = strtok(NULL, ": "); // 자른 것 이후
		temp.NerveSeverity1_Min = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "NerveSeverity1_Max") == 0)
	{
		tok = strtok(NULL, ": "); // 자른 것 이후
		temp.NerveSeverity1_Max = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "NerveSeverity2_Min") == 0)
	{
		tok = strtok(NULL, ": "); // 자른 것 이후
		temp.NerveSeverity2_Min = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "NerveSeverity2_Max") == 0)
	{
		tok = strtok(NULL, ": "); // 자른 것 이후
		temp.NerveSeverity2_Max = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "NerveSeverity3_Min") == 0)
	{
		tok = strtok(NULL, ": "); // 자른 것 이후
		temp.NerveSeverity3_Min = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "NerveSeverity3_Max") == 0)
	{
		tok = strtok(NULL, ": "); // 자른 것 이후
		temp.NerveSeverity3_Max = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "NerveSeverity4_Min") == 0)
	{
		tok = strtok(NULL, ": "); // 자른 것 이후
		temp.NerveSeverity4_Min = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "NerveSeverity4_Max") == 0)
	{
		tok = strtok(NULL, ": "); // 자른 것 이후
		temp.NerveSeverity4_Max = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "NerveSeverity5_Min") == 0)
	{
		tok = strtok(NULL, ": "); // 자른 것 이후
		temp.NerveSeverity5_Min = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "NerveSeverity5_Max") == 0)
	{
		tok = strtok(NULL, ": "); // 자른 것 이후
		temp.NerveSeverity5_Max = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "ChestSeverity1_Min") == 0)
	{
		tok = strtok(NULL, ": "); // 자른 것 이후
		temp.ChestSeverity1_Min = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "ChestSeverity1_Max") == 0)
	{
		tok = strtok(NULL, ": "); // 자른 것 이후
		temp.ChestSeverity1_Max = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "ChestSeverity2_Min") == 0)
	{
		tok = strtok(NULL, ": "); // 자른 것 이후
		temp.ChestSeverity2_Min = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "ChestSeverity2_Max") == 0)
	{
		tok = strtok(NULL, ": "); // 자른 것 이후
		temp.ChestSeverity2_Max = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "ChestSeverity3_Min") == 0)
	{
		tok = strtok(NULL, ": "); // 자른 것 이후
		temp.ChestSeverity3_Min = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "ChestSeverity3_Max") == 0)
	{
		tok = strtok(NULL, ": "); // 자른 것 이후
		temp.ChestSeverity3_Max = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "ChestSeverity4_Min") == 0)
	{
		tok = strtok(NULL, ": "); // 자른 것 이후
		temp.ChestSeverity4_Min = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "ChestSeverity4_Max") == 0)
	{
		tok = strtok(NULL, ": "); // 자른 것 이후
		temp.ChestSeverity4_Max = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "ChestSeverity5_Min") == 0)
	{
		tok = strtok(NULL, ": "); // 자른 것 이후
		temp.ChestSeverity5_Min = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "ChestSeverity5_Max") == 0)
	{
		tok = strtok(NULL, ": "); // 자른 것 이후
		temp.ChestSeverity5_Max = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "SpineSeverity1_Min") == 0)
	{
		tok = strtok(NULL, ": "); // 자른 것 이후
		temp.SpineSeverity1_Min = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "SpineSeverity1_Max") == 0)
	{
		tok = strtok(NULL, ": "); // 자른 것 이후
		temp.SpineSeverity1_Max = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "SpineSeverity2_Min") == 0)
	{
		tok = strtok(NULL, ": "); // 자른 것 이후
		temp.SpineSeverity2_Min = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "SpineSeverity2_Max") == 0)
	{
		tok = strtok(NULL, ": "); // 자른 것 이후
		temp.SpineSeverity2_Max = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "SpineSeverity3_Min") == 0)
	{
		tok = strtok(NULL, ": "); // 자른 것 이후
		temp.SpineSeverity3_Min = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "SpineSeverity3_Max") == 0)
	{
		tok = strtok(NULL, ": "); // 자른 것 이후
		temp.SpineSeverity3_Max = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "SpineSeverity4_Min") == 0)
	{
		tok = strtok(NULL, ": "); // 자른 것 이후
		temp.SpineSeverity4_Min = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "SpineSeverity4_Max") == 0)
	{
		tok = strtok(NULL, ": "); // 자른 것 이후
		temp.SpineSeverity4_Max = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "SpineSeverity5_Min") == 0)
	{
		tok = strtok(NULL, ": "); // 자른 것 이후
		temp.SpineSeverity5_Min = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "SpineSeverity5_Max") == 0)
	{
		tok = strtok(NULL, ": "); // 자른 것 이후
		temp.SpineSeverity5_Max = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "BurnSeverity1_Min") == 0)
	{
		tok = strtok(NULL, ": "); // 자른 것 이후
		temp.BurnSeverity1_Min = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "BurnSeverity1_Max") == 0)
	{
		tok = strtok(NULL, ": "); // 자른 것 이후
		temp.BurnSeverity1_Max = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "BurnSeverity2_Min") == 0)
	{
		tok = strtok(NULL, ": "); // 자른 것 이후
		temp.BurnSeverity2_Min = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "BurnSeverity2_Max") == 0)
	{
		tok = strtok(NULL, ": "); // 자른 것 이후
		temp.BurnSeverity2_Max = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "BurnSeverity3_Min") == 0)
	{
		tok = strtok(NULL, ": "); // 자른 것 이후
		temp.BurnSeverity3_Min = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "BurnSeverity3_Max") == 0)
	{
		tok = strtok(NULL, ": "); // 자른 것 이후
		temp.BurnSeverity3_Max = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "BurnSeverity4_Min") == 0)
	{
		tok = strtok(NULL, ": "); // 자른 것 이후
		temp.BurnSeverity4_Min = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "BurnSeverity4_Max") == 0)
	{
		tok = strtok(NULL, ": "); // 자른 것 이후
		temp.BurnSeverity4_Max = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "BurnSeverity5_Min") == 0)
	{
		tok = strtok(NULL, ": "); // 자른 것 이후
		temp.BurnSeverity5_Min = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "BurnSeverity5_Max") == 0)
	{
		tok = strtok(NULL, ": "); // 자른 것 이후
		temp.BurnSeverity5_Max = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "FractureSeverity1_Min") == 0)
	{
		tok = strtok(NULL, ": "); // 자른 것 이후
		temp.FractureSeverity1_Min = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "FractureSeverity1_Max") == 0)
	{
		tok = strtok(NULL, ": "); // 자른 것 이후
		temp.FractureSeverity1_Max = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "FractureSeverity2_Min") == 0)
	{
		tok = strtok(NULL, ": "); // 자른 것 이후
		temp.FractureSeverity2_Min = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "FractureSeverity2_Max") == 0)
	{
		tok = strtok(NULL, ": "); // 자른 것 이후
		temp.FractureSeverity2_Max = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "FractureSeverity3_Min") == 0)
	{
		tok = strtok(NULL, ": "); // 자른 것 이후
		temp.FractureSeverity3_Min = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "FractureSeverity3_Max") == 0)
	{
		tok = strtok(NULL, ": "); // 자른 것 이후
		temp.FractureSeverity3_Max = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "FractureSeverity4_Min") == 0)
	{
		tok = strtok(NULL, ": "); // 자른 것 이후
		temp.FractureSeverity4_Min = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "FractureSeverity4_Max") == 0)
	{
		tok = strtok(NULL, ": "); // 자른 것 이후
		temp.FractureSeverity4_Max = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "FractureSeverity5_Min") == 0)
	{
		tok = strtok(NULL, ": "); // 자른 것 이후
		temp.FractureSeverity5_Min = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "FractureSeverity5_Max") == 0)
	{
		tok = strtok(NULL, ": "); // 자른 것 이후
		temp.FractureSeverity5_Max = atoi(tok);
		return false;
	}
	else if (strcmp(tok, "-----") == 0)
	{
		return true;
	}
}
*/
