/*
 Date.h
 Name: Yuansheng Lu
 Student ID: 136654167
 E-mail: ylu140@myseneca.ca
 */
#ifndef SICT_DATE_H__
#define SICT_DATE_H__

#include <iostream>

namespace sict{
    // Possible error values for readErrorCode_ member-variable
    const int NO_ERROR = 0;
    const int CIN_FAILED = 1;
    const int YEAR_ERROR = 2;
    const int MON_ERROR = 3;
    const int DAY_ERROR = 4;

    class Date {
    private:
        int year_;
        int mon_;
        int day_;
        int readErrorCode_; // error code
        int value()const; // used to compare two dates
        void errCode(int errorCode); //set readErrorCode_
    public:
        Date();
        Date(int year, int mon, int day);
        int mdays()const; // returns the number of days in a month
        std::istream& read(std::istream& istr);
        std::ostream& write(std::ostream& ostr)const;
        bool operator==(const Date& D)const;
        bool operator!=(const Date& D)const;
        bool operator<(const Date& D)const;
        bool operator>(const Date& D)const;
        bool operator<=(const Date& D)const;
        bool operator>=(const Date& D)const;
        int errCode()const; // return readErrorCode_
        bool bad()const; // return the state of readErrorCode_
    };

    // helper operator << and operator >>
    std::ostream& operator<<(std::ostream& ostr, const Date& d);
    std::istream& operator>>(std::istream& istr, Date& d);
}
#endif
