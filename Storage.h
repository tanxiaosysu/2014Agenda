#ifndef AGENDA_STORAGE_H
#define AGENDA_STORAGE_H

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&); \
  void operator=(const TypeName&)

#include <list>
#include <string>
#include <functional>

#include "User.h"
#include "Meeting.h"

class Storage {
    public:
    // singleton
    static Storage *getInstance(void);
    ~Storage();
    // CRUD for User & Meeting using C++11
    // Function Template and Lambda Expressions
    void createUser(const User& u);
    std::list<User> queryUser(std::function<bool(const User & u)> filter);
    // return found users
    int updateUser(std::function<bool(const User & u)> filter,
                   std::function<void(User & u)> switcher);
                   // return the number of updated users
    int deleteUser(std::function<bool(const User & u)> filter);
    // return the number of deleted users
    void createMeeting(const Meeting & m);
    std::list<Meeting> queryMeeting(std::function<bool(const Meeting & m)>
                                    filter);
    // return found meetings
    int updateMeeting(std::function<bool(const Meeting & m)> filter,
                      std::function<void(Meeting & m)> switcher);
                      // return the number of updated meetings
    int deleteMeeting(std::function<bool(const Meeting & m)> filter);
    // return the number of deleted meetings
    // File IO
    bool sync(void);

    private:
    static Storage *instance_;
    Storage();
    // storage structure with list, or you have better
    // structures e.g. balanced tree
    std::list<User> userList_;
    std::list<Meeting> meetingList_;
    // File IO
    bool readFromFile(const char *fpath);
    bool writeToFile(const char *fpath);
    DISALLOW_COPY_AND_ASSIGN(Storage);
};

#endif

