#pragma once

#include <queue>
#include <unordered_map>
#include "algobox.hpp"


template <typename T>
class algobox::vector{
    public:
        static_assert(std::is_arithmetic_v<T>, "You should use number data types.");

        AlgoMode mode;

        template <typename T2>
        vector(const T2 _vector_, const size_t _size_, const size_t _capacity_, const size_t _width_limit_);

        vector(const T* _vector_, const size_t _size_);
        vector(const std::vector<T>& _vector_);
        vector(const std::initializer_list<T> _vector_);
        vector(const size_t _size_);
        vector();

        ~vector();

        vector(const vector<T>& other);
        vector(vector<T>&& other);

        vector<T>& operator=(const vector<T>& other);
        vector<T>& operator=(vector<T>&& other);
        void operator++(int);

        T& operator[](size_t index);
        const T& operator[](size_t index) const;

        struct iterator{
            using pointer = T*;
            using reference = T&;

            algobox::vector<T>* _parent;
            pointer _ptr;
            iterator(pointer ptr, algobox::vector<T>* parent);

            reference operator*() const;
            pointer operator->();

            iterator& operator++();
            iterator operator++(int);

            iterator operator-(size_t n);
            iterator operator-(int n);
            iterator operator+(size_t n);

            operator bool();

            bool operator==(const iterator& other) const;
            bool operator!=(const iterator& other) const;

            T get() const;
        };

        void push_back(T element);
        void erase(size_t pos);
        void clear();
        size_t size() const;
        size_t capacity() const;
        size_t width_limit() const;
        bool empty() const;
        T get_max();
        T get_min();
        T at(size_t index);
        void swap(size_t index_1, size_t index_2);
        void swap(iterator it1, iterator it2);
        bool is_greater(iterator it1, iterator it2);
        const T* get_data_ptr() const;

        iterator begin();
        iterator end();

        mutable std::queue<size_t> nodes;
        mutable std::queue<algobox::State<T>> copies;

    private:
        T* data;
        size_t _width_limit;
        size_t _capacity;
        size_t _size;
};

template <typename T>
template <typename T2>
algobox::vector<T>::vector(const T2 _vector_, const size_t _size_, const size_t _capacity_, const size_t _width_limit_) : 
    _size(_size_), _capacity(_size_), _width_limit(_width_limit_), mode(AlgoMode::NONE) {
    if (_capacity > _width_limit_){
        throw algobox::SizeLimitException(_capacity_, _width_limit_);
    }

    data = new T[_capacity];

    for (size_t i=0; i<_size_; i++){
        data[i] = _vector_[i];
    }
}

template <typename T>
algobox::vector<T>::vector(const T* _vector_, const size_t _size_) :
    vector(_vector_, _size_, _size_, 720) {}


template <typename T>
algobox::vector<T>::vector(const std::initializer_list<T> _vector_) :
    vector(_vector_.begin(), _vector_.size(), _vector_.size(), 720) {}

template <typename T>
algobox::vector<T>::vector(const std::vector<T>& _vector_) :
    vector(_vector_.data(), _vector_.size(), _vector_.size(), 720) {}

template <typename T>
algobox::vector<T>::vector(const size_t _size_) :
    _size(_size_), _capacity(_size_), _width_limit(720) {
    if (_capacity > _width_limit){
        throw algobox::SizeLimitException(_capacity, _width_limit);
    }

    data = new T[_capacity];

    for (size_t i=0; i<_size; i++){
        data[i] = 0;
    }
}

template <typename T>
algobox::vector<T>::vector() : _size(0), _capacity(0), _width_limit(720), data(nullptr) {}

template <typename T>
algobox::vector<T>::~vector(){
    delete[] data;
}

template <typename T>
algobox::vector<T>::vector(const vector<T>& other) :
    vector(other.data, other._size, other._capacity, other._width_limit) {
    mode = other.mode;
}

template <typename T>
algobox::vector<T>::vector(vector<T>&& other) : _size(0), _capacity(0), _width_limit(720), data(nullptr) {
    *this = std::move(other);
}

template <typename T>
algobox::vector<T>& algobox::vector<T>::operator=(const vector<T>& other) {
    if (this != &other){
        delete[] data;

        mode = other.mode;
        _size = other._size;
        _capacity = other._capacity;
        _width_limit = other._width_limit;

        nodes = other.nodes;
        copies = other.copies;

        data = new T[_capacity];

        for (size_t i=0; i<_size; i++){
            data[i] = other.data[i];
        }
    }
    return *this;
}

template <typename T>
algobox::vector<T>& algobox::vector<T>::operator=(vector<T>&& other) {
    if (this != &other){
        delete[] data;

        mode = other.mode;
        data = other.data;
        _size = other._size;
        _capacity = other._capacity;
        _width_limit = other._width_limit;

        nodes = std::move(other.nodes);
        copies = std::move(other.copies);

        other.mode = AlgoMode::NONE;
        other.data = nullptr;
        other._size = 0;
        other._capacity = 0;
    }
    return *this;
}

template <typename T>
void algobox::vector<T>::operator++(int){
    nodes.push(algobox::empty_element);
}

template <typename T>
void algobox::vector<T>::push_back(T element){
    if (_size == 0 || _capacity == 0){
        _capacity = 1;
        delete[] data;
        data = new T[1];
    }
    else if (_size+1>_capacity){
        if (_capacity+1 > _width_limit){
            throw algobox::SizeLimitException(_capacity+1, _width_limit);
        }

        if (_capacity * 2 < _width_limit)
            _capacity = _capacity * 2;
        else
            _capacity = _width_limit;

        T* tmp = data;
        data = new T[_capacity];
        for (size_t i=0; i<_size; i++){
            data[i] = tmp[i];
        }
        delete[] tmp;
    }
    data[_size] = element;
    _size++;
    if (mode != NONE)
        copies.emplace(std::vector<T>(data, data+_size), _size-1,
                        algobox::empty_element, algobox::empty_element);
}

template<typename T>
void algobox::vector<T>::erase(size_t pos){
    if (pos >= _size){
        throw algobox::OutOfRange(pos, _size);
    }
    if (pos < _size - 1){
        for (int i=pos; i<_size-1; i++){
            data[i] = data[i+1];
        }
    }
    data[_size-1] = 0;
    _size--;

    if (mode != NONE){
        copies.emplace(std::vector<T>(data, data+_size), algobox::empty_element,
                        pos, algobox::empty_element);
    }
}

template <typename T>
void algobox::vector<T>::clear(){
    delete[] data;
    data = nullptr;
    _size = 0;
    _capacity = 0;
}

template <typename T>
size_t algobox::vector<T>::size() const{
    return _size;
}

template <typename T>
size_t algobox::vector<T>::capacity() const{
    return _capacity;
}

template <typename T>
size_t algobox::vector<T>::width_limit() const{
    return _width_limit;
}

template <typename T>
bool algobox::vector<T>::empty() const{
    return _size == 0;
}

template <typename T>
T algobox::vector<T>::get_max(){
    if (this->empty())
        return 0;

    T m = data[0];
    for (int i=0; i<_size; i++){
        if (data[i] > m) m = data[i];
    }
    return m;
}

template <typename T>
T algobox::vector<T>::get_min(){
    if (this->empty())
        return 0;

    T m = data[0];
    for (int i=0; i<_size; i++){
        if (data[i] < m) m = data[i];
    }
    return m;
}

template <typename T>
T algobox::vector<T>::at(size_t index){
    if (index >= _size)
        throw algobox::OutOfRange(index, _size);

    return data[index];
}

template <typename T>
const T* algobox::vector<T>::get_data_ptr() const { return data;}

template <typename T>
void algobox::vector<T>::swap(size_t green_index, size_t red_index){
    if (green_index >= _size || red_index >= _size)
        throw algobox::OutOfRange(std::max(green_index, red_index), _size);

    T tmp = data[green_index];
    T tmp_2 = data[red_index];
    data[green_index] = data[red_index];
    data[red_index] = tmp;
    copies.emplace(std::vector<T>(data, data + _size), algobox::empty_element, green_index, red_index);
}

template <typename T>
void algobox::vector<T>::swap(iterator it1, iterator it2){

    size_t green_index = it1._ptr - data;
    size_t red_index = it2._ptr - data;

    swap(green_index, red_index);
}

template <typename T>
bool algobox::vector<T>::is_greater(iterator it1, iterator it2){

    return it1.get() > it2.get();
}


template <typename T>
algobox::vector<T>::iterator::iterator(pointer ptr, algobox::vector<T>* parent) :
    _ptr(ptr), _parent(parent) {}

template <typename T>
typename algobox::vector<T>::iterator::reference
algobox::vector<T>::iterator::operator*() const{
    size_t index = _ptr - _parent->data;
    if (_parent && _parent->mode != NONE){
        if (_parent->mode == SEARCH){
            if (_parent->nodes.empty()){
                _parent->nodes.push(index);
            }
            _parent->nodes.back() = index;
        }

        if (_parent->mode == SORT){
            if (_parent->copies.empty() || _parent->copies.back().index != index)
                _parent->copies.emplace(
                    std::vector<T>(_parent->data, _parent->data + _parent->_size), index,
                    algobox::empty_element, algobox::empty_element);
        }
    }
    return *_ptr;
}

template <typename T>
typename algobox::vector<T>::iterator::pointer
algobox::vector<T>::iterator::operator->(){
    return _ptr;
}

template <typename T>
typename algobox::vector<T>::iterator&
algobox::vector<T>::iterator::operator++(){
    _ptr++;
    return *this;
}

template <typename T>
typename algobox::vector<T>::iterator
algobox::vector<T>::iterator::operator++(int){
    iterator tmp = *this;
    ++(*this);
    return tmp;
}

template <typename T>
typename algobox::vector<T>::iterator
algobox::vector<T>::iterator::operator-(size_t n){
    return iterator(_ptr - n, _parent);
}
template <typename T>
typename algobox::vector<T>::iterator
algobox::vector<T>::iterator::operator-(int n){
    return iterator(_ptr - n, _parent);
}

template <typename T>
typename algobox::vector<T>::iterator
algobox::vector<T>::iterator::operator+(size_t n){
    return iterator(_ptr + n, _parent);
}

template <typename T>
algobox::vector<T>::iterator::operator bool(){
    if (!_parent || !_ptr) return false;
    return (_ptr >= _parent->data) && (_ptr < (_parent->data+_parent->_size-1));
}

template <typename T>
bool algobox::vector<T>::iterator::operator==(const iterator& other) const{
    return _ptr == other._ptr;
}

template <typename T>
bool algobox::vector<T>::iterator::operator!=(const iterator& other) const{
    return _ptr != other._ptr;
}

template <typename T>
typename algobox::vector<T>::iterator algobox::vector<T>::begin(){
    return iterator(data, this);
}

template <typename T>
typename algobox::vector<T>::iterator algobox::vector<T>::end(){
    return iterator(data + _size, this);
}

template <typename T>
T algobox::vector<T>::iterator::get() const{
    return *_ptr;
}


template <typename T>
T& algobox::vector<T>::operator[](size_t index){
    if (index >= _size)
        throw algobox::OutOfRange(index, _size);

    switch (mode) {
        case SEARCH:
            if (nodes.empty()){
                nodes.push(index);
            }
            nodes.back() = index;
            break;

        case SORT:
            if (!copies.empty() && copies.back().index == index)
                break;
            copies.emplace(std::vector<T>(data, data + _size), index,
                        algobox::empty_element, algobox::empty_element);
            break;

        default:
            throw algobox::NoAlgoModeSelected();
    }
    return data[index];
}

template <typename T>
const T& algobox::vector<T>::operator[](size_t index) const{
    if (index >= _size)
        throw algobox::OutOfRange(index, _size);

    switch (mode) {
        case SEARCH:
            if (nodes.empty()){
                nodes.push(index);
            }
            nodes.back() = index;
            break;

        case SORT:
            if (!copies.empty() && copies.back().index == index)
                break;
            copies.emplace(std::vector<T>(data, data + _size), index,
                        algobox::empty_element, algobox::empty_element);
            break;

        default:
            throw algobox::NoAlgoModeSelected();
    }
    return data[index];
}