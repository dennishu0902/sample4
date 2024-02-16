#include "Volunteer.hpp"
const unsigned int kMinAllowed=2;
Volunteer::Volunteer(const std::string &name, double build_experience, double physical_stamina, bool returning)
{
    vname_ = name;
    if(build_experience < MIN_ALLOWED) build_experience = MIN_ALLOWED;
    if(build_experience > MAX_ALLOWED) build_experience = MAX_ALLOWED;
    if(physical_stamina < MIN_ALLOWED) physical_stamina = MIN_ALLOWED;
    if(physical_stamina > MAX_ALLOWED) physical_stamina = MAX_ALLOWED;
    BuildingExperience_ = build_experience;
    PhysicalStamina_ = physical_stamina;
    isReturning_ = returning;
}

std::string Volunteer::GetName()
{
   return vname_;
}
double Volunteer::GetBuildingExperience()
{
    return BuildingExperience_;
}
double Volunteer::GetPhysicalStamina()
{
    return PhysicalStamina_;
}
bool Volunteer::isReturning()
{
    return  isReturning_;
}
