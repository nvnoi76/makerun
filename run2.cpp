#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 10
#define min(a,b) ((a)<(b)?(a):(b))

void shift(int a[], int q, int r)
{
	int i=q, j=2*i+1, x=a[i];
	while (j<=r)
	{
		if ((j<r) && (a[j]> a[j+1]))  
			j++;
		if (x<a[j]) 
			break;
		else
		{
			a[i]=a[j];
			i = j;
			j = i*2+1;
		}
	}
	a[i] = x;
}

void Distribute(FILE * fi, FILE * fo[], int numfile)
{
	int n=0; int b;
	int a[BUFSIZE];
	int i,q, r;
	int m, mh;
	int k=0;

	while (n<BUFSIZE)
		if (fscanf(fi,"%d",&a[n])==1)
			n++;
		else
			break;

	m = min(BUFSIZE,n);
	mh =m/2;
	i = mh-1;
	while (i>=0)
	{
		shift(a,i,m-1);
		i--;
	}

	q = m-1;
	while (fscanf(fi,"%d",&b)==1)
	{
		n++;
		fprintf(fo[k]," %d",a[0]);
		if (a[0]<b)
		{
			a[0] = b;
			shift(a,0,q);
		}
		else
		{
			a[0] = a[q];
			shift(a,0,q-1);
			a[q] = b;
			if (q<mh)
				shift(a,q,m-1);			
			q=q-1;
			if (q<0)
			{
				q = m-1;
				fprintf(fo[k],"\n");
				k++;
				if (k>=numfile)
					k-=numfile; 
			}
		}
	}
	r = m-1;
	while (q>=0)
	{
		fprintf(fo[k]," %d",a[0]);
		a[0] = a[q];
		shift(a,0,q-1);
		a[q] =a[r];
		r = r -1;
		if (q<mh)
			shift(a,q,r);
		q = q-1;
	}	
	fprintf(fo[k],"\n");
	k++;
	if (k>=numfile)
			k-=numfile; 
	while (r>=0)
	{
		fprintf(fo[k]," %d",a[0]);
		a[0] = a[r];
		r = r-1;
		shift(a, 0, r);
	}
}

void main()
{
	FILE * fi = fopen("ti.txt","rt");
	FILE * fo[2];
	fo[0]= fopen("to1.txt","wt");
	fo[1]= fopen("to2.txt","wt");
	Distribute(fi,fo,2);
}

/*void HeapSort(int b[], int n)
{
	int a[BUFSIZE];
	int k=0,i,q, r;
	int m = min(BUFSIZE,n);
	int mh =m/2;

	for(i=mh;i<m;i++)
		a[i]=b[k++];

	i = mh-1;
	while (i>=0)
	{
		a[i]=b[k++];
		shift(a,i,m-1);
		i--;
	}

	q = m-1;
	while (k<n)
	{	
		printf(" %d",a[0]);
		if (a[0]<b[k])
		{
			a[0] = b[k++];
			shift(a,0,q);
		}
		else
		{
			a[0] = a[q];
			shift(a,0,q-1);
			a[q] = b[k++];
			if (q<mh)
				shift(a,q,m-1);			
			q=q-1;
			if (q<0)
			{
				q = m-1;
				printf("\n");
			}
		}
	}
	r = m-1;
	while (q>=0)
	{
		printf(" %d",a[0]);
		a[0] = a[q];
		shift(a,0,q-1);
		a[q] =a[r];
		r = r -1;
		if (q<mh)
			shift(a,q,r);
		q = q-1;
	}	
	printf("\n");
	while (r>=0)
	{
		printf(" %d",a[0]);
		a[0] = a[r];
		r = r-1;
		shift(a, 0, r);
	}
}

void main()
{
	int b[]={3,5,6,23,65,7,8,0,7,5,4,5,23,5,6,34,7,8,9,1,3,4,50,38,29,2,4, 82, 5, 28,2, 100, 0,1,3,4,20,20,10,600,0,1,0,500};
	//int b[]={5,3,100,2,9,1,78,6,10,5,1,88,7,2,19,40,12,80,26,45,22,11,6,5,78};
	int n = sizeof(b)/sizeof(b[0]);
	in(b,n);
	HeapSort(b,n);
} */


/*
3 5 6 23 65 7 8 0 7 7 5 4 5 23 5 6 34 7 8 9 1 3 4 50 38 29 2 4 82 5 28 2 100 0 1
 3 4 20 20 10 600 0 1 0 500
 0 3 4 5 5 5 6 6 7 7 7 7 8 8 9 23 23 29 34 38 50 65 82 100
 0 1 1 2 2 3 3 4 4 4 5 5 10 20 20 28 500 600
 0 0 1
 */
/*
3 5 6 23 65 7 8 0 7 5 4 5 23 5 6 34 7 8 9 1 3 4 50 38 29 2 4 82 5 28 2 100 0 1 3
 4 20 20 10 600 0 1 0 500
 3 5 6 7 7 8 23 65
 0 4 5 5 5 6 7 8 9 23 34 38 50
 1 2 3 4 4 5 28 29 82 100
 0 1 2 3 4 10 20 20 500 600
 0 0 1
 */