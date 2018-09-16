#include "Outmost.h"
#include "GlobalVar.h"
#include "PG_coupled.h"
#include "AG_coupled.h"
#include "Command_Center.h"
#include "SH_coupled.h"
#include "InitManager.h"
#include "TimeDelay.h"
#include "HH_outmost.h"
#include "Firehouse.h"

COutmost::COutmost()
{
	SetName("Outmost");

	CModel* pPG_coupled = new CPG_coupled;
	CModel* pAG_coupled = new CAG_coupled;
	CModel* ptemp = new CCommand_Center;
	CModel* pSH_coupled = new SH_coupled;
	CModel* pHH_coupled = new HH_outmost;
	

	CInitManager initManager;



	CModel* pFirehouse = new CFirehouse(initManager.GetInitVectorAN().back(), initManager.GetInitVectorTD().back());
	CModel *pPN = new CTimeDelay(initManager.GetInitVectorTD().back());
	CModel *pPN1 = new CTimeDelay(initManager.GetInitVectorTD().back());
	CModel *pPN2 = new CTimeDelay(initManager.GetInitVectorTD().back());
	AddComponent(4, pPN1, pPN2, pPN, pFirehouse);

	
	AddComponent(5, pAG_coupled, pPG_coupled, ptemp, pSH_coupled, pHH_coupled);


	// PG���� AG
	AddCoupling(pPG_coupled, CPG_coupled::outC_PG_to_AG.c_str(), pAG_coupled, CAG_coupled::inC_PatientG_to_AmbulanceG.c_str());
	// PG���� HH(�Ϲ� ���� ȯ��)
	AddCoupling(pPG_coupled, CPG_coupled::outC_PG_to_HH_G.c_str(), pHH_coupled, HH_outmost::from_AG.c_str());


	// AG���� �ҹ漭�� ������ ���� ����
	AddCoupling(pPG_coupled, CPG_coupled::outC_PG_to_FH.c_str(), pFirehouse, CFirehouse::inA_PG_to_Firehouse.c_str());
	AddCoupling(pFirehouse, CFirehouse::outA_Firehouse_to_AG.c_str(), pAG_coupled, CAG_coupled::inC_Firehouse_to_AmbulanceG.c_str());


	// AG���� SH ���� ȯ�� ������ ����
	AddCoupling(pAG_coupled, CAG_coupled::outC_AmbulanceG_to_SmallH.c_str(), pPN, CTimeDelay::inA_incoming.c_str());
	AddCoupling(pPN, CTimeDelay::outA_outcoming.c_str(), pSH_coupled, SH_coupled::inC_from_AG_coupled.c_str());


	// AG���� �������� �ʰ� HH ���� ȯ�� ������ ����
	AddCoupling(pAG_coupled, CAG_coupled::outC_AmbulanceG_to_HugeH.c_str(), pPN1, CTimeDelay::inA_incoming.c_str());
	AddCoupling(pPN1, CTimeDelay::outA_outcoming.c_str(), pHH_coupled, HH_outmost::from_AG.c_str());


	// SH���� HH ���� ȯ�� ������ ����
	AddCoupling(pSH_coupled, SH_coupled::outC_SH_to_HH.c_str(), pPN2, CTimeDelay::inA_incoming.c_str());
	AddCoupling(pPN2, CTimeDelay::outA_outcoming.c_str(), pHH_coupled, HH_outmost::from_AG.c_str());


	// HH���� AG�� �ٽ� ����
	AddCoupling(pHH_coupled, HH_outmost::to_AG.c_str(), pAG_coupled, CAG_coupled::inC_HugeH_to_AmbulanceG.c_str());
	
	// HH���� CC��
	AddCoupling(pHH_coupled, HH_outmost::to_CC.c_str(), ptemp, CCommand_Center::inA_HH_to_CC.c_str());

	
}


COutmost::~COutmost()
{
}
