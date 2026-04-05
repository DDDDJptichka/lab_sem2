#pragma once

#include "Sequence.h"
#include "ArraySequence.h"

struct Bit{

    bool value;

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
            item.value = 0;

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

        BitSequence(int *data, size_t count){

            Bit item;
            sequence = new ArraySequence<Bit>();

            for (size_t i = 0; i < count; ++i){

                item.value = data[i] % 2;
                sequence->append(item);

            }

        }

        BitSequence(Bit *data, size_t count){

            sequence = new ArraySequence<Bit>();

            for (size_t i = 0; i < count; ++i){

                sequence->append(data[i]);

            }

        }

        BitSequence(bool *data, size_t count){

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

        Sequence<Bit> *append(Bit item) override{

            this->sequence->append(item);

            return this;

        }

    
};