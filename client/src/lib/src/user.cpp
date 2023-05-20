#include <string>
#include <memory>

#include "user.hpp"


int User::GetId ()
{
    return _id;
}

std::string User::GetName()
{
    return _name;
}

std::string User::GetPassword()
{
    return _password;
}

std::string User::GetEmail()
{
    return _email;
}

void User::SetId (int id)
{
    _id = id;
}

void User::SetName(std::string name)
{
    _name = name;
}

void User::SetPassword(std::string pass)
{
    _password = pass;
}

void User::SetEmail(std::string email)
{
    _email = email;
}
