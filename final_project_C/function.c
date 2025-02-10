// noi trien khai cac ham
#include <stdio.h>
#include "datatype.h" 

void printMainMenu(){
	int choice;
	do{
		printf("\n***************************************\n");
		printf(" ***Store Management System Using C*** \n");
		printf("***************************************\n\n");
		printf("              MAIN MENU               \n");
		printf("=======================================\n");
		printf("[1] Manage Categories\n");
		printf("[2] Manage Product\n");
		printf("[3] Exit program\n");
		printf("=======================================\n");
		printf("Enter your choice: ");
		scanf("%d",&choice);
		
		switch (choice){
			case 1: printCategoryMenu(); break;
			case 2: printProductMenu(); break;
			case 3: printf("Exitting...\n"); break;
			default: printf("Invalid choice!\n");
		}
	}while (choice !=3);
}

void printCategoryMenu(){
	system("cls");
	int choice;
    do {
    	printf("===============================\n");
        printf("        CATEGORY MENU        \n");
        printf("===============================\n");
        printf("[1] Add Category\n");
        printf("[2] Display Categories\n");
        printf("[3] Edit Category\n");
        printf("[4] Delete Category\n");
        printf("[5] Search Category\n");
        printf("[6] Sort Categories\n");
        printf("[7] Back to Main Menu\n");
        printf("===============================\n");
        printf("Enter Your Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addCategory(); break;
            case 2: displayCategories(); break;
            case 3: printf("Editing category...\n"); break;
            case 4: printf("Deleting category...\n"); break;
            case 5: printf("Searching category...\n"); break;
            case 6: printf("Sorting categories...\n"); break;
            case 7: system("cls"); return;
            default: printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 7);
}

void printProductMenu(){
	system("cls");
	int choice;
    do {
        printf("===============================\n");
        printf("        PRODUCT MENU        \n");
        printf("===============================\n");
        printf("[1] Add Product\n");
        printf("[2] Display Products\n");
        printf("[3] Edit Product\n");
        printf("[4] Delete Product\n");
        printf("[5] Search Product\n");
        printf("[6] Sort Products\n");
        printf("[7] Filter Products\n");
        printf("[8] Back to Main Menu\n");
        printf("===============================\n");
        printf("Enter Your Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: printf("Adding product...\n"); break;
            case 2: printf("Displaying products...\n"); break;
            case 3: printf("Editing product...\n"); break;
            case 4: printf("Deleting product...\n"); break;
            case 5: printf("Searching product...\n"); break;
            case 6: printf("Sorting products...\n"); break;
            case 7: printf("Filtering products...\n"); break;
            case 8: system("cls"); return;
            default: printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 8);
}

void saveProductsToFile(){
	FILE *f=fopen(FILE_NAME,"wb");
	if(!f){
		printf("Error saving products!");
		return;
	}
	fwrite(&product_count,sizeof(int),1,f);
	fwrite(products, sizeof(Product), product_count, f);
	fclose(f);
}

void loadProductsFromFile(){
	FILE *f=fopen(FILE_NAME,"rb");
	if(!f){
		printf("Error loading products!");
		return;
	}
	fread(&product_count,sizeof(int),1,f);
	fread(products, sizeof(Product), product_count, f);
    fclose(f);
}

void saveCategoriesToFile() {
    FILE *f = fopen(CATEGORY_FILE, "wb");
    if (!f) {
        printf("Error saving categories!\n");
        return;
    }
    fwrite(&category_count, sizeof(int), 1, f);
    fwrite(categories, sizeof(Category), category_count, f);
    fclose(f);
}

void loadCategoriesFromFile() {
    FILE *f = fopen(CATEGORY_FILE, "rb");
    if (!f) {
    	printf("Error loading categories!\n");
    	return;
	}
    fread(&category_count, sizeof(int), 1, f);
    fread(categories, sizeof(Category), category_count, f);
    fclose(f);
}

void addCategory(){
	if (category_count >= MAX_CATEGORIES) {
        printf("Category list is full!\n");
        return;
    }
    
    printf("\nEnter category ID: ");
    
    scanf("%s", &categories[category_count].CategoryId);
    fflush(stdin);   
    
    printf("Enter category name: ");
    gets(categories[category_count].CategoryName);
    
	category_count++; 
    saveCategoriesToFile(); 
    
    printf("Add a successful category!\n");
    system("cls");
}

void displayCategories() {
    printf("\nDanh sach danh muc\n");
    printf("+-----+----------------------+\n");
    printf("| ID  | Ten danh muc         |\n");
    printf("+-----+----------------------+\n");
    
    int i; 
    for(i = 0; i < category_count; i++) {
        printf("|%-5s|%-22s|\n", categories[i].CategoryId, categories[i].CategoryName);
    }

    printf("+-----+----------------------+\n");
}







