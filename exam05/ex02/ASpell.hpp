#pragma once

#include <iostream>
#include <string>

class ATarget;

class ASpell
{
	protected:
		std::string _name;
		std::string _effects;
	public:
		ASpell();
		ASpell(const std::string &n, const std::string &ef);
		ASpell(const ASpell& as);
		ASpell &operator=(const ASpell& as);
		virtual ~ASpell();

		std::string const &getName() const;
		std::string const &getEffects() const;


		void launch(const ATarget &at);
		virtual ASpell *clone() const = 0;

		
};

#include "ATarget.hpp"

