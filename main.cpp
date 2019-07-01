#include <iostream>
#include <list>
#include <vector>
#include <fstream>
#include <windows.h>
#include "graph.h"
using namespace std;




int main()
{

    int total_nodes=0,again=1,total_edges=0;
    char way;


    cout<<"\n\t\t\t\t   Welcome To The Social Media Analysis Project\n";
    cout<<"\t\t\t\t   ============================================\n\n";
    cout<<"\t\t\tAuthors: Abdelrahman Shawqy , Alaa Atef , Zyad Mohamed and Samir Mossad\n";
    cout<<"\t\t\t=======================================================================\n\n";


    while(again)
    {
    Graph myGraph;

    /*GUI*/
     vector<pair<int,int> > nodes_and_edges;
    /*=====*/



    cout<<"** Please choose a way for the input data:\n\t (a)Text File: Enter F \t (b)Console: Enter C\n";
    cin>>way;





    if(way=='F' || way=='f')
    {

 /*Using a text File*/
    ifstream myFile("App_Data/input_file.txt");
    myFile>>total_nodes>>total_edges;
    myGraph.set_numberNode(total_nodes);
    myGraph.read_File(myFile,nodes_and_edges);

    }

    else
    {

    /*using the CLI */
    cout<<"\n** Enter the total number of nodes: ";
    cin>>total_nodes;
    cout<<"\n** Enter the total number of edges: ";
    cin>>total_edges;
    myGraph.set_numberNode(total_nodes);
    myGraph.read_File(total_edges,nodes_and_edges);

    }




     vector<int> DegreeCentralities(total_nodes,0);
     vector<float> ClosenessCentralities(total_nodes,0);

    cout<<"\nDegree-Centerality"<<endl;
    cout<<"==================\n";
    myGraph.degree_printAll(DegreeCentralities);
    cout<<"\nCloseness-Centerality"<<endl;
    cout<<"=====================\n";
    myGraph.closenessCentrality_printAll(ClosenessCentralities);




    ofstream outFile1;
    ofstream outFile2;
    outFile1.open("App_Data/degree_centrality.txt");
    outFile2.open("App_Data/closeness_centrality.txt");
    outFile1<<total_nodes<<" "<<total_edges<<endl;
    outFile2<<total_nodes<<" "<<total_edges<<endl;



    for(int i=0;i<total_edges;i++)
    {

     outFile1<<nodes_and_edges[i].first<<" "<<nodes_and_edges[i].second<<endl;
     outFile2<<nodes_and_edges[i].first<<" "<<nodes_and_edges[i].second<<endl;

    }


    for(int i=0;i<total_nodes;i++)
        outFile1<<DegreeCentralities[i]<<endl;

    for(int i=0;i<total_nodes;i++)
        outFile2<<(int)(ClosenessCentralities[i]*20)%4<<endl;

    outFile1.close();
    outFile2.close();

    ShellExecute(NULL, "open", "App.exe", NULL, NULL, SW_SHOWDEFAULT);


    cout<<"\n\n ** For Another Input Press (Y) , To Exit Press (N)\n";
    cin>>way;

    if(way== 'Y' || way== 'y') again=1;
    else                       again=0;


    }

    cout<<"\n\n\t\t\t\t **** Thank You for using our application, See you next time <3 ****\n\n";


    return 0;
}
