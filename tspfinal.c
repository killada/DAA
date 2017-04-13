#include<stdlib.h>
#include<stdio.h>
#include<limits.h>
typedef struct node
{
	int lower,*rcm,vertex,level;
	struct node *parent;
}node;

typedef struct list
{
	node *address;
	struct list *next;
}list;

void print(int *a,int n)
{
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(a[(i*n)+j]==INT_MAX)
				printf(" # ");
			else
				printf(" %d ",a[(i*n)+j]);
		}
		printf("\n");
	}
	printf("\n");
}

void create(int *f,int n)
{
	int src,dest,wt,i,j;
	char ch;
	
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			f[i*n+j]=INT_MAX;	
		}	
	}	
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
								if(f[(src-1)*n+dest-1]!=INT_MAX)
								{
									printf("\n Edge already exists\n");
								}
								else
								{
									printf("\nenter weight of %d->%d : ",src,dest);
									scanf("%d",&wt);
									if(wt<0)
									{
										printf("\n NEgitive weights not allowed\n");
									}
									else
										f[(src-1)*n+dest-1]=wt;
								}
							}
							else
							{
								printf("\ninvalid destination\n");
							}
						}
						else
							printf("\ninvalid source");
					}
	}while(ch=='y');
	
}
/*void create(int *w,int n)
{
	int i,j,temp;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			scanf("%d",&temp);
			if(temp>=100)
				w[i*n+j]=INT_MAX;
			else
				w[i*n+j]=temp;
		}
	}
}*/
list *push(list *start,node *nod,int n)
{
	list *temp, *current,*previous;
	temp=(struct list *)malloc(sizeof(struct list));
	temp->address=nod;
	temp->next=NULL;
	if(start==NULL)
		start=temp;
	else if(start->address->lower>nod->lower)
	{
		temp->next=start;
		start=temp;
	}
	else
	{
		current=start;
		previous=NULL;
		while(current!=NULL && current->address->lower<=nod->lower)
		{
			previous=current;
			current=current->next;
		}	
		temp->next=current;
		previous->next=temp;
	}
	return start;
}	
list *del(list *start)
{
	list *ptr;
	ptr=start;
	if(ptr!=NULL)
	{
		start=ptr->next;
		free(ptr);
		return start;
	}
	else
	{
		printf("\nLive nodes list is Empty\n");
		//return NULL;
	}		
}
node *rcm(node *nod,int *w,int n)
{
	int i,j,min,lower=0,k,*rcm;
	rcm=(int*)calloc(n*n,sizeof(int));
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			rcm[i*n+j]=w[i*n+j];
		}
	}
	if(nod->parent!=NULL)
	{
		i=nod->parent->vertex;
		for(j=0;j<n;j++)
			rcm[i*n+j]=INT_MAX;
		j=nod->vertex;
		for(i=0;i<n;i++)
			rcm[i*n+j]=INT_MAX;
		rcm[j*n+0]=INT_MAX;
	}
	for(i=0;i<n;i++)
	{
		min=INT_MAX;
		for(j=0;j<n;j++)
		{
			if(rcm[i*n+j]<min)
				min=rcm[i*n+j];
		}
		if(min!=0 && min!=INT_MAX)
		{
			lower+=min;
			for(k=0;k<n;k++)
			{
				if(rcm[i*n+k]!=INT_MAX)
					rcm[i*n+k]-=min;
			}
		}
	}
	for(j=0;j<n;j++)
	{
		min=INT_MAX;
		for(i=0;i<n;i++)
		{
			if(rcm[i*n+j]<min)
				min=rcm[i*n+j];
		}
		if(min!=INT_MAX)
			lower+=min;
		if(min!=0 && min!=INT_MAX)
		{
			for(k=0;k<n;k++)
			{
				if(rcm[k*n+j]!=INT_MAX)
					rcm[k*n+j]-=min;
			}
		}
	}
	if(nod->parent==NULL)
	{
		nod->lower=lower;
		nod->rcm=rcm;
	}
	else
	{
		nod->lower=lower+nod->parent->lower+nod->parent->rcm[nod->parent->vertex*n+nod->vertex];
		nod->rcm=rcm;
	}
	//printf("\n");
	return nod;
}
void solution(node *nod,int n)
{
	int i=n-1;
	int *x=(int*)calloc(n,sizeof(int));
	printf("\n %d is the distance of the cycle\n",nod->lower);
	while(nod!=NULL && i>=0)
	{
		x[i]=nod->vertex;
		nod=nod->parent;
		i--;
	}
	for(i=0;i<n;i++)
	{
		printf("%d->",x[i]+1);
	}
	printf("1\n");
	free(x);
}
void free_node(node *nod)
{
	free(nod->rcm);
	free(nod);
}
void free_list(list *dead)
{
	list *ptr;
	ptr=dead;
	while(ptr!=NULL)
	{
		dead=ptr->next;
		free_node(ptr->address);
		free(ptr);
		ptr=dead;
	}
}	
void tsp(list *live,int n,list *dead,int bound,int *adj)
{
	
	int i;
	node *E,*temp,*answer=NULL;
	list *dtemp,*ptr;
	while(1)
	{
		if(live==NULL)
			break;
		E=live->address;
		live=del(live);
		if(E->lower<=bound)
		{
			for(i=1;i<n;i++)
			{
				
				if(E->rcm[E->vertex*n+i]!=INT_MAX)
				{
					temp=(struct node *)malloc(sizeof(struct node));
					temp->vertex=i;
					temp->level=E->level+1;
					temp->parent=E;
					temp=rcm(temp,E->rcm,n);
					
					if(temp->level==n-1)
					{
						if(adj[temp->vertex*n]!=INT_MAX && temp->lower<bound)
						{
							if(answer==NULL)
								answer=temp;
							else
							{
								free_node(answer);
								answer=temp;
							}	
							bound=temp->lower;
						}
						else
							free_node(temp);
					}
					else
						live=push(live,temp,n);

			
				}
				
			}
			dtemp=(struct list *)malloc(sizeof(struct list));
			dtemp->address=E;
			dtemp->next=dead;
			dead=dtemp;
		}
		else
		{
			//printf("\n node with %d cost is killed\n",E->lower); 
			free_node(E);
		}
	}
	if(answer==NULL)
		printf("\n No solution\n");
	else
		solution(answer,n);
	
	free_list(dead);	
}		
int main()
{
	int k,n,i,*w=NULL,bound=INT_MAX;
	node *root;
	list *live,*dead=NULL;
	do
	{
		printf("\n1.Enter the graph\n2.Solve TSP with LCBB\n3.Exit\n");
		scanf("%d",&k);
		switch(k)
		{
			case 1:if(w!=NULL)
					free(w);
				printf("\nENTER NO. OF VERTICES : ");
				scanf("%d",&n);
				w=(int*)calloc(n*n,sizeof(int));
				create(w,n);
				printf("\n.......MATRIX.....\n");
				print(w,n);
				break;
			case 2:if(n==0)
				{
					printf("\n First enter the graph\n");
					break;
				}
				root=(struct node *)malloc(sizeof(struct node));
				root->parent=NULL;
				root->level=0;
				root->vertex=0;
				root=rcm(root,w,n);
				live=NULL;
				live=push(live,root,n);
				tsp(live,n,dead,bound,w);
				break;
			case 3:free(w);
				break;
		}
	}while(k!=3);						
}
