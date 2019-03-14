#include <iostream>
#include <string>
#include "Report.h"
#include "AgeList.h"
#include "QuantityList.h"
#include "CostList.h"
void printReport(int input) {
	switch (input) {

	case 1: {
		BookList *list = new BookList(getBooks(), getSize());
		list->printBooks();
		delete list;
		break;
	}
	case 2: {
		BookList *wholesale = new BookList(getBooks(), getSize());
		double totalWholesaleValue = wholesale->printWholesaleValue();
		std::cout << "The total wholesale value for all the books in the inventory is: " << totalWholesaleValue << std::endl;
		delete wholesale;
		break;
	}
	case 3: {
		BookList *retail = new BookList(getBooks(), getSize());
		double totalRetailValue = retail->printRetailValue();
		std::cout << "The total retail value for all the books in the inventory is: " << totalRetailValue << std::endl;
		delete retail;
		break;
	}
	case 4: {
		BookList *byQuant = new QuantityList(getBooks(), getSize());
		byQuant->sortBooks();
		byQuant->printBooks();
		delete byQuant;
		break;
	}
	case 5: {
		BookList *byCost = new CostList(getBooks(), getSize());
		byCost->sortBooks();
		byCost->printBooks();
		delete byCost;
		break;
	}
	case 6: {
		BookList *byAge = new AgeList(getBooks(), getSize());
		byAge->sortBooks();
		byAge->printBooks();
		delete byAge;
		break;
	}
}