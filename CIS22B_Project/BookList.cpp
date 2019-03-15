#define _CRT_SECURE_NO_WARNINGS
#include "BookList.h"

/*
Default constructor to create an array of Books of size 0
*/
BookList::BookList() {
	books = new Book[0];	//creates an array Books of size 0
	size = 0;
}

/*
Two argument constructor that takes a pointer to an array of Books and a size as its arguments.
An array of Books is created with the size argument and
each value is copied from the Book array passed as an argument
*/
BookList::BookList(Book *b, int s) {
	books = new Book[s];	//array of Books is created with size s
	size = s;

	for (int i = 0; i < size; i++) {
		books[i] = b[i];	//each value of the Book array b is copied to books
	}
}

/*
Copy constructor that takes a consant reference to a BookList object as its arugment.
It uses the BookList object to copy the values of its Book array into this class's Book array
*/
BookList::BookList(const BookList& bl) {
	books = new Book[bl.size];
	size = bl.size;

	for (int i = 0; i < size; i++) {
		books[i] = bl.books[i];
	}
}

/*
deletes the Book array
*/
BookList::~BookList() {
	if (books != nullptr) {
		delete[size] books;
		books = nullptr;
	}
}

/*
returns the size of the Book array
*/

int BookList::getSize() {
	return size;			//returns the size of books
}

/*
returns the whole Book array
*/
Book* BookList::getBooks() {
	return books;
}


/*
Function to check if the Book exists in the Book array by using linear search
Takes one Book object as its argument and checks each Book's ISBN in the books array to see if they match
returns the position of the book in the books array
*/
int BookList::doesBookExist(Book b) {	// just going to go with linear search to make it easy
	for (int i = 0; i < size; i++) {				//uses linear seach to go through each element of the books array
		if (b.getISBN() == books[i].getISBN()) {	//checks the argument's ISBN with the Book in the books array's ISBN
			return i;								//returns the position of the Book in the books array
		}
	}
	return -1;
}


/*
function to add a book to the books array
Takes one Book object as its argument and checks if the Book already exists in the books array
if the books exists, then just change the quantity of the book
if the book doesn't exist, then create a new Book array with a bigger size
copy all the books from the books array to the new array and place the object passed as an argument as the last book in the array
delete the books array and copy the address of the new Book array into the books array
return the new size of the array
*/
int BookList::addBook(Book b) {
	int index = doesBookExist(b);		//check is Book object b already exists
	if (index > -1) {					//if the book object already exists
		books[index].setQuantity(b.getQuantity() + books[index].getQuantity());		//add the quantity of b to the quantity of the same book already existing inside the books array
	}
	else {	//if the book doesn't exist already
		Book* bl = new Book[++size];	//create a new Book array with size + 1
		for (int i = 0; i < size - 1; i++) {	//copy the books from books array to bl array
			bl[i] = books[i];
		}
		bl[size - 1] = b;	//place b as the last book in bl array 

		delete[size] books;	//delete the books array
		books = bl;			//copy the address of the bl array into the books
	}

	return size;			//return the size of the modified books array
}

/*
function to remove a book from the books array
takes a Book object as its argument and checks if the Book already exists in the books array
if the book doesn't exist return -1
if the book exists, then create a new Book array with a bigger size
copy the books over to the new array except for the removed book
decrease the size by one and return the new size of the books array
*/
int BookList::removeBook(Book b) {
	int index = doesBookExist(b);	//check if the Book object b exists in the books array
	if (index == -1) {				//if it doesn't exist
		return -1;
	}
	else {						//if the book exists in the books array
		Book* bl = new Book[--size];	//create a new Book array with size - 1
		for (int i = 0; i < index; i++) {
			bl[i] = books[i];	//copy the books from books array to bl array
		}
		for (int i = index; i < size; i++) {
			bl[i] = books[i + 1];
		}
		delete[size + 1] books;	//delete the books array
		books = bl;				//copy the address of the bl array into the books array
	}
	return size;				//return the size of the modified books array
}

/*
function to change the information of one book in the books array
takes one Book object as its argument and checks if the book exists in the books array
if the book exists, take the argument and copy it into the books array
if the books doesn't exist in the array, then throw an expection saying that the book doesn't exist
*/
void BookList::updateBookInfo(Book b) {
	int index = doesBookExist(b);
	if (index != -1) {		//if the book already exists in the array
		books[index] = b;
	}
	else {					//if the book doesn't exist already
		throw "Book does not exist.";
	}
}

/*
function to save the information of a Book into a file
takes a file name as its argument.
opens the file and copies the information for each book in the books array into the file.
*/
void BookList::saveBookListData(std::string fileName) {
	std::ofstream outputStream;
	outputStream.open(fileName);
	for (int i = 0; i < size; i++) {
		Book b = books[i];
		outputStream << b.getISBN() << "," << b.getTitle() << "," << b.getAuthor() << ","
			<< b.getPublish() << "," << b.getDateAdd() << "," << b.getQuantity() << ","
			<< b.getWholeSale() << "," << b.getRetail() << std::endl;
	}
}

/*
function to print the information for each book in the books array onto the screen
*/
void BookList::printBooks() {
	for (int i = 0; i < size; i++) {
		Book b = books[i];
		std::cout << b.getISBN() << "," << b.getTitle() << "," << b.getAuthor() << ","
			<< b.getPublish() << "," << b.getDateAdd() << "," << b.getQuantity() << ","
			<< b.getWholeSale() << "," << b.getRetail() << std::endl;
	}
}

/*
function to print the wholesale cost for each book in the books array
calculates and returns the total wholesale cost for all the books
*/
double BookList::printWholesaleValue() {
	double totalWholesale = 0;

	for (int i = 0; i < size; i++) {
		Book b = books[i];			//goes through each book in the books array
		std::cout << b.getISBN() << "," << b.getTitle() << ","
			<< b.getWholeSale() << std::endl;
		totalWholesale += b.getWholeSale();	//calculates the total wholesale cost by adding the wholesale cost for all the books in the books array
	}
	return totalWholesale;		//returns the total wholesale cost for all the books
}

/*
function to print the retail price for each book in the books array
calculates and returns the total retail price for all the books
*/
double BookList::printRetailValue() {
	double totalRetail = 0;

	for (int i = 0; i < size; i++) {
		Book b = books[i];		//goes through each book in the books array
		std::cout << b.getISBN() << "," << b.getTitle() << ", " << b.getRetail() << std::endl;		//print the ISBN, title, and wholesale cost for every book in the books array
		totalRetail += b.getRetail();		//calculates the total wholesale cost by adding the wholesale cost for all the books in the books array
	}
	return totalRetail;		//returns the total wholesale cost for all the books
}
