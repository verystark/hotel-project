#include "visit.hh"

Visit::Visit(const Date& start) : start_(start), end_() {}

Visit::~Visit() {}

const Date& Visit::get_start()
{
    return start_;
}

const Date& Visit::get_end()
{
    return end_;
}

void Visit::set_end(const Date& end)
{
    end_ = end;
}
