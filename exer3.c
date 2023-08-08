#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Product
{
    double old_price;
    double new_price;
    unsigned int id;
    char product_type;
    char product_name[20];
};


double randomDouble(double min, double max)
{
    return min + ((double)rand() / RAND_MAX) * (max - min);
}

// randiom char ot a do d
char randomProductType()
{
    return 'A' + rand() % 4;
}

//random ime na produkt
void randomProductName(char *name)
{
    static const char *names[] = {"Product A", "Product B", "Product C", "Product D"};
    int index = rand() % 4;
    strcpy(name, names[index]);
}

int compareProducts(const void *a, const void *b)
{
    struct Product *productA = (struct Product *)a;
    struct Product *productB = (struct Product *)b;

    double diffPriceA = productA->new_price - productA->old_price;
    double diffPriceB = productB->new_price - productB->old_price;

    if (fabs(diffPriceA - diffPriceB) < 0.01) {
        if (productA->product_type != productB->product_type) {
            return productB->product_type - productA->product_type;
        }
        int nameComparison = strcmp(productA->product_name, productB->product_name);
        if (nameComparison != 0) {
            return nameComparison;
        }
        return productA->id - productB->id;
    }

    return (diffPriceB - diffPriceA) > 0 ? 1 : -1;
}

int main()
{
    srand(time(NULL));

    struct Product products[40];

    for (int i = 0; i < 40; i++) {
        products[i].old_price = randomDouble(4.99, 100.45);
        products[i].new_price = randomDouble(4.99, 100.45);
        products[i].id = i + 1;
        products[i].product_type = randomProductType();
        randomProductName(products[i].product_name);
    }

    printf("Products before sorting:\n");
    for (int i = 0; i < 40; i++) {
        printf("ID: %u, Type: %c, Name: %s, Old Price: %.2lf, New Price: %.2lf\n",
            products[i].id, products[i].product_type, products[i].product_name,
            products[i].old_price, products[i].new_price);
    }

    qsort(products, 40, sizeof(struct Product), compareProducts);

    printf("\nProducts after sorting:\n");
    for (int i = 0; i < 40; i++) {
        printf("ID: %u, Type: %c, Name: %s, Old Price: %.2lf, New Price: %.2lf\n",
            products[i].id, products[i].product_type, products[i].product_name,
            products[i].old_price, products[i].new_price);
    }

    return 0;
}//end of main
