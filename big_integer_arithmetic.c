#include <stdio.h>
#include <stdlib.h>
#include "intal.h"
#include <string.h>
#define lli long long int
//#define MALL(t,s) (t*)malloc(sizeof(t)*s)

typedef struct intal{
	int *data;
	int len;
}INTAL;

void intal_destroy(void *intal1){
	if(intal1==NULL)	
		return;
	free(intal1);
}

char* intal2str(void* intal1){
	INTAL *x = (INTAL*)intal1;
	if(x == NULL){
		char *z = MALL(char,4);
		strcpy(z,"NaN");
		z[3] = '\0';
		return z;
	}
	char *z = MALL(char,x->len+1);
	int i=0;
	for(i=0;i<x->len;i++){
		z[i] = x->data[i]+'0';
	}
	z[i]='\0';
	return z;
}

int intal_compare(void *intal1,void *intal2){
	INTAL *x = (INTAL*)intal1;
	INTAL *y = (INTAL*)intal2;
	if(x->len>y->len){
		return 1;
	}else if(x->len < y->len){
		return -1;
	}else{
		int i=0;
		while(i<x->len){
			if(x->data[i] > y->data[i]){
				return 1;
			}else if(x->data[i] < y->data[i]){
				return -1;
			}
			i++;
		}
		return 0;
	}
}


void print(void *x){
	INTAL *t = (INTAL*)x;
	int i;
	if(t==NULL){
		printf("NaN\n");
		return ;
	}
	for(i=0;i<t->len;i++){
		printf("%d", t->data[i]);
	}
	printf("\n");
}

void *intal_create(const char *str){
	int n = strlen(str);
	int i=0;
	while(str[i]=='0' && i<n)
		i++;
	int diff = n-i;
	INTAL *A = MALL(INTAL,1);
	
	if(diff==0){

		A->data = MALL(int,1);
		A->data[0] = 0;
		A->len = 1;
	}else{
		A->data = MALL(int,diff);
		A->len = diff;
		for(i=0;i<diff;i++){
			A->data[i] = str[i+n-diff]-'0';
		}
	}
	return A;
}

void *rem_zeros(INTAL *intal1){
	int j=0;
	INTAL *temp;
	while( intal1->data[j]==0 && j<intal1->len)
		j++;
	if(j==intal1->len){
		temp = intal_create("0");
	}
	else{
		int i=0;
		temp = MALL(INTAL,1);
		temp->len = intal1->len-j;
		temp->data = MALL(int,temp->len);
		while(j<intal1->len){
			temp->data[i++]=intal1->data[j++];
		}
	}
	return temp;
}

void *intal_increment(void *intal1){
	INTAL *x = (INTAL*)intal1;
	int *ne = MALL(int,x->len+1);
	int i,s=0,c=1;;
	for (i = x->len-1; i>=0; i--){
		s = x->data[i]+c;
		c = s/10;
		s = s%10;
		ne[i+1] = s;
	}
	if(c){
		ne[i+1] = c;
		free(x->data);
		x->data = ne;
		x->len++;
	}else{
		for(i=0;i<x->len;i++)
			x->data[i] = ne[i+1];
		free(ne);
	}
	return x;

}

void *intal_decrement(void *intal1){
	INTAL *x = (INTAL*)intal1;
	INTAL *zero = intal_create("0");
	if(intal_compare(zero,x)==0){
		return zero;
	}
	int *ne = MALL(int,x->len);
	int i,s=0,c=-1;
	for (i = x->len-1; i>=0; i--){
		s = x->data[i]+c;
		if(s<0){
			s += 10;
			c = -1;
		}else{
			c=0;
		}
		ne[i] = s;
	}

	if(ne[i+1]==0){
		free(x->data);
		x->data = ne;
		x->len--;
	}else{
		x->data = MALL(int,x->len);
		for(i=0;i<x->len;i++)
			x->data[i] = ne[i];
		
	}
	return x;
}

void *intal_add(void *intal1,void *intal2){
	INTAL *x,*y,*z;
	int ch = intal_compare(intal1,intal2);
	if(ch==1){
		x = (INTAL*)intal1;
		y = (INTAL*)intal2;
	}else{
		x = (INTAL*)intal2;
		y = (INTAL*)intal1;
	}
	z = MALL(INTAL,1);
	z->len = x->len;
	int n = x->len;
	int *ne = MALL(int,x->len+1);
	int i=0,diff = n-y->len,s = 0,c=0;

	for (i = y->len-1; i>=0; i--){
		s = x->data[i+diff]+c+y->data[i];
		c = s/10;
		s = s%10;
		ne[i+1+diff] = s;
	
	}
	while(i+diff>=0){
		s = x->data[i+diff]+c;
		c = s/10;
		s = s%10;
		ne[i+1+diff] = s;
		i--;
	
	}

	if(c){
		z->len = x->len+1;
		ne[0] = c;
		z->data = ne;
	}else{
		z->data = MALL(int,x->len);
		for(i=0;i<n;i++)
			z->data[i] = ne[i+1];
		free(ne);
	}

	return z;
}

void *intal_diff(void *intal1,void *intal2){
	INTAL *x,*y;
	int ch = intal_compare(intal1,intal2);
	if(ch==1){
		x = (INTAL*)intal1;
		y = (INTAL*)intal2;
	}else if(ch==-1){
		x = (INTAL*)intal2;
		y = (INTAL*)intal1;
	}else{
		INTAL *z = intal_create("0");
		return z;
	}

	INTAL *z = MALL(INTAL,1);
	z->len = x->len;

	int *ne = MALL(int,x->len);

	int s=0,c=0,i=0;
	int diff = x->len-y->len;

	for(i=y->len-1;i>=0;i--){
		s = x->data[i+diff]-y->data[i]+c;
		if(s<0){
			s += 10;
			c = -1;
		}else{
			c=0;
		}
		ne[i+diff] = s;	
	}
	while(i+diff>=0){
		s = x->data[i+diff]+c;
		if(s<0){
			s+=10;
			c=-1;
		}else{
			c = 0;
		}
		ne[i+diff] = s;
		i--;
	}
	i = 0;
	while(i<x->len && ne[i]==0)
		i++;
	
	z->data = MALL(int,x->len-i);
	z->len = x->len-i;
	int j = 0;
	for(j=0;j<z->len;j++)
		z->data[j] = ne[i+j];
	
	free(ne);
	return z;
}


void *intal_multiply(void *intal1,void *intal2){
	if(intal1==NULL || intal2==NULL)
		return NULL;

	INTAL *zero = intal_create("0");
	if(intal_compare(intal1,zero)==0 || intal_compare(intal2,zero)==0)
		return zero;
	
	INTAL *x = (INTAL*)intal1;
	INTAL *y = (INTAL*)intal2;


	INTAL *z = MALL(INTAL,1);
	z->len = x->len+y->len;
	z->data = MALL(int,z->len);
	int i;
    for(i=0;i<z->len;i++)
        z->data[i]=0;

    int shift = z->len-1,c,k,j,s=0;

    for(i=y->len-1;i>=0;i--){
        c=0,k=0,j=0;
        for(j=x->len-1;j>=0;j--){    
            s = y->data[i]*x->data[j]+c;
            s = s + z->data[shift-k];
            c=s/10;
            z->data[shift-k]=s%10;
            k=k+1;
        }         
        if(c>0)
            z->data[shift-k]=c;
        shift=shift-1;
 	}
 	z = rem_zeros(z);
    return z;
}
																																				

void* intal_divide(void* intal1, void* intal2){
	INTAL *i1,*i2;
	i1=(INTAL *)intal1;
	i2=(INTAL *)intal2;
    if(i1==NULL || i2==NULL)
		return NULL;
	
	INTAL *zero = intal_create("0");
	
	if(intal_compare(zero,intal2)==0){
		return NULL;
	}
	if(intal_compare(zero,intal1)==0 || intal_compare(intal1,intal2)==-1){
		return zero;
	}
	if(intal_compare(intal1,intal2)==0){

		INTAL *one =  intal_create("1");
		return one;

	}else{
		
		INTAL *ne = MALL(INTAL,1);
		ne->data = MALL(int,(i1->len));

		INTAL *d1 = MALL(INTAL,1);
		d1->data = MALL(int,(i2->len));

		INTAL *d0 = MALL(INTAL,1);
		d0->data = MALL(int,(i2->len));
		
		d1->len=d0->len=i2->len;

		INTAL *res = intal_create("0");

		int m = i1->len;
		int n = i2->len;
		int i;
		for(i=0;i<n;i++){
			d1->data[i] = i1->data[i];
			d0->data[i] = i2->data[i];
		}
		int t = n;
		int count=0;

		while(t<=m){
			int f=0;
			if(intal_compare(d1,d0)>=0){
				while(intal_compare(d1,d0)>=0){

					d1 = (INTAL*)intal_diff(d1,d0);
					d1 = (INTAL*)rem_zeros(d1);
					res = (INTAL*)intal_increment(res);
				}
				ne->data[count++] = res->data[0];
				res->data[0] = 0;
				res->len = 1;
				f=1;
			}else{
				
				if(t==m)
					break;
				d1=(INTAL *)realloc(d1,sizeof(INTAL)+(d1->len+1)*sizeof(int));
				d1->len++;
				d1->data[d1->len-1]=i1->data[t];
				d1=(INTAL*)rem_zeros(d1);

			   	t++;

			}
			if(!f && intal_compare(d1,d0)==-1){
				ne->data[count++]=0;	
			}
		}
		ne->len=count;
		free(d1);
		free(d0);
		free(res);
		return ne;
	}
}


void *intal_pow(void *intal1,void *intal2){
	INTAL *zero = intal_create("0");
	INTAL *one = intal_create("1");
	if(intal_compare(intal1,zero)==0){
		INTAL *z = intal_create("0");
		return z;
	}
	if(intal_compare(intal2,zero)==0 || intal_compare(one,intal1)==0){
		INTAL *z = intal_create("1");
		return z;
	}

	INTAL *pdt = intal_create("1");

	while(intal_compare(intal2,zero)>=0){
		pdt = intal_multiply(pdt,intal1);
		intal2 = intal_decrement(intal2);
	}

	return pdt;
}
