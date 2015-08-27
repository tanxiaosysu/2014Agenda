#include <iostream>
#include "AgendaService.h"
#include <iomanip>
using std::cin;
using std::cout;
using std::string;
using std::setw;
void printuser(std::list<User> in) {
    std::list<User>::iterator i;
    cout << setw(20) << "name" << setw(20) << "email" << setw(20) << "phone\n";
    for (i = in.begin(); i != in.end(); i++)
        cout << setw(20) << i->getName() << setw(20) << i->getEmail()
             << setw(20) << i->getPhone() << "\n";
}
void printmeet(std::list<Meeting> in) {
    std::list<Meeting>::iterator i;
    cout << setw(20) << "Sponsor" << setw(20) << "Participator" << setw(20)
    << "Start" << setw(20) << "End" << setw(20) <<"Title\n";
    for (i = in.begin(); i != in.end(); i++)
        cout << setw(20) << i->getSponsor() << setw(20)
             << i->getParticipator() << setw(20)
             << Date::dateToString(i->getStartDate()) << setw(20)
             << Date::dateToString(i->getEndDate()) << setw(20)
             << i->getTitle() << "\n";
}
string randstr() {
    string out;
    int i = rand() % 14 + 1;
    for (int j = 0; j < i; j++) out += (rand() % 94 + 32);
    return out;
}
string randdate() {
    string o1;
    int tmp, temp;
    int month[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    o1 += (rand() % 9 + 1) + '0';
    for (int i = 0; i < 3; i++) o1 += (rand() % 10) + '0';
    o1 += '-';
    tmp = rand() % 12 + 1;
    temp = tmp - 1;
    o1 += tmp / 10 + '0';
    o1 += tmp % 10 + '0';
    o1 += '-';
    tmp = rand() % month[temp] + 1;
    o1 += tmp / 10 + '0';
    o1 += tmp % 10 + '0';
    o1 += '/';
    tmp = rand() % 24;
    o1 += tmp / 10 + '0';
    o1 += tmp % 10 + '0';
    o1 += ':';
    tmp = rand() % 59;
    o1 += tmp / 10 + '0';
    o1 += tmp % 10 + '0';
    return o1;
}
int main() {
    char agenda[] = { "agenda.data" };
    AgendaService as;
    as.startAgenda();
    int t;
    cin >> t;
    while (t--) {
        string n = randstr(), p = randstr(), e = randstr(), ph = randstr();
        cout << as.userRegister(n, p, e, ph);
        /*//mod 1
        cout << "exist:\n";
        printuser(as.listAllUsers());
        // test create user
        // mod 2
        cout << "deleted:\n";
        as.deleteUser(n, p);
        printuser(as.listAllUsers());
        // test delete user*/
        // mod 3
        string n1 = randstr(), p1 = randstr(), e1 = randstr(), ph1 = randstr();
        string n2 = randstr(), p2 = randstr(), e2 = randstr(), ph2 = randstr();
        string st1 = randdate(), en1 = randdate(), ti = randstr();
        while (Date::stringToDate(st1) > Date::stringToDate(en1)) {
            st1 = randdate();
            en1 = randdate();
        }
        cout << as.userRegister(n, p, e, ph);
        bool flag;
        //as.userRegister(n1, p1, e1, ph1);
        cout << "name1   :  " << n << "\nname2   :   " << n1 << "\n";
        cout << "exist:\n";
        printuser(as.listAllUsers());
        /*cout << "fault create meeting:\n";
        flag = as.createMeeting(n, ti, n2, st1, en1);
        cout << ((flag) ? "success!\\n" : "fail!\n");*/
        /*cout << "true create meeting:\n";
        flag = as.createMeeting(n, ti, n1, st1, en1);
        cout << ((flag) ? "success!\n" : "fail!\n");*/
        // test create meeting
    }
    as.quitAgenda();
    return 0;
}

