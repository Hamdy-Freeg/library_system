#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream> 

using namespace std;


struct User {

    string name;
    int id;
    vector<int> borrowerd_books_ids;
    
};

struct Book {

    int id;
    string name;
    int quantity;
    vector<int> borrower_ids;
    
};

vector<User> users_array;
vector<Book> books_array;


//---------------------------searching functions---------------------------

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




//---------------------------file handling functions---------------------------

void load_data() {
    //loading books
    ifstream books_file("data/books.csv");
    string line, token;
    if (books_file.is_open()) {
        while (getline(books_file, line)) {
            stringstream ss(line);
            Book b;
            getline(ss, token, ','); b.id = stoi(token);
            getline(ss, token, ','); b.name = token;
            getline(ss, token, ','); b.quantity = stoi(token);
            while (getline(ss, token, ',')) {
                b.borrower_ids.push_back(stoi(token));
            }
            books_array.push_back(b);
        }
        books_file.close();
    }

    //loading users
    ifstream users_file("data/users.csv");
    if (users_file.is_open()) {
        while (getline(users_file, line)) {
            stringstream ss(line);
            User u;
            getline(ss, token, ','); u.id = stoi(token);
            getline(ss, token, ','); u.name = token;
            while (getline(ss, token, ',')) {
                u.borrowerd_books_ids.push_back(stoi(token));
            }
            users_array.push_back(u);
        }
        users_file.close();
    }
}

void save_data() {

    //saving books

    ofstream books_file("data/books.csv");
    if (books_file.is_open()) {
        for (const auto& b : books_array) {
            books_file << b.id << "," << b.name << "," << b.quantity;
            for (int uid : b.borrower_ids) books_file << "," << uid;
            books_file << "\n";
        }
        books_file.close();
    } else {
        cout << "Warning: 'data' folder not found! Could not save books.csv\n";
    }

    // saving users
    ofstream users_file("data/users.csv");
    if (users_file.is_open()) {

        for (const auto& u : users_array) {

            users_file << u.id << "," << u.name;
            for (int bid : u.borrowerd_books_ids) users_file << "," << bid;
            users_file << "\n";

        }
        users_file.close();

    }
}


//---------------------------core functions---------------------------


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

    int borrowers_number = books_array[book_index].borrower_ids.size();

    for (int i =0; i < borrowers_number; ++i) {

        int current_user_id = books_array[book_index].borrower_ids[i];
        int user_idx = checking_if_user_exists(users_array, current_user_id);

        if (user_idx != -1) {

            cout << "User : " << users_array[user_idx].name << " has borrow the book\n";

        }

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

    vector<int> &borrowers_arr = books_array[book_index].borrower_ids;

    if (books_array[book_index].quantity > 0) {

        for (int i =0; i < borrowers_arr.size(); ++i) {

            if(borrowers_arr[i] == user_id) {
                cout << "you cannot borrow the same book twice \n";
                return;
            }
        }

        books_array[book_index].borrower_ids.push_back(user_id);
        books_array[book_index].quantity--;        
        users_array[user_index].borrowerd_books_ids.push_back(books_array[book_index].id);

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


    vector<int> &borrowers_arr = books_array[book_index].borrower_ids;
    vector<int> &borrowerd_books_by_user = users_array[user_index].borrowerd_books_ids;

    bool id_is_valid = false;
    bool book_name_is_valid = false;

    int erease_user_book_idx {-1};
    int erease_book_user_idx {-1};


    for (int i =0; i < borrowers_arr.size(); ++i) {

        if (user_id == borrowers_arr[i]) {

            id_is_valid = true;
            erease_user_book_idx = i;
            break;

        }
    }
    for (int i=0; i < borrowerd_books_by_user.size(); ++i) {
        if (books_array[book_index].id == borrowerd_books_by_user[i]) {

            book_name_is_valid = true;
            erease_book_user_idx = i;
            break;

        }
    }
    
    if (book_name_is_valid && id_is_valid) {

        borrowers_arr.erase(borrowers_arr.begin() + erease_user_book_idx);
        books_array[book_index].quantity++;
        borrowerd_books_by_user.erase(borrowerd_books_by_user.begin() + erease_book_user_idx);

        cout << "the book returned successfully \n";

    } else {

        cout << "This user hasn't borrow this book \n";

    }
    

}



void start() {

    load_data();
    
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
                save_data();
                running_system = false;
                break;

        }
    }
}

int main() {

    start();

    return 0;
}