// noi trien khai cac ham
#include "datatype.h"

int i,j,k;

int isNumeric(const char *str) {
    if (str[0] == '\0') return 0; 
    for (i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) { 
            return 0; 
        }
    }
    return 1; 
} 

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
//CATEGORY
void printCategoryMenu(){
	system("cls");
	int choice;
    do {
    	printf("\n***************************************\n");
		printf(" ***Store Management System Using C*** \n");
		printf("***************************************\n\n");
    	printf("    ===============================\n");
        printf("             CATEGORY MENU        \n");
        printf("    ===============================\n");
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
    int valid;

    do {
        valid = 1;
        
        fflush(stdin); 
        printf("\nEnter category ID: ");
        fgets(newCategory.CategoryId, sizeof(newCategory.CategoryId), stdin);
        trimNewline(newCategory.CategoryId);

        if (strlen(newCategory.CategoryId) == 0) {  //ktra chuoi rong
            printf("ID cannot be empty! Please enter again.\n");
            valid = 0;
        } else if(!isNumeric(newCategory.CategoryId)){   // ktra chuoi chua chu khong
        	printf("Invalid ID! Please enter only numbers.\n");
            valid = 0;
		} else {
            for (i = 0; i < category_count; i++) {   // ktra bi trung id
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
}


void displayCategories() {
	system("cls");
	
    printf("\n   List of categories\n");
    printf("+-----+----------------------+\n");
    printf("| ID  | Name of categories   |\n");
    printf("+-----+----------------------+\n");
    
    for(i = 0; i < category_count; i++) {
        printf("|%-5s|%-22s|\n", categories[i].CategoryId, categories[i].CategoryName);
    }

    printf("+-----+----------------------+\n");
}

void editCategory(){
	
	system("cls");
	
	char id[10];
	int found=0, valid;
	
	fflush(stdin);
	printf("Enter category ID: ");
	fgets(id,sizeof(id),stdin);
	trimNewline(id);
	
	for(i=0;i<category_count;i++){
		if(strcmp(id,categories[i].CategoryId)==0){
			
			printf("\n        Category %s         \n",categories[i].CategoryId);
            printf("+-----+----------------------+\n");
            printf("| ID  | Name of categories   |\n");
            printf("+-----+----------------------+\n");
            printf("|%-5s|%-22s|\n", categories[i].CategoryId, categories[i].CategoryName);
            printf("+-----+----------------------+\n");
			
			do{
				valid=1;
				
				printf("Enter the new name: ");
	    		fgets(categories[i].CategoryName,sizeof(categories[i].CategoryName),stdin);
		    	trimNewline(categories[i].CategoryName);
		    	
		    	if (strlen(categories[i].CategoryName) == 0) {
                    printf("Category name cannot be empty! Please enter again.\n");
                    valid = 0;
                } else {
                	int cnt=0;
                    for (j = 0; j < category_count; j++) {
                        if (strcmp(categories[i].CategoryName, categories[j].CategoryName) == 0) {
                        cnt++;
                        }
                    }
                    if(cnt>1){
                    	printf("Category name has existed, please enter another name!\n");
                    	valid = 0;
					}
                }
			}while(!valid);
			
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
	
	char choice[10];
	for(i=0;i<category_count;i++){
		if(strcmp(id,categories[i].CategoryId)==0){
			
			printf("Confirmation of the category deletion?(yes/no)\n");
			fgets(choice,sizeof(choice),stdin);
			trimNewline(choice);
			
			if(strcmp(choice,"yes")==0){
				j=0;
				while(j<product_count){
					if(strcmp(id,products[j].categoryID)==0){
						for(k=j;k<product_count-1;k++){
							products[k]=products[k+1]; 
						}
						product_count--;
					}else{
						j++;
					}
				}
				
				for(j=i;j<category_count-1;j++){
					categories[j]=categories[j+1];
				}
				category_count--;
				saveCategoriesToFile();
		    	printf("Delete success!\n");
		    	found=1;
		    	break;	
			}else if(strcmp(choice,"no")==0){
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
    
    while(1){
    	fflush(stdin);
        printf("Enter the name of product: ");
        fgets(searchTerm, sizeof(searchTerm), stdin);
        trimNewline(searchTerm);
        
        if(strlen(searchTerm)==0){
        	printf("Category name cannot be empty! Please enter again.\n");
		}else break;
	}
    
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
            
            int j; 
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

//PRODUCT
void printProductMenu(){
	system("cls");
	int choice;
    do {
    	printf("\n***************************************\n");
		printf(" ***Store Management System Using C*** \n");
		printf("***************************************\n\n");
        printf("    ===============================\n");
        printf("              PRODUCT MENU        \n");
        printf("    ===============================\n");
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
            case 1: addProduct(); break;
            case 2: displayProducts(); break;
            case 3: editProduct(); break;
            case 4: deleteProduct(); break;
            case 5: searchProduct(); break;
            case 6: sortProducts(); break;
            case 7: filterProducts(); break;
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

void displayProducts(){
	system("cls");
	
	printf("\n                  List of products                   \n");
	printf("+------+----------------+--------+--------+-----------+\n");
	printf("|  ID  |      Name      |  Price |Quantity|Category ID|\n");
	printf("+------+----------------+--------+--------+-----------+\n");
	
	int i;
	for(i=0;i<product_count;i++){
		printf("|%-6s|%-16s|%-8d|%-8d|%-11s|\n",
		products[i].productID,products[i].productName,products[i].price,products[i].quantity,products[i].categoryID);
	}
	printf("+------+----------------+--------+--------+-----------+\n");
} 

void addProduct(){
	system("cls");
	
	if(product_count>= MAX_PRODUCTS){
		printf("List of products is full!\n");
		return;
	}
	
	Product newProduct;
	
	fflush(stdin); 
	char id[5];
	printf("Enter the ID of the category: ");
	fgets(id,sizeof(id),stdin);
	trimNewline(id);
	
	int found=0;
	
	for(i=0;i<category_count;i++){
		if(strcmp(id,categories[i].CategoryId)==0){
			found=1;
		}
	}
	
	if(!found){
		printf("The category ID does not exist!\n");
		return;
	}else{
			int valid;
			
			strcpy(newProduct.categoryID,id);
			do{
				valid=1;
				
				fflush(stdin);
				printf("Enter new product ID: ");
				fgets(newProduct.productID,sizeof(newProduct.productID),stdin);
				trimNewline(newProduct.productID);
				
				if (strlen(newProduct.productID) == 0) {
                    printf("Product ID cannot be empty! Please enter again.\n");
                    valid = 0;
                } else {
                    for (i = 0; i < product_count; i++) {
                        if (strcmp(products[i].productID,newProduct.productID) == 0) {
                        printf("Product ID has existed, please enter another ID!\n");
                        valid = 0;
                        break;
                        }
                    }
                }
			}while(!valid);
			
			do{
				valid=1;
				
				fflush(stdin); 
				printf("Enter new product name: ");
				fgets(newProduct.productName,sizeof(newProduct.productName),stdin);
				trimNewline(newProduct.productName);
				
				if (strlen(newProduct.productName) == 0) {
                    printf("Product name cannot be empty! Please enter again.\n");
                    valid = 0;
                } else {
                    for (i = 0; i < product_count; i++) {
                        if (strcmp(products[i].productName,newProduct.productName) == 0) {
                        printf("Product name has existed, please enter another name!\n");
                        valid = 0;
                        break;
                        }
                    }
                }
			}while(!valid);
			
			do {
                valid = 1;
                printf("Enter New Product Quantity: ");
                scanf("%d",&newProduct.quantity);
                getchar();

                if (newProduct.quantity <=0) {
                printf("The quantity is invalid!(>0)\n");
                valid = 0;
                }
            } while (!valid);
            
            do {
                valid = 1;
                printf("Enter New Product Price: ");
                scanf("%d",&newProduct.price);
                getchar();

                if (newProduct.price <1000) {
                printf("The price is invalid!(>=1000)\n");
                valid = 0;
                }
            } while (!valid);
    }
    products[product_count++]=newProduct;
    saveProductsToFile();

    printf("Add a successful product!\n");
    system("cls");
}

void editProduct(){
	system("cls");
	
	char id[10];
	int found=0, valid;
	
	fflush(stdin);
	printf("Enter category ID: ");
	fgets(id,sizeof(id),stdin);
	trimNewline(id);
	
	for(i=0;i<product_count;i++){
		if(strcmp(products[i].productID,id)==0){
			printf("\n                  List of products                   \n");
        	printf("+------+----------------+--------+--------+-----------+\n");
        	printf("|  ID  |      Name      |  Price |Quantity|Category ID|\n");
        	printf("+------+----------------+--------+--------+-----------+\n");   
        	printf("|%-6s|%-16s|%-8d|%-8d|%-11s|\n",
	    	products[i].productID,products[i].productName,products[i].price,products[i].quantity,products[i].categoryID);
	    	printf("+------+----------------+--------+--------+-----------+\n");
	    	
	    	do{
            	int fn=0;
            	char temp[10];
            	valid = 1;
            	
            	printf("Enter Category ID: ");
            	fflush(stdin);
            	fgets(temp,sizeof(temp),stdin);
            	trimNewline(temp);
            	
            	for(j=0;j<category_count;j++){
            		if(strcmp(temp,categories[j].CategoryId) == 0){
            			fn=1;
            			strcpy(products[i].categoryID, temp);
            			break; 
					}
				}
				
				if(!fn){
					printf("This category ID does not exist, please enter another category ID\n");
					valid=0; 
				}
			}while(!valid);
			
	    	do{
	    		valid=1;
	    		
	    		fflush(stdin); 
	    		printf("Enter New Product Name: ");
	    		fgets(products[i].productName,sizeof(products[i].productName),stdin);
	    		trimNewline(products[i].productName);
	    		
	    		if (strlen(products[i].productName) == 0) {
                    printf("Category name cannot be empty! Please enter again.\n");
                    valid = 0;
                } else {
                	int cnt=0;
                    for (j = 0; j < category_count; j++) {
                        if (strcmp(products[i].productName,products[j].productName) == 0) {
                        cnt++;
                        }
                    }
                    if(cnt>1){
                    	printf("Product name has existed, please enter another name!\n");
                    	valid = 0;
					}
                }
			}while(!valid);
			
			do{
				valid=1;
				
				printf("Enter New Price: ");
				scanf("%d",&products[i].price);
				getchar();
				
				if(products[i].price<=0){
					printf("The price is invalid!(>=1000)\n");
					valid=0;
		    	}
			}while(!valid);
			
			do {
                valid = 1;
                printf("Enter New Product Quantity: ");
                scanf("%d",&products[i].quantity);
                getchar();

                if (products[i].quantity <=0) {
                printf("The quantity is invalid!(>0)\n");
                valid = 0;
                }
            } while (!valid);
			
			saveProductsToFile();
			printf("Successful repair!!\n");
			found=1;
			break;
		}
	}
	if(!found) printf("CANNOT FIND ID IN THE PRODUCT LIST!\n");
}

void deleteProduct(){
	system("cls");
	
	char id[10];
	int found=0;
	
	printf("Enter product ID: ");
	scanf("%s",id);
	getchar();
	
	char choice[10];
	for(i=0;i<product_count;i++){
		if(strcmp(id,products[i].productID)==0){
			
			printf("Confirmation of the product deletion?(yes/no)\n");
			fgets(choice,sizeof(choice),stdin);
			trimNewline(choice);
			
			if(strcmp(choice,"yes")==0){
				for(j=i;j<product_count-1;j++){
					products[j]=products[j+1];
				}
				product_count--;
				saveProductsToFile();
		    	printf("Delete success!\n");
		    	found=1;
		    	break;	
			}else if(strcmp(choice,"no")==0){
				found=1;
				break;
			}else{
				printf("Invalid choice!");
				return;
			}
		}
	}
	if(!found) printf("CANNOT FIND ID IN THE PRODUCT LIST!\n");
}

void searchProduct() {
    system("cls");
    char searchTerm[25];
    int found = 0;

    while(1){
    	fflush(stdin);
        printf("Enter the name of product: ");
        fgets(searchTerm, sizeof(searchTerm), stdin);
        trimNewline(searchTerm);
        
        if(strlen(searchTerm)==0){
        	printf("Product name cannot be empty! Please enter again.\n");
		}else break;
	}
    
    for (i = 0; i < product_count; i++) {
        if (strstr(products[i].productName, searchTerm) != NULL) {
            found = 1;
            break;
        }
    }

    if (found) {
        printf("\n                  List of products                   \n");
        printf("+------+----------------+--------+--------+-----------+\n");
        printf("|  ID  |      Name      |  Price |Quantity|Category ID|\n");
        printf("+------+----------------+--------+--------+-----------+\n");

        for (i = 0; i < product_count; i++) {
            if (strstr(products[i].productName, searchTerm) != NULL) {
                printf("|%-6s|%-16s|%-8d|%-8d|%-11s|\n",
	        	products[i].productID,products[i].productName,products[i].price,products[i].quantity,products[i].categoryID);
            }
        }

        printf("+------+----------------+--------+--------+-----------+\n");
    } else {
        printf("CANNOT FIND NAME OF THE CATEGORY!\n");
    }
}

void sortProducts(){
	system("cls");
	int choice;
    do {
        printf("\n========== SORT PRODUCT LIST ==========\n");
        printf("1. Sort by Name (Ascending A -> Z)\n");
        printf("2. Sort by Name (Descending Z <- A)\n");
        printf("3. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); 

        if (choice == 1 || choice == 2) {
            int ascending = (choice == 1); 
            
            int j; 
            for (i = 0; i < product_count - 1; i++) {
                for (j = 0; j < product_count - i - 1; j++) {
                    if ((ascending && strcmp(products[j].productName,products[j+1].productName) > 0) ||
                        (!ascending && strcmp(products[j].productName,products[j+1].productName) < 0)) {
                       
                        Product temp = products[j];
                        products[j]=products[j+1];
                        products[j+1]=temp;
                    }
                }
            }

            printf("Product list sorted in %s order!\n", ascending ? "ascending" : "descending");
            displayProducts();
            saveProductsToFile(); 
        } 
        else if (choice != 3) {
            printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 3);
    system("cls");
}

//sap xep danh sach san pham
void filterProducts() {
    system("cls");
    int choice;
    do {
        printf("\n========== FILTER PRODUCTS ==========\n");
        printf("1. Filter by Category\n");
        printf("2. Filter by Price Range\n");
        printf("3. Back to Product Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch(choice) {
            case 1: filterByCategory(); break;
            case 2: filterByPrice(); break;
            case 3: system("cls"); return;
            default: printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 3);
}

void filterByCategory() {
	system("cls");
    char categoryId[10];
    int found = 0, hasProducts = 0;
    
    fflush(stdin);
    printf("Enter category ID: ");
    fgets(categoryId, sizeof(categoryId), stdin);
    trimNewline(categoryId);

    for(i = 0; i < category_count; i++) {
        if(strcmp(categoryId, categories[i].CategoryId) == 0) {
            found = 1;
            break;
        }
    }

    if(!found) {
        printf("Category ID does not exist!\n");
        return;
    }

    printf("\n                  List of products                   \n");
    printf("+------+----------------+--------+--------+-----------+\n");
    printf("|  ID  |      Name      |  Price |Quantity|Category ID|\n");
    printf("+------+----------------+--------+--------+-----------+\n");

    for(i = 0; i < product_count; i++) {
        if(strcmp(products[i].categoryID, categoryId) == 0) {
            printf("|%-6s|%-16s|%-8d|%-8d|%-11s|\n",
                products[i].productID, products[i].productName, 
                products[i].price, products[i].quantity, 
                products[i].categoryID);
            hasProducts = 1;
        }
    }

    if(!hasProducts) {
        printf("No products found in this category!\n");
    } else {
        printf("+------+----------------+--------+--------+-----------+\n");
    }
}

void filterByPrice() {
	system("cls");
    int startPrice, endPrice;
    int hasProducts = 0;
    
    printf("Enter start price: ");
    scanf("%d", &startPrice);
    printf("Enter end price: ");
    scanf("%d", &endPrice);
    getchar();

    if(startPrice < 0 || endPrice < 0 || startPrice > endPrice) {
        printf("Invalid price range!\n");
        return;
    }

    printf("\n                  List of products                   \n");
    printf("+------+----------------+--------+--------+-----------+\n");
    printf("|  ID  |      Name      |  Price |Quantity|Category ID|\n");
    printf("+------+----------------+--------+--------+-----------+\n");

    for(i = 0; i < product_count; i++) {
        if(products[i].price >= startPrice && products[i].price <= endPrice) {
            printf("|%-6s|%-16s|%-8d|%-8d|%-11s|\n",
                products[i].productID, products[i].productName, 
                products[i].price, products[i].quantity, 
                products[i].categoryID);
            hasProducts = 1;
        }
    }

    if(!hasProducts) {
        printf("No products found in this price range!\n");
    } else {
        printf("+------+----------------+--------+--------+-----------+\n");
    }
}

//XAC THUC ADMIN 
void saveAdminToFile() {
    FILE *f = fopen(ADMIN_FILE, "w");
    if (!f) {
        printf("Error saving admin information!\n");
        return;
    }
    fprintf(f, "%s\n%s\n", admin.username, admin.password);
    fclose(f);
}

void loadAdminFromFile() {
    FILE *f = fopen(ADMIN_FILE, "r");
    
    if (!f) {
        strcpy(admin.username, "admin");//tai khoan mac dinh
        strcpy(admin.password, "admin123");
        saveAdminToFile();
        return;
    }
    
    if (fgets(admin.username, MAX_USERNAME, f)) {
        admin.username[strcspn(admin.username, "\n")] = 0; 
    }
    if (fgets(admin.password, MAX_PASSWORD, f)) {
        admin.password[strcspn(admin.password, "\n")] = 0; 
    }
    
    fclose(f);
}

void getPasswordInput() { 
    char ch;
    i = 0;  
    
    while (1) {
        ch = getch();
        
        if (ch == 13) {
            password[i] = '\0';
            printf("\n");
            break;
        } else if (ch == 8) { 
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        } else if (i < MAX_PASSWORD - 1) {
            password[i++] = ch;
            printf("*");
        }
    }
}

int loginAdmin() {
    char inputUsername[MAX_USERNAME];
   
    loadAdminFromFile();

    while (1) {
        system("cls");
        printf("\n=================================\n");
        printf("           ADMIN LOGIN           \n");
        printf("=================================\n\n");
        
        printf("Username: ");
        fflush(stdin);
        fgets(inputUsername, sizeof(inputUsername), stdin);
        trimNewline(inputUsername); 
        
        printf("Password: ");
        getPasswordInput();

        if (strcmp(inputUsername, admin.username) == 0 && 
            strcmp(password, admin.password) == 0) {
            printf("\nSign in successfully\n");
            return 1;
        } else {
            printf("\nWrong name or wrong password, please enter again!\n");
            sleep(3);
        }
    }
    return 0;
}
