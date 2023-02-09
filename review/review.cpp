#include "review.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;
void ReadStdIn()
{
    int val1;
    double val2;
    string val3;

    cin >> val1;
    cin >> val2;
    cin >> val3;

    cout << val1 << "\n";
    cout << val2 << "\n";
    cout << val3 << "\n";
}

int WriteOut(std::string output)
{
    cout << output;
    return 1;
}
int WriteOut(int output)
{
    cout << output;
    return 2;
}
int WriteOut(double output)
{
    cout << output;
    return 3;
}

void ReadStdIn2()
{
    std::string tmp;
    int itemsRead = 0;
    while (cin >> tmp && tmp != "q")
    {
        itemsRead++;
    }
    cout << itemsRead;
}
void ReadWrite(){
    std::vector<std::string> items;
    std::string tmp;
    while (cin >> tmp && tmp != "q"){
        items.push_back(tmp);
    }
    for(string item : items){
        cout << item << " ";
    }
    cout << "\n";

}

std::vector <int> InitializeArray(int size){
    std::vector<int> newVec;
    for(int i = 0; i < size; i++){
        newVec.push_back(0);
    }
    return newVec;
}

void LoopThrough(double *data, int size){
    for(int i = 0; i < size; i++){
        data[i] = data[i] + 1;
    }
}

int Fibonacci(int a){
    if(a == 0){ return 0; }
    if(a == 1){ return 1; }

    int lastNum1 = 1;
    int lastNum2 = 0;
    int currentNum = 1;
    
    for(int i = 1; i < a; i++){
        int tmp = lastNum1 + lastNum2;
        
        currentNum = tmp;

        lastNum2 = lastNum1;
        lastNum1 = currentNum;
    }

    return currentNum;

}

int add(int a, int b){
    return a+b;
}