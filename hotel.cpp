#include "hotel.hh"
#include "utils.hh"
#include <iostream>
#include <fstream>
#include <set>

// Error and information outputs
const string FILE_NOT_FOUND = "Error: Input file not found."s;
const string WRONG_FORMAT = "Error: Wrong format in file."s;
const string NOT_NUMERIC = "Error: Wrong type of parameters."s;
const string ALREADY_EXISTS = "Error: Already exists: "s;
const string CANT_FIND = "Error: Can't find anything matching: "s;
const string GUEST_ENTERED = "A new guest has entered."s;
const string GUEST_LEFT = "Guest left hotel, visit closed."s;
const string FULL = "Error: Can't book, no such rooms available."s;

Hotel::Hotel()
{
    //cout << "Hotel constructor" << endl;
}

Hotel::~Hotel()
{
    //cout << "Hotel destructor" << endl;
}

bool Hotel::init()
{
    cout << "Input file: ";
    string file_name = "";
    getline(cin, file_name);
    ifstream file(file_name);
    if ( !file )
    {
        cout << FILE_NOT_FOUND << endl;
        return false;
    }

    string line = "";
    while ( getline(file, line) )
    {
        vector<string> parts = utils::split(line, ';');
        if ( parts.size() != 2 )
        {
            cout << WRONG_FORMAT << endl;
            return false;
        }
        if ( !( utils::is_numeric(parts.at(0), false) &&
                   utils::is_numeric(parts.at(1), false) ) )
        {
            cout << NOT_NUMERIC << endl;
            return false;
        }

        unsigned int size = stoi(parts.at(0));
        unsigned int amount = stoi(parts.at(1));
        for ( unsigned int i = 0; i < amount; ++i )
        {
            rooms_.push_back(Room{size});
        }
    }

    return true;
}


void Hotel::set_date(Params params)
{
    string day = params.at(0);
    string month = params.at(1);
    string year = params.at(2);
    if ( !utils::is_numeric(day, false) ||
         !utils::is_numeric(month, false) ||
         !utils::is_numeric(year, false) )
    {
        cout << NOT_NUMERIC << endl;
        return;
    }
    utils::today.set(stoi(day), stoi(month), stoi(year));
    cout << "Date has been set to ";
    utils::today.print();
    cout << endl;
}

void Hotel::advance_date(Params params)
{
    string amount = params.at(0);
    if ( !utils::is_numeric(amount, true) )
    {
        cout << NOT_NUMERIC << endl;
        return;
    }
    utils::today.advance(stoi(amount));
    cout << "New date is ";
    utils::today.print();
    cout << endl;
}

void Hotel::print_rooms(Params /*params*/)
{
    int room_number = 1;
    for (Room& room : rooms_) {
        cout << "Room " << room_number << " : for " << room.capacity << " person(s) ";
        int available_spots = room.capacity - room.occupants;
        if (available_spots == 0) {
            cout << ": full" << endl;
        } else {
            cout << ": available for " << available_spots << " person(s)" << endl;
        }
        room_number++;
    }
}

void Hotel::book(Params params)
{
    string id = params.at(0);
    string room_str = params.at(1);
    if (!utils::is_numeric(room_str, false)) {
        cout << NOT_NUMERIC << endl;
        return;
    }   

    for (Person& person : persons_) {
        if (id == person.id) {
            if (person.booked_in) {
                cout << ALREADY_EXISTS << id << endl;
                return;
            }
        }
    }
    unsigned int room_size = stoi(params.at(1));
    Room* best_room = nullptr;
    for (Room& room : rooms_) {
        if (room.capacity == room_size && room.occupants < room.capacity) {
            if (!best_room || room.occupants < best_room->occupants) {
                best_room = &room;
            }
        }
    }
    if (!best_room) {
        cout << FULL << endl;
        return;
    }
    int room_number = best_room - &rooms_.at(0) + 1;
    // Check if persons object is already in hotel system
    for (Person& person : persons_) {
        // If person found in system book new visit into persons object
        if (person.id == id) {
            person.visits.push_back(Visit(utils::today));
            person.room = room_number;
            person.booked_in = true;
            best_room->occupants++;
            cout << GUEST_ENTERED << endl;
            return;
        }
    }
    // If person not in hotel system create new object and book visit
    Person new_person;
    new_person.id = id;
    new_person.visits.push_back(Visit(utils::today));
    new_person.booked_in = true;
    new_person.room = room_number;
    persons_.push_back(new_person);
    best_room->occupants++;
    cout << GUEST_ENTERED << endl;
}

void Hotel::leave(Params params)
{
    string id = params.at(0);
    for (Person& person : persons_) {
        if (person.id  == id) {
            if (person.booked_in) {
                rooms_[person.room - 1].occupants--;
                person.room = 0;
                person.booked_in = false;
                person.visits.back().set_end(utils::today);
                cout << GUEST_LEFT << endl;
                return;
            }
        }
    }
    cout << CANT_FIND << params.at(0) << endl;
}

void Hotel::print_guest_info(Params params)
{
    string id = params.at(0);
    for (Person& person : persons_) {
        if (person.id == id) {
            for (Visit visit : person.visits) {
                cout << "* Visit: ";
                visit.get_start().print();
                cout << " - ";
                if (!visit.get_end().is_default()) {
                    visit.get_end().print();
                }
                cout << endl;
            }
            return;
        }
    }
    cout << CANT_FIND << id << endl;
}

void Hotel::print_all_visits(Params /*params*/)
{
    if (hotel_empty()) {
        cout << "None" << endl;  // Only print here if the hotel is empty
        return;
    }
    vector<Person> alphabetical = set_persons_alphabetical(persons_);
    for (const Person& person : alphabetical) {
        cout << person.id << endl;
        vector<string> param = {person.id};
        print_guest_info(param);
    }
}
void Hotel::print_current_visits(Params /*params*/)
{
    if (hotel_empty()) {
        cout << "None" << endl;  // Print only when needed
        return;
    }
    vector<Person> booked_persons;
    for (Person person : persons_) {
        if (person.booked_in) {
            booked_persons.push_back(person);
        }
    }
    if (booked_persons.empty()) {
        cout << "None" << endl;
        return;
    }
    vector<Person> alphabetical = set_persons_alphabetical(booked_persons);
    for (Person person : alphabetical) {
        cout << person.id << " is boarded in Room " << person.room << endl;
    }
}


void Hotel::print_honor_guests(Params /*params*/)
{
    if (hotel_empty()) {
        return;
    }
    size_t max_visits = 0;

    for (const Person& person : persons_) {
        if (person.visits.size() > max_visits) {
            max_visits = person.visits.size();
        }
    }

    if (max_visits == 0) {
        cout << "None" << endl;
        return;
    }

    vector<Person> honor_guests;
    for (const Person& person : persons_) {
        if (person.visits.size() == max_visits) {
            honor_guests.push_back(person);
        }
    }

    honor_guests = set_persons_alphabetical(honor_guests);

    cout << "With " << max_visits << " visit(s), the following guest(s) get(s) honorary award:" << endl;
    for (const Person& person : honor_guests) {
        cout << "* " << person.id << endl;
    }
}

vector<Person> Hotel::set_persons_alphabetical(vector<Person> persons)
{
    for (size_t i = 0; i < persons.size(); ++i) {
        for (size_t j = i + 1; j < persons.size(); ++j) {
            if (persons.at(j).id < persons.at(i).id) {
                swap(persons.at(i), persons.at(j));
            }
        }
    }
    return persons;
}

bool Hotel::hotel_empty()
{
    return persons_.empty();
}
