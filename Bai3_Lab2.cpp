#include<iostream>
#include<stack>
using namespace std;



void RemoveN (stack<int> &s, int N) {
    int size = 0;
    stack<int> temp;
    while(!s.empty()) {
        temp.push(s.top());
        s.pop();
        size+=1;
    }

    if(N>size) {
        return;
    }

    int index = 1;

    while(!temp.empty()) {
        if(N!=index) {
            s.push(temp.top());
        }
        temp.pop();
        index++;
    }
}



void print(stack<int> s) {
    stack <int> temp;
    while(!s.empty()) {
        temp.push(s.top());
        s.pop();
    }

    while(!temp.empty()) {
        cout<<temp.top()<<" ";
        temp.pop();
    }


}

int main() {
    stack <int> s;

    int i = 1;
    while(i!=7) {
        s.push(i);
        i++;
    }

    RemoveN(s,6);

    print(s);

}