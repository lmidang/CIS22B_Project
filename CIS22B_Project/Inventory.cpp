#define _CRT_SECURE_NO_WARNINGS

#include "Inventory.h"

Inventory::Inventory(BookList* pB)
{
	mpBL = pB;
}

Inventory::~Inventory() {
};

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

Book Inventory::lookUpAuthor(std::string s) {
	AuthorList authorList = AuthorList(*mpBL);
	authorList.sortBooks();
	
	ISBNList isbnList = authorList.getBooks(s);
	int size = isbnList.getSize();
	if (size == 0) {
		throw bookDoesNotExistException();
	}

	std::cout << "Select one of the following, by the first number.\n";
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

Book Inventory::lookUpTitle(std::string s) {
	TitleList titleList = TitleList(*mpBL);
	titleList.sortBooks();

	ISBNList isbnList = titleList.getBooks(s);
	int size = isbnList.getSize();
	if (size == 0) {
		throw bookDoesNotExistException();
	}

	std::cout << "Select one of the following, by the first number.\n";
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

	std::cout << "Please enter the ISBN of the book (integer with no dashes): ";
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
		bookToAdd.setQuantity(quantity);

		std::cout << "Please enter the wholesale cost of the book: ";
		std::cin >> wholesaleCost;
		bookToAdd.setWholeSale(wholesaleCost);

		std::cout << "Please enter the retail price of the book: ";
		std::cin >> retailPrice;
		bookToAdd.setRetail(retailPrice);

		mpBL->addBook(bookToAdd);
	}

}

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

void Inventory::saveBookInventory(std::string fileName) {
	mpBL->saveBookListData(fileName);
}