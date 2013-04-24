#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <stack>
using namespace std;

enum State
{
	UN_VISITED =0,
	VISITED =1
};



class Node
{
private:
	int data;
	list<Node*> adjList;
	enum State state;
public:
	Node()
	{
	}
	
	Node(int a)
	{
		data =a;
		state = UN_VISITED;
	}

	void setVisited()
	{
		state = VISITED;
	}

	void setUnVisited()
	{
		state = UN_VISITED;
	}

	enum State getVisitedStatus()
	{
		return state;
	}

	int getdata()
	{
		return data;
	}

	int getEdgeCount()
	{
		return adjList.size();
	}

	void AddEdge(Node & child)
	{
		list<Node*>::iterator i;
		for(i=adjList.begin(); i != adjList.end(); ++i) 
		{
			if((*i)->getdata()== child.getdata())
			{
				cout<<endl<<"Edge present between "<< (*i)->getdata()<<" & "<<child.getdata();
				return;
			}
		}
		this->adjList.push_back(&child);
	}
	
	void displayEdges()
	{
		list<Node*>::iterator i;
		for(i=adjList.begin(); i != adjList.end(); ++i) 
		{
			cout<<" "<< (*i)->getdata();
		}
	}

	Node * getNthChild(int n)
	{
		list<Node*>::iterator i;
		int count = 0;
		for(i=adjList.begin(); i != adjList.end(); ++i) 
		{
			if(count == n)
				return (*i);
		

				count++;
		}
	}

};


class Graph
{
private:
	list<Node*> nodeList;
	
public:
	Node * root;

    void setAllNodesUnvisted()
	{
		list<Node*>::iterator i;
		for(i=nodeList.begin(); i != nodeList.end(); ++i) 
		{
			(*i)->setUnVisited();
		}
	}

	void AddNode(Node & node)
	{
		if(nodeList.size()>0)
		{

			list<Node*>::iterator i;
			 for(i=nodeList.begin(); i != nodeList.end(); ++i) 
			 {
				 if((*i)->getdata()== node.getdata())
				 {
					 cout<<endl<<"Node already present in the graph";
					 return;
				 }
			 }

		}
		else
		{
			root =&node;
		}
		nodeList.push_back(&node);
	}

	void AddEdge(Node &src, Node &dst)
	{
		//src and dest both should be in the graph
		list<Node*>::iterator i;
		bool srcFound = false;
		bool destFound = false;
		for(i=nodeList.begin(); i != nodeList.end(); ++i) 
		{
			if((*i)->getdata()== src.getdata())
				srcFound = true;

			if((*i)->getdata() == dst.getdata())
				destFound = true;
		}

		if(!srcFound || !destFound)
		{
			cout<<endl<< "either node not found";
			return;
		}

		src.AddEdge(dst);

	}

	void displayGraph()
	{
		if(nodeList.size()>0)
		{
			list<Node*>::iterator i;
			for(i=nodeList.begin(); i != nodeList.end(); ++i) 
			{
				cout<<endl <<"Node "<<(*i)->getdata() <<" edges";
				(*i)->displayEdges();
			}
		}
	}
};

void BFS(Graph & graph, bool isRoot, std::queue<Node*> &queuePtr)
{
	if(queuePtr.size() == 0 &&  isRoot)
	{
		cout<<endl <<"BFS display ::";
		queuePtr.push(graph.root);
	}

	if(!queuePtr.empty())
	{
		Node * ptr = queuePtr.front();
		queuePtr.pop();
		if(ptr->getVisitedStatus() == UN_VISITED)
		{
			cout<< " "<<ptr->getdata();
			ptr->setVisited();
			for(int i=0; i< ptr->getEdgeCount(); ++i)
			{
				queuePtr.push(ptr->getNthChild(i));
			}
			BFS(graph, false, queuePtr);
		}
	}

}

void DFS(Graph & graph, bool isRoot, std::stack<Node*> &stackPtr)
{
	if(stackPtr.size() == 0 &&  isRoot)
	{
		cout<<endl <<"DFS display ::";
		stackPtr.push(graph.root);
	}

	if(!stackPtr.empty())
	{
		Node * ptr = stackPtr.top();
		stackPtr.pop();
		
		if(ptr->getVisitedStatus() == UN_VISITED)
		{
			cout<< " "<<ptr->getdata();
			ptr->setVisited();
			for(int i=0; i< ptr->getEdgeCount(); ++i)
			{
				stackPtr.push(ptr->getNthChild(i));
			}
			DFS(graph, false, stackPtr);
		}
	}

}

int main()
{
	Graph graph;
	Node node1(1),node2(2),node3(3),node4(4);
	graph.AddNode(node1);
	graph.AddNode(node2);
	graph.AddNode(node3);
	graph.AddNode(node4);

	graph.AddEdge(node1, node2);
	graph.AddEdge(node1, node4);
	graph.AddEdge(node2, node3);
	graph.AddEdge(node3, node1);

	graph.displayGraph();

	//Implement BFS
	std::queue<Node*> queuePtr;
	BFS(graph, true, queuePtr);
	graph.setAllNodesUnvisted();
	std::stack<Node*> stackPtr;
	DFS(graph, true, stackPtr);
	getchar();
}