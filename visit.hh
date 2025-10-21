/* Class Visit
 * ----------
 * COMP.CS.110 FALL 2025
 * ----------
 * Class for describing a guest's visit in hotel.
 *
 * Note: Students need to implement almost all of this class by themselves.
 * */
#ifndef VISIT_HH
#define VISIT_HH

#include "date.hh"

using namespace std;

class Visit
{
public:
    // Constructor
    Visit(const Date& start);

    // Destructor
    ~Visit();

    // Returns the start date of the visit
    const Date& get_start();

    // Returns the end date of the visit
    const Date& get_end();

    // Set end date for visit
    void set_end(const Date& end);

private:
    Date start_;
    Date end_;

    // TODO: More attributes and private methods
};

#endif // VISIT_HH
