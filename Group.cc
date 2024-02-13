#include "Group.hpp"
int  Group::AddVolunteer(const Volunteer &vol)
{
   myList.push_back(vol);
}
int  Group::GetAvgBuildingExp() const
{
  int avgexp=0,cnt=0;
  for(auto vol:myList)
     {
        avgexp += vol.GetBuildingExperience();
        cnt    += 1;
     }
  if(cnt != 0)  avgexp = avgexp/cnt;
  else  avgexp = 0;
  return avgexp;
}
int  Group::GetAvgStamina() const
{
  int avgstamina=0,cnt=0;
  for(auto vol:myList)
     {
        avgstamina += vol.GetPhysicalStamina();
        cnt    += 1;
     }
  if(cnt != 0)  avgstamina = avgstamina/cnt;
  else  avgstamina = 0;
  return avgstamina;
}
std::vector<Volunteer>  Group::GetReturningMembors()
{
   std::vector<Volunteer> returning;
   for(auto vol:myList)
      if(vol.isReturning() == true) returning.push_back(vol);
   return  returning;
}
Volunteer  Group::GetRandomVolunteer()
{

}

