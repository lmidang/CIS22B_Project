#include "ISBNList.h"

ISBNList::ISBNList() : BookList() {

}

ISBNList::ISBNList(Book b[], int s) : BookList(b, s){

}

ISBNList::ISBNList(const BookList& bl) : BookList(bl) {

}

void ISBNList::sortBooks() {
	int startIndex;		// starting index
	int minIndex;		// index for the minimum value

	// loop through the array from 0
	for (startIndex = 0; startIndex < size; startIndex++) {
		minIndex = startIndex;	// set minimum value index to starting index
		unsigned int minISBN = books[minIndex].getISBN();	// set to the element at minIndex

		// loop through the array from one after the startIndex
		for (int index = startIndex + 1; index < size; index++) {
			// if the word at the index is lower than minValue set minIndex to index and minValue to word
			minISBN = minimum(minISBN, books[index].getISBN());
		}

		// switch the element at minIndex and the element at startIndex
		Book tempB = books[minIndex];
		books[minIndex] = books[startIndex];
		books[startIndex] = tempB;
	}

}

Book ISBNList::getBook(unsigned int bISBN) {
	int firstElement = 0;		// index of the first element to search through
	int lastElement = size;		// index of the last element to search through + 1
	int middle;					// index of the middle element
	int position = -1;			// position of the word found  (set to -1 by default)

	// loop while position is still -1 (word not found) and the first element < last element
	while ((position == -1) && (firstElement < lastElement)) {
		// set middle to the average of first element and last element (truncate if necessary)
		middle = (firstElement + lastElement) / 2;
		int comparison = compare(books[middle].getISBN(), bISBN);

		// if the ISBN matches the element's set position to middle
		if (comparison == 0) {
			position = middle;
		}
		else if (comparison > 0) {
			// if the ISBN is less than the that of middle element, set last element to middle
			lastElement = middle;
		}
		else {
			// word is greater than the middle element, set first element to middle + 1
			firstElement = middle + 1;
		}
	}

	if (position == -1) {
		throw "Book not found.";
	}

	// book at position of the word
	return books[position];
}

Book* ISBNList::getBooks() {
	return books;
}