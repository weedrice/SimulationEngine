#pragma once
#include "Info.h"
#include <vector>
#include "Receiver_copled.h"
#include "SH.h"
class CInitManager
{
public:
	CInitManager();
	~CInitManager();
	


	/*std::vector<Receiver_copled>&GetInitVectorRCoupled(){ return initVectorRCoupled; }*/
	std::vector<PG_init>& GetInitVectorDP(){ return initVectorDP; }
	std::vector<PG_init>& GetInitVectorGP(){ return initVectorGP; }
	std::vector<TimeDelay_init>& GetInitVectorTD(){ return initVectorTD; }
	std::vector<int>& GetInitVectorAN(){ return initVectorAmbulNum; }
	bool parseSHInit(char* buf, SH_init& temp);
	bool parseGPInit(char* buf, PG_init& temp);
	bool parseDPInit(char* buf, PG_init& temp);
	bool parseDTInit(char* buf, TimeDelay_init& temp);
	bool parseHHInit(char* buf, HH_init& temp);
	bool parseANInit(char* buf, int &num);

public:
	std::vector<SH_init> initVectorSH[5];
	std::vector<HH_init> initVectorHH[3];
	
private:
	/*std::vector<Receiver_copled> initVectorRCoupled;*/
	std::vector<PG_init> initVectorDP;
	std::vector<PG_init> initVectorGP;
	std::vector<TimeDelay_init> initVectorTD;
	std::vector<int> initVectorAmbulNum;

};

