/*
 AidApp.h
 Name: Yuansheng Lu
 Student ID: 136654167
 E-mail: ylu140@myseneca.ca
*/
#ifndef SICT_AIDAPP_H__
#define SICT_AIDAPP_H__

#include "AmaPerishable.h"
#include <fstream>

namespace sict {
	class AidApp {
		char filename_[256];
		Product* product_[MAX_NO_RECS];
		std::fstream datafile_;
		int noOfProducts_;
		// private function
		void pause()const;
		int menu();
		void loadRecs();
		void saveRecs();
		void listProducts()const;
		int SearchProducts(const char* sku)const;
		void addQty(const char* sku);
		void addProduct(bool isPerishable);
	public:
		AidApp();
		AidApp(const char* filename);
		AidApp(const AidApp& app) = delete; // prevent copy constructor
		AidApp& operator=(const AidApp& app) = delete; // prevent copy assignment operator
		int run();
	};

}

#endif
