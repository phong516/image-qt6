#include "image.h"
#include <QImage>
#include <QImageReader>
#include <QImage>
#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QPushButton>

image::image(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout * mainLayout = new QHBoxLayout(this);
    QVBoxLayout * rightPanel = new QVBoxLayout();
    mainLayout->addLayout(rightPanel);

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
