#define _CRT_SECURE_NO_WARNINGS

#include "Report.h"

/*
One argument constructor that passes in a pointer to the BookList class.
*/
Report::Report(BookList *pBl) {
	booksOriginal = pBl;	//copies the address of a pointer to a BookList class
}

/*
Destructor to delete the objects printBooks.
*/
Report::~Report() {
	if (printBooks != nullptr) {	//if printBooks exists
		delete printBooks;			//delete printBooks
		printBooks = nullptr;
	}
}

/*
Function to print various reports when asked by the user.
Switch statment to print each report based on the user's choice
If the user enters 1, the books are first sorted by ISBN and then the inventory list of all the books' information is printed.
If the user enters 2, all the books are first sorted by ISBN and then the books' wholesale costs are printed followed by the total wholesale cost.
If the user enters 3, all the books are first storted by ISBN and then the books' retail prices are printed followed by the total retail price.
If the user enters 4, all the books are first sorted by quantity and then printed from greatest to least quantity.
If the user enters 5, all the books are first sorted by wholesale cost and then printed from greatest to least wholesale cost.
If the user enters 6, all the books are first sorted by age and then printed from the book which was in the inventory the longest to the book which was in the inventory the shortest.
If the user enters in a different number/character, the program throws an error message for wrong input.
*/
void Report::printReport(int input) {
	switch (input) {
	case 2: {
		printBooks = new ISBNList(*booksOriginal);	//create an ISBNList object
		std::cout << "Num books " << booksOriginal->getSize() << " " << printBooks->getSize() << std::endl;
		printBooks->sortBooks();	//sort the books by ISBN
		double totalWholesaleValue = printBooks->printWholesaleValue();	//print the wholesale costs for all the books
		std::cout << "The total wholesale value for all the books in the inventory is: " << totalWholesaleValue << std::endl;
		delete printBooks;
		printBooks = nullptr;
		break;
	}
	case 3: {
		printBooks = new ISBNList(*booksOriginal);	//create an ISBNList object
		printBooks->sortBooks();		//sort the books by ISBN	
		double totalRetailValue = printBooks->printRetailValue();	//print the retail prices for all the books
		std::cout << "The total retail value for all the books in the inventory is: " << totalRetailValue << std::endl;
		delete printBooks;
		printBooks = nullptr;
		break;
	}
	default: {
		switch (input) {
		case 1: {
			printBooks = new ISBNList(*booksOriginal);	//create an ISBNList object
			break;
		}
		case 4: {
			printBooks = new QuantityList(*booksOriginal);	//create a QuantityList object
			break;
		}
		case 5: {
			printBooks = new CostList(*booksOriginal);	//create a CostList object
			break;
		}
		case 6: {
			printBooks = new AgeList(*booksOriginal);	//create an AgeList object
			break;
		}
		default: {
			throw "Wrong input";	//throw an error message for wrong input
		}
		}

		printBooks->sortBooks();	//sort all the books based on whether the object is an ISBNList, QuantityList, CostList, or an AgeList.
		printBooks->printBooks();	//print all the books based on greatest to least ISBN, Quantity, Cost, or Age
		delete printBooks;			//delete the printBooks object
		printBooks = nullptr;
	}
	}
}