#include "Volunteer.hpp"
#include "Group.hpp"
using namespace std;
int main()
{
    Volunteer  Vol1("Lee", 3, 5, false);
    Volunteer  Vol2("Wang", 9, 8, true);
    Volunteer  Vol3("Zhang", 2, 10, false);
    Volunteer  Vol4("Sun", 7, 8, true);
    Volunteer  Vol5("Liu", 6, 7, false);
    Volunteer  Vol6("Xu", 5, 8, true);
    Group G1;
    G1.AddVolunteer(Vol1);
    G1.AddVolunteer(Vol2);
    G1.AddVolunteer(Vol3);
    G1.AddVolunteer(Vol4);
    G1.AddVolunteer(Vol5);
    G1.AddVolunteer(Vol6);
    cout << G1;
}
