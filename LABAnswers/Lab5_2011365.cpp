#include<iostream>
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<string>
#include<fstream>
#include<stack>

using namespace std;
#define MAX_VERTEX  50

#define UNDIRECTEDGRAPH 0
#define DIRECTEDGRAPH 1

#define DISPLAYGRAPH 0
#define DEPTHFIRSTTRAVERSAL 1

#define INCREASINGORDER 0
#define DECREASINGORDER 1

struct VertexType { 
    char strName[10];
    float weight;
    bool isMarked;
    VertexType *next;
    VertexType () {
        strcpy(strName, "");
        weight = 0;
        isMarked = false;
        next = NULL;
    }
};


struct GraphNode {
    VertexType vertex;
    VertexType *adjVertex;
    int indegree;
    int outdegree;
    bool isMarked;
    GraphNode () {
        indegree = 0;
        outdegree = 0;
        isMarked = false;
        adjVertex = NULL;
    }
};

struct Graph {
    int nGraphType;
    int nOperation;
    int nVertexNum;
    VertexType startVertex;
    int nOrder;
    GraphNode graph[MAX_VERTEX];
};

Graph myGraph;

void addAdjVertex(Graph &myGraph, int index, int adjIndex) {
    switch (myGraph.nOrder) {
        case INCREASINGORDER:
            if(strcmp(myGraph.graph[adjIndex].vertex.strName, myGraph.graph[index].adjVertex->strName)<0) {
                VertexType* newVertex = new VertexType();
                *newVertex = myGraph.graph[adjIndex].vertex;
                newVertex -> next = myGraph.graph[index].adjVertex;
                myGraph.graph[index].adjVertex= newVertex;
            }

            else {
                VertexType* p  = myGraph.graph[index].adjVertex;
                while(p!=NULL) {
                    char* adjName = myGraph.graph[adjIndex].vertex.strName;

                    if (strcmp(p->strName,adjName) < 0 && (p->next == NULL || strcmp(p->next->strName,adjName) > 0 ) ) {
                        
                        VertexType* newVertex = new VertexType();
                        *newVertex = myGraph.graph[adjIndex].vertex;
                        newVertex -> next = p -> next;
                        p -> next = newVertex;
                        p = newVertex;
                    }

                    p = p -> next;
                }
            }

            break;
        default:
            if(strcmp(myGraph.graph[adjIndex].vertex.strName, myGraph.graph[index].adjVertex->strName)>0) {
                VertexType* newVertex = new VertexType();
                *newVertex = myGraph.graph[adjIndex].vertex;
                newVertex -> next = myGraph.graph[index].adjVertex;
                myGraph.graph[index].adjVertex= newVertex;
            }

            else {
                VertexType* p  = myGraph.graph[index].adjVertex;
                while(p!=NULL) {
                    char* adjName = myGraph.graph[adjIndex].vertex.strName;

                    if (strcmp(p->strName,adjName) > 0 && (p->next == NULL || strcmp(p->next->strName,adjName) < 0 ) ) {
                        
                        VertexType* newVertex = new VertexType();
                        *newVertex = myGraph.graph[adjIndex].vertex;
                        newVertex -> next = p -> next;
                        p -> next = newVertex;
                        p = newVertex;
                    }

                    p = p -> next;
                }
            }
            break;
    }
}
int convertStringToInt(string input) {
    int result = 0;
    for (int i =0 ; i< input.size(); i++) {
        // Checking if the element is number
        char c = input[i];
        if (c >= '0' && c <= '9') {
            result = result * 10 + (c - '0');
        }
        // Otherwise print bad output
        else {
            cout << "Bad Input";
            return 1;
        }
    }

    return result;
}
int readFile (Graph &myGraph, char* filename) {
    ifstream input(filename);
    string inputLine[256];
    int i = 0;
    while(!input.eof()) {
        getline(input, inputLine[i]);
        i++;
    }
    int size =i;
    myGraph.nGraphType = (inputLine[0] == "0") ? 0 : 1;
    myGraph.nOperation = (inputLine[1] == "0") ? 0 : 1;
    myGraph.nVertexNum = convertStringToInt(inputLine[2]);
    
    

    myGraph.nOrder = (inputLine[5]=="1")? 1: 0;
    string* vertexName = new string[myGraph.nVertexNum];
    string getName = inputLine[3];
    i = 0;
    while(i<myGraph.nVertexNum) {
        int space = getName.find(' ');
        string name = getName.substr(0,space);
        vertexName[i]= name;
        i++;
        getName = getName.substr(space+1);
    }    

    /*STORE NAME OF VERTEX*/
    i = 0;
    while(i < myGraph.nVertexNum) {
        int k = 0;
        string nameToStore = vertexName[i];
        while(k<nameToStore.size()) {
            myGraph.graph[i].vertex.strName[k] = nameToStore[k];
            k++;
        }
        myGraph.graph[i].vertex.strName[k] = '\0';
        i++;
    }
    
    /*DEAL WITH MATRIX*/
    i = 6; 
    while(i-6<myGraph.nVertexNum) {     
    
        /*STORE ADJACENCY VERTEX*/

        string curr = inputLine[i];
        int j =0;
        int index =0;

        while(j<curr.size()) {
            if (curr[j] == '0') {
                index++;
            }

            if (curr[j] != '0' && curr[j] != ' ') {
                if(myGraph.graph[i-6].adjVertex == NULL) {
                    myGraph.graph[i-6].adjVertex = new VertexType();
                    *myGraph.graph[i-6].adjVertex = myGraph.graph[index].vertex;
                }
                else {
                    addAdjVertex(myGraph, i-6, index);
                }
                index++;
            }

            j++;
        }

        if(vertexName[i-6] == inputLine[4]) {
            myGraph.startVertex = myGraph.graph[i-6].vertex;
        }

        i++;
    }
    
    return 1;
}

void displayReverse(VertexType* p) {
    if(p!=NULL) {
    displayReverse(p->next);
    cout<<p->strName<<" ";
    }
}

void DisplayGraph (Graph &myGraph) {
    int i = 0;
    if (myGraph.nOrder == 0) {
        while(i<myGraph.nVertexNum) {
        cout<<myGraph.graph[i].vertex.strName;
        if(myGraph.graph[i].adjVertex !=NULL) {
            cout<<": ";
            VertexType* p = myGraph.graph[i].adjVertex;
            while(p != NULL) {
                cout<<p->strName<<" ";
                p = p -> next;
            }
        }
        cout<<endl;
        i++;
    }
    }

    else {
        while(i<myGraph.nVertexNum) {
        cout<<myGraph.graph[i].vertex.strName;
        if(myGraph.graph[i].adjVertex !=NULL) {
            cout<<": ";
            VertexType* p = myGraph.graph[i].adjVertex;
            displayReverse(p);
        }
        cout<<endl;
        i++;
    }
    }
    
}


int checkIfMarked(VertexType* p, Graph &myGraph) {
    int i =0;
    while(i<myGraph.nVertexNum) {
        
        if(strcmp(p->strName,myGraph.graph[i].vertex.strName) == 0) {
            if(myGraph.graph[i].isMarked) {

                return -1;
            }
            break;
        }

        i++;
    }

    return i;
}

string depthFirstTraversal (Graph &myGraph, VertexType startVertex) {
    string result = "";
    
    
        stack<GraphNode> DFtraversal;
        for (int i = 0; i<myGraph.nVertexNum; i++) {
            if(strcmp(myGraph.graph[i].vertex.strName,startVertex.strName) == 0) {
                myGraph.graph[i].isMarked = true; 
                DFtraversal.push(myGraph.graph[i]);
                result = result + myGraph.graph[i].vertex.strName + " ";
                break;
            }
        }

        while(!DFtraversal.empty()) {
            
            if (DFtraversal.top().adjVertex == NULL) {
                //result = result + DFtraversal.top().vertex.strName + " ";
                DFtraversal.pop();
                /*CHECK IF THERE IS ANY VERTEX THAT HAS NOT BEEN VISITED*/
                if(DFtraversal.empty()) {
                    //INCREASING ORDER
                    if(myGraph.nOrder == 0) {
                        bool vertexExist = false;
                        int saveIndex = -1;
                        for (int k = 0; k < myGraph.nVertexNum; k++) {
                            if(myGraph.graph[k].isMarked = false) {
                                if (!vertexExist) {
                                    saveIndex = k;
                                    vertexExist = true;
                                }
                                else {
                                    if(strcmp(myGraph.graph[k].vertex.strName, myGraph.graph[saveIndex].vertex.strName) < 0) {
                                        saveIndex = k;
                                    }
                                } 
                            }
                        }

                        if(vertexExist) {
                            DFtraversal.push(myGraph.graph[saveIndex]);
                            myGraph.graph[saveIndex].isMarked=true;
                            result = result + myGraph.graph[saveIndex].vertex.strName + " ";
                        }
                    }

                    //DECREASING ORDER
                    else {
                        bool vertexExist = false;
                        int saveIndex = -1;
                        for (int k = 0; k < myGraph.nVertexNum; k++) {
                            if(myGraph.graph[k].isMarked = false) {
                                if (!vertexExist) {
                                    saveIndex = k;
                                    vertexExist = true;
                                }
                                else {
                                    if(strcmp(myGraph.graph[k].vertex.strName, myGraph.graph[saveIndex].vertex.strName) > 0) {
                                        saveIndex = k;
                                    }
                                } 
                            }
                        }

                        if(vertexExist) {
                            DFtraversal.push(myGraph.graph[saveIndex]);
                            myGraph.graph[saveIndex].isMarked=true;
                        }
                    }
                }
            }

            else {
                bool allMarked = true;
                VertexType* p = DFtraversal.top().adjVertex;
                
                while(p!=NULL) {
                    int index = checkIfMarked(p,myGraph);
                    
                   
                    if(index!=-1) {
                        
                        DFtraversal.push(myGraph.graph[index]);
                        myGraph.graph[index].isMarked=true;
                        allMarked = false;
                        result = result + myGraph.graph[index].vertex.strName + " ";
                        break;
                    }

                    p = p -> next;
                }

                

                if(allMarked) {
                    //result = result + DFtraversal.top().vertex.strName + " ";
                    DFtraversal.pop();
                }
                
                /*Check if There is a vertex that has not been visited*/
                if(DFtraversal.empty()) {
                    //INCREASING ORDER
                    if(myGraph.nOrder == 0) {
                        bool vertexExist = false;
                        int saveIndex = -1;
                        for (int k = 0; k < myGraph.nVertexNum; k++) {
                            if(myGraph.graph[k].isMarked = false) {
                                if (!vertexExist) {
                                    saveIndex = k;
                                    vertexExist = true;
                                }
                                else {
                                    if(strcmp(myGraph.graph[k].vertex.strName, myGraph.graph[saveIndex].vertex.strName) < 0) {
                                        saveIndex = k;
                                    }
                                } 
                            }
                        }

                        if(vertexExist) {
                            DFtraversal.push(myGraph.graph[saveIndex]);
                            myGraph.graph[saveIndex].isMarked=true;
                            result = result + myGraph.graph[saveIndex].vertex.strName + " ";
                        }
                    }

                    //DECREASING ORDER
                    else {
                        bool vertexExist = false;
                        int saveIndex = -1;
                        for (int k = 0; k < myGraph.nVertexNum; k++) {
                            if(myGraph.graph[k].isMarked = false) {
                                if (!vertexExist) {
                                    saveIndex = k;
                                    vertexExist = true;
                                }
                                else {
                                    if(strcmp(myGraph.graph[k].vertex.strName, myGraph.graph[saveIndex].vertex.strName) > 0) {
                                        saveIndex = k;
                                    }
                                } 
                            }
                        }

                        if(vertexExist) {
                            DFtraversal.push(myGraph.graph[saveIndex]);
                            myGraph.graph[saveIndex].isMarked=true;
                        }
                    }
                }
                /*--------------------------------------*/
            }            
        }
    
    return result;
}

int main () {
    for (int i = 0; i<MAX_VERTEX; i++) {
        strcpy(myGraph.graph[i].vertex.strName, "-1");
    }
    
    readFile(myGraph,"input.txt");
    
    
    switch(myGraph.nOperation) {
        case DISPLAYGRAPH:
            cout<<"Display Graph"<<endl;
            DisplayGraph(myGraph);
            cout<<"-----------------------------"<<endl;
            break;
        case DEPTHFIRSTTRAVERSAL:
            cout<<"Depth First Traversal"<<endl;
            cout<<depthFirstTraversal(myGraph, myGraph.startVertex)<<endl;
            cout<<"-----------------------------"<<endl;
            break;
    }

    return 0;
}