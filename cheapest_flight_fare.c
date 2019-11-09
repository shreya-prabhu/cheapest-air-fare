 #include<stdio.h>
 #include<stdlib.h>

#define INFINITY 9999
#define MAX 10

 typedef struct node
 {
	int adj_vertex;
	int fare;
	int travel_time;
	struct node *next;
 }node;

int visited[50] = {[0 ... 49] = 0};
int t_visited[50] = {[0 ... 49] = 0};
int cost[50][50]={ [0 ... 49][0 ... 49]= INFINITY};
int time[50][50]={ [0 ... 49][0 ... 49]= INFINITY};
node *a[50] = {[0 ... 49] = NULL};
int number_of_vertices,i,j,w,t,l,m;
int startnode,endnode;

void creategraph();
void insert(int i,int j , int w, int t);
void cost_matrix();
void travel_time_matrix();

void dijkstra_cost(int startnode, int endnode);
void dijkstra_time(int startnode, int endnode);

int main()
{
	
	printf("Enter no. of vertices:");
	scanf("%d",&number_of_vertices);

	creategraph();
	
	dijkstra_cost(startnode,endnode);
	dijkstra_time(startnode,endnode);
	
}


void creategraph()
{
   
	int flag = 0;
 	int counter = 1;
    while(!flag)
    {
    	
    	printf("Enter the source vertex,destination vertex fare and time taken for the edge \n");
        printf("Enter -1 -1 as vertices to stop \n");

        scanf("%d %d %d %d",&i,&j,&w,&t);
        insert(i,j,w,t);

        if(counter == number_of_vertices*number_of_vertices || (i==-1 && j==-1))
            		flag = 1;
            
        counter++;
    }
	printf("Enter source and destination airports\n");
	scanf("%d %d", &startnode ,&endnode);

}

//Create a cost matrix to store fares between every two airports
void cost_matrix()
{
	for(int x = 0; x<number_of_vertices; x++)
	{
		node * p = a[x];
		
		while(p!=NULL)
		{
			cost[x][p->adj_vertex] = p->fare;
			p = p->next;
		}
	}
        
}

//Create a travel matrix to store flying time between every two airports
void travel_time_matrix()
{
	for(int x = 0; x<number_of_vertices; x++)
	{
		node * p = a[x];
		
		while(p!=NULL)
		{
			time[x][p->adj_vertex] = p->travel_time;
			p = p->next;
		}
	}
        
}
//adjacency list
void insert(int i, int j,int w, int t)
{
   node *temp;
   temp=(struct node*)malloc(sizeof(struct node));
   temp->adj_vertex = j;
   temp->fare = w;
   temp->travel_time = t;
   temp->next=a[i];
   a[i]=temp;
}



void dijkstra_cost(int startnode, int endnode)
{

 	int price[MAX],prev[MAX];
	int visited[MAX],count,minprice,nextnode,i,j;
	
	cost_matrix();
	
	
	for(i=0;i<number_of_vertices;i++)
	{

		//price[i] tells the cost of travelling from startnode to ith node
		//prev[i] stores the node
		price[i]=cost[startnode][i];
		prev[i]=startnode;
		visited[i]=0;
	}
	
	price[startnode]=0;
	visited[startnode]=1;
	count=1;
	
	while(count<number_of_vertices-1)
	{
		minprice=INFINITY;
		
		//nextnode gives the node at minimum price
		for(i=0;i<number_of_vertices;i++)
		{
			if((price[i]<minprice) && (!visited[i]))
			{
				minprice=price[i];
				nextnode=i;
			}
		}
			
			
			//check if a better path exists through nextnode			
			visited[nextnode]=1;
			for(i=0;i<number_of_vertices;i++)
			{
				if(!visited[i])
					if(minprice+cost[nextnode][i]<price[i])
					{
						price[i]=minprice+cost[nextnode][i];
						prev[i]=nextnode;
					}
			}

		count++;
	}


 
	//print the path and price of each node
	for(i=0;i<number_of_vertices;i++)
		if(i == endnode)
		{
			printf("\nLeast Price of ticket to reach node %d=%d",i,price[i]);
			printf("\nCorresponding path=%d",i);
			
			j=i;
			do
			{
				j=prev[j];
				printf("<-%d",j);
			}while(j!=startnode);
	}
}


void dijkstra_time(int startnode, int endnode)
{
 	int travel_time[MAX],t_prev[MAX];
	int t_visited[MAX],t_count,min_travel_time,nextnode;
	
	travel_time_matrix();
	
	
	//initialize t_prev[],travel_time[] and t_visited[]
	for(i=0;i<number_of_vertices;i++)
	{

		//travel_time[i] tells the time taken to travel from startnode to ith node
		//t_prev[i] stores the node
		travel_time[i]=time[startnode][i];
		t_prev[i]=startnode;
		t_visited[i]=0;
	}
	
	travel_time[startnode]=0;
	t_visited[startnode]=1;
	t_count=1;
	
	while(t_count<number_of_vertices-1)
	{
		min_travel_time=INFINITY;
		
		//nextnode gives the node at minimum travel_time
		for(i=0;i<number_of_vertices;i++)
		{
			if((travel_time[i]<min_travel_time) && (!t_visited[i]))
			{
				min_travel_time=travel_time[i];
				nextnode=i;
			}
		}
			
			
			//check if a better path exists through nextnode			
			t_visited[nextnode]=1;
			for(i=0;i<number_of_vertices;i++)
			{
				if(!t_visited[i])
					if(min_travel_time+cost[nextnode][i]<travel_time[i])
					{
						travel_time[i]=min_travel_time+cost[nextnode][i];
						t_prev[i]=nextnode;
					}
			}

		t_count++;
	}


 
	//print the path and travel_time of each node
	for(int k=0;k<number_of_vertices;k++)
		if(k == endnode)
		{
			printf("\nLeast travel_time of ticket to reach node %d=%d",k,travel_time[k]);
			printf("\nCorresponding path=%d",k);
			
			int h = k;
			do
			{
				h=t_prev[k];
				printf("<-%d",h);
			}while(h!=startnode);
	}
}


 