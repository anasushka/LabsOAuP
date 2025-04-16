#ifndef DATE_H
#define DATE_H
#include <QString>

class Date
{
public:
    Date();
    Date(int day, int month, int year);

    int getDay() const;
    int getMonth() const;
    int gerYear() const;

    QString getFormatted() const;

    bool IsLeap() const;

    int daysFromStart(const Date &d);


    Date NextDay() const;
    Date PreviousDay() const;
    short WeekNumber() const;
    int DaysTillYourBithday(const Date &birthdayDate);
    int Duration(const Date &other);

private:
    int day, month, year;
};

#endif // DATE_H
