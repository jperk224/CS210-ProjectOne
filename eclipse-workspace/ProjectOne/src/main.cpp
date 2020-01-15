/*
 * Jeff Perkinson
 * CS-210 J3528
 * January 2020
 *
 * Create two clocks for ChadaTech that display simultaneously
 * using ISO 8601 standards and allow for user input
 */

// C++ Library inclusions
#include <iostream>             // Library needed for cin and cout objects
#include <iomanip>              // Library needed for output manipulation
                                // e.g. setprecision
                                // http://www.cplusplus.com/reference/ctime/
#include <string>               // Library needed to allow use of string type
#include <vector>               // Library needed to allow use of vector type

// User-defined file inclusions
#include "clockFunctions.h"     // Header housing the function definitions for
                                // the functions defined in printFunctions.cpp
                                // used to display output

using namespace std;

// The individual functions called by main() are defined within
// PrintFunctions.cpp in lieu of simple declarations/stubs above main()
// with definitions below main()
// This approach was chosen for ease of maintenance/portability
// If future versions of this program require a change to the function
// name or parameters, setting the stubs above main() creates an additional
// place in the code in which they must be modified that may be overlooked

int main () {

	// Program global variables
	    // Best practice is to only use constants
	    // when declaring global variables to avoid
	    // unintended side effects
	    // All other variables should be declared within
	    // the appropriate functions to limit their scope

	    // Menu Options String Array
	    const vector<string> MENU_OPTIONS = { "Add One Hour", "Add One Minute",
	                                        "Add One Second", "Exit Program"};
	    const int BOX_WIDTH = 26;

	// FIXME: Display current time
	displayClocks(BOX_WIDTH, currentTime());

	// Display the options menu
	int userVal = displayMenu(MENU_OPTIONS, BOX_WIDTH);
	// FIXME: somehow this display need to be wrapped in a time that clears
	// the screen if no selection is made?

	// continue looping through the program until the user opts to quit
	// a while loop is used here instead of a for loop because the number
	// of iterations is unknown at the onset of loop entry
	while (userVal != 4) {
		// use a switch statement for easier readability than multiple if-else
		// this is likely the most manually intensive portion of the program
		// to maintain; as options are add to/removed from the MENU_OPTIONS
		// vector, those cases will need to be manually added to this switch
		switch (userVal) {
		case 1:
			cout
					<< "FIXME: Add one hour; wait; then clear screen; then display current time again.";
			cout << endl << endl;
			break;
		case 2:
			cout
					<< "FIXME: Add one minute; wait; then clear screen; then display current time again.";
			cout << endl << endl;
			break;
		case 3:
			cout
					<< "FIXME: Add one second; then clear screen; then display current time again.";
			cout << endl << endl;
			break;
		default: 				// catch an exit selection, do nothing and proceed to end the program
			break; 				// no other entry should hit this default due to the exception
		}                   	// handling built into displayMenu()
		userVal = displayMenu(MENU_OPTIONS, BOX_WIDTH);
	}

	cout << "End Program.";

	return 0;
}
