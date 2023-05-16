#pragma once
#include <string>
#include <memory>

#include "user.hpp"

class Message
{
public:

    int GetId();

    void SetId(int);

    std::string GetAuthorName ();

    std::string GetAuthorAvatarUrl ();

    bool SetAuthor (User);

    std::string GetTextBody();

    void SetTextBody(std::string);

    std::string GetAttachmentUrl();

    void SetAttachmentUrl(std::string);

    std::string GetPostTime();

    void SetPostTime(std::string);

    bool Delete();

private:
    int _id;
    User _author;
    std::string _text_body;
    std::string _attachment_url;
    std::string _post_time;
    
};
