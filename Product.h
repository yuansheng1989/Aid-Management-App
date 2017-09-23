/*
 Product.h
 Name: Yuansheng Lu
 Student ID: 136654167
 E-mail: ylu140@myseneca.ca
 */
#ifndef SICT_PRODUCT_H__
#define SICT_PRODUCT_H__

#include <iostream>
#include "Streamable.h"
#include "general.h"

namespace sict {
    class Product : public Streamable {
        char sku_[MAX_SKU_LEN + 1];
        char* name_;
        double price_;
        bool taxed_;
        int quantity_;
        int qtyNeeded_;
    public:
        // constructors, destructor and copy operator
        Product();
        Product(const char* m_sku, const char* m_name, double m_price = 0, int m_qtyNeeded = 0, bool m_taxed = true);
        Product(const Product& src);
        Product& operator=(const Product& src);
        virtual ~Product();

        // setters
        void sku(const char* sku);
        void price(double price);
        void name(const char* name);
        void taxed(bool taxed);
        void quantity(int quantity);
        void qtyNeeded(int qtyNeeded);

        // getters
        const char* sku() const;
        double price() const;
        const char* name() const;
        bool taxed() const;
        int quantity() const;
        int qtyNeeded() const;
        double cost() const;
        bool isEmpty() const;

        // member operators
        bool operator==(const char* sku) const;
        int operator+=(int quantity);
        int operator-=(int quantity);
    };

    // helper operators
    double operator+=(double& left_operand, const Product& product);
    std::ostream& operator<<(std::ostream& ostr, const Product& product);
    std::istream& operator>>(std::istream& istr, Product& product);
}

#endif
