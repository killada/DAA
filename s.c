#include<stdio.h>
#include<stdlib.h>
void create(int *a,int n,int n1)
{
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			scanf("%d",&a[(i*n1)+j]);
		}
	}
}
void print(int *a,int n,int n1)
{
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("%d ",a[(i*n1)+j]);
		}
		printf("\n");
	}
}

void copy(int *a,int*b,int *a1,int *a2,int *a3,int *a4,int *b1,int *b2,int *b3,int *b4,int n)
{
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			a1[i*n +j]=a[i*2*n+j];
			b1[i*n +j]=b[i*2*n+j];
			a2[i*n +j]=a[i*2*n +j+n];
			b2[i*n +j]=b[i*2*n +j+n];
			a3[i*n +j]=a[(i+n)*(2*n)+j];
			b3[i*n +j]=b[(i+n)*(2*n)+j];
			a4[i*n +j]=a[(i+n)*(2*n)+j+n];
			b4[i*n +j]=b[(i+n)*(2*n)+j+n];
		}
	}
}
void add(int *a,int *b, int *c,int n)
{
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		c[(i*n)+j]=a[(i*n)+j]+b[(i*n)+j];	
	}
}

void sub(int *a,int *b, int *c,int n)
{
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		c[(i*n)+j]=a[(i*n)+j]-b[(i*n)+j];	
	}
}

int check(int n)
{
	int num=1;
	while(n>num)
	{
		
		num=num*2;
	}
	return num;
}
void copy1(int *c,int *c11,int *c12,int *c21,int *c22,int n)
{
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			c[i*2*n+j]         = c11[i*n+j];
			c[i*2*n +j+n]      = c12[i*n+j];
			c[(i+n)*(2*n)+j]   = c21[i*n+j];
			c[(i+n)*(2*n)+j+n] = c22[i*n+j];
	
		}
	}
}
//NORMAL MULTIPLICATION
void multiply( int *a,int *b,int *c,int n)
{
	int i,j,k;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			c[(i*n)+j]=0;
			for(k=0;k<n;k++)
			{
				c[(i*n)+j]+=a[(i*n)+k]*b[(k*n)+j];
			}
		}
	}
}
//STRASSENS MATRIX MULTIPLICATION 

void strassens(int *a,int *b, int *c,int n)
{
	int *a11,*a12,*a21,*a22,*b11,*b12,*b21,*b22,*p1,*p2,*p3,*p4,*p5,*p6,*p7,*t1,*t2,*c11,*c12,*c21,*c22;

	if(n==1)
	{
		c[0]=a[0]*b[0];
		return;
	}

	a11=(int*)calloc(n/2 * n/2,sizeof(int));
	a12=(int*)calloc(n/2*n/2,sizeof(int));
	a21=(int*)calloc(n/2*n/2,sizeof(int));
	a22=(int*)calloc(n/2*n/2,sizeof(int));
	b11=(int*)calloc(n/2*n/2,sizeof(int));
	b12=(int*)calloc(n/2*n/2,sizeof(int));
	b21=(int*)calloc(n/2*n/2,sizeof(int));
	b22=(int*)calloc(n/2*n/2,sizeof(int));
	p1=(int*)calloc(n/2*n/2,sizeof(int));
	p2=(int*)calloc(n/2*n/2,sizeof(int));
	p3=(int*)calloc(n/2*n/2,sizeof(int));
	p4=(int*)calloc(n/2*n/2,sizeof(int));
	p5=(int*)calloc(n/2*n/2,sizeof(int));
	p6=(int*)calloc(n/2*n/2,sizeof(int));
	p7=(int*)calloc(n/2*n/2,sizeof(int));
	t1=(int*)calloc(n/2*n/2,sizeof(int));
	t2=(int*)calloc(n/2*n/2,sizeof(int));
	c11=(int*)calloc(n/2*n/2,sizeof(int));
	c12=(int*)calloc(n/2*n/2,sizeof(int));
	c21=(int*)calloc(n/2*n/2,sizeof(int));
	c22=(int*)calloc(n/2*n/2,sizeof(int));
		copy(a,b,a11,a12,a21,a22,b11,b12,b21,b22,n/2);
		
		add(a11,a22,t1,n/2);
		add(b11,b22,t2,n/2);
		strassens(t1,t2,p1,n/2);
		add(a21,a22,t1,n/2);
		strassens(t1,b11,p2,n/2);
		sub(b12,b22,t1,n/2);
		strassens(a11,t1,p3,n/2);
		sub(b21,b11,t1,n/2);
		strassens(a22,t1,p4,n/2);
		add(a11,a12,t1,n/2);
		strassens(t1,b22,p5,n/2);
		sub(a21,a11,t1,n/2);
		add(b11,b12,t2,n/2);
		strassens(t1,t2,p6,n/2);
		sub(a12,a22,t1,n/2);
		add(b21,b22,t2,n/2);
		strassens(t1,t2,p7,n/2);
		
		add(p1,p4,t1,n/2);
		add(t1,p7,t2,n/2);
		sub(t2,p5,c11,n/2);
		add(p3,p5,c12,n/2);
		add(p2,p4,c21,n/2);
		add(p1,p3,t1,n/2);
		add(t1,p6,t2,n/2);
		sub(t2,p2,c22,n/2);
		copy1(c,c11,c12,c21,c22,n/2);
	free(a11);
	free(a12);
	free(a21);
	free(a22);
	free(b11);
	free(b12);
	free(b21);
	free(b22);
	free(t1);
	free(t2);
	free(p1);
	free(p2);
	free(p3);
	free(p4);
	free(p5);
	free(p6);
	free(p7);
	free(c11);
	free(c12);
	free(c21);
	free(c22);
}
//*******************MAIN********************************
int main()
{
	int n,k,n1;
	int *a,*b,*c,*d;
	do
	{
		printf("\n1.Input\n2.Multiplication Bruteforce\n3.Multiplication using strassens\n4.Exit\n Enter ur choice : ");
		scanf("%d",&k);
		printf("\n");
		switch(k)
		{
			case 1:	if(a!=NULL && b!=NULL)
				{
					free(a);
					free(b);
				}
					printf("enter size of square matrix : ");
					scanf("%d",&n);
					if(n>=1)
					{
					
						n1=check(n);
						a=(int*)calloc(n1*n1,sizeof(int));
						b=(int*)calloc(n1*n1,sizeof(int));
						
						printf("enter elements of first matrix\n");
						create(a,n,n1);
						printf("enter elements of second matrix\n");
						create(b,n,n1);
						printf("matrix 1\n");
						print(a,n,n1);
						printf("matrix 2\n");
						print(b,n,n1);
					}
					else
					{
						printf("Invalid size of matrix\n");
					}
					break;
			case 2:	d=(int*)calloc(n1*n1,sizeof(int));
					multiply(a,b,d,n1);
					printf("matrix multiplication by bruteforce\n");
					print(d,n,n1);
					free(d);
					break;
			case 3:c=(int*)calloc(n1*n1,sizeof(int));
					strassens(a,b,c,n1);
					printf("stassens matrix multiplication\n");
					print(c,n,n1);
					free(c);
					break;
			case 4:free(a);
					free(b);
					break;
				
		}
	}while(k!=4);

	return 0;
}

