// noi import cac thu vien, khai bao cac struct
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_PRODUCTS 100
#define MAX_CATEGORIES 50

#define FILE_NAME "product.bin"
#define CATEGORY_FILE "category.bin"

extern int product_count;//extern dung de khai bao bien toan cuc da duoc dinh nghia o 1 file .c de tranh loi undeclared identifier
extern int category_count;


typedef struct{
	int month, day, year;
}Date;

typedef struct{
	char CategoryId[5];
	char CategoryName[15];
}Category;

typedef struct{
	char productID[5];
	char categoryID[5];
	char productName[15];
	int quantity, price;
}Product;

typedef struct{
	char orderID[10];
	char customerID[20];
	Date date;
	Product product;
}Order;

Product products[MAX_PRODUCTS];
Category categories[MAX_CATEGORIES];
