#ifndef GROUP_H
#define GROUP_H
#include "Volunteer.hpp"
#include <list>
#include <vector>
#include <string>
#include <iostream>

class Group
{
   std::list<Volunteer> myList;
public:
   int AddVolunteer(const Volunteer &vol);
   int GetAvgBuildingExp() const;
   int GetAvgStamina() const;
   std::vector<Volunteer> GetReturningMembors();
   Volunteer GetRandomVolunteer();
   friend ostream& operator<<(std::ostream &os,  const Group &g_in)
   {
      os << "Group:" << std::endl; 
      for(auto g1:g_in.myList)
      {
         os << g1.GetName()<< std::endl;
      }
      os << "AvgBuildingExp";
      os << g_in.GetAvgBuildingExp();
      os <<  std::endl; 
      os << "GetAvgStamina" ;
      os << g_in.GetAvgStamina();
   };
};
#endif