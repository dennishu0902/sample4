#include "Group.hpp"
#include <cstdlib>
#include <cassert>

int  Group::AddVolunteer(const Volunteer &vol)
{
   myList_.push_back(vol);
   return 1;
}
double  Group::GetAvgBuildingExp() const
{
  double avgexp=0.0,totalexp=0.0;
  int cnt=0;
  if(myList_.empty()) return avgexp;
  for(auto vol:myList_)
     {
        totalexp += vol.GetBuildingExperience();
        cnt    += 1;
     }
  return totalexp/cnt;
}
double  Group::GetAvgStamina() const
{
  double avgsta=0.0,totalsta=0.0;
  int cnt=0;
  if(myList_.empty()) return avgsta;
  for(auto vol:myList_)
     {
        avgsta += vol.GetPhysicalStamina();
        cnt    += 1;
     }
  return totalsta/cnt;
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

