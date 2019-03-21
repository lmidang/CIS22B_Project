#define _CRT_SECURE_NO_WARNINGS

#include "Cashier.h"


/*
constructor with parameters of an object bl that points to the BookList class
	string mInputISBN equals string value  of "0000000"
	ISBNList varaiable mpCartList equals a new dynamically allocated ISBNList object
	mpInventory variable equals bl variable which is a pointer to BookList
*/

Cashier::Cashier(BookList* bl) //constructor
{
	mInputISBN = "0000000"; //sets isbn value to deafult of zero
	mpCartList = new ISBNList(); //new dynamically allocated class created from ISBNList
	mpInventory = bl; //copies the address of a pointer to a ISBNList class
}

/*
destructor with no parameters
	if ISBNList variable mpCartList is not equal to a null pointer
		delete mpCartList
		mpCartList equals nullpointer
*/

Cashier::~Cashier() //destructor
{
	if (mpCartList != nullptr) //if mpCartList exists
	{
		delete mpCartList; //clears mpCartList
		mpCartList = nullptr; //sets the adress to CartList to zero
	}
}

/*
function string gets user input isbn and is constant with no parameters
	return isbn input string
*/

std::string Cashier::getInputISBN() const //getter function
{
	return mInputISBN;
}

/*
function void sets user input isbn has parameter string I
	if BookList variable mpInventory calling function doesBookExist with paramter I is less than 0
		throw exception that isbn does not exist
	isbn input string equals string I
*/

void Cashier::setInputISBN(std::string I) //setter function with exception

{
	if (mpInventory->doesBookExist(I) < 0)
	{
		throw isbnDoesNotExistException(); //exception if isbn does not exist in inventory file
	}
	mInputISBN = I;
}

/*
function void adds a book to the cart with parameters string ISBN and integer qty
	integer index equals position of book in inventory
	integer cartQty equals integer qty
	if position is greater than -1
		class Book variable invB equals array of book with specific isbn in BookList variable mpInventory
		integer cartIndex equals position of book in cart
		if position is greater than -1
			class Book b gets book based from cart based on index position in cart
			add quantity to book object in cart
		if the cart quantity is greater than inventory quantity
			throw exception that there are not enough books in stock
		else
			class Book b equals class Book with paramters invB
			b call function setQuantity with paramters qty
			mpCartList call function addBook with paramter b
	else
		throw exception that isbn does not exist
*/

void Cashier::addToCart(std::string ISBN, int qty) //function to add book objects to a cart
{
	int index = mpInventory->doesBookExist(ISBN); //variable index gets position of book 
	int cartQty = qty;
	if (index > -1)
	{
		Book invB = mpInventory->getBooks()[index]; //class Book invB gets book with input isbn

		int cartIndex = mpCartList->doesBookExist(ISBN); //cartIndex gets position of book that was input with an isbn
		if (cartIndex > -1)
		{
			Book b = mpCartList->getBooks()[cartIndex]; //class Book b gets book from index position in cart
			cartQty += b.getQuantity(); //add quantity to book object in cart
		}

		if (cartQty > invB.getQuantity())
		{
			throw notEnoughInStockException(); //exception if quantity of book equals zero
		}
		else
		{
			Book b = Book(invB);
			b.setQuantity(qty); //book class quantity gets quantity of cart
			mpCartList->addBook(b); //adds book into cart by creating a new space in the array
		}
	}
	else
	{
		throw isbnDoesNotExistException(); //exception if isbn doesn not exist
	}
}


/*
function integer removes a book from the cart with paramters string isbn and integer qty
	int index equals position of book in cart
	if position is greater than -1
		object b in book class equals array of book in cart
		integer book quantity equals the book quantity after subtracting it from the cart
		if book quantity is greater than 0
			set quantity of book b object to book qunatity after substraction
			update info in cart by copying book b into the books array
		else if book quantity is equal to 0
			remove the book from the cart entirely
		else
			throw exception that user is subtracting more books than are in the cart
	else
		throw exception that the isbn does not exist
	return the size of the book array of the cart book object
*/

int Cashier::removeFromCart(std::string isbn, int qty) //function to subtract book objects from the cart
{
	int index = mpCartList->doesBookExist(isbn); //variable index gets position of book 
	if (index > -1)
	{
		Book b = mpCartList->getBooks()[index]; //class Book invB gets book with input isbn
		int bQty = subtractBookQty(b, qty);
		if (bQty > 0)
		{
			b.setQuantity(bQty); //set quantity of book in book class
			mpCartList->updateBookInfo(b); //update cartlist by getting quantity of book b
		}
		else if (bQty == 0)
		{
			mpCartList->removeBook(b); //removes book from cart
		}
		else
		{
			throw negativeQtyException(); //exception if isbn is a negative number
		}
	}
	else
	{
		throw isbnDoesNotExistException(); //exception if isbn doesn not exist
	}
	return mpCartList->getSize(); //return size of cartlist in terms of book objects
}

/*
function void updates inventory with paremters string fileName
	integer variable equals getSize function from cart object
	for integer i equals zero, i is less than size of cart, incease i by 1
		class Book variable of cart is equal to getBooks function with array i from cart object
		class Book variable of inventory is equal to getBooks function with array position of Book
		integer variable of quantity equals value returned from call function subtract book quantity
		set quantity in inventory object of class book
		update book info of class variable inventory from booklist
	save bookdata into fileNmae in inventory variable
*/

void Cashier::updateInventory(std::string fileName) //function to subtract books from inventory list file
{
	int size = mpCartList->getSize();
	for (int i = 0; i < size; i++)
	{
		Book bookCart = mpCartList->getBooks()[i]; //class book bookCart gets book in cart
		Book bookInv = mpInventory->getBooks()[mpInventory->doesBookExist(bookCart.getISBN())];

		int qty = subtractBookQty(bookInv, bookCart); //set variable qty to function that removes a book quantity

		bookInv.setQuantity(qty); //set new quantity in Book class
		mpInventory->updateBookInfo(bookInv); //call funstion to update book info of book class object
	}
	mpInventory->saveBookListData(fileName); //saves data directly into file from book class object
}

/*
function void prints the cart
	integer variable equals getSize function from cart object
	sort books from cartlist object
	for integer i equals zero, i is less than size of cart, incease i by 1
		class Book b is equal to getBooks function with array i from cart object
		setwidth to 20 between all pieces of information except 40 before title
		ouptut "quanity, ISBN, Title, Retail Cost, Total price(quantity times cost)"
*/

void Cashier::printCart() //function to print quantity, isbn, name, and price values from cart
{
	int size = mpCartList->getSize();
	mpCartList->sortBooks();
	for (int i = 0; i < size; i++)
	{
		Book b = mpCartList->getBooks()[i]; //Book b = book in cartlist
		std::cout << std::setw(20) << b.getQuantity() << std::setw(20) << b.getISBN() << std::setw(40) << b.getTitle();
		std::cout << std::setw(20) << b.getRetail() << std::setw(20) << b.getQuantity() * b.getRetail() << std::endl;
	}
}

/*
function double that gets a sales tax with no parameters
	set double variable of a taxrate equal to .09
	set double variable equal to the subtotal times the sales tax
	return tax value
*/

double Cashier::getSalesTax() //function to multipy subtotal function by a tax rate to obtain a taxed value
{
	double SALES_TAX = .09; //set sales tax rate to 9%
	double salesTax = getSubTotal() * SALES_TAX; //multiply subtotal by 9%
	return salesTax; //return tax based on subtotal
}

/*
function double that gets a subtotal from cart with no parameters
	integer variable equals getSize function from cart object
	double variable of subtotal equals zero
	for integer i equals zero, i is less than size of cart, incease i by 1
		class Book b is equal to getBooks function with array i from cart object
		subtotal is equal to subtotal plus quantity times retail value of book b
	return subtotal
*/

double Cashier::getSubTotal() //function to add price values of books multiplied by quantity in cart to obtain a subtotal
{
	int size = mpCartList->getSize();

	double subTotal = 0;
	for (int i = 0; i < size; i++) //loops while objects exist in cart
	{
		Book b = mpCartList->getBooks()[i]; //Book b = book in cartlist
		subTotal += (b.getQuantity() * b.getRetail()); //subtotal = quantity times retail value
	}
	return subTotal;
}