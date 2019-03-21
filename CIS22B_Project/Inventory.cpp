#define _CRT_SECURE_NO_WARNINGS

#include "Inventory.h"
/*
Argument constructor that passes object pB to Booklist class
*/

Inventory::Inventory(BookList* pB)
{
	mpBL = pB;
}
/*
Destructor with no parameters
*/
Inventory::~Inventory() {
};
/*
Function to look up ISBN numbers by user in a string
  IBSNList object is created
  Checks if book exists with ISBN passed as argument
  Returns the string
  Exception is thrown if it does not exist
*/
Book Inventory::lookUpISBN(std::string i) {
	ISBNList isbnList = ISBNList(*mpBL);
	isbnList.sortBooks();
	if (isbnList.doesBookExist(i) > -1) {
		return isbnList.getBook(i);
	}
	else {
		throw bookDoesNotExistException();
	}
}
/*
Function to look up authors by user in string
	AuthorList object is created and is sorted by authorList

  Takes ISBN object as argument and passes it through getBooks string
  Goes through object and checks if it exists
  Exception is thrown if it does not exist

  Asks user to select an option in AuthorList by typing the first number
  with the options being the ISBN, Title, and Author of each book
  if userSelection is greater than size of book or less than 0
  User is asked to input a value in that range

  Returns the book choosen from array
*/
Book Inventory::lookUpAuthor(std::string s) {
	AuthorList authorList = AuthorList(*mpBL);
	authorList.sortBooks();

	ISBNList isbnList = authorList.getBooks(s);
	int size = isbnList.getSize();
	if (size == 0) {
		throw bookDoesNotExistException();
	}

	std::cout << "\nSelect one of the following, by the first number.\n";
	for (int i = 0; i < size; i++) {
		Book b = isbnList.getBooks()[i];
		std::cout << i << ": " << b.getISBN() << ", " << b.getTitle() << ", " << b.getAuthor() << std::endl;
	}
	int userSelection;
	std::cin >> userSelection;
	while ((userSelection < 0) || (userSelection > size - 1)) {
		std::cout << "Please enter an appropriate number listed above.\n";
		std::cin >> userSelection;
	}
	return isbnList.getBooks()[userSelection];
}
/*
Function to look up title by user in string
	TitleList object is created and is sorted by titleList

  Takes ISBN object as argument and passes it through getBooks string
  Goes through object and checks if it exists
  Exception is thrown if it does not exist

  Asks user to select an option in TitleList by typing the first number
  with the options being the ISBN, Title, and Author of each book
  if userSelection is greater than size of book or less than 0
  User is asked to input a value in that range

  Returns the book choosen from array

*/
Book Inventory::lookUpTitle(std::string s) {
	TitleList titleList = TitleList(*mpBL);
	titleList.sortBooks();

	ISBNList isbnList = titleList.getBooks(s);
	int size = isbnList.getSize();
	if (size == 0) {
		throw bookDoesNotExistException();
	}

	std::cout << "\nSelect one of the following, by the first number.\n";
	for (int i = 0; i < size; i++) {
		Book b = isbnList.getBooks()[i];
		std::cout << i << ": " << b.getISBN() << ", " << b.getTitle() << ", " << b.getAuthor() << std::endl;
	}
	int userSelection;
	std::cin >> userSelection;
	while ((userSelection < 0) || (userSelection > size - 1)) {
		std::cout << "Please enter an appropriate number listed above.\n";
		std::cin >> userSelection;
	}
	return isbnList.getBooks()[userSelection];
}
/*
  Function to add books with 9 member variables
  Asks user for ISBN of book to add
  Checks if it exists
  If exists, user is asked to enter title, author,
  publisher, date, quantity, whole sale cost, and retail price
    While loop is used to prevent user from entering
    a negetive integer value
  Exception is thrown if it does not exist
  Stores it in mpBL object
*/
void Inventory::addBook()
{
	Book bookToAdd;
	std::string isbn;
	std::string title;
	std::string author;
	std::string publisher;
	std::string dateAdded;
	int quantity;
	double wholesaleCost;
	double retailPrice;

	std::cout << "\nPlease enter the ISBN of the book (integer with no dashes): ";
	std::cin >> isbn;
	bookToAdd.setISBN(isbn);
	std::cin.ignore();

	if (mpBL->doesBookExist(isbn) > -1) {
		throw bookAlreadyExistsException();
	}
	else {
		std::cout << "Please enter the title of the book: ";
		std::getline(std::cin, title);
		bookToAdd.setTitle(title);

		std::cout << "Please enter the author of the book: ";
		std::getline(std::cin, author);
		bookToAdd.setAuthor(author);

		std::cout << "Please enter the publisher of the book: ";
		std::getline(std::cin, publisher);
		bookToAdd.setPublish(publisher);

		std::cout << "Please enter the date the book was added in YYYY/MM/DD: ";
		std::cin >> dateAdded;
		bookToAdd.setDateAdd(dateAdded);

		std::cout << "Please enter the quantity of the book: ";
		std::cin >> quantity;
		while (quantity < 0) {
			std::cout << "Please enter an appropriate number (0 or above)\n";
			std::cin >> quantity;
		}
		bookToAdd.setQuantity(quantity);

		std::cout << "Please enter the wholesale cost of the book: ";
		std::cin >> wholesaleCost;
		while (wholesaleCost < 0) {
			std::cout << "Please enter an appropriate number (0 or above)\n";
			std::cin >> wholesaleCost;
		}
		bookToAdd.setWholeSale(wholesaleCost);

		std::cout << "Please enter the retail price of the book: ";
		std::cin >> retailPrice;
		while (retailPrice < 0) {
			std::cout << "Please enter an appropriate number (0 or above)\n";
			std::cin >> retailPrice;
		}
		bookToAdd.setRetail(retailPrice);

		mpBL->addBook(bookToAdd);
	}

}
/*
Function to edit book in book array with 11 member variables
  While index is not 10
  Switch statment to edit book based on user input
    case is 0
      Asks user which part of the book they want to edit
			Displays edit menu options
		case is 1
			Prompts user to enter ISBN
			Stores new ISBN in string
		case is 2
      Promps user to enter title
      Stores new title in string
    case is 3
      Prompts user to enter author
      Stores new author in string
    case is 4
      Prompts user to enter publisher
      Stores new publisher in string
    case is 5
      Prompts user to enter date added in YYYY/MM/DD format
      Stores new date in string
    case is 6
      Prompts user to enter quantity
      Stores new quantity in string
    case is 7
      Prompts user to enter whole sale cost
      Stores new whole sale cost in string
    case is 8
      Prompts user to enter retail price
      Stores new retail price in string
    case is 9
      Asks user if editedBook needs to be deleted
      Deletes book entry
  else returns null
*/
void Inventory::editBook(Book b)
{
	Book editedBook = b;
	int index = 0;
	std::string isbn;
	std::string title;
	std::string author;
	std::string publisher;
	std::string dateAdded;
	int quantity;
	double wholesaleCost;
	double retailPrice;
	int willDelete;

	while (index != 10) {
		switch (index)
		{
		case 0:
			std::cout << std::endl << "How would you like to edit? " << std::endl
				<< "1. ISBN\n"
				<< "2. Title:\n"
				<< "3. Author\n"
				<< "4. Publisher\n"
				<< "5. Date Added\n"
				<< "6. Quantity\n"
				<< "7. Wholesale Cost\n"
				<< "8. Retail Price\n"
				<< "9. Remove this book\n"
				<< "10. Finished\n"
				<< "Please select item:";
			std::cin >> index;
			break;
		case 1:
			std::cout << "Please enter the new ISBN: ";
			std::cin >> isbn;
			editedBook.setISBN(isbn);

			index = 0;
			break;
		case 2:
			std::cout << "Please enter the new Title: ";
			std::cin.ignore();
			std::getline(std::cin, title);
			editedBook.setTitle(title);

			index = 0;
			break;
		case 3:
			std::cout << "Please enter the new Author: ";
			std::cin.ignore();
			std::getline(std::cin, author);
			editedBook.setAuthor(author);

			index = 0;
			break;
		case 4:
			std::cout << "Please enter the new Publisher: ";
			std::cin.ignore();
			std::getline(std::cin, publisher);
			editedBook.setPublish(publisher);

			index = 0;
			break;
		case 5:
			std::cout << "Please enter the new Date in YYYY/MM/DD: ";
			std::cin.ignore();
			std::getline(std::cin, dateAdded);
			editedBook.setDateAdd(dateAdded);

			index = 0;
			break;
		case 6:
			std::cout << "Please enter the new quantity: ";
			std::cin >> quantity;
			editedBook.setQuantity(quantity);

			index = 0;
			break;
		case 7:
			std::cout << "Please enter the new WholesaleCost: ";
			std::cin >> wholesaleCost;
			editedBook.setWholeSale(wholesaleCost);

			index = 0;
			break;
		case 8:
			std::cout << "Please enter the new RetailPrice: ";
			std::cin >> retailPrice;
			editedBook.setRetail(retailPrice);

			index = 0;
			break;
		case 9:
			std::cout << "Are you sure you want to remove this? 0 for yes, any other number for no.";
			std::cin >> willDelete;
			if (willDelete == 0) {
				mpBL->removeBook(editedBook);
				index = 10;
			}
			else {
				index = 0;
			}
		break;
		default:
			std::cout << "Invalid input.";
			return;
		}
	}

	mpBL->updateBookInfo(editedBook);
}
/*
  Function takes name of file and sends it to saveBookListData function
  All books are copied into new file
*/
void Inventory::saveBookInventory(std::string fileName) {
	mpBL->saveBookListData(fileName);
}
