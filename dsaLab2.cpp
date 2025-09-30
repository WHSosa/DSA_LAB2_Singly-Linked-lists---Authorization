#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct User {
    string username;
    string password;
    vector<string> permissions;
    User* next;

    User(const string& u, const string& p, const vector<string>& perms = {"view"}) {
        username = u;
        password = p;
        permissions = perms;
        next = nullptr;
    }
};

bool insertUser(User*& head, const string& username, const string& password, const vector<string>& perms = {"view"}) {
    User* newUser = new User(username, password, perms);
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

    for (const auto& perm : user->permissions) {
        if (perm == action) return true;
    }
    return false;
}

int main() {
    User* head = nullptr;

    cout << "Inserting Users" << endl;
    insertUser(head, "alice", "password");                            // default {"view"}
    insertUser(head, "bobisgreat", "12345", {"view", "edit", "create"});
    insertUser(head, "Marie", "Marie", {"view", "edit", "create", "delete"});

    cout << "\nAuthorization tests:" << endl;
    cout << "Alice (viewer-only) trying to view: " << authorize(head, "alice", "view") << endl;
    cout << "Alice (viewer-only) trying to edit: " << authorize(head, "alice", "edit") << endl;

    cout << "Bob (editor-like) trying to create: " << authorize(head, "bobisgreat", "create") << endl;
    cout << "Bob (editor-like) trying to delete: " << authorize(head, "bobisgreat", "delete") << endl;

    cout << "Marie (full perms) trying to delete: " << authorize(head, "Marie", "delete") << endl;

    return 0;
}