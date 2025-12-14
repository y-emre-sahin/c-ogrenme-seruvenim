#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct musteri
{
    int musteriNo;
    struct musteri *next;
};

struct musteri *front = NULL;
struct musteri *rear = NULL;

void enqueue(int numara)
{

    struct musteri *yeniMusteri = malloc(sizeof(struct musteri));
    yeniMusteri->musteriNo = numara;
    yeniMusteri->next = NULL;

    if (front == NULL)
    {
        front = yeniMusteri;
        rear = yeniMusteri;
    }
    else
    {
        rear->next = yeniMusteri;
        rear = yeniMusteri;
    }
}
void yazdir()
{

    if (front == NULL)
    {
        printf("Kuyruk bos.\n");
        return;
    }

    struct musteri *temp = front;

    printf("Kuyruk: ");
    while (temp != NULL)
    {
        printf("%d -> ", temp->musteriNo);
        temp = temp->next;
    }
    printf("NULL\n");
}

int main()
{

    enqueue(100);
    enqueue(200);
    enqueue(300);
    enqueue(400);

    yazdir();

    return 0;
}