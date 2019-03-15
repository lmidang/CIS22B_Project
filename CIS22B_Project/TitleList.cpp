#define _CRT_SECURE_NO_WARNINGS

#include "TitleList.h"

TitleList::TitleList(Book b[], int s) : BookList(b, s) {

}

TitleList::TitleList(const BookList& bl) : BookList(bl) {

}

void TitleList::sortBooks() {
	int startIndex;		// starting index
	int minIndex;		// index for the minimum value

	// loop through the array from 0
	for (startIndex = 0; startIndex < size; startIndex++) {
		minIndex = startIndex;	// set minimum value index to starting index
		std::string minTitle = books[minIndex].getTitle();	// set to the element at minIndex

		// loop through the array from one after the startIndex
		for (int index = startIndex + 1; index < size; index++) {
			// if the word at the index is lower than minValue set minIndex to index and minValue to word
			minTitle = minimum(minTitle, books[index].getTitle());
		}

		// switch the element at minIndex and the element at startIndex
		Book tempB = books[minIndex];
		books[minIndex] = books[startIndex];
		books[startIndex] = tempB;
	}
}

// under assumption that books have been sorted
ISBNList TitleList::getBooks(std::string title) {
	int num = 0;
	const int numBooks = size;
	ISBNList bl;

	for (int i = 0; i < size; i++) {
		if (compare(books[i].getTitle(), title) == 0) {
			bl.addBook(books[i]);
		}
		else if (num > 0) {
			break;
		}
	}

	return bl;
}