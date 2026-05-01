#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <DynamicArray.h>
#include <LinkedList.h>
#include <Sequence.h>
#include <ArraySequence.h>
#include <ListSequence.h>
#include <ImmutableArraySequence.h>
#include <ImmutableListSequence.h>

#include <memory.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    private:

        Ui::MainWindow *ui;

        std::unique_ptr<Sequence<double>> seq;

        void create_sequence();
        void update_output(const Sequence<double> *seqq) const;
        void replace_sequence(Sequence<double> *res);

    private slots:

        void on_sequenceTypeBox_clicked();
        void on_executeButton_clicked();

    public:

        explicit MainWindow(QWidget *parent = nullptr);
        ~MainWindow() override;

};
#endif
