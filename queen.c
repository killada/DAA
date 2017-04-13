#include<stdio.h>
#include<stdlib.h>
int place(int row2,int col2,int *A)
{
	int i;
	for(i=0;i<row2;i++)
	{
		int row1=i;
		int col1=A[i];
		if(abs(row1-row2)==abs(col1-col2)||col2==col1)
			return 0;	
	}
	return 1;
}
void print(int n,int *A)
{
				int m=0,i,j,last=2*n+1,test=0;
				for(i=0;i<last;i++)
				{	
					
					if(i%2==0)
					{	
						for(j=0;j<last;j++)
						{
							printf("_");
						}
						printf("\n");
					}
					else
					{
						for(j=0;j<last;j++)
						{
							if(j%2==0)
								printf("|");
							else
							{
	
								test=2*(A[m])+1;
								//printf("%d %d\n",m,A[m]);
								if(j==test)
								{
									printf("Q");
									
								}
								else
									printf("-");	
							}
							
						}
						printf("\n");
						m++;
					}
					
					//m++;
				}
}
int nq(int n,int *A,int flag)
{
	int count=0,i;
	int k=0;
	
	while(k>=0)
	{
		A[k]=A[k]+1;
		if(A[k]<=n-1)
		{
			if(place(k,A[k],A))
			{
				if(k==n-1)
				{
					count++;
					printf("\n%d solution\n",count);
					print(n,A);
					if(flag==0)
						return 1;
				}
				else
					k=k+1;
			}
		}
		else
		{
			A[k]=-1;
			k=k-1;
		}
				
	}
	return count;
}
int rnq(int k,int n,int *A,int flag,int *count)
{
	int i;
	for(i=0;i<n;i++)
	{
		if(flag==-1)
			return flag;
		if(place(k,i,A))
		{
			A[k]=i;
			if(k==n-1)
			{
				*count=*count+1;
				printf("%d solution is\n",*count);
				print(n,A);
				if(flag==0)
					return -1;
			}
			else
				flag=rnq(k+1,n,A,flag,count);
		}
	}
	return flag;
}
int main()
{
	int n=0,i,j,k=0,*A,l=0,track=0;
	while(j!=4)
	{
		printf("Enter Your Choice:\n");
		printf("1.Enter the number of queens(Must be greater than 3)\n2.Solution by Iterative Backtracking\n3.Solution by recursive backtracking\n4.Exit\n");
		scanf("%d",&j);
		switch(j)
		{
			case 1:printf("\n Enter the number of queens\n");
					scanf("%d",&n);
					if(n<=3)
					{
						printf("Number of queens must be greater than 3\n");
						
					}
					break;
			case 2:	if(n==0)
				{
					printf("\n Enter the number of queens first\n");
					break;
				}
				else
				{
					A=malloc(sizeof (int) * n);
					
					while(k!=3)
					{
						printf("\n1.Do you want only one solution?\n2.Do you want to see all possible solutions\n3.Exit\n");
						
						scanf("%d",&k);
						for(i=0;i<n;i++)
						{
							A[i]=-1;
						}
						switch(k)
						{
							case 1://test=0;
								nq(n,A,0);
								//track=0;
								break;
							case 2:	printf("\n Total solutions are %d\n",nq(n,A,1));
								//track=0;
								break;
							case 3:break;
							default:exit(0);
						}	
					}
					k=0;
					free(A);
					break;
				}
			case 3:	if(n==0)
				{
					printf("\n Enter the number of queens first\n");
					break;
				}
				else
				{
					A=malloc(sizeof (int) * n);	
					
					while(k!=3)
					{
						printf("\n1.Do you want only one solution?\n2.Do you want to see all possible solutions\n3.Exit\n");
						scanf("%d",&k);
						switch(k)
						{
					
							case 1:	track=0;
								rnq(0,n,A,0,&track);
								//track=0;
								break;
							case 2:	track=0;
								rnq(0,n,A,1,&track);
								printf("\n Total solutions are %d\n",track);
								//track=0;
								break;
							case 3:break;
							default:exit(0);
						}
					}
					k=0;
					free(A);
					break;
				}
			default: //free(A);
				exit(0);		
	
					
		}
	}	
	
	return 0;



}
