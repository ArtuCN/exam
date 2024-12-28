#include "ATarget.hpp"

ATarget::ATarget()
{
    _type = "default";
}

ATarget::ATarget(const ATarget &at)
{
    _type = at._type;
}

ATarget::ATarget(const std::string &type)
{
    _type = type;
}

ATarget &ATarget::operator=(const ATarget &at)
{
    _type = at._type;
    return *this;
}

void ATarget::getHitBySpell(const ASpell &as)
{
    std::cout<<_type<<" has been "<<as.getEffects()<<"!\n";
}