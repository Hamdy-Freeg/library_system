#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;



struct User {
    string name;
    int id;
    vector<Book> borrowerd_books;
    
};

struct Book {
    int id;
    string name;
    int quantity;
    vector<User> borrower;
    
};


vector<User> users_array;
vector<Book> books_array;


//binary search method for adding books and other functionalities

int checking_if_book_exists(const vector<Book> &books, string target) {
    int low =0;
    int high = books.size() -1;

    while(low <= high) {
        int mid = low + (high-low)/2;

        if (books[mid].name == target) {
            return mid;
        }

        if (books[mid].name < target) {
            low = mid +1;
        } else {
            high = mid  - 1;
        }
    }

    return -1;
}


// repeated my self hahaha :) 

int checking_if_user_exists(const vector<User> &users, int target_id) {
    int low =0;
    int high = users.size() -1;

    while(low <= high) {
        int mid = low + (high-low)/2;

        if (users[mid].id == target_id) {
            return mid;
        }

        if (users[mid].id < target_id) {
            low = mid +1;
        } else {
            high = mid -1;
        }
    }
    return -1;
}


void add_book() {

    Book book;
    cout << "Please enter book id, name and quantity : ";
    cin >> book.id >> book.name >> book.quantity;
    cout << "\n";

    // cheking if the book is the first one then add it directly

    if (books_array.empty()) {
        books_array.push_back(book);
        return;
    }

    // checking if the book already added to the array, then let it and increase its quantitiy

    int index = checking_if_book_exists(books_array, book.name);

    if (index != -1) {
        books_array[index].quantity += book.quantity;
        return ;
    }
    

    // insert the book by order (alphabitc)

    bool is_inserted = false;

    for (int i =0; i < books_array.size(); ++i) {
        if ( book.name < books_array[i].name ) {
            books_array.insert(books_array.begin() +1, book);
            is_inserted =true;
            break;
        }
    }

    if(!is_inserted) {
        books_array.push_back(book);
    }

}




void add_user() {
    // add users by sorting them by id to inhance speed of cheking 

    User user;
    cout << "Please enter user name and id : ";
    cin >> user.name >> user.id;
    cout << "\n";

    if (users_array.empty()) {
        users_array.push_back(user);
    }

    int index = checking_if_user_exists(users_array, user.id);

    if (index == -1) {
        cout << "this user is already exists try again with different id ";
        return ;
    }

    bool is_inserted = false;

    for (int i =0; i < users_array.size(); ++i) {
        if (user.id < users_array[i].id) {
            users_array.insert(users_array.begin() + 1, user);
            is_inserted = true;
            break;
        }
    }

    if(!is_inserted) {
        users_array.push_back(user);
    }

}


void search_books_by_prefix() {

    cout << "please enter a prefix of the book \n";
    string prefix;
    cin >> prefix;

    // itrate on books using binary search to get the starting point

    auto it = lower_bound(books_array.begin(), books_array.end(), prefix, [](const Book &book, const string& p) {
            return book.name < p; 
        });

    bool found = false;


    // print all books starts with our prefix

    while(it != books_array.end() && it->name.find(prefix) == 0) {
        cout << "Found: " << it->name << "( ID: " << it->id << " Quantity: " << it->quantity << ")\n";
        it++;
        found = true;
    }

    if (!found) {
        cout << "No books found starting with '" << prefix << "'\n";
    }

}





void start() {
    bool running_system = true;

    while (running_system) {
        int choise;

        cout << "1) Add Book \n";
        cout << "2) Add user \n";
        cout << "3) Search on books by prefix \n";
        cout << "4) users who borrow spicific book \n";
        cout << "5) Print library by id \n";
        cout << "6) Print library by name\n";
        cout << "7) user borrow book \n";
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