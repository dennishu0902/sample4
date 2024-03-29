#ifndef GROUP_H
#define GROUP_H
#include "Volunteer.hpp"
#include <vector>
#include <string>
#include <iostream>

class Group
{
   std::vector<Volunteer> myList_;
public:
   int AddVolunteer(const Volunteer &vol);
   double GetAvgBuildingExp() const;
   double GetAvgStamina() const;
   int GetReturningMembers();
   Volunteer& GetRandomVolunteer();
   friend ostream& operator<<(std::ostream &os,  const Group &g_in)
   {
      os << "Group:" ;
      os << " AvgBuildingExp  ";
      os << g_in.GetAvgBuildingExp();
      os << " GetAvgStamina  " ;
      os << g_in.GetAvgStamina();
      os << std::endl; 
      for(auto g1:g_in.myList_)
      {
         os << g1.GetName()<< std::endl;
      }
      
      return os;
   };
};
#endif