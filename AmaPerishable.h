/*
 AmaPerishable.h
 Name: Yuansheng Lu
 Student ID: 136654167
 E-mail: ylu140@myseneca.ca
 */
#ifndef SICT_AMAPERISHABLE_H__
#define SICT_AMAPERISHABLE_H__

#include "AmaProduct.h"
#include "Date.h"

namespace sict {
    class AmaPerishable : public AmaProduct {
        Date expiry_;
    public:
        AmaPerishable();

        // assessor of expiry_
        const Date& expiry()const;
        void expiry(const Date &value);

        // streamable functions
        std::fstream& store(std::fstream& file, bool addNewLine = true)const;
        std::fstream& load(std::fstream& file);
        std::ostream& write(std::ostream& os, bool linear)const;
        std::istream& read(std::istream& is);
    };
}

#endif
