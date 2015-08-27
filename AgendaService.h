#ifndef AGENDASERVICE_H
#define AGENDASERVICE_H

#include "Storage.h"
#include <list>
#include <string>

class AgendaService {
    public:
    AgendaService();
    ~AgendaService();
    bool ValidDate(const std::string & str);
    bool ValidEmail(const std::string & str);
    bool ValidPhone(const std::string & str);
    bool ValidNameOrPassword(const std::string & str);
    bool userLogIn(std::string userName, std::string password);
    bool userRegister(std::string userName, std::string password,
    std::string email, std::string phone);
    bool userSetInformation(std::string UserName, std::string Email,
                            std::string Phone);
    bool changePassword(std::string UserName, std::string Password,
                        std::string Email, std::string Phone);
    bool deleteUser(std::string userName, std::string password);
    // a user can only delete itself
    std::list<User> listAllUsers(void);
    bool createMeeting(std::string userName, std::string title,
    std::string participator,
    std::string startDate, std::string endDate);
    std::list<Meeting> meetingQuery(std::string userName, std::string title);
    std::list<Meeting> meetingQuery(std::string userName, std::string startDate,
    std::string endDate);
    std::list<Meeting> listAllMeetings(std::string userName);
    std::list<Meeting> listAllSponsorMeetings(std::string userName);
    std::list<Meeting> listAllParticipateMeetings(std::string userName);
    bool deleteMeeting(std::string userName, std::string title);
    bool deleteAllMeetings(std::string userName);
    void startAgenda(void);
    void quitAgenda(void);

    private:
    Storage *storage_;
};

#endif

