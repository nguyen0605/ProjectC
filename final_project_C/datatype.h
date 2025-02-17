// noi import cac thu vien, khai bao cac struct
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include<windows.h>

#define CATEGORY_FILE "category.bin"
#define MAX_CATEGORIES 50

#define FILE_NAME "product.bin"
#define MAX_PRODUCTS 100

#define ADMIN_FILE "admin.txt"
#define MAX_USERNAME 50
#define MAX_PASSWORD 50

extern int product_count;//extern dung de khai bao bien toan cuc da duoc dinh nghia o 1 file .c de tranh loi undeclared identifier
extern int category_count;
extern char password[MAX_PASSWORD];

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

typedef struct {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
} Admin;

Product products[MAX_PRODUCTS];
Category categories[MAX_CATEGORIES];
Admin admin;
