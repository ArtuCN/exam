#ifndef WARLOCK_HPP
#define WARLOCK_HPP


#include <iostream>

class Warlock
{
    private:
        std::string _name;
        std::string _title;
        Warlock(const Warlock &w);
        Warlock& operator=(const Warlock &w);
    public:
        Warlock();
        Warlock(const std::string &name);
        Warlock(const std::string &name, const std::string &title);
        ~Warlock();

        void introduce() const;
        void setTitle(const std::string &title);

        const std::string &getName() const;
        const std::string &getTitle() const;
};

#endif