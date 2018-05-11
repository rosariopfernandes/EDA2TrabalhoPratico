#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Graphs
{  private:
     //GRAPH
	 struct Edge
	 {  int vertex_id,edge_weight;
		Edge *next_edge;
	 };

	 struct Vertex
	 {  int vertex_id;
		Vertex *next_vertex;
		Edge *edge_head,*edge_tail;
	 }
	 *graph_vertex_head,*graph_vertex_tail;
	 
	 int number_of_vertices_on_the_graph;
	 
	 //DIJKSTRA
	 struct Dijkstra_Single_Source_Shortest_Paths
	 {  int source_id, destination_id, vertex_weight;
        bool vertex_visit;
     };
	 vector<Dijkstra_Single_Source_Shortest_Paths>dijkstra_shortest_path_tree;
	 //DIJKSTRA

   
  public:
    Graphs();
	//GRAPH
	void add_vertex(int vertex_id);
	void add_edge(int source_id,int destination_id,int edge_weight);
	Edge* edges_of_a_vertex(int vertex_id);
	//GRAPH
	
	//DIJKSTRA
	void dijkstra();
	void dijkstra_input();
	void initialize_dijkstra_single_source_shortest_paths(int source_vertex);
	void dijkstra_single_source_shortest_paths(int source_id,int destination_id);
	int next_visit();
	void view_dijkstra_single_source_shortest_paths();
	//DIJKSTRA
};

Graphs::Graphs()
{
    graph_vertex_head=graph_vertex_tail=NULL;
    number_of_vertices_on_the_graph=0;
}

void Graphs::add_vertex(int vertex_id)
{  Vertex *new_vertex;
   new_vertex=new Vertex;
   new_vertex->vertex_id=vertex_id;
   new_vertex->edge_head=NULL;
   new_vertex->edge_tail=NULL;
   new_vertex->next_vertex=NULL;

   if(graph_vertex_head==NULL)
   {  graph_vertex_head=graph_vertex_tail=new_vertex;
   }
   else
   {  graph_vertex_tail->next_vertex=new_vertex;
   	  graph_vertex_tail=new_vertex;
   }
   
   number_of_vertices_on_the_graph++;
}

void Graphs::add_edge(int source_id,int destination_id,int edge_weight)
{  Vertex *vertex_pointer;
   Edge *new_edge;
   
   vertex_pointer=graph_vertex_head;
   
   while(vertex_pointer!=NULL)
   {  if(vertex_pointer->vertex_id==source_id)
      {  new_edge=new Edge;
         new_edge->vertex_id=destination_id;
         new_edge->edge_weight=edge_weight;
         new_edge->next_edge=NULL;
	     if(vertex_pointer->edge_head==NULL)
	     {  vertex_pointer->edge_head=vertex_pointer->edge_tail=new_edge;
		 }
		 else
		 {  vertex_pointer->edge_tail->next_edge=new_edge;
		 	vertex_pointer->edge_tail=new_edge;
		 }
      }
      vertex_pointer=vertex_pointer->next_vertex;
   }
}

Graphs::Edge*Graphs::edges_of_a_vertex(int vertex_id)
{  Vertex *vertex_pointer;
   
   vertex_pointer=graph_vertex_head;
   while(vertex_pointer!=NULL)
   {  if(vertex_pointer->vertex_id==vertex_id)
      {  return vertex_pointer->edge_head;
	  }
	  vertex_pointer=vertex_pointer->next_vertex;
   }
   return NULL;
}

void Graphs::dijkstra()
{
    dijkstra_input();

   int source_id,destination_id;
   cout<<"SOURCE?"<<endl;
   cin>>source_id;
   cout<<"DESTINATION?"<<endl;
   cin>>destination_id;
   cout<<endl;
   
   initialize_dijkstra_single_source_shortest_paths(source_id);
   
   dijkstra_single_source_shortest_paths(source_id,destination_id);
   
   view_dijkstra_single_source_shortest_paths();
}

void Graphs::dijkstra_input()
{  graph_vertex_head=graph_vertex_tail=NULL;
   add_vertex(0);
   add_vertex(1);
   add_vertex(2);
   add_vertex(3);
   add_vertex(4);
   
   add_edge(0,4,5);
   add_edge(0,2,1);
   add_edge(1,0,1);
   add_edge(1,2,5);
   add_edge(2,3,1);
   add_edge(3,0,3);
   add_edge(3,4,2); 
}

void Graphs::initialize_dijkstra_single_source_shortest_paths(int source_id)
{  Vertex *vertex_pointer;
   Dijkstra_Single_Source_Shortest_Paths new_path;
   
   vertex_pointer=graph_vertex_head;
   while(vertex_pointer!=NULL)
   {  new_path.source_id=-1;
	  new_path.destination_id=vertex_pointer->vertex_id;
	  if(vertex_pointer->vertex_id==source_id)
      {  new_path.vertex_weight=0;
      }
	  else
      {  new_path.vertex_weight=999;
	  }
	  new_path.vertex_visit=false;
	  
	  dijkstra_shortest_path_tree.push_back(new_path);
	  
	  vertex_pointer=vertex_pointer->next_vertex;
   }
}

int Graphs::next_visit()
{  int minimum_edge_weight=9999;
   int next_visit;
   //O VERTICE A PESQUISAR SERA O PROXIMO MENOR QUE NAO ESTEJA TRATADO NO VECTOR
   for(int i= 0;i<dijkstra_shortest_path_tree.size();i++)
   {  if(minimum_edge_weight>=dijkstra_shortest_path_tree[i].vertex_weight&&!dijkstra_shortest_path_tree[i].vertex_visit)
      {  minimum_edge_weight= dijkstra_shortest_path_tree[i].vertex_weight;
         next_visit=i;
      }
   }
   return next_visit;
}

void Graphs::dijkstra_single_source_shortest_paths(int source_id,int destination_id)
{  Edge *edge_pointer;
   int number_of_vertices_in_dijkstra_shortest_path_tree=0;
   int next_visit_position=next_visit();
   int next_visit_weight=dijkstra_shortest_path_tree[next_visit_position].vertex_weight;
   int next_visit_destination_id=dijkstra_shortest_path_tree[next_visit_position].destination_id;
   
   while(number_of_vertices_in_dijkstra_shortest_path_tree!=number_of_vertices_on_the_graph)
   {  next_visit_position=next_visit();
      next_visit_weight=dijkstra_shortest_path_tree[next_visit_position].vertex_weight;
      next_visit_destination_id=dijkstra_shortest_path_tree[next_visit_position].destination_id;
   
      edge_pointer=edges_of_a_vertex(next_visit_destination_id);
      while (edge_pointer!=NULL)//PARA CADA SUCESSOR DESTE VERTICE VOU TER QUE ALTERAR SEU REPRESENTATE E PESO
	  {  for(int i= 0;i<dijkstra_shortest_path_tree.size();i++)//PROCURAR PELO SUCESSOR DO VERTICE QUE ESTAMOS A TRATAR
	     {  if(dijkstra_shortest_path_tree[i].destination_id==edge_pointer->vertex_id)//ENCONTREI O SUCESSOR DAQUELE VERTICE (QUE E PROXIMA VISITA)
	        {  if(dijkstra_shortest_path_tree[i].vertex_weight>edge_pointer->edge_weight+next_visit_weight)//SE O PESO ACTUAL DESTE SUCESSOR FOR MENOR QUE O PESO DO VERTICE ORIGEM MAIS O PESO DO ARCO ENTRE O VERTICE ORIGEM E ESTE SUCESSO, ENTAO VAMOS ALTERAR O PESO DESTE VERTICE.
               {  dijkstra_shortest_path_tree[i].vertex_weight=edge_pointer->edge_weight+next_visit_weight;
                  dijkstra_shortest_path_tree[i].source_id=next_visit_destination_id;                   
               }
            }
        }
        edge_pointer=edge_pointer->next_edge;
      }
      dijkstra_shortest_path_tree[next_visit_position].vertex_visit=true;
      number_of_vertices_in_dijkstra_shortest_path_tree++;
   }
}

void Graphs::view_dijkstra_single_source_shortest_paths()
{
    for(int i= 0;i<dijkstra_shortest_path_tree.size();i++)
    {
        if(dijkstra_shortest_path_tree[i].source_id!=-1)
        {
            cout<<"SOURCE_ID: "<<dijkstra_shortest_path_tree[i].source_id<<endl;
            cout<<"DESTINATION_ID: "<<dijkstra_shortest_path_tree[i].destination_id<<endl;
            cout<<"WEIGHT: "<<dijkstra_shortest_path_tree[i].vertex_weight<<endl<<endl;
        }
    }
}

int main()
{
    Graphs g;
	g.dijkstra();
	
   //system("pause");
    return 0;
}
