#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct product {
	char *name;
	double price;
} product_t;


/*
 * @param ptrProd a pointer to a product struct
 * @return The price of the product pointed by ptrProd
 */
double getPtrPrice(product_t *ptrProd) {
	return ptrProd->price;
}

/*
 *@return the price of the product prod
 */
double getPrice(product_t prod) {
	return prod.price;
}

/*
 * @param ptrProd a pointer to a product_t
 * @return a string on the heap that contains the name of the product pointed by ptrProd or NULL if an error happens 
 * 
 */
char *getPtrName(product_t *ptrProd) {

	if (!ptrProd || !ptrProd->name) 
		return NULL;

	size_t len = strlen(ptrProd->name);
	char *name = malloc(len + 1);
	if (!name) 
		return NULL;

	strcpy(name, ptrProd->name);
	return name;
}

/*
 * @param prod a product
 * @return a string on the heap that contains the name of the product prod or NULL if an error happens
 *
 */
char *getName(product_t prod) {
	
	if (!prod.name) 
		return NULL;

	size_t len = strlen(prod.name);
	char *name = malloc(len + 1);
	if (!name)
		return NULL;
	
	strcpy(name, prod.name);
	return name;
}

/*
 * @param ptrProd A pointer to a product_t
 * @param prod A product_t
 * @return 1 if the two products are the same, i.e., they have the same price and the same name
 *
 */
int prodEquals(product_t *ptrProd, product_t prod) {
	char *name1 = ptrProd->name;
	char *name2 = prod.name;

	if (!name1 || !name2)
		return 0;

	double price1 = ptrProd->price;
	double price2 = prod.price;

	return (strcmp(name1, name2) == 0) && (price1 == price2);
}

int main() {
	printf("Structures and pointers to structures\n");
	return 0;
}

