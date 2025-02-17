
#include "function.h"
#include "datatype.h"

int product_count ;
int category_count ;
char password[MAX_PASSWORD];

int main(int argc, char *argv[]) {
	
    while(!loginAdmin()){
    	printf("Login failed!");
	}
	printf("WELCOM, ADMIN!");
	sleep(2);
	system("cls"); 
    
	loadProductsFromFile();
	loadCategoriesFromFile();
	printMainMenu();
	return 0;
}
