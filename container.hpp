#ifndef CONTAINER_HPP
#define CONTAINER_HPP
#include <stdexcept>
#include <climits>

using namespace std;


namespace container
{
template <typename T>
class Container
{
public:
    Container(size_t size)
        : _ptr{new T[size]}, _idx{0}, _size{size}
    {}

    ~Container()
    {
        delete [] _ptr;
        _ptr = nullptr;
    }

    void push_back(const T& element)
    {
        if( _idx >= _size )
        {
            reallocate_move();
        }
        _ptr[_idx++] = element;
    }

    void push_back(T&& element)
    {
        if( _idx >= _size )
        {
            reallocate_move();
        }
        _ptr[_idx++] = std::move(element);
    }

    T& operator[](size_t idx)
    {
        if( idx >= _size )
        {
            throw std::out_of_range("Out of range exception");
        }
        return _ptr[idx];
    }

    size_t size() const
    {
        return _size;
    }

    T* begin() const
    {
        return &_ptr[0];
    }

    T* end() const
    {
        return &_ptr[_idx];
    }

protected:
    void reallocate()
    {
        size_t new_size = 2 * _size;
        T* new_ptr = new T[new_size];
        std::copy(_ptr, _ptr+_size, new_ptr);
        std::swap(new_ptr, _ptr);
        delete [] new_ptr;
        _size = new_size;
    }

    void reallocate_move()
    {
        size_t new_size = 2 * _size;
        T* new_ptr = new T[new_size];
        for(size_t i = 0; i < _size; i++)
        {
            new_ptr[i] = std::move(_ptr[i]);
        }
        std::swap(new_ptr, _ptr);
        delete [] new_ptr;
        _size = new_size;
    }

private:

    T* _ptr;
    size_t _idx;
    size_t _size;
};


}
#endif // CONTAINER_HPP
