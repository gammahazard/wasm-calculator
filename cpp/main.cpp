#include <iostream> 
// we need <limits> for that numeric_limits thing later to clear memory
#include <limits>   

// pulling in our own little header files.
// notice we use quotes "" for our own files and brackets <> for system files.
// this tells the compiler to look in our folder first.
#include "add.h"
#include "subtract.h"
#include "multiply.h"
#include "divide.h"

// this lets us type "cout" instead of "std::cout" every time. 
using namespace std;

// just a helper function to print text.
// keeps the main loop cleaner so we don't have 5 lines of text cluttering it.
void showMenu() {
    cout << "\n=== c++ calculator ===" << endl;
    cout << "enter an expression (e.g., 5 + 5) or 'q' to quit" << endl;
    cout << "> ";
}

// the entry point where everything starts
int main() {
    // doubles allow decimals (like 5.5), int would chop them off
    double num1, num2;
    // char holds a single character, perfect for +, -, *, /
    char op; 

    // while(true) creates an infinite loop.
    // the app will run forever until we manually break out of it.
    while (true) {
        showMenu();

        // peek() looks at the very next key press without actually "eating" it.
        // we need to check if they typed 'q' before we try to grab numbers.
        char nextChar = cin.peek();
        
        // checking for 'q' or 'Q' to exit gracefully
        if (nextChar == 'q' || nextChar == 'Q') {
            cout << "later!" << endl;
            // break instantly kills the while loop and exits the app
            break;
        }

        // this is the heavy lifter.
        // it tries to grab a number, then a symbol, then another number.
        // if the user types "hello" instead of a number, this fails and returns false.
        if (!(cin >> num1 >> op >> num2)) {
            // if we get here, the input stream is "broken" (fail state).
            cout << "bad input, gotta use numbers" << endl;
            
            // clear the error flag so cin works again
            cin.clear(); 
            // ignore everything left in the line so it doesn't read the same garbage again.
            // specifically, ignore up to the maximum possible characters until a new line.
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            
            // jump back to the start of the while loop immediately
            continue;
        }

        double result = 0;
        // this flag tracks if the math was valid.
        // usually true, but becomes false if they divide by zero or use a weird symbol.
        bool ok = true; 

        // switch is cleaner than writing 4 "if else" statements.
        // it jumps directly to the matching case based on 'op'.
        switch (op) {
            case '+':
                result = add(num1, num2);
                break; // break is needed so we don't fall through to the next case
            case '-':
                result = subtract(num1, num2);
                break;
            case '*':
                result = multiply(num1, num2);
                break;
            case '/':
                // we pass 'ok' by reference here (see divide.h).
                // if divide() sees a zero, it sets ok to false.
                result = divide(num1, num2, ok);
                if (!ok) {
                    cout << "cant divide by zero, thats illegal" << endl;
                }
                break;
            default:
                // this runs if op is something we didn't plan for, like '?' or '$'
                cout << "idk what '" << op << "' is" << endl;
                ok = false;
                break;
        }

        // only show the result if 'ok' is still true.
        // we don't want to print "result: 0" if they tried to divide by zero.
        if (ok) {
            cout << "result: " << result << endl;
        }
    }

    // return 0 tells the operating system everything finished correctly
    return 0;
}