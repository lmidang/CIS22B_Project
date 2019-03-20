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
An array of Books is created with the size argument
	each value is copied from Book array b to Book array books using a for loop
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
It uses the BookList object to copy the values of that instance's Book array into this class's Book array
*/
BookList::BookList(const BookList& bl) {
	books = new Book[bl.size];
	size = bl.size;

	for (int i = 0; i < size; i++) {
		books[i] = bl.books[i];
	}
}

/*
checks if the Book array exists
	deletes the Book array
	sets the Book array address to null
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
Takes one Book object as its argument
	Checks each Book's ISBN in the books array to see if they match
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
Function to check if the Book exists in the Book array by using linear search
Takes one unsigned long long as its argument
	Checks each Book's ISBN in the books array to see if they match
		returns the position of the book in the books array
*/

int BookList::doesBookExist(std::string isbn) {
	for (int i = 0; i < size; i++) {				//uses linear seach to go through each element of the books array
		if (isbn == books[i].getISBN()) {	//checks the ISBN argument with the Book in the books array's ISBN
			return i;								//returns the position of the Book in the books array
		}
	}
	return -1;
}


/*
function to add a book to the books array
Takes one Book object as its argument 
Checks if the Book already exists in the books array y passing it to the doesBookExist() function
if the book exists 
	just change the quantity of the book
if the book doesn't exist
	create a new Book array with a bigger size
		copy all the books from the books array to the new array 
	place the object passed as an argument as the last book in the array
	delete the books array 
	copy the address of the new Book array into the books array
return the new size of the array
*/
int BookList::addBook(Book b) {
	int index = doesBookExist(b);		//check is Book object b already exists
	if (index > -1) {					//if the book object already exists
		//add the quantity of b to the quantity of the same book already existing inside the books array
		books[index].setQuantity(addBookQty(b, books[index]));
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
takes a Book object as its argument 
checks if the Book already exists in the books array
if the book doesn't exist 
	return -1
if the book exists 
	create a new Book array bl with a bigger size
		copy the books from the array books to bl until index where the book being removed exists
		copy the books from the next index in the array books to the current index in bl until the end of the bl array
	decrease the size by one 
	copy the address of the new Book array into the array books
return the new size of the books array
*/
int BookList::removeBook(Book b) {
	int index = doesBookExist(b);	//check if the Book object b exists in the books array
	if (index == -1) {				//if it doesn't exist
		return -1;
	}
	else {						//if the book exists in the books array
		Book* bl = new Book[--size];	//create a new Book array with size - 1
		for (int i = 0; i < index; i++) {
			bl[i] = books[i];	//the books that come before index are simply just copied from the books array to the bl array
		}
		//the books that come after index are copied from the books array and placed in the previous index of the bl array
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
takes one Book object b as its argument 
checks if the book exists in the books array
if the book exists
	changes the book already existing in the array at that index by copying Book b into the array 
if the book doesn't exist in the array
	throw an expection saying that the book doesn't exist
*/
void BookList::updateBookInfo(Book b) {
	int index = doesBookExist(b);
	if (index != -1) {		//if the book already exists in the array
		books[index] = b;	//take Book b and copies it into the books array
	}
	else {					//if the book doesn't exist already
		throw "Book does not exist.";	//throw an exception saying that the book doesn't exist
	}
}

/*
function to save the information of a Book into a file
takes a file name as its argument.
opens the file
	copies the information for each book in the books array into the file.
*/
void BookList::saveBookListData(std::string fileName) {
	std::ofstream outputStream;
	outputStream.open(fileName);	//opens a file with the filename provided as a parameter
	for (int i = 0; i < size; i++) {
		Book b = books[i];	//goes through every book in the books array
		//prints the information for all the books into a file
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
		Book b = books[i];	//goes through every book in the books array
		//prints the information for all the books onto the screen
		std::cout << b.getISBN() << "," << b.getTitle() << "," << b.getAuthor() << ","
			<< b.getPublish() << "," << b.getDateAdd() << "," << b.getQuantity() << ","
			<< b.getWholeSale() << "," << b.getRetail() << std::endl;
	}
}

/*
function to print the wholesale cost for each book in the books array
	prints the ISBN, Title, and Wholesale Cost for all the books in the list
	calculates the total wholesale cost by adding the wholesale costs together for all the books
returns the total wholesale cost for all the books
*/
double BookList::printWholesaleValue() {
	double totalWholesale = 0;

	for (int i = 0; i < size; i++) {
		Book b = books[i];			//goes through each book in the books array
		std::cout << b.getISBN() << "," << b.getTitle() << ","	//prints the ISBN, Title, and wholesale cost for all the books onto the screen
			<< b.getWholeSale() << std::endl;
		//calculates the total wholesale cost by adding the wholesale cost for all the books in the books array
		totalWholesale += b.getWholeSale();
	}
	return totalWholesale;		//returns the total wholesale cost for all the books
}

/*
function to print the retail price for each book in the books array
	prints the ISBN, Title, and Retail Price for all the books in the list
	calculates the total retail price by adding the retail prices together for all the books
returns the total retail price for all the books
*/
double BookList::printRetailValue() {
	double totalRetail = 0;

	for (int i = 0; i < size; i++) {
		Book b = books[i];		//goes through each book in the books array
		//print the ISBN, title, and wholesale cost for every book in the books array
		std::cout << b.getISBN() << "," << b.getTitle() << ", " << b.getRetail() << std::endl;
		//calculates the total wholesale cost by adding the wholesale cost for all the books in the books array
		totalRetail += b.getRetail();
	}
	return totalRetail;		//returns the total wholesale cost for all the books
}