#include <memory>

#include "message.hpp"


int Message::GetId()
{
    return _id;
}

void Message::SetId(int id)
{
    _id = id;
}

std::string Message::GetAuthorName()
{
    return _author.GetName();
}

std::string Message::GetAuthorAvatarUrl ()
{
    return "url";
}

bool Message::SetAuthor (User user)
{
    _author = user;
    return true;
}

std::string Message::GetTextBody()
{
    return _text_body;
}

void Message::SetTextBody(std::string text)
{
    _text_body = text;
}

std::string Message::GetAttachmentUrl()
{
    return _attachment_url;
}

void Message::SetAttachmentUrl(std::string url)
{
    _attachment_url = url;
}

std::string Message::GetPostTime()
{
    return _post_time;
}

void Message::SetPostTime(std::string time)
{
    _post_time = time;
}

bool Message::Delete()
{
    return true;
}
