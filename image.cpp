#include "image.h"
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

image::image(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout * mainLayout = new QHBoxLayout(this);

    int screenWidth = QGuiApplication::primaryScreen()->availableGeometry().width();
    int screenHeight = QGuiApplication::primaryScreen()->availableGeometry().height();
    this->resize(screenWidth, screenHeight);

    QGroupBox * imageBox =  new QGroupBox("Image");
    QHBoxLayout * imageLayout = new QHBoxLayout(imageBox);
    QLabel * imageLabel = new QLabel(imageBox);
    imageLabel->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    imageLabel->setAlignment(Qt::AlignCenter);
    imageLayout->addWidget(imageLabel);
    imageBox->setLayout(imageLayout);
    mainLayout->addWidget(imageBox, 9);

    QVBoxLayout * rightPanel = new QVBoxLayout();
    mainLayout->addLayout(rightPanel, 1);

    QGroupBox * inputBox = new QGroupBox("Input");
    QVBoxLayout * inputLayout = new QVBoxLayout(inputBox);
    QPushButton * openButton = new QPushButton("Open Image", inputBox);
    inputLayout->addWidget(openButton);
    inputBox->setLayout(inputLayout);

    QGroupBox * modifyBox = new QGroupBox("Modify");
    QVBoxLayout * modifyLayout = new QVBoxLayout(modifyBox);
    QPushButton * grayscaleButton = new QPushButton("GrayScale", modifyBox);
    QPushButton * rgbButton = new QPushButton("RGB", modifyBox);
    QPushButton * cmykButton = new QPushButton("CMYK", modifyBox);
    modifyLayout->addWidget(grayscaleButton);
    modifyLayout->addWidget(rgbButton);
    modifyLayout->addWidget(cmykButton);
    modifyBox->setLayout(modifyLayout);

    QGroupBox * outputBox = new QGroupBox("Output");
    QVBoxLayout * outputLayout = new QVBoxLayout(outputBox);
    QPushButton * saveButton = new QPushButton("Save Image", outputBox);
    outputLayout->addWidget(saveButton);
    outputBox->setLayout(outputLayout);

    rightPanel->addWidget(inputBox, 1);
    rightPanel->addWidget(modifyBox, 8);
    rightPanel->addWidget(outputBox, 1);


   // OPEN IMAGE
    QString imageFileName;
    connect(openButton, &QPushButton::clicked, this, [this, &imageFileName, imageLabel](){
        imageFileName = QFileDialog::getOpenFileName(this, "Open Image", QDir::homePath(), "Images (*.png *.xpm *.jpg)");
        //qInfo() << "Path: " << imageFileName;
        if (imageFileName.isEmpty())
            {
            qInfo("No file selected");
            return;
        }
        QImageReader imageReader(imageFileName);
        if (!imageReader.canRead())
        {
            qWarning("Image file is invalid");
            return;
        }
        QPixmap imagePixmap = QPixmap::fromImageReader(&imageReader);
        qInfo() << "imagePixmap: " << imagePixmap.size();
        qInfo() << "imageLabel: " << imageLabel->size();
        if (imagePixmap.width() > imageLabel->width() || imagePixmap.height() > imageLabel->height())
        {
            imagePixmap.scaled(imageLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
            qInfo() << "imagePixmap: " << imagePixmap.size();
        }
        imageLabel->setPixmap(imagePixmap);

    });
}

image::~image()
{

}

QWidget * image::setInputBox()
{
    ;
}

QWidget * image::setModifyBox()
{
    ;
}

QWidget * image::setOutputBox()
{
    ;
}
