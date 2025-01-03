#ifndef ASPELL_HPP
#define ASPELL_HPP

#include <iostream>
#include "ATarget.hpp"

class ASpell
{
    protected:
        std::string _name;
        std::string _effects;
        ASpell();
        ASpell(const ASpell &as);
        ASpell &operator=(const ASpell &as);
    public:
        const std::string getName() const;
        const std::string getEffects() const;
        virtual ASpell *clone() const = 0;
        ASpell(const std::string &name, const std::string &effects);
        void launch(ATarget const &at) const;
        ~ASpell();
};

#endif