#include "AgendaService.h"
#include <iostream>
using std::cout;
bool AgendaService::ValidNameOrPassword(const std::string & str) {
    for (int i = 0; i < str.size(); i++) {
        if (str[i] < 48) return 0;
    if (str[i] < 65 && str[i] > 57) return 0;
    if (str[i] < 97 && str[i] > 90) return 0;
    if (str[i] > 122) return 0;
    }
    return 1;
}
bool normalformat(const char & c) {
    if (c < 48) return 0;
    if (c < 65 && c > 57) return 0;
    if (c < 97 && c > 90) return 0;
    if (c > 122) return 0;
    return 1;
}
bool AgendaService::ValidPhone(const std::string & str) {
    if (str.size() < 3) return 0;
    for (int i = 0; i < str.size(); i++)
        if (str[i] < '0' || str[i] > '9') return 0;
    return 1;
}
bool AgendaService::ValidEmail(const std::string & str) {
    for (int i = 0; i < str.size(); i++)
        if (str[i] == '"' || str[i] == ':') return 0;
    int at = 0, point = 0;
    for (int i = 0; i < str.size(); i++) {
        if (str[i] == '@') at++;
        if (str[i] == '.') point++;
    }
    if (at != 1 || point != 1) return 0;
    int at1, point1;
    for (int i = 0; i < str.size(); i++) {
        if (str[i] == '@') at1 = i;
        if (str[i] == '.') point1 = i;
    }
    for (int i = 0; i < str.size(); i++) {
        if (i != at1 && i != point1) if (!normalformat(str[i])) return 0;
    }
    return 1;
}
bool AgendaService::ValidDate(const std::string & str) {
    if (str.length() != 16) return 0;
    for (int i = 0; i < 16; i++) {
        if (i == 4 || i == 7)
            if (str[i] != '-') return 0;
        else if (i == 10)
            if (str[i] != '/') return 0;
        else if (i == 13)
            if (str[i] != ':') return 0;
        else
            if (str[i] < '0' || str[i] > '9') return 0;
    }
    Date test = Date::stringToDate(str);
    return Date::isValid(test);
}
AgendaService::AgendaService() {}
AgendaService::~AgendaService() {}
bool AgendaService::userLogIn(std::string userName, std::string password) {
        std::function<bool(const User & u)> filter =
            [userName, password](const User & u)
            {return (u.getName() == userName && u.getPassword() == password); };
            std::list<User> out = storage_->queryUser(filter);
        return (!(out.empty()));
    }
bool AgendaService::userRegister(std::string userName, std::string password,
std::string email, std::string phone) {
    if (!ValidNameOrPassword(userName) || !ValidNameOrPassword(password)) {
        cout << "\nIllegal UserName / Password!\n";
        return 0;
    }
    if (!ValidEmail(email) || !ValidPhone(phone)) {
        cout << "\nIllegal Email / Phone!\n";
        return 0;
    }
    std::function<bool(const User & u)> filter =
        [userName](const User & u) {return (u.getName() == userName); };
    std::list<User> out = storage_->queryUser(filter);
    if (out.empty()) {
        User usr(userName, password, email, phone);
        storage_->createUser(usr);
        return 1;
    }
    cout << "\nUser has existed!\n";
    return 0;
}
bool AgendaService::userSetInformation(std::string UserName, std::string Email,
                                       std::string Phone) {
    if (!ValidEmail(Email) || !ValidPhone(Phone)) {
        cout << "\nIllegal Email / Phone!\n";
        return 0;
    }
    std::function<bool(const User & u)> filter =
        [UserName](const User & u) {return (u.getName() == UserName); };
    std::function<void(User & u)> switcher =
        [Email, Phone](User & u)->void {u.setEmail(Email); u.setPhone(Phone); };
    return (storage_->updateUser(filter, switcher));
}
bool AgendaService::changePassword(std::string UserName, std::string Password,
                                   std::string Email, std::string Phone) {
    if (!ValidEmail(Email) || !ValidPhone(Phone)) {
        cout << "\nIllegal Email / Phone!\n";
        return 0;
    }
    std::function<bool(const User & u)> filter1 =
        [UserName, Email, Phone](const User & u) {return ((u.getName()
         == UserName && u.getEmail() == Email) && (u.getPhone() == Phone)); };
    std::list<User> out = storage_->queryUser(filter1);
    if (out.empty()) return 0;
    std::function<bool(const User & u)> filter2 =
        [UserName](const User & u) {return (u.getName() == UserName); };
    std::function<void(User & u)> switcher =
        [Password](User & u)->void {u.setPassword(Password); };
    return (storage_->updateUser(filter2, switcher));
}
bool AgendaService::deleteUser(std::string userName, std::string password) {
    std::function<bool(const User & u)> filter =
            [userName, password](const User & u)
            {return (u.getName() == userName && u.getPassword() == password); };
    std::list<User> out = storage_->queryUser(filter);
    if (out.empty()) return 0;
    deleteAllMeetings(userName);
    std::function<bool(const Meeting & u)> filterp =
        [userName](const Meeting & u)
        {return (userName == u.getParticipator()); };
    storage_->deleteMeeting(filterp);
    return (storage_->deleteUser(filter));
}
// a user can only delete itself
std::list<User> AgendaService::listAllUsers(void) {
    std::function<bool(const User & u)> filter =
        [](const User & u) {return 1; };
    std::list<User> out = storage_->queryUser(filter);
    return out;
}

bool AgendaService::createMeeting(std::string userName, std::string title,
std::string participator, std::string startDate, std::string endDate) {
    if (!(ValidDate(startDate)) || !(ValidDate(endDate))) return 0;
    // 日期非法
    if (Date::stringToDate(startDate) >= Date::stringToDate(endDate)) return 0;
    // 时间大小
    if (!ValidNameOrPassword(userName) || (!ValidNameOrPassword(participator) ||
        !ValidNameOrPassword(title))) return 0;
    std::function<bool(const User & u)> filters =
        [userName](const User & u) {return (u.getName() == userName); };
        std::function<bool(const User & u)> filterp = [participator]
        (const User & u) {return (u.getName() == participator); };
        // 发起人和参与人的过滤
    if (!(storage_->queryUser(filters).size() &&
        storage_->queryUser(filterp).size())) return 0;
        // 保证用户存在
    Date st = Date::stringToDate(startDate), en = Date::stringToDate(endDate);
    std::list<Meeting> spon = listAllMeetings(userName);
    std::list<Meeting> part = listAllMeetings(participator);
    std::list<Meeting>::iterator i;
    for (i = spon.begin(); i != spon.end(); i++) {
        if (!((en <= i->getStartDate()) || (st >= i->getEndDate()))) return 0;
        if (title == i->getTitle()) return 0;
    }
    // 时间非法， 标题重复
    for (i = part.begin(); i != part.end(); i++) {
        if (!(en <= i->getStartDate() || st >= i->getEndDate())) return 0;
        if (title == i->getTitle()) return 0;
    }
    Meeting met(userName, participator, Date::stringToDate(startDate),
        Date::stringToDate(endDate), title);
    storage_->createMeeting(met);
    return 1;
}
std::list<Meeting> AgendaService::meetingQuery(std::string userName,
    std::string title) {
    std::list<Meeting> out;
    std::function<bool(const Meeting & u)> filters =
        [userName, title](const Meeting & u)
        {return (userName == u.getSponsor() && title == u.getTitle()); };
    out = storage_->queryMeeting(filters);
    std::list<Meeting> o1;
    std::function<bool(const Meeting & u)> filterp =
        [userName, title](const Meeting & u)
        {return (userName == u.getParticipator() && title == u.getTitle()); };
    o1 = storage_->queryMeeting(filterp);
    std::list<Meeting>::iterator i;
    for (i = o1.begin(); i != o1.end(); i++) out.push_back(*i);
    return out;
}
std::list<Meeting> AgendaService::meetingQuery(std::string userName,
    std::string startDate, std::string endDate) {
    std::list<Meeting> out;
    std::list<Meeting> o1;
    if (!(ValidDate(startDate)) && !(ValidDate(endDate))) return out;
    if (Date::stringToDate(startDate) > Date::stringToDate(endDate)) return out;
    std::function<bool(const Meeting & u)> filters =
        [userName, startDate, endDate](const Meeting & u)
        {return (userName == u.getSponsor() && ((Date::stringToDate(startDate)
        >= u.getStartDate() && Date::stringToDate(startDate) <= u.getEndDate())
        || (Date::stringToDate(startDate) < u.getStartDate() &&
        Date::stringToDate(endDate) >= u.getStartDate()))); };
    std::function<bool(const Meeting & u)> filterp =
        [userName, startDate, endDate](const Meeting & u)
        {return (userName == u.getParticipator() &&
        ((Date::stringToDate(startDate)
        >= u.getStartDate() && Date::stringToDate(startDate) <= u.getEndDate())
        || (Date::stringToDate(startDate) < u.getStartDate() &&
        Date::stringToDate(endDate) >= u.getStartDate()))); };
    out = storage_->queryMeeting(filters);
    o1 = storage_->queryMeeting(filterp);
    std::list<Meeting>::iterator i;
    for (i = o1.begin(); i != o1.end(); i++)
        out.push_back(*i);
    return out;
}
std::list<Meeting> AgendaService::listAllMeetings(std::string userName) {
    std::list<Meeting> out = listAllSponsorMeetings(userName);
    std::list<Meeting> tmp = listAllParticipateMeetings(userName);
    std::list<Meeting>::iterator i;
    for (i = tmp.begin(); i != tmp.end(); i++)
        out.push_back(*i);
    return out;
}
std::list<Meeting> AgendaService::listAllSponsorMeetings(std::string userName) {
    std::list<Meeting> out;
    std::function<bool(const Meeting & u)> filter =
        [userName](const Meeting & u)
        {return (userName == u.getSponsor()); };
    out = storage_->queryMeeting(filter);
    return out;
}
std::list<Meeting> AgendaService::listAllParticipateMeetings
    (std::string userName) {
    std::list<Meeting> out;
    std::function<bool(const Meeting & u)> filter =
        [userName](const Meeting & u)
        {return (userName == u.getParticipator()); };
    out = storage_->queryMeeting(filter);
    return out;
}
bool AgendaService::deleteMeeting(std::string userName, std::string title) {
    std::function<bool(const Meeting & u)> filter =
        [userName, title](const Meeting & u)
        {return (userName == u.getSponsor() && title == u.getTitle()); };
    return storage_->deleteMeeting(filter);
}
bool AgendaService::deleteAllMeetings(std::string userName) {
    std::function<bool(const Meeting & u)> filter = [userName]
        (const Meeting & u) {return (userName == u.getSponsor()); };
    return storage_->deleteMeeting(filter);
}
void AgendaService::startAgenda(void) {
    storage_ = Storage::getInstance();
}
void AgendaService::quitAgenda(void) {
    storage_->sync();
}

