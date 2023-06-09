#include <stdio.h>
#include <stdlib.h>
#include<time.h>

struct node{            
	int data;
	struct node *next;
};

	
struct node* carkSayilarEkle(int sayilar[],int M){            // Cark fonksiyonunda olusturdugumuz random sayilari
	int i;                                                    // circular linked listlere ekleme
	struct node *head=NULL;
	struct node *tail=NULL;
	
	for (i=0; i<M-1 ;i++){
		struct node* newNode = (struct node*)malloc(sizeof(struct node));
		newNode->data = sayilar[i];
		newNode->next = NULL;
		
		if(head==NULL){
			head= newNode;
			tail= newNode;
		}
		else {
			tail->next = newNode;
			tail= newNode;
		}
	}
	tail->next=head;
	return head;
}


void carkOrtakEkle(struct node **headref, int ortak, int M, int sira ) {          //Ortak elemani carklara ekleme
	 int i;																		
	 struct node* newNode = (struct node*)malloc(sizeof(struct node));
	 newNode->data = ortak;
	 newNode->next = NULL;
	 struct node* currentNode = *headref;
	 struct node* previousNode = NULL;
	 
	 if(sira==1){    // ortak elemanin carkin basina eklenmesi
	 
	      struct node* tail= *headref;
	      while(tail->next != *headref){
	     	 tail = tail->next;
		  }
		  newNode->next = *headref;
	      *headref = newNode;
		  tail->next = *headref;
		  return;
	 }
	 
        for ( i = 1; i < sira-1 ; i++) {             // ortak elemanin random bir indexe eklenmesi
        	 currentNode = currentNode->next;
        	 if (currentNode == *headref) {
            	 return;
        	 }
    	 }
    	 newNode->next = currentNode->next;
    	 currentNode->next = newNode;	 	
}

     
void carkYazdir(struct node *head){            //Carklari ekrana yazdirma
	struct node* currentNode = head;
	do{
		printf("%d ",currentNode->data);
		currentNode = currentNode->next;
	}while(currentNode != head);
	printf("\n");
}

 struct kaydirma {
	int yon;
	int cevir;
};

struct kaydirma yonCevir(  int M, int x1, int x2){ // 2 ci ve 3 cu Carkin hangi yone ve ne kadar cevirmeyi gosterme
	struct kaydirma X;
	if (x1 > x2) {
		if (x1-x2 < M-x1+x2) {
			X.cevir = x1-x2;
			X.yon = 1;                 // 0 degeri sol 1 degeri sag yonu gosteriyor 
		}
		else {
			X.cevir = M-x1+x2;
			X.yon = 0;
		}
	}
	else {
		if (x2-x1 < M-x2+x1){
			X.cevir = x2-x1;
			X.yon = 0;
		}
		else{
			X.cevir = M-x2+x1;
			X.yon = 1;
		}
	}
	return X;
}


void carkDondur(struct node **headref, struct kaydirma dondur, int M){      //Cark cevirme
	int i;       
	if (dondur.yon==1){                         //   Saat yonunde cevirme 
	    	for (i=0;i<M-dondur.cevir;i++){
	    		*headref = (*headref)->next;
			}	    		
	} 
	else {
		for (i=0;i<dondur.cevir;i++){            //Saat yonunun tersinde cevirme
	    		*headref = (*headref)->next;
			}	    
	}      	 
}


void cark(int M , int N ,int ortak){           
	//Carklarda kullanilan  random sayilari yaratma
   int random,i,j;
   int* cark1Sayilar = malloc((M-1)*sizeof(int));      // her carkta 1 tane sayi ortak olacagi için 
   int* cark2Sayilar = malloc((M-1)*sizeof(int));      // M-1 tane random unique sayi uretiyoruz
   int* cark3Sayilar = malloc((M-1)*sizeof(int));
   
   i=0;                                //cark 1 sayilari
   while ( i<(M-1)){
   	srand(time(0));
    random = rand() % N + 1;
   	j=0;
   	while ((j<M-1)&&(random != cark1Sayilar[j])&& (random != ortak)) {
   		j++;
		    
   		if (j == (M-1)) {
			cark1Sayilar[i]=random;
			i++;
	    	} 
		}		    
    }
    
   i=0;                                // cark 2 sayilari
   while ( i<(M-1)){
   	srand(time(0));
   	random = rand() % N + 1;
   	j=0;
   	while ((j<M-1)&&(random != cark1Sayilar[j])&&(random != cark2Sayilar[j])&&(random != ortak)){
   		j++; 
   		if (j == (M-1)) {
			cark2Sayilar[i]=random;
			i++;
	    	} 
		}		   
    }
    
   i=0;                                // cark 3 sayilari
   while ( i<(M-1)){
   	srand(time(0));
   	random = rand() % N + 1;
   	j=0;
   	while ((j<M-1)&&(random != cark1Sayilar[j])&&(random != cark2Sayilar[j])&&(random != cark3Sayilar[j])&&(random != ortak)){
   		j++;
		if (j == (M-1)) {
			cark3Sayilar[i]=random;
			i++;
	    	}    
		}	   
    }
    
    struct node *cark1 = NULL;
	struct node *cark2 = NULL;
	struct node *cark3 = NULL; 
    
    cark1 = carkSayilarEkle(cark1Sayilar,M);
    cark2 = carkSayilarEkle(cark2Sayilar,M);
    cark3 = carkSayilarEkle(cark3Sayilar,M);
    	
    int index1, index2,index3,tmp;
    srand(time(0));                                    // ortak sayinin carklara random yerlere eklenmesi icin
    index1 = rand() % M + 1;                           // unique random indexlerin yaratilmasi
    tmp = rand() % M + 1;
    while (index1 == tmp ){
    	tmp = rand() % M + 1;
	}
	index2 = tmp;
	tmp= rand() % M + 1;
	while (index1==tmp || index2==tmp){
	    tmp = rand() % M + 1;
	}
	index3=tmp;
	
	carkOrtakEkle(&cark1,ortak,M,index1);
	carkOrtakEkle(&cark2,ortak,M,index2);
	carkOrtakEkle(&cark3,ortak,M,index3);
	
	
	printf(" cark 1:  ");
	carkYazdir(cark1);                 // Carklarin ilk halinin yazdirilmasi
	printf(" cark 2:  ");
	carkYazdir(cark2);
	printf(" cark 3:  ");
	carkYazdir(cark3);
	
	printf ("\n Ortak Sayi: %d  \n 1. carktaki konumu: %d \n 2. carktaki konumu: %d \n 3. carktaki konumu: %d \n ",ortak,index1,index2,index3);
	
	
	struct kaydirma dondur2 = yonCevir(M,index1,index2);
	struct kaydirma dondur3 = yonCevir(M,index1,index3);
	
	if (dondur2.yon==1) {
		printf("\n 2. cark Saat yonunde %d adim cevrilmeli ",dondur2.cevir);
	}
	else printf("\n 2. cark Saatin ters yonunde %d adim cevrilmeli ",dondur2.cevir);
	
	if (dondur3.yon==1) {
		printf("\n 3. cark Saat yonunde %d adim cevrilmeli ",dondur3.cevir);
	}
	else printf("\n 3. cark Saatin ters yonunde %d adim cevrilmeli \n",dondur3.cevir);
	
	carkDondur(&cark2,dondur2,M);
	carkDondur(&cark3,dondur3,M);
	printf("\n Carklarin son hali: \n");
	printf(" cark 1:  ");
	carkYazdir(cark1);                             // Carklarin son halinin yazdirilmasi
	printf(" cark 2:  ");
	carkYazdir(cark2);
	printf(" cark 3:  ");
	carkYazdir(cark3);
	
	
}


int main() {              
   int M,N;
   printf (" Her bir carkta olan eleman sayisini ve onlarin deger araligini giriniz :  ");
   scanf ("%d%d",&M,&N);
   while ( M<3 || (M*3-2) > N) {
   	printf (" Girilen degerler mantikli degildir lutfen yeni degerler giriniz : ");
   	scanf ("%d%d", &M,&N);
   }
   printf("\n");
   
   //random ortak sayi yaratma
   int ortak;              
   srand(time(0));
   ortak = rand() % N + 1;
   
   cark(M,N,ortak);

   return 0;
} 
