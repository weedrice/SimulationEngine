#include "ReceiverVector.h"
#include "DEVSim.h"
#include "info.h"
#include "Receiver_copled.h"
#include "InitManager.h"
#include "GlobalVar.h"

std::string ReceiverVector::in_vector_to_doctor = "vector_to_connect_in";
std::string ReceiverVector::out_vector_to_doctor = "vector_to_connect_out";
std::string ReceiverVector::from_doctor_to_vector = "from_doctor_to_vector";


ReceiverVector::ReceiverVector(int _id, bool* _doctorTable,int _doctorNum)
	:id(_id), doctor_table(_doctorTable), doctorNum(_doctorNum)
{
	

	SetName("ReceiverVector");
	AddInPorts(2, in_vector_to_doctor.c_str(), from_doctor_to_vector.c_str());
	AddOutPorts(1, out_vector_to_doctor.c_str());
	_mState = IDLE;
	totalDocNum = _doctorNum;
	
	
		
}


ReceiverVector::~ReceiverVector()
{

}

bool ReceiverVector::ExtTransFn(const CDEVSimMessage & _msg)
{
	if (_msg.GetPort().compare(from_doctor_to_vector.c_str()) == 0)
	{
		//가능한 의사를 체크한다. docterNum을 증가시킨다 어떤 의사인지
		SHInfo *sendDoctor = (SHInfo *)_msg.GetArg(0);
		doctor_table[sendDoctor->data.doctorId] = true;
		doctorNum++;
		GLOBAL_VARIABLE->IncreaseSHDoctorNum(id);
		
	}

	else if (_msg.GetPort().compare(in_vector_to_doctor.c_str()) == 0)
	{
		CInfo * arrived_patient_msg = (CInfo*)_msg.GetArg(0);

		if (arrived_patient_msg->data.small_h == id)
		{
			pVector.push_back(arrived_patient_msg->data);
			if (doctorNum > 0)
			{
				/*SHInfo *sendDoctor = (SHInfo *)_msg.GetArg(0);
				doctor_table[sendDoctor->data.doctorId] = false; //*/
				_mState = SEND;

				doctorNum--;
				GLOBAL_VARIABLE->DecreaseSHDoctorNum(id);

			}
			else
			{
				_mState = IDLE;


			}

		}
	
	}


	return true;
}

bool ReceiverVector::IntTransFn()
{
	if (_mState == SEND){
		_mState = IDLE;
	}
	else{
		_mState = IDLE;
	}
	return true;

}

bool ReceiverVector::OutputFn(CDEVSimMessage &_msg)
{
	if(_mState == SEND)
	{
		
		CInfo* temp = new CInfo(pVector.front());
		
		//_msg.SetPortValue(out_vector_to_doctor.c_str(), new CInfo(pVector.front()));
		//

		for (int i = 0; i < totalDocNum; i++)
		{
			if (doctor_table[i] ==true)
			{
				temp->set_sh_doctor(i);
				_msg.SetPortValue(out_vector_to_doctor.c_str(), temp);
				doctor_table[i] = false;
				break;
			}
		}

		pVector.erase(pVector.begin()); //의문점
		
		
	}
	else if (_mState == IDLE)
	{
		_msg.SetPortValue(out_vector_to_doctor.c_str(), NULL);
	}
	return true;
	
}

TimeType ReceiverVector::TimeAdvanceFn()
{
	if (_mState == IDLE)
		return Infinity;
	else if(_mState == SEND)
		return 0;
}

