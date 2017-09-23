/*
 Date.cpp
 Name: Yuansheng Lu
 Student ID: 136654167
 E-mail: ylu140@myseneca.ca
 */
#include "Date.h"
#include "general.h"

using namespace std;

namespace sict{

    // This function returns a unique integer number based on the date
    // This value is used to compare two dates
    int Date::value()const {
        return year_ * 372 + mon_ * 31 + day_;
    }

    // Returns the number of days in a month
    int Date::mdays()const {
        int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
        int mon = mon_ >= 1 && mon_ <= 12 ? mon_ : 13;
        mon--;
        return days[mon] + int((mon == 1)*((year_ % 4 == 0) && (year_ % 100 != 0)) || (year_ % 400 == 0));
    }

    // Set the readErrorCode_ member-variable
    void Date::errCode(int errorCode) {
        readErrorCode_ = errorCode;
    }

    Date::Date() {
        year_ = 0;
        mon_ = 0;
        day_ = 0;
        readErrorCode_ = NO_ERROR;
    }

    Date::Date(int year, int mon, int day) {
        year_ = year;
        mon_ = mon;
        day_ = day;
        readErrorCode_ = NO_ERROR;
    }

    // Reads the date in the following format:
    // YYYY?MM?DD (e.g. 2016/03/24 or 2016-03-24) from the console
    istream& Date::read(istream& istr) {
        // Store the input data
        // If not in correct format, set the error message to CIN_FAILED
        istr >> year_;
        if (istr.fail()) {
            errCode(CIN_FAILED);
            return istr;
        }
        if (istr.get() != '/' && istr.get() != '-') {
            errCode(CIN_FAILED);
            return istr;
        }
        istr >> mon_;
        if (istr.fail()) {
            errCode(CIN_FAILED);
            return istr;
        }
        if (istr.get() != '/' && istr.get() != '-') {
            errCode(CIN_FAILED);
            return istr;
        }
        istr >> day_;
        if (istr.fail()) {
            errCode(CIN_FAILED);
            return istr;
        }

        // Validate the data received in range
        if (year_ < MIN_YEAR  ||  year_ > MAX_YEAR)
             errCode(YEAR_ERROR);
        else if (mon_ < 1 || mon_ > 12)
            errCode(MON_ERROR);
        else if (day_ < 1 || day_ > mdays())
            errCode(DAY_ERROR);
        else
            errCode(NO_ERROR);

        return istr;
    }

    // Writes the date in the following format: YYYY/MM/DD
    ostream& Date::write(ostream& ostr)const {
        ostr << year_ << "/";

        if (mon_ >= 0 && mon_ <= 9)
            ostr << "0" << mon_ << "/";
        else
            ostr << mon_ << "/";

        if (day_ >= 0 && day_ <= 9)
            ostr << "0" << day_;
        else
            ostr << day_;

        return ostr;
    }

    // Helper operator<< overloaded
    ostream& operator<<(ostream& ostr, const Date& d) {
        d.write(ostr);
        return ostr;
    }

    // Helper operator>> overloaded
    istream& operator>>(istream& istr, Date& d) {
        d.read(istr);
        return istr;
    }

    bool Date::operator==(const Date& D)const {
        bool rv;

        if (this->value() == D.value())
            rv = true;
        else
            rv = false;

        return rv;
    }

    bool Date::operator!=(const Date& D)const {
        bool rv;

        if (this->value() != D.value())
            rv = true;
        else
            rv = false;

        return rv;
    }

    bool Date::operator<(const Date& D)const {
        bool rv;

        if (this->value() < D.value())
            rv = true;
        else
            rv = false;

        return rv;
    }

    bool Date::operator>(const Date& D)const {
        bool rv;

        if (this->value() > D.value())
            rv = true;
        else
            rv = false;

        return rv;
    }

    bool Date::operator<=(const Date& D)const {
        bool rv;

        if (this->value() <= D.value())
            rv = true;
        else
            rv = false;

        return rv;
    }

    bool Date::operator>=(const Date& D)const {
        bool rv;

        if (this->value() >= D.value())
            rv = true;
        else
            rv = false;

        return rv;
    }

    // Return the readErrorCode_ member-variable
    int Date::errCode()const {
        return readErrorCode_;
    }

    // Returns true if readErrorCode_ is not equal to zero
    bool Date::bad()const {
        bool rv;

        if (errCode() != 0)
            rv = true;
        else
            rv = false;

        return rv;
    }
}
