#include "date.h"
#include <QString>

Date::Date() : day(1), month(1), year(1) { }
Date::Date(int day, int month, int year):day(day), month(month), year(year) {
}

int Date::getDay() const{
    return day;
}

int Date::getMonth() const{
    return month;
}

int Date::gerYear() const{
    return year;
}

QString Date::getFormatted() const {
      return QString("%1.%2.%3")
        .arg(day, 2, 10, QChar('0'))
        .arg(month, 2, 10, QChar('0'))
        .arg(year, 4, 10, QChar('0'));
}

bool Date::IsLeap() const{
    if (year % 400 ==0){
        return true;
    }else if(year % 100 ==0 ){
        return false;
    }else if(year % 4 ==0){
        return true;
    }else{
        return false;
    }
}

static bool isLeap(int y) {
    if (y % 400 == 0) return true;
    if (y % 100 == 0) return false;
    return y % 4 == 0;
}


static int daysInMonth(int m, int y) {
    if (m == 2) {
        if (((y % 400) == 0) || ((y % 4 == 0) && (y % 100 != 0)))
            return 29;
        else
            return 28;
    }
    else if (m == 4 || m == 6 || m == 9 || m == 11) {
        return 30;
    }
    else {
        return 31;
    }
}

Date Date::NextDay() const {
    Date nd = *this;
    nd.day++;
    int dim = daysInMonth(nd.month, nd.year);
    if (nd.day > dim) {
        nd.day = 1;
        nd.month++;
        if (nd.month > 12) {
            nd.month = 1;
            nd.year++;
        }
    }
    return nd;
}

short Date::WeekNumber() const {
    int dayOfYear = 0;
    for (int m = 1; m < month; m++) {
        dayOfYear += daysInMonth(m, year);
    }
    dayOfYear += day;
    short w = (dayOfYear + 6) / 7;
    return w;
}


Date Date::PreviousDay() const {
    Date pd = *this;
    pd.day--;
    if (pd.day < 1) {
        pd.month--;
        if (pd.month < 1) {
            pd.month = 12;
            pd.year--;
        }
        pd.day = daysInMonth(pd.month, pd.year);
    }
    return pd;
}



int Date::daysFromStart(const Date &d){
    int n = d.day;
    for( int m=1; m<d.month; m++){
        if (m==2){
            n+=d.IsLeap() ? 29 :28;
        }else if (m==4 || m==6 ||m==9 ||m==11){
            n+= 30;
        } else{
            n+=31  ;
        }
    }
    int days =0;
    for (int year=1; year<d.year; year++){
        days += (isLeap(year) ? 366 : 365);
    }
    return n+days;
}


int Date::Duration( const Date &other){
    int duraction=daysFromStart(*this)-daysFromStart(other);
    return duraction > 0 ? duraction : -duraction;
}

int Date::DaysTillYourBithday(const Date &birthday){
    Date nextBirthday(birthday.day, birthday.month, year);
    if (birthday.month < month || (birthday.month == month && birthday.day < day)) {
        nextBirthday.year = year + 1;
    } else {
        nextBirthday.year = year;
    }
    return Duration(nextBirthday);
}








