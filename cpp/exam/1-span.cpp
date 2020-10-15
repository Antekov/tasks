#include <iostream>

namespace std {
    constexpr std::size_t dynamic_extent = -1;

    template<typename T, std::size_t Extent = std::dynamic_extent>
    class span {
        static constexpr std::size_t extent = Extent;
        typedef T element_type;
        typedef std::remove_cv_t<T> value_type;
        typedef std::size_t size_type;
        typedef std::size_t difference_type;
        typedef value_type * pointer;
        typedef const value_type * const_pointer;
        typedef value_type & reference;
        typedef const value_type & const_reference;

        struct iterator;
        struct const_iterator : public std::iterator<std::bidirectional_iterator_tag, const T>
        {
            const_iterator() = default;
            reference operator*() { return *itm; }
            const pointer operator->() { return itm; }
            const_iterator operator++() {
                itm++;
                return *this;
            }
            const_iterator operator--() { 
                // std::cerr << "List::const_iterator::operator--()" << (itm == nullptr) << std::endl;
                itm--; return *this; }
            const_iterator operator++(int) { const_iterator ret=*this; itm++; return ret; }
            const_iterator operator--(int) { const_iterator ret=*this; itm--; return ret; }
            bool operator==(const_iterator oth) const { return itm==oth.itm; }
            bool operator!=(const_iterator oth) const { return itm!=oth.itm; }
        private:
            pointer itm = nullptr;
            const_iterator(pointer i) : itm(i) {}
            friend class span;
            friend struct iterator;
        };

        struct iterator : public std::iterator<std::bidirectional_iterator_tag, T>
        {
            iterator() = default;
            reference operator*() { return *itm; }
            pointer operator->() { return itm; }
            iterator operator++() { 
                itm++;
                return *this;
            }
            iterator operator--() { 
                itm--; return *this; }
            iterator operator++(int) { 
                iterator ret=*this; itm++; return ret; }
            iterator operator--(int) { 
                iterator ret=*this; itm--; return ret; }
            bool operator==(iterator oth) const { return itm==oth.itm; }
            bool operator!=(iterator oth) const { return itm!=oth.itm; }
            operator const_iterator() { return {itm}; }
        private:
            pointer itm = nullptr;
            iterator(pointer i) : itm(i) {}
            friend class span;
        };

        typedef std::reverse_iterator<iterator> reverse_iterator;
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

        

        size_t _size;
        pointer _data;

    public:
        size_t size() { return _size; }
        pointer data() { return _data; }
    
        span() {
            if (extent == 0 || extent == std::dynamic_extent) {
                _size = extent;
                _data = nullptr;
            } else {
                _size = extent;
                _data = new value_type[_size];
            }
        }
        template<std::size_t N>
        span(element_type (&arr)[N]) {
            _size = N;
            _data = new value_type[_size];
            for (int i = 0; i < N; i++) {
                *(_data+i) = *(arr+i);
            }
        }

        span(pointer p, size_t count) {
            _data = p;
            _size = count;
        }

        ~span() {
            if (_data != nullptr) {
                delete[] _data;
            }
        }

        iterator begin() {
            return iterator(_data);
        }

        iterator end() {
            return iterator(_data + _size);
        }

        reverse_iterator rbegin() {
            return reverse_iterator(_data + _size - 1); 
        }

        reverse_iterator rend() {
            return reverse_iterator(_data - 1); 
        }

        reference front() { return _data[0]; }
        reference back() { return _data[_size - 1]; }

        reference operator[](size_t i) const { return _data[i]; }
        size_t size_bytes() { return size() * sizeof(value_type); }
        bool empty() { return size() == 0; }

        template<size_t Count>
        span<element_type, Count> first() {
            return *new span<element_type, Count>(_data, Count);
        }

        span<element_type, std::dynamic_extent> first(size_t Count) {
            return *new span<element_type, std::dynamic_extent>(_data, Count);
        }

        template<size_t Count>
        span<element_type, Count> last() {
            return span<element_type, Count>(_data + (_size - Count), Count);
        }

        span<element_type, std::dynamic_extent> last(size_t Count) {
            return span<element_type, std::dynamic_extent>(this->data() + (this->size() - Count), Count);
        }

        template<size_t Offset, size_t Count=std::dynamic_extent>
        span<element_type, Count> subspan() {
            size_t count;
            if (Count == std::dynamic_extent) {
                count = this->size() - Offset;
            } else {
                count = Count;
            }
            return span<element_type, Count>(_data + Offset, count);
        }

        span<element_type, std::dynamic_extent> subspan(size_t Offset, size_t Count = std::dynamic_extent) {
            size_t count;
            if (Count == std::dynamic_extent) {
                count = this->size() - Offset;
            } else {
                count = Count;
            }
            return span<element_type, std::dynamic_extent>(this->data() + Offset, count);
        }
    };
}


int main1() {
    std::span<int, 10> s;
    int i = 1;
    for (auto &a : s)
    {
        a = i++;
    }

    for (auto a : s) {
        std::cout << a << " ";
    }
    return 0;
}

void show_sizes(std::span<const int> span)
{
    std::cout
        << span                 .size() << ' ' // 8
        << span.first(7)        .size() << ' ' // 7
        << span.first<6>()      .size() << ' ' // 6 
        << span.last(5)         .size() << ' ' // 5 
        << span.last<4>()       .size() << ' ' // 4
        << span.subspan(2, 3)   .size() << ' ' // 3 
        << span.subspan<3, 2>() .size() << ' ' // 2
        << '\n';
}
 
int main()
{
    int antique_array[] { 1, 2, 3, 4, 5, 6, 7, 8 };
    show_sizes(antique_array);
}