#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include "Report.h"
#include "Cashier.h"
#include "Inventory.h"

using namespace std;

enum moduleType { kMenu, kCashier, kInventory, kReport, kExit };
enum CashierMenu { kCashMenu, kCashAdd, kCashRemove, kCashReview, kCashExit, kCashExitProgram };
enum InventoryMenu {kInvMenu, kInvLookUp, kInvExit, kInvExitProgram, kInvEnterAdmin, kSaveInventory, kInvAddBook, kInvBookDisplay};

const string adminPass = "thisIsNotAPassword";

int getData(string, BookList&);

int main() {
	int moduleState = kMenu;
	string fileName = "booklist.csv";

	ISBNList bl;
	cout << getData(fileName, bl) << endl << endl;

//	cout << bl.getSize();
	cout << "Welcome to Serendipity Booksellers!\n";

	//ISBNList blCopy = bl;
	//blCopy.printBooks();

	while (moduleState != kExit) {
		switch (moduleState) {
		case kMenu: {
			int moduleInput;
			cout << "\nPlease select one of the following:\n";
			cout << "1: Cashier\n"
				<< "2: Inventory Database\n"
				<< "3: Report\n"
				<< "4: Exit\n";
			std::cin >> moduleInput;
			if ((moduleInput < 1) || (moduleInput > 4)) {
				cout << "Please enter a number between 1 and 4";
				moduleState = kMenu;
			}
			else {
				moduleState = moduleInput;
			}
			break;
		}
		case kCashier: {
			Cashier cashier = Cashier(&bl); //declares cashier1 object
			unsigned long long int CInputISBN; //local variable for input with class Cashier
			int cashierMainMenuChoice; //for main menu choices
			int cashState = kCashMenu;
			int yesOrNo; //to continue the program
			int quantityOfBook; //number of books entered
			cout << fixed << setprecision(2);

			while (moduleState == kCashier) {
				switch (cashState)
				{
				case kCashMenu: {
					cout << "\nCash Register Main Menu" << endl;
					cout << "Enter a number from the menu to continue" << endl;
					cout << kCashAdd << ". Add a book to the cart" << endl;
					cout << kCashRemove << ". Remove a book from the cart" << endl;
					cout << kCashReview << ". Review the cart and finish the purchase" << endl;
					cout << kCashExit << ". Exit the Cashier" << endl;
					cout << kCashExitProgram << ". Exit the program" << endl;
					std::cin >> cashierMainMenuChoice;

					while (cashierMainMenuChoice > 5 || cashierMainMenuChoice < 1)
					{
						cout << "Error, invalid menu choice. Please enter a new number" << endl;
						std::cin >> cashierMainMenuChoice;
					}
					cashState = cashierMainMenuChoice;
					break;
				}
				case kCashAdd:
				{
						try {
							std::cout << "Adding a book to the cart" << endl;
							std::cout << "Enter the ISBN of the book. Do not use dashes." << endl;
							std::cin >> CInputISBN;
							cashier.setInputISBN(CInputISBN);
							std::cout << "Enter The quantity of the book you would like to add" << endl;
							std::cin >> quantityOfBook;

							cashier.ISBNArrayAdd(CInputISBN, quantityOfBook);
						}
						catch (Cashier::isbnDoesNotExistException) {
							std::cout << " Error: Book does not exist." << endl;
						}
						catch (Cashier::notEnoughInStockException) {
							std::cout << "Not enough books in stock." << endl;
						}
						std::cout << "Would you like to add another book? Enter the number from the menu " << endl;
						std::cout << "1. Yes" << endl;
						std::cout << "2. No" << endl;
						std::cin >> yesOrNo;

						while ((yesOrNo < 0) || (yesOrNo > 2)) {
							std::cout << "Wrong input. Would you like to add another book? Enter the number from the menu " << endl;
							std::cout << "1. Yes" << endl;
							std::cout << "2. No" << endl;
							std::cin >> yesOrNo;
						}

						if (yesOrNo == 1) {
							cashState = kCashAdd;
						}
						else {
							cashState = kCashMenu;
						}
					break;
				}
				case kCashRemove:
				{
					try {

						cout << "Removing a book from the cart" << endl;
						cout << "Enter the ISBN of the book. Do not use dashes." << endl;
						std::cin >> CInputISBN;
						cout << "Enter The quantity of the book you would like to remove" << endl;
						std::cin >> quantityOfBook;

						cashier.removeFromCart(CInputISBN, quantityOfBook);
					}
					catch (Cashier::isbnDoesNotExistException) {
						cout << "Error: Book is not in cart\n";
					}
					catch (Cashier::negativeQtyException) {
						cout << "Error: Too many books subtracted\n";
					}
					cout << "Would you like to remove another book? Enter the number from the menu " << endl;
					cout << "1. Yes" << endl;
					cout << "2. No" << endl;
					std::cin >> yesOrNo;

					while ((yesOrNo < 0) || (yesOrNo > 2)) {
							std::cout << "Wrong input. Would you like to add another book? Enter the number from the menu " << endl;
							std::cout << "1. Yes" << endl;
							std::cout << "2. No" << endl;
							std::cin >> yesOrNo;
					}

						if (yesOrNo == 1) {
							cashState = kCashRemove;
						}
						else {
							cashState = kCashMenu;
						}
					break;
				}
				case kCashReview:
				{
					cout << "Here is the current cart" << endl;
					cout << left << setw(10) << "Quantity" << left << setw(10) << "Name" << left << setw(10) << "ISBN";
					cout << left << setw(10) << "Price" << left << setw(10) << "Total" << endl;
					cout << "----------------------------------------------------------------" << endl;
					cashier.printCart();
					cout << "----------------------------------------------------------------" << endl;
					cout << left << setw(40) << "Subtotal" << left << "$" << cashier.getSubTotal() << endl;
					cout << left << setw(40) << "Tax(9%)" << left << "$" << cashier.getSalesTax() << endl;
					cout << left << setw(40) << "Total" << left << "$" << cashier.getSubTotal() + cashier.getSalesTax() << endl;


					cout << "Enter a number from the following menu to continue." << endl;
					cout << "1. Confirm Checkout and purchase order" << endl;
					cout << "2. Return to previous menu and edit the cart" << endl;
					std::cin >> yesOrNo;
					if (yesOrNo == 1) {
						cashier.updateInventory(fileName);
						cashState = kCashExit;
					}
					else {
						cashState = kCashMenu;
					}
					break;
				}
				case kCashExit:
				{
					cout << "Exiting the Cashier" << endl;
					moduleState = kMenu;
					break;
				}
				case kCashExitProgram:
				{
					moduleState = kExit;
				}
				}
			}


			break;
		}
		case kInventory: { // finish this
			cout << "Am in Inventory" << endl;
			int invState = kInvMenu;
			int isAdmin = false;
			int invModeInput = 0;
			Book bookLookedUp;
			Inventory inventory = Inventory(&bl);

			while (moduleState == kInventory) {
				switch (invState) {
				case kInvMenu: {
					int range = 4;
					cout << setw(20) << "\nWelcome to the Inventory Menu" << endl << endl;
					cout << left
						<< "Please select the following options:\n" << endl
						<< kInvLookUp << ": Look up a Book" << endl;
					if (!isAdmin) {
						cout << kInvExit << ": Return to Module Menu" << endl
							<< kInvExitProgram << ": Exit Program" << endl
							<< kInvEnterAdmin << ": Enter Admin Mode" << endl;
					}
					else {
						cout << "2: Add a book" << endl
							<< "3: Save Inventory" << endl
							<< "4: Return to Module Menu" << endl
							<< "5: Exit Program" << endl;
						range = 5;
					}
					cout << "Enter Your Choice: ";
					std::cin >> invModeInput;
					if ((invModeInput < 1) || (invModeInput > range)) {
						cout << "Please enter a valid input." << endl;
					}
					else {
						invState = invModeInput;
						if (isAdmin && (invState == 2)) {
							invState = kInvAddBook;
						}
						else if (isAdmin && (invState == 3)) {
							invState = kSaveInventory;
						}
						else if (isAdmin && (invState == 4)) {
							invState = kInvExit;
						}
						else if (isAdmin && (invState == 5)) {
							invState = kInvExitProgram;
						}


					}
					break;
				}
				case kInvLookUp: {
					int lookUpNumber;
					bool bookExists = false;

					cout << "Select a search option:\n"
						<< "1: ISBN\n"
						<< "2: Book Title\n"
						<< "3: Author\n"
						<< "4: Exit\n";
					std::cin >> lookUpNumber;
					while ((lookUpNumber < 1) || (lookUpNumber > 4)) {
						cout << "Please enter a valid number from above.\n";
						std::cin >> lookUpNumber;
					}
					try {
						switch (lookUpNumber) {
						case 1: {
							int isbnSearch;
							cout << "Please enter the ISBN of the book you want to search. No dashes.\n";
							std::cin >> isbnSearch;
							bookLookedUp = inventory.lookUpISBN(isbnSearch);

							invState = kInvBookDisplay;
							break;
						}
						case 2: {
							string bookTitle;
							cout << "Please enter the title of the book you want to search.\n";
							std::cin.ignore();
							std::getline(std::cin, bookTitle);
							bookLookedUp = inventory.lookUpTitle(bookTitle);

							invState = kInvBookDisplay;
							break;
						}
						case 3: {
							string author;
							cout << "Please enter the author of the book you want to search.\n";
							std::cin.ignore();
							std::getline(std::cin, author);
							bookLookedUp = inventory.lookUpAuthor(author);

							invState = kInvBookDisplay;
							break;
						}
						case 4: {
							invState = kInvMenu;
							break;
						}
						default: {
							cout << "Invalid input";
						}
						}

					}
					catch (Inventory::bookDoesNotExistException) {
						cout << "Book does not exit" << endl;
						invState = kInvLookUp;
					}
					break;
				}
				case kInvExit: {
					moduleState = kMenu; 
					break;
				}
				case kInvExitProgram: {
					moduleState = kExit;
					break;
				}
				case kInvEnterAdmin: {
					string passInput;
					cout << "Enter a password to enter admin mode, or press 0 to exit\n";
					std::cin >> passInput;
					if (passInput == adminPass) {
						isAdmin = true;
						invState = kMenu;
					}
					else if (passInput == "0") {
						invState = kMenu;
					}
					break;
				}
				case kSaveInventory: {
					inventory.saveBookInventory(fileName);

					cout << "Saved in file " << fileName << endl;
					invState = kInvMenu;
					break;
				}
				case kInvAddBook: {
					try {
						inventory.addBook();
						cout << "Book has been added.\n";
					}
					catch (Inventory::bookAlreadyExistsException) {
						cout << "This book already exists. Please edit from looking it up on the inventory list." << endl;
					}

					invState = kInvMenu;
					break;
				}
				case kInvBookDisplay: {
					cout << bookLookedUp;

					if (isAdmin) {
						inventory.editBook(bookLookedUp);
					}
					invState = kInvLookUp;
				}
				}
			}

			break;
		}
		case kReport: {
			int userReportInput;
			cout << "\nEnter which report you would like printed on the screen:\n"
				<< "1: The inventory list\n"
				<< "2: The wholesale cost report\n"
				<< "3: The retail price report\n"
				<< "4: The inventory list based on quantity\n"
				<< "5: The inventory list based on cost\n"
				<< "6: The inventory list based on age\n"
				<< "7: Exit the Inventory Report\n"
				<< "8: Exit the program\n";
			std::cin >> userReportInput;
			switch (userReportInput) {
			case 7:
				moduleState = kMenu;
				break;
			case 8:
				moduleState = kExit;
				break;
			default:
				if ((userReportInput < 1) || (userReportInput > 8)) {
					cout << "Please enter a number between 1 and 8.\n";
				}
				else {
					Report rp = Report(&bl);
					rp.printReport(userReportInput);
				}
				moduleState = kReport;
			}
			break;
		}
		case kExit: {
			cout << "Exiting" << endl;
			moduleState = kExit;

			break;
		}
		default:
			cout << "There was an error in modules.\n";
			moduleState = kExit;
		}
	}

	cout << endl << endl << "Press Enter to Exit\n";
	cin.ignore();
	cin.get();
	return 0;
}

int getData(string inputFileName, BookList &bl) {
	ifstream inFile;			// input file to read string from
	int index = 0;
	inFile.open(inputFileName);
	if (inFile.good()) {
		string line;

		cout << inputFileName << endl;
		// while index is less than the maximum number of words
		while (getline(inFile, line)) {
			//			cout << line << endl << endl;
			Book b;
			unsigned long long isbn = stoull(line.substr(0, line.find(',')));
			line = line.substr(line.find(',') + 1);
			string title = line.substr(0, line.find(','));
			line = line.substr(line.find(',') + 1);
			string author = line.substr(0, line.find(','));
			line = line.substr(line.find(',') + 1);
			string publisher = line.substr(0, line.find(','));
			line = line.substr(line.find(',') + 1);
			string date = line.substr(0, line.find(','));
			line = line.substr(line.find(',') + 1);
			int qty = stoi(line.substr(0, line.find(',')));
			line = line.substr(line.find(',') + 1);
			double cost = stod(line.substr(0, line.find(',')));
			line = line.substr(line.find(',') + 1);
			double retail = stod(line.substr(0, line.find(',' + 1)));


			b.setISBN(isbn);
			b.setTitle(title);
			b.setAuthor(author);
			b.setPublish(publisher);
			b.setDateAdd(date);
			b.setQuantity(qty);
			b.setWholeSale(cost);
			b.setRetail(retail);

			bl.addBook(b);
			index++;
		}
	}
	return index;
}
