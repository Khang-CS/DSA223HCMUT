#include<iostream>
#include<stack>
using namespace std;

struct node {
    int data;
    node* next = NULL;
};

class Stack {
    private:
    node* top;
    int maxSize = 0;
    int size = 0;
    

    public:
    Stack() {
        Creates();
    }

    Stack(int maxSize) {
        Creates(maxSize);
    }

    ~Stack() {
        Clear();
    }
    bool isEmpty() {
        if(size == 0) {
            return true;
        }

        return false;
    }

    bool isFull() {
        if(size == maxSize) {
            return true;
        }
        return false;
    }

    void Clear() {
        node* p = top;
        while(p!=NULL) {
            node* del = p;
            p = p -> next;
            delete del;
        }
        top = NULL;
        size =0;
    }

    int Size() {
        return size;
    }

    void Creates() {
        top = NULL;
        size = 0;
        maxSize = 100;
    }

    void Creates(int size) {
        top = NULL;
        this -> maxSize = size;
        size = 0;
    }

    void Push(int data) {
        if(this->isFull()) {
            cout<<"Stack is full !"<<endl;
            return;
        }
        node* newNode = new node;
        newNode -> data = data;
        if(top == NULL) {
            top = newNode;
        }

        else {
            newNode -> next = top;
            top = newNode;
        }

        size +=1;

    }

    void Pop() {
        if(isEmpty()) {
            cout<<"Stack is empty !"<<endl;
            return; 
        }
        node* pop = top;
        top = top -> next;
        pop -> next = NULL;
        delete pop;
        size-=1;
    }

    int Top() {
        return top ->data;       
    }
};

int main() {
    Stack p;
    int i =0;
    while(i!=8) {
        p.Push(i);
        i++;
    }

    cout<<p.Size()<<endl;

    cout<<p.Top()<<endl;

    p.Pop();

    cout<<p.Top()<<" "<<p.Size();
}