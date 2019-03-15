#define _CRT_SECURE_NO_WARNINGS

#include "CostList.h"

CostList::CostList(Book b[], int s) : BookList(b, s) {
}



CostList::CostList(const BookList& bl) : BookList(bl) {
}

void CostList::sortBooks() {

	int startIndex;		// starting index
	int minIndex;		// index for the minimum value

	// loop through the array from 0

	for (startIndex = 0; startIndex < getSize(); startIndex++) {
		minIndex = startIndex;	// set minimum value index to starting index
		double minWholeSale = books[minIndex].getWholeSale();	// set to the element at minIndex

		// loop through the array from one after the startIndex
		for (int index = startIndex + 1; index < getSize(); index++) {
			// if the word at the index is lower than minValue set minIndex to index and minValue to word
			minWholeSale = minimum(minWholeSale, books[index].getWholeSale());
		}
		// switch the element at minIndex and the element at startIndex

		Book tempB = books[minIndex];
		books[minIndex] = books[startIndex];
		books[startIndex] = tempB;
	}
}

void CostList::printBooks() {
	// TODO FIX THE FORMATTING
	std::cout << "ISBN" << "Title" << "Author" << "Cost" << std::endl;
	for (int i = 0; i < size; i++) {
		Book b = books[i];
		std::cout << b.getISBN() << "," << b.getTitle() << "," << b.getAuthor() << "," << " $" << b.getWholeSale() << std::endl;
	}
}