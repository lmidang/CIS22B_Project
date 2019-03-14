#include <iostream>
#include <string>
#include "Publisher.h"



Quantity::Quantity(Book b[], int s) : BookList(b, s) {



}



Quantity::Quantity(const BookList& bl) : BookList(bl) {



}



void Quantity::sortBooks() {

	int startIndex;		// starting index

	int minIndex;		// index for the minimum value



	// loop through the array from 0

	for (startIndex = 0; startIndex < getSize(); startIndex++) {

		minIndex = startIndex;	// set minimum value index to starting index

		int minQuantity = books[minIndex].getQuantity();	// set to the element at minIndex



		// loop through the array from one after the startIndex

		for (int index = startIndex + 1; index < getSize(); index++) {

			// if the word at the index is lower than minValue set minIndex to index and minValue to word

			minQuantity = minimum(minQuantity, books[index].getQuantity());

		}



		// switch the element at minIndex and the element at startIndex

		Book tempB = books[minIndex];

		books[minIndex] = books[startIndex];

		books[startIndex] = tempB;

	}

}



// under assumption that books have been sorted

ISBNList Quantity::getBooks(int quantity) {

	int num = 0;

	const int numBooks = getSize();

	ISBNList bl;



	for (int i = 0; i < getSize(); i++) {

		if (compare(books[i].getQuantity(), quantity) == 0) {

			bl.addBook(books[i]);

		}

		else if (num > 0) {

			break;

		}

	}



	return bl;

}