#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct harf
{
    char karakter;
    struct harf *next;
};

struct harf *top = NULL;

void push(char c)
{
    struct harf *yeni = malloc(sizeof(struct harf));
    yeni->karakter = c;
    yeni->next = top;
    top = yeni;
}

char pop()
{
    if (top == NULL)
        return '\0';
    struct harf *temp = top;
    char c = temp->karakter;
    top = top->next;
    free(temp);
    return c;
}

int parantezKontrol(char *ifade)
{
    for (int i = 0; ifade[i] != '\0'; i++)
    {
        char gelen = ifade[i];

        if (gelen == '(' || gelen == '[' || gelen == '{')
        {
            push(gelen);
        }
        else if (gelen == ')' || gelen == ']' || gelen == '}')
        {
            if (top == NULL)
                return 0;

            char cikan = pop();

            if (gelen == ')' && cikan != '(')
                return 0;
            if (gelen == ']' && cikan != '[')
                return 0;
            if (gelen == '}' && cikan != '{')
                return 0;
        }
    }

    if (top == NULL)
        return 1;
    else
        return 0;
}

int main()
{
    char *test1 = "{[()]}";
    char *test2 = "{[(])}";
    char *test3 = "((("; 

    if (parantezKontrol(test1))
        printf("%s -> Gecerli \n", test1);
    else
        printf("%s -> Gecersiz \n", test1);

    while (pop() != '\0');

    if (parantezKontrol(test2))
        printf("%s -> Gecerli \n", test2);
    else
        printf("%s -> Gecersiz\n", test2);

    while (pop() != '\0');

    if (parantezKontrol(test3))
        printf("%s -> Gecerli \n", test3);
    else
        printf("%s -> Gecersiz \n", test3);

    return 0;
}