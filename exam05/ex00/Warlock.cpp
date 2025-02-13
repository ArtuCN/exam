#include "Warlock.hpp"
#include <string>


Warlock::Warlock(): _name("Default"), _title("The Defaulter")
{
	std::cout<<_name + ": This looks like another boring day.\n";
}

Warlock::Warlock(const std::string &nm, const std::string &tt): _name(nm), _title(tt)
{
	std::cout<<_name + ": This looks like another boring day.\n";
}

Warlock::~Warlock()
{
	std::cout<<_name+": My job here is done!\n";
}

std::string const &Warlock::getName() const
{
	return _name;
}

std::string const &Warlock::getTitle() const
{
	return _title;
}

void Warlock::introduce() const
{
	std::cout<< _name + ": I am " + _name + ", " +_title+ "!\n";
}

void Warlock::setTitle(const std::string &tt)
{
	_title = tt;
}

Warlock::Warlock(const Warlock &wr): _name(wr.getName()), _title(wr.getTitle())
{
	std::cout<<_name + ": This looks like another boring day.\n";
}

Warlock &Warlock::operator=(const Warlock &wr)
{
	if (&wr != this)
	{
		_name = wr._name;
		_title = wr.getTitle();
	}
	return *this;
}