#include <iostream>
#include <cstdlib>
#include <ctime>
#include<unistd.h>
using namespace std;

const int MAX_TRIES = 5;

int main() {
abc:
    srand(time(NULL));

    // Generate a random number between 1 and 100
    int secretNumber = rand() % 100 + 1;

    // Initialize the game state
    int tries = 0;
    int guess;
    bool gameOver = false;

    // Print the welcome message
    cout << "Welcome to the number guessing game!" << endl;
    cout << "I'm thinking of a number between 1 and 100. You have " << MAX_TRIES << " tries to guess it." << endl;

    // Game loop
    while (!gameOver) {
        // Get a guess from the user
        cout << "Guess #" << tries + 1 << ": ";
        cin >> guess;

        // Check if the guess is correct
        if (guess == secretNumber) {
            cout << "Congratulations! You guessed the number in " << tries + 1 << " tries." << endl;
            gameOver = true;
        }
        // Check if the guess is too high
        else if (guess > secretNumber) {
            cout << "Too high." << endl;
        }
        // Check if the guess is too low
        else {
            cout << "Too low." << endl;
        }

        // Check if the player has used up all their tries
        tries++;
        if (tries == MAX_TRIES) {
            cout << "Sorry, you're out of tries. The number was " << secretNumber << "." << endl;
            gameOver = true;
        }
    }
    int a;
    // Print the goodbye message
    cout << "Thanks for playing!" << endl;
    cout<<"Press 1: for Play Again:"<<endl;
    cout<<"Press 2: for Go Back:"<<endl;
    cin>>a;
    if(a==1)
    {
      system("clear");
      goto abc;
    }
    else
    {
          system("gnome-terminal -- bash -c './games; exec bash'");   
    }
    return 0;
}
