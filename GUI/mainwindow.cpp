#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPainter>
#include <QColor>
#include <QRectF>
#include <QVBoxLayout>
#include <QMessageBox>

#include <algorithm>
#include <cmath>

#include "Heat.h"

HeatCanvas::HeatCanvas(QWidget *parent) : QWidget(parent){}

void HeatCanvas::set_layers(const DynamicArray<ArraySequence<double>> &new_layers){

    layers = new_layers;
    update();

}

void HeatCanvas::paintEvent(QPaintEvent *event){

    Q_UNUSED(event);

    QPainter painter(this);

    size_t time_count = layers.get_size();

    if (time_count == 0){

        painter.drawText(rect(), Qt::AlignCenter, "No data");
        return;

    }

    size_t x_count = layers[0].get_length();

    if (x_count == 0){

        painter.drawText(rect(), Qt::AlignCenter, "No data");
        return;

    }

    double min_value = layers[0][0];
    double max_value = layers[0][0];

    for (size_t t = 0; t < time_count; ++t){

        for (size_t x = 0; x < x_count; ++x){

            min_value = std::min(min_value, layers[t][x]);
            max_value = std::max(max_value, layers[t][x]);

        }

    }

    double cell_w = (double)(width() / x_count);
    double cell_h = (double)(height() / time_count);

    for (size_t t = 0; t < time_count; ++t){

        for (size_t x = 0; x < x_count; ++x){

            double value = layers[t][x];
            double normalized = 0.0;

            if (max_value != min_value){

                normalized = (value - min_value) / (max_value - min_value);

            }

            int red = 255 * normalized;
            int blue = 255 * (1 - normalized);

            painter.fillRect(QRectF(x * cell_w, t * cell_h, cell_w + 1, cell_h + 1), QColor(red, 0, blue));

        }

    }

}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){

    ui->setupUi(this);
    canvas = new HeatCanvas(ui->canvasPlace);

    QVBoxLayout *canvasLayout = new QVBoxLayout(ui->canvasPlace);
    canvasLayout->setContentsMargins(0, 0, 0, 0);
    canvasLayout->addWidget(canvas);

    ui->NBox->setRange(10, 300);
    ui->NBox->setValue(80);
    ui->NBox->setMinimumWidth(80);

    ui->stepsBox->setRange(1, 450);
    ui->stepsBox->setValue(200);
    ui->stepsBox->setMinimumWidth(80);

    ui->aBox->setRange(0.01, 10.0);
    ui->aBox->setValue(1.0);
    ui->aBox->setMinimumWidth(80);

    ui->tauBox->setDecimals(8);
    ui->tauBox->setRange(0.000001, 1.0);
    ui->tauBox->setValue(0.00005);
    ui->tauBox->setMinimumWidth(80);

    ui->leftBox->setRange(-1000.0, 1000.0);
    ui->leftBox->setValue(0.0);
    ui->leftBox->setMinimumWidth(80);

    ui->rightBox->setRange(-1000.0, 1000.0);
    ui->rightBox->setValue(0.0);
    ui->rightBox->setMinimumWidth(80);

    ui->hotBox->setRange(-1000.0, 1000.0);
    ui->hotBox->setValue(100.0);
    ui->hotBox->setMinimumWidth(100);

    connect(ui->calcButton, &QPushButton::clicked, this, &MainWindow::calculate);

    calculate();

}

MainWindow::~MainWindow(){

    delete ui;

}

void MainWindow::calculate(){

    try{

        size_t N = ui->NBox->value();
        size_t steps = ui->stepsBox->value();

        double a = ui->aBox->value();
        double tau = ui->tauBox->value();
        double left_t = ui->leftBox->value();
        double right_t = ui->rightBox->value();
        double hot_t = ui->hotBox->value();
        double h = 1.0 / N;
        double sigma = a * a * tau / (h * h);

        ArraySequence<double> start_layer;

        for (size_t i = 0; i <= N; ++i){

            if (i == 0){

                start_layer.append(left_t);

            }
            else if (i == N){

                start_layer.append(right_t);

            }
            else if (i > N / 3 && i < 2 * N / 3){

                start_layer.append(hot_t);

            }
            else{

                start_layer.append(0.0);

            }

        }

        auto layers = solve_heat_equation<ArraySequence>(start_layer, steps, left_t, right_t, sigma);
        canvas->set_layers(layers);

    }
    catch (const std::exception &error){

        QMessageBox::warning(this, "Error", error.what());

    }

}