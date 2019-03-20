#ifndef Inventory_H
#define Inventory_H


#include <iostream>
#include <istream>
#include <iomanip>
#include <string>
#include "BookList.h"
#include "AuthorList.h"
#include "TitleList.h"

class Inventory
{
private:
	BookList* mpBL;

public:
	class bookDoesNotExistException {};
	class bookAlreadyExistsException {};

	Inventory(BookList*);        //constructor
	~Inventory();
	Book lookUpISBN(std::string);
	Book lookUpTitle(std::string);
	Book lookUpAuthor(std::string);
	void addBook();
	void editBook(Book);
	void saveBookInventory(std::string);
};
#endif
