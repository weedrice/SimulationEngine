#include <iostream>
#include "DEVSim.h"
#include "Outmost.h"
#include "SH_coupled.h"
#include <time.h>
#include "GlobalVar.h"


int main()
{

	//srand(1);
	//CREATE_LOG_STD(SIM_RESULT, LOG_INFO); // 화면에 일련의 과정 수행 출력!!
	
	
	CREATE_LOG_FILE(CAT_ALL, LOG_DEBUG, "result");

	// DEVSimInterface 설정
	CDEVSimInterface* pInterface = CDEVSimInterfaceDefaultFactory::create();
	SET_DEVSINTERFACE(pInterface);

	pInterface->SimOption.dRatio = 200;
	pInterface->SimOption.TimeMode = CSimOption::SECOND;
	pInterface->SimOption.bRealtime = true;
	pInterface->SimOption.bMultiThread = false;

	CCoupled* model = new COutmost;
	pInterface->SetModel(model);

	pInterface->SimulationStart();

	//pInterface->SimOption.bMultiThread = false; 이므로
	// 다음 함수에서 종료시까지 Blocking
	pInterface->EngineStart();


	// 모델 삭제
	delete pInterface->GetModel();
	pInterface->SetModel(NULL);

	CDEVSimInterfaceDefaultFactory::destroy(pInterface);
	pInterface = NULL;
}