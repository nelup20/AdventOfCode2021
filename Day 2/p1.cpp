#include <iostream>
#include <fstream>

using namespace std;

int main(){
    ifstream file("../input.txt");

    string direction;
    int amount;
    int x = 0;
    int y = 0;

    while(file >> direction >> amount){
        if(direction == "forward") x += amount;
        if(direction == "down") y += amount;
        if(direction == "up") y -= amount;
    }

    cout << x * y;
}
