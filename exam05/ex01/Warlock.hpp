#pragma once

#include <iostream>
#include "ASpell.hpp"
#include "ATarget.hpp"

#include <string>
#include <map>

class ASpell;
class ATarget;


class Warlock
{
	private:
		std::map<std::string, ASpell *> _knownSpells;
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


		void learnSpell(ASpell *as);
		void forgetSpell(const std::string &str);
		void launchSpell(const std::string &str, const ATarget &at);

		void introduce() const;

};
