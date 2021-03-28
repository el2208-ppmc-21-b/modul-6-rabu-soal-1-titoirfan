#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//Struktur linked list
struct Node{
    char name[20];
    int attack;
    int defense;
    struct Node* next;
};

//Menambahkan karakter baru di awal list
void push(struct Node** team, char name[20], int attack, int defense){
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    strcpy(newNode->name, name);
    newNode->attack = attack;
    newNode->defense = defense;
    newNode->next = *team;
    *team = newNode;
}

//Menukar urutan 2 karakter dalam list
struct Node* swap(struct Node* ptr1, struct Node* ptr2)
{
    struct Node* tmp = ptr2->next;
    ptr2->next = ptr1;
    ptr1->next = tmp;
    return ptr2;
}

//Mengurutkan list dari yang terkecil ke terbesar
void bubbleSort(struct Node** team, int N){
    struct Node** h;
    int i, j, swapped;

    for (i = 0; i <= N; i++) {

        h = team;
        swapped = 0;

        for (j = 0; j < N - i - 1; j++) {

            struct Node* p1 = *h;
            struct Node* p2 = p1->next;

            if (p1->attack > p2->attack) {
                *h = swap(p1, p2);
                swapped = 1;
            }
            if (p1->attack == p2->attack) {
                if(p1->defense > p2->defense){
                    *h = swap(p1, p2);
                    swapped = 1;
                }
            }
            h = &(*h)->next;
        }

        if (swapped == 0)
            break;
    }
}

//Memulai penyerangan dalam game
void startGame(struct Node *pemburu, struct Node *iblis, int N){
    int i, skorIblis, skorPemburu, sumPemburu, sumIblis;
    skorIblis = 0; skorPemburu = 0;
    sumPemburu = 0; sumIblis = 0;
    printf("Hasil pertarungan\n");
    for(i=0; i<N; i++){
        printf("%s vs %s: ", pemburu->name, iblis->name);
        if((i%2)==0){
            if(pemburu->attack > iblis->defense){
                printf("pemenangnya adalah %s dari tim pemburu\n", pemburu->name);
                skorPemburu++;
                sumPemburu += pemburu->attack;
            } else{
                printf("hasilnya seri\n");
                sumPemburu += pemburu->attack;
                sumIblis += iblis->attack;
            }
        } else{
            if(iblis->attack > pemburu->defense){
                printf("pemenangnya adalah %s dari tim iblis\n", iblis->name);
                skorIblis++;
                sumIblis += iblis->attack;
            } else{
                printf("hasilnya seri\n");
                sumPemburu += pemburu->attack;
                sumIblis += iblis->attack;
            }
        }
        pemburu = pemburu->next;
        iblis = iblis->next;
    }
    printf("\nSkor akhir : %d untuk tim pemburu dan %d untuk tim iblis\n", skorPemburu, skorIblis);
    if(skorPemburu > skorIblis){
        printf("\nPEMENANGANYA ADALAH TIM PEMBURU");
    } else if(skorIblis > skorPemburu){
        printf("\nPEMENANGANYA ADALAH TIM IBLIS");
    } else{
        printf("Jumlah attack pemburu: %d\n", sumPemburu);
        printf("Jumlah attack iblis: %d\n", sumIblis);
        if(sumPemburu > sumIblis){
            printf("\nPEMENANGANYA ADALAH TIM PEMBURU");
        } else{
            printf("\nPEMENANGANYA ADALAH TIM IBLIS");
        }
    }
}

int main(){
    int N, i;
    struct Node *pemburu, *iblis, *temp;

    pemburu = (struct Node*)malloc(sizeof(struct Node));
    iblis = (struct Node*)malloc(sizeof(struct Node));
    temp = (struct Node*)malloc(sizeof(struct Node));
    pemburu = NULL;
    iblis = NULL;
    printf("Masukkan jumlah karakter: ");
    scanf("%d", &N);

    printf("\n#Tim Pemburu\n");
    for (i=0; i<N; i++){
        printf("Masukkan nama pemburu ke-%d: ", i+1);
        scanf("%s", &(temp->name));
        printf("Masukkan attack pemburu ke-%d: ", i+1);
        scanf("%d", &(temp->attack));
        printf("Masukkan defense pemburu ke-%d: ", i+1);
        scanf("%d", &(temp->defense));
        printf("\n");
        push(&pemburu, temp->name, temp->attack, temp->defense);
    }
    printf("\n#Tim Iblis\n");
    for (i=0; i<N; i++){
        printf("Masukkan nama iblis ke-%d: ", i+1);
        scanf("%s", &(temp->name));
        printf("Masukkan attack iblis ke-%d: ", i+1);
        scanf("%d", &(temp->attack));
        printf("Masukkan defense iblis ke-%d: ", i+1);
        scanf("%d", &(temp->defense));
        printf("\n");
        push(&iblis, temp->name, temp->attack, temp->defense);
    }

    bubbleSort(&pemburu, N);
    bubbleSort(&iblis, N);
    startGame(pemburu, iblis, N);

    return 0;
}
