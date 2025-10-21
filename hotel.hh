/* Class Hotel
 * ----------
 * COMP.CS.110 FALL 2025
 * ----------
 * Class for describing a hotel. Only a single object created from this
 * class. Implements all commands in hotel program.
 *
 * Note: Students need change this class to implement commands missing
 * in the template code.
 * */
#ifndef HOTEL_HH
#define HOTEL_HH

#include "visit.hh"
#include "date.hh"
#include <vector>
#include <map>
#include <memory>

using namespace std;
using Params = const vector<string>&;

// Definition for a room
struct Room
{
    unsigned int capacity;
    unsigned int occupants = 0;
};

// Definition for a person
struct Person
{
    string id;
    vector<Visit> visits;
    bool booked_in = false;
    int room;
};

class Hotel
{
public:
    /**
     * @brief Hotel
     */
    Hotel();

    /**
      * @brief destructor
      */
    ~Hotel();

    /**
     * @brief init
     * Initializes a hotel, i.e. fills it with rooms found from the input file
     */
    bool init();

    /**
     * @brief set_date
     * @param params vector containing parameters of the corresponding command
     */
    void set_date(Params params);

    /**
     * @brief advance_date
     * @param params vector containing parameters of the corresponding command
     * Advances the current date with the given number of days.
     */
    void advance_date(Params params);

    /**
     * @brief print_rooms
     */
    void print_rooms(Params params);

    /**
     * @brief book
     * @param params vector containing parameters of the corresponding command
     * Adds a guest in the hotel and creates a new visit.
     * If the guest given as a parameter has never visited the hotel earlier,
     * creates a new person pointer, otherwise just adds an existing
     * person in the newly created visit.
     */
    void book(Params params);

    /**
     * @brief leave
     * @param params vector containing parameters of the corresponding command
     * Removes the guest given as a parameter from the hotel, and closes
     * guest's visits. However, the guest still remains in all_visits_.
     */
    void leave(Params params);

    /**
     * @brief print_guest_info
     * @param params vector containing parameters of the corresponding command
     * Prints the given guest's all visits.
     */
    void print_guest_info(Params params);

    /**
     * @brief print_all_visits
     * Prints all guests visited the hotel at some time, i.e. all
     * current and earlier guests.
     * More precisely, prints each guest's id and visiting period
     */
    void print_all_visits(Params);

    /**
     * @brief print_current_visits
     * Prints the current guests' ids and room numbers.
     */
    void print_current_visits(Params params);

    /**
     * @brief print_honor_guests
     * Prints the ids of those guests that have visited the hotel most often.
     */
    void print_honor_guests(Params);

private:
    vector<Room> rooms_;
    vector<Person> persons_;

    // Set persons into alphabetical order
    vector<Person> set_persons_alphabetical(vector<Person> persons);

    // Return true if hotel is empty, false if not empty
    bool hotel_empty();

};

#endif // HOTEL_HH
