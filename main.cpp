#include <memory>
#include <stdexcept>

#include <functional>
#include <cstddef>

template <class T> class LinkedListt{};

template <class T> class DynamicArrayy{};

template <class T> struct NOde{};

class LinkedList{

    private:

        struct Node{

            int value;
            std::unique_ptr<Node> next;
            Node *prev;
            
            Node(int value) : value(value), next(nullptr), prev(nullptr){}

        };

        std::unique_ptr<Node> head;

    public:

        int get(size_t index){

            Node *curr = head.get();

            for (size_t i = 0; i < index; ++i){

                if (curr == nullptr){

                    /*throw*/ return 1;

                }

                curr = curr->next.get();

            }

            if (curr == nullptr){

                /*throw*/ return 1;

            }
    
            return curr->value;

        }

        LinkedList* insert_at(size_t index, int value){

            auto new_node = std::make_unique<Node>(value);
            
            if (index == 0){

                new_node->next = std::move(head);

                if (new_node->next != nullptr){

                    new_node->next->prev = new_node.get();

                }

                head = std::move(new_node);

                return this;

            }

            Node *curr = head.get();

            for (size_t i = 0; i < index - 1; ++i){

                if (curr == nullptr){

                    return nullptr;

                }

                curr = curr->next.get();

            }

            if (curr == nullptr){

                return nullptr;

            }

            new_node->next = std::move(curr->next);
            new_node->prev = curr;

            if (new_node->next != nullptr){

                new_node->next->prev = new_node.get();

            }

            curr->next = std::move(new_node);

            return this;

        }

        LinkedList* del(size_t index){

            if (head == nullptr){

                return this;

            }

            Node *curr = head.get();

            if (index == 0){

                head = std::move(head->next);

                if (head != nullptr){

                    head->prev = nullptr;

                }

                return this;

            }

            for (int i = 0; i < index; ++i){

                if (curr != nullptr){

                    curr = curr->next.get();

                }
                else{

                    return nullptr;

                }

            }

            if (curr == nullptr){

                return nullptr;

            }

            Node *prev = curr->prev;
            auto to_del = std::move(prev->next);
            prev->next = std::move(to_del->next);

            if (prev->next != nullptr){

                prev->next->prev = prev;

            }

            return this;

        }

};






//ДЛЯ КОЛЬЦЕВОГО


class CLinkedList {

    private:

        struct Node{
            
            int value;
            Node* next;
            Node* prev;

            Node(int value) : value(value), next(nullptr), prev(nullptr) {}
        };

        Node* head = nullptr;

    public:

        int get(size_t index){

            if (head == nullptr){

                /*throw*/ return 1;
            
            }

            Node* curr = head;

            for (size_t i = 0; i < index; ++i){

                curr = curr->next;
            
            }

            return curr->value;
        
        }

        CLinkedList* insert_at(size_t index, int value){

            Node* new_node = new Node(value);

            if (head == nullptr){

                new_node->next = new_node;
                new_node->prev = new_node;
                head = new_node;
                
                return this;

            }

            if (index == 0){

                new_node->next = head;
                new_node->prev = head->prev;

                head->prev->next = new_node;
                head->prev = new_node;

                head = new_node;

                return this;
            
            }

            Node* curr = head;

            for (size_t i = 0; i < index - 1; ++i){

                curr = curr->next;
            
            }

            new_node->next = curr->next;
            new_node->prev = curr;

            curr->next->prev = new_node;
            curr->next = new_node;

            return this;
        }

        CLinkedList* del(size_t index){
            
            if (head == nullptr) {
                
                return nullptr;
            
            }

            Node* curr = head;

            for (size_t i = 0; i < index; ++i){

                curr = curr->next;

            }

            if (curr->next == curr) {

                delete curr;
                head = nullptr;

                return this;

            }

            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;

            if (curr == head){

                head = curr->next;

            }

            delete curr;

            return this;
        }
};






//ОЧЕРЕДЬ НА ДВУСВЯЗНОМ

class Queue {

    private:

        struct Node{

            int value;
            std::unique_ptr<Node> next;

            Node(int value) : value(value), next(nullptr) {}
        
        };

        std::unique_ptr<Node> head;
        Node* tail = nullptr;

    public:

        Queue* enqueue(int value){

            auto new_node = std::make_unique<Node>(value);

            if (head == nullptr){

                tail = new_node.get();
                head = std::move(new_node);
                
                return this;
            
            }

            tail->next = std::move(new_node);
            tail = tail->next.get();

            return this;
        
        }

        int dequeue() {

            if (head == nullptr){

                /*throw*/ return 1;
            
            }

            int val = head->value;

            head = std::move(head->next);

            if (head == nullptr){

                tail = nullptr;
            
            }

            return val;
        }
};





// СТЕК НА ЮНИКПТРЕ


class Stack{

    private:

        struct Snode{

            int value;
            std::unique_ptr<Snode> next;

            Snode(int value) : value(value), next(nullptr){}

        };

        std::unique_ptr<Snode> head;

    public:

        Stack* push(int value){

            auto new_node = std::make_unique<Snode>(value);

            new_node->next = std::move(head);
            head = std::move(new_node);

            return this; 

        }

        int pop(){

            if (head == nullptr){

                /*throw*/ return 1;

            }

            int value = head->value;
            head = std::move(head->next);

            return value;

        }

};









// ДЕК НА ДВУСВЯЗНОМ


class Dack{

    private:

        struct Node{

            int value;
            std::unique_ptr<Node> next;
            Node* prev;

            Node(int value) : value(value), next(nullptr), prev(nullptr){}

        };

        std::unique_ptr<Node> tail;
        Node* head = nullptr;

    public:

        int pop_back(){

            if (tail == nullptr){

                /*throw*/ return 1;

            }

            int value = tail->value;

            if (tail.get() == head){

                tail = nullptr;
                head = nullptr;
                
                return value;

            }

            tail = std::move(tail->next);
            tail->prev = nullptr;

            return value;

        }

        int pop_front(){

            if (head == nullptr){

                /*throw*/ return 1;

            }

            int value = head->value;

            if (head == tail.get()){

                tail = nullptr;
                head = nullptr;

                return value;

            }

            head = head->prev;
            head->next = nullptr;

            return value;

        }

        Dack* push_back(int value){

            auto new_node = std::make_unique<Node>(value);

            if (tail == nullptr){

                head = new_node.get();
                tail = std::move(new_node);

                return this;

            }

            tail->prev = new_node.get();
            new_node->next = std::move(tail);
            tail = std::move(new_node);

            return this;
            
        }

        Dack* push_front(int value){

            auto new_node = std::make_unique<Node>(value);

            if (head == nullptr){

                head = new_node.get();
                tail = std::move(new_node);

                return this;

            }

            new_node->prev = head;
            head->next = std::move(new_node);
            head = head->next.get();

            return this;

        }

};






//ДИНАМИЧЕСКИЙ МАССИВ

class DynamicArray{

    private: 

        int *data;
        size_t size;
        size_t capacity;

    public:

        int insert_at(size_t index, int item){

            if (index > size){

                return 1;

            }

            if (size >= capacity){

                int *new_data = new int[capacity + size]();

                for (size_t i = 0; i < index; ++i){

                    new_data[i] = data[i];

                }

                new_data[index] = item;

                for (size_t i = index; i < size; ++i){

                    new_data[i + 1] = data[i];

                }

                delete[] data;
                data = new_data;
                capacity += size;
                ++size;

                return 0;

            }

            for (int i = size; i > index; --i){

                data[i] = data[i - 1];

            }

            data[index] = item;
            ++size;

            return 0;

        }

        int del(size_t index){

            if (index >= size){

                return 1;

            }

            for (size_t i = index; i < size - 1; ++i){

                data[i] = data[i + 1];

            }

            --size;

            return 0;

        }

}; 




//ПОТОКИ

#include <cstddef>

template <typename T> class Stream{

    public:

        virtual ~Stream() = default;
        virtual bool eof() const = 0;
        virtual bool read(T& value) = 0;
        virtual bool write(const T& value) = 0;

};

template <typename T> class ArrayStream : public Stream<T>{

    private:

        T *data;
        size_t size;
        size_t capacity;
        size_t position;

    public:

        ArrayStream() : data(nullptr), size(0), capacity(0), position(0){}

        ~ArrayStream(){

            delete[] data;

        }

        bool eof() const override{

            return position >= size;

        }

        bool read(T& value) override{

            if (eof()){

                return false;

            }

            value = data[position];
            ++position;

            return true;

        }

        bool write(const T& value) override{

            if (size >= capacity){

                size_t new_capacity = capacity == 0 ? 1 : capacity * 2;

                T *new_data = new T[new_capacity];

                for (size_t i = 0; i < size; ++i){

                    new_data[i] = data[i];

                }

                delete[] data;
                data = new_data;
                capacity = new_capacity;

            }

            data[size] = value;
            ++size;

            return true;

        }

};




// OPTION 



template <typename T> class Option{

    private:

        alignas(T) unsigned char data[sizeof(T)];
        bool has_val = false;

        T* ptr(){

            return reinterpret_cast<T*>(data);

        }

    public:

        Option(){}

        Option(const T& value){

            new (data) T(value);
            has_val = true;

        }

        ~Option(){

            reset();

        }

        bool has_value() const{

            return has_val;

        }

        T& value(){

            if (has_val == false){

                throw std::runtime_error("empty option");

            }

            return *ptr();

        }

        void reset(){

            if (has_val == true){

                ptr()->~T();
                has_val = false;

            }

        }

};




// EITHER<T1, T2>


#include <stdexcept>

template <class T1, class T2> class Either{

    private:

        T1* value1;
        T2* value2;

    public:

        Either(const T1& v) : value1(new T1(v)), value2(nullptr){}

        Either(const T2& v) : value1(nullptr), value2(new T2(v)){}

        bool IsFirst() const{

            return value1 != nullptr;

        }

        bool IsSecond() const{

            return value2 != nullptr;

        }

        const T1& GetFirst() const{

            if (!IsFirst()){

                throw std::runtime_error("Either хранит второй вариант, не первый");

            }

            return *value1;

        }

        const T2& GetSecond() const{

            if (!IsSecond()){

                throw std::runtime_error("Either хранит первый вариант, не второй");

            }

            return *value2;

        }

};







//WHERE MAP REDUCE на массиве и списке


template <class T> DynamicArrayy<T> Where(const DynamicArrayy<T> &array, bool (*p)(T)){

    DynamicArrayy<T> result;

    for (size_t i = 0; i < array.get_size(); ++i){

        T value = array.get(i);

        if (p(value) == true){

            result.append(value);

        }

    }

    return result;

}

template <class T> LinkedListt<T> Where(const LinkedListt<T> &list, bool (*p)(T)){

    LinkedListt<T> result;
    NOde<T> *curr = list.head;

    while (curr != nullptr){

        if (p(curr.get(i)) == true){

            result.append(curr.value);

        }

        curr = curr.next;

    }

    return result;

}

///////////////////////////////

template <class T, typename func> DynamicArrayy<T> Map(const DynamicArrayy<T> &array, func f){

    DynamicArrayy<T> result;

    for (size_t i = 0; i < array.get_size(); ++i){

        result.append(f(array.get(i)));

    }

    return result;

}

template <class T, typename func> LinkedListt<T> Map(const LinkedListt<T> &list, func f){

    LinkedListt<T> result;

    for (size_t i = 0; i < list.get_size(); ++i){

        result.append(f(list.get(i)));

    }

    return result;

}


/////////////////////////////////////


template <class T, typename func> T Reduce(const DynamicArrayy<T> &array, func f, T start){

    T result = start;

    for (size_t i = 0; i < array.get_size(); ++i){

        result = f(result, array.get(i));

    }

    return result;

}

template <class T, typename func> T Reduce(const LinkedListt<T> &list, func f, T start){

    T result = start;

    for (size_t i = 0; i < list.get_size(); ++i){

        result = f(result, list.get(i));

    }

    return result;

}



////////////////////////

template <typename T1, typename T2> struct Pair{

    T1 first;
    T2 second;

    Pair(T1 a, T2 b) : first(a), second(b){}

};

template <typename T1, typename T2> DynamicArrayy<Pair<T1, T2>> Zip(const DynamicArrayy<T1> &array1, const DynamicArrayy<T2> &array2){

    DynamicArrayy<Pair<T1, T2>> res;

    int size = std::min(array1.get_size(), array2.get_size());

    for (int i = 0; i < size; ++i){

        res.append(Pair<T1, T2>(array1.get(i), array2.get(i)));

    }

    return res;

};

template <typename T1, typename T2> LinkedListt<Pair<T1, T2>> Zip(const LinkedListt<T1> &list1, const LinkedListt<T2> &list2){

    LinkedListt<Pair<T1, T2>> res;

    int size = std::min(list1.get_size(), list2.get_size());

    for (int i = 0; i < size; ++i){

        res.append(Pair<T1, T2>(list1.get(i), list2.get(i)));

    }

    return res;

};






/////////////////////////////////////////////////// ЛЕНИВОСТЬ


class Factorials{

    private:

        mutable long long cache[21]{};

        Factorials(){

            cache[0] = 1;
            cache[1] = 1;

        }

    public:

        static const Factorials& Global(){

            static Factorials obj;

            return obj;

        }

        long long get(size_t n) const{

            if (n >= 21){

                throw std::out_of_range("too big");

            }

            if (cache[n] != 0){

                return cache[n];

            }

            cache[n] = n * get(n - 1);

            return cache[n];

        }

};







///////////////////////////////////////


template <class T> class Generator{

    private:

        std::function<T(size_t)> rule;
        size_t index = 0;
        size_t count = 0;
        bool inf = false;

    public:

        Generator(){}

        Generator(std::function<T(size_t)> rule) : rule(rule), inf(true){}

        Generator(std::function<T(size_t)> rule, size_t count) : rule(rule), count(count), inf(false){}

        bool has_next() const{

            return rule && (inf || index < count);

        }

        T get_next(){

            if (has_next() == false){

                throw std::out_of_range("Generator ended");

            }

            T value = rule(index);
            ++index;

            return value;

        }

        size_t get_position() const{

            return index;

        }

};





/////////////////////////////////// ОРДИНАЛЫ


class Ordinal{

    private:

        size_t omega_count;
        size_t finite_tail;

    public:

        Ordinal(size_t omega_count, size_t finite_tail) : omega_count(omega_count), finite_tail(finite_tail){}

        bool is_finite() const{

            return omega_count == 0;

        }

        Ordinal add(const Ordinal& beta) const{

            if (beta.omega_count == 0){

                return Ordinal(omega_count, finite_tail + beta.finite_tail);

            }

            return Ordinal(omega_count + beta.omega_count, beta.finite_tail);

        }

        size_t get_omega_count() const{

            return omega_count;

        }

        size_t get_finite_tail() const{

            return finite_tail;

        }

};



///////////////////////////////////////////////////ЛЕЙЗИСИКВЕНС


template <class T> class LazySequence{

    private:

        mutable Generator<T> generator;
        mutable ArraySequence<T> cache;

        bool inf = false;
        size_t length = 0;

        void materialize_to(size_t index) const{

            if (!inf && index >= length){

                throw std::out_of_range("index out of range");

            }

            while (cache.get_length() <= index){

                if (!generator.has_next()){

                    throw std::out_of_range("generator ended");

                }

                cache.append(generator.get_next());

            }

        }

    public:

        LazySequence(Generator<T> generator) : generator(generator), inf(true), length(0){}

        LazySequence(Generator<T> generator, size_t length) : generator(generator), inf(false), length(length){}

        T get(size_t index) const{

            materialize_to(index);

            return cache[index];

        }

        size_t materialised_size() const{

            return cache.get_length();

        }

        bool is_infinite() const{

            return inf;

        }

};







/////////////////////////////////////////////////////ДЛИННАЯ АРИФМЕТИКА


#include <string>
#include <algorithm>

class BigInt{

    private:

        std::string digits; // цифры в обратном порядке


        void normalize(){

            while ((digits.size() > 1) && (digits.back() == '0')){

                digits.pop_back();

            }

        }


    public:

        BigInt() : digits("0"){}

        BigInt(const std::string &str){

            digits = str;

            std::reverse(digits.begin(), digits.end());

            normalize();

        }

        BigInt add(const BigInt &another) const{

            BigInt result;

            result.digits = "";

            int carry = 0;

            size_t n = std::max(digits.size(), another.digits.size());

            for (size_t i = 0; i < n || carry; ++i){

                int sum = carry;

                if (i < digits.size()){

                    sum += digits[i] - '0';

                }

                if (i < another.digits.size()){

                    sum += another.digits[i] - '0';

                }

                result.digits.push_back(char(sum % 10 + '0'));
                carry = sum / 10;

            }

            result.normalize();

            return result;

        }

        BigInt multiply(const BigInt &another) const{

            BigInt result;

            result.digits = std::string(digits.size() + another.digits.size(), '0');

            for (size_t i = 0; i < digits.size(); ++i){

                int carry = 0;

                for (size_t j = 0; j < another.digits.size() || carry; ++j){

                    int cur = result.digits[i + j] - '0' + carry;

                    if (j < another.digits.size()){

                        cur += (digits[i] - '0') * (another.digits[j] - '0');

                    }

                    result.digits[i + j] = char(cur % 10 + '0');
                    carry = cur / 10;

                }

            }

            result.normalize();

            return result;

        }

        std::string to_string() const{

            std::string result = digits;

            std::reverse(result.begin(), result.end());

            return result;

        }

};

int main(){

    long long a = Factorials::Global().get(5);
    long long b = Factorials::Global().get(6);

    return 0;

}