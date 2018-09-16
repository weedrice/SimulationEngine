#include "ReceiverConnector.h"


ReceiverConnector::ReceiverConnector()
{
	SetName("ReceiverConnector");

	AddInPorts(1, from_vector.c_str());
	AddOutPorts(1, in_connect_to_doctor.c_str());

	_mState = IDLE;

}


ReceiverConnector::~ReceiverConnector()
{
}

bool ReceiverConnector::ExtTransFn(CDEVSimMessage & _msg)
{
	CInfo* arrived_patient_msg = (CInfo*)_msg.GetArg(0);
	arrived_patient = arrived_patient_msg->data;

	if (_msg.GetPort().compare(from_vector.c_str())){

		_mState = SEND;
	}

	return true;
}

bool ReceiverConnector::IntTransFn()
{
	if (_mState == SEND)
	{
		_mState = IDLE;
	}
	else if (_mState == IDLE)
	{
		_mState = IDLE;
	}

	return true;
}

bool ReceiverConnector::OutputFn(CDEVSimMessage &_msg)
{
	if (_mState == SEND)
	{
		//환자를 적절한 의사에게 보내준다.
	}

	return true;
}

TimeType ReceiverConnector::TimeAdvanceFn()
{
	return Infinity;
}

std::string ReceiverConnector::from_vector;

std::string ReceiverConnector::in_connect_to_doctor;
