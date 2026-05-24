#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QTableWidgetItem>
#include <QMessageBox>
#include <QString>
#include <QStringList>
#include <QHeaderView>
#include <QAbstractSpinBox>

#include <format>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow){

    ui->setupUi(this);

    ui->ContainerTypeBox->clear();
    ui->ContainerTypeBox->addItems({"DynamicArray", "LinkedList", "ArraySequence", "ListSequence"});

    ui->MethodBox->clear();
    ui->MethodBox->addItems({"get", "set", "get_diag_count", "get_matrix_size", "get_inverse_matrix", "frobenius_norm", "multiply_by_scalar", "summary_with_scalar", "summary_with_matrix", "map", "where", "reduce"});

    ui->MatrixSizeBox->setMinimum(1);
    ui->MatrixSizeBox->setMaximum(100);
    ui->MatrixSizeBox->setValue(5);
    ui->MatrixSizeBox->setMinimumWidth(75);
    ui->MatrixSizeBox->setMaximumWidth(90);
    ui->MatrixSizeBox->setAlignment(Qt::AlignCenter);

    ui->DiagCountBox->setMinimum(1);
    ui->DiagCountBox->setMaximum(199);
    ui->DiagCountBox->setSingleStep(2);
    ui->DiagCountBox->setValue(1);
    ui->DiagCountBox->setMinimumWidth(75);
    ui->DiagCountBox->setMaximumWidth(90);
    ui->DiagCountBox->setAlignment(Qt::AlignCenter);

    ui->ScalarInput->setPlaceholderText("scalar или: row col value");

    ui->MatrixTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->MatrixTable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

}

MainWindow::~MainWindow(){

    delete ui;

}

template <template <typename> class Container> DiagonalMatrix<Container, double> MainWindow::create_zero_matrix(int n, int diag_count){

    int side = (diag_count - 1) / 2;
    int count = n + ((n - 1) + (n - side)) * side;

    Container<double> buffer;

    for (int i = 0; i < count; ++i){

        buffer.append(0.0);

    }

    return DiagonalMatrix<Container, double>(buffer, count, diag_count);

}

void MainWindow::on_CreateMatrixButton_clicked(){

    create_matrix_from_ui();
    fill_table_from_matrix();
    update_info("matrix has been created");

}

void MainWindow::create_matrix_from_ui(){

    int n = ui->MatrixSizeBox->value();
    int diag_count = ui->DiagCountBox->value();

    if (diag_count % 2 == 0){

        QMessageBox::warning(this, "Error", "diag_count must be odd: 1, 3, 5...");
        return;

    }

    if (diag_count > 2 * n - 1){

        QMessageBox::warning(this, "Error", "Too many diagonals for this matrix size");
        return;

    }

    QString container_type = ui->ContainerTypeBox->currentText();

    if (container_type == "DynamicArray"){

        matrix = create_zero_matrix<DynamicArray>(n, diag_count);

    }
    else if (container_type == "LinkedList"){

        matrix = create_zero_matrix<LinkedList>(n, diag_count);

    }
    else if (container_type == "ArraySequence"){

        matrix = create_zero_matrix<ArraySequence>(n, diag_count);

    }
    else if (container_type == "ListSequence"){

        matrix = create_zero_matrix<ListSequence>(n, diag_count);

    }
    else{

        QMessageBox::warning(this, "Error", "Unknown container type");
        return;

    }

    matrix_created = true;

}

void MainWindow::fill_table_from_matrix(){

    if (matrix_created == 0){

        return;

    }

    table_is_updating = true;
    int n = std::visit([](const auto &mtrx){return static_cast<int>(mtrx.get_matrix_size());}, matrix);

    ui->MatrixTable->clear();
    ui->MatrixTable->setRowCount(n);
    ui->MatrixTable->setColumnCount(n);

    for (int i = 0; i < n; ++i){

        ui->MatrixTable->setHorizontalHeaderItem(i, new QTableWidgetItem(QString::number(i)));
        ui->MatrixTable->setVerticalHeaderItem(i, new QTableWidgetItem(QString::number(i)));

    }

    std::visit([&](const auto &mtrx){

        for (int i = 0; i < n; ++i){

            for (int j = 0; j < n; ++j){

                double value = mtrx.get(i, j);

                QTableWidgetItem *item = new QTableWidgetItem(QString::number(value));
                item->setTextAlignment(Qt::AlignCenter);

                ui->MatrixTable->setItem(i, j, item);

            }

        }

    }, matrix);

    table_is_updating = false;

}

void MainWindow::on_MatrixTable_cellChanged(int row, int column){

    if ((matrix_created == 0) || (table_is_updating == 1)){

        return;

    }

    update_matrix_from_cell(row, column);
    update_info("cell [" + QString::number(row) + "][" + QString::number(column) + "] changed");;

}

void MainWindow::update_matrix_from_cell(int row, int column){

    QTableWidgetItem *item = ui->MatrixTable->item(row, column);

    if (item == nullptr){

        return;

    }

    bool ok = false;
    double value = item->text().toDouble(&ok);

    if (ok == 0){

        QMessageBox::warning(this, "Error", "Cell value must be number");

        table_is_updating = true;
        std::visit([&](const auto &mtrx){item->setText(QString::number(mtrx.get(row, column)));}, matrix);
        table_is_updating = false;

        return;

    }

    try{

        std::visit([&](auto &mtrx){mtrx.set(row, column, value);}, matrix);

    }
    catch (const std::exception &msg){

        QMessageBox::warning(this, "Error", msg.what());

    }

}

void MainWindow::on_RunButton_clicked(){

    if (matrix_created == 0){

        QMessageBox::warning(this, "Error", "Create matrix first");
        return;

    }

    QString method = ui->MethodBox->currentText();

    try{

        if (method == "multiply_by_scalar"){

            bool ok = false;
            double scalar = ui->ScalarInput->text().toDouble(&ok);

            if (ok == 0){

                QMessageBox::warning(this, "Error", "For multiply_by_scalar enter scalar");
                return;

            }

            std::visit([&](auto &mtrx){mtrx = mtrx.multiply_by_scalar(scalar);}, matrix);

            fill_table_from_matrix();
            update_info(QString::fromStdString(std::format("matrix has been multiplied by {}", scalar)));


        }
        else if (method == "summary_with_scalar"){

            bool ok = false;
            double scalar = ui->ScalarInput->text().toDouble(&ok);

            if (!ok){

                QMessageBox::warning(this, "Error", "For summary_with_scalar enter scalar");
                return;

            }

            std::visit([&](auto &mtrx){mtrx = mtrx.summary_with_scalar(scalar);}, matrix);

            fill_table_from_matrix();
            update_info(QString::fromStdString(std::format("matrix has been summed by {}", scalar)));

        }
        else if (method == "frobenius_norm"){

            double norm = std::visit([](const auto &mtrx){return mtrx.frobenius_norm();}, matrix);

            ui->OutputText->setText("frobenius_norm = " + QString::number(norm));

        }
        else if (method == "get_matrix_size"){

            int size = std::visit([](const auto &mtrx){return static_cast<int>(mtrx.get_matrix_size());}, matrix);

            ui->OutputText->setText("matrix_size = " + QString::number(size));

        }
        else if (method == "get_diag_count"){

            int diag_count = std::visit([](const auto &mtrx){return static_cast<int>(mtrx.get_diag_count());}, matrix);

            ui->OutputText->setText("diag_count = " + QString::number(diag_count));

        }
        else if (method == "get_inverse_matrix"){

            std::visit([&](auto &mtrx){mtrx = mtrx.get_inverse_matrix();}, matrix);

            fill_table_from_matrix();
            update_info("matrix has been inversed");

        }
        else if (method == "get"){

            QStringList values = ui->ScalarInput->text().split(" ", Qt::SkipEmptyParts);

            if (values.size() != 2){

                QMessageBox::warning(this, "Error", "For get enter: row column");
                return;

            }

            bool ok1 = false;
            bool ok2 = false;

            int row = values[0].toInt(&ok1);
            int column = values[1].toInt(&ok2);

            if ((ok1 == 0) || (ok2 == 0)){

                QMessageBox::warning(this, "Error", "row and column must be int");
                return;

            }

            double res = std::visit([&](const auto &mtrx){return mtrx.get(row, column);}, matrix);

            ui->OutputText->setText(QString::fromStdString(std::format("matrix[ {} ][ {} ] = {}", row, column, res)));

        }
        else if (method == "set"){

            QStringList values = ui->ScalarInput->text().split(" ", Qt::SkipEmptyParts);

            if (values.size() != 3){

                QMessageBox::warning(this, "Error", "For set enter: row column value");
                return;

            }

            bool ok1 = false;
            bool ok2 = false;
            bool ok3 = false;

            int row = values[0].toInt(&ok1);
            int column = values[1].toInt(&ok2);
            double value = values[2].toDouble(&ok3);

            if ((ok1 == 0) || (ok2 == 0) || (ok3 == 0)){

                QMessageBox::warning(this, "Error", "Wrong format. Need: row column value");
                return;

            }

            std::visit([&](auto &mtrx){mtrx.set(row, column, value);}, matrix);

            fill_table_from_matrix();
            update_info(QString::fromStdString(std::format("element {} has been set on (row, column) : ({}, {})", value, row, column)));

        }
        else if (method == "summary_with_matrix"){

            QMessageBox::information(this, "Info", "summary_with_matrix needs second matrix");

        }
        else if ((method == "map") || (method == "where") || (method == "reduce")){

            QMessageBox::information(this, "Info", "");

        }
        else{

            QMessageBox::warning(this, "Error", "Unknown method");

        }

    }
    catch (const std::exception &msg){

        ui->OutputText->setText(QString("Error: ") + msg.what());

    }

}

void MainWindow::update_info(const QString &last_operation){

    if (matrix_created == 0){

        ui->OutputText->setText("No matrix");

        return;

    }

    int matrix_size = 0;
    int diag_count = 0;

    std::visit([&](const auto &mtrx){matrix_size = mtrx.get_matrix_size(); diag_count = mtrx.get_diag_count();}, matrix);

    if (last_operation != ""){

        ui->OutputText->setText(QString::fromStdString(std::format("Container: {}\nSize: {}\nDiagonals: {}\nLast operation: {}\n", ui->ContainerTypeBox->currentText().toStdString(), matrix_size, diag_count, last_operation.toStdString())));

    }
    else{

        ui->OutputText->setText(QString::fromStdString(std::format("Container: {}\nSize: {}\nDiagonals: {}\n", ui->ContainerTypeBox->currentText().toStdString(), matrix_size, diag_count)));

    }

}