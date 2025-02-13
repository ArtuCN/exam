#pragma once

#include "ATarget.hpp"
#include <map>
class TargetGenerator
{
	private:
		TargetGenerator(const TargetGenerator &tg);
		std::map<std::string, ATarget *> _knownTargets;
		TargetGenerator &operator=(const TargetGenerator &tg);

	public:
		TargetGenerator();
		~TargetGenerator();

		void learnTargetType(ATarget *at);
		void forgetTargetType(const std::string &str);
		ATarget *createTarget(const std::string &str);

};