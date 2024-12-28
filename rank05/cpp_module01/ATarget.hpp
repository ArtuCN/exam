#ifndef ATARGET_HPP
#define ATARGET_HPP

#include <iostream>
#include "ASpell.hpp"


class ATarget
{
    protected:
        std::string _type;
        ATarget(const ATarget &at);
        ATarget &operator=(const ATarget &at);
    public:
        std::string getType();
        ATarget();
        ATarget(const std::string &type);
        virtual ATarget clone() const = 0;
        ~ATarget();
        void getHitBySpell(const ASpell &as);

};

#endif