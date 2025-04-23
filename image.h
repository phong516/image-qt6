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
    QImage *getPr_image() const;
    void setPr_image(QImage *newPr_image);
    QImageReader *getPr_imageReader() const;
    void setPr_imageReader(QImageReader *newPr_imageReader);
    QPixmap *getPr_pixmap() const;
    void setPr_pixmap(QPixmap *newPr_pixmap);
    QString *getPr_filepath() const;
    void setPr_filepath(QString *newPr_filepath);

private:
    QImage * pr_image = new QImage();
    QImageReader * pr_imageReader = new QImageReader();
    QPixmap * pr_pixmap = new QPixmap();
    QString * pr_filepath = new QString();



signals:
    void signal_modify(modifyMode);

private slots:
    void slot_openImage();
    void slot_modifyImage(modifyMode);
};
#endif // IMAGE_H
