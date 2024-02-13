#include <fstream>
#include "Volunteer.hpp"
#include "Group.hpp"
using namespace std;
#define GROUPSIZE 5
#define GOOD_EXP  5
#define GOOD_STM  5


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

int main()
{   

    Volunteer  *pVol;
    std::vector<Volunteer> vols;
    std::vector<Volunteer> vols_r;
    std::string sname;
    int i,j;
    int build_experience;
    int physical_stamina;
    bool returning;
    int totalpeople=0;
    int total_build_experience=0;
    int total_physical_stamina=0;
    int total_returning=0;

    Group *pGrp1=NULL;
    std::vector<Group> grps;
    std::vector<Group> grps_w;
 
    std::fstream fs;
    char title[256];
    string s1;
    std::vector<string> s_volin;
    int  cnt;
    int  maxgrps;

    fs.open ("small.txt", std::fstream::in );
    do
    {
    fs.getline(title,256);   
    cout << title << std::endl;
    s1 = title;
    cnt = s1.size();
    cout << "cnt" << cnt << std::endl;
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
        pVol = new Volunteer(sname,build_experience,physical_stamina,returning);
        
        if(returning) 
        {
            vols_r.push_back(*pVol); 
            total_returning++;
        }
        else
            vols.push_back(*pVol);
        totalpeople++;
        }
    }while(cnt); 
    //Assign returning 
    if((totalpeople/GROUPSIZE) >= total_returning)
       maxgrps = total_returning;
    else 
       {
        maxgrps = totalpeople/GROUPSIZE;   
        //move some returning to general
        for(i=maxgrps; i<total_returning; i++)
           {
            vols.push_back(vols_r.back());
            vols_r.pop_back();
           }
       }
    for(i=0;i<maxgrps;i++)
    {
        pGrp1 = new Group();
        pGrp1->AddVolunteer(vols_r.back());
        vols_r.pop_back();
        for(j=0; j< GROUPSIZE -1; j++)
          {
            pGrp1->AddVolunteer(vols.back());
            vols.pop_back();
          } 
       // cout << *pGrp1;   
        grps.push_back(*pGrp1);   
    }
    for(auto iter=grps.begin();iter != grps.end();iter++)
    {
        if(((*iter).GetAvgBuildingExp() == GOOD_EXP) && ((*iter).GetAvgStamina() == GOOD_STM))
        {
            grps_w.push_back(*iter);
            cout << "Good One";
            cout << *iter;
            //grps.remove(*iter);   
        }
    } 


  //  while(i< MAXITERATION)
  // {
 //

   // }
 
   // cout << G1;
  //  cout<<G1.GetRandomVolunteer()->GetName()<<std::endl;
  //  swap(*G1.GetRandomVolunteer(),Vol6);
   //  cout << G2;
  //  cout<<G1.GetRandomVolunteer()->GetName()<<std::endl;
   // cout<<G1.GetRandomVolunteer()->GetName()<<std::endl;
}
