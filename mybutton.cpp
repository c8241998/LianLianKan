#include "mybutton.h"

MyButton::MyButton(QWidget* parent)
    : QPushButton(parent)
{
}
void MyButton::enterEvent(QEvent* e)
{
    setIconSize(QSize(70,70));
}
void MyButton::leaveEvent(QEvent* e)
{
    setIconSize(QSize(40,40));
}
