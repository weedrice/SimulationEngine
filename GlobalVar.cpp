#include "GlobalVar.h"

CGlobalVar* CGlobalVar::pInstance_ = NULL;

CGlobalVar::CGlobalVar(void)
	:ambulance_count(0)
{
	doctor = 0;
	PatientId_G = 0;
	PatientId_D = 0;
	GetHHNum = 0;
	PGpatient = 0;
	//bool SHTable = new bool[5];
	for (int i = 0; i < 5; i++)
		SHTable[i] = true;


	CheckSH = 0;

	srand(0);
	gen_rand_num = 0;
}	

CGlobalVar::~CGlobalVar()
{
}

CGlobalVar* CGlobalVar::GetInstance()
{
	if (pInstance_ == NULL)
	{
		pInstance_ = new CGlobalVar();
	}

	return pInstance_;
}

bool CGlobalVar::isEmpty()
{
	int _empty = 0;

	for (int i = 0; i < 3; i++)
	{
		if (pMapPG[i].empty() != true)
			_empty++;
	}

	if (_empty == 2)
		return false;
	else
		return true;
}

void CGlobalVar::InsertToPatientList(int _idx, sPatient_info _info)
{
	pMapPG[_idx].insert(std::pair<int, sPatient_info>(_info.id, _info));
	//pVectorPG[_idx].push_back(_info);
}

bool CGlobalVar::RemoveFromPatientList(int _idx, int pid)
{
	
	std::map<int, sPatient_info>::iterator _iter = pMapPG[_idx].find(pid);

	if (_iter != pMapPG[_idx].end())
	{
		pMapPG[_idx].erase(pid);
		return true;
	}
	else
		return false;

		
// 	if (!pVectorPG[_idx].empty())
// 	{
// 		for (std::vector<sPatient_info>::iterator _iter = pVectorPG[_idx].begin();
// 			_iter != pVectorPG[_idx].end();
// 			)
// 		{
// 			if ((*_iter).id == pid)
// 			{
// 				_iter = pVectorPG[_idx].erase(_iter);
// 			}
// 			else
// 				_iter++;
// 		}
// 
// 		return true;
// 	}
// 	else
// 		return false;
	
}

int CGlobalVar::GenRand()
{
	//srand(0);
	//gen_rand_num++;
	//std::cout << "gen num:" << gen_rand_num << " ";
	return rand();
}
