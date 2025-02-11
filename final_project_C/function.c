// noi trien khai cac ham
#include <stdio.h>
#include "datatype.h" 


void trimNewline(char *str) {
    str[strcspn(str, "\n")] = 0;
}

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
            case 3: editCategory(); break;
            case 4: deleteCategory(); break;
            case 5: searchCategoryByName(); break;
            case 6: sortCategories(); break;
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

void addCategory() {
    if (category_count >= MAX_CATEGORIES) {
        printf("Category list is full!\n");
        return;
    }

    Category newCategory;
    int valid, i;

    do {
        valid = 1;
        
        fflush(stdin); 
        printf("\nEnter category ID: ");
        fgets(newCategory.CategoryId, sizeof(newCategory.CategoryId), stdin);
        trimNewline(newCategory.CategoryId);

        if (strlen(newCategory.CategoryId) == 0) {
            printf("ID cannot be empty! Please enter again.\n");
            valid = 0;
        } else {
            for (i = 0; i < category_count; i++) {
                if (strcmp(categories[i].CategoryId, newCategory.CategoryId) == 0) {
                    printf("ID has existed, please enter another ID!\n");
                    valid = 0;
                    break;
                }
            }
        }
    } while (!valid);

    do {
        valid = 1;
        printf("Enter category name: ");
        fgets(newCategory.CategoryName, sizeof(newCategory.CategoryName), stdin);
        trimNewline(newCategory.CategoryName);

        if (strlen(newCategory.CategoryName) == 0) {
            printf("Category name cannot be empty! Please enter again.\n");
            valid = 0;
        } else {
            for (i = 0; i < category_count; i++) {
                if (strcmp(categories[i].CategoryName, newCategory.CategoryName) == 0) {
                    printf("Category name has existed, please enter another name!\n");
                    valid = 0;
                    break;
                }
            }
        }
    } while (!valid);

    categories[category_count++] = newCategory;
    saveCategoriesToFile();

    printf("Add a successful category!\n");
    system("cls");
}


void displayCategories() {
	system("cls");
    printf("\nList of categories\n");
    printf("+-----+----------------------+\n");
    printf("| ID  | Name of categories   |\n");
    printf("+-----+----------------------+\n");
    
    int i; 
    for(i = 0; i < category_count; i++) {
        printf("|%-5s|%-22s|\n", categories[i].CategoryId, categories[i].CategoryName);
    }

    printf("+-----+----------------------+\n");
}

void editCategory(){
	
	system("cls");
	
	char id[10];
	int found=0;
	
	printf("Enter category ID: ");
	scanf("%s",id);
	getchar();
	
	int i;
	for(i=0;i<category_count;i++){
		if(strcmp(id,categories[i].CategoryId)==0){
			printf("Enter the new name: ");
			fgets(categories[i].CategoryName,sizeof(categories[i].CategoryName),stdin);
			trimNewline(categories[i].CategoryName);
			
			saveCategoriesToFile();
			printf("Successful repair!!\n");
			found=1;
			break;
		}
	}
	if(!found) printf("CANNOT FIND ID IN THE CATEGORY!\n");
}

void deleteCategory(){
	system("cls");
	
	char id[10];
	int found=0;
	
	printf("Enter category ID: ");
	scanf("%s",id);
	getchar();
	
	int i;
	char choice[10];
	for(i=0;i<category_count;i++){
		if(strcmp(id,categories[i].CategoryId)==0){
			
			printf("Confirmation of the category deletion?(yes/no)\n");
			fgets(choice,sizeof(choice),stdin);
			trimNewline(choice);
			
			if((strcmp(choice,"yes")==0) || (strcmp(choice,"no")==0)){
				int j;
				for(j=i;j<category_count-1;j++){
					categories[j]=categories[j+1];
				}
				category_count--;
				saveCategoriesToFile();
		    	printf("Delete success!\n");
		    	found=1;
		    	break;	
			}else{
				printf("Invalid choice!");
				return;
			}
		}
	}
	if(!found) printf("CANNOT FIND ID IN THE CATEGORY!\n");
}

void searchCategoryByName() {
    system("cls");
    char searchTerm[25];
    int found = 0;

    fflush(stdin);
    printf("Enter the name of category: ");
    fgets(searchTerm, sizeof(searchTerm), stdin);
    trimNewline(searchTerm);
    
    int i;
    for (i = 0; i < category_count; i++) {
        if (strstr(categories[i].CategoryName, searchTerm) != NULL) {
            found = 1;
            break;
        }
    }

    if (found) {
        printf("\n     List of categories     \n");
        printf("+-----+----------------------+\n");
        printf("| ID  | Name of categories   |\n");
        printf("+-----+----------------------+\n");

        for (i = 0; i < category_count; i++) {
            if (strstr(categories[i].CategoryName, searchTerm) != NULL) {
                printf("|%-5s|%-22s|\n", categories[i].CategoryId, categories[i].CategoryName);
            }
        }

        printf("+-----+----------------------+\n");
    } else {
        printf("CANNOT FIND NAME OF THE CATEGORY!\n");
    }
}

void sortCategories(){
	system("cls");
	int choice;
    do {
        printf("\n========== SORT CATEGORY ==========\n");
        printf("1. Sort by Name (Ascending A -> Z)\n");
        printf("2. Sort by Name (Descending Z <- A)\n");
        printf("3. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); 

        if (choice == 1 || choice == 2) {
            int ascending = (choice == 1); 
            
            int i,j; 
            for (i = 0; i < category_count - 1; i++) {
                for (j = 0; j < category_count - i - 1; j++) {
                    if ((ascending && strcmp(categories[j].CategoryName, categories[j + 1].CategoryName) > 0) ||
                        (!ascending && strcmp(categories[j].CategoryName, categories[j + 1].CategoryName) < 0)) {
                       
                        Category temp = categories[j];
                        categories[j] = categories[j + 1];
                        categories[j + 1] = temp;
                    }
                }
            }

            printf("Categories sorted in %s order!\n", ascending ? "ascending" : "descending");
            displayCategories();
            saveCategoriesToFile(); 
        } 
        else if (choice != 3) {
            printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 3);
    system("cls");
}




