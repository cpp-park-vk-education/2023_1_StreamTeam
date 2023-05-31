#ifndef QDYNAMICBUTTON_H
#define QDYNAMICBUTTON_H

#include "room.hpp"

#include <QPushButton>
#include <memory>

template <typename T>
class IQDynamicButton
{
public:
    virtual std::shared_ptr<T> getObjectPtr();

    virtual void setObjectPtr(std::shared_ptr<T>);

protected:
    std::shared_ptr<T> object_pointer;
};

//template <typename T>
class QDynamicButtonRoom : public QPushButton, public IQDynamicButton<Room>
{
    Q_OBJECT
public:
    explicit QDynamicButtonRoom(QWidget *parent = nullptr);
    ~QDynamicButtonRoom();
 
public slots:
 
private:

};
 
#endif
