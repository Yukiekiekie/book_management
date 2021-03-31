#include "book_management.h"
BookArray* Bookarray;//ʵ����BookArray
//LoanArray* Loanarray = (LoanArray*)malloc(sizeof(LoanArray));
LoanArray* Loanarray;
//main menu
void menu() {
	printf("Please choose an option:\n");
	printf("1) Register an account\n");
	printf("2) Login\n");
	printf("3) Search for books\n");
	printf("4) Display all books\n");
	printf("5) Quit\n");
}
//search menu
void search_menu() {
	printf("Please choose an option:\n");
	printf("1) Find books by title\n");
	printf("2) Find books by author\n");
	printf("3) Find books by year\n");
	printf("4) Return to privious menu\n");
}
//user menu
void user_menu() {
	printf("Please choose an option:\n");
	printf("1) Borrow a book\n");
	printf("2) Return a book\n");
	printf("3) Search for books\n");
	printf("4) Display all books\n");
	printf("5) Log out\n");
}
void admin_menu() {
	printf("Please choose an option:\n");
	printf("1) Add a book\n");
	printf("2) Remove a book\n");
	printf("3) Search for books\n");
	printf("4) Display all books\n");
	printf("5) Log out\n");
}
int add_book(Book book) {
	*&book.id = Bookarray->length + 1;
	printf("Enter the title of the book you wish to add:");
	book.title = (char*)malloc(100);
	getchar();
	fgets(*&book.title, 100,stdin);
	*&book.title[strlen(*&book.title) - 1] = 0;
	printf("Enter the authors of the book you wish to add:");
	book.authors = (char*)malloc(100);
	fgets(*&book.authors, 100, stdin);
	*&book.authors[strlen(*&book.authors) - 1] = 0;
	printf("Enter the year of the book you wish to add was released:");
	int year_t = scanf("%d", &book.year);
	if (year_t == 0) {
		printf("Sorry, you attempt to add an invalid book, please try again.");
		return 1;
	}
	printf("Enter the copies of the book you wish to add was released:");
	int copy_t = scanf("%d", &book.copies);
	if (copy_t == 0) {
		printf("Sorry, you attempt to add an invalid book, please try again.");
		return 1;
	}
	Bookarray->array[Bookarray->length] = book;
	return 0;
}
//saves the database of books in the specified file
//returns 0 if books were stored correctly, or an error code otherwise
int store_books(FILE* file) {
	int i;
	for (i = 0; i < Bookarray->length; i++) {
		fprintf(file, "%d\t%s\t%s\t%d\t%d\n", Bookarray->array[i].id, Bookarray->array[i].title, Bookarray->array[i].authors, Bookarray->array[i].year, Bookarray->array[i].copies);
	}
	fclose(file);
	return 0;
}

//loads the database of books from the specified file
//the file must have been generated by a previous call to store_books()
//returns 0 if books were loaded correctly, or an error code otherwise
int load_books(FILE* file) {
	char *StrLine = (char*)malloc(1024);
	while (fgets(StrLine,1024,file)!=NULL) {
		///StrLine = (char*)malloc(1024);
		//char StrLine[1024] = { '\0' };
		//fgets(StrLine, 1024, file);
		char delims[] = "\t";
		char* result = NULL;
		result = strtok(StrLine, delims);
		Bookarray->array[Bookarray->length].id = atoi(result);
		result = strtok(NULL, delims);
		Bookarray->array[Bookarray->length].title = (char*)malloc(100);
		strcpy(Bookarray->array[Bookarray->length].title, result);
		result = strtok(NULL, delims);
		Bookarray->array[Bookarray->length].authors = (char*)malloc(100);
		strcpy(Bookarray->array[Bookarray->length].authors, result);
		result = strtok(NULL, delims);
		Bookarray->array[Bookarray->length].year = atoi(result);
		result = strtok(NULL, delims);
		Bookarray->array[Bookarray->length].copies = atoi(result);
		Bookarray->length++;
		StrLine = (char*)malloc(1024);
	}
	fclose(file);
	return 0;
}
int load_loans(FILE* file) {
	while (!feof(file)) {
		fscanf(file,"%s%d", Loanarray->array[Loanarray->length].name, Loanarray->array[Loanarray->length].id);
		Loanarray->length++;
	}
	fclose(file);
	return 0;
}
//removes a book from the library
//returns 0 if the book could be successfully removed, or an error code otherwise.
int remove_book(Book book) {
	int i,j;
	for (i = 0; i < Bookarray->length; i++) {
		if (Bookarray->array[i].id == book.id) {
			for (j = i; j < Bookarray->length - 1; j++) {
				Bookarray->array[j] = Bookarray->array[j + 1];
			}
			Bookarray->length--;
			return 0;
		}
	}
	return 1;
}
//finds books with a given title.
//returns a BookArray structure, where the field "array" is a newly allocated array of books, or null if no book with the 
//provided title can be found. The length of the array is also recorded in the returned structure, with 0 in case
//array is the null pointer.
BookArray find_book_by_title(const char* title) {
	int i;
	//int length = 0;
	BookArray* Ba = (BookArray*)malloc(sizeof(BookArray));
	Ba->length = 0;
	Ba->array = (Book*)malloc(100 * sizeof(Book));
	for (i = 0; i < Bookarray->length; i++) {
		if (strcmp(title, Bookarray->array[i].title) == 0) {
			Ba->array[Ba->length] = Bookarray->array[i];
			Ba->length++;
		}
	}
	return *Ba;
}
//finds books with the given authors.
//returns a BookArray structure, where the field "array" is a newly allocated array of books, or null if no book with the 
//provided title can be found. The length of the array is also recorded in the returned structure, with 0 in case
//array is the null pointer.
BookArray find_book_by_author(const char* author) {
	int i;
	//int length = 0;
	BookArray* Ba = (BookArray*)malloc(sizeof(BookArray));
	Ba->length = 0;
	Ba->array = (Book*)malloc(100 * sizeof(Book));
	for (i = 0; i < Bookarray->length; i++) {
		if (strcmp(author, Bookarray->array[i].authors) == 0) {
			Ba->array[Ba->length] = Bookarray->array[i];
			Ba->length++;
		}
	}
	return *Ba;
}

//finds books published in the given year.
//returns a BookArray structure, where the field "array" is a newly allocated array of books, or null if no book with the 
//provided title can be found. The length of the array is also recorded in the returned structure, with 0 in case
//array is the null pointer.
BookArray find_book_by_year(unsigned int year) {
	int i;
	//int length = 0;
	BookArray* Ba = (BookArray*)malloc(sizeof(BookArray));
	Ba->length = 0;
	Ba->array = (Book*)malloc(100 * sizeof(Book));
	for (i = 0; i < Bookarray->length; i++) {
		if (year == Bookarray->array[i].year) {
			Ba->array[Ba->length] = Bookarray->array[i];
			Ba->length++;
		}
	}
	return *Ba;
}

