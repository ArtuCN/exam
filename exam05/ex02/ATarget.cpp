#include "ATarget.hpp"


ATarget::ATarget() :_type() {}

ATarget::ATarget(std::string const &type) { this->_type = type;}


ATarget::ATarget(const ATarget &at) { _type = at._type;}

ATarget &ATarget::operator=(const ATarget &at){
	if (this != &at)
		_type = at._type;
	return *this;
}

ATarget ::~ATarget(){}

std::string const &ATarget::getType() const { return _type;}

void ATarget::getHitBySpell(const ASpell &as) const
{
	std::cout<< _type + " has been " + as.getEffects() + "!\n";
}