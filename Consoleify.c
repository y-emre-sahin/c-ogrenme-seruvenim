#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct sarki
{
    char ad[50];
    char sanatci[50];
    struct sarki *next;
    struct sarki *prev;
};

// --- EKLEME ---
struct sarki *sarkiEkle(struct sarki *head, char ad[50], char sanatci[50])
{
    struct sarki *yeniSarki = malloc(sizeof(struct sarki));
    strcpy(yeniSarki->ad, ad);
    strcpy(yeniSarki->sanatci, sanatci);
    yeniSarki->next = NULL;

    if (head == NULL)
    {
        yeniSarki->prev = NULL;
        return yeniSarki;
    }

    struct sarki *temp;
    temp = head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = yeniSarki;
    yeniSarki->prev = temp;

    return head;
}

struct sarki *sarkiCikar(struct sarki *head, char silinecekIsim[50])
{
    struct sarki *temp = head;
    struct sarki *onceki = NULL;

    if (head == NULL)
    {
        printf("Liste zaten bos.\n");
        return NULL;
    }

    // Baştakini silme
    if (strcmp(head->ad, silinecekIsim) == 0)
    {
        head = head->next;
        if (head != NULL)
        {
            head->prev = NULL;
        }
        free(temp);
        printf("%s silindi\n", silinecekIsim);
        return head;
    }

    // Arama
    while (temp != NULL && strcmp(temp->ad, silinecekIsim) != 0)
    {
        onceki = temp;
        temp = temp->next;
    }

    // Bulunamadıysa
    if (temp == NULL)
    {
        printf("Sarki bulunamadi.\n");
        return head;
    }

    // Silme
    onceki->next = temp->next;
    if (temp->prev != NULL)
    {
        temp->prev->next = temp->next;
    }

    if (temp->next != NULL)
    {
        temp->next->prev = temp->prev;
    }
    free(temp);
    printf("%s silindi.\n", silinecekIsim);

    return head;
}

// --- LİSTELEME ---
void sarkiListe(struct sarki *head)
{
    struct sarki *gezgin;
    gezgin = head;

    if (gezgin == NULL)
    {
        printf("\nHenuz sarki eklemediniz.\n");
        return;
    }

    printf("\n--- LISTE ---\n");
    while (gezgin != NULL)
    {
        printf("Sarki: %s - Sanatci: %s\n", gezgin->ad, gezgin->sanatci);
        gezgin = gezgin->next;
    }
    printf("-------------\n");
}

void sarkiKaydetme(struct sarki *head)
{

    struct sarki *gezgin2;
    gezgin2 = head;
    FILE *dosya = fopen("playlist.txt", "w");
    if (dosya == NULL)
    {
        printf("Dosya acilamadi!\n");
        return;
    }
    while (gezgin2 != NULL)
    {
        fprintf(dosya, "%s;%s\n", gezgin2->ad, gezgin2->sanatci);
        gezgin2 = gezgin2->next;
    }
    fclose(dosya);
}

struct sarki *yerDegistir(struct sarki *head, char ilkSarki[50], char ikinciSarki[50])
{
    if (strcmp(ilkSarki, ikinciSarki) == 0)
        return head;

    struct sarki *prevX = NULL;
    struct sarki *currX = head;
    while (currX != NULL && strcmp(currX->ad, ilkSarki) != 0)
    {
        prevX = currX;
        currX = currX->next;
    }

    struct sarki *prevY = NULL;
    struct sarki *currY = head;
    while (currY != NULL && strcmp(currY->ad, ikinciSarki) != 0)
    {
        prevY = currY;
        currY = currY->next;
    }

    if (currX == NULL || currY == NULL)
    {
        printf("Sarkilar bulunamadi.\n");
        return head;
    }

    if (prevX != NULL)
    {
        prevX->next = currY;
    }
    else
    {
        head = currY;
    }

    if (prevY != NULL)
    {
        prevY->next = currX;
    }
    else
    {
        head = currX;
    }

    struct sarki *temp = currY->next;
    currY->next = currX->next;
    currX->next = temp;

    printf("'%s' ve '%s' yer degistirdi!\n", ilkSarki, ikinciSarki);
    return head;
}

void terstenYazdir(struct sarki *head)
{
    struct sarki *temp = head;

    if (head == NULL)
    {
        printf("Liste bos, tersten yazdirilamaz.\n");
        return;
    }

    while (temp->next != NULL)
    {
        temp = temp->next;
    }

    while (temp != NULL)
    {
        printf("%s\n", temp->ad);
        temp = temp->prev;
    }
}

int main()
{
    int secim = 0;
    char ad[50];
    char sanatci[50];
    struct sarki *muzik = NULL;

    while (secim != 4)
    {
        printf("\n---- MENU ----\n");
        printf("1-Sarki Ekle\n2-Listeyi goster\n3-Sarki cikar\n4-Kaydet ve Cikis\n5-Sarki yer degistir\nSeciminiz: ");
        scanf("%d", &secim);

        if (secim > 5 || secim < 1)
        {
            printf("Hatali secim\n");
            continue;
        }

        switch (secim)
        {
        case 1:
            printf("Sarki Adi: ");
            scanf(" %[^\n]", ad);
            printf("Sanatci: ");
            scanf(" %[^\n]", sanatci);
            muzik = sarkiEkle(muzik, ad, sanatci);
            printf("Sarki eklendi!\n");
            break;

        case 2:
            sarkiListe(muzik);
            terstenYazdir(muzik);
            break;

        case 3:
            char cikarilacakIsim[50];
            printf("Silinecek Sarki: ");
            scanf(" %[^\n]", cikarilacakIsim);
            muzik = sarkiCikar(muzik, cikarilacakIsim);
            break;

        case 4:
            sarkiKaydetme(muzik);
            printf("Liste 'playlist.txt' dosyasina kaydedildi.\n");
            break;
        case 5:
            char ilkSarki[50];
            char ikinciSarki[50];
            printf("degistirmek istediginiz ilk sarkinin adini girin:");
            scanf(" %[^\n]", ilkSarki);
            printf("degistirmek istediginiz ikini sarkinin adini girin:");
            scanf(" %[^\n]", ikinciSarki);
            muzik = yerDegistir(muzik, ilkSarki, ikinciSarki);
            break;
        }
    }
    return 0;
}