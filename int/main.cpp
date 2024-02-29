
#include "mainwindow.h"

#include <QApplication>
#include <iostream>
#include <foo/exec.h>
// #include <vtk-9.3/vtkSmartPointer.h>


int main(int argc, char *argv[])
{
    std::cout <<"Hihi";
    // QApplication a(argc, argv);
    Exec exec;
    exec.calculate(1,2);
    // MainWindow w;
    // w.show();
    // return a.exec();
}
