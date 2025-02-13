#include "ASpell.hpp"
#include "ATarget.hpp"
#include <string>

ASpell::ASpell() {}

ASpell::ASpell(const std::string &n, const std::string &e): _name(n), _effects(e) {}

ASpell::ASpell(const ASpell &as)
{
	_name = as._name;
	_effects = as._effects;
}

ASpell &ASpell::operator=(const ASpell &as)
{
	if (this != &as)
	{
		_name = as._name;
		_effects = as._effects;
	}
	return *this;
}

std::string const &ASpell::getName() const {return _name;}

std::string const &ASpell::getEffects() const {return _effects;}

ASpell::~ASpell() {}

void ASpell::launch(const ATarget &at)
{
	at.getHitBySpell(*this);
}

