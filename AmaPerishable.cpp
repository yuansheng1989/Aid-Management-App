/*
 AmaPerishable.cpp
 Name: Yuansheng Lu
 Student ID: 136654167
 E-mail: ylu140@myseneca.ca
 */
#include "AmaPerishable.h"

using namespace std;

namespace sict {
    AmaPerishable::AmaPerishable() : AmaProduct('P') {}

    // assessor of expiry_
    //
    const Date& AmaPerishable::expiry()const {
        return expiry_;
    }

    void AmaPerishable::expiry(const Date &value) {
        expiry_ = value;
    }

    // streamable functions
    //
    fstream& AmaPerishable::store(fstream& file, bool addNewLine)const {
        AmaProduct::store(file, false) << "," << expiry_ << endl;
        return file;
    }

    fstream& AmaPerishable::load(fstream& file) {
        AmaProduct::load(file);
        file >> expiry_;
        file.ignore();
        return file;
    }

    ostream& AmaPerishable::write(ostream& os, bool linear)const {
        AmaProduct::write(os, linear);

        if (err_.isClear()) { // product is not empty
            if (linear) {
                os << expiry_;
            } else {
                os << endl;
                os << "Expiry date: " << expiry_;
            }
        }

        return os;
    }

    istream& AmaPerishable::read(istream& is) {
        Date expiry_t;
        AmaProduct::read(is);

        if (err_.isClear()) {
            cout << "Expiry date (YYYY/MM/DD): ";
            is >> expiry_t;

            if (expiry_t.bad()) {
                switch(expiry_t.errCode()) {
                case 1:
                    err_.message("Invalid Date Entry");
                    break;
                case 2:
                    err_.message("Invalid Year in Date Entry");
                    break;
                case 3:
                    err_.message("Invalid Month in Date Entry");
                    break;
                case 4:
                    err_.message("Invalid Day in Date Entry");
                    break;
                }

                is.setstate(ios::failbit);
            } else {
                expiry_ = expiry_t;
            }
        }

        return is;
    }

}
