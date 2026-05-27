#include <utility>

template <class T> class Option{

    private:

        alignas(T) std::byte data[sizeof(T)];
        bool has_value = false;

        T* ptr();
        const T* ptr();
        void clear();

    public:

        Option(){}

        Option(const T& value){}

};