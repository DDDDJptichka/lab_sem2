#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QWidget>

#include "DynamicArray.h"
#include "ArraySequence.h"

QT_BEGIN_NAMESPACE
namespace Ui {class MainWindow;}
QT_END_NAMESPACE

class HeatCanvas : public QWidget{

    Q_OBJECT

    private:

        DynamicArray<ArraySequence<double>> layers;

    public:

        HeatCanvas(QWidget *parent = nullptr);

        void set_layers(const DynamicArray<ArraySequence<double>> &new_layers);

    protected:

        void paintEvent(QPaintEvent *event) override;

};

class MainWindow : public QMainWindow{

    Q_OBJECT

    private:

        Ui::MainWindow *ui;
        HeatCanvas *canvas;

        void calculate();

    public:

        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

};

#endif