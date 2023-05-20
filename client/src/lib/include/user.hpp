#ifndef USER_H
#define USER_H

#include <string>
#include <memory>

class User
{
public:
    int GetId ();

    std::string GetName();

    std::string GetPassword();

    std::string GetEmail();

    void SetId (int);

    void SetName(std::string);

    void SetPassword(std::string);

    void SetEmail(std::string);

private:
    int _id;
    std::string _name;
    std::string _password;
    std::string _email;

};

#endif // USER_H
