#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * The while loop represents the game.
 * Each iteration represents a turn of the game
 * where you are given inputs (the heights of the mountains)
 * and where you have to print an output (the index of the mountain to fire on)
 * The inputs you are given are automatically updated according to your last actions.
 **/

int main()
{

    int mountainH; // represents the height of one mountain.
    // game loop
    while (1) {
        for (int i = 0; i < 8; i++) {
            cin >> mountainH;
            cin.ignore();
            cerr << mountainH << endl;
            cout << mountainH << endl;
            cerr << "First shot " << mountainH << endl;
        }

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;

        cout << mountainH << endl;
        cerr << "First shot " << mountainH << endl;


    }
}
