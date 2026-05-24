#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <variant>

#include "ArraySequence.h"
#include "ListSequence.h"
#include "DynamicArray.h"
#include "LinkedList.h"
#include "DiagonalMatrix.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow{

    Q_OBJECT

    private:

        Ui::MainWindow *ui;

        using MatrixDynamicArray = DiagonalMatrix<DynamicArray, double>;
        using MatrixLinkedList = DiagonalMatrix<LinkedList, double>;
        using MatrixArraySequence = DiagonalMatrix<ArraySequence, double>;
        using MatrixListSequence = DiagonalMatrix<ListSequence, double>;

        std::variant<MatrixDynamicArray, MatrixLinkedList, MatrixArraySequence, MatrixListSequence> matrix;

        bool matrix_created = false;
        bool table_is_updating = false;

        void create_matrix_from_ui();
        void fill_table_from_matrix();
        void update_matrix_from_cell(int row, int column);
        void update_info(const QString &last_operation = "");

        template <template <typename> class Container>
        DiagonalMatrix<Container, double> create_zero_matrix(int n, int diag_count);

    private slots:

        void on_CreateMatrixButton_clicked();
        void on_MatrixTable_cellChanged(int row, int column);
        void on_RunButton_clicked();

    public:

        explicit MainWindow(QWidget *parent = nullptr);
        ~MainWindow() override;
};

#endif