#ifndef CS61_MOTELFRIEND_HH
#define CS61_MOTELFRIEND_HH
#include <cstddef>

bool check_in(unsigned long room);
    // Check in a guest to room number `room`.
    // Return false if `room` was previously occupied, true otherwise.

unsigned long empty_room();
    // Return the number of a currently-unoccupied room.
    // Since the hotel is very long, and the office is located in “room” 0,
    // return the *minimum* unoccupied room number.


// Extra functions for testing

bool check_map_size(size_t expected_size);
    // Return true if the room map data structure has size `expected_size`.

bool check_rep();
    // Run internal tests on the room map data structure and return true
    // if it is valid.

#endif
