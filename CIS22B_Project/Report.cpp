#include "Report.h"

Report::Report(BookList* pBl) {
	booksOriginal = pBl;
}

Report::~Report() {
	if (booksOriginal != nullptr) {
		delete booksOriginal;
		booksOriginal = nullptr;
	}

	if (printBooks != nullptr) {
		delete printBooks;
		printBooks = nullptr;
	}
}

void Report::printReport(int input) {
	switch (input) {
	case 2: {
		printBooks = new ISBNList(*booksOriginal);
		printBooks->sortBooks();
		double totalWholesaleValue = printBooks->printWholesaleValue();
		std::cout << "The total wholesale value for all the books in the inventory is: " << totalWholesaleValue << std::endl;
		delete printBooks;
		break;
	}
	case 3: {
		printBooks = new ISBNList(*booksOriginal);
		printBooks->sortBooks();
		double totalRetailValue = printBooks->printRetailValue();
		std::cout << "The total retail value for all the books in the inventory is: " << totalRetailValue << std::endl;
		delete printBooks;
		break;
	}
	default: {
		switch (input) {
		case 1: {
			printBooks = new ISBNList(*booksOriginal);
			break;
		}
		case 4: {
			printBooks = new QuantityList(*booksOriginal);
			break;
		}
		case 5: {
			printBooks = new PriceList(*booksOriginal);
			break;
		}
		case 6: {
			printBooks = new AgeList(*booksOriginal);
			break;
		}
		default: {
			throw "Wrong input";
		}
		}

		printBooks->sortBooks();
		printBooks->printBooks();
		delete printBooks;
		printBooks = nullptr;
	}
	}
}