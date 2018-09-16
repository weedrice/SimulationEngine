#ifndef _GLOBAL_VAR_H
#define _GLOBAL_VAR_H

#include <vector>
#include <string>
#include <map>
#include "Info.h"

#define SIM_RESULT	5723
#define DEBUG_LOG	2735

class CGlobalVar
{
public:
	int CheckSH;
	int count_severity[5][5];
	static CGlobalVar* GetInstance();
	virtual ~CGlobalVar();

	void IncreaseAmbulanceNum(){ ambulance_count++; }
	void DecreaseAmbulanceNum(){ ambulance_count--; }
	void SetAmbulanceNum(int _num) { ambulance_count = _num; }
	int GetAmulanceNum(){ return ambulance_count; }

	int GetAmulanceNum_FH(){ return initambulance_count; }
	void DecreaseAmbulanceNum_FH(){ initambulance_count--; }
	void SetAmbulanceNum_FH(int _num) { initambulance_count = _num; }


	void SetDoctorNum(int _idx, int num){ shDoctorNum[_idx] = num; }
	int GetDoctorNUm(int _idx){ return shDoctorNum[_idx]; }
	void DecreaseSHDoctorNum(int _idx){ shDoctorNum[_idx]--; }
	void IncreaseSHDoctorNum(int _idx){ shDoctorNum[_idx]++; }


	int GetDisasterPatientLast() { return PatientId_D; }
	int IncreasePatientId_G(){ return PatientId_G++; }
	int IncreasePatientId_D(){ return PatientId_D++; }


	void SetHH(HH_init HH, int id )	{ m_HH[id] = HH; }
	void SetHH_for_PG(HH_init HH, int id){ m_HH_for_PG[id] = HH; }

	int GetHHDoctorNum(int id) { return m_HH[id].num_doctor; }
	int GetHHNurseNum(int id) { return m_HH[id].num_nurse; }
	int GetHHSPINENum(int id) { return m_HH[id].num_spine; }
	int GetHHBURNNum(int id) { return m_HH[id].num_burn; }
	int GetHHFRACTURENum(int id) { return m_HH[id].num_fracture; }
	int GetHHCHESTNum(int id) { return m_HH[id].num_chest; }
	int GetHHNERVENum(int id) { return m_HH[id].num_nerve; }
	int GetHHSurgeryNum(int id) { return m_HH[id].surgery_room; }
	int GetHHSurgeryNum_for_PG(int id) { return m_HH_for_PG[id].surgery_room; }
	void DecreaseHHDoctorNum(int id) { m_HH[id].num_doctor--; }
	void DecreaseHHNurseNum(int id) { m_HH[id].num_nurse--; }
	void DecreaseHHSPINENum(int id) { m_HH[id].num_spine--; }	
	void DecreaseHHBURNNum(int id) { m_HH[id].num_burn--; }
	void DecreaseHHFRACTURENum(int id) { m_HH[id].num_fracture--; }
	void DecreaseHHCHESTNum(int id) { m_HH[id].num_chest--; }
	void DecreaseHHNERVENum(int id) { m_HH[id].num_nerve--; }
	void DecreaseHHSurgeryNum(int id) { m_HH[id].surgery_room--; }
	void DecreaseHHSurgeryNum_for_PG(int id){ m_HH_for_PG[id].surgery_room--; }
	void IncreaseHHDoctorNum(int id) { m_HH[id].num_doctor++; }
	void IncreaseHHNurseNum(int id) { m_HH[id].num_nurse++; }
	void IncreaseHHSPINENum(int id) { m_HH[id].num_spine++; }
	void IncreaseHHBURNNum(int id) { m_HH[id].num_burn++; }
	void IncreaseHHFRACTURENum(int id) { m_HH[id].num_fracture++; }
	void IncreaseHHCHESTNum(int id) { m_HH[id].num_chest++; }
	void IncreaseHHNERVENum(int id) { m_HH[id].num_nerve++; }
	void IncreaseHHSurgeryNum(int id) { m_HH[id].surgery_room++; }
	void IncreaseHHSurgeryNum_for_PG(int id){ m_HH_for_PG[id].surgery_room++; }
	int GetPL(int id){ return PatienWaiting[id]; }
	void SetPL(int id, int num){ PatienWaiting[id]=num;}
	void DecreasePL(int id){ PatienWaiting[id]--; }
	void IncreasePL(int id){ PatienWaiting[id]++; }
	void IncreaseAfter(){ AfterSurgeryNum++; }
	void DecreaseAfter(){ AfterSurgeryNum--; }
	int GetAfterNum(){ return AfterSurgeryNum; }
	void SetAfterNum(int pNum){ AfterSurgeryNum = pNum; }
	int GetGetHHNum(){ return GetHHNum; }
	void IncreaseHHnum(){ GetHHNum++; }

	int GetPGpatientNum() { return PGpatient; }
	void IncreasePGpatient() { PGpatient++; }

	void setDiagnosisNum(int _id) { diagnosisNum[_id] = 0; }
	void IncreaseDiagnosis(int _id) { diagnosisNum[_id]++; }
	int GetDiagnosisNum(int _id) { return diagnosisNum[_id]; }
	
	void ChangeSHTable(int _idx)
	{
		if (SHTable[_idx] == true)
		{
			SHTable[_idx] = false;
		}

		if (SHTable[_idx] == false)
		{
			SHTable[_idx] = true;
		}
	}
	bool GetSHTable(int _idx)
	{
		return SHTable[_idx];

	}

	bool isEmpty();
		
	void InsertToPatientList(int _idx, sPatient_info _info);

	bool RemoveFromPatientList(int _idx, int pid);

protected:

	CGlobalVar(void);


private:
	static CGlobalVar*	pInstance_;

	int PatientId_D;
	int PatientId_G;

	int PGpatient;

	int initambulance_count;
	int ambulance_count;
	int doctor; // 임시변수
	int shDoctorNum[5];
	int diagnosisNum[3];
	HH_init m_HH[3];
	HH_init m_HH_for_PG[3];
	int PatienWaiting[5];
	int AfterSurgeryNum;
	int GetHHNum;
	bool SHTable[5];
	std::map<int, sPatient_info> pMapPG[3];
	std::vector<sPatient_info> pVectorPG[3];

	int gen_rand_num;
public:
	int GenRand();
};

#define GLOBAL_VARIABLE	(CGlobalVar::GetInstance())


#endif	// _GLOBAL_VAR_H