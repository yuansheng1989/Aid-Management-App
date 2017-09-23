/*
 Product.cpp
 Name: Yuansheng Lu
 Student ID: 136654167
 E-mail: ylu140@myseneca.ca
 */
#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include "Product.h"

using namespace std;

namespace sict {
    // constructors, destructor and copy operator
    //
    Product::Product() {
        sku_[0] = '\0'; // set safe empty state
        name_ = nullptr;
        price_ = 0;
        taxed_ = false;
        quantity_ = 0;
        qtyNeeded_ = 0;
    }

    Product::Product(const char* m_sku, const char* m_name, double m_price, int m_qtyNeeded, bool m_taxed) {
        sku(m_sku);
        name(m_name);
        quantity(0); // set current quantity_ to zero
        price(m_price);
        qtyNeeded(m_qtyNeeded);
        taxed(m_taxed);
    }

    Product::Product(const Product& src) {
        // shallow copy non-resource variables
        sku(src.sku_);
        price(src.price_);
        taxed(src.taxed_);
        quantity(src.quantity_);
        qtyNeeded(src.qtyNeeded_);

        // allocate dynamic memory for name
        name(src.name_);
    }

    Product& Product::operator=(const Product& src) {
        // check for self-assignment
        if (this != &src) {
            // shallow copy non-resource variables
            sku(src.sku_);
            price(src.price_);
            taxed(src.taxed_);
            quantity(src.quantity_);
            qtyNeeded(src.qtyNeeded_);

            // deallocate previously allocated dynamic memory
            delete [] name_;
            // allocate new dynamic memory
            name(src.name_);
        }

        return *this;
    }

    Product::~Product() {
        delete [] name_;
    }

    // setters
    //
    void Product::sku(const char* sku) {
        if (sku != nullptr) { // validate the received sku
            strncpy(sku_, sku, MAX_SKU_LEN);
            sku_[MAX_SKU_LEN] = '\0';
        } else {
            sku_[0] = '\0';
        }
    }

    void Product::name(const char* name) {
        if (name != nullptr) { // validate the received name
            name_ = new char[strlen(name) + 1]; // allocate dynamic memory
            strncpy(name_, name, strlen(name));
            name_[strlen(name)] = '\0';
        } else {
            name_ = nullptr;
        }
    }

    void Product::price(double price) {
        price_ = price;
    }

    void Product::taxed(bool taxed) {
        taxed_ = taxed;
    }

    void Product::quantity(int quantity) {
        quantity_ = quantity;
    }

    void Product::qtyNeeded(int qtyNeeded) {
        qtyNeeded_ = qtyNeeded;
    }

    // getters
    //
    const char* Product::sku() const {
        return sku_;
    }

    double Product::price() const {
        return price_;
    }

    const char* Product::name() const {
        return name_;
    }

    bool Product::taxed() const {
        return taxed_;
    }
    int Product::quantity() const {
        return quantity_;
    }

    int Product::qtyNeeded() const {
        return qtyNeeded_;
    }

    double Product::cost() const {
        double cost_product;

        if (taxed_)
            cost_product = price_ * (TAX + 1);
        else
            cost_product = price_;

        return cost_product;
    }

    bool Product::isEmpty() const {
        bool rv;

        if (sku_[0] == '\0')
            rv = true;
        else
            rv = false;

        return rv;
    }

    // member operators
    //
    bool Product::operator==(const char* sku) const {
        return strcmp(sku_, sku) == 0;
    }

    int Product::operator+=(int quantity) {
        quantity_ += quantity;
        return quantity_;
    }

    int Product::operator-=(int quantity) {
        quantity_ -= quantity;
        return quantity_;
    }

    // helper operators
    //
    double operator+=(double& left_operand, const Product& product) {
        left_operand += product.cost() * product.quantity();
        return left_operand;
    }

    ostream& operator<<(ostream& ostr, const Product& product) {
        product.write(ostr, true);
        return ostr;
    }

    istream& operator>>(istream& istr, Product& product) {
        product.read(istr);
        return istr;
    }
}
