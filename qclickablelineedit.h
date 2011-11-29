#ifndef QCLICKABLELINEEDIT_H
#define QCLICKABLELINEEDIT_H

#include <QLineEdit>
#include <QMouseEvent>

class QClickableLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit QClickableLineEdit(QWidget *parent = 0);
    bool isPressed();
    QVariant data();

public slots:
    void setData(QVariant data);

protected:
    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);

signals:
    void pressed();
    void released();
    void clicked();

private:
    bool m_pressed;
    QVariant m_data;
};

#endif // QCLICKABLELINEEDIT_H
