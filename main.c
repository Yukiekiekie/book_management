#include "book_management.h"
#include<stdlib.h>
#include<string.h>
/*
* books.txt
* loans.txt
* users.txt
*/
//BookArray* Bookarray = (BookArray*)malloc(sizeof(BookArray));//ʵ����BookArray


int main() {
	Bookarray = (BookArray*)malloc(sizeof(BookArray));
	Bookarray->length = 0;
	Bookarray->array = (Book*)malloc(100 * sizeof(Book));
	Loanarray = (LoanArray*)malloc(sizeof(LoanArray));
	Loanarray->length = 0;
	FILE* fp;
	FILE* fp_loan;
	fp = fopen("books.txt", "rb");
	if (fp != NULL) {
		load_books(fp);
	}
	fp_loan = fopen("loans.txt", "rb");
	if (fp_loan != NULL) {

	}
	int choo;//chooice
	int i;
	char book_menu[6][8] = { "ID","Title","Authors","year","copies" };
	int main_t = 1;
	while (1) {
		if (main_t == 0) { break; }
		menu();
		
		scanf("%d",&choo);
		
			//register
		if( choo== 1)
		{
			int temp = 0;
			char username_1[20];
			char password_1[20];
			char username_exit[20];
			char password_exit[20];
			printf("Please enter a username:");
			scanf("%s", username_1);
			FILE* fin_user;
			fin_user = fopen("users.txt", "rb");
			if (fin_user != NULL) {
				while (!feof(fin_user)) {
					fscanf(fin_user, "%s%s", username_exit, password_exit);
					if (strcmp(username_exit, username_1) == 0) {
						printf("Sorry,registration unsuccessful,the username you entered already exists.\n");
						temp = 1;
						fclose(fin_user);
						break;
					}
				}
			}
			if (temp == 0) {
				printf("Please enter a password:");
				scanf("%s", password_1);
				fin_user = fopen("users.txt", "ab+");
				fprintf(fin_user, "%s\t%s\n", username_1, password_1);
				printf("Registered library account successfully!\n");
				fclose(fin_user);
			}
			
		}
		//login
		
		else if (choo==2)
		{
			char username_2[20];
			char password_2[20];
			char username_login[20];
			char password_login[20];
			int choo_manager;
			int choo_users;
			printf("Please enter your username:");
			scanf("%s", username_2);
			printf("Please enter your password:");
			scanf("%s", password_2);
			//manager
			if (strcmp(username_2, "librarian") == 0 && strcmp(password_2, "librarian") == 0) {
				int manager_t = 1;
				while (1) {
					if (manager_t == 0) { break; }
					printf("\n(logged in as: %s)\n", username_2);
					admin_menu();
					scanf("%d", &choo_manager);
					switch (choo_manager) {
						//add a book
					case 1:
					{
						int add_t = add_book(*&Bookarray->array[Bookarray->length]);
						if (add_t == 0) {
							printf("Book was successfully added!\n");
							Bookarray->array[Bookarray->length].id = ++Bookarray->length;
							//Bookarray->length++;
						}
						break;
					}
					//Remove a book
					case 2: {
						int remove_ID;
						printf("Enter the ID number of the book you wish to remove:");
						scanf("%d", &remove_ID);
						FILE* borrow_file;
						borrow_file = fopen("loans.txt", "rb");
						char borrow_name_list[50];
						int borrow_ID_list;
						int remove_r = 0;
						if (borrow_file != NULL) {
							while (!feof(borrow_file)) {
								fscanf(borrow_file, "%s%d", borrow_name_list, &borrow_ID_list);
								if (borrow_ID_list == remove_ID) {
									remove_r = 1;
								}
							}
						}
						if (remove_r == 0) {
							Book* book = (Book*)malloc(sizeof(Book));
							book->id = remove_ID;
							int remove_t = remove_book(*book);
							if (remove_t == 0) {
								printf("remove success!\n");
							}
							else {
								printf("remove failed!\n");
							}
						}
						if (remove_r == 1) {
							printf("can't remove!\n");
						}
						break;
					}

						  //Search for books
					case 3: {
						int choo_search_1;
						printf("\nLoading search menu...\n");
						int search_t_2 = 1;
						while (1) {
							if (search_t_2 == 0) { break; }
							search_menu();
							printf(" Option:");
							scanf("%d", &choo_search_1);
							switch (choo_search_1) {
								//find by title
							case 1: {
								char* title = (char*)malloc(100);
								printf("Enter the title of book you with to find:");
								getchar();
								fgets(title, 100, stdin);
								title[strlen(title) - 1] = 0;
								BookArray* find_title = (BookArray*)malloc(sizeof(BookArray));
								*find_title = find_book_by_title(title);
								if (find_title->length == 0) {
									printf("none!\n");
								}
								else {
									printf("%-5s\t%-40s\t%-40s\t%-4s\t%-6s\n", book_menu[0], book_menu[1], book_menu[2], book_menu[3], book_menu[4]);
									for (i = 0; i < find_title->length; i++) {
										printf("%-5d\t%-40s\t%-40s\t%-4d\t%-d\n", find_title->array[i].id, find_title->array[i].title, find_title->array[i].authors, find_title->array[i].year, find_title->array[i].copies);
									}
								}

							}
								  break;
								  //find by authors
							case 2:
							{
								char* author = (char*)malloc(100);
								printf("Enter the authors of book you with to find:");
								getchar();
								fgets(author, 100, stdin);
								author[strlen(author) - 1] = 0;
								BookArray* find_author = (BookArray*)malloc(sizeof(BookArray));
								*find_author = find_book_by_author(author);
								if (find_author->length == 0) {
									printf("none!\n");
								}
								else {
									printf("%-5s\t%-40s\t%-40s\t%-4s\t%-6s\n", book_menu[0], book_menu[1], book_menu[2], book_menu[3], book_menu[4]);
									for (i = 0; i < find_author->length; i++) {
										printf("%-5d\t%-40s\t%-40s\t%-4d\t%-d\n", find_author->array[i].id, find_author->array[i].title, find_author->array[i].authors, find_author->array[i].year, find_author->array[i].copies);
									}
								}
							}
							break;
							//find by year
							case 3:
							{
								unsigned int year_t;
								printf("Please enter year:");
								scanf("%d", &year_t);
								BookArray* BA_year = (BookArray*)malloc(sizeof(BookArray));
								*BA_year = find_book_by_year(year_t);
								if (BA_year->length == 0) {
									printf("none!\n");
								}
								else {
									printf("%-5s\t%-40s\t%-40s\t%-4s\t%-6s\n", book_menu[0], book_menu[1], book_menu[2], book_menu[3], book_menu[4]);
									for (i = 0; i < BA_year->length; i++) {
										printf("%-5d\t%-40s\t%-40s\t%-4d\t%-d\n", BA_year->array[i].id, BA_year->array[i].title, BA_year->array[i].authors, BA_year->array[i].year, BA_year->array[i].copies);
									}
								}
								break;
							}
							//return
							case 4:
								search_t_2 = 0;
								break;
							default:
								break;
							}
						}
						break;
					}
						  //Display all books
					case 4:
						printf("%-5s\t%-40s\t%-40s\t%-4s\t%-6s\n", book_menu[0], book_menu[1], book_menu[2], book_menu[3], book_menu[4]);
						//printf("len==%d\n", Bookarray->length);
						//printf("id==%d\n", Bookarray->array[Bookarray->length - 1].id);
						for (i = 0; i < Bookarray->length; i++) {
							printf("%-5d\t%-40s\t%-40s\t%-4d\t%-d\n", Bookarray->array[i].id, Bookarray->array[i].title, Bookarray->array[i].authors, Bookarray->array[i].year, Bookarray->array[i].copies);
						}
						break;
						//Log out
					case 5:
						manager_t = 0;
						break;
					default:
						printf("echo:%c\n",choo);
						break;
					}
				}
			}
			//users
			FILE* fin_login;
			int temp_login = 0;
			fin_login = fopen("users.txt", "rb");
			if (fin_login != NULL) {
				while (!feof(fin_login)) {
					fscanf(fin_login, "%s%s", username_login, password_login);
					if (strcmp(username_login, username_2) == 0 && strcmp(password_login, password_2) == 0) {
						temp_login = 1;
						break;
					}
				}
				fclose(fin_login);
			}
			//successful
			if (temp_login == 1) {
				int user_t = 1;
				while (1) {
					if (user_t == 0) { break; }
					printf("\n(logged in as: %s)", username_2);
					user_menu();
					scanf("%d", &choo_users);
					switch (choo_users) {
						//Borrow a book
					case 1:
					{
						int borrow_ID;
						int z = 0;
						int j;
						printf("Enter the number of the book you wish to borrow:");
						scanf("%d", &borrow_ID);
						FILE* borrow_file;
						borrow_file = fopen("loans.txt", "rb");
						int borrow_ID_list;
						char borrow_name_list[50];
						int temp_borrow = 0;
						if (borrow_file != NULL) {
							while (!feof(borrow_file)) {
								fscanf(borrow_file, "%s%d", borrow_name_list, &borrow_ID_list);
								if (borrow_ID_list == borrow_ID && strcmp(borrow_name_list, username_2) == 0) {
									printf("Sorry, you already have a copy of this book on loan\n");
									temp_borrow = 1;
									break;
								}
							}
							fclose(borrow_file);
						}
						if (temp_borrow == 0) {
							for (i = 0; i < Bookarray->length; i++) {
								if (Bookarray->array[i].id == borrow_ID) {
									if (Bookarray->array->copies >= 1) {
										Bookarray->array->copies -= 1;
										Loanarray->array[Loanarray->length].id = borrow_ID;
										strcpy(Loanarray->array[Loanarray->length].name, username_2);
										Loanarray->length++;
										printf("You have successfully borrwoed the book!\n");
										borrow_file = fopen("loans.txt", "wb");
										for (j = 0; j < Loanarray->length; j++) {
											fprintf(borrow_file, "%s\t%d", username_2, borrow_ID);
										}
									}
								}
							}
							fclose(borrow_file);
						}
						break;
					}
					//Return a book
					case 2:
					{
						FILE* borrow_file;
						borrow_file = fopen("loans.txt", "rb");
						int borrow_ID_list;
						char borrow_name_list[50];
						printf("Below is the list of books you are currently borrowing:\n");
						printf("%-5s\t%-40s\t%-40s\t%-4s\t%-6s\n", book_menu[0], book_menu[1], book_menu[2], book_menu[3], book_menu[4]);
						if (borrow_file != NULL) {
							while (!feof(borrow_file)) {
								fscanf(borrow_file, "%s%d", borrow_name_list, &borrow_ID_list);
								Loanarray->array[Loanarray->length].id = borrow_ID_list;
								strcpy(Loanarray->array[Loanarray->length].name, borrow_name_list);
								Loanarray->length++;
								if (strcmp(borrow_name_list, username_2) == 0) {
									for (i = 0; i < Bookarray->length; i++) {
										if (Bookarray->array[i].id == borrow_ID_list)
											printf("%-5d\t%-40s\t%-40s\t%-4d\t%-d\n", Bookarray->array[i].id, Bookarray->array[i].title, Bookarray->array[i].authors, Bookarray->array[i].year, Bookarray->array[i].copies);
									}
								}
							}
						}
						fclose(borrow_file);
						printf("Enter the ID number of the book you wish to return:");
						unsigned int return_ID;
						scanf("%d", &return_ID);
						for (i = 0; i < Loanarray->length; i++) {
							if (return_ID == Loanarray->array->id && strcmp(Loanarray->array->name, username_2) == 0) {
								printf("Return book successfully!\n");
								Loanarray->array->id = 0;
								Loanarray->length--;
							}
						}
						borrow_file = fopen("loans.txt", "wb");
						for (i = 0; i < Loanarray->length; i++) {
							if (Loanarray->array[i].id != 0) {
								fprintf(borrow_file, "%s\t%d\n", Loanarray->array[i].name, Loanarray->array->id);
							}
						}

						break;
					}
					//Search for books
					case 3:
					{
						int choo_3;
						int sear_t = 1;
						printf("\nLoading search menu...\n");
						while (1) {
							if (sear_t == 0) {
								break;
							}
							search_menu();
							printf(" Option:");
							scanf("%d", &choo_3);
							switch (choo_3) {
								//find by title
							case 1: {
								char* title = (char*)malloc(100);
								printf("Enter the title of book you with to find:");
								getchar();
								fgets(title, 100, stdin);
								title[strlen(title) - 1] = 0;
								BookArray* find_title = (BookArray*)malloc(sizeof(BookArray));
								*find_title = find_book_by_title(title);
								if (find_title->length == 0) {
									printf("none!\n");
								}
								else {
									printf("%-5s\t%-40s\t%-40s\t%-4s\t%-6s\n", book_menu[0], book_menu[1], book_menu[2], book_menu[3], book_menu[4]);
									for (i = 0; i < find_title->length; i++) {
										printf("%-5d\t%-40s\t%-40s\t%-4d\t%-d\n", find_title->array[i].id, find_title->array[i].title, find_title->array[i].authors, find_title->array[i].year, find_title->array[i].copies);
									}
								}

							}
								  break;
								  //find by authors
							case 2:
							{
								char* author = (char*)malloc(100);
								printf("Enter the authors of book you with to find:");
								getchar();
								fgets(author, 100, stdin);
								author[strlen(author) - 1] = 0;
								BookArray* find_author = (BookArray*)malloc(sizeof(BookArray));
								*find_author = find_book_by_author(author);
								if (find_author->length == 0) {
									printf("none!\n");
								}
								else {
									printf("%-5s\t%-40s\t%-40s\t%-4s\t%-6s\n", book_menu[0], book_menu[1], book_menu[2], book_menu[3], book_menu[4]);
									for (i = 0; i < find_author->length; i++) {
										printf("%-5d\t%-40s\t%-40s\t%-4d\t%-d\n", find_author->array[i].id, find_author->array[i].title, find_author->array[i].authors, find_author->array[i].year, find_author->array[i].copies);
									}
								}

							}
							break;
							//find by year
							case 3:
							{
								unsigned int year_t;
								printf("Please enter year:");
								scanf("%d", &year_t);
								BookArray* BA_year = (BookArray*)malloc(sizeof(BookArray));
								*BA_year = find_book_by_year(year_t);
								if (BA_year->length == 0) {
									printf("none!\n");
								}
								else {
									printf("%-5s\t%-40s\t%-40s\t%-4s\t%-6s\n", book_menu[0], book_menu[1], book_menu[2], book_menu[3], book_menu[4]);
									for (i = 0; i < BA_year->length; i++) {
										printf("%-5d\t%-40s\t%-40s\t%-4d\t%-d\n", BA_year->array[i].id, BA_year->array[i].title, BA_year->array[i].authors, BA_year->array[i].year, BA_year->array[i].copies);
									}
								}

								break;
							}
							//return
							case 4:
								sear_t = 0;
								break;
							default:
								break;
							}
						}
						break;
					}
					//Display all books
					case 4:
						printf("%-5s\t%-40s\t%-40s\t%-4s\t%-6s\n", book_menu[0], book_menu[1], book_menu[2], book_menu[3], book_menu[4]);
						for (i = 0; i < Bookarray->length; i++) {
							printf("%-5d\t%-40s\t%-40s\t%-4d\t%-d\n", Bookarray->array[i].id, Bookarray->array[i].title, Bookarray->array[i].authors, Bookarray->array[i].year, Bookarray->array[i].copies);
						}
						break;
						//Log out
					case 5:
						user_t = 0;
						break;
					default:
						break;
					}
				}
			}
			else {
				printf("login failed!\n");

			}
			
		}
		
		//Search for books
		else if (choo ==3)
		{
			int choo_search_1;
			printf("\nLoading search menu...\n");
			int search_t_1 = 1;
			while (1) {
				if (search_t_1 == 0) { break; }
				search_menu();
				printf(" Option:");
				scanf("%d", &choo_search_1);
				switch (choo_search_1) {
					//find by title
				case 1: {
					char* title = (char*)malloc(100);
					printf("Enter the title of book you with to find:");
					getchar();
					fgets(title, 100, stdin);
					title[strlen(title) - 1] = 0;
					BookArray* find_title = (BookArray*)malloc(sizeof(BookArray));
					*find_title = find_book_by_title(title);
					if (find_title->length == 0) {
						printf("none!\n");
					}
					else {
						printf("%-5s\t%-40s\t%-40s\t%-4s\t%-6s\n", book_menu[0], book_menu[1], book_menu[2], book_menu[3], book_menu[4]);
						for (i = 0; i < find_title->length; i++) {
							printf("%-5d\t%-40s\t%-40s\t%-4d\t%-d\n", find_title->array[i].id, find_title->array[i].title, find_title->array[i].authors, find_title->array[i].year, find_title->array[i].copies);
						}
					}
	  				break;
				}
				
					  //find by authors
				case 2:
				{
					char* author = (char*)malloc(100);
					printf("Enter the authors of book you with to find:");
					getchar();
					fgets(author, 100, stdin);
					author[strlen(author) - 1] = 0;
					BookArray* find_author = (BookArray*)malloc(sizeof(BookArray));
					*find_author = find_book_by_author(author);
					if (find_author->length == 0) {
						printf("none!\n");
					}
					else {
						printf("%-5s\t%-40s\t%-40s\t%-4s\t%-6s\n", book_menu[0], book_menu[1], book_menu[2], book_menu[3], book_menu[4]);
						for (i = 0; i < find_author->length; i++) {
							printf("%-5d\t%-40s\t%-40s\t%-4d\t%-d\n", find_author->array[i].id, find_author->array[i].title, find_author->array[i].authors, find_author->array[i].year, find_author->array[i].copies);
						}

					}
				break;
				}
			
				//find by year
				case 3:
				{
					int year_t;
					printf("Please enter year:");
					scanf("%d", &year_t);
					printf("year_t == %d\n",year_t);
					BookArray* BA_year = (BookArray*)malloc(sizeof(BookArray));
					*BA_year = find_book_by_year(year_t);
					if (BA_year->length == 0) {
						printf("none!\n");
					}
					else {
						printf("%-5s\t%-40s\t%-40s\t%-4s\t%-6s\n", book_menu[0], book_menu[1], book_menu[2], book_menu[3], book_menu[4]);
						for (i = 0; i < BA_year->length; i++) {
							printf("%-5d\t%-40s\t%-40s\t%-4d\t%-d\n", BA_year->array[i].id, BA_year->array[i].title, BA_year->array[i].authors, BA_year->array[i].year, BA_year->array[i].copies);
						}
					}
					break;
				
				}
				//return
				case 4:
					search_t_1 = 0;
					break;
				default:
					break;
				}
			}
			
		}
		
		//Display all books
		else if (choo ==4)
		{
			printf("%-5s\t%-40s\t%-40s\t%-4s\t%-6s\n", book_menu[0], book_menu[1], book_menu[2], book_menu[3], book_menu[4]);
			for (i = 0; i < Bookarray->length; i++) {
				printf("%-5d\t%-40s\t%-40s\t%-4d\t%-d\n", Bookarray->array[i].id, Bookarray->array[i].title, Bookarray->array[i].authors, Bookarray->array[i].year, Bookarray->array[i].copies);
			}
		
		}
		else if (choo== 5)
		{
			main_t = 0;
			printf("Thank you for using the library!\nGoodbye!\n");
			
		}
		else {
			printf("Sorry, the option you entered was invalid,please try anain.\n");
			
		}
		
	}
	FILE* fp_store;
	fp_store = fopen("books.txt", "wb");
	store_books(fp_store);
	//system("pause");
	return 0;
}

