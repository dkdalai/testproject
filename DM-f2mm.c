// construction of WAPB functions from f_2 with modification when n even (k odd & even)
#include <stdio.h>
#include <stdlib.h>
void comb_all(int, int **);
int comb(int, int);
int wt(int, int);
void ttanf(char *, char *, int);
void print_anf(char *, int);
int walshXform(char *, int *, int);
int walshXformk(char *, int *, int, int);

int main(){
	int n, m, m1, i, j, k, t, t1, t2, tv, tv1, nl, snl;
	int **c, *cnt, *ws;
	char **tt, *anf;

	printf("n = ");
	scanf("%d",&n);
	
	tt = (char **) malloc((n+1)*sizeof(char *)); //for truth table
	for(i = 0; i <= n; i++){
		tv = 1 << i;
		tt[i] = (char *) malloc(tv*sizeof(char));
	}

	cnt = (int *) malloc((n+1)*sizeof(int)); //for weight wise weight
	ws = (int *) malloc(tv*sizeof(int));
	
	c = (int **) malloc((n+1)*sizeof(int *));
	for(i = 0; i <= n; i++)
		c[i] = (int *) malloc((i+1)*sizeof(int));
	comb_all(n, c);
	
	m = 2;	tv = 1 << m; //for f_2
	tt[m][0] = tt[m][1] = 0;
	tt[m][2] = tt[m][3] = 1;
	printf("*************n = %d************\n",m);
/*	printf("S(f_%d) : ",m);
	for(i = 0; i < tv; i++)
		if(tt[m][i])	printf("%d,",i);
	printf("\n");*/
	for(i = 0; i <= m; i++)	cnt[i] = 0;
	for(i = 0; i < tv; i++)
		if(tt[m][i])	cnt[wt(i,m)]++;
	printf("     ===weight diff(2*sup-comb[n][i]) ===\n");
	for(i = 0; i <= m; i++)
		printf("%2d,",i);
	printf("\n");
	for(i = 0; i <= m; i++)
		printf("%2d,",2*cnt[i] - c[m][i]);
	printf("\n");
	nl =  walshXform(tt[m], ws, m);
	printf("Nonlinearity : %d\n",nl);
	snl = 0;
	printf("Nonlinearity_k : ");
	for(k = 0; k <= m; k++){
		nl =  walshXformk(tt[m], ws, m, k);
		printf("%d(%d),",nl,k);
		snl = snl + nl;
	}
	printf("%d\n",snl);

	t = 2;	//temp var to read binary bits of n from MSB
	while(t <= n) t = t << 1;
	t = t >> 1;  //2^(log_2 n)
	
	t = t >> 1;
	if(n&t){    //for f_3 if required i.e., if 2nd MSB is 1
		m++;	tv1 = tv;	tv = tv*2;
		for(i = 0; i < tv1; i++){
			tt[m][i] = tt[m-1][i];
			tt[m][tv1+i] = tt[m-1][i] ^ 1;
		}
		printf("*************n = %d************\n",m);
/*		printf("S(f_%d) : ",m);
		for(i = 0; i < tv; i++)
			if(tt[m][i])	printf("%d,",i);
		printf("\n");*/
		for( i = 0; i <= m; i++)	cnt[i] = 0;
		for(i = 0; i < tv; i++)
			if(tt[m][i])	cnt[wt(i,m)]++;
		printf("     ===weight diff(2*sup-comb[n][i]) ===\n");
		for(i = 0; i <= m; i++)
			printf("%2d,",i);
		printf("\n");
		for(i = 0; i <= m; i++)
			printf("%2d,",2*cnt[i] - c[m][i]);
		printf("\n");
		nl =  walshXform(tt[m], ws, m);
		printf("Nonlinearity : %d\n",nl);
		snl = 0;
		printf("Nonlinearity_k : ");
		for(k = 0; k <= m; k++){
			nl =  walshXformk(tt[m], ws, m, k);
			printf("%d(%d),",nl,k);
			snl = snl + nl;
		}
		printf("%d\n",snl);
	}
	while(m < n){
		m1 = m;	m = m << 1;	tv = 1 << m;	tv1 = 1 << m1;
		for(i = 0; i < tv; i++)	tt[m][i] = 0;
		for(i = 0; i < tv1; i++){
			if(wt(i,m1)%2){
				t1 = i << m1;
				for(j = 0; j < tv1; j++){
					if(wt(j,m1)%2){
//						if((j&1) != (i&1)){
						if((j&1) && !(i&1)){
							t2 = ((i^1) << m1)+ (j^1);
							tt[m][t2] = 1;
						}
						else	tt[m][t1+j] = 1;
					}
					else{
						if(j&1)
							tt[m][t1+j] = 1;
						else{	
							t2 = j << m1;
							tt[m][t2+i] = 1;
						}
					}
				}

			}
		}
		for(i = 0; i < tv1; i++){
			if(tt[m1][i]){
				t1 = (i << m1) ^ i;
				tt[m][t1] = tt[m][t1]^1;
			}
		}
		printf("*************n = %d************\n",m);
/*		printf("S(f_%d) : ",m);
		for(i = 0; i < tv; i++)
			if(tt[m][i])	printf("%d,",i);
		printf("\n");*/
		for( i = 0; i <= m; i++)	cnt[i] = 0;
		for(i = 0; i < tv; i++)
			if(tt[m][i])	cnt[wt(i,m)]++;
		printf("     ===weight diff(2*sup-comb[n][i]) ===\n");
		for(i = 0; i <= m; i++)
			printf("%2d,",i);
		printf("\n");
		for(i = 0; i <= m; i++)
			printf("%2d,",2*cnt[i] - c[m][i]);
		printf("\n");
		nl =  walshXform(tt[m], ws, m);
		printf("Nonlinearity : %d\n",nl);
		snl = 0;
		printf("Nonlinearity_k : ");
		for(k = 0; k <= m; k++){
			nl =  walshXformk(tt[m], ws, m, k);
			printf("%d(%d),",nl,k);
			snl = snl + nl;
		}
		printf("%d\n",snl);


		t = t >> 1;
		if(n&t){
			m++;	tv1 = tv;	tv = tv*2;
			for(i = 0; i < tv1; i++){
				tt[m][i] = tt[m-1][i];
				tt[m][tv1+i] = tt[m-1][i]^1;
			}
			printf("*************n = %d************\n",m);
/*			printf("S(f_%d) : ",m);
			for(i = 0; i < tv; i++)
				if(tt[m][i])	printf("%d,",i);
			printf("\n");*/
			for( i = 0; i <= m; i++)	cnt[i] = 0;
			for(i = 0; i < tv; i++)
				if(tt[m][i])	cnt[wt(i,m)]++;
			printf("     ===weight diff(2*sup-comb[n][i]) ===\n");
			for(i = 0; i <= m; i++)
				printf("%2d,",i);
			printf("\n");
			for(i = 0; i <= m; i++)
				printf("%2d,",2*cnt[i] - c[m][i]);
			printf("\n");
			nl =  walshXform(tt[m], ws, m);
			printf("Nonlinearity : %d\n",nl);
			snl = 0;
			printf("Nonlinearity_k : ");
			for(k = 0; k <= m; k++){
				nl =  walshXformk(tt[m], ws, m, k);
				printf("%d(%d),",nl,k);
				snl = snl + nl;
			}
			printf("%d\n",snl);
		}
	}
	
/*	tv = 1 << n;
	for( i = 0; i < tv; i++)	tt[n][i] = '0'+tt[n][i];
	printf("TT : ");	puts(tt[n]);
	anf = (char *) malloc(tv*sizeof(char));
	ttanf(tt[n],anf,n);
	printf("ANF : ");
	print_anf(anf, n);*/

	return 0;
}

void comb_all(int m, int **c)
{       int i, j;
	for(i = 0; i <= m; i++)
		c[i][0] = c[i][i] = 1;
	for(i = 2; i <= m; i++)
		for(j = 1; j < i; j++)	c[i][j] = 0;
	for(i = 2; i <= m; i++)
		for(j = 1; j < i; j++)
			c[i][j] = c[i-1][j] + c[i-1][j-1];
}
int comb(int n, int r)
{       int i;
        int t;
        long long int l;

	if(r > n/2)	r = n-r;
        l = 1;
        for(i = 1; i <= r; i++)
        	l = (l*(n-i+1))/i;
        t = l;
        return t;
}
int wt(int v, int n)
{	int i, t, w;
	w = 0;	t = 1;
	for(i = 0; i < n; i++){
		if(v&t)	w++;
		t = t << 1;
	}
	return(w);
}
void ttanf(char *tt, char *anf, int n){
	int i, j, k, l, p, q;

	p = 1 << n;
	for(i = 0; i < p; i++)	anf[i] = tt[i]-'0';

	p = p >> 1;	q = 1;
	for(i = 0; i < n; i++){
		l = 0;
		for(j = 0; j < p; j++){
			for(k = 0; k < q; k++){
				anf[l+q] = anf[l]^anf[l+q];
				l++;
			}	l = l+q;
		}	p = p >> 1;	q = q << 1;
	}
	for(i = 0; i < q; i++)	anf[i] = anf[i]+'0';
}
void print_anf(char *anf, int n){
	int i, j, k, tot;

	tot  = 1 << n;
	if(anf[0] == '1')	printf("0 + ");
	for(i = 1; i < tot; i++) {
		if(anf[i] == '1'){
			j = 1;	k = 1;
			while(k <= n){
				if((i & j))	printf("%d",k);
				k++;	j = j << 1;
			}
			printf(" + ");
		}
	}
	printf("\n");
}
int walshXform(char *tt, int *ws, int n){
	int i, j, k, l, p, q, nl;

	p = 1 << n;
	for(i = 0; i < p; i++)
		if((tt[i] != 0) && (tt[i] != 1)){
			printf("Error in Input(at %dth place)...\n",i);
			exit(0);
		}
	for(i = 0; i < p; i++){
		if(tt[i] == 0)	ws[i] = 1;
		else		ws[i] = -1;
	}

	p = p >> 1;	q = 1;
	for(i = 0; i < n; i++){
		l = 0;
		for(j = 0; j < p; j++){
			for(k = 0; k < q; k++){
				ws[l] = ws[l] + ws[l+q];
				ws[l+q] = ws[l] - 2*ws[l+q]; //ws[l] has been updated 
				l++;
			}
			l = l+q;
		}
		p = p >> 1;	q = q << 1;
	}
//To Compute Nonlinearity
	p = abs(ws[0]);
	k = 1 << n;
	for(i = 1; i < k; i++){
		q = abs(ws[i]);
		if(q > p)	p = q;
	}
	nl = (1 << (n-1)) - (p >> 1);
	return(nl);
}
int walshXformk(char *tt, int *ws, int n, int k){
	int i, j, s, l, p, q, nl;

	if(k > n){
		printf("Error: k can not be bigger than %d \n",n);
		exit(0);
	}
	p = 1 << n;
	for(i = 0; i < p; i++)
		if((tt[i] != 0) && (tt[i] != 1)){
			printf("Error in Input(at %dth place)...\n",i);
			exit(0);
		}
	for(i = 0; i < p; i++)	ws[i] = 0;
	for(i = 0; i < p; i++){
		if(wt(i,n) == k){
			if(tt[i] == 0)	ws[i] = 1;
			else		ws[i] = -1;
		}
	}

	p = p >> 1;	q = 1;
	for(i = 0; i < n; i++){
		l = 0;
		for(j = 0; j < p; j++){
			for(s = 0; s < q; s++){
				ws[l] = ws[l] + ws[l+q];
				ws[l+q] = ws[l] - 2*ws[l+q]; //ws[l] has been updated 
				l++;
			}
			l = l+q;
		}
		p = p >> 1;	q = q << 1;
	}
//To Compute Nonlinearity
	p = abs(ws[0]);
	s = 1 << n;
	for(i = 1; i < s; i++){
		q = abs(ws[i]);
		if(q > p)	p = q;
	}
	nl = (comb(n,k) - p) >> 1;
	return(nl);
}
