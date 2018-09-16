#include "HH_Patience_Manage.h"
#include "GlobalVar.h"

std::string HH_Patience_Manage::from_Clinic = "from_Clinic";
std::string HH_Patience_Manage::from_X_ray = "from_X_ray";
std::string HH_Patience_Manage::from_CT = "from_CT";
std::string HH_Patience_Manage::to_manage_surgery = "to_manage_surgery";
std::string HH_Patience_Manage::to_CT = "to_CT";
std::string HH_Patience_Manage::to_Clinic = "to_Clinic";
std::string HH_Patience_Manage::to_X_ray = "to_X_ray";
std::string HH_Patience_Manage::from_receive = "from_receive";


HH_Patience_Manage::HH_Patience_Manage()
{
}

HH_Patience_Manage::HH_Patience_Manage(int x_ray, int ct, int clinic, int _id)
{
	SetName("HH_Patience_Manage");
	AddInPorts(4, from_X_ray.c_str(), from_CT.c_str(), from_Clinic.c_str(), from_receive.c_str());
	AddOutPorts(4, to_X_ray.c_str(), to_manage_surgery.c_str(), to_CT.c_str(), to_Clinic.c_str());
	_mState = IDLE;
	id = _id;
	X_ray_room = x_ray; // ������
	av_X_ray = X_ray_room; 
	CT_room = ct; // ������
	av_CT = ct;
	Clinic_room = clinic; // ������
	av_Clinic = clinic;

	available_clinic = new bool[clinic];
	for (int i = 0; i < clinic; i++)
	{
		available_clinic[i] = true;
	}
	available_ct = new bool(ct);
	for (int i = 0; i < clinic; i++)
	{
		available_ct[i] = true;
	}
	available_x_ray = new bool(x_ray);
	for (int i = 0; i < clinic; i++)
	{
		available_x_ray[i] = true;
	}

}


HH_Patience_Manage::~HH_Patience_Manage()
{
	
}

bool HH_Patience_Manage::ExtTransFn(const CDEVSimMessage &msg)
{
	if (msg.GetPort().compare(from_receive.c_str()) == 0)
	{
		CInfo* arrived_patient_msg = (CInfo*)msg.GetArg(0);
		if (arrived_patient_msg->data._Pstate == GENERAL)
		{
			GLOBAL_VARIABLE->IncreaseHHDoctorNum(id);
			GLOBAL_VARIABLE->IncreaseHHNurseNum(id);
			/*COUT << "ȯ�� " << arrived_patient_msg->data.id << " �� 1�����Ḧ ��ġ�� �����߽��ϴ�." << ENDL;*/
		}
// 		else
// 			COUT << "�糭ȯ��" << arrived_patient_msg->data.id << "�� �˻�ǿ� �����߽��ϴ�." << ENDL;

		if (arrived_patient_msg->data.X_ray == false)
		{
			if (arrived_patient_msg->data._Pstate == DISASTER)
				X_ray_P.push_front(arrived_patient_msg->data);
			else
				X_ray_P.push_back(arrived_patient_msg->data);
		}
		else if (arrived_patient_msg->data.CT == false)
		{
			if (arrived_patient_msg->data._Pstate == DISASTER)
				CT_P.push_front(arrived_patient_msg->data);
			else
				CT_P.push_back(arrived_patient_msg->data);
		}
		else if (arrived_patient_msg->data.Clinic == false)
		{
			if (arrived_patient_msg->data._Pstate == DISASTER)
				Clinic_P.push_front(arrived_patient_msg->data);
			else
				Clinic_P.push_back(arrived_patient_msg->data);
		}
		else
		{
			All_done.push_back(arrived_patient_msg->data);
		}
		_mState = SEND;
	}
	if (msg.GetPort().compare(from_X_ray.c_str()) == 0)
	{
		CInfo* arrived_patient_msg = (CInfo*)msg.GetArg(0);
		available_x_ray[arrived_patient_msg->get_hh_room()] = true;
		av_X_ray++;
		if (arrived_patient_msg->data.CT == false)
		{
			if (arrived_patient_msg->data._Pstate == DISASTER)
				CT_P.push_front(arrived_patient_msg->data);
			else
				CT_P.push_back(arrived_patient_msg->data);
		}
		else if (arrived_patient_msg->data.Clinic == false)
		{
			if (arrived_patient_msg->data._Pstate == DISASTER)
				Clinic_P.push_front(arrived_patient_msg->data);
			else
				Clinic_P.push_back(arrived_patient_msg->data);
		}
		else
		{
			All_done.push_back(arrived_patient_msg->data);
		}
			/*COUT << "ȯ��" << arrived_patient_msg->data.id << "�� X_ray �˻縦 ��ġ�� ���Խ��ϴ�." << ENDL;*/
		// �ش� xray�� id�� �޾� true�� ��ȯ
		_mState = SEND;
	}
	else if (msg.GetPort().compare(from_CT.c_str()) == 0)
	{
		CInfo* arrived_patient_msg = (CInfo*)msg.GetArg(0);
		available_ct[arrived_patient_msg->get_hh_room()] = true;
		av_CT++;
		if (arrived_patient_msg->data.Clinic == false)
		{
			if (arrived_patient_msg->data._Pstate == DISASTER)
				Clinic_P.push_front(arrived_patient_msg->data);
			else
				Clinic_P.push_back(arrived_patient_msg->data);
		}
		else
		{
			All_done.push_back(arrived_patient_msg->data);
		}
		/*COUT << "ȯ��" << arrived_patient_msg->data.id << "�� CT �˻縦 ��ġ�� ���Խ��ϴ�." << ENDL;*/
		// �ش� ct�� id�� �޾� true�� ��ȯ
		_mState = SEND;
	}
	else if (msg.GetPort().compare(from_Clinic.c_str()) == 0)
	{
		CInfo* arrived_patient_msg = (CInfo*)msg.GetArg(0);
		All_done.push_back(arrived_patient_msg->data);
		available_clinic[arrived_patient_msg->get_hh_room()] = true;
		av_Clinic++;
		/*COUT << "ȯ��" << arrived_patient_msg->data.id << "�� �ӻ󺴸��˻縦 ��ġ�� ���Խ��ϴ�." << ENDL;*/
		// �ش� clinic�� id�� �޾� true�� ��ȯ
		_mState = SEND;
	}

	return true;
}

bool HH_Patience_Manage::IntTransFn()
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

bool HH_Patience_Manage::OutputFn(CDEVSimMessage &msg)
{
	if (_mState == SEND)
	{
		if (X_ray_P.size() != 0)
		{
			sPatient_info info = X_ray_P.front();
			CInfo* XR = new CInfo(info);
			if (XR->data.X_ray == false && av_X_ray > 0)
			{
				for (int i = 0; i < X_ray_room; i++)
				{
					if (available_x_ray[i] == true)
					{
						//COUT << "ȯ�� " << XR->data.id << " �� X_Ray �˻縦 ������ ���ϴ�" << ENDL;
						XR->set_hh_room(i);
						msg.SetPortValue(to_X_ray.c_str(), XR);
						av_X_ray--;
						available_x_ray[i] = false;
						X_ray_P.erase(X_ray_P.begin());
						break;
					}
				}
				//Xray�� ������
			}
		}

		if (CT_P.size() != 0)
		{
			CInfo* CT = new CInfo(CT_P.front());
			if (CT->data.CT == false && available_ct > 0)
			{
				//CT�� ������
				for (int i = 0; i < CT_room; i++)
				{
					if (available_ct[i] == true)
					{
						//COUT << "ȯ�� " << CT->data.id << " �� CT �˻縦 ������ ���ϴ�" << ENDL;
						CT->set_hh_room(i);
						msg.SetPortValue(to_CT.c_str(), CT);
						av_CT--;
						available_ct[i] = false;
						CT_P.erase(CT_P.begin());
						break;
					}
				}
			}
		
		}

		if (Clinic_P.size() != 0)
		{
			CInfo* CI = new CInfo(Clinic_P.front());
			if (CI->data.Clinic == false && av_Clinic > 0)
			{
				//Clinic���� ������
				for (int i = 0; i < Clinic_room; i++)
				{
					if (available_clinic[i] == true)
					{
	
						//COUT << "ȯ�� " << CI->data.id << " �� �ӻ󺴸��˻縦 ������ ���ϴ�" << ENDL;
						CI->set_hh_room(i);
						msg.SetPortValue(to_Clinic.c_str(), CI);
						av_Clinic--;
						available_clinic[i] = false;
						Clinic_P.erase(Clinic_P.begin());
						break;
					}
				}
			}
		}
/*

		if (All_done.size() != 0)
		{
			msg.SetPortValue(to_manage_surgery.c_str(), new CInfo(All_done.front()));
			All_done.erase(All_done.begin());
		}*/
		if (All_done.size() > 1)
		{

			for (std::vector<sPatient_info>::iterator it = All_done.begin(); it != All_done.end(); it++)
			{
					msg.SetPortValue(to_manage_surgery.c_str(), new CInfo(*it));
			}
			All_done.clear();
		}
		else if (All_done.size() == 1)
		{
			m_PI = All_done.front();
			msg.SetPortValue(to_manage_surgery.c_str(), new CInfo(m_PI));
			All_done.erase(All_done.begin());
		}
		/*std::cout << id << " ���� " << CT_P.size() << " CT ������" << std::endl;
		std::cout << id << " ���� " << X_ray_P.size() << " X_ray ������" << std::endl;
		std::cout << id << " ���� " << Clinic_P.size() << " Clinic ������" << std::endl;
		std::cout << id << " ���� " << All_done.size() << " Alldone ������" << std::endl;*/
	}
	else if (_mState == IDLE)
	{
		return true;
	}

	
	return true;
}

TimeType HH_Patience_Manage::TimeAdvanceFn()
{
	if (_mState == IDLE)
	{
		return Infinity;
	}
	else if (_mState == SEND)
	{
		return 0;
	}
}

bool HH_Patience_Manage::check_patient(sPatient_info Patient)
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
