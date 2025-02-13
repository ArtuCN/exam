#pragma once

#include <string>


class ASpell;


class ATarget
{
	protected:
		std::string _type;
	public:
		ATarget();
		ATarget(std::string const &type);
		ATarget(const ATarget &at);
		ATarget &operator=(const ATarget &at);
		virtual ~ATarget();

		std::string const &getType() const;
		
		void getHitBySpell(const ASpell &as) const;
		virtual ATarget *clone() const = 0;

};

#include "ASpell.hpp"

