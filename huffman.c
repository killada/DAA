#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
typedef struct info
{
	int freq;
	char id;
}info;

typedef struct huff
{
         info in_huff;
         struct huff *l,*r;
}huff;

typedef struct node
{
         int flag;
         struct node* next;
	union data
	 {
	   info in;
	   huff * addr;
	 }data;
  
}node;

typedef struct mapping
{
	char * code;
}mapping;


typedef struct qnode
{
	huff * addr;
	struct qnode* next;
	
}qnode;

typedef struct queue
{
	qnode* front,* rear;
}queue;

void init(queue* q)
{
	q->front=q->rear=NULL;
} 
int isempty(queue * q)
{
	if(q->front==NULL)
	return 1;
	return 0;
}
void enqueue(huff *root ,queue* q)
{
	qnode* p;
	p=(qnode*)malloc(sizeof(qnode));
	
	p->addr=root;
	p->next=NULL;
	
	if(q->rear==NULL)
	{
		q->rear=q->front=p;
	}
	else
	{
		q->rear->next=p;
		q->rear=p;
	}	
	
}

huff* dequeue(queue *q)
{
	qnode* p;
	huff* h;
	p=q->front;
	if(q->rear==q->front)
	{
		
		q->rear=q->front=NULL;
	}
	else
	{
		q->front=q->front->next;
		
	}
	h=p->addr;
	free(p);
	return h;
	
}


void heap_up(info *list,int n)
{
	int i=1,c,p;
	info temp;
	for(;i<n;i++)
	{
		c=i;
		p=(c-1)/2;
		temp=list[i];	
		while(temp.freq>list[p].freq && c>0)
		{
			list[c] = list[p];
			c=p;
			p=(c-1)/2;
		}
		list[c]=temp;	
	}
	
}
void heap_sort(info *list,int n)
{
	int i=n-1,c,p;
	info temp;
	for(;i>0;i--)
	{
		temp = list[0];
		list[0] = list[i];
		list[i] = temp;
		p = 0;
		temp = list[p];
		c = 1;
		if((c+1)<i && (list[c].freq < list[c+1].freq))
			c +=1;	
		while(temp.freq < list[c].freq && c < i)
		{
			list[p] = list[c];
			p = c;
			c = 2 * c + 1;
			if((c+1)<i && (list[c].freq <= list[c+1].freq))
			c +=1;	
		}
		list[p] = temp;
	}
	return ;
}
char check(info *list,int n)
{
	char ch;
	int i;
	while(1)
	{
	
		printf("ENTER ID: ");
		scanf(" %c",&ch);
		if(isalpha(ch) && islower(ch))
		{
			for(i=0;i<n;i++)
			{
				if(list[i].id==ch)
				{
					printf("INVALID ID TRY AGAIN\n");
					break;
				}
			}
		}
		if(i==n)
			return ch;
	}
}

info* create(int n)
{
	info* list;
	int i;
	list = (info*)calloc(n,sizeof(info));
	for(i=0;i<n;i++)
	{
		list[i].id=check(list,i);
		printf("ENTER FREQUENCY: ");
		scanf("%d",&list[i].freq);
	}
	return list;
}

node* create_linklst(info *list,int m)
{
       node* n,*p,*head;
       int i;
       head=(node*)malloc(sizeof(node));
	head->flag=0;
       
       head->data.in=list[0];
       
       p=head;
       	for(i=1;i<m;i++)
	{
	  n=(node*)malloc(sizeof(node));
           n->flag=0;
	   p->next=n;
           
	   n->data.in=list[i];
           p=n;
        }
	n->next=NULL;
	free(list);
	return head;
       
}

/*void display(node *n)
{
  while(n!=NULL)
    {
      printf(" \n %d %c - %d",n->flag,n->data.in.id,n->data.in.freq);
      n=n->next;
    }
}*/

node* sort(node* temp,node* head ,int val)
{
	node *p,*q;
	p=head;
	
	if(p->flag==0)
	{
		if(val <= p->data.in.freq)
			{
			
				
				head=temp;
				return head;
		
			} 
	
	}
	else
	{
		if(val <= p->data.addr->in_huff.freq)
			{
				
		
				head=temp;
				return head;
			} 
	}

	q=p;
	p=p->next;
	while(p)
	{
		if(p->flag==0)
		{
			if(val <= p->data.in.freq)
			{
				q->next=temp;
				temp->next=p;
				
				break;
			} 
		}
		else
		{
			if(val <= p->data.addr->in_huff.freq)
			{
				q->next=temp;
				temp->next=p;
				break;
			} 
		}
		q=p;
		p=p->next;
	}
	if(p==NULL)
	{
		q->next=temp;
		temp->next=NULL;
	}

return head;
}
huff* create_hufftree(node* head)
{
	int f;
	huff *lc,*rc,*p;
	node* temp;
	
	while(head!=NULL)
	{
		temp=head;
		head=head->next;
		if(temp->flag==0)
		{
			lc= (huff*)malloc(sizeof(huff));
			lc->in_huff=temp->data.in;
			lc->l=NULL;
			lc->r=NULL;
		}
		else
		{
			lc=temp->data.addr;
		}
		free(temp);		
		if(head==NULL)
			return lc;
		if(head->flag==0)
			{
				rc= (huff*)malloc(sizeof(huff));
				rc->in_huff=head->data.in;
				rc->l=NULL;
				rc->r=NULL;
			}
			else
			{
				rc=head->data.addr;
			}
			
			p= (huff*)malloc(sizeof(huff));
			f=p->in_huff.freq=lc->in_huff.freq + rc->in_huff.freq;
			p->l=lc;
			p->r=rc;
			temp=head;
			temp->flag=1;
			temp->data.addr=p;
			head=head->next;
			if(head!=NULL)
			{
				head=sort(temp,head,f);
			}
			else
			{
				free(temp);
				return p;
			}	
	}
}
void encoding(huff* root,int ind,char arr[],mapping *m)
{
	int i;
	if(root!=NULL)
	{
		if(root->l!=NULL)
		{
			arr[ind]='0';
			encoding(root->l,ind+1,arr,m);
			arr[ind]='1';
			encoding(root->r,ind+1,arr,m);
		}
		else
		{
			m[root->in_huff.id-'a'].code=(char*)calloc(ind+1,sizeof(char));
			for(i=0;i<ind;i++)
			{
				m[root->in_huff.id-'a'].code[i]=arr[i];
	
			}
			m[root->in_huff.id-'a'].code[ind]='\0';
		}
	}
}

void decoding(char str[],huff* root)
{
	int i=0,j=0;
	huff * p;
	char act[100];
	p=root;
	for(;str[i]!='\0';i++)
	{
		if(str[i]=='0')
		p=p->l;
		else
		{
			if(str[i]=='1')
			p=p->r;
			else
			{
				break;
			}
			
		}
		if(p->l==NULL)
		{

			act[j++]=p->in_huff.id;
			p=root;
		}
	}
	if(p!=root && str[i]!='\0')
	{
		printf("INVALID STRING \n");
	}
	else
	{
		act[j]='\0';
		printf("%s\n",act);
	}	
}
void del_huff(huff *head)
{
	if(head!=NULL)
	{
		del_huff(head->l);
		del_huff(head->r);
		free(head);
	}
}
void mem_free(mapping * m,huff* root)
{
	
	del_huff(root);
	
	int i;
	for(i=0;i<26;i++)
		free(m[i].code);
	free(m);
}
void traversal(huff* root)
{
	huff *p;
	queue q;
	init(&q);
	enqueue(root,&q);
	while(!isempty(&q))
	{
		p=dequeue(&q);
		printf("%d  ",p->in_huff.freq);
		if(p->l!=NULL)
		{
			enqueue(p->l,&q);
			enqueue(p->r,&q);
		}
	}
	
}		
int main()
{
	int n,i,k,ch;
	char str[100];
	info* list;
	node* head;
	huff* root=NULL;
	char arr[100];
	mapping *m;
	do
	{
		printf("\n1.CREATE TREE\n2.DISPLAY\n3.ENCODING\n4.DECODING\n5.EXIT\n");	
		scanf("%d",&ch);
		switch(ch)
		{
			case 1 :
				if(root!=NULL)
				{
					mem_free(m,root);
				}
				m=(mapping*)calloc(26,sizeof(mapping));
				printf("ENTER NUMBER OF ELEMENTS: ");
				scanf("%d",&n);
				list = create(n);
				heap_up(list,n);
				heap_sort(list,n);
				for(i=0;i<n;i++)
					printf("%c-%d ",list[i].id,list[i].freq);
				head=create_linklst(list,n);
				root=create_hufftree(head);
				encoding(root,0,arr,m);
				break;
			case 2 :
				if(root==NULL)
				{
					printf("\nCreate Tree first");
				}
			traversal(root); 
				break;
			
			case 3 :if(root!=NULL)
				{
					
					printf("\nENTER STRING TO ENCODE: ");
					scanf("%s",str);
					ch=0;
					for(i=0;str[i]!='\0';i++)
					{
						if(isalpha(str[i]) && islower(str[i]) && m[str[i]-'a'].code!=NULL)
						{
							n=str[i]-'a';
							printf("\n%d %d",n,i);
							for(k=0;m[n].code[k]!='\0';k++)
							{
								arr[ch]=m[n].code[k];
								ch++;
							}
		
						}
						else
						{
							printf("invalid string \n");
							break;
						}

					}
					if(str[i]=='\0')
					{
						arr[ch]='\0';
						printf("\n%s\n",arr);
					}
				}
				else
					printf("CREATE TREE FIRST \n");
				break;
			case 4 :if(root!=NULL)
				{
					printf("enter string for decoding: ");
					scanf("%s",str);
					decoding(str,root);
				}
				else
					printf("CREATE TREE FIRST \n");
				break;

			case 5 :mem_free(m,root); 
				break;
		}
	}while(ch!=5);
return 0;
}







	

