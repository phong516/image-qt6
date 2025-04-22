#ifndef IMAGE_H
#define IMAGE_H

#include <QWidget>

class image : public QWidget
{
    Q_OBJECT

public:
    image(QWidget *parent = nullptr);
    ~image();
};
#endif // IMAGE_H
