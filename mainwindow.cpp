#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;

QImage image,image2;
QString filename;
bool isImageLoaded=false;


// Adds Infrared Effect
void Infra(QImage& image) {
    for (int i = 0; i < image.width(); i++) {
        for (int j = 0; j < image.height(); j++) {
            QRgb pixel = image.pixel(i, j);
            int red = qRed(pixel);
            int green = qGreen(pixel);
            int blue = qBlue(pixel);
            int avg = (red + green + blue) / 3;

            // Modify pixel values to add frame effect
            red = 255;
            green = blue = qMin(avg, 255); // Ensure the value does not exceed 255

            // Set modified pixel values back to the image
            image.setPixel(i, j, qRgb(red, green, blue));
        }
    }
}
void Slimey(QImage& image) {
    for (int i = 0; i < image.width(); i++) {
        for (int j = 0; j < image.height(); j++) {
            QRgb pixel = image.pixel(i, j);
            int red = qRed(pixel);
            int green = qGreen(pixel);
            int blue = qBlue(pixel);
            int avg = (red + green + blue) / 3;

            // Modify pixel values to add frame effect
            green=255;
            red=blue= qMin(avg, 255); // Ensure the value does not exceed 255

            // Set modified pixel values back to the image
            image.setPixel(i, j, qRgb(red, green, blue));
        }
    }
}
// Adds Purple Hue
void Purple(QImage& image) {
    for (int i = 0; i < image.width(); i++) {
        for (int j = 0; j < image.height(); j++) {
            QRgb pixel = image.pixel(i, j);

            // Extract the RGB components
            int red = qRed(pixel);
            int green = qGreen(pixel);
            int blue = qBlue(pixel);

            // Dims Green Color
            green = static_cast<int>(green * 0.8);

            // Enhance Red and Blue colors
            red = qMin(static_cast<int>(red * 1.3), 255);
            blue = qMin(static_cast<int>(blue * 1.3), 255);

            // Set the modified pixel values back to the image
            image.setPixel(i, j, qRgb(red, green, blue));
        }
    }
}
// Adds Yellow Hue
void Yellow(QImage& image) {
    for (int i = 0; i < image.width(); i++) {
        for (int j = 0; j < image.height(); j++) {
            QRgb pixel = image.pixel(i, j);

            // Extract the RGB components
            int red = qRed(pixel);
            int green = qGreen(pixel);
            int blue = qBlue(pixel);

            // Dims Blue color and takes smaller value between the two
            blue = static_cast<int>(blue * 0.8);

            // Enhance Red and Green colors and takes smaller value between the two
            red = qMin(static_cast<int>(red * 1.3), 255);
            green = qMin(static_cast<int>(green * 1.3), 255);

            // Set the modified pixel values back to the image
            image.setPixel(i, j, qRgb(red, green, blue));
        }
    }
}

// Inverts image colors
void Inverted(QImage& image){
    for(int i=0;i<image.width();i++){
        for(int j=0;j<image.height();j++){
            QRgb pixel=(image.pixel(i,j));
            int red=255-qRed(pixel);
            int green=255-qGreen(pixel);
            int blue=255-qBlue(pixel);

            image.setPixel(i,j,qRgb(red,green,blue));
        }
    }
}
// Blurs Image
void Blur(QImage& image) {
    QImage blur(image.width() - 22, image.height() - 22, QImage::Format_RGB32);

    // Loop through the image excluding borders to apply the blur
    for (int i = 11; i < image.width() - 11; i++) {
        for (int j = 11; j < image.height() - 11; j++) {
            int red = 0, green = 0, blue = 0;

            // Accumulate pixel values in a 11x11 neighborhood
            for (int x = -5; x <= 5; x++) {
                for (int y = -5; y <= 5; y++) {
                    QRgb pixel = image.pixel(i + x, j + y);
                    red += qRed(pixel);
                    green += qGreen(pixel);
                    blue += qBlue(pixel);
                }
            }

            // Calculate average pixel values
            red /= 121;
            green /= 121;
            blue /= 121;

            // Assign the average value to the corresponding pixel in the blur image
            blur.setPixelColor(i - 11, j - 11, QColor(red, green, blue));
        }
    }

    // Update the original image with the blur image
    image = blur;
}

void blackWhite(QImage& image){
    for (int i = 0; i < image.width(); ++i) {
        for (int j = 0; j < image.height(); ++j) {
            unsigned int avg = 0;
            // get the sum of RGB colours for each pixel
            QRgb pixel = image.pixel(i, j);
            int red = qRed(pixel);
            int green = qGreen(pixel);
            int blue = qBlue(pixel);
            avg = (red + green + blue) / 3;
            // if the average is greater than or equal 155, set the RGB to 255, white colour
            if(avg >= 155) {
                image.setPixel(i, j, qRgb(255, 255, 255));
            }
            // if the average is less than 155, set the RGB to 0, black colour
            else{
                image.setPixel(i, j, qRgb(0, 0, 0));
            }
        }
    }
}

void greyScale(QImage& image){
    // Loop on all pixels of the image
    for (int i = 0; i < image.width(); ++i){
        for (int j = 0; j < image.height(); ++j){
            unsigned int avg = 0;
            // Get the RGB values of the pixel
            QRgb pixel = image.pixel(i, j);
            int red = qRed(pixel);
            int green = qGreen(pixel);
            int blue = qBlue(pixel);
            // Calculate the average of RGB values
            avg =qMin(255,(red + green + blue) / 3);
            // Set the pixel color to the grayscale value
            image.setPixelColor(i, j, QColor(avg, avg, avg));
        }
    }
}

void brightness(QImage& image,double ratio) {
    // Loop on all pixels of the image
    for (int i = 0; i < image.width(); ++i) {
        for (int j = 0; j < image.height(); ++j) {
            // Get the RGB values of the pixel
            QRgb pixel = image.pixel(i, j);
            int red = qRed(pixel);
            int green = qGreen(pixel);
            int blue = qBlue(pixel);
            // Brighten each color channel by 50%
            red = qMin(255, int(red * ratio));
            green = qMin(255, int(green * ratio));
            blue = qMin(255, int(blue * ratio));
            // Set the pixel color with the modified values
            image.setPixelColor(i, j, QColor(red, green, blue));
        }
    }
}
void Pixelate(QImage& image) {
    // Loop through the image with a step size of 22
    for (int i = 0; i < image.width(); i += 22) {
        for (int j = 0; j < image.height(); j += 22) {
            int red = 0, green = 0, blue = 0;
            int count = 0; // To keep track of the number of pixels in the block

            // Accumulate pixel values in a 22x22 block
            for (int x = i; x < qMin(i + 22, image.width()); x++) {
                for (int y = j; y < qMin(j + 22, image.height()); y++) {
                    QRgb pixelValue = image.pixel(x, y);
                    red += qRed(pixelValue);
                    green += qGreen(pixelValue);
                    blue += qBlue(pixelValue);
                    count++;
                }
            }

            // Calculate average pixel values
            red /= count;
            green /= count;
            blue /= count;

            // Assign the average value to the corresponding pixels in the original image
            for (int x = i; x < qMin(i + 22, image.width()); x++) {
                for (int y = j; y < qMin(j + 22, image.height()); y++) {
                    image.setPixelColor(x, y, QColor(red, green, blue));
                }
            }
        }
    }
}
void edge_detection(QImage& image){
    // Convert image to grey scale
    greyScale(image);

    // Kernels for the vertical and horizontal edge detection
    int Gx[3][3] = {{-1, 0, 1},
                    {-2, 0, 2},
                    {-1, 0, 1}};

    int Gy[3][3] = {{-1, -2, -1},
                    {0, 0, 0},
                    {1, 2, 1}};

    // Create a new QImage object to store the edge-detected image
    QImage edgeDetectedImage(image.width(), image.height(), QImage::Format_Grayscale8);

    // Make sure kernels are never out of bounds
    for (int i = 1; i < image.width() - 1; ++i) {
        for (int j = 1; j < image.height() - 1; ++j) {
            int sum_x = 0;
            int sum_y = 0;
            for(int x = -1; x <= 1; x++){
                for(int y = -1; y <= 1; y++) {
                    sum_x += qRed(image.pixel(i + x, j + y)) * Gx[x + 1][y + 1];
                    sum_y += qRed(image.pixel(i + x, j + y)) * Gy[x + 1][y + 1];
                }
            }
            // Calculate the gradient magnitude
            int Grad = static_cast<int>(sqrt(sum_x * sum_x + sum_y * sum_y));

            // Apply threshold to detect edges
            // If the gradient magnitude is greater than 128, the pixel is considered an edge set to white
            // if not set to black
            QRgb edge_value = (Grad < 128) ? qRgb(255, 255, 255) : qRgb(0, 0, 0);
            edgeDetectedImage.setPixel(i, j, edge_value);
        }
    }
    // Swap the new image back as the original image
    image = std::move(edgeDetectedImage);
}
void resizee(QImage& image, double ratio) {
    // Calculate the new width and height of the image
    int newWidth = image.width() * ratio;
    int newHeight = image.height() * ratio;

    // Resize the image
    image = image.scaled(newWidth, newHeight);
}


void Frame(QImage& image, QColor color) {
    QImage image1(image.width() + 50, image.height() + 50, QImage::Format_RGB32);

    // Fill the image1 with the calculated color
    image1.fill(color);

    // Copy the original image into the center of the frame
    int X = (image1.width() - image.width()) / 2;
    int Y = (image1.height() - image.height()) / 2;

    for (int i = 0; i < image.width(); ++i) {
        for (int j = 0; j < image.height(); ++j) {
            image1.setPixelColor(i + X, j + Y, image.pixelColor(i, j));
        }
    }

    // Update the original image with the framed image
    image = image1;
}

// Merge the 2 images with the dimensions of the smaller one
void merge_smaller(QImage& image1, QImage& image2){
    // Create a new image with the width and height of the smaller image
    QImage merged_img(std::min(image1.width(), image2.width()), std::min(image1.height(), image2.height()), QImage::Format_RGB32);

    for (int i = 0; i < merged_img.width(); ++i) {
        for (int j = 0; j < merged_img.height(); ++j) {
            QRgb color1 = image1.pixel(i, j);
            QRgb color2 = image2.pixel(i, j);
            int r1 = qRed(color1);
            int g1 = qGreen(color1);
            int b1 = qBlue(color1);
            int r2 = qRed(color2);
            int g2 = qGreen(color2);
            int b2 = qBlue(color2);
            int r_avg = (r1 + r2) / 2;
            int g_avg = (g1 + g2) / 2;
            int b_avg = (b1 + b2) / 2;
            QColor merged_color(qBound(0, r_avg, 255), qBound(0, g_avg, 255), qBound(0, b_avg, 255));
            merged_img.setPixelColor(i, j, merged_color);
        }
    }
    image1.swap(merged_img);
}

// Function to resize the smaller image as the larger image
QImage resize_merge(const QImage& image, int w, int h){
    double scale_width = static_cast<double>(image.width()) / w;
    double scale_height = static_cast<double>(image.height()) / h;
    QImage resized(w, h, QImage::Format_RGB32);
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            int a = qBound(0, qRound(i * scale_width), image.width() - 1);
            int b = qBound(0, qRound(j * scale_height), image.height() - 1);
            QRgb color = image.pixel(a, b);
            resized.setPixelColor(i, j, QColor(color));
        }
    }
    return resized;
}

// Merge the 2 images with the dimensions of the larger one
void merge_bigger(QImage& image1, QImage& image2){
    int new_w = max(image1.width(), image2.width());
    int new_h = max(image1.height(), image2.height());
    image1 = resize_merge(image1, new_w, new_h);
    image2 = resize_merge(image2, new_w, new_h);
    QImage merged_img(new_w, new_h, QImage::Format_RGB32);

    for (int i = 0; i < merged_img.width(); ++i) {
        for (int j = 0; j < merged_img.height(); ++j) {
            QRgb color1 = image1.pixel(i, j);
            QRgb color2 = image2.pixel(i, j);
            int r_avg = (qRed(color1) + qRed(color2)) / 2;
            int g_avg = (qGreen(color1) + qGreen(color2)) / 2;
            int b_avg = (qBlue(color1) + qBlue(color2)) / 2;
            QColor merged_color(qBound(0, r_avg, 255), qBound(0, g_avg, 255), qBound(0, b_avg, 255));
            merged_img.setPixelColor(i, j, merged_color);
        }
    }
    image1.swap(merged_img);
}

void Rotate(QImage& image, int degree) {
    // Creates a new image with rotated dimensions
    QImage rotatedImage((degree == 90 || degree == 270) ? image.height() : image.width(),
                        (degree == 90 || degree == 270) ? image.width() : image.height(),
                        QImage::Format_RGB32);

    // Loop through each pixel in the original image
    for (int i = 0; i < image.width(); ++i) {
        for (int j = 0; j < image.height(); ++j) {
            // Calculate the new coordinates for the rotated image
            int newI, newJ;
            if (degree == 90) {
                newI = j;
                newJ = image.width() - 1 - i;
            } else if (degree == 180) {
                newI = image.width() - 1 - i;
                newJ = image.height() - 1 - j;
            } else if (degree == 270) {
                newI = image.height() - 1 - j;
                newJ = i;
            }
            // Copy the pixel values from the original image to the rotated image
            rotatedImage.setPixelColor(newI, newJ, image.pixelColor(i, j));
        }
    }
    // Assign the rotated image to the original image
    image = move(rotatedImage);
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->image2->setVisible(false);
    ui->load2->setVisible(false);
    ui->typebox->setVisible(false);
    ui->ratio->setVisible(false);
    ui->ratiotxt->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Function to Load Image
void MainWindow::on_loadbut_clicked()
{
    // Opens a file dialog to select an image
    filename = QFileDialog::getOpenFileName(this, tr("Select an image"), "", tr("Images (*.png *.jpg *.bmp *.jpeg)"));


    if (!filename.isEmpty()) {


        bool valid = image.load(filename);

        if (valid) {
            // Sets the ratio of image to fit in the Box
            image = image.scaled(image.size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

            ui->image->setPixmap(QPixmap::fromImage(image));

            isImageLoaded=true;

            ui->Qmessage->setText("Image Loaded Successfully!");
        }
        else {
            ui->Qmessage->setText("Image Failed to Load.");
        }
    }
    else {
        ui->Qmessage->setText("No Image Selected.");
    }
}
    void MainWindow::on_load2_clicked()
    {
        // Opens a file dialog to select an image
        filename = QFileDialog::getOpenFileName(this, tr("Select an image"), "", tr("Images (*.png *.jpg *.bmp *.jpeg)"));


        if (!filename.isEmpty()) {


            bool valid2 = image2.load(filename);

            if (valid2) {
                // Sets the ratio of image to fit in the Box
                image2 = image2.scaled(image2.size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

                ui->image2->setPixmap(QPixmap::fromImage(image2));

                isImageLoaded=true;

                ui->Qmessage->setText("Image Loaded Successfully!");
            }
            else {
                ui->Qmessage->setText("Image Failed to Load.");
            }
        }
        else {
            ui->Qmessage->setText("No Image Selected.");
        }
    }



void MainWindow::on_savebut_clicked()
{
    filename = QFileDialog::getSaveFileName(this,"","",tr("Images (*.png *.jpg *.bmp *.jpeg)"));

    // If the user cancels the dialog or doesn't choose a file, return
    if(filename.isEmpty())
        ui->Qmessage->setText("No Image Selected.");

    // Get the pixmap from the label
    QPixmap pixmap = ui->image->pixmap();

    // Check if the label has a pixmap
    if(pixmap.isNull()) {
        return;
    }

    if(pixmap.save(filename)){
        ui->Qmessage->setText("Image Saved Successfully!");
    }
    else
        ui->Qmessage->setText("Failed to Save Image.");

}


void MainWindow::on_Apply_clicked()
{
     if(isImageLoaded) {
    switch(ui->Filterbox->currentIndex())
         {
        case 1:
           Infra(image);
           break;

        case 2: Purple(image);
            break;

        case 3: Yellow(image);
            break;

        case 4: Inverted(image);
            break;

        case 5:
        {
            QColor color = QColorDialog::getColor(Qt::white, this, "Choose Color");
            if (color.isValid())
                Frame(image, color);
        }
            break;

        case 6: Blur(image);
            break;

        case 7: blackWhite(image);
            break;

        case 8: greyScale(image);
            break;

        case 9: brightness(image,ui->ratio->value());
            break;

        case 10: Pixelate(image);
            break;

        case 11:
            if(ui->typebox->currentIndex()==0) image = image.mirrored(false, true);

            else if(ui->typebox->currentIndex()==1) image = image.mirrored(true, false);

            break;

        case 12:if(ui->typebox->currentIndex()==1)Rotate(image,90);
           else if(ui->typebox->currentIndex()==2)Rotate(image,180);
           else if(ui->typebox->currentIndex()==3)Rotate(image,270);
           break;
        case 13:
            image=image.transformed(QTransform().shear(0.4,0));
            image = image.mirrored(true, false);
            break;
        case 14:
            edge_detection(image);
            break;
        case 15:
            resizee(image,ui->ratio->value());
            break;
        case 16: if(ui->typebox->currentIndex()==0)merge_smaller(image,image2);
            else if(ui->typebox->currentIndex()==1)merge_bigger(image,image2);
            break;
        case 17: // Crop
            break;
        case 18: // Oil
            break;
        case 19: // TV
            break;

        case 20: Slimey(image);
            break;
        default:
            ui->Qmessage->setText("Please choose a filter!");
            break;
        }

        ui->image->setPixmap(QPixmap::fromImage(image));
        ui->Qmessage->setText("Filter Applied Successfully!");
    }
     else
         ui->Qmessage->setText("Please load an image to apply filters!");

}

void MainWindow::on_Filterbox_activated(int index)
{
    QString selectedText = ui->Filterbox->itemText(index);

    if (index == 9)
    {
        ui->ratio->setVisible(true);
        ui->ratiotxt->setVisible(true);
    }
    else if (index == 11)
    {
        ui->typebox->clear();
        ui->typebox->addItem("Vertical");
        ui->typebox->addItem("Horizontal");
        ui->typebox->setVisible(true);
    }
    else if (index == 12){
        ui->typebox->clear();
        ui->typebox->addItem("Select a Degree");
        ui->typebox->addItem("90");
        ui->typebox->addItem("180");
        ui->typebox->addItem("270");
        ui->typebox->setVisible(true);
    }
    else if (index == 15){
        ui->ratio->setVisible(true);
        ui->ratiotxt->setVisible(true);
    }
    else if (index == 16){
        ui->typebox->clear();
        ui->typebox->addItem("Merge Bigger Ratio");
        ui->typebox->addItem("Merge Smaller Ratio");
        ui->typebox->setVisible(true);
        ui->image2->setVisible(true);
        ui->load2->setVisible(true);
    }
    // Hides the buttons
    else
    {
        ui->typebox->setVisible(false);
        ui->ratio->setVisible(false);
        ui->ratiotxt->setVisible(false);
        ui->image2->setVisible(false);
        ui->load2->setVisible(false);
    }
}



void MainWindow::on_typebox_activated(int index)
{

}


void MainWindow::on_typebox_destroyed()
{

}


void MainWindow::on_Filterbox_currentIndexChanged(int index)
{

}


void MainWindow::on_ratio_valueChanged(double arg1)
{

}



