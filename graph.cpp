#include "graph.h"


Graph::Graph()
{

}

Graph::Graph(int number_nodes)
{

    adj_list.resize(number_nodes);
    nodes_edges.resize(number_nodes,0);


}

void Graph::set_numberNode(int number_nodes)
{
    adj_list.resize(number_nodes);
    nodes_edges.resize(number_nodes,0);

}

void Graph::read_File(ifstream& myFile,vector<pair<int,int> >& nodes_and_edges)
{

    int node,adjacent_node,edge_weight;

    while(!(myFile.eof()))
    {
        myFile>>node>>adjacent_node>>edge_weight;

        /*GUI*/
        nodes_and_edges.push_back({node,adjacent_node});
        /*===*/

        adj_list[node].push_back({adjacent_node,edge_weight});
        adj_list[adjacent_node].push_back({node,edge_weight});
        nodes_edges[node]++;
        nodes_edges[adjacent_node]++;
    }


}

void Graph::read_File(int number_edges,vector<pair<int,int> >& nodes_and_edges)
{

    int node,adjacent_node,edge_weight;

    cout<<"\n\t\t** Now Please Enter The Node , Adjacent Node and Weight Separated By Spaces **\n\n";

    while(number_edges--)
    {
        cin>>node>>adjacent_node>>edge_weight;

        /*GUI*/
        nodes_and_edges.push_back({node,adjacent_node});
        /*===*/

        adj_list[node].push_back({adjacent_node,edge_weight});
        adj_list[adjacent_node].push_back({node,edge_weight});
        nodes_edges[node]++;
        nodes_edges[adjacent_node]++;

    }

}



void Graph::degree_printAll(vector<int>& DegreeCentralities)
{

    int size=nodes_edges.size();
    for(int i=0;i<size;i++)
       {
            cout<<"Node("<<i<<") ==> Degree="<<nodes_edges[i]<<endl;

            /*GUI*/
            DegreeCentralities[i]=nodes_edges[i];
            /*======*/
       }

}

void Graph::print_adjacencyList()
{


    for(int i=0;i<adj_list.size();i++)
    {
        list<pair<int,int> >::iterator it;

        for(it=adj_list[i].begin();it!=adj_list[i].end();it++)
        {

                cout<<i<<"=="<<it->second<<"==>"<<it->first<<endl;
        }
    }


}


void Graph::shortest_Path(int source,vector<int>& shortest_distances,vector<int>& parents)
{

    //pair (distance , node)
    priority_queue<pair<pair<int,int>,int>,vector<pair<pair<int,int>,int> >,greater<pair<pair<int,int>,int> > > p_queue;

    p_queue.push({{0,source},source});
    shortest_distances[source]=0;
    parents[source]=source;


    list<pair<int,int> >::iterator it;

    while(!(p_queue.empty()))
    {

        int next_node=p_queue.top().first.second;
        int accumlative_distance=p_queue.top().first.first;
        int parent=p_queue.top().second;
        p_queue.pop();


    if(shortest_distances[next_node] == INFINITY)
    {

        shortest_distances[next_node]=accumlative_distance;
        parents[next_node]=parent;
    }


        for(it=adj_list[next_node].begin();it!=adj_list[next_node].end();it++)
        {


            int adj_node= it->first;
            int adj_node_weight=it->second;




            if(shortest_distances[adj_node] == INFINITY)
            {

                p_queue.push({{adj_node_weight+accumlative_distance,adj_node},next_node});

            }


        }



    }

}



void Graph::closenessCentrality_printAll(vector<float>& ClosenessCentralities)
{



    int size=adj_list.size();
    int sum;

    for(int i=0;i<size;i++)
    {

    sum=0;
    vector<int> shortest_distances(size,INFINITY);
    vector<int> parents(size,-1);

    shortest_Path(i,shortest_distances,parents);

    for(int j=0;j<size;j++)
    {
        sum+=shortest_distances[j];
    }

    ClosenessCentralities[i]=((float)(size-1))/sum;
    cout<<setprecision(9)<<ClosenessCentralities[i]<<endl;


    }



}




void Graph::shortest_Path(int source, vector<vector<int> >& shortest_distances, vector<vector<int> >& parents,vector<int>& Conjunctions)
{

	//pair (distance , node)
	priority_queue<PriorityElement, vector<PriorityElement>, myComparator> p_queue;
	PriorityElement Pri_Element;

	vector<int> GlobalMini_Distances(adj_list.size(), INFINITY);

	int number_NewTables = 0, index;
	int branched = 0;
	int size = adj_list.size();


	Pri_Element.Distance = 0;
	Pri_Element.Node = source;
	Pri_Element.Parent = source;
	Pri_Element.Table = 0;

	p_queue.push(Pri_Element);

	shortest_distances[0][source] = 0;
	parents[0][source] = source;


	list<pair<int, int> >::iterator it;

	while (!(p_queue.empty()))
	{

		branched = 0;
		int next_node = p_queue.top().Node;
		int accumlative_distance = p_queue.top().Distance;
		int parent = p_queue.top().Parent;
		int table = p_queue.top().Table;
		p_queue.pop();




		if (GlobalMini_Distances[next_node] == INFINITY)
		{

			shortest_distances[table][next_node] = accumlative_distance;
			GlobalMini_Distances[next_node] = accumlative_distance;
			parents[table][next_node] = parent;

		}
		else if ((GlobalMini_Distances[next_node] == accumlative_distance))
		{
			if (shortest_distances[table][next_node] != INFINITY)
			{
				++number_NewTables;
				Conjunctions.push_back(table);
				shortest_distances.resize(shortest_distances.size() + 1, vector<int>(size, INFINITY));
				parents.resize(parents.size() + 1, vector<int>(size, -1));
				index = number_NewTables;
				branched = 1;

			}
			else
			{
				index = table;

			}

			shortest_distances[index][next_node] = accumlative_distance;
			parents[index][next_node] = parent;


		}


		if (branched)
			table = number_NewTables;


		for (it = adj_list[next_node].begin(); it != adj_list[next_node].end(); it++)
		{


			int adj_node = it->first;
			int adj_node_weight = it->second;



			if (GlobalMini_Distances[adj_node] == INFINITY)
			{


				Pri_Element.Distance = adj_node_weight + accumlative_distance;
				Pri_Element.Node = adj_node;
				Pri_Element.Parent = next_node;
				Pri_Element.Table = table;
				p_queue.push(Pri_Element);

			}



		}



	}

}



void Graph::betwenessCentrality_printAll()
{

	int size = adj_list.size();
	vector<vector<int> > shortest_distances(1, vector<int>(size, INFINITY));
	vector<vector<int> > parents(1, vector<int>(size, -1));
	vector<int> conjunctions;

	shortest_Path(0, shortest_distances, parents,conjunctions);

}
