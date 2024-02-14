#ifndef VOLUNTEER_H
#define VOLUNTEER_H
#define MIN_ALLOWED 1
#define MAX_ALLOWED 9
#include <string>
using namespace std;
class Volunteer
{
    std::string vname;
    int  m_BuildingExperience;
    int  m_PhysicalStamina;
    bool m_isReturning;
public:
    Volunteer(const std::string &name, int build_experience, int physical_stamina, bool returning);
    std::string GetName();
    int GetBuildingExperience();
    int GetPhysicalStamina();
    bool isReturning();
};
#endif