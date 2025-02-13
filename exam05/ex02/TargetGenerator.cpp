#include "TargetGenerator.hpp"
#include "ATarget.hpp"
#include <cstddef>
#include <map>
#include <utility>


TargetGenerator::TargetGenerator()
{}

TargetGenerator::TargetGenerator(const TargetGenerator &tg) { *this = tg;}

TargetGenerator &TargetGenerator::operator=(const TargetGenerator &tg) {
	if (this != &tg)
	{
		_knownTargets = tg._knownTargets;
	}
	return *this;
}

TargetGenerator::~TargetGenerator()
{
	std::map<std::string, ATarget *>::iterator it = _knownTargets.begin();
	std::map<std::string, ATarget *>::iterator end = _knownTargets.end();
	
	while (it != end)
	{
		delete it->second;
		++it;
	}
	_knownTargets.clear();
}

void TargetGenerator::learnTargetType(ATarget *at)
{
	if (at)
		_knownTargets.insert(std::pair<std::string, ATarget *>(at->getType(), at->clone()));
}

void TargetGenerator::forgetTargetType(const std::string &str)
{
	_knownTargets.erase(str);
}

ATarget *TargetGenerator::createTarget(const std::string &str)
{
	std::map<std::string, ATarget *>::iterator it = _knownTargets.find(str);
	if (it != _knownTargets.end())
	{
		return _knownTargets[str];
	}
	return NULL;
}