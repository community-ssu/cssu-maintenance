#include "qclickablelineedit.h"

QClickableLineEdit::QClickableLineEdit(QWidget *parent) :
    QLineEdit(parent)
{
}

void QClickableLineEdit::mousePressEvent(QMouseEvent *ev)
{
    if (ev->button() == Qt::LeftButton) {
        m_pressed = true;
        emit pressed();
    }
}

void QClickableLineEdit::mouseReleaseEvent(QMouseEvent *ev)
{
    if (ev->button() == Qt::LeftButton) {
        m_pressed = false;
        emit released();
        if (rect().contains(ev->pos())) {
            emit clicked();
        }
    }
}

bool QClickableLineEdit::isPressed()
{
    return m_pressed;
}

void QClickableLineEdit::setData(QVariant data)
{
    m_data = data;
}

QVariant QClickableLineEdit::data()
{
    return m_data;
}
