#include "HH_Patience_Coupled.h"
#include "HH_Patience_Manage.h"
#include "X_ray.h"
#include "CT_room.h"
#include "Clinic.h"
#include <vector>

std::string HH_Patience_Coupled::from_receive = "from_receive";
std::string HH_Patience_Coupled::from_Manager_to_Surgery = "from_Manager_to_Surgery";


HH_Patience_Coupled::HH_Patience_Coupled(int _id, int _X_ray, int _ct, int _clinic)
{
	SetName("HH_Patience_Coupled");

	X_ray_room = _X_ray;
	_CT_room = _ct;
	Clinic_room = _clinic;

	HH_Patience_Manage* manager = new HH_Patience_Manage(X_ray_room, _CT_room, Clinic_room, _id);
	AddInPorts(1, from_receive.c_str());
	AddOutPorts(1, from_Manager_to_Surgery.c_str());

	AddComponent(1, manager);
	AddCoupling(this, this->from_receive.c_str(), manager, HH_Patience_Manage::from_receive.c_str());
	AddCoupling(manager, HH_Patience_Manage::to_manage_surgery.c_str(), this, this->from_Manager_to_Surgery.c_str());

	std::vector<CModel*> X_ray_list;
	for (int i = 0; i < X_ray_room; i++)
	{
		CModel *temp = new X_ray(i);
		AddComponent(1, temp);
		AddCoupling(manager, HH_Patience_Manage::to_X_ray.c_str(), temp, X_ray::from_Manager.c_str());
		AddCoupling(temp, X_ray::to_Manager.c_str(), manager, HH_Patience_Manage::from_X_ray.c_str());
		X_ray_list.push_back(temp);

		
	}

	std::vector<CModel*> Clinic_list;
	for (int i = 0; i < Clinic_room; i++)
	{
		CModel *temp = new Clinic(i);
		AddComponent(1, temp);
		AddCoupling(manager, HH_Patience_Manage::to_Clinic.c_str(), temp, Clinic::from_Manager.c_str());
		AddCoupling(temp, Clinic::to_Manager.c_str(), manager, HH_Patience_Manage::from_Clinic.c_str());
		Clinic_list.push_back(temp);

		
	}

	std::vector<CModel*> CT_list;
	for (int i = 0; i < _CT_room; i++)
	{
		CModel* temp = new CT_room(i);
		AddComponent(1, temp);
		AddCoupling(manager, HH_Patience_Manage::to_CT.c_str(), temp, CT_room::from_Manager.c_str());
		AddCoupling(temp, CT_room::to_Manager.c_str(), manager, HH_Patience_Manage::from_CT.c_str());
		CT_list.push_back(temp);

	}


}


HH_Patience_Coupled::~HH_Patience_Coupled()
{
}