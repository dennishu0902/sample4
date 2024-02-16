#include "Group.hpp"
#include <cstdlib>
#include <cassert>

int  Group::AddVolunteer(const Volunteer &vol)
{
   myList_.push_back(vol);
   return 1;
}
int  Group::GetAvgBuildingExp() const
{
  int avgexp=0,cnt=0;
  for(auto vol:myList_)
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
  for(auto vol:myList_)
     {
        avgstamina += vol.GetPhysicalStamina();
        cnt    += 1;
     }
  if(cnt != 0)  avgstamina = avgstamina/cnt;
  else  avgstamina = 0;
  return avgstamina;
}
int Group::GetReturningMembers()
{
   int i=0;
   for(auto vol:myList_)
      if(vol.isReturning()) i++;
   return  i;
}
Volunteer&  Group::GetRandomVolunteer()
{
  int i,size;
  i = rand();
  size = myList_.size();
  assert(size>0);
  i = i % size;
  return myList_[i];
}

