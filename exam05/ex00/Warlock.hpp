#ifndef WARLOCK_HPP
#define WARLOCK_HPP

#include <iostream>
#include <string>


class Warlock
{
	private:
		std::string _name;
		std::string _title;
		Warlock();
		Warlock(const Warlock &wr);
		Warlock &operator=(const Warlock &wr);
	public:
		std::string const &getName() const;
		std::string const &getTitle() const;

		Warlock(const std::string &nm, const std::string &tt);
		~Warlock();
		
		void setTitle(const std::string &tt);

		void introduce() const;

};

#endif