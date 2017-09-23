/*
 AidApp.cpp
 Name: Yuansheng Lu
 Student ID: 136654167
 E-mail: ylu140@myseneca.ca
*/
#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <iomanip>
#include "AidApp.h"

using namespace std;

namespace sict {
	// constructor
	//
	AidApp::AidApp() {
		filename_[0] = '\0';

		for (int i = 0; i < MAX_NO_RECS; i++)
			product_[i] = nullptr;

		noOfProducts_ = 0;
		loadRecs();
	}

	AidApp::AidApp(const char* filename) {
		strcpy(filename_, filename);

		for (int i = 0; i < MAX_NO_RECS; i++)
			product_[i] = nullptr;

		noOfProducts_ = 0;
		loadRecs();
	}

	// private function
	//
	void AidApp::pause()const {
		cout << "Press Enter to continue..." << endl;
		while (cin.get() != '\n') {} // wait for user pressing enter
	}

	int AidApp::menu() {
		int choice;
		int rv;

		cout << "Disaster Aid Supply Management Program" << endl;
		cout << "1- List products" << endl;
		cout << "2- Display product" << endl;
		cout << "3- Add non-perishable product" << endl;
		cout << "4- Add perishable product" << endl;
		cout << "5- Add to quantity of purchased products" << endl;
		cout << "0- Exit program" << endl;
		cout << "> ";

		cin >> choice;

		if (choice >= 0 && choice <= 5)
			rv = choice;
		else
			rv = -1;

        cout << endl;
        cin.ignore(2000, '\n'); // clear input buffer
		return rv;
	}

	void AidApp::loadRecs() {
        int readIndex = 0;
        char id;
        datafile_.open(filename_, ios::in); // open a file to read

        if (datafile_.fail()) { // if the file does not exist
            datafile_.clear();
            datafile_.close();
            datafile_.open(filename_, ios::out); // create a new file
            datafile_.close();
        } else { // if the file exists

            do {
                //delete [] product_[readIndex]; // deallocate memory
                datafile_ >> id;

                if (!datafile_.fail()) {

                    if (id == 'P') {
                        product_[readIndex] = new AmaPerishable;
                    }
                    else if (id == 'N') {
                        product_[readIndex] = new AmaProduct;
                    }

                    if (id == 'P' || id == 'N') {
                        datafile_.ignore(); // skip the comma
                        product_[readIndex]->load(datafile_);
                        readIndex++;
                    }

                }

            } while (!datafile_.fail());
            noOfProducts_ = readIndex;
            datafile_.close();
        }
	}

	void AidApp::saveRecs() {
        datafile_.open(filename_, ios::out); // open a file to write
        for (int i = 0; i < noOfProducts_; i++) {
            product_[i]->store(datafile_);
        }
        datafile_.close();
	}

    void AidApp::listProducts()const {
        double total = 0;

        cout << " Row | SKU    | Product Name       | Cost  | QTY| Unit     |Need| Expiry   " << endl;
        cout << "-----|--------|--------------------|-------|----|----------|----|----------" << endl;

        for (int i = 0; i < noOfProducts_; i++) {
            cout << setw(4) << right << i + 1 << " | ";
            cout.unsetf(ios::right);
            //product_[i]->write(cout, true);
            cout << *product_[i] << endl;

            total += *product_[i];

            if ((i + 1) % 10 == 0)
                pause();
        }

        cout << "---------------------------------------------------------------------------" << endl;
        cout << "Total cost of support: $" << fixed << setprecision(2) << total << endl << endl;
    }

    int AidApp::SearchProducts(const char* sku)const {
        int index = -1;
        for (int i = 0; i < noOfProducts_ && index == -1; i++) {
            if (*product_[i] == sku)
                index = i;
        }
        return index;
    }

    void AidApp::addQty(const char* sku) { // update quantity
        int index = SearchProducts(sku);
        int amount, amountLeft;

        if (index == -1){
            cout << "Not found!" << endl;
        } else {
            product_[index]->write(cout, false);
            cout << endl << endl;
            cout << "Please enter the number of purchased items: ";
            cin >> amount;
            cout << endl;

            if (cin.fail()) {
                cout << "Invalid quantity value!" << endl;
                cin.clear();
            } else {
                amountLeft = product_[index]->qtyNeeded() - product_[index]->quantity();

                if (amount <= amountLeft) {
                    *product_[index] += amount;
                } else {
                    cout << "Too many items; only ";
                    cout << amountLeft;
                    cout << " is needed, please return the extra ";
                    cout << amount - amountLeft;
                    cout << " items." << endl << endl;
                    amount = amountLeft;
                    *product_[index] += amount;
                }

                saveRecs();
                cout << "Updated!" << endl << endl;
                cin.ignore(2000, '\n'); // clear input buffer
            }
        }
    }

    void AidApp::addProduct(bool isPerishable) {
        if (isPerishable) {
            AmaPerishable p_product;
            cin >> p_product;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(2000, '\n'); // clear input buffer
                cout << endl << p_product << endl << endl;
            } else {
                product_[noOfProducts_] = &p_product;
                noOfProducts_++;
                saveRecs();
                cout << endl << "Product added" << endl << endl;
            }

        } else {
            AmaProduct n_product;
            cin >> n_product;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(2000, '\n'); // clear input buffer
                cout << endl << n_product << endl << endl;
            } else {
                product_[noOfProducts_] = &n_product;
                noOfProducts_++;
                saveRecs();
                cout << endl << "Product added" << endl << endl;
            }

        }
    }
    int AidApp::run() {
        bool exit = false;
        int choice, index;
        char sku[MAX_SKU_LEN + 1];

        while (!exit) {
            choice = menu();

            switch (choice) {
            case 1:
                listProducts();
                pause();
                break;
            case 2:
                cout << "Please enter the SKU: ";
                cin >> sku;
                cin.ignore(2000, '\n'); // clear input buffer
                cout << endl;
                index = SearchProducts(sku);

                if (index == -1)
                    cout << "Not found!";
                else
                    product_[index]->write(cout, false);

                cout << endl << endl;
                pause();
                break;
            case 3:
                addProduct(false);
                loadRecs();
                break;
            case 4:
                addProduct(true);
                loadRecs();
                break;
            case 5:
                cout << "Please enter the SKU: ";
                cin >> sku;
                cout << endl;
                addQty(sku);
                break;
            case 0:
                exit = true;
                cout << "Goodbye!!" << endl;
                break;
            default:
                cout << "===Invalid Selection, try again.===" << endl;
            }
        }

        return 0;
    }
}






