#define _CRT_SECURE_NO_WARNINGS

#include "Report.h"

/*
One argument constructor that passes in a pointer to the BookList class.
*/
Report::Report(BookList *pBl) {
	booksOriginal = pBl;	//copies the address of a pointer to a BookList class
	printBooks = nullptr;
}

/*
Destructor to delete the objects printBooks.
*/
Report::~Report() {
	if (printBooks != nullptr) {	//if printBooks exists
		delete printBooks;			//delete printBooks
		printBooks = nullptr;		//make the address of printBooks as null
	}
}

/*
Function to print various reports when asked by the user.
Switch statment to print each report based on the user's choice
If the user enters 2
	An array of books sorted by ISBN is created using the original array of books
	The size of the original array and the size of the ISBNList is printed onto the screen
	all the books are first sorted by ISBN 
	the books' wholesale costs are printed by calling the printWholesaleValue() function which is located in the base class
	Then the total wholesale cost is printed.
	The ISBNList is deleted and the address is set to null
If the user enters 3
	An array of books sorted by ISBN is created using the original array of books
	all the books are first sorted by ISBN
	the books' retail prices are printed by calling the printRetailValue() function which is located in the base class
	Then the total retail price is printed.
	The ISBNList is deleted and the address is set to null
The default condition is:
	If the user enters 1
	An array of books sorted by ISBN is created using the original array of books
	If the user enters 4
	An array of books sorted by quantity is created using the original array of books
	If the user enters 5
	An array of books sorted by wholesale cost is created using the original array of books
	If the user enters 6
	An array of books sorted by age is created using the original array of books
	If the user enters in a different number/character
		the program throws an error message for wrong input.
	The books are sorted based on whether the object is an ISBNList, QuantityList, CostList, or AgeList
	The books are printed based on whether the object is an ISBNList, QuantityList, CostList, or AgeList
	The object is deleted and the address is set to null.
*/
void Report::printReport(int input) {
	switch (input) {
	case 2: {
		printBooks = new ISBNList(*booksOriginal);	//create an ISBNList object
		//the size of the original array and the size of the ISBNList is printed on the screen
		printBooks->sortBooks();	//sort the books by ISBN
		double totalWholesaleValue = printBooks->printWholesaleValue();	//print the wholesale costs for all the books
		//print the total wholesale cost
		std::cout << "The total wholesale value for all the books in the inventory is: " << totalWholesaleValue << std::endl;
		//delete the ISBNList and set the address to null
		delete printBooks;
		printBooks = nullptr;
		break;
	}
	case 3: {
		printBooks = new ISBNList(*booksOriginal);	//create an ISBNList object
		printBooks->sortBooks();		//sort the books by ISBN	
		double totalRetailValue = printBooks->printRetailValue();	//print the retail prices for all the books
		//print the total retail price
		std::cout << "The total retail value for all the books in the inventory is: " << totalRetailValue << std::endl;
		//delete the ISBNList and set the address to null
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
		printBooks->printBooks();	//print all the books based on whether the object is an ISBNList, QuantityList, CostList, or an AgeList.
		delete printBooks;			//delete the printBooks object
		printBooks = nullptr;		//set the object's address to null
	}
	}
}