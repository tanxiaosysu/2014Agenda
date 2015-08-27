#include "AgendaUI.h"
#include <iomanip>
#include <stdlib.h>
using std::setw;
using std::left;
using std::cin;
using std::cout;
using std::endl;
using std::string;
void printstart() {
    cout << "\n";
    for (int i = 0; i < 36; i++) cout << "-";
    cout << " Agenda ";
    for (int i = 0; i < 36; i++) cout << "-";
    cout << "\n\nAction :\n"
         << "l   - log in Agenda by user name and password\n"
         << "r   - register an Agenda account\n"
         << "q   - quit Agenda\n";
    for (int i = 0; i < 80; i++) cout << "-";
    cout << "\n\nAgenda : ~$ ";
}
void printlogin(const string & userName) {
    cout << "\n";
    for (int i = 0; i < 36; i++) cout << "-";
    cout << " Agenda ";
    for (int i = 0; i < 36; i++) cout << "-";
    cout << "\n\nAction :\n"
         << "o   - log out Agenda\n"
         << "dc  - delete Agenda account\n"
         << "cp  - change password\n"
         << "spi - set personal information\n"
         << "lu  - list all Agenda user\n"
         << "cm  - create a meeting\n"
         << "la  - list all meetings\n"
         << "las - list all sponsor meetings\n"
         << "lap - list all participate meetings\n"
         << "qm  - query meeting by title\n"
         << "qt  - query meeting by time interval\n"
         << "dm  - delete meeting by title\n"
         << "da  - delete all meetings\n";
    for (int i = 0; i < 80; i++) cout << "-";
    cout << "\n\nAgenda@" << userName << " : # ";
}
AgendaUI::AgendaUI() {
    userName_ = "";
    userPassword_ = "";
}
void AgendaUI::OperationLoop(void) {
    startAgenda();
    system("clear");
    while (1) {
        printstart();
        string in = getOperation();
        system("clear");
        if (!executeOperation(in)) break;
    }
    quitAgenda();
}
void AgendaUI::startAgenda(void) {
    agendaService_.startAgenda();
}
string AgendaUI::getOperation() {
    string op;
    cin >> op;
    return op;
}
bool AgendaUI::executeLogOperation(string op) {
    if (op == "o")
        return 0;
    else if (op == "dc") {
        deleteUser();
        return 0;
    } else if (op == "cp") {
        changePassword();
    } else if (op == "spi") {
        setPersonalInformation();
    } else if (op == "lu") {
        listAllUsers();
    } else if (op == "cm") {
        createMeeting();
    } else if (op == "la") {
        listAllMeetings();
    } else if (op == "las") {
        listAllSponsorMeetings();
    } else if (op == "lap") {
        listAllParticipateMeetings();
    } else if (op == "qm") {
        queryMeetingByTitle();
    } else if (op == "qt") {
        queryMeetingByTimeInterval();
    } else if (op == "dm") {
        deleteMeetingByTitle();
    } else if (op == "da") {
        deleteAllMeetings();
    } else {
        system("clear");
        cout << "\n[error]   valid input!\n";
    }
    return 1;
}
bool AgendaUI::executeOperation(string op) {
    if (op == "q") {
        return 0;
    } else if (op == "r") {
        userRegister();
    } else if (op == "l") {
        userLogIn();
    } else {
        system("clear");
        cout << "\n[error]   valid input!\n";
    }
    return 1;
}
void AgendaUI::userLogIn(void) {
    cout << "\n[log in]   [user name]  [password]\n"
         << "[log in]   ";
    string username, password;
    cin >> username >> password;
    bool tmp = agendaService_.userLogIn(username, password);
    system("clear");
    cout << (tmp ? "\n[log in]   succeed!\n" : "\n[error]   log in fail!\n");
    if (tmp) {
        userName_ = username;
        userPassword_ = password;
        while (1) {
            printlogin(userName_);
            string in = getOperation();
            if (!executeLogOperation(in)) {
                userLogOut();
                break;
            }
        }
    }
}
void AgendaUI::userRegister(void) {
    cout << "\n[WARNING]   your input can not include '\"' or ':'"
         << "\n[register]   [user name]  [password]  [password again]  "
         << "[email]  [phone]\n"
         << "[register]   ";
    string name, password = "1", email, phone, passwordagain = "2";
    while (1) {
        cin >> name >> password >> passwordagain >> email >> phone;
        system("clear");
        if (password != passwordagain) {
            cout << "\n[register]   input again!\n"
                 << "\n[WARNING]   your input can not include '\"' or ':'"
                 << "\n[register]   [user name]  [password]  [password again]  "
                 << "[email]  [phone]\n[register]   ";
        } else
            break;
    }
    bool tmp = agendaService_.userRegister(name, password, email, phone);
    cout << (tmp ? "\n[register]   succeed!\n" : "\n[register]   fail\n");
}
void AgendaUI::quitAgenda(void) {
    agendaService_.quitAgenda();
}
void AgendaUI::userLogOut(void) {
    system("clear");
    cout << "\n[log out]   succeed!\n";
    userName_.clear();
    userPassword_.clear();
}
void AgendaUI::deleteUser(void) {
    system("clear");
    cout << "\n[WARNING]   please input your password again"
         << "\n[delete user]   [password]\n[delete user]   ";
    string password;
    cin >> password;
    bool tmp = agendaService_.deleteUser(userName_, password);
    system("clear");
    cout << (tmp ? "\n[delete agenda account]   succeed!\n" :
             "\n[error]  delete fail!\n");
}
void AgendaUI::changePassword() {
    system("clear");
    cout << "\n[change password]   please input your new password, "
         << "email and phone number"
         << "\n[change password]   [new password]  [email]  [phone]"
         << "\n[change password]   ";
    string password, email, phone;
    cin >> password >> email >> phone;
    bool tmp = agendaService_.changePassword(userName_, password, email, phone);
    system("clear");
    cout << (tmp ? "\n[change password]   succeed!\n" :
             "\n[error]  change password fail!\n");
}
void AgendaUI::setPersonalInformation() {
    system("clear");
    cout << "\n[set information]   please input your email and phone number"
         << "\n[set information]   [email]  [phone]"
         << "\n[set information]   ";
    string email, phone;
    cin >> email >> phone;
    bool tmp = agendaService_.userSetInformation(userName_, email, phone);
    system("clear");
    cout << (tmp ? "\n[set information]   succeed!\n" :
             "\n[error]  set information fail!\n");
}
void AgendaUI::listAllUsers(void) {
    system("clear");
    cout << "\n[list all users]\n";
    std::list<User> out = agendaService_.listAllUsers();
    printUsers(out);
}
void AgendaUI::createMeeting(void) {
    system("clear");
    cout << "\n[create meeting]   [title]  [participator]  "
         << "[start time(yyyy-mm-dd/hh:mm)]  [end time(yyyy-mm-dd/hh:mm)]\n"
         << "[create meeting]   ";
    string title, ptc, start, end;
    cin >> title >> ptc >> start >> end;
    bool t = agendaService_.createMeeting(userName_, title, ptc, start, end);
    system("clear");
    cout << (t ? "\n[create meeting]   succeed!\n" :
            "\n[error]   create meeting fail!\n");
}
void AgendaUI::listAllMeetings(void) {
    system("clear");
    cout << "\n[list all meetings]\n";
    std::list<Meeting> out = agendaService_.listAllMeetings(userName_);
    printMeetings(out);
}
void AgendaUI::listAllSponsorMeetings(void) {
    system("clear");
    cout << "\n[list all sponsor meetings]\n";
    std::list<Meeting> out = agendaService_.listAllSponsorMeetings(userName_);
    printMeetings(out);
}
void AgendaUI::listAllParticipateMeetings(void) {
    system("clear");
    cout << "\n[list all participate meetings]\n";
    std::list<Meeting> o = agendaService_.listAllParticipateMeetings(userName_);
    printMeetings(o);
}
void AgendaUI::queryMeetingByTitle(void) {
    system("clear");
    cout << "\n[query meetings]   [title]\n[query meetings]   ";
    string title;
    cin >> title;
    std::list<Meeting> out = agendaService_.meetingQuery(userName_, title);
    printMeetings(out);
}
void AgendaUI::queryMeetingByTimeInterval(void) {
    system("clear");
    cout << "\n[query meetings]   [start time(yyyy-mm-dd/hh:mm)]  "
         << "[end time(yyyy-mm-dd/hh:mm)]\n[query meetings]   ";
    string st, end;
    cin >> st >> end;
    std::list<Meeting> out = agendaService_.meetingQuery(userName_, st, end);
    printMeetings(out);
}
void AgendaUI::deleteMeetingByTitle(void) {
    system("clear");
    cout << "\n[delete meetings]   [title]\n[delete meetings]   ";
    string title;
    cin >> title;
    bool out = agendaService_.deleteMeeting(userName_, title);
    system("clear");
    cout << (out ? "\n[delete meeting by title]   succeed!\n" :
            "\n[error]   delete meeting fail!\n");
}
void AgendaUI::deleteAllMeetings(void) {
    bool out = agendaService_.deleteAllMeetings(userName_);
    system("clear");
    cout << (out ? "\n[delete all meetings]   succeed!\n" :
            "\n[error]   delete meeting fail!\n");
}
void AgendaUI::printUsers(std::list<User> in) {
    std::list<User>::iterator i;
    int max = 0;
    for (i = in.begin(); i != in.end(); i++) {
        if (i->getName().size() > max) max = i->getName().size();
        if (i->getEmail().size() > max) max = i->getEmail().size();
        if (i->getPhone().size() > max) max = i->getPhone().size();
    }
    if (max < 6) max = 6;
    cout << "\n" << left;
    cout << setw(max + 1) << "name" << setw(max + 1) << "email"
         << setw(max + 1) << "phone" << "\n\n";
    for (i = in.begin(); i != in.end(); i++)
        cout << setw(max + 1) << i->getName()
             << setw(max + 1) << i->getEmail()
             << setw(max + 1) << i->getPhone() << "\n";
}
void AgendaUI::printMeetings(std::list<Meeting> in) {
    std::list<Meeting>::iterator i;
    int max = 0;
    for (i = in.begin(); i != in.end(); i++) {
        if (i->getTitle().size() > max) max = i->getTitle().size();
        if (i->getSponsor().size() > max) max = i->getSponsor().size();
        if (i->getParticipator().size() > max)
            max = i->getParticipator().size();
    }
    if (max < 16) max = 16;
    cout << "\n" << left;
    cout << setw(max + 1) <<"Title" << setw(max + 1) << "Sponsor"
         << setw(max + 1) << "Participator" << setw(max + 1) << "Start"
         << setw(max + 1) << "End" << "\n\n";
    for (i = in.begin(); i != in.end(); i++)
        cout << setw(max + 1) << i->getTitle()
             << setw(max + 1) << i->getSponsor()
             << setw(max + 1) << i->getParticipator()
             << setw(max + 1) << Date::dateToString(i->getStartDate())
             << setw(max + 1) << Date::dateToString(i->getEndDate()) << "\n";
}

