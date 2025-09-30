#include <iostream>
#include <string>
using namespace std;

struct User {
    string username;
    string password;
    string role;   // "admin", "editor", "viewer"
    User* next;

    User(const string& u, const string& p, const string& r = "viewer") {
        username = u;
        password = p;
        role = r;
        next = nullptr;
    }
};

bool insertUser(User*& head, const string& username, const string& password, const string& role = "viewer") {
    User* newUser = new User(username, password, role);
    newUser->next = head;
    head = newUser;
    return true;
}

User* findUser(User* head, const string& username) {
    while (head != nullptr) {
        if (head->username == username) return head;
        head = head->next;
    }
    return nullptr;
}

bool authorize(User* head, const string& username, const string& action) {
    User* user = findUser(head, username);
    if (!user) return false;

    if (user->role == "admin") {
        return true;
    } else if (user->role == "editor") {
        return (action == "view" || action == "edit" || action == "create");
    } else if (user->role == "viewer") {
        return (action == "view");
    }
    return false; // invalid role
}

int main() {
    User* head = nullptr;

    cout << "Inserting Users" << endl;
    insertUser(head, "alice", "password");                 // default role: viewer
    insertUser(head, "bobisgreat", "12345", "editor");
    insertUser(head, "Marie", "Marie", "admin");

    cout << "\nAuthorization tests:" << endl;
    cout << "Alice (viewer) trying to view: " << authorize(head, "alice", "view") << endl;
    cout << "Alice (viewer) trying to edit: " << authorize(head, "alice", "edit") << endl;

    cout << "Bob (editor) trying to create: " << authorize(head, "bobisgreat", "create") << endl;
    cout << "Bob (editor) trying to delete: " << authorize(head, "bobisgreat", "delete") << endl;

    cout << "Marie (admin) trying to delete: " << authorize(head, "Marie", "delete") << endl;

    return 0;
}