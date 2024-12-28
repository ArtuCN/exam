#ifndef FWOOSH_HPP
#define FWOOSH_HPP

#include "ATarget.hpp"

class Fwoosh: public ASpell
{
    private:

    public:
        Fwoosh();
		~Fwoosh();
		ASpell* clone() const;

};


#endif