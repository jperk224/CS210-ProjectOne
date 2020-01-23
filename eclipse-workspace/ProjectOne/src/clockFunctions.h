/*
 * Jeff Perkinson
 * CS-210 J3528
 * January 2020
 *
 * Create two clocks for ChadaTech that display simultaneously
 * using ISO 8601 standards and allow for user input
 */

/*
 * Header file for function declarations
 * The compiler does not see the function definitions in printFunctions.cpp
 * while processing the main file because
 * those definitions are in separate files (e.g printFunctions.cpp).
 * Function declarations must be provided before main() in main.cpp
 * so the compiler knows about the functions to compile calls to them.
 * Instead of typing the declarations directly above main(),
 * a programmer can provide the function declarations in a header file
 * (Zybooks Programming Languages 4.16 Separate Files)
 */

/*
 * Header file guards ensure the compiler only includes the contents of
 * the header file one time.  #ifndef tells the compiler to only include the
 * code between the #define and #endif instructs if CLOCKFUNCTION_H_ is not
 * already defined
 * (Zybooks Programming Languages 4.16: Separate Files)
 */

#ifndef CLOCKFUNCTIONS_H_
#define CLOCKFUNCTIONS_H_

time_t currentTime();                                                   // Return the current time
// The namespaces below are scoped to the specific function declarations
// Using 'namespace std' is considered bad practice, particularly
// in a header file that can potentially be used in multiple other files
// https://stackoverflow.com/questions/1452721/why-is-using-namespace-std-considered-bad-practice

std::string displayClock24(time_t time);                                // Display time in the 24-hour format

std::string displayClock12(time_t time);                                // Display time in 12-hour format
void displayHorizontalBorder    (int length);                           // Display clock and menu upper
                                                                        // and lower horizontal borders

void displayMarquee(std::string displayString, int spanLength,          // Display contents in the box
                    bool isCentered=true);                              // (e.g. clock, options menu)

void displayMarqueeWithCount(std::string displayString, int spanLength, // Display contents with a numerical
                            int identifier, bool isCentered=false);     // identifier (e.g. 4 - Exit)

void displayClocks(int boxWidth, time_t timeToDisplay);                 // Display clocks (12 and 24 hour)
int displayMenu(std::vector<std::string> menuOptions, int boxWidth);    // Display options menu and capture/return
                                                                        // user selection
void pauseProgram(int pauseTime);										// Loop to suspend execution

#endif /* CLOCKFUNCTIONS_H_ */
