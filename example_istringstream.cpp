//
// Climate++ project
// Example file:
// Using istringstream
//
#include <iostream>
#include <sstream>

using namespace std;

int main()
{
    bool more = true;

    cout << "To exit the loop, just insert 0 somewhere in the list\n\n";
    do
    {
        string input;
        cout << "Enter a list of integer: ";
        getline(cin,input);

        cout << "Your input was: ";
        int n;

        // making 'iss' an istringstream object
        istringstream iss(input);

        // reading the content of the 'iss' object
        while ( iss >> n )
        {
            cout << n << " ";
            if ( n == 0 )
                more = false;
        }
        cout << endl;
    } while ( more );

    cout << "\nBye, bye!\n";

    return 0;
}
