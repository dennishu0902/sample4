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
#define MAXITERATION 500000

std::vector<string>  split(string strin)   // whitespace
{
    std::vector<string>  words;
    std::string str1;
    std::string sname;
    int build_experience;
    int physical_stamina;
    bool returning;
    int i=0;
    while( i < strin.size())
     {
       if(strin[i] != ' ') 
           {
             str1.push_back(strin[i]);
             i++;
           }
       else
         { 
            i++; 
            if(str1.empty()==true) continue;//white space at first
            words.push_back(str1);
            str1.clear();
        }
     }
     //the end word, no white space
     if(str1.empty() !=true) words.push_back(str1);
     return words; 
}
bool CheckifAllfine(std::vector<Group> grps)
{
bool allfine = true;
 for(auto iter:grps)
    {
        if((iter.GetAvgBuildingExp() < GOOD_EXP) || (iter.GetAvgStamina() < GOOD_STM)||(iter.GetReturningMembers() < 1))
        {   //satisfied, move to grp_w
            allfine = false;
            break;
        }
    }
return allfine;    
}
void GetOptGroup(std::vector<Group> &grps)
{

  int i=0;
  while(i< MAXITERATION)
    {
       //find Group pair
        int index1  =rand()% grps.size();
        int index2  =rand()% grps.size();
        while(index1 == index2) index2  =rand()% grps.size();

        Volunteer& Vol1 = grps[index1].GetRandomVolunteer();
        Volunteer& Vol2 = grps[index2].GetRandomVolunteer();
        swap(Vol1, Vol2);
        i++;
        //check 
        if(CheckifAllfine(grps)) { cout<<"BREAK" <<i ;break;}
     }
}
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
#define MAX_LINE 120
int main(int argc, char *argv[])
{   
    
    std::vector<Volunteer> vols;
    std::vector<Volunteer> vols_r;
    std::string sname;
    int i,j,k,h,l;
    int build_experience;
    int physical_stamina;
    bool returning;
    int totalpeople=0;
    int total_build_experience=0;
    int total_physical_stamina=0;
    int total_returning=0;

    std::vector<Group> grps;
    std::vector<Group> grps_w;
 
    std::fstream fs,fsout;
    char title[MAX_LINE];
    string s1;
    std::vector<string> s_volin;
    int  cnt;
   
    if(argc < 3) 
    {
        std::cout << "3 parameters"<<std::endl;
        return -1;
    } 
    srand(time(NULL));
    fs.open (argv[1], std::fstream::in );
    do
    {
    fs.getline(title,MAX_LINE);   
    s1 = title;
    cnt = s1.size();
    if(cnt!=0)
        {
        s_volin = split(s1);
        sname = s_volin[0];
        build_experience = stoi(s_volin[1]);
        physical_stamina = stoi(s_volin[2]);
        if(stoi(s_volin[3]))
            returning = true;
        else
            returning = false;    
        Volunteer Vol=Volunteer(sname,build_experience,physical_stamina,returning);
        vols.push_back(Vol);
        totalpeople++;
        }
    }while(cnt); 
    //Assign returning, make sure at least one returning in group 
   for(i=0;i< totalpeople/GROUPSIZE;i++)
    {
        Group Grp1;
        for(j=0; j< GROUPSIZE; j++)
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
   fs.close();
   return 0;  
}
