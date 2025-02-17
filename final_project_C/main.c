
#include "function.h"
#include "datatype.h"

int product_count ;
int category_count ;

int main(int argc, char *argv[]) {
	loadProductsFromFile();
	loadCategoriesFromFile();
	printMainMenu();
	return 0;
}
