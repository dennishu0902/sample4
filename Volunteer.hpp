#ifndef VOLUNTEER_H
#define VOLUNTEER_H
#define MIN_ALLOWED 1
#define MAX_ALLOWED 9
#include <string>
using namespace std;
class Volunteer
{
    std::string vname_;
    double  BuildingExperience_;
    double  PhysicalStamina_;
    bool isReturning_;
public:
    Volunteer(const std::string &name, double build_experience, double physical_stamina, bool returning);
    std::string GetName();
    double GetBuildingExperience();
    double GetPhysicalStamina();
    bool isReturning();
};
#endif