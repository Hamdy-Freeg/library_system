#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream> 

using namespace std;

struct Book;
struct User;

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
            books_array.insert(books_array.begin() + i, book);
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

    if (index != -1) {
        cout << "this user is already exists try again with different id ";
        return ;
    }

    bool is_inserted = false;

    for (int i =0; i < users_array.size(); ++i) {
        if (user.id < users_array[i].id) {
            users_array.insert(users_array.begin() + i, user);
            is_inserted = true;
            break;
        }
    }

    if(!is_inserted) {
        users_array.push_back(user);
    }

}


void search_by_prefix() {

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


void print_users_by_book() {

    cout << "please enter book name : ";
    string book_name;
    cin >> book_name;
    cout << "\n";


    int book_index = checking_if_book_exists(books_array, book_name);

    if(book_index == -1) {
        cout << "There are no books with this name \n";
        return;
    }

    int borrowers_number = books_array[book_index].borrower.size();

    for (int i =0; i < borrowers_number; ++i) {
        cout << "User : " << books_array[book_index].borrower[i].name << " has borrow the book";
    }

}


void print_library_by_id() {

    if (books_array.empty()) {
        cout << "there are no books to print \n";
        return;
    }

    for (int i =0; i < books_array.size(); ++i) {
        cout << "ID :" << books_array[i].id << " Name : " << books_array[i].name << " \n";
        cout << "------------------------------- \n";
    }


}

void print_library_by_name() {

    if (books_array.empty()) {
        cout << "there are no books to print \n";
        return;
    }

    for (int i =0; i < books_array.size(); ++i) {
        cout << "Name :" << books_array[i].name << " ID : " << books_array[i].id << " \n";
        cout << "------------------------------- \n";
    }
}


void user_borrow_book() {
    cout << "please enter user id and book name:";
    int user_id;
    string book_name;
    cin >> user_id >> book_name ;
    cout << "\n";

    int user_index = checking_if_user_exists(users_array, user_id);
    int book_index = checking_if_book_exists(books_array, book_name);


    if(user_index == -1 ) {
        cout << "There is no user with this id, please create new user first \n";
        return;
    }
    if(book_index == -1) {
        cout << "There is no book with this name please check your inventory \n";
        return;
    }

    vector<User> &borrowers_arr = books_array[book_index].borrower;

    if (books_array[book_index].quantity > 0) {
        for (int i =0; i < borrowers_arr.size(); ++i) {
            if(borrowers_arr[i].id == users_array[user_index].id) {
                cout << "you cannot borrow the same book twice \n";
                return;
            }
        }
        books_array[book_index].borrower.push_back(users_array[user_index]);
        books_array[book_index].quantity--;        
        users_array[user_index].borrowerd_books.push_back(books_array[book_index]);
        cout << "the book borrowed successfully";
    } else {
        cout << "this book is not available right now ): \n";
    }
}



void user_return_book() {

    cout << "please enter user id and book name:";
    int user_id;
    string book_name;
    cin >> user_id >> book_name ;
    cout << "\n";

    int user_index = checking_if_user_exists(users_array, user_id);
    int book_index = checking_if_book_exists(books_array, book_name);

    if(user_index == -1 ) {
        cout << "There is no user with this id\n";
        return;
    }

    if(book_index == -1) {
        cout << "There is no book with this name please check your inventory \n";
        return;
    }


    vector<User> &borrowers_arr = books_array[book_index].borrower;

    vector<Book> &borrowered_books_by_user = users_array[user_index].borrowerd_books;

    bool id_is_valid = false;
    bool book_name_is_valid = false;

    int erease_user_book_idx {-1};
    int erease_book_user_idx {-1};


    for (int i =0; i < borrowers_arr.size(); ++i) {
        if (user_id == borrowers_arr[i].id) {

            id_is_valid = true;
            erease_user_book_idx = i;
            break;
        }
    }
    for (int i=0; i < borrowered_books_by_user.size(); ++i) {
        if (book_name == borrowered_books_by_user[i].name) {

            book_name_is_valid = true;
            erease_book_user_idx = i;
            break;

        }
    }
    
    if (book_name_is_valid && id_is_valid) {

        borrowers_arr.erase(borrowers_arr.begin() + erease_user_book_idx);
        books_array[book_index].quantity++;
        borrowered_books_by_user.erase(borrowered_books_by_user.begin() + erease_book_user_idx);
        cout << "the book returned successfully \n";
    } else {
        cout << "This user hasn't borrow this book \n";
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

        switch (choise) {
            case 1 :
                add_book();
                break;
            case 2 :
                add_user();
                break;
            case 3 :
                search_by_prefix();
                break;
            case 4 :
                print_users_by_book();
                break;
            case 5 :
                print_library_by_id();
                break;
            case 6 :
                print_library_by_name();
                break;
            case 7 :
                user_borrow_book();
                break;
            case 8 :
                user_return_book();
                break;
            case 9 :
                running_system = false;
                break;

        }
    }
}

int main() {

    start();

    return 0;
}