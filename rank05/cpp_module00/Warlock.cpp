#include "Warlock.hpp"

Warlock::Warlock()
{
    _name = "Default";
    _title = "Default";
    std::cout << _name << ": This looks like another boring day." << std::endl;
}

Warlock::Warlock(const std::string &name)
{
    _name = name;
    _title = "Default";
    std::cout << _name << ": This looks like another boring day." << std::endl;
}

Warlock::Warlock(const std::string &name, const std::string &title)
{
    _name = name;
    _title = title;
    std::cout << _name << ": This looks like another boring day." << std::endl;
}

Warlock::Warlock(const Warlock &w)
{
    if (this != &w)
    {
        _name = w._name;
        _title = w._title;
    }
}

Warlock &Warlock::operator=(const Warlock &w)
{
    this->_name = w._name;
	this->_title = w._title;
	return *this;
}


const std::string &Warlock::getName() const
{
    return _name;
}

const std::string &Warlock::getTitle() const
{
    return _title;
}

Warlock::~Warlock()
{
	std::cout << _name << ": My job here is done!" << std::endl;
}

void	Warlock::introduce() const
{
	std::cout << _name << ": I am " << _name << ", " << _title << "!" << std::endl;
}

void    Warlock::setTitle(const std::string &title)
{
    _title = title;
}