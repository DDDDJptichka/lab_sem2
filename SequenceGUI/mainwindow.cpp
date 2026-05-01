#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow){

    ui->setupUi(this);
    ui->SequenceTypeBox->addItems({"ArraySequence", "ListSequence", "ImmutableArraySequence", "ImmutableListSequence"});
    ui->MethodTypeBox->addItems({"append", "prepend", "insert_at", "get", "get_first", "get_last", "get_length", "print", "get_sub_sequence", "concat"});
    ui->DataTypeBox->addItems({"double"});

    create_sequence();

}

MainWindow::~MainWindow(){

    delete ui;

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

void MainWindow::replace_sequence(Sequence<double> *res){

    if (res != seq.get()){

        seq.reset(res);

    }

}

void MainWindow::create_sequence(){

    QString seq_kind = ui->SequenceTypeBox->currentText();

    if (seq_kind == "ArraySequence"){

        seq = std::make_unique<ArraySequence<double>>();

    }
    else if (seq_kind == "ListSequence"){

        seq = std::make_unique<ListSequence<double>>();

    }
    else if (seq_kind == "ImmutableArraySequence"){

        seq = std::make_unique<ImmutableArraySequence<double>>();

    }
    else if (seq_kind == "ImmutablelistSequence"){

        seq = std::make_unique<ImmutableListSequence<double>>();

    }

    update_output(seq.get());

}

void MainWindow::on_sequenceTypeBox_clicked(){

    create_sequence();

}

void MainWindow::on_executeButton_clicked(){

    if (seq == nullptr){

        return;

    }

    QString method = ui->MethodTypeBox->currentText();

    try{

        if (method == "append"){

            double value = ui->valueEdit->text().toDouble();
            Sequence<double> *res = seq->append(value);

            replace_sequence(res);
            update_output(res);

        }
        else if (method == "prepend"){

            double value = ui->valueEdit->text().toDouble();
            Sequence<double> *res = seq->prepend(value);

            replace_sequence(res);
            update_output(res);

        }
        else if (method == "insert_at"){

            double value = ui->valueEdit->text().toDouble();
            int index = ui->indexEdit->text().toInt();
            Sequence<double> *res = seq->insert_at(value, index);

            replace_sequence(res);
            update_output(res);

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
        else if (method == "get_sub_seq"){

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
            replace_sequence(res);

            update_output(res);

        }
        else if (method == "print"){

            update_output(seq.get());

        }

    }
    catch (const std::exception &msg){

        ui->OutputText->setText(QString("Error: ") + msg.what());

    }

}