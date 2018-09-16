#include "HH_General_Manage.h"


std::string HH_General_Manage::from_Clinic = "from_Clinic";
std::string HH_General_Manage::from_X_ray = "from_X_ray";
std::string HH_General_Manage::from_CT = "from_CT";
std::string HH_General_Manage::to_manage_surgery = "to_manage_surgery";
std::string HH_General_Manage::to_CT = "to_CT";
std::string HH_General_Manage::to_Clinic = "to_Clinic";
std::string HH_General_Manage::to_X_ray = "to_X_ray";
std::string HH_General_Manage::from_sort = "from_sort";
std::string HH_General_Manage::to_no_surgery = "to_no_surgery";


HH_General_Manage::HH_General_Manage()
{
	SetName("HH_General_Manage");
	AddInPorts(4, from_sort.c_str(), from_X_ray.c_str(), from_CT.c_str(), from_Clinic.c_str());
	AddOutPorts(4, to_X_ray.c_str(), to_manage_surgery.c_str(), to_CT.c_str(), to_Clinic.c_str());
	_mState = IDLE;

}

HH_General_Manage::~HH_General_Manage()
{

}



bool HH_General_Manage::ExtTransFn(const CDEVSimMessage &msg)
{
	if (msg.GetPort().compare(from_sort.c_str()) == 0)
	{
		CInfo* arrived_patient_msg = (CInfo*)msg.GetArg(0);
		pVector.push_back(arrived_patient_msg->data);
		if (X_ray_room > 0 || CT_room > 0 || Clinic_room > 0)
		{
			_mState = SEND;
		}
	}
	if (msg.GetPort().compare(from_X_ray.c_str()) == 0)
	{
		X_ray_room++;
		// 해당 xray룸 id를 받아 true로 전환
	}
	else if (msg.GetPort().compare(from_CT.c_str()) == 0)
	{
		CT_room++;
		// 해당 ct룸 id를 받아 true로 전환
	}
	else if (msg.GetPort().compare(from_Clinic.c_str()) == 0)
	{
		Clinic_room++;
		// 해당 clinic룸 id를 받아 true로 전환
	}

	return true;
}

bool HH_General_Manage::IntTransFn()
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

bool HH_General_Manage::OutputFn(CDEVSimMessage &msg)
{
	if (_mState == SEND)
	{
		CInfo* temp = new CInfo(pVector.front());

		if (temp->data.X_ray == false && X_ray_room > 0)
		{
			//Xray로 보내기
		}
		else if (temp->data.Clinic == false && Clinic_room > 0)
		{
			//Clinic으로 보내기
		}
		else if (temp->data.CT == false && CT_room > 0)
		{
			//CT로 보내기
		}
		else if (check_patient(temp->data) == true)
		{
			if (temp->data.severity == 6) // 경미한 환자의 경우
			{
				msg.SetPortValue(to_no_surgery.c_str(), temp);
			}
			else
			{
				//Surgery로 보내기
				msg.SetPortValue(to_manage_surgery.c_str(), temp);
			}
		}
	}
	else if (_mState == IDLE)
	{
		return true;
	}

	return true;
}

TimeType HH_General_Manage::TimeAdvanceFn()
{
	if (_mState == IDLE)
	{
		return INFINITY;
	}
	else if (_mState == SEND)
	{
		return 0;
	}
}

bool HH_General_Manage::check_patient(sPatient_info Patient)
{
	if (Patient.CT == true)
	{
		if (Patient.Clinic == true)
		{
			if (Patient.X_ray == true)
			{
				return true;
			}
		}
	}
	return false;
}
