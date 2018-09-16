#include <iostream>
#include "DEVSim.h"
#include "Outmost.h"
#include "SH_coupled.h"
#include <time.h>
#include "GlobalVar.h"


int main()
{

	//srand(1);
	//CREATE_LOG_STD(SIM_RESULT, LOG_INFO); // ȭ�鿡 �Ϸ��� ���� ���� ���!!
	
	
	CREATE_LOG_FILE(CAT_ALL, LOG_DEBUG, "result");

	// DEVSimInterface ����
	CDEVSimInterface* pInterface = CDEVSimInterfaceDefaultFactory::create();
	SET_DEVSINTERFACE(pInterface);

	pInterface->SimOption.dRatio = 200;
	pInterface->SimOption.TimeMode = CSimOption::SECOND;
	pInterface->SimOption.bRealtime = true;
	pInterface->SimOption.bMultiThread = false;

	CCoupled* model = new COutmost;
	pInterface->SetModel(model);

	pInterface->SimulationStart();

	//pInterface->SimOption.bMultiThread = false; �̹Ƿ�
	// ���� �Լ����� ����ñ��� Blocking
	pInterface->EngineStart();


	// �� ����
	delete pInterface->GetModel();
	pInterface->SetModel(NULL);

	CDEVSimInterfaceDefaultFactory::destroy(pInterface);
	pInterface = NULL;
}