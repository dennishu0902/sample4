#include "Volunteer.hpp"
Volunteer::Volunteer(const std::string &name, int build_experience, int physical_stamina, bool returning)
{
    vname = name;
    if(build_experience < MIN_ALLOWED) build_experience = MIN_ALLOWED;
    if(build_experience > MAX_ALLOWED) build_experience = MAX_ALLOWED;
    if(physical_stamina < MIN_ALLOWED) physical_stamina = MIN_ALLOWED;
    if(physical_stamina > MAX_ALLOWED) physical_stamina = MAX_ALLOWED;
    m_BuildingExperience = build_experience;
    m_PhysicalStamina = physical_stamina;
    m_isReturning = returning;
}

std::string Volunteer::GetName()
{
   return vname;
}
int Volunteer::GetBuildingExperience()
{
    return m_BuildingExperience;
}
int Volunteer::GetPhysicalStamina()
{
    return m_PhysicalStamina;
}
bool Volunteer::isReturning()
{
    return  m_isReturning;
}
