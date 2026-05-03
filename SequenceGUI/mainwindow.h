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

#include <memory>

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

        std::unique_ptr<Sequence<double>> arr_seq;
        std::unique_ptr<Sequence<double>> list_seq;
        std::unique_ptr<Sequence<double>> imm_arr_seq;
        std::unique_ptr<Sequence<double>> imm_list_seq;
        Sequence<double> *curr_seq();

        void update_output(const Sequence<double> *seqq, QString *res_txt) const;
        void replace_current_sequence(Sequence<double> *res);
        void add_history(const QString &operation);

    private slots:

        void on_SequenceTypeBox_clicked(int index);
        void on_executeButton_clicked();

    public:

        explicit MainWindow(QWidget *parent = nullptr);
        ~MainWindow() override;

};
#endif
