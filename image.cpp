#include "image.h"

image::image(QWidget *parent)
    : QWidget(parent)
{
    mainLayout = new QHBoxLayout(this);

    int screenWidth = QGuiApplication::primaryScreen()->availableGeometry().width();
    int screenHeight = QGuiApplication::primaryScreen()->availableGeometry().height();
    this->resize(screenWidth, screenHeight);

    imageBox =  new QGroupBox("Image");
    imageLayout = new QHBoxLayout(imageBox);
    imageLabel = new QLabel(imageBox);
    imageLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    imageLabel->setAlignment(Qt::AlignCenter);
    imageLayout->addWidget(imageLabel);
    imageBox->setLayout(imageLayout);
    mainLayout->addWidget(imageBox, 9);

    rightPanel = new QVBoxLayout();
    mainLayout->addLayout(rightPanel, 1);

    inputBox = new QGroupBox("Input");
    inputLayout = new QVBoxLayout(inputBox);
    openButton = new QPushButton("Open Image", inputBox);
    inputLayout->addWidget(openButton);
    inputBox->setLayout(inputLayout);

    modifyBox = new QGroupBox("Modify");
    modifyLayout = new QVBoxLayout(modifyBox);
    grayscaleButton = new QPushButton("GrayScale", modifyBox);
    rgbButton = new QPushButton("RGB", modifyBox);
    cmykButton = new QPushButton("CMYK", modifyBox);
    modifyLayout->addWidget(grayscaleButton);
    modifyLayout->addWidget(rgbButton);
    modifyLayout->addWidget(cmykButton);
    modifyBox->setLayout(modifyLayout);

    outputBox = new QGroupBox("Output");
    outputLayout = new QVBoxLayout(outputBox);
    saveButton = new QPushButton("Save Image", outputBox);
    outputLayout->addWidget(saveButton);
    outputBox->setLayout(outputLayout);

    rightPanel->addWidget(inputBox, 1);
    rightPanel->addWidget(modifyBox, 8);
    rightPanel->addWidget(outputBox, 1);

   // OPEN IMAGE
    connect(openButton, &QPushButton::clicked, this , &image::slot_openImage);
}

image::~image()
{

}

void image::slot_openImage()
{
        QString imageFileName = QFileDialog::getOpenFileName(this, "Open Image", QDir::homePath(), "Images (*.png *.jpeg *.jpg)");
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
        //qInfo() << "imagePixmap: " << imagePixmap.size();
        //qInfo() << "imageLabel: " << imageLabel->size();
        if (imagePixmap.width() > imageLabel->width() || imagePixmap.height() > imageLabel->height())
        {
            imagePixmap = imagePixmap.scaled(imageLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        //    qInfo() << "imagePixmap: " << imagePixmap.size();
        }
        imageLabel->setPixmap(imagePixmap);
}

void image::slot_modifyImage(modifyMode)
{

}
