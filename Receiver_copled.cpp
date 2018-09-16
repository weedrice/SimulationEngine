#pragma once
#include "Receiver_copled.h"
#include "DEVSim.h"
#include "Info.h"
//#include "ReceiverConnector.h"
#include "ReceiverVector.h"
#include "GlobalVar.h"

 std::string Receiver_copled::SH_to_Receiver_coupled = "SH_to_Receiver_coupled";
 std::string Receiver_copled::i_SHCoupled = "i_SHCoupled";
 std::string Receiver_copled::o_SHCoupled = "o_SHcoupeld";

Receiver_copled::Receiver_copled(){ }
Receiver_copled::Receiver_copled(int id, int _count) //�ڱⰡ ���° Ŀ�õ� ����, �� �ڱ����� �Ҵ�� �ǻ簡 �������./
	:_id(id), count(_count)
{
	char buf[100];
	sprintf(buf, "ReciverCouple[%d]", id);

	SetName(buf);

	AddInPorts(2, SH_to_Receiver_coupled.c_str(),i_SHCoupled.c_str());
	AddOutPorts(1, o_SHCoupled.c_str());
	//Model
	GLOBAL_VARIABLE->SetDoctorNum(id,_count); // �Ҵ�ÿ� �ǻ� ���� �־��ش�. 
	// Error 
	// doctorTable = new bool[count] maybe?
	
	bool *doctor = new bool[count];
	for (int i = 0; i < count; i++)
	{
		doctor[i] = true;
	}

	CModel*vectorModel = new ReceiverVector(_id, doctor,count);
	

	AddComponent(1, vectorModel);
	
	
	
	AddCoupling(vectorModel, ReceiverVector::out_vector_to_doctor.c_str(), this, o_SHCoupled.c_str());
	AddCoupling(this, i_SHCoupled.c_str(), vectorModel, ReceiverVector::in_vector_to_doctor.c_str());
	AddCoupling(this, SH_to_Receiver_coupled.c_str(), vectorModel, ReceiverVector::from_doctor_to_vector.c_str());
}


Receiver_copled::~Receiver_copled()
{
}
