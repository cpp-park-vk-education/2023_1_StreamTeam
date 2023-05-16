#include "qdynamicbutton.h"

QDynamicButtonRoom::QDynamicButtonRoom(QWidget *parent) :
    QPushButton(parent)
{
    setFixedHeight(40);
}

QDynamicButtonRoom::~QDynamicButtonRoom()
{
 
}

template <typename T>
std::shared_ptr<T> IQDynamicButton<T>::getObjectPtr()
{
    return object_pointer;
}

template <typename T>
void IQDynamicButton<T>::setObjectPtr(std::shared_ptr<T> ptr)
{
    object_pointer = ptr;
}

