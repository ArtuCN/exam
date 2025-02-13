#pragma once

#include "ASpell.hpp"
#include <map>
#include <string>

class SpellBook
{
	private:
		SpellBook(const SpellBook &sp);
		SpellBook &operator=(const SpellBook &sp);
		std::map<std::string, ASpell *> _copiedSpells;

	public:
		SpellBook();
		~SpellBook();
		void forgetSpell(std::string const &sp);
		void learnSpell(const ASpell &as);
		ASpell* createSpell(std::string const &sp);
};