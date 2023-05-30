#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>

typedef struct distance{														//koordinatak structuraja
	int id;
	double x;
	double y;

}distance;

typedef struct rest{															//ettermek structuraja
	int id;
	char adress[50];
	char type[20];
	char szep[5];
	int price;
	int rating;
	char name[50];
	struct rest *next;
	struct distance *head;
}rest;

void destroy(rest * head_rest){													//memoria felszabaditasa
	rest *tmp_rest=head_rest;
	distance *tmp_dist = NULL;
	while (head_rest != NULL){
		tmp_dist = head_rest->head;			
		free(tmp_dist);															//fogak felszabaditasa
		tmp_rest= head_rest->next;
		free(head_rest);														//torzs felszabaditasa
		head_rest = tmp_rest;
	}
}

rest *restaurants_read(FILE *fp){ 										// létrehozza a lista torzset, es feltolti az etterem adataival a tagokat
	int id,price,rating;
	int z = 1;
	char adress[50],type[20],szep[5],name[20];
	rest *head = NULL;
	rest *head_ret = NULL;
	head = (rest*) malloc (sizeof(rest));
	rest *tmp = head;
	if(fp == NULL){					//HIBAS FAJLNYITAS ESETEN VISSZATER A MAINBE
		printf("NEM SIKERULT MEGNYITNI A FAJT\n");
		return NULL;
	}
	while (fscanf(fp,"%d %s %s %s %d %d %s",&id,&adress,&type,&szep,&price,&rating,&name)==7){ // adatok beolvasasa, memoriaba masolja
		
		rest *p1 = (rest*) malloc (sizeof(rest));
		if((p1 == NULL)){
			printf("HIBAS MEMORIAFOGLALAS");	//HIBAS MEMORIAFOGLALAS ESETEN VISSZATER A MAINBE
			return NULL;
		}
		p1->next = NULL;
		p1->id = id;								//feltolti a torzs adott elemenek adatait
		strcpy(p1->name,name);										
		strcpy(p1->adress,adress);
		strcpy(p1->type,type);
		strcpy(p1->szep,szep);
		p1->price = price;
		p1->rating = rating;
		p1->head = NULL;
		tmp ->next = p1;
		tmp = p1;
		p1 = NULL;
		if(head_ret == NULL){					//beallitja a headet, amit visszafog adni
			head_ret = tmp;
		}
	}

	free(head);
	fclose(fp);
	return head_ret;		//visszadja a torzs kedzocimet
}

distance *distance_read(rest *head,FILE *fp){								// letrehozza a lista fokait, es rafuzi a torzs megfelelo tagjaira azokat
	int id;
	double x,y;
	
	distance *first = NULL;
	distance *tmp = first;
	rest *tmp2 = head;
	if(fp == NULL){					//HIBAS FAJLNYITAS ESETEN VISSZATER A MAINBE
		printf("NEM SIKERULT MEGNYITNI A FAJT");
		return NULL;
	}
	while (fscanf(fp,"%d %lf %lf",&id,&x,&y)==3){
		distance *p1 = (distance*) malloc (sizeof(distance));
		if((p1 == NULL)){
			printf("HIBAS MEMORIAFOGLALAS");	//HIBAS MEMORIAFOGLALAS ESETEN VISSZATER A MAINBE
			return NULL;
		}
		p1->id = id;							//feltolti a fokok adatait
		p1->x = x;
		p1->y = y;
		tmp2->head = p1;
		tmp2 = tmp2->next;
	}
	fclose(fp);
	return first;
}

void read_stdin(char type_input[10],double *dist){								//beolvassa az adatokat stdinputrol es indirekt modon adja azokat vissza
	char type_input_tmp[10] = {'\0'};
	double dist_tmp;
	int ok;
	int i;
	printf("Adjon meg egy etterem tipust, es egy keresesi tavolsagot(km)!\n");		// ,,uzenet" a felhasznalonak
	printf("Etterem tipusok:\nkinai,gyors,bufek,kifozde,kavezo \n");
	scanf("%s %lf",&type_input_tmp,&dist_tmp);									//adatok beolvasasa stdinputrol
	for(i = 0;type_input_tmp[i] != 0;i++){									//adatok beirasa a stringbe
		type_input[i] = type_input_tmp[i];	
	}
	i++;
	type_input[i] = '\0';
	*dist = dist_tmp;															//adatok beirasa double-be
	printf("\n");
}

void print_type(rest *head){												//elso modban kiirja a ettermeket 
	for(int i = 0;head->adress[i] != 0;i++){								//szepeti a kiirast kicsereli ,,_" -t space -re
		if(head->adress[i] == '_'){
			head->adress[i] = ' ';
		}
	}
	for(int i = 0;head->name[i] != 0;i++){									//szepeti a kiirast kicsereli ,,_" -t space -re
		if(head->name[i] == '_'){
			head->name[i] = ' ';
		}
	}
	printf("Az etterem neve: %s\n",head->name);
	printf("Az etterem cime: %s\n",head->adress);							//kiirja az ettermek adatait
	printf("Az etterem tipusa: %s\n",head->type);
	printf("SZEP kartyaval fizetes: %s\n",head->szep);
	printf("Ar nagysag(1-5):%d\n",head->price);
	printf("Az etterem ertekelese(GOOGLE MAPS): %d\n",head->rating);
	printf("\n");
	
}

void print_asc(rest *t[],int l ){											//masodik modban kiirja a tombben levo ettermeket
	for(int i = 0; i < l; i ++){
		for(int j = 0;j < l;j++){
			for(int z = 0; t[j]->adress[z] != 0;z++){						//szepeti a kiirast
				if(t[j]->adress[z] == '_'){
					t[j]->adress[z] = ' ';
				}
			}
		}
		
		for(int j = 0;j < l;j++){
			for(int z = 0; t[j]->name[z] != 0;z++){						//szepeti a kiirast
				if(t[j]->name[z] == '_'){
					t[j]->name[z] = ' ';
				}
			}
		}		
		
		printf("Az etterem neve: %s\n",t[i]->name);						//kiirja az adatait az ettermeknek
		printf("Az etterem cime: %s\n",t[i]->adress);
		printf("Az etterem tipusa: %s\n",t[i]->type);
		printf("SZEP kartyaval fizetes: %s\n",t[i]->szep);
		printf("Ar nagysag(1-5):%d\n",t[i]->price);
		printf("Az etterem ertekelese(GOOGLE MAPS): %d\n",t[i]->rating);
		printf("\n");
	}
}

double dist_count(double x, double y){											//kiszamolja I epulettol valo tavolsagat az etteremnek
	double ix, iy;
	double i;
	ix = 47.47;
	iy =  19.06;
	if(x < 0 ){
		x = -x; 
	}
	if(y < 0){
		y = -y;
	}
	i = sqrt((ix-x)*(ix-x)+(iy-y)*(iy-y));
	i = i* 111.139;
	return i;
}

void print_none(void){												//ha a program nem talalt megfelelo ettermet kiir egy uzenetet
	printf("Nincs az adatoknak megfelelo etterem\n");
}

void dist_asc(char type_input[],rest *head_rest){							//kiirja a megfelelo tipusu ettermeket novekvo sorrenben
	rest *tmp1 = head_rest;
	int i,j,k,l,m = 0;
	i= 0;
	l = 0;
	rest * tmp2 = NULL;
	double min;
	rest *t[500] = {NULL};
	char type_comp[10] = {'\0'};
	char type_head[10] = {'\0'};

	for(i = 0;type_input[i] != 0;i++){										//stringe masolja a kivant fajtat
		type_comp[i] = type_input[i];
	}

	while(tmp1 != NULL){
		for(j = 0;tmp1->type[j] != 0;j++){
			type_head[j] = tmp1->type[j];									//stringbe masolja a current fajtat
		}
		type_head[j] = '\0';	
		k = strcmp(type_head,type_comp);									//feltolt egy tombot a fajtanak megfelelo ettermek pointereivel
		if (k == 0){
			t[l] = tmp1;
			l++;
			
		}
		tmp1 = tmp1->next;

	}
	tmp1 = head_rest;
	for(i = 0; i < l;i++){													//sorba rakta a pointereket novekvo sorrend szerint
		for(j= i + 1; j < l; j ++){
			if(dist_count(t[i]->head->x,t[i]->head->y) > dist_count(t[j]->head->x,t[j]->head->y)){
				tmp2 = t[i];
				t[i] = t[j];
				t[j] = tmp2;
			}
		}
	}
	if (l == 0){															//ha nincs megfelelo etterem meghivja a fuggvenyt
		print_none();
	}
	else{
		print_asc(t,l);														//meghivja a fuggvenyt, ami kiirja a tombbot
	}
}



void match(char type_input[],double dist,rest* head_rest){						//eldonti, hogy melyek a megfelelo ettermek, azokat egy uj listaba rakja
	double dist_comp = 0;
	char type_comp[10] = {'\0'};
	char type_head[10] = {'\0'};
	int k = -4;
	int u = 0;
	int i = 0, j = 0;
	rest *tmp1 = head_rest;
	rest * tmp_head = NULL;

	distance *tmp3 = head_rest->head;
	distance *tmp4 = NULL;
	for(i = 0;type_input[i] != 0;i++){												//stringbe masolja a kivant fajtat
		type_comp[i] = type_input[i];
	}
	while (tmp1 != NULL){
		dist_comp = dist_count(tmp1->head->x,tmp1->head->y);						//stringbe masolja a jelenlegi etterem fajtajat
		for(j = 0;tmp1->type[j] != 0;j++){
			type_head[j] = tmp1->type[j];
		}
		type_head[j] = '\0';
		k = strcmp(type_head,type_comp);					
		if(k == 0 &&  dist >= dist_comp){								//ha megfelel a fajta, kiprinteli az etterem adatait a fuggveny meghivasaval
			print_type(tmp1);
			u++;
		}
		tmp1 = tmp1->next;
	}
	if(u==0){
		print_none();
	}
}

void sort(char type_input[],double dist,rest *head_rest){						//eldonti, hogy a program melyik modjat hasznalja, meghivja a szukseges fuggvenyeket
	if(dist < 0){
		dist_asc(type_input,head_rest);
	}		
	if(dist > 0){															
		match(type_input,dist,head_rest);
	}
	if(dist == 0){															// 0 tavolsag eseten meghivja fuggvenyt
		print_none();
	}

}


int main(void){																	//MAIN FGV meghivja a fuggvenyeket
	char type_input[10];
	double dist = 0; 
	FILE *pfajl = fopen("ettermek.txt","r");
	FILE *pfajl2 = fopen("koord.txt","r");
	rest *head_rest;
	distance *head_dist; 
	head_rest = restaurants_read(pfajl);										//fajlolvaso fuggvenyek meghivasa
	head_dist = distance_read(head_rest,pfajl2);
	read_stdin(type_input,&dist);												//adatok kerese felhasznalotol
	sort(type_input,dist,head_rest);											//meghivja a fuggvenyt, ami eldonti, hogy melyik modot hasznalja a program
	
	
	destroy(head_rest);															//felszabaditja a foglalt memoriat
	return 0;
}
