#include "Storage.h"
#include <fstream>
#include <iostream>
using std::cout;
using std::ofstream;
using std::ifstream;
using std::string;
Storage* Storage::instance_ = 0;
Storage * Storage::getInstance(void) {
    if (!instance_) instance_ = new Storage;
    return instance_;
}
Storage::~Storage() {
    instance_ = 0;
}
string jiami(const string & Str) {
    string str = Str;
    for (int i = 0; i < str.size(); i++) {
        if (str[i] >= 48 && str[i] <= 57) str[i] = (str[i] - 43) % 10 + 48;
        if (str[i] >= 65 && str[i] <= 90) str[i] = (str[i] - 55) % 26 + 65;
        if (str[i] >= 97 && str[i] <= 122) str[i] = (str[i] - 87) % 26 + 97;
    }
    return str;
}
void jiemi(string & str) {
    for (int i = 0; i < str.size(); i++) {
        if (str[i] >= 48 && str[i] <= 57) {
            if (str[i] - 53 >= 0)
                str[i] -= 5;
            else
                str[i] += 5;
        } else if (str[i] >= 65 && str[i] <= 90) {
            if (str[i] - 75 >= 0)
                str[i] -= 10;
            else
                str[i] += 16;
        
        } else if (str[i] >= 97 && str[i] <= 122) {
            if (str[i] - 107 >= 0)
                str[i] -= 10;
            else
                str[i] += 16;
        }
    }
}
void Storage::createUser(const User & user) {
    userList_.push_back(user);
}
std::list<User> Storage::queryUser(std::function<bool(const User & u)> filter) {
    std::list<User>::iterator out;
    std::list<User> out1;
    for (out = userList_.begin(); out != userList_.end(); out++) {
        if (filter(*out)) {
            out1.push_back(*out);
        }
    }
    return out1;
}
int Storage::updateUser(std::function<bool(const User & u)> filter,
    std::function<void(User & u)> switcher) {
    int out = 0;
    std::list<User>::iterator i;
    for (i = userList_.begin(); i != userList_.end(); i++) {
        if (filter(*i)) {
            switcher(*i);
            out++;
        }
    }
    return out;
}
int Storage::deleteUser(std::function<bool(const User & u)> filter) {
    int out = 0;
    std::list<User>::iterator i;
    i = userList_.begin();
    while (i != userList_.end()) {
        if (filter(*i)) {
            i = userList_.erase(i);
            out++;
        } else {
            i++;
        }
    }
    return out;
}
void Storage::createMeeting(const Meeting & meet) {
    meetingList_.push_back(meet);
}
std::list<Meeting> Storage::queryMeeting(std::function<bool(const Meeting & m)>
                                         filter) {
    std::list<Meeting> out1;
    std::list<Meeting>::iterator i;
    for (i = meetingList_.begin(); i != meetingList_.end(); i++) {
        if (filter(*i)) {
            out1.push_back(*i);
        }
    }
    return out1;
}
int Storage::updateMeeting(std::function<bool(const Meeting & m)> filter,
    std::function<void(Meeting & m)> switcher) {
    int out = 0;
    std::list<Meeting>::iterator i;
    for (i = meetingList_.begin(); i != meetingList_.end(); i++) {
        if (filter(*i)) {
            switcher(*i);
            out++;
        }
    }
    return out;
}
int Storage::deleteMeeting(std::function<bool(const Meeting & m)> filter) {
    int out = 0;
    std::list<Meeting>::iterator i;
    i = meetingList_.begin();
    while (i != meetingList_.end()) {
        if (filter(*i)) {
            i = meetingList_.erase(i);
            out++;
        } else {
            i++;
        }
    }
    return out;
}
bool Storage::sync(void) {
    return writeToFile("agenda.data");
}
Storage::Storage() {
    readFromFile("agenda.data");
}
bool Storage::readFromFile(const char *fpath) {
    if (fpath) {
        ifstream in(fpath);
        if (in.is_open()) {
            string line, temp;
            int total = 0, judge = 0;
            bool flag = 0;
            getline(in, line);
            if (line.size()) if (line[0] != '{') return 0;
            for (int i = 0; i < line.size(); i++) {
                if (line[i] >= '0' && line[i] <= '9')
                    total = total * 10 + (line[i] - '0');
            }
            for (int I = 0; I < total; I++) {
                string name, password, email, phone;
                getline(in, temp);
                judge = 0;
                flag = 0;
                for (int i = 0; i < temp.size(); i++) {
                    if (temp[i] == ':') judge++;
                    if (temp[i] == '"') flag = !flag;
                    if (flag && temp[i] != '"') {
                        if (judge == 1)
                            name += temp[i];
                        else if (judge == 2)
                            password += temp[i];
                        else if (judge == 3)
                            email += temp[i];
                        else if (judge == 4)
                            phone += temp[i];
                    }
                }
                jiemi(password);
                User usr(name, password, email, phone);
                userList_.push_back(usr);
            }
            total = 0;
            getline(in, line);
            for (int i = 0; i < line.size(); i++) {
                if (line[i] >= '0' && line[i] <= '9')
                    total = total * 10 + (line[i] - '0');
            }
            for (int I = 0; I < total; I++) {
                string sponsor, parti, start, end, title;
                getline(in, temp);
                judge = 0;
                flag = 0;
                for (int i = 0; i < temp.size(); i++) {
                    if (temp[i] == ':') judge++;
                    if (temp[i] == '"') flag = !flag;
                    if (flag && temp[i] != '"') {
                        if (judge == 1)
                            sponsor += temp[i];
                        else if (judge == 2)
                            parti += temp[i];
                        else if (judge >= 3 && judge <= 4)
                            start += temp[i];
                        else if (judge >= 5 && judge <= 6)
                            end += temp[i];
                        else if (judge == 7)
                            title += temp[i];
                    }
                }
                Date St = Date::stringToDate(start);
                Date En = Date::stringToDate(end);
                Meeting met(sponsor, parti, St, En, title);
                meetingList_.push_back(met);
            }
            in.close();
            return 1;
        } else {
            return 0;
        }
    }
    return 0;
}
bool Storage::writeToFile(const char *fpath) {
    if (fpath) {
        ofstream out(fpath, std::fstream::in);
        if (out.is_open()) {
            out << "{collection:\"User\",total:" << userList_.size() << "}\n";
            std::list<User>::iterator o1;
            for (o1 = userList_.begin(); o1 != userList_.end(); o1++) {
                out << "{name:\"" << o1->getName()
                    << "\",password:\"" << jiami(o1->getPassword())
                    << "\",email:\"" << o1->getEmail()
                    << "\",phone:\"" << o1->getPhone() << "\"}\n";
            }
            out << "{collection:\"Meeting\",total:"
                << meetingList_.size() << "}\n";
            std::list<Meeting>::iterator o2;
            for (o2 = meetingList_.begin(); o2 != meetingList_.end(); o2++) {
                Date st = o2->getStartDate(), en = o2->getEndDate();
                out << "{sponsor:\""
                    << o2->getSponsor() << "\",participator:\""
                    << o2->getParticipator() << "\",sdate:\""
                    << Date::dateToString(st) << "\",edate:\""
                    << Date::dateToString(en) << "\",title:\""
                    << o2->getTitle() << "\"}\n";
            }
            out.close();
            return 1;
        } else {
            return 0;
        }
    }
    return 0;
}

