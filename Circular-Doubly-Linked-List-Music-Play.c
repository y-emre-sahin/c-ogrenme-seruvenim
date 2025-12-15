#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct sarki
{
    char isim[50];
    struct sarki *next;
    struct sarki *prev;
};

struct sarki *head = NULL;
struct sarki *tail = NULL;

struct sarki *suAnCalan = NULL;

void sonaSarkiEkle(char *gelenIsim)
{
    struct sarki *yeni = malloc(sizeof(struct sarki));
    strcpy(yeni->isim, gelenIsim);
    yeni->next = head;
    yeni->prev = tail;

    if (head == NULL)
    {
        head = yeni;
        tail = yeni;
        suAnCalan = yeni;
        suAnCalan->next = yeni;
        suAnCalan->prev = yeni;
    }
    else
    {
        tail->next = yeni;
        yeni->prev = tail;
        tail = yeni;
        tail->next = head;
        head->prev = tail;
    }
}

void sonrakiSarki()
{
    if (suAnCalan == NULL)
    {
        printf("liste bos");
        return;
    }
    else
    {
        suAnCalan = suAnCalan->next;
        printf("%s\n", suAnCalan->isim);
    }
}

void oncekiSarki()
{

    if (suAnCalan == NULL)
    {
        printf("liste bos");
        return;
    }
    else
    {
        suAnCalan = suAnCalan->prev;
        printf("%s\n", suAnCalan->isim);
    }
}

void calanSarkiyiSil()
{
    struct sarki *temp = suAnCalan;
    if (suAnCalan == NULL) 
    {
        printf("Liste zaten bos, silinecek sarki yok.\n");
        return;
    }
    if (head == tail) 
    {
        head = NULL;
        tail = NULL;
        suAnCalan = NULL;
        free(temp);
        printf("Son sarki silindi, liste artik bos.\n");
        return;
    }
    if (suAnCalan == tail)
    {
        suAnCalan = suAnCalan->prev;
        printf("son sarki silindi bir oncekine donuldu\n");
        tail = suAnCalan;
        tail->next = head;
        head->prev = tail;
        free(temp);
        printf("%s\n", suAnCalan->isim);
        return;
    }
    else if (suAnCalan == head)
    {
        suAnCalan = suAnCalan->next;
        head = suAnCalan;
        head->prev = tail;
        tail->next = head;
        free(temp);
        printf("%s\n", suAnCalan->isim);
        return ;

    }
    else
    {
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        suAnCalan = suAnCalan->next;
        printf("%s\n", suAnCalan->isim);
        free(temp);
    }
}

int main()
{
    sonaSarkiEkle("Sarki 1");
    sonaSarkiEkle("Sarki 2");
    sonaSarkiEkle("Sarki 3");

    printf("Baslangic: %s\n", suAnCalan->isim);

    sonrakiSarki(); 
    sonrakiSarki(); 
    sonrakiSarki(); 
    sonrakiSarki(); 

    printf("-- Geri Gidiyoruz --\n");
    oncekiSarki(); 
    oncekiSarki(); 

    return 0;
}