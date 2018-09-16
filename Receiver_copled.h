#pragma once
#include "DEVSim.h"
#include "Info.h"

class Receiver_copled : public CCoupled
{
public:
	Receiver_copled(int id, int _count);
	Receiver_copled();
	~Receiver_copled(); 
	static std::string SH_to_Receiver_coupled;
	static std::string i_SHCoupled;
	static std::string o_SHCoupled;

	int GetId(){ return _id; }
	void SetId(int id){ _id = id;}
	
private:

	  int _id;
	  int count;
	  bool* doctorTable;
};

