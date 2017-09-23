/*
 Stremable.h
 Name: Yuansheng Lu
 Student ID: 136654167
 E-mail: ylu140@myseneca.ca
 */
#ifndef SICT_STREAMABLE_H__
#define SICT_STREAMABLE_H__

#include <iostream>
#include <fstream>

namespace sict {
    class Streamable {
    public:
        // pure virtual member functions
        virtual std::fstream& store(std::fstream& file, bool addNewLine = true)const = 0;
        virtual std::fstream& load(std::fstream& file) = 0;
        virtual std::ostream& write(std::ostream& os, bool linear)const = 0;
        virtual std::istream& read(std::istream& is) = 0;
    };
}

#endif
