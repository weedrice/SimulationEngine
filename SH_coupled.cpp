#include "SH_coupled.h"
#include <vector>
#include "InitManager.h"
#include "Info.h"
#include "SH.h"
#include "Receiver_copled.h"
#include "GlobalVar.h"
#include "ReceiverVector.h"
#include "ReceiverConnector.h"

 //std::string SH_coupled::outC_SH_to_Receiver="SH_to_Receciver";
 std::string SH_coupled::outC_SH_to_HH = "SH_to_HH";
 std::string SH_coupled::inC_from_AG_coupled = "from AG_coupled";

SH_coupled::SH_coupled()
{
	SetName("SH_coupled");

	CInitManager initManager;

	AddOutPorts(1, outC_SH_to_HH.c_str());
	AddInPorts(1, inC_from_AG_coupled.c_str());

	std::vector<CCoupled*> coupledList;
	
	

	for (int i = 0; i < 5;i++)
	{	
		CCoupled *pPN = new Receiver_copled(i, initManager.initVectorSH[i].size());
		AddComponent(1, pPN);
		coupledList.push_back(pPN);
	}
	//���⼭ ���� SH �� �� �Ҵ��ϱ� 



	std::vector<CModel*>compoList[5];

	
	for (int i = 0; i < 5; i++)
	{
		for (std::vector<SH_init>::iterator it = initManager.initVectorSH[i].begin(); it != initManager.initVectorSH[i].end(); it++)
			{
				CModel *pSN = new CSH(*it); // �־��ְ� �Ҵ�.
				AddComponent(1, pSN);
				compoList[i].push_back(pSN);
				
			}
	}


	for (int i = 0; i < 5; i++)
	{
		int count = 0;
		for (std::vector<CModel*>::iterator itM = compoList[i].begin(); itM != compoList[i].end(); itM++)
		{
			count++;
		}
		GLOBAL_VARIABLE->SetDoctorNum(i, count);

	}


	
//���� �𵨵��� �Ҵ���, ���� Ŀ�ø�
	
	int count = 0;
	for (std::vector<CCoupled*>::iterator it = coupledList.begin(); it != coupledList.end(); it++)
	{
		AddCoupling(this, inC_from_AG_coupled.c_str(), *it, Receiver_copled::i_SHCoupled.c_str());
		for (std::vector<CModel*>::iterator itM = compoList[count].begin(); itM != compoList[count].end(); itM++)
		{

			AddCoupling(*it, Receiver_copled::o_SHCoupled.c_str(), *itM, CSH::from_Receiver.c_str());
			AddCoupling(*itM, CSH::cureDone.c_str(), *it, Receiver_copled::SH_to_Receiver_coupled.c_str());
			AddCoupling(*itM, CSH::outSH_to_HH.c_str(), this, SH_coupled::outC_SH_to_HH.c_str());
		}
		count++;
	
	}

	/*for (int i = 0; i < 5; i++){
		for (std::vector<CModel*>::iterator itM = compoList[i].begin(); itM != compoList[i].end(); itM++)
		{
			AddCoupling(*itM, CSH::outSH_to_HH.c_str(), this, SH_coupled::outC_SH_to_HH.c_str());
		}
	}*/
	// �� ������ �ǻ� �� �� �����ؼ� i�� ���� 
	


}



SH_coupled::~SH_coupled()
{

}
