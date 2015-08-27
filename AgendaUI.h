#ifndef AGENDAUI_H
#define AGENDAUI_H

#include "AgendaService.h"
#include <iostream>
#include <string>

class AgendaUI {
    public:
    AgendaUI();
    void OperationLoop(void);

    private:
    // task functions
    void startAgenda(void);
    std::string getOperation();
    bool executeLogOperation(std::string op);
    bool executeOperation(std::string op);
    void userLogIn(void);
    void userRegister(void);
    void changePassword(void);
    void setPersonalInformation(void);
    void quitAgenda(void);
    void userLogOut(void);
    void deleteUser(void);
    void listAllUsers(void);
    void createMeeting(void);
    void listAllMeetings(void);
    void listAllSponsorMeetings(void);
    void listAllParticipateMeetings(void);
    void queryMeetingByTitle(void);
    void queryMeetingByTimeInterval(void);
    void deleteMeetingByTitle(void);
    void deleteAllMeetings(void);
    void printUsers(std::list<User> users);
    void printMeetings(std::list<Meeting> meetings);
    // dates
    std::string userName_;
    std::string userPassword_;
    AgendaService agendaService_;
};

#endif

