#ifndef IMAGE_H
#define IMAGE_H

#include <QWidget>

class image : public QWidget
{
    Q_OBJECT

public:
    image(QWidget *parent = nullptr);
    ~image();
private:
    QWidget * setInputBox();
    QWidget * setModifyBox();
    QWidget * setOutputBox();
};
#endif // IMAGE_H
