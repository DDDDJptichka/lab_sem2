#include <iostream>
#include <limits>

#include "ArraySequence.h"
#include "ListSequence.h"
#include "ImmutableArraySequence.h"
#include "ImmutableListSequence.h"
#include "NormalBitSequence.h"

double input_double(){
    
    double x;

    while (true) {
        
        if (!(std::cin >> x)) {
            
            std::cout << "Wrong input\n\n";

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            continue;

        }

        return x;
    
    }

}

int input_int(){
    
    int x;

    while (true) {
        
        if (!(std::cin >> x)) {
            
            std::cout << "Wrong input \n\n";

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            continue;

        }
        
        return x;
    
    }

}

Sequence<double> *choose_seq(){

    int seq_kind;

    while (true){

        std::cout << "1 ArraySequence<double>\n";
        std::cout << "2 ListSequence<double>\n";
        std::cout << "3 ImmutableArraySequence<double>\n";
        std::cout << "4 ImmutableListSequence<double>\n\n";
        std::cout << "kind of sequence: ";
    
        if (!(std::cin >> seq_kind)){

            std::cout << "\n\nWrong kind of sequence\n\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            continue;

        }

        if ((seq_kind >= 1) && (seq_kind <= 4)){

            break;

        }

        std::cout << "\n\nWrong kind of sequence\n\n";

    }

    Sequence<double> *seq = nullptr;

    if (seq_kind == 1){

        seq = new ArraySequence<double>();

    }
    else if (seq_kind == 2){

        seq = new ListSequence<double>();

    }
    else if (seq_kind == 3){

        seq = new ImmutableArraySequence<double>();

    }
    else if (seq_kind == 4){

        seq = new ImmutableListSequence<double>();

    }

    return seq;

}

void print_seq(Sequence<double> *seq){

    std::cout << "[ ";
    
    size_t legth = seq->get_length();

    for (size_t i = 0; i < legth; ++i){

        std::cout << seq->get(i) << " ";

    }

    std::cout << "]\n";

}

void do_operations(Sequence<double> *&seq){

    while (true){

        std::cout << "\n----- MENU -----\n";
        std::cout << "1 append\n";
        std::cout << "2 prepend\n";
        std::cout << "3 insert_at\n";
        std::cout << "4 get_first\n";
        std::cout << "5 get_last\n";
        std::cout << "6 get_length\n";
        std::cout << "7 get\n";
        std::cout << "8 get_sub_sequence\n";
        std::cout << "9 concat\n";
        std::cout << "10 print\n";
        std::cout << "0 exit\n\n";
        std::cout << "number: ";

        int arg = input_int();

        if (arg == 0){

            break;

        }

        if (arg == 1){

            std::cout << "value: ";
            double value = input_double();

            Sequence<double> *old = seq;
            Sequence<double> *res = seq->append(value);

            if (res != old){

                seq = res;
                delete old;

            }

            print_seq(seq);

        }
        else if (arg == 2){

            std::cout << "value: ";
            double value = input_double();

            Sequence<double> *res = seq->prepend(value);

            print_seq(res);

            delete res;

        }
        else if (arg == 3){

            std::cout << "value: ";
            double value = input_double();

            std::cout << "index: ";
            int index = input_int();

            Sequence<double> *res = seq->insert_at(value, index);

            print_seq(res);

            delete res;

        }
        else if (arg == 4){

            std::cout << seq->get_first();

        }
        else if (arg == 5){

            std::cout << seq->get_last();

        }
        else if (arg == 6){

            std::cout << seq->get_length();

        }
        else if (arg == 7){

            std::cout << "index: ";
            int index = input_int();

            std::cout << seq->get(index);

        }
        else if (arg == 8){

            std::cout << "start index: ";
            int start_index = input_int();

            std::cout << "end index: ";
            int end_index = input_int();

            Sequence<double> *res = seq->get_sub_sequence(start_index, end_index);
            
            print_seq(res);

            delete res;

        }
        else if (arg == 9){

            std::cout << "\nCreate second sequence:\n";
            Sequence<double> *other = choose_seq();

            std::cout << "How many elements: ";
            int size = input_int();

            for (size_t i = 0; i < size; ++i){
                
                std::cout << "value[" << i << "]: ";
                other->append(input_double());
            
            }

            Sequence<double> *res = seq->concat(other);

            print_seq(res);

            delete res;

        }
        else if (arg == 10){

            print_seq(seq);

        }

    }

}