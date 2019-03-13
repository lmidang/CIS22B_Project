#include "BookList.h"

BookList::BookList() {
	books = new Book[0];
	size = 0;
}

BookList::BookList(Book *b, int s) {
	books = new Book[s];
	size = s;

	for (int i = 0; i < size; i++) {
		books[i] = b[i];
	}
}

BookList::BookList(const BookList& bl) {
	books = new Book[bl.size];

	for (int i = 0; i < size; i++) {
		books[i] = bl.books[i];
	}
}

BookList::~BookList() {
	delete books;
	books = nullptr;
}

int BookList::getSize() {
	return size;
}

int BookList::doesBookExist(Book b) {	// just going to go with linear search to make it easy
	for (int i = 0; i < size; i++) {
		if (b.getISBN() == books[i].getISBN()) {
			return i;
		}
	}
	return -1;
}

int BookList::addBook(Book b) {
	int index = doesBookExist(b);
	if (index > -1) {
		books[index].setQuantity(b.getQuantity() + books[index].getQuantity());
	} else {
		Book* bl = new Book[++size];
		for (int i = 0; i < size - 1; i++) {
			bl[i] = books[i];
		}
		bl[size - 1] = b;
		
		delete books;
		books = bl;
	}

	return size;
}

int BookList::removeBook(Book b) {
	int index = doesBookExist(b);
	if (index == -1) {
		return -1;
	} else {
		for (int i = index; i < size - 1; i++) {
			books[i] = books[i + 1];
		}
		size--;
	}
	return size;
}

void BookList::updateBookInfo(Book b ) {
	int index = doesBookExist(b);
	if (index != -1) {
		books[index] = b;
	}
	else {
		throw "Book does not exist.";
	}
}

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

void BookList::printBooks()  {
	for (int i = 0; i < size; i++) {
		Book b = books[i];
		std::cout << b.getISBN() << "," << b.getTitle() << "," << b.getAuthor() << ","
			<< b.getPublish() << "," << b.getDateAdd() << "," << b.getQuantity() << ","
			<< b.getWholeSale() << "," << b.getRetail() << std::endl;
	}
}