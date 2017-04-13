#include<stdio.h>
#include<stdlib.h>
void create(int *w,int n)
{
	int src,dest;
	char ch;
	do
	{
		printf("\nIS THEIR ANY EDGE PRESS Y IF YES ELSE N : ");
		scanf(" %c",&ch);
		if(ch=='y')
		{
			printf("\n ENTER SOURCE VERTEX : ");
			scanf("%d",&src);
			if(src<=n && src>0)
			{
				printf("\n ENTER DESTINATION VERTEX : ");
				scanf("%d",&dest);
				if(dest<=n && dest>0)
				{
								
					if(w[(src-1)*n+dest-1]==1)
					{
						printf("\n Edge already exists\n");
					}
					else
						w[(src-1)*n+dest-1]=1;
					
								
				}
				else
				{
					printf("\ninvalid destination\n");
				}
			}
			else
				printf("\ninvalid source\n");
		}
	}while(ch=='y');
	
}
void print(int *a,int n)
{
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			printf(" %d ",a[(i*n)+j]);
		}
		printf("\n");
	}
}
void nextval(int k,int n,int *x,int *adj)
{
	int i;
	while(1)
	{
		if(x[k]==n)
			x[k]=-1;
		x[k]=x[k]+1;
		if(x[k]==n)
			return;
		if(adj[x[k-1]*n+x[k]]==1)
		{
			for(i=0;i<k;i++)
			{
				if(x[i]==x[k])
					break;
			}
			if(i==k)
			{
				if((k<n-1) || ((k==n-1) && adj[x[k]*n+0]==1))
					return;
			}
		}
	}
}
int rec(int k,int n,int flag,int *x,int *adj,int *count)
{
	int i;
	while(1)
	{
		if(flag==-1)
			return flag;
		nextval(k,n,x,adj);
		if(x[k]==n)
		{
			return flag;
		}
		if(k==n-1)
		{
			*count=*count+1;
			printf("\nsolution %d is\n",*count);
			for(i=0;i<n;i++)
				printf("%d->",x[i]+1);
			printf("%d",1);
			printf("\n");
			if(flag==0)
				return -1;
		}
		else
		{
			flag=rec(k+1,n,flag,x,adj,count);
		}
	}
	return flag;
}
int ite(int n,int flag,int *x,int *adj)
{
	int i,count=0,k;
	k=1;
	while(k>0 && k<n)
	{
		nextval(k,n,x,adj);
		if(x[k]==n)
		{
			x[k]=-1;
			k=k-1;
		}
		else
		{
			if(k==n-1)
			{
				count++;
				printf("\nsolution %d is\n",count);
				for(i=0;i<n;i++)
					printf("%d->",x[i]+1);
				printf("%d",1);
				printf("\n");
				if(flag==0)
					return 1;
			}
			else
			{
				k=k+1;
			}
		}
	}
	return count;;
}
int main()
{
	int k,n,i,l,count=0;
	int *adj=NULL,*x;
	do
	{
		printf("\n1.Enter the graph\n2.Recursive Backtracking\n3.Iterative Backtracking\n4.Exit\n ENTER UR CHOICE : ");
		scanf("%d",&k);
		switch(k)
		{
			case 1:if(adj!=NULL)
					free(adj);
				printf("\nENTER NO. OF VERTICES : ");
					scanf("%d",&n);
					adj=(int*)calloc(n*n,sizeof(int));
					create(adj,n);
					print(adj,n);
					break;
			case 2:
				do
				{
					printf("\n1.Do you want only one solution?\n2.Do you want to see all possible solutions\n3.Exit\n");	
					scanf("%d",&l);
					x=(int*)malloc(n*sizeof(int));
					x[0]=0;
					for(i=1;i<n;i++)
						x[i]=-1;
					switch(l)
					{
						case 1:count=0;
							rec(1,n,0,x,adj,&count);
							break;
						case 2:	count=0;
							rec(1,n,1,x,adj,&count);
							printf("\n Total solutions are %d\n",count);
							break;
						case 3:break;
					}
					free(x);	
				}while(l!=3);
				break;
			case 3:do
				{
					printf("\n1.Do you want only one solution?\n2.Do you want to see all possible solutions\n3.Exit\n");	
					scanf("%d",&l);
					x=(int*)malloc(n*sizeof(int));
					x[0]=0;
					for(i=1;i<n;i++)
						x[i]=-1;
					switch(l)
					{
						case 1:ite(n,0,x,adj);
							break;
						case 2:printf("\n Total solutions are %d\n",ite(n,1,x,adj));
							break;
						case 3:break;
					}
					free(x);	
				}while(l!=3);
				break;
			case 4:printf("\nExited\n");
				free(adj);
				//exit(0);
				break;
		}
	}while(k!=4);
}
