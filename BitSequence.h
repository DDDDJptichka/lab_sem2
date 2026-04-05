#pragma once

#include <iostream>
#include <algorithm>
#include "Sequence.h"
#include "ArraySequence.h"

struct Bit{

    bool value = false;

};

class BitSequence : public Sequence<Bit>{

    protected:

        Sequence<Bit> *sequence;

    public:

        BitSequence(){

            sequence = new ArraySequence<Bit>();

        }

        BitSequence(size_t size){

            Bit item;

            sequence = new ArraySequence<Bit>();

            for (size_t i = 0; i < size; ++i){

                sequence->append(item);

            }

        }

        BitSequence(const DynamicArray<Bit> &another){

            sequence = new ArraySequence<Bit>(another);

        }

        BitSequence(const Sequence<Bit> &another){

            size_t size = another.get_length();

            sequence = new ArraySequence<Bit>();

            for (size_t i = 0; i < size; ++i){

                sequence->append(another.get(i));

            }

        }

        BitSequence(const BitSequence &another){

            sequence = new ArraySequence<Bit>();

            for(int i = 0; i < another.get_length(); ++i){

                sequence->append(another.get(i));

            }

        }

        BitSequence(const int *data, size_t count){

            Bit item;
            sequence = new ArraySequence<Bit>();

            for (size_t i = 0; i < count; ++i){

                item.value = data[i] % 2;
                sequence->append(item);

            }

        }

        BitSequence(const Bit *data, size_t count){

            sequence = new ArraySequence<Bit>();

            for (size_t i = 0; i < count; ++i){

                sequence->append(data[i]);

            }

        }

        BitSequence(const bool *data, size_t count){

            Bit item;
            sequence = new ArraySequence<Bit>();

            for (size_t i = 0; i < count; ++i){

                item.value = data[i];
                sequence->append(item);

            }

        }

        ~BitSequence(){

            delete sequence;

        }

        Bit get_first() const override{

            return sequence->get_first();

        }

        Bit get_last() const override{

            return sequence->get_last();

        }

        Bit get(int index) const override{

            return sequence->get(index);

        }

        int get_length() const override{

            return sequence->get_length();

        }

        BitSequence *append(Bit item) override{

            this->sequence->append(item);

            return this;

        }

        BitSequence *prepend(Bit item) override{

            this->sequence->prepend(item);

            return this;

        }

        BitSequence *insert_at(Bit item, int index) override{

            this->sequence->insert_at(item, index);

            return this;

        }

        BitSequence *get_sub_sequence(int start_index, int end_index) override{

            Sequence<Bit> *res_seq = sequence->get_sub_sequence(start_index, end_index);
            BitSequence *res_bit = new BitSequence(*res_seq);

            delete res_seq;

            return res_bit;

        }

        BitSequence *concat(Sequence<Bit> *another_seq) override{

            Sequence<Bit> *res_seq = sequence->concat(another_seq);
            BitSequence *res_bit = new BitSequence(*res_seq);

            delete res_seq;

            return res_bit;

        }
    
        BitSequence *AND(Sequence<Bit> *another_seq){

            size_t seq_size = sequence->get_length();
            size_t anthr_seq_size = another_seq->get_length();

            BitSequence *res_seq = new BitSequence();

            for(size_t i = 0; i < std::min(seq_size, anthr_seq_size); ++i){

                Bit item;
                item.value = sequence->get(i).value && another_seq->get(i).value;
                res_seq->append(item);

            }

            for (size_t i = std::min(seq_size, anthr_seq_size); i < std::max(seq_size, anthr_seq_size); ++i){

                Bit item;
                res_seq->append(item);

            }

            return res_seq;

        }

};