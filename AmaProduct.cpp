/*
 AmaProduct.cpp
 Name: Yuansheng Lu
 Student ID: 136654167
 E-mail: ylu140@myseneca.ca
 */
#define _CRT_SECURE_NO_WARNINGS
#include "AmaProduct.h"
#include "cstring"

using namespace std;

namespace sict {
    AmaProduct::AmaProduct(char fileTag) {
        fileTag_ = fileTag;
    }

    // assessor of unit_
    //
    const char* AmaProduct::unit()const {
        return unit_;
    }

    void AmaProduct::unit(const char* value) {
        strncpy(unit_, value, 10);
        unit_[10] = '\0';
    }

    // streamable functions
    //
    fstream& AmaProduct::store(fstream& file, bool addNewLine)const {
        file << fileTag_ << ',';
        file << sku() << ',';
        file << name() << ',';
        file << price() << ',';
        file << taxed() << ',';
        file << quantity() << ',';
        file << unit_ << ',';
        file << qtyNeeded();

        if (addNewLine == true)
            file << endl;

        return file;
    }

    fstream& AmaProduct::load(fstream& file) {
        char sku_t[MAX_SKU_LEN + 1];
        char name_t[100];
        double price_t;
        bool taxed_t;
        int quantity_t;
        int qtyNeeded_t;

        file.getline(sku_t, MAX_SKU_LEN + 1, ',');
        file.getline(name_t, 100, ',');
        file >> price_t;
        file.ignore();
        file >> taxed_t;
        file.ignore();
        file >> quantity_t;
        file.ignore();
        file.getline(unit_, 11, ',');
        file >> qtyNeeded_t;
        file.ignore();

        sku(sku_t);
        name(name_t);
        price(price_t);
        taxed(taxed_t);
        quantity(quantity_t);
        qtyNeeded(qtyNeeded_t);

        return file;
    }

    ostream& AmaProduct::write(ostream& os, bool linear)const {
         if (err_.isClear() == false) {
            os << err_;
         } else {
            if (linear) {
                os.width(MAX_SKU_LEN);
                os.setf(ios::left);
                os << sku();
                os << '|';

                os.width(20);
                os << name();
                os << '|';
                os.unsetf(ios::left);

                os.width(7);
                os.precision(2);
                os.setf(ios::fixed);
                os.setf(ios::right);
                os << cost();
                os << '|';
                os.precision(6);
                os.unsetf(ios::fixed);

                os.width(4);
                os << quantity();
                os << '|';
                os.unsetf(ios::right);

                os.width(10);
                os.setf(ios::left);
                os << unit_;
                os << '|';
                os.unsetf(ios::left);

                os.width(4);
                os.setf(ios::right);
                os << qtyNeeded();
                os << '|';
                os.unsetf(ios::right);

            } else {
                os << "Sku: " << sku() << endl;
                os << "Name: " << name() <<endl;
                os.precision(2);
                os.setf(ios::fixed);
                os << "Price: " << price() << endl;
                os << "Price after tax: ";
                if (taxed())
                    os << cost() << endl;
                else
                    os << "N/A" << endl;
                os << "Quantity On Hand: " << quantity() << " " << unit_ << endl;
                os << "Quantity Needed: " << qtyNeeded();
                os.precision(6);
                os.unsetf(ios::fixed);
            }
         }

         return os;
    }

    istream& AmaProduct::read(istream& is) {
        char sku_t[MAX_SKU_LEN + 1];
        char name_t[100];
        double price_t;
        char taxed_t;
        int quantity_t;
        int qtyNeeded_t;

        err_.clear(); // clear previous error message

        cout << "Sku: ";
        is >> sku_t;
        sku(sku_t);

        cout << "Name: ";
        //is >> name_t;
        is.ignore(2000, '\n');
        is.get(name_t, 21, '\n');
        name(name_t);

        cout << "Unit: ";
        //is >> unit_;
        is.ignore(2000, '\n');
        is.getline(unit_, 11, '\n'); // no unit is allowed

        cout << "Taxed? (y/n): ";
        is >> taxed_t;
        if (taxed_t == 'y' || taxed_t == 'Y') {
            taxed(true);
        } else if (taxed_t == 'n' || taxed_t == 'N') {
            taxed(false);
        } else {
            err_.message("Only (Y)es or (N)o are acceptable");
            is.setstate(ios::failbit);
            return is;
        }

        cout << "Price: ";
        is >> price_t;
        if (is.fail()) {
            err_.message("Invalid Price Entry");
            return is;
        } else {
            price(price_t);
        }

        cout << "Quantity On hand: ";
        is >> quantity_t;
        if (is.fail()) {
            err_.message("Invalid Quantity Entry");
            return is;
        } else {
            quantity(quantity_t);
        }

        cout << "Quantity Needed: ";
        is >> qtyNeeded_t;
        if (is.fail()) {
            err_.message("Invalid Quantity Needed Entry");
            return is;
        } else {
            qtyNeeded(qtyNeeded_t);
        }

        return is;
    }
}
