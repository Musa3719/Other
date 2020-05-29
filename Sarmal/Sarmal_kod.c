#include <stdio.h>
#include <stdlib.h>
/* Şekildeki listeyi içten dışa sarmal şeklinde oluşturur listenin elemanları üzerinde sağ,sol,yukarı ve aşağı hareketleri yapılabilir
 * Listeden istenilen 2 sayı arasında yol almak için hangi sayılardan geçilir ve kaç hareket yapılır bulan algoritma
 * X ve Y değerlerine sahip karelerin arasında ilerlemek için x ve y ağaçları bulunur. Bir tane olan X ağacı her değerini için bir Y ağacı bulundurur.
 * Örnek olarak x=2 y=5 bu durumda x ağacında 2 bulunur ve 2'nin y ağacına gidilir. Orda da 5 değeri bulunur. Bulunan node içerisinde o koordinattaki struct kare bulunur
 */
struct kare{
    int deger;
    int x;
    int y;
};
struct Xagac{
    int x;
    struct Xagac *sol;
    struct Xagac *sag;
    struct Yagac *y_agac;
};
struct Yagac{
    int x;
    int y;
    struct kare *kare_node;
    struct Yagac *sol;
    struct Yagac *sag;
};

struct Xagac* x_agac_eleman_bul(struct Xagac *root,int x);
struct Yagac* y_agac_eleman_bul(struct Yagac *root,int y);
struct kare* agac_eleman_bul(struct Xagac *x_root,int x,int y);
void agac_eleman_ekle(struct Xagac *root,struct kare *kare_node,int x,int y);
struct Yagac* y_agac_eleman_ekle(struct Yagac *root,struct kare *karenode,int x,int y);
struct Xagac* listeyi_olustur(int eleman_sayisi);
void eleman_olustur(int sayi,int xfonk,int yfonk,struct Xagac *x_agac);
void iki_eleman_arasi_bul(struct Xagac *x_agac,int sayi1,int sayi2);
void koordinat_bul(struct Xagac *x_agac,int sayi,int *x,int *y);
void koordinat_bul_y(struct Yagac *y_agac,int sayi,int *x,int *y);

struct Xagac* x_agac_eleman_bul(struct Xagac *root,int x){
    while(root!=NULL){
        if(x == root->x){
            return root;
        }
        else if(x > root->x){
            root = root->sag;
        }
        else if(x < root->x){
            root = root->sol;
        }
    }
    printf("X agacindan eleman bulunamadi...\n");
}

struct Yagac* y_agac_eleman_bul(struct Yagac *root,int y){
    while(root!=NULL){
        if(y == root->y){
            return root;
        }
        else if(y > root->y){
            root = root->sag;
        }
        else if(y < root->y){
            root = root->sol;
        }
    }
    printf("Y agacindan eleman bulunamadi...\n");
}

struct kare* agac_eleman_bul(struct Xagac *x_root,int x,int y){
	struct Xagac *x_node = x_agac_eleman_bul(x_root,x);
	struct Yagac *y_node = y_agac_eleman_bul(x_node->y_agac ,y);
	return y_node->kare_node;
}

void agac_eleman_ekle(struct Xagac *root,struct kare *kare_node,int x,int y){
	int solmu=0;
	struct Xagac *geri=NULL;
	while(root!=NULL){
		if(x == root->x){
			y_agac_eleman_ekle(root->y_agac,kare_node,x,y);
			return;
		}
		else if(x > root->x){
			geri=root;
			root=root->sag;
			solmu=0;
		}
		else if(x < root->x){
			geri=root;
			solmu=1;
			root=root->sol;
		}
	}
	struct Xagac *yeni_x = (struct Xagac*)malloc(sizeof(struct Xagac));
	yeni_x->sag=NULL;
	yeni_x->sol=NULL;
	yeni_x->y_agac=NULL;
	yeni_x->y_agac= y_agac_eleman_ekle(yeni_x->y_agac,kare_node,x,y);
	yeni_x->x = x;
	if(solmu==1)
		geri->sol=yeni_x;
	else
		geri->sag=yeni_x;
}

struct Yagac* y_agac_eleman_ekle(struct Yagac *root,struct kare *karenode,int x,int y){
	int solmu=0;
	struct Yagac *geri=NULL;
	while(root!=NULL){
		if(y == root->y){
			printf("y degeri zaten var...\n");
			return root;
		}
		else if(y > root->y){
			geri=root;
			root=root->sag;
			solmu=0;
		}
		else if(y < root->y){
			geri=root;
			root=root->sol;
			solmu=1;
		}
	}
	struct Yagac *yeni_y = (struct Yagac*)malloc(sizeof(struct Yagac));
	yeni_y->kare_node = karenode;
	yeni_y->sag=NULL;
	yeni_y->sol=NULL;
	yeni_y->x =x;
	yeni_y->y =y;
	if(geri!=NULL){
		if(solmu==1)
			geri->sol=yeni_y;
		else
			geri->sag=yeni_y;
		return yeni_y;
	}
	else{
		return yeni_y;
	}
}

struct Xagac* listeyi_olustur(int eleman_sayisi){
    struct Xagac *x_agac = (struct Xagac*)malloc(sizeof(struct Xagac));
    x_agac->sag=NULL;
	x_agac->sol=NULL;
	x_agac->x=0;
	struct Yagac *y_agac = (struct Yagac*)malloc(sizeof(struct Yagac));
	y_agac->sag=NULL;
	y_agac->sol=NULL;
	y_agac->x=0;
	y_agac->y=0;
	struct kare *karenode = (struct kare*)malloc(sizeof(struct kare));
	y_agac->kare_node=karenode;
	y_agac->kare_node->deger=0;
	y_agac->kare_node->x=0;
	y_agac->kare_node->y=0;
	x_agac->y_agac=y_agac;
	int i;
	int x_degeri=1;
	int y_degeri=0;
	int yon_degistirme_sayisi=1;
	int c=0;
	int arttirma=0;
	int yon=1;
    for(i=1;i<eleman_sayisi;i++){
        eleman_olustur(i,x_degeri,y_degeri,x_agac);
        c++;
        if(c==yon_degistirme_sayisi){
        	if(yon!=4)
        		yon++;
        	else
        		yon=1;
        	c=0;
        	arttirma++;
        	if(arttirma==2){
        		yon_degistirme_sayisi++;
        		arttirma=0;
        	}
	}
	switch(yon){
		case 1:
			x_degeri++;
			break;
		case 2:
			y_degeri--;
			break;
		case 3:
			x_degeri--;
			break;
		case 4:
			y_degeri++;
			break;
	}
    }
    return x_agac;
}

void eleman_olustur(int sayi,int xfonk,int yfonk,struct Xagac *x_agac){
    struct kare *yeni = (struct kare*)malloc(sizeof(struct kare));
    yeni->deger = sayi;
    yeni->x = xfonk;
    yeni->y = yfonk;
    agac_eleman_ekle(x_agac,yeni,xfonk,yfonk);
}

void koordinat_bul_y(struct Yagac *y_agac,int sayi,int *x,int *y){
	if(y_agac==NULL)
		return;
	if(y_agac->kare_node->deger == sayi){
		*x = y_agac->x;
		*y = y_agac->y;
	}
	koordinat_bul_y(y_agac->sol,sayi,x,y);
	koordinat_bul_y(y_agac->sag,sayi,x,y);
}

void koordinat_bul(struct Xagac *x_agac,int sayi,int *x,int *y){
	if(x_agac==NULL)
		return;
	koordinat_bul_y(x_agac->y_agac,sayi,x,y);
	koordinat_bul(x_agac->sol,sayi,x,y);
	koordinat_bul(x_agac->sag,sayi,x,y);
}


void iki_eleman_arasi_bul(struct Xagac *x_agac,int sayi1,int sayi2){
	int x1,x2,y1,y2;
	koordinat_bul(x_agac,sayi1,&x1,&y1);
	koordinat_bul(x_agac,sayi2,&x2,&y2);
	int c=0;
	struct kare *eleman;
	eleman = agac_eleman_bul(x_agac,x1,y1);
	printf("%d ",eleman->deger);
	while(x1!=x2 || y1!=y2){
		if(y1!=y2){
			if(y2>y1)
				y1++;
			else
				y1--;
			c++;
			eleman = agac_eleman_bul(x_agac,x1,y1);
			printf("%d ",eleman->deger);
		}
		if(x1!=x2){
			if(x2>x1)
				x1++;
			else
				x1--;
			c++;
			eleman = agac_eleman_bul(x_agac,x1,y1);
			printf("%d ",eleman->deger);
		}
	}
	printf("\n%d kez hareket edildi...",c);
}

int main()
{
    struct Xagac *x_agac=NULL;
    int sayi;
    printf("sarmalin eleman sayisini giriniz:\n");
    scanf("%d",&sayi);
    x_agac = listeyi_olustur(sayi);
    printf("sarmalda yol haritasi cizmek icin 2 sayi giriniz:\n");
    int a,b;
    scanf("%d",&a);
    scanf("%d",&b);
    iki_eleman_arasi_bul(x_agac,a,b);
    return 0;
}
