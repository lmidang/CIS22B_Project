#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include "Report.h"
#include "Cashier.h"
#include "Inventory.h"

using namespace std;

// enum for the state of the module or each individual module
enum moduleType { kMenu, kCashier, kInventory, kReport, kExit };
enum CashierMenu { kCashMenu, kCashAdd, kCashRemove, kCashReview, kCashExit, kCashExitProgram };
enum InventoryMenu {kInvMenu, kInvLookUp, kInvExit, kInvExitProgram, 
	kInvEnterAdmin, kSaveInventory, kInvAddBook, kInvBookDisplay};

// password to enter admin mode
const string adminPass = "thisIsNotAPassword";

// function to pull data from the file to the booklist object
int getData(string, BookList&);

/**
* Main function
*
set moduleState to kMenu
set fileName to "booklist.csv"
set numBooks to the number returned from reading the file
if numBooks less than 1
	exit the program after notifying the user
while moduleState is not kExit
	case moduleState is kMenu
		print out options for the user
		read in the input to moduleInput
	case moduleState is kCashier
		create cashier object
		set cashState to kCashMenu

		while moduleState is kCashier
			case cashState is kCashMenu
				displays cashier menu
				receives userInput
				while userInput is not in range keep asking for a number
				set cashState to userInput
			case cashState is kCashAdd
				try
					receiving CInputISBN from user
					receiving the quantity from the user
					adding the variables to cart
				catch exception that isbn doesn't exit
				catch exception that not enough books are in stock
				ask user to continue
				continues asking if the input is not within range
				if user wants to continue keep cashState in kCashAdd
				else set cashState to kCashMenu
			case cashstate is kCashRemove
				try
					receiving CInputISBN from the user
					receiving quantity
					removing the book from cart accordingly
				catch exception isbn doesnt exist
				catch exception too many books subtracted
				asks the user if continue remove
				if yes cashState stays as kCashRemove
				else set cashState to kCashMenu
			case cashState is kCashReview
				prints list of books in cart, subtotal, sales tax and total
				confirm purchase from user (yes or no)
				if yes updateInventory and setCashState to kCashExit
				else setCashState to kCashMenu
			case cashState is kCashExit
				set moduleState to kMenu
			case cashState is kCashExitProgram
				set moduleState to kExit
	case moduleState is kInventory
		set invState to kInvMenu
		set isAdmin to false
		set invModeInput = 0
		create inventory object
		
		while moduleState is kInventory
			case cashState is kInvMenu
				display menu options for non-admin or admin
				checks of the input is not within range
				else
					set invState to invModeInput
					for admin sets invState according to the menu displayed
			case invState is kInvLookUp
				set bookExists to false
				displays search options
				keeps asking user for input in range
				try
					case lookUpNumber is 1
						takes in integer
						sets bookLookedUp to book returned by inventory lookUpISBN
						sets invState to kBookDisplay
					case lookUpNumber is 2
						takes string booktitle
						sets bookLookedUp to book returned by inventory lookUpTitle
						sets invState to kBookDisplay
					case lookUpNumber is 3
						takes string author
						sets bookLookedUp to book returned by inventory lookUpAuthor
						set invState to kBookDisplay
					case lookUpNumber is 4, sets invState to kInvMenu
					case default: print invalid
				catch exception that book doesn't exist
					set invState to kInvLookUp
			case invState is kInvExit
				set moduleState to kMenu
			case invState is kInvExitProgram
				set mdoeulState to kExit
			case invState is kInvEnterAdmin
				receives passInput
				if passWord is right, set isAdmin to true
				else, set invState to kMenu
			case invState is kSaveInventory
				saves database from inventory to file
				sets invState to kMenu
			case invState is kInvAddBook
				try adding book from inventory
				catch if book already exists, notify the user to check the lookup
			case invState is kInvBookDisplay
				print the bookLookedUp
				if user is admin, editBook through inventory
				set invState kInvLookUp 
	case moduleState is kReport
		display Report menu options
		receives user input
		case userReportInput is 7
			set moduleState to kMenu
		case userReportInput is 8
			setModuleState to kExit
		case default
			if userReportInput is not within range
				notify the user
			else
				create Report object
				prints from the object according to user input
	case default
		set moduleState to kMenu

	asks for user to press enter before leaving	
*/
int main() {
	int moduleState = kMenu;
	string fileName = "booklist.csv";	// file containing the books

	ISBNList bl;
	// check if there are any books and if there are none display an error and leave
	int numBooks = getData(fileName, bl);
	if (numBooks < 1) {
		cout << "Problem reading the inventory file. Press enter to exit the program\n";
		cin.get();
		return 0;
	}

	cout << "Welcome to Serendipity Booksellers!\n";

	// while moduleState is not kExit
	while (moduleState != kExit) {
		switch (moduleState) {

		case kMenu: {
			int moduleInput;	// displays module menu options
			cout << "\nPlease select one of the following:\n";
			cout << "1: Cashier\n"
				<< "2: Inventory Database\n"
				<< "3: Report\n"
				<< "4: Exit\n";
			std::cin >> moduleInput;
			moduleState = moduleInput;
			break;
		}
		case kCashier: {
			Cashier cashier = Cashier(&bl); //declares cashier1 object
			std::string CInputISBN; //local variable for input with class Cashier
			int cashierMainMenuChoice; //for main menu choices
			int cashState = kCashMenu;
			int yesOrNo; //to continue the program
			int quantityOfBook; //number of books entered
			cout << fixed << setprecision(2);

			while (moduleState == kCashier) {
				switch (cashState)
				{
				case kCashMenu: {
					// displays cashier menu options
					cout << "\nCash Register Main Menu" << endl;
					cout << "Enter a number from the menu to continue" << endl;
					cout << kCashAdd << ". Add a book to the cart" << endl;
					cout << kCashRemove << ". Remove a book from the cart" << endl;
					cout << kCashReview << ". Review the cart and finish the purchase" << endl;
					cout << kCashExit << ". Exit the Cashier" << endl;
					cout << kCashExitProgram << ". Exit the Program" << endl;
					std::cin >> cashierMainMenuChoice;

					// checking for good input
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
							// add book into card according to user input
							std::cout << "Adding a book to the cart" << endl;
							std::cout << "Enter the ISBN of the book. Do not use dashes." << endl;
							std::cin >> CInputISBN;
							cashier.setInputISBN(CInputISBN);
							std::cout << "Enter The quantity of the book you would like to add" << endl;
							std::cin >> quantityOfBook;

							cashier.addToCart(CInputISBN, quantityOfBook);
						}
						catch (Cashier::isbnDoesNotExistException) {	// inform user if isbn entered doesn't exist
							std::cout << " Error: Book does not exist." << endl;
						}
						catch (Cashier::notEnoughInStockException) {	// infrom use in not enough books in stock
							std::cout << "Not enough books in stock." << endl;
						}

						// asking user for continuity 
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
						// receives input isbn from user and removes the book from cart
						cout << "Removing a book from the cart" << endl;
						cout << "Enter the ISBN of the book. Do not use dashes." << endl;
						std::cin >> CInputISBN;
						cout << "Enter The quantity of the book you would like to remove" << endl;
						std::cin >> quantityOfBook;

						cashier.removeFromCart(CInputISBN, quantityOfBook);
					}
					// if isbn doesn't exist
					catch (Cashier::isbnDoesNotExistException) {
						cout << "Error: Book is not in cart\n";
					}
					// if too many books are subtracted
					catch (Cashier::negativeQtyException) {
						cout << "Error: Too many books subtracted\n";
					}

					// asks user for continuity
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
					// dispalys what's in cart, price, subtotal, tax, and total
					cout << "Here is the current cart" << endl;
					cout << left << setw(20) << "Quantity" << left << setw(20) << "ISBN" << left << setw(40) << "Name";
					cout << left << setw(20) << "Price" << left << setw(20) << "Total" << endl;
					cout << "--------------------------------------------------------------------------------------";
					cout << "--------------------" <<endl;
					cashier.printCart();
					cout << "--------------------------------------------------------------------------------------";
					cout << "--------------------" << endl;
					cout << left << setw(80) << "Subtotal" << left << "$" << cashier.getSubTotal() << endl;
					cout << left << setw(80) << "Tax(9%)" << left << "$" << cashier.getSalesTax() << endl;
					cout << left << setw(80) << "Total" << left << "$" << cashier.getSubTotal() + cashier.getSalesTax() << endl;

					// asks if user would like to purchase order
					cout << "Enter a number from the following menu to continue." << endl;
					cout << "1. Confirm Checkout and purchase order" << endl;
					cout << "2. Return to previous menu and edit the cart" << endl;
					std::cin >> yesOrNo;
					if (yesOrNo == 1) {	// if yes update database through cashier and cashState set to kCashExit
						cashier.updateInventory(fileName);
						cashState = kCashExit;
					}
					else {
						// if not return to kCashMenu
						cashState = kCashMenu;
					}
					break;
				}
				case kCashExit:
				{
					// return to module menu
					cout << "Exiting the Cashier" << endl;
					moduleState = kMenu;
					break;
				}
				case kCashExitProgram:
				{
					// exit the program
					moduleState = kExit;
				}
				}
			}


			break;
		}
		case kInventory: {
			int invState = kInvMenu;	// inventory menu state
			int isAdmin = false;		// if user is admin
			int invModeInput = 0;		// inputModule = 0
			Book bookLookedUp;			// book looked up
			Inventory inventory = Inventory(&bl);

			while (moduleState == kInventory) {
				switch (invState) {
				case kInvMenu: {
					int range = 4;	// range for user input

					// displays options for user input for inventory
					cout << setw(20) << "\nWelcome to the Inventory Menu" << endl << endl;
					cout << left
						<< "Please select the following options:\n" << endl
						<< kInvLookUp << ": Look up a Book" << endl;
					if (!isAdmin) {	// display less options if not admin
						cout << kInvExit << ": Return to Module Menu" << endl
							<< kInvExitProgram << ": Exit Program" << endl
							<< kInvEnterAdmin << ": Enter Admin Mode" << endl;
					}
					else {	// dispay more options if admin
						cout << "2: Add a book" << endl
							<< "3: Save Inventory" << endl
							<< "4: Return to Module Menu" << endl
							<< "5: Exit Program" << endl;
						range = 5;
					}
					cout << "Enter Your Choice: ";
					std::cin >> invModeInput;
					
					// checks if user input is within range
					if ((invModeInput < 1) || (invModeInput > range)) {
						cout << "Please enter a valid input." << endl;
					}
					else {
						invState = invModeInput;

						// for user admin, assign invState according to input
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
					
					// display search option
					cout << "Select a search option:\n"
						<< "1: ISBN\n"
						<< "2: Book Title\n"
						<< "3: Author\n"
						<< "4: Exit\n";
					std::cin >> lookUpNumber;

					// checks if input is valid
					while ((lookUpNumber < 1) || (lookUpNumber > 4)) {
						cout << "Please enter a valid number from above.\n";
						std::cin >> lookUpNumber;
					}
					try {
						switch (lookUpNumber) {
						case 1: {	// search for book by isbn
							std::string isbnSearch;
							cout << "Please enter the ISBN of the book you want to search. No dashes.\n";
							std::cin >> isbnSearch;
							bookLookedUp = inventory.lookUpISBN(isbnSearch);

							invState = kInvBookDisplay;
							break;
						}
						case 2: {	// search for book by title
							string bookTitle;
							cout << "Please enter the title of the book you want to search.\n";
							std::cin.ignore();
							std::getline(std::cin, bookTitle);
							bookLookedUp = inventory.lookUpTitle(bookTitle);

							invState = kInvBookDisplay;
							break;
						}
						case 3: {	// search book by author
							string author;
							cout << "Please enter the author of the book you want to search.\n";
							std::cin.ignore();
							std::getline(std::cin, author);
							bookLookedUp = inventory.lookUpAuthor(author);

							invState = kInvBookDisplay;
							break;
						}
						case 4: {	// return to inventory menu
							invState = kInvMenu;
							break;
						}
						default: {	// stay in kInvLookUp
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
				case kInvExit: {	// return to module menu
					moduleState = kMenu; 
					break;
				}
				case kInvExitProgram: {	// exit the program
					moduleState = kExit;
					break;
				}
				case kInvEnterAdmin: {	// asks for password to enter admin mode
					string passInput;
					cout << "Enter a password to enter admin mode, or press 0 to exit\n";
					std::cin >> passInput;
					if (passInput == adminPass) {	// if password is right, isAdmin is set to true, set invState to kMenu
						isAdmin = true;
						invState = kMenu;
					}
					else if (passInput == "0") {	// if 0, set invState to kMenu
						invState = kMenu;
					}
					break;
				}
				case kSaveInventory: {	// saves book inventory from inventory to file
					inventory.saveBookInventory(fileName);

					cout << "Saved in file " << fileName << endl;
					invState = kInvMenu;	// return to InvMenu
					break;
				}
				case kInvAddBook: {	// add book through inventory
					try {
						inventory.addBook();
						cout << "Book has been added.\n";
					}
					catch (Inventory::bookAlreadyExistsException) {	// if the book exists, suggest editing from inventory list
						cout << "This book already exists. Please edit from looking it up on the inventory list." << endl;
					}

					invState = kInvMenu;
					break;
				}
				case kInvBookDisplay: {	// dipsplay book from lookUpBook
					cout << bookLookedUp;

					if (isAdmin) {	// if isAdmin, provide editing options for book info
						inventory.editBook(bookLookedUp);
					}
					// set invState to kInvLookUp
					invState = kInvLookUp;
				}
				}
			}

			break;
		}
		case kReport: {
			int userReportInput;
			// displays user options
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
			case 7:	// return to module state
				moduleState = kMenu;
				break;
			case 8:	// exit program
				moduleState = kExit;
				break;
			default:
				// checks for input range
				if ((userReportInput < 1) || (userReportInput > 8)) {
					cout << "Please enter a number between 1 and 8.\n";
				}
				else {	// displays report according to user input from report object
					Report rp = Report(&bl);
					rp.printReport(userReportInput);
				}
				moduleState = kReport;
			}
			break;
		}
		case kExit: {	// exits program
			cout << "Exiting" << endl;
			moduleState = kExit;

			break;
		}
		default:	// return moduleState kMenu
			cout << "Please enter a number between 1 and 4";
			moduleState = kMenu;
		}
	}

	cout << endl << endl << "Press Enter to Exit\n";
	cin.ignore();
	cin.get();
	return 0;
}

/**
*	getData function
*	@param inputFileName - name of the file
*	@param &bl - reference to the booklist
*	
*	return - the number of books read
sets index to 0
opens the file to read
if the file exists
	while a line is read from file
		set values for title, author, publisher, date, quantity, cost, and retail of a book
		adds the book to the list
		increase index by one
return index
*/
int getData(string inputFileName, BookList &bl) {
	ifstream inFile;			// input file to read string from
	int index = 0;
	inFile.open(inputFileName);
	if (inFile.good()) {
		string line;

		// while index is less than the maximum number of words
		while (getline(inFile, line)) {
			Book b;

			// reading values from the file into the appropriate variables for book b
			std::string isbn = line.substr(0, line.find(','));
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

			// sets the values to book b
			b.setISBN(isbn);
			b.setTitle(title);
			b.setAuthor(author);
			b.setPublish(publisher);
			b.setDateAdd(date);
			b.setQuantity(qty);
			b.setWholeSale(cost);
			b.setRetail(retail);

			// add book b to the list
			bl.addBook(b);

			// increase index by one
			index++;
		}
	}
	return index;
}
