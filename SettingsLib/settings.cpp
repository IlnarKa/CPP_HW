#include "settings.h"

settings::param::param(const string & name, std::string value, const settings *parent)
{

}

settings::param::operator std::string() const
{
}
settings::param::operator bool() const
{
}
settings::param::operator int() const
{
}
settings::param::operator double() const
{
}
settings::param & settings::param::operator=(char const * value)
{
}
settings::param & settings::param::operator=(std::string const & value)
{

}
settings::param & settings::param::operator=(int value)
{

}
settings::param & settings::param::operator=(bool value)
{

}
settings::param & settings::param::operator=(double value)
{

}

settings::param & settings::param::operator+=(std::string const & value)
{

}
settings::param & settings::param::operator+=(int value)
{

}
settings::param & settings::param::operator+=(double value)
{

}

settings::param & settings::param::operator-=(int value)
{

}
settings::param & settings::param::operator-=(double value)
{

}

settings::param & settings::param::operator*=(int value)
{

}
settings::param & settings::param::operator*=(double value)
{

}

settings::param & settings::param::operator/=(int value)
{

}
settings::param & settings::param::operator/=(double value)
{

}

settings::param & settings::param::operator|=(bool value)
{

}
settings::param & settings::param::operator&=(bool value)
{

}
bool settings::param::is_empty() const
{

}

settings::settings(const string & filename)
{
}
string const & settings::get(std::string const & name, std::string const & def) const
{
}
void settings::set(std::string const &name, std::string const &value)
{

}
void settings::reset()
{

}
void settings::reload()
{

}
const settings::param settings::operator[](std::string const &name) const
{

settings::param settings::operator[](std::string const & name)
{

}
void settings::updateFile()
{

}
