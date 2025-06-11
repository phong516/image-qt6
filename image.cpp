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
    revertButton = new QPushButton("Revert", modifyBox);
    grayscaleButton = new QPushButton("GrayScale", modifyBox);
    rgbButton = new QPushButton("RGB", modifyBox);
    cmykButton = new QPushButton("CMYK", modifyBox);
    modifyLayout->addWidget(revertButton);
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

    connect(revertButton, &QPushButton::clicked, this, [=]() {slot_modifyImage(modifyMode::raw);});
    connect(grayscaleButton, &QPushButton::clicked, this, [=]() {slot_modifyImage(modifyMode::grayscale);});
    connect(rgbButton, &QPushButton::clicked, this, [=]() {slot_modifyImage(modifyMode::rgb);});
    connect(cmykButton, &QPushButton::clicked, this, [=]() {slot_modifyImage(modifyMode::cmyk);});

    connect(saveButton, &QPushButton::clicked, this, &image::slot_saveImage);
}

image::~image()
{

}

void image::display(QImage * image)
{
    QPixmap pixmap = QPixmap::fromImage(*image);
        //qInfo() << "pixmap: " << pixmap.size();
        //qInfo() << "imageLabel: " << imageLabel->size();
        if (pixmap.width() > imageLabel->width() || pixmap.height() > imageLabel->height())
        {
            pixmap = pixmap.scaled(imageLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        //    qInfo() << "pixmap: " << pixmap.size();
        }
        imageLabel->setPixmap(pixmap);
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

        QImage image(imageFileName);
        if (image.isNull())
        {
            qWarning("Image file is invalid");
            return;
        }

        if (pr_image != nullptr)
        {
            delete pr_image;
        }
        pr_image = new QImage(image);

        display(pr_image);
}

void image::slot_saveImage()
{
    QString saveFileName = QFileDialog::getSaveFileName(this, "Save Image", QDir::homePath(), "Images (*.png *.jpeg *.jpg");
    imageLabel->pixmap().save(saveFileName);
}
void image::slot_modifyImage(modifyMode mode)
{
    if (imageLabel->pixmap().isNull())
    {
        return;
    }
    QImage modifiedImage;
    QImage::Format format;
    switch (mode)
    {
    case modifyMode::raw:
        display(pr_image);
        return;
    case modifyMode::grayscale:
        format = QImage::Format_Grayscale8;
        break;
    case modifyMode::rgb:
        format = QImage::Format_RGB16;
        break;
    case modifyMode::cmyk:
        format = QImage::Format_CMYK8888;
        break;
    }

    modifiedImage = pr_image->convertToFormat(format);
    display(&modifiedImage);
}

