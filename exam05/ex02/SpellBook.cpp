#include "SpellBook.hpp"
#include "ASpell.hpp"
#include <cstddef>
#include <map>
#include <string>
#include <utility>

SpellBook::SpellBook() {}

SpellBook::SpellBook(const SpellBook &sp) { *this = sp;}

SpellBook &SpellBook::operator=(const SpellBook &sp) 
{
	if (&sp != this)
		_copiedSpells = sp._copiedSpells;
	return *this;
}

SpellBook::~SpellBook()
{
	std::map<std::string, ASpell *>::iterator it = _copiedSpells.begin();
	std::map<std::string, ASpell *>::iterator end = _copiedSpells.end();
	while (it != end) {
		delete it->second;
		it++;
	}
}

void SpellBook::learnSpell(const ASpell &as)
{
	std::map<std::string, ASpell *>::iterator it = _copiedSpells.begin();
	std::map<std::string, ASpell *>::iterator end = _copiedSpells.end();
	while (it != end) {
		if (it->first == as.getName())
			return;
		it++;
	}
	_copiedSpells.insert(std::pair<std::string, ASpell *>(as.getName(), as.clone()));
}


void SpellBook::forgetSpell(const std::string &str)
{
	std::map<std::string, ASpell *>::iterator it = _copiedSpells.find(str);
	if (it != _copiedSpells.end())
		delete it->second;
	_copiedSpells.erase(str);
}

ASpell *SpellBook::createSpell(const std::string &sp)
{
	std::map<std::string, ASpell *>::iterator it = _copiedSpells.find(sp);
	if (it != _copiedSpells.end())
		return _copiedSpells[sp];
	return NULL;
}