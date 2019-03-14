#include "QuantityList.h"



QuantityList::QuantityList(Book b[], int s) : BookList(b, s) {



}



QuantityList::QuantityList(const BookList& bl) : BookList(bl) {



}



void QuantityList::sortBooks() {

	int startIndex;		// starting index

	int maxIndex;		// index for the minimum value



	// loop through the array from 0

	for (startIndex = 0; startIndex < getSize(); startIndex++) {

		maxIndex = startIndex;	// set minimum value index to starting index

		int maxQty = books[maxIndex].getQuantity();	// set to the element at minIndex



		// loop through the array from one after the startIndex

		for (int index = startIndex + 1; index < getSize(); index++) {

			// if the word at the index is lower than minValue set minIndex to index and minValue to word

			maxQty = maximum(maxQty, books[index].getQuantity());

		}



		// switch the element at minIndex and the element at startIndex

		Book tempB = books[maxIndex];

		books[maxIndex] = books[startIndex];

		books[startIndex] = tempB;

	}

}