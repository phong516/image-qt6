#ifndef IMAGE_H
#define IMAGE_H

#include <QWidget>
#include <QImage>
#include <QImageReader>
#include <QImage>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QLabel>
#include <QScreen>
#include <QPixmap>

enum class modifyMode
{
    raw,
    grayscale,
    rgb,
    cmyk,
};

class image : public QWidget
{
    Q_OBJECT

public:
    image(QWidget *parent = nullptr);
    ~image();

private:
    QImage * pr_image;
    QPixmap * pr_pixmap;
    QHBoxLayout * mainLayout;
    QGroupBox * imageBox       ;
    QHBoxLayout * imageLayout  ;
    QLabel * imageLabel        ;
    QVBoxLayout * rightPanel   ;
    QGroupBox * inputBox       ;
    QVBoxLayout * inputLayout  ;
    QPushButton * openButton   ;
    QGroupBox * modifyBox      ;
    QVBoxLayout * modifyLayout ;
    QPushButton * grayscaleButton;
    QPushButton * rgbButton    ;
    QPushButton * cmykButton   ;
    QGroupBox * outputBox      ;
    QVBoxLayout * outputLayout ;
    QPushButton * saveButton   ;

signals:
    void signal_modify(modifyMode);

private slots:
    void slot_openImage();
    void slot_modifyImage(modifyMode);
};
#endif // IMAGE_H
