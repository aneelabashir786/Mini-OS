#include <cstdlib> // For system
#include <iostream>
#include <string>
using namespace std;

void listFilePermissions(const string& filename) {
    string command = "ls -l " + filename;
    system(command.c_str());
}

int main() {
    string filename;
    cout << "Enter file name: ";
    cin >> filename;

    listFilePermissions(filename);

    return 0;
}
