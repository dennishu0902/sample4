#include <fstream>
#include <ctime>
#include <cstdlib>
#include "Volunteer.hpp"
#include "Group.hpp"
using namespace std;
#define GROUPSIZE 5
#define GOOD_EXP  5
#define GOOD_STM  5
#define MAXITERATION 50

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

int main(int argc, char *argv[])
{   
    Volunteer  *pVol, *pVol1, *pVol2;
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

    Group *pGrp1=NULL;
    std::vector<Group> grps;
    std::vector<Group> grps_w;
 
    std::fstream fs,fsout;
    char title[256];
    string s1;
    std::vector<string> s_volin;
    int  cnt;
    int  maxgrps;

    if(argc < 3) 
    {
        std::cout << "3 parameters"<<std::endl;
        return -1;
    } 
    srand(time(NULL));
    fs.open (argv[1], std::fstream::in );
    
    do
    {
    fs.getline(title,256);   
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
    //Assign returning, make sure at least one returning in group 
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
        grps.push_back(*pGrp1);   
    }
    for(auto iter=grps.begin();iter != grps.end();)
    {
        if(((*iter).GetAvgBuildingExp() == GOOD_EXP) && ((*iter).GetAvgStamina() == GOOD_STM))
        {   //satisfied, move to grp_w
            grps_w.push_back(*iter);
            grps.erase(iter);   
        }
        else
            iter++;
    } 

    cnt=0;
    for(auto iter=grps.begin();iter != grps.end();iter++)
    {
        if(((*iter).GetAvgBuildingExp() >= GOOD_EXP) && ((*iter).GetAvgStamina() >= GOOD_STM))
        {   //satisfied, move to grp_w
            cnt++;
        }
    } 
    cout << "initial" << cnt + grps_w.size();
    cout << std::endl;
    i = 0;
    j=k=h=l=0;
    std::vector<Group>::iterator G1,G2,G3,G4;
    while(i< MAXITERATION)
    {
       //find Group pair
       for(auto iter=grps.begin();iter != grps.end();iter++)
        {
         if(((*iter).GetAvgBuildingExp() >= GOOD_EXP) && ((*iter).GetAvgStamina() >= GOOD_STM)) 
              { G1 = iter; j=1;}      
         else if(((*iter).GetAvgBuildingExp() <= GOOD_EXP) && ((*iter).GetAvgStamina() <= GOOD_STM)) 
              { G2 = iter; k=1;}   
         else if(((*iter).GetAvgBuildingExp() >= GOOD_EXP) && ((*iter).GetAvgStamina() <= GOOD_STM)) 
              { G3 = iter; h=1;}  
         else if(((*iter).GetAvgBuildingExp() <= GOOD_EXP) && ((*iter).GetAvgStamina() >= GOOD_STM)) 
              { G4 = iter; l=1;}     
         if((j==1) && (k==1))
         { //matching
           cnt = 0;
           do
           {
            pVol1 = G1->GetRandomVolunteer();
            pVol2 = G2->GetRandomVolunteer();
            if(pVol1->isReturning() && pVol2->isReturning() )
            {
                swap(*pVol1,*pVol2);

            }
            else if((!pVol1->isReturning()) && (!pVol2->isReturning()) )
            {
                swap(*pVol1,*pVol2);
            }
            /* code */
           } while (cnt++<GROUPSIZE);
           j=0;
           k=0;
         }
        if((h==1) && (l==1))
         { //matching
           cnt = 0;
           do
           {
            pVol1 = G3->GetRandomVolunteer();
            pVol2 = G4->GetRandomVolunteer();
            if(pVol1->isReturning() && pVol2->isReturning() )
            {
                swap(*pVol1,*pVol2);
            }
            else if((!pVol1->isReturning()) && (!pVol2->isReturning()) )
            {
                swap(*pVol1,*pVol2);
            }
           } while (cnt++<GROUPSIZE);
           h=0;
           l=0;
         }
        }
       i++;  

    }
   
   for(auto iter=grps.begin();iter != grps.end();)
    {
        if(((*iter).GetAvgBuildingExp() >= GOOD_EXP) && ((*iter).GetAvgStamina() >= GOOD_STM))
        {   //satisfied, move to grp_w
            grps_w.push_back(*iter);
            grps.erase(iter);
        }
        else
          iter++;
    } 
  
  if(grps_w.size())
  {
     fsout.open(argv[3], std::fstream::out );
    for(auto iter=grps_w.begin();iter != grps_w.end(); iter++)
     {
            fsout << *iter;
     }
    
     cout << "finally" << grps_w.size()<<std::endl;
    /*   
    if(grps.size())
    {
     fsout << "lost"<<std::endl;
     for(auto iter=grps.begin();iter != grps.end(); iter++)
     {
            fsout << *iter;
     }
    } */
     fsout.close();
  } 
   fs.close();
   return 0;  
}
