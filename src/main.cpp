#include <iostream>
#include <vector>
#include <string>

using namespace std ;

struct User {
    string name;
    int id;

};

struct Book {
    int id;
    string name;
    int quantity;
    

};


void start() {
    bool running_system = true;

    while (running_system) {
        int choise;

        cout << "1) Add Book \n";
        cout << "2) Add user \n";
        cout << "3) Search on books by prefix \n";
        cout << "4) Print who borrow book by name \n";
        cout << "5) Print library by id \n";
        cout << "6) Print library by name\n";
        cout << "7) users who borrow spicific book \n";
        cout << "8) user return book \n";
        cout << "9) Exit \n";

        cin >> choise;
/* 
        switch (choise) {
            case 1 :
                
                break;
            case 2 :
                break;
            case 3 :
                break;
            case 4 :
                break;
            case 5 :
                break;
            case 6 :
                break;
            case 7 :
                break;
            case 8 :
                break;
            case 9 :
                running_system = false;
                break;

        }
 */

    }
}

int main() {



    return 0;
}