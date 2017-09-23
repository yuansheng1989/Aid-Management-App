/*
 AmaProduct.h
 Name: Yuansheng Lu
 Student ID: 136654167
 E-mail: ylu140@myseneca.ca
 */
#ifndef SICT_AMAPRODUCT_H__
#define SICT_AMAPRODUCT_H__

#include "Product.h"
#include "ErrorMessage.h"

namespace sict {
    class AmaProduct : public Product {
        char fileTag_; // tag records as Perishable or non-Perishable
        char unit_[11]; // unit of measurement
    protected:
        ErrorMessage err_;
    public:
        AmaProduct(char fileTag = 'N');

        // assessor of unit_
        const char* unit()const;
        void unit(const char* value);

        // streamable functions
        std::fstream& store(std::fstream& file, bool addNewLine = true)const;
        std::fstream& load(std::fstream& file);
        std::ostream& write(std::ostream& os, bool linear)const;
        std::istream& read(std::istream& is);
    };
}

#endif
