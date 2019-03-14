#include <iostream>
#include <string>
#include "PublisherList.h"
#include "BookList.h"



PriceList::PriceList(Book b[], int s) : BookList(b, s) {



}



PriceList::PriceList(const BookList& bl) : BookList(bl) {



}



void BookList::sortBooks() {

	int startIndex;		// starting index

	int minIndex;		// index for the minimum value



	// loop through the array from 0

	for (startIndex = 0; startIndex < getSize(); startIndex++) {

		minIndex = startIndex;	// set minimum value index to starting index

		double minRetail = books[minIndex].getRetail();	// set to the element at minIndex



		// loop through the array from one after the startIndex

		for (int index = startIndex + 1; index < getSize(); index++) {

			// if the word at the index is lower than minValue set minIndex to index and minValue to word

			minRetail = minimum(minRetail, books[index].getRetail());

		}



		// switch the element at minIndex and the element at startIndex

		Book tempB = books[minIndex];

		books[minIndex] = books[startIndex];

		books[startIndex] = tempB;

	}

}



// under assumption that books have been sorted

ISBNList PriceList::getBooks(int retail) {

	int num = 0;

	const int numBooks = getSize();

	ISBNList bl;



	for (int i = 0; i < getSize(); i++) {

		if (compare(books[i].getRetail(), retail) == 0) {

			bl.addBook(books[i]);

		}

		else if (num > 0) {

			break;

		}

	}



	return bl;

}