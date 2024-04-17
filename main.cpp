/*
 * FCAI Structured Programming  2024 - Assignment 3
 *
 * CS112_A3_Part3_18_2023620.cpp
 *
 * Program Description: The Mini Photoshop program is designed to perform various image processing
 * tasks on images loaded into the application of the images according to their preferences.
 *
 * Last Modification Date: 17/4/2024
 *
 * Mohamed Mahmoud Bayoumi Mohamed ElGabry , 20230620 , Section 18 , mohammed.elgabry7@gmail.com
 *
 * Teaching Assistant: Ahmad Lotfy
 *
 * Github link: https://github.com/Mohamedelgabryy1/Photoshop-GUI
 *
*/
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
