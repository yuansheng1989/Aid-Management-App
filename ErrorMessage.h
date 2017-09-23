/*
 ErrorMessage.h
 Name: Yuansheng Lu
 Student ID: 136654167
 E-mail: ylu140@myseneca.ca
 */
#ifndef SICT_ERROR_MESSAGE_H__
#define SICT_ERROR_MESSAGE_H__

#include <iostream>

namespace sict {
    class ErrorMessage {
        char* message_;
    public:
        // Constructors
        ErrorMessage();
        ErrorMessage(const char* errorMessage);
        ErrorMessage(const ErrorMessage& em) = delete;
        // Public member functions and operator overloads
        ErrorMessage& operator=(const ErrorMessage& em) = delete;
        ErrorMessage& operator=(const char* errorMessage);
        virtual ~ErrorMessage();
        void clear(); // De-allocates the memory pointed by message_
        bool isClear()const; // Check whether message_ is nullptr or not
        void message(const char* value); // message_ setter
        const char* message()const; // Return message_
    };

    // Helper operator <<
    std::ostream& operator<<(std::ostream& ostr, const ErrorMessage& em);
}

#endif
