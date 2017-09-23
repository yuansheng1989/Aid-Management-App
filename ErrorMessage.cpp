/*
 ErrorMessage.cpp
 Name: Yuansheng Lu
 Student ID: 136654167
 E-mail: ylu140@myseneca.ca
 */
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include "ErrorMessage.h"

using namespace std;

namespace sict {
    ErrorMessage::ErrorMessage() {
        message_ = nullptr;
    }

    ErrorMessage::ErrorMessage(const char* errorMessage) {
        message_ = nullptr;
        message(errorMessage);
    }

    ErrorMessage& ErrorMessage::operator=(const char* errorMessage) {
        message(errorMessage);
        return *this;
    }

    ErrorMessage::~ErrorMessage() {
        delete [] message_;
    }

    // De-allocates the memory pointed by message_
    void ErrorMessage::clear() {
        delete [] message_;
        message_ = nullptr;
    }

    // message_ setter
    void ErrorMessage::message(const char* value) {
        clear(); // deallocate original memory
        message_ = new char[strlen(value) + 1];
        strcpy(message_, value);
    }

    // Check whether message_ is nullptr or not
    bool ErrorMessage::isClear()const {
        bool rv;

        if (message_ == nullptr)
            rv = true;
        else
            rv = false;

        return rv;
    }

    // Return message_
    const char* ErrorMessage::message()const {
        return message_;
    }

    // Helper operator <<
    ostream& operator<<(ostream& ostr, const ErrorMessage& em) {
        if (!em.isClear())
            ostr << em.message();
        return ostr;
    }
}
