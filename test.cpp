#include<iostream>
using namespace std;

int main() {
    int p = 10;
    int &q = p;
    q = 6;
    cout<<p;
}