#include<stdio.h>
#define INFINITY 9999
#define MAX 10
int simplelist[25][25], visited_cities[10],v,cost = 0;
//-----------------------------------------Dijkstra----------------------------------------------------------------------------
void dijkstra(int G[MAX][MAX],int n,int startnode,int pred[],int distance[])
{

	int cost[n][n];
	int visited[MAX],count,mindistance,nextnode,i,j;
	for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            if(G[i][j]==0)
                cost[i][j]=INFINITY;//Putting infinity if nodes have no connection
            else
                cost[i][j]=G[i][j];//Else putting that distance if both are connected
        }
    }
    //Initializing distance , pred and visited
	for(i=0;i<n;i++)
	{
		distance[i]=cost[startnode][i];
		pred[i]=startnode;
		visited[i]=0;
	}

	distance[startnode]=0;
	visited[startnode]=1;
	count=1;
    //This is the logic for dijkstra algorithm
	while(count<n-1)
	{
		mindistance=INFINITY;
		//nextnode gives the node at minimum distance
		for(i=0;i<n;i++)
        {
            if(distance[i]<mindistance&&!visited[i])
            {
				mindistance=distance[i];
				nextnode=i;
            }
        }

        //check if a better path exists through nextnode
        visited[nextnode]=1;
        for(i=0;i<n;i++)
        {
            if(!visited[i])
            {
                if(mindistance+cost[nextnode][i]<distance[i])
                {
                    distance[i]=mindistance+cost[nextnode][i];
                    pred[i]=nextnode;
                }
            }
        }
		count++;
	}

}
//-------------------------------------Tsp-------------------------------------------------------------------------
int tsp(int c)
{
	 int count, nearest_city = 999;
	 int minimum = 999, temp;
	 for(count = 0; count < v; count++)
	 {
		 if((simplelist[c][count] != 0) && (visited_cities[count] == 0))
		 {
			 if(simplelist[c][count] < minimum)
			 {
			 minimum = simplelist[count][0] + simplelist[c][count];
			 temp = simplelist[c][count];
			 nearest_city = count;
			 }
		 }
	 }
	 //updating cost for every visitnodes on by one
	 if(minimum != 999)
	 {
		cost = cost + temp;
	 }
	 return nearest_city;
}
//-------------------------------------------Minimum Cost-------------------------------------------------
void minimum_cost(int city)
	{
		 int nearest_city;
		 visited_cities[city] = 1;
		 printf("%d ", city + 1);
		 nearest_city = tsp(city);
		 if(nearest_city == 999)
		 {
			 nearest_city = 0;
			 printf("%d", nearest_city + 1);
			 cost = cost + simplelist[city][nearest_city];
			 return;
		 }
		minimum_cost(nearest_city);
	}
//----------------------------------------------Main----------------------------------------------------------------------------
int main()
{
	int Adjacency[MAX][MAX],i,j,n,u;
	printf("Enter total no. of vertices:");
	scanf("%d",&n);
	printf("\nEnter the adjacency matrix:\n");
	//--Adjacency stores the adjacency list of graph
	for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            scanf("%d",&Adjacency[i][j]);
        }
    }
    //distance stores the individual shortest distances
    //pred stores the previous node list it helps to traceback path
	int pred[n],distance[n];
	printf("Enter no of vertices to visit including starting vertex at first  :");
	scanf("%d",&v);
	int visitnodelist[v];
	//v denotes no. of nodes to visit
	//visitnodelist contains the list of node that delivery boy needs to deliver pizza
	for(i=0;i<v;i++)
    {
        printf("Enter %d vertices no.:",i);
        scanf("%d",&visitnodelist[i]);
    }
	int pre[v][n];
	for(i=0;i<v;i++)
    {
        dijkstra(Adjacency,n,visitnodelist[i],pred,distance);
        for(j=0;j<n;j++)
        {
            simplelist[i][j]=distance[j];
            //simplelist stores the adjacency list for only visit nodes i.e. v*n
            pre[i][j]=pred[j];
            //pre matrix stores the pred matrix for all nodes in visitnodelist
        }
        visited_cities[i] = 0;
    }
//-------------------------------------------------Printing Part---------------------------------------------------------
    /*for(i=0;i<v;i++)
    {
        for(j=0;j<n;j++)
        {
            printf("%d ",simplelist[i][j]);
        }
        printf("\n");
    }
    for(i=0;i<v;i++)
    {
        for(j=0;j<n;j++)
        {
            printf("%d ",pre[i][j]);
        }
        printf("\n");
    }*/
   //print the path and distance of each node
   int k,startnode;
	for(i=0;i<v;i++)
      {
        startnode=visitnodelist[i];
        printf("\n----------------From Node %d----------------\n",startnode);
        for(j=0;j<n;j++)
        {
            if(j!=startnode)
            {
                printf("\nDistance of node%d=%d",j,simplelist[i][j]);
                printf("\nPath=%d",j);
                k=j;
                do
                {
                    k=pre[i][k];
                    printf("<-%d",k);
                }while(k!=startnode);
            }
        }
      }
//------------------------------------------------Traveling salesman Problem-------------------------------------------------------------------
	//Updating simplelist to store first v columns as visitnodeslist only
	for(i=0;i<v;i++)
	{
		for(j=0;j<v;j++)
		{
			k=visitnodelist[j];
			simplelist[i][j]=simplelist[i][k];
			//printf("%d ",simplelist[i][j]);
		}
		printf("\n");
	}
	 printf("\n\nPath:\t");

	 minimum_cost(0);

	 printf("\n\nMinimum Cost: \t");
	 printf("%d\n", cost);
	return 0;
}
