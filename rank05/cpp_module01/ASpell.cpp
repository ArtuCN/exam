#include "ASpell.hpp"

ASpell::ASpell()
{
    _name = "default";
    _effects = "default";
}

ASpell::ASpell(const std::string &name, const std::string &effects)
{
    _name = name;
    _effects = effects;
}

ASpell & ASpell::operator=(ASpell const & as)
{
	_name = as.getName();
	_effects = as.getEffects();
	return *this;
}

ASpell::ASpell(ASpell const & as)
{
	*this = as;
}

const std::string ASpell::getEffects() const
{
    return _effects;
}

const std::string ASpell::getName() const
{
    return _name;
}

ASpell::~ASpell()
{

}

void ASpell::launch(ATarget const &at) const
{
    at.getHitBySpell(*this);
}