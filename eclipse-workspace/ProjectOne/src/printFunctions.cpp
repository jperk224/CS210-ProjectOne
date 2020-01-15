/*
 * Jeff Perkinson
 * CS-210 J3528
 * January 2020
 *
 * Create two clocks for ChadaTech that display simultaneously
 * using ISO 8601 standards and allow for user input
 */

#include <iostream>             // Library needed for cin and cout objects
#include <ctime>                // Library needed to get and manipulate
                                // date and time information
#include <string>               // Library needed to allow use of string type
#include <vector>               // Library needed to allow use of vector type
#include <stdlib.h>             // Library needed for itoa function to convert int to string
#include <stdexcept>            // Library needed for the runtime_error object to be
                                // thrown/caught in exception handling cases

using namespace std;

// Function to return current time
// The return value should be passed into
// the functions that display current time,
// add one second, or add one hour
/**************************************
 * currentTime() --> return the current
 * time
 *************************************/
time_t currentTime() {                  // time_t is a C++ arithmetic type from
    return time(NULL);                  // the ctime library capable of representing time
}                                       // (http://www.cplusplus.com/reference/ctime/time_t/)
                                        // The arithmetic capability will allow it to be used
                                        // in expressions to display the current time or
                                        // manipulated time (i.e. add one second, add
                                        // one hour) as addressed in the requirements

/**************************************
 * displayClock24() --> Display
 * time in the 24-hour format not
 * to exceed 23:59:59
 *************************************/
string displayClock24(time_t time) {                    // Parameter is of type time_t to allow
                                                        // manipulated time to be passed in (e.g. time + 1 second)
    string timeAsString = asctime(localtime(&time));    // localtime converts time_t argument (e.g. given time since
                                                        // epoch (1/1/1970)) into calendar time, expressed in
                                                        // local time (https://en.cppreference.com/w/cpp/chrono/c/localtime)
                                                        // Argument to localtime must be a pointer to a
                                                        // time_t object, this is why the function's time parameter
                                                        // is passed by reference into localtime()
                                                        // asctime converts calendar time argument (e.g.
                                                        // localtime(&time)) into a string representing the
                                                        // calendar time argument

    // asctime() returns a fixed 25-character string formatted in a fixed way
    // (e.g. 3-letter day, 3-letter month, 2-digit day of month, 2-digit hour, etc.)
    // (https://en.cppreference.com/w/cpp/chrono/c/asctime)
    // Allowing the use of substr() to extract the time
    // The timestamp starts at index 11 and is 8 characters in length
    string timeStamp = timeAsString.substr(11,8);

    return timeStamp;
}

/**************************************
 * displayClock12() --> Display
 * time in the 12-hour format not
 * to exceed 12:59:59
 *************************************/
// This function derives a string format of the time parameter
// in the same fashion as displayClock24(), but carries additional logic
// to convert the output to 12-hour time
// Only comments related to that logic are discussed within this function
// For comments pertaining to the arrival at the string representation
// of the time parameter, see displayClock24() above.
string displayClock12(time_t time) {
    string timeAsString = asctime(localtime(&time));
    string timeStamp = timeAsString.substr(11,8);

    // Use a switch statement to convert the hour where necessary
    // and append time with AM/PM
    // With the expected number of cases, a switch statement here is cleaner
    // that a multiple if-else-if-else branch construct

    string timeStampHour = timeStamp.substr(0,2);       // Capture the hour from timeStamp
    int timeStampHourAsInt = stoi(timeStampHour);       // std::stoi converts a string to int
                                                        // to use for the switch statement
                                                        // (https://www.techiedelight.com/convert-string-to-int-cpp/)
    switch(timeStampHourAsInt) {
        case 0:
            timeStamp.replace(0,2,"12");
            timeStamp.append(" AM");
            break;
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
            timeStamp.append(" AM");
            break;
        case 12:
            timeStamp.append(" PM");
            break;
        case 13:
            timeStamp.replace(0,2,"01");
            timeStamp.append(" PM");
            break;
        case 14:
            timeStamp.replace(0,2,"02");
            timeStamp.append(" PM");
            break;
        case 15:
            timeStamp.replace(0,2,"03");
            timeStamp.append(" PM");
            break;
        case 16:
            timeStamp.replace(0,2,"04");
            timeStamp.append(" PM");
            break;
        case 17:
            timeStamp.replace(0,2,"05");
            timeStamp.append(" PM");
            break;
        case 18:
            timeStamp.replace(0,2,"06");
            timeStamp.append(" PM");
            break;
        case 19:
            timeStamp.replace(0,2,"07");
            timeStamp.append(" PM");
            break;
        case 20:
            timeStamp.replace(0,2,"08");
            timeStamp.append(" PM");
            break;
        case 21:
            timeStamp.replace(0,2,"09");
            timeStamp.append(" PM");
            break;
        case 22:
            timeStamp.replace(0,2,"10");
            timeStamp.append(" PM");
            break;
        case 23:
            timeStamp.replace(0,2,"11");
            timeStamp.append(" PM");
            break;
        default:
            break;
    }

    return timeStamp;
}

/**************************************
 * displayHorizontalBorder() -->
 * Display the horizontal borders for the
 * clock and menu.  Moved to separate function
 * to avoid repetitive code and to easily
 * change border ASCII character
 *************************************/
void displayHorizontalBorder(int length) {
    const char BORDER_CHAR = '*';       // this is defined in the function
                                        // to limit the number of arguments needed
                                        // this program does not have a need to
                                        // output borders of different ASCII characters

    for (int i = 0; i < length; ++i) {
        cout << BORDER_CHAR;
    }

    return;                             // even with no return type, best practice
}                                       // is to include a return statement to
                                        // clear the stack frame

/**************************************
 * displayMarquee() --> Display given
 * text inside a border
 * Placed as a separate function
 * to avoid repetitive
 * code and ease of adaptation
 *************************************/
void displayMarquee(string displayString, int spanLength, bool isCentered=true) {   // spanLength is desired length of horizontal span                                         // marquee and white space (i.e. the
                                                                                    // (e.g. entire line in the box.)

    const int LEADING_WHITE_SPACE = 1;      // Space between border character and element display
                                            // use if isCentered is false
    const char BORDER_CHAR = '*';
    const int SIDE_CHAR_COUNT = 1;          // Utilizes 1 character per side per the spec
                                            // and assumes equal characters per side
    int innerWhiteSpace;                    // holds length of inner whitespace; varies by branch
    int leftWhiteSpace;                     // holds length of left whitespace; used in centered branch
    int rightWhiteSpace;                    // holds length of right whitespace; used in centered branch

    // function parameters drive loop iterations
    // this approach makes maintenance/adjustment
    // easier as loops/output can be scaled by changing the
    // arguments to the function call

    // display leading border character(s)
    for (int i = 0; i < SIDE_CHAR_COUNT; ++i) {
        cout << BORDER_CHAR;
    }

    // display marquee
    if(!isCentered) {
        // display leading whitespace
        for (int i = 0; i < LEADING_WHITE_SPACE; ++i) {
            cout << " ";
        }

        cout << displayString;

        // determine length of remaining white space to output
        innerWhiteSpace =    spanLength - (SIDE_CHAR_COUNT * 2)
                            - LEADING_WHITE_SPACE - displayString.size();

        // display trailing whitespace
        for (int i = 0; i < innerWhiteSpace; ++i) {
            cout << " ";
        }
    }
    else {                              // centered (i.e. if(isCentered))
        // Because the marquee is centered, there's no LEADING_WHITE_SPACE
        // to factor into the innerWhiteSpace calculation
        innerWhiteSpace = spanLength - (SIDE_CHAR_COUNT * 2) - displayString.size();
        // split per-side white space into two separate variables
        // to account for potential truncation from int division
        // while this may result in each side's white space not being equivalent
        // (e.g. one side > other due to truncation) it ensures
        // white space will not extend beyond spanLength
        leftWhiteSpace = innerWhiteSpace / 2;
        rightWhiteSpace = innerWhiteSpace - leftWhiteSpace;

        // display marquee output
        // display left side white space
        for (int i = 0; i < leftWhiteSpace; ++i) {
            cout << " ";
        }

        cout << displayString;

        // display left side white space
        for (int i = 0; i < rightWhiteSpace; ++i) {
            cout << " ";
        }
    }

    // display trailing border character(s)
    for (int i = 0; i < SIDE_CHAR_COUNT; ++i) {
        cout << BORDER_CHAR;
    }

    return;
}

/**************************************
 * displayMarqueeWithCount() -->
 * Display given text inside a border
 * Placed as a separate function
 * to avoid repetitive
 * code and ease of adaptation
 * displayMarquee was split into 2 functions
 * to limit the number of parameters needed,
 * as good practice suggests to not go
 * beyond 3-4 parameters for a given function
 * https://softwareengineering.stackexchange.com/questions/145055/are-there-guidelines-on-how-many-parameters-a-function-should-accept
 *************************************/

void displayMarqueeWithCount(string displayString, int spanLength,      // isCentered defaults to false to support
                            int identifier, bool isCentered=false) {    // the spec output for the options menu
    // spanLength is desired length of horizontal span marquee and white space
    // (i.e. the entire line in the box.)
    // numberIdentifier is used to hold the 'count' or 'identifier'
    // to display if showCount is true
    const string SPACE_BETWEEN = " ";                                    // To adjust space between identifier and displayString
    const char MARQUEE_CHAR = '-';

    // using to_string() to convert the index count to a string causes an error
    // that appears to be a compiler bug?  With the best solution being to
    // downgrade the compiler.
    // https://stackoverflow.com/questions/43294488/mingw-g-multiple-definition-of-vsnprintf-when-using-to-string
    // So instead I converted the index count to a string
    // using itoa from stdlib
    // http://www.cplusplus.com/reference/cstdlib/itoa/
    char buffer [10];
    string identifierString;
    identifierString = itoa((identifier), buffer, 10);

    // build the marquee argument to pass to displayMarquee()
    const string marqueeOutput  = identifierString + SPACE_BETWEEN + MARQUEE_CHAR
                                + SPACE_BETWEEN + displayString;

    if (isCentered) {
        displayMarquee(marqueeOutput, spanLength, true);
    }
    else {
        displayMarquee(marqueeOutput, spanLength, false);
    }

    return;
}

/**************************************
 displayClocks() --> Display 12 and 24
 hour clocks simultaneously
 *************************************/
void displayClocks(int boxWidth, time_t timeToDisplay) {
    // boxWidth serves as spanLength argument for displayMarquee()
    // timeToDisplay is an arithmetic time_t argument (see currentTime()
    // function definition above for further detail)
    // the display will be built by loops whose iteration counts are derived
    // from the constants and parameters, easing future maintainability
    // boxWidth represents the width of a box housing one clock, output should
    // be two boxes overall

    const int BOX_GAP = 6;          // Vertical whitespace between each clock box
    const string CLOCK12_TITLE = "12-Hour Clock";
    const string CLOCK24_TITLE = "24-Hour Clock";
    const string CLOCK12 = displayClock12(timeToDisplay);
    const string CLOCK24 = displayClock24(timeToDisplay);
    // concatenate string variables to build arguments
    // to pass into displayMarquee() to print the clocks
    // simultaneously per the specification
    string boxGap = "";                         // start with an empty string and
    for (int i = 0; i < BOX_GAP; ++i) {         // loop BOX_GAP times to add an empty
        boxGap += " ";                          // space; the end result should be
    }                                           // utilized in the overall display output
                                                // this approach is taken
                                                // because C++ does not all string multiplication
                                                // https://stackoverflow.com/questions/11843226/multiplying-a-string-by-an-int-in-c/11844806

    // build vectors to loop through to pull elements
    // to pass into simultaneous displayMarquee() calls
    // to display both the 12 and 24 hour clocks per the specification

    // these vectors must be the same length for the display loop to
    // I first tried using a const int (e.g. const int VECTOR_SIZE)
    // to determine the length to enforce this and the populate the
    // vectors via vector::push_back
    // and provide a loop counter to control calls to displayMarquee
    // I could not get it to work or successfully debug, so I instead opted
    // to use vector initialization
    const vector<string> CLOCK12_VECTOR = {CLOCK12_TITLE, CLOCK12};
    const vector<string> CLOCK24_VECTOR = {CLOCK24_TITLE, CLOCK24};

    // Display top horizontal borders
    displayHorizontalBorder(boxWidth);

    for (int i = 0; i < BOX_GAP; ++i) {
        cout << " ";
    }
    displayHorizontalBorder(boxWidth);
    cout << endl;

    // Display actual clocks
    for (int i = 0; i < 2; ++i) {
        displayMarquee(CLOCK12_VECTOR.at(i), boxWidth, true);
        cout << boxGap;
        displayMarquee(CLOCK24_VECTOR.at(i), boxWidth, true);
        cout << endl;
    }

    // Display bottom horizontal borders
    displayHorizontalBorder(boxWidth);
    for (int i = 0; i < BOX_GAP; ++i) {
        cout << " ";
    }
    displayHorizontalBorder(boxWidth);
    cout << endl;

    return;
}

// Function to display the menu and capture user selection
// The function will return an int representing the user's selection
// Exception handling ensures valid output is captured and returned
/**************************************
 * displayMenu() --> Display the
 * options menu for the user to make
 * their selection and return the
 * selection made
 *************************************/
// pass in a vector used in main to store the menu options
// looping through the vector to display the menu makes
// future maintenance simpler via adding or removing
// vector elements
int displayMenu(vector<string> menuOptions, int boxWidth) {
    // boxWidth serves as spanLength argument for displayMarqueeWithCount()

    bool validEntry;            // flag to drive exception handling
    string userEntryAsString;   // store user input to conver to int
    int userEntry;              // store user input as int to return

    // exception handling to validate user selection

    do {                    // a do-while loop is used because the menu should
                            // be displayed at least once and assume the user
                            // makes a valid selection
                            // don't initiate a loop until an exception is thrown
        validEntry = true;  // set to true, assume selection will be valid
        try {
            // Display top horizontal border
            displayHorizontalBorder(boxWidth);
            cout << endl;

            for (int i = 0; i < menuOptions.size(); ++i) {
            displayMarqueeWithCount(menuOptions.at(i), boxWidth, (i + 1), false);
            cout << endl;
            }

            // Display bottom horizontal border
            displayHorizontalBorder(boxWidth);
            cout << endl;

            cin >> userEntryAsString;

            userEntry = stoi(userEntryAsString);        // std::stoi is one of the most
                                                        // common ways to convert a string to int
                                                        // http://www.cplusplus.com/reference/string/stoi/
            // Ensuring valid int
            if ((userEntry < 1) || (userEntry > menuOptions.size())) {
                // using to_string() to convert the index count to a string causes an error
                // that appears to be a compiler bug?  With the best solution being to
                // downgrade the compiler.
                // https://stackoverflow.com/questions/43294488/mingw-g-multiple-definition-of-vsnprintf-when-using-to-string
                // So instead I converted the index count to a string
                // using itoa from stdlib
                // http://www.cplusplus.com/reference/cstdlib/itoa/
                char buffer [10];
                string menuOptionCount;
                menuOptionCount = itoa((menuOptions.size()), buffer, 10);
                throw runtime_error("Invalid entry. Please select between 1 and " + menuOptionCount);
            }
        }
        // catch an invalid selection and print error message
        catch (runtime_error& excpt) {
            cout << excpt.what() << endl << endl;
            validEntry = false;
        }
        // catch an invalid argument (e.g. user enters a string in lieu of int
        // for their menu selection)
        catch (invalid_argument& excpt) {
            cout << "Invalid entry type, please enter a number." << endl << endl;
            validEntry = false;
        }
    } while (!validEntry);

    return userEntry;
}

/*
 * Jeff Perkinson
 * CS-210 J3528
 * January 2020
 *
 * Create two clocks for ChadaTech that display simultaneously
 * using ISO 8601 standards and allow for user input
 */

//#include <ctime>                // Library needed to get and manipulate
//                                // date and time information
//
//// User-defined file inclusions
//#include "clockFunctions.h"     // Header housing the function definitions for
//                           	   // the functions defined in printFunctions.cpp
//                           	   // and pause.cpp


// The below program is not a print function and was originally
// intended to be in a separate pauseProgram.cpp file, but that cause compilation
// errors I could not fix, so I've included it here
/**************************************
 * pauseProgram() --> Pause the program
 * for seconds passed as argument
 * Best to go one second past intended
 * pause time due to processing speed
 * e.g. to pause one second pass in an argument
 * of '2'.
 *************************************/
// A while loop is used because sleep() is OS specific and also not recommended
// due to it being processor-speed dependent and the idea that programs
// should not be hanging themselves
// http://www.cplusplus.com/forum/beginner/76351/
void pauseProgram(int pauseTime) {
    time_t start = currentTime();
    while(currentTime() < (start + pauseTime)) {    // Adding '2' seems to pause the program
       continue;                                    // roughly 1 second; simply adding '1'
    }                                               // processed to abruptly and the initial clock could not be read

    return;
}

