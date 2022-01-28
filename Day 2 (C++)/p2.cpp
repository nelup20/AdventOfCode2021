#include <iostream>
#include <fstream>

using namespace std;

int main(){
    ifstream file("../input.txt");

    string direction;
    int amount;
    int x = 0;
    int y = 0;
    int aim = 0;

    while(file >> direction >> amount){
        if(direction == "down") aim += amount;
        if(direction == "up") aim -= amount;

        if(direction == "forward"){
            x += amount;
            y += (aim * amount);
        }
    }

    cout << x * y;
}
