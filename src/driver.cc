#include <fstream>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include "Volunteer.hpp"
#include "Group.hpp"
using namespace std;
#define GROUPSIZE 5
#define GOOD_EXP  5 
#define GOOD_STM  5
#define MAXITERATION 100000
/*
  Check if all group meet requirements.
  IN: Group Vector
  OUT: true, all group meet requirements.
*/
bool CheckifAllfine(std::vector<Group> grps)
{
 bool allfine = true;
 for(auto iter:grps)
    {
        if((iter.GetAvgBuildingExp() < GOOD_EXP) || (iter.GetAvgStamina() < GOOD_STM)||(iter.GetReturningMembers() < 1))
        {   //satisfied, move to grp_w
            allfine = false;
            break;   //find one not meet, break loop
        }
    }
return allfine;    
}
/*
  Do group optimize through exchange Volunteer between random group.
  and randong Volunteer
  IN: Groups vector, using reference  "&", since we need change the input groups.
       if not use reference, will only take a groups copy to function.
  OUT: None    
  Return: None  
*/
void GetOptGroup(std::vector<Group> &grps)
{

    unsigned int i=0;
    while(i< MAXITERATION)
    {
       //find Group pair
        int index1  =rand()% grps.size();
        int index2  =rand()% grps.size();
        while(index1 == index2) index2  =rand()% grps.size();//until find a different group
        //Get Random Volunteer. since we need exchange the content of orginal Volunteer 
        //So, we define "&" here, and function GetRandomVolunteer() return is also "&"
        Volunteer& Vol1 = grps[index1].GetRandomVolunteer();
        Volunteer& Vol2 = grps[index2].GetRandomVolunteer();
        swap(Vol1, Vol2);
        i++;
        //check 
        if(CheckifAllfine(grps)) { cout<<"BREAK" <<i ;break;}//if all meet, break loop
     }
}
/*
   Get Matched Group, and save to grps_w
   IN: Group Vector 
   IN/OUT: Group Vector reference
   Return: None
*/
void GetMatchedGroup(std::vector<Group> grps, std::vector<Group> &grps_w)
{  
    #if 0
    for(auto iter=grps.begin();iter != grps.end();iter++)
    {
        if(((*iter).GetAvgBuildingExp() >= GOOD_EXP) && ((*iter).GetAvgStamina() >= GOOD_STM))
        {   //satisfied, move to grp_w
            grps_w.push_back(*iter);
        }
    } 
    #endif
    for(auto iter:grps)
    {
        if((iter.GetAvgBuildingExp() >= GOOD_EXP) && (iter.GetAvgStamina() >= GOOD_STM)&& (iter.GetReturningMembers() >= 1))
        {   //satisfied, move to grp_w
            grps_w.push_back(iter);
        }
    }

}
/*
   Read name, building_experience, stamina, and isReturning from file.
   IN: filename[]
   IN/OUT: Volunteer Vector, reference
   Return: -1, no people, other, total people
*/
int ReadfromFile(char *FileName, std::vector<Volunteer>& vols)
{
    std::fstream fs;
    int totalpeople=0,cnt;
    int build_experience;
    int physical_stamina;
    bool returning;
    std::string s1,sname;
    fs.open (FileName, std::fstream::in );//open file
    if(!fs.is_open()) return -1; //check if open file success.
    
    while(std::getline(fs, s1,' ')) //Read string, use ' 'as seperator
    {
        switch(cnt)
        {
            case 0: 
                  sname = s1; cnt++;break;
            case 1: 
                  build_experience = stoi(s1); cnt++; break;
            case 2: 
                  physical_stamina = stoi(s1); cnt++; break;
            case 3: 
                  returning = stoi(s1) ? true : false; cnt=0; 
                  Volunteer Vol=Volunteer(sname,build_experience,physical_stamina,returning);
                  vols.push_back(Vol);
                  totalpeople++;      
                  break;    //Init Volunteer and save to Vector.
        }
    }
    fs.close();
    return totalpeople;
}
int main(int argc, char *argv[])
{   
    
    std::vector<Volunteer> vols;
    std::vector<Volunteer> vols_r;
    std::vector<string>    vStr;
    
    int i;
  
    std::vector<Group> grps; 
    std::vector<Group> grps_w;
 
    std::fstream fsout;
    
    std::vector<string> s_volin;
    int  totalpeople;
   
    if(argc < 4) 
    {
        std::cout << "4 parameters"<<std::endl;
        return -1;
    } 
    srand(time(NULL));
    
    totalpeople = ReadfromFile(argv[1], vols);
    if(totalpeople == -1) return -1;
    
    std::cout << "Read file end"<<std::endl;
    //Assign returning, make sure at least one returning in group 
   for(i=0;i< totalpeople/GROUPSIZE;i++)
    {
        Group Grp1;
        for(int j=0; j< GROUPSIZE; j++)
          {
            Grp1.AddVolunteer(vols.back());
            vols.pop_back();
          } 
        grps.push_back(Grp1);   
    }

    GetOptGroup(grps);
    GetMatchedGroup(grps,grps_w);
    if(grps_w.size())
    {
      fsout.open(argv[3], std::fstream::out );
     for(auto iter=grps_w.begin();iter != grps_w.end(); iter++)
     {
            fsout << *iter;
     }
    
     cout << "finally" << grps_w.size()<<std::endl;
     fsout.close();
  } 
   
   return 0;  
}
