#include "SH.h"
#include "info.h"
#include "GlobalVar.h"
#include <stdlib.h>

std::string CSH::outSH_to_HH = "SH to HH";
std::string CSH::from_Receiver = "from Receiver";
std::string CSH::cureDone = "Cure Done";


CSH::CSH(SH_init _sh)
	:m_SH(_sh)
{
	char buf[100];
	sprintf(buf, "SH%d", m_SH.id);

	SetName(buf);

	AddInPorts(1, from_Receiver.c_str());
	AddOutPorts(2, outSH_to_HH.c_str(), cureDone.c_str());

	_mState = IDLE;
}


CSH::~CSH()
{
}

bool CSH::ExtTransFn(const CDEVSimMessage &msg)
{
	
	if (msg.GetPort().compare(from_Receiver.c_str()) == 0)
	{
		CInfo * arrived_patient_msg = (CInfo*)msg.GetArg(0);
		

		if (arrived_patient_msg->get_sh_doctor() == m_SH.doctorId)
		{	

//			COUT << "" << m_SH.id << ENDL;
			m_PI = arrived_patient_msg->data;
			_mState = CURE;
			
			

			std::cout << " ������ ���� �ð� : " << DEVSINTERFACE_PTR->GetCurrentSimulationTime().GetValue() << std::endl;
			std::cout << " �߼Һ����� ȯ�� �����Ͽ����ϴ�.  ȯ�� ���̵� : " << arrived_patient_msg->data.id << std::endl;
			std::cout << " ȯ�� �λ���� : " << arrived_patient_msg->data.injury_part << std::endl;
			std::cout << " ȯ�� ���� ���� : ";
			if (arrived_patient_msg->data.small_h == SH1)
				std::cout << " SH1" << std::endl;
			else if (arrived_patient_msg->data.small_h == SH2)
				std::cout << " SH2" << std::endl;
			else if (arrived_patient_msg->data.small_h == SH3)
				std::cout << " SH3" << std::endl;
			else if (arrived_patient_msg->data.small_h == SH4)
				std::cout << " SH4" << std::endl;
			else if (arrived_patient_msg->data.small_h == SH5)
				std::cout << " SH5" << std::endl;

			std::cout << "���� ���� ID : " << m_SH.id << std::endl;
			std::cout << "ȯ�� ��� ���� : ";

			if (arrived_patient_msg->data.huge_h == HH1)
				std::cout << " HH1" << std::endl;
			else if (arrived_patient_msg->data.huge_h == HH2)
				std::cout << " HH2" << std::endl;
			else if (arrived_patient_msg->data.huge_h == HH3)
				std::cout << " HH3" << std::endl;
		}
	}

	

	return true;
}

bool CSH::IntTransFn()
{
	if (_mState == CURE)
	{
		_mState = IDLE;
	}
	else if (_mState == IDLE)
	{
		_mState = IDLE;
	}

	return true;
}

bool CSH::OutputFn(CDEVSimMessage &msg)
{
	if (_mState == CURE)
	{
		m_PI.pPosition = SH;

		msg.SetPortValue(outSH_to_HH.c_str(), new CInfo(m_PI));
		msg.SetPortValue(cureDone.c_str(), new SHInfo(m_SH)); //receiver coupled �� ����. m_sh�� ���� ���� ��� �־���?
		
		std::cout << " �߼Һ������� [" << m_SH.id << "] ���� ȯ�ڸ� ġ���Ͽ����ϴ�." << std::endl;
		std::cout << " ���� �ð��� : " << DEVSINTERFACE_PTR->GetCurrentSimulationTime().GetValue() << std::endl;
	}
	return true;
}

TimeType CSH::TimeAdvanceFn()
{
	if (_mState == IDLE)
		return Infinity;
	else if (_mState == CURE)
		return GLOBAL_VARIABLE->GenRand() % m_SH.gapTime + m_SH.minTime;
	else
		return Infinity;
}
