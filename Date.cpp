#include "Date.h"
Date::Date() {}
Date::Date(int y, int m, int d, int h, int mi) {
    year_ = y;
    month_ = m;
    day_ = d;
    hour_ = h;
    minute_ = mi;
}
int Date::getYear(void) const {
    return year_;
}
void Date::setYear(int year) {
    year_ = year;
}
int Date::getMonth(void) const {
    return month_;
}
void Date::setMonth(int month) {
    month_ = month;
}
int Date::getDay(void) const {
    return day_;
}
void Date::setDay(int day) {
    day_ = day;
}
int Date::getHour(void) const {
    return hour_;
}
void Date::setHour(int hour) {
    hour_ = hour;
}
int Date::getMinute(void) const {
    return minute_;
}
void Date::setMinute(int minute) {
    minute_ = minute;
}
bool Date::isValid(Date date) {
    if (date.getHour() > 23 || date.getHour() < 0) return 0;
    if (date.getMinute() > 59 || date.getMinute() < 0) return 0;
    if (date.getYear() >9999 || date.getYear() < 1000) return 0;
    if (date.getMonth() >12 || date.getMonth() < 1) return 0;
    if (date.getDay() < 1 || date.getDay() > 31) return 0;
    if (date.getDay() == 31) {
        int m = date.getMonth();
        if (m == 2 || m == 4 || m == 6 || m == 9 || m == 11) return 0;
    }
    if (date.getDay() == 30 && date.getMonth() == 2) return 0;
    if (date.getDay() == 29 && date.getMonth() == 2) {
        bool run = 0;
        int y = date.getYear();
        if ((y % 100 && !(y % 4)) || !(y % 400)) run = 1;
        return run;
    }
    return 1;
}
Date Date::stringToDate(std::string dateString) {
    Date outdate;
    int y, m, d, h, mi;
    y = (dateString[0] - '0') * 1000 + (dateString[1] - '0') * 100
        + (dateString[2] - '0') * 10 + (dateString[3] - '0');
    m = (dateString[5] - '0') * 10 + (dateString[6] - '0');
    d = (dateString[8] - '0') * 10 + (dateString[9] - '0');
    h = (dateString[11] - '0') * 10 + (dateString[12] - '0');
    mi = (dateString[14] - '0') * 10 + (dateString[15] - '0');
    outdate.setYear(y);
    outdate.setMonth(m);
    outdate.setDay(d);
    outdate.setHour(h);
    outdate.setMinute(mi);
    return outdate;
}
std::string Date::dateToString(Date date) {
    std::string outdate;
    int y = date.getYear(), m = date.getMonth(), d = date.getDay(),
        h = date.getHour(), mi = date.getMinute();
    outdate += (y / 1000 + '0');
    outdate += ((y / 100) % 10 + '0');
    outdate += ((y / 10) % 10 + '0');
    outdate += (y % 10 + '0');
    outdate += '-';
    outdate += (m / 10 + '0');
    outdate += (m % 10 + '0');
    outdate += '-';
    outdate += (d / 10 + '0');
    outdate += (d % 10 + '0');
    outdate += '/';
    outdate += (h / 10 + '0');
    outdate += (h % 10 + '0');
    outdate += ':';
    outdate += (mi / 10 + '0');
    outdate += (mi % 10 + '0');
    return outdate;
}
Date & Date::operator=(const Date& date) {
    year_ = date.getYear();
    month_ = date.getMonth();
    day_ = date.getDay();
    hour_ = date.getHour();
    minute_ = date.getMinute();
    return *this;
}
bool Date::operator==(const Date& date) const {
    if (year_ == date.getYear())
    if (month_ == date.getMonth())
    if (day_ == date.getDay())
    if (hour_ == date.getHour())
    if (minute_ == date.getMinute())
        return 1;
    return 0;
}
bool Date::operator>(const Date& date) const {
    if (year_ > date.getYear()) return 1;
    if (year_ < date.getYear()) return 0;
    if (month_ > date.getMonth()) return 1;
    if (month_ < date.getMonth()) return 0;
    if (day_ > date.getDay()) return 1;
    if (day_ < date.getDay()) return 0;
    if (hour_ > date.getHour()) return 1;
    if (hour_ < date.getHour()) return 0;
    if (minute_ > date.getMinute()) return 1;
    return 0;
}
bool Date::operator<(const Date& date) const {
    if (year_ < date.getYear()) return 1;
    if (year_ > date.getYear()) return 0;
    if (month_ < date.getMonth()) return 1;
    if (month_ > date.getMonth()) return 0;
    if (day_ < date.getDay()) return 1;
    if (day_ > date.getDay()) return 0;
    if (hour_ < date.getHour()) return 1;
    if (hour_ > date.getHour()) return 0;
    if (minute_ < date.getMinute()) return 1;
    return 0;
}
bool Date::operator>=(const Date& date) const {
    if (*this < date) return 0;
    return 1;
}
bool Date::operator<=(const Date& date) const {
    if (*this > date) return 0;
    return 1;
}

