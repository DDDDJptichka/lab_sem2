#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow){

    ui->setupUi(this);
    ui->SequenceTypeBox->addItems({"ArraySequence", "ListSequence", "ImmutableArraySequence", "ImmutableListSequence"});
    ui->MethodTypeBox->addItems({"append", "prepend", "insert_at", "get", "get_first", "get_last", "get_length", "print", "get_sub_sequence", "concat"});
    ui->DataTypeBox->addItems({"double"});

    arr_seq = std::make_unique<ArraySequence<double>>();
    list_seq = std::make_unique<ListSequence<double>>();
    imm_arr_seq = std::make_unique<ImmutableArraySequence<double>>();
    imm_list_seq = std::make_unique<ImmutableListSequence<double>>();

    update_output(curr_seq());

}

MainWindow::~MainWindow(){

    delete ui;

}

Sequence<double> *MainWindow::curr_seq(){

    QString seq_kind = ui->SequenceTypeBox->currentText();

    if (seq_kind == "ArraySequence"){

        return arr_seq.get();

    }
    else if (seq_kind == "ListSequence"){

        return list_seq.get();

    }
    else if (seq_kind == "ImmutableArraySequence"){

        return imm_arr_seq.get();

    }
    else if (seq_kind == "ImmutableListSequence"){

        return imm_list_seq.get();

    }

    return nullptr;

}

void MainWindow::update_output(const Sequence<double> *seqq) const{

    if (seqq == nullptr){

        ui->OutputText->setText("No sequence");
        return;

    }

    QString text = "[ ";

    for (size_t i = 0; i < seqq->get_length(); ++i){

        text += "  " + QString::number(seqq->get(i));

    }

    text += "  ]";
    ui->OutputText->setText(text);

}

void MainWindow::replace_current_sequence(Sequence<double> *res){

    QString seq_kind = ui->SequenceTypeBox->currentText();

    if (seq_kind == "ArraySequence"){

        if (res != arr_seq.get()){

            arr_seq.reset(res);

        }

    }
    else if (seq_kind == "ListSequence"){

        if (res != list_seq.get()){

            list_seq.reset(res);

        }

    }
    else if (seq_kind == "ImmutableArraySequence"){

        if (res != imm_arr_seq.get()){

            imm_arr_seq.reset(res);

        }

    }
    else if (seq_kind == "ImmutableListSequence"){

        if (res != imm_list_seq.get()){

            imm_list_seq.reset(res);

        }

    }

}


void MainWindow::on_sequenceTypeBox_clicked(int){

    update_output(curr_seq());

}

void MainWindow::on_executeButton_clicked(){

    Sequence<double> *seq = curr_seq();

    if (seq == nullptr){
        return;
    }

    QString method = ui->MethodTypeBox->currentText();

    try{

        if (method == "append"){

            double value = ui->valueEdit->text().toDouble();
            Sequence<double> *res = seq->append(value);

            replace_current_sequence(res);
            update_output(curr_seq());

        }
        else if (method == "prepend"){

            double value = ui->valueEdit->text().toDouble();
            Sequence<double> *res = seq->prepend(value);

            replace_current_sequence(res);
            update_output(curr_seq());

        }
        else if (method == "insert_at"){

            double value = ui->valueEdit->text().toDouble();
            int index = ui->indexEdit->text().toInt();
            Sequence<double> *res = seq->insert_at(value, index);

            replace_current_sequence(res);
            update_output(curr_seq());

        }
        else if (method == "get"){

            int index = ui->indexEdit->text().toInt();

            ui->OutputText->setText(QString::number(seq->get(index)));

        }
        else if (method == "get_first"){

            ui->OutputText->setText(QString::number(seq->get_first()));

        }
        else if (method == "get_last"){

            ui->OutputText->setText(QString::number(seq->get_last()));

        }
        else if (method == "get_length"){

            ui->OutputText->setText(QString::number(seq->get_length()));

        }
        else if (method == "get_sub_sequence"){

            int start_index = ui->startEdit->text().toInt();
            int end_index = ui->endEdit->text().toInt();

            std::unique_ptr<Sequence<double>> res(seq->get_sub_sequence(start_index, end_index));
            update_output(res.get());

        }
        else if (method == "concat"){

            std::unique_ptr<Sequence<double>> other = std::make_unique<ArraySequence<double>>();

            QString input = ui->valueEdit->text();
            QStringList values = input.split(" ", Qt::SkipEmptyParts);

            for (const QString &value : values){

                Sequence<double> *res = other->append(value.toDouble());

                if (res != other.get()){

                    other.reset(res);

                }

            }

            Sequence<double> *res = seq->concat(other.get());
            replace_current_sequence(res);
            update_output(curr_seq());

        }
        else if (method == "print"){

            update_output(curr_seq());

        }

    }
    catch (const std::exception &msg){

        ui->OutputText->setText(QString("Error: ") + msg.what());

    }

}