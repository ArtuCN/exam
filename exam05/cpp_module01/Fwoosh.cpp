#include "Fwoosh.hpp"

Fwoosh::Fwoosh()
{
    _name = "Fwoosh";
    _effects = "Fwooshed";
}

ASpell *ASpell::clone() const
{
    return new Fwoosh();
}

Fwoosh::~Fwoosh()
{}