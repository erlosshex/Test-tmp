#ifndef _VECTOR_H_
#define _VECTOR_H_
#include <stddef.h>
#include <algorithm>
#include <memory>

template <typename T>
class Vector
{
    public:
        typedef T *iterator;
        typedef const T *const_iterator;
        typedef size_t size_type;
        typedef T value_type;

        class reverse_iterator
        {
            public:
                reverse_iterator(iterator it = NULL):current_(it) {}
                iterator base() const { return current_; }

                reverse_iterator &operator++()//前置
                {
                    --current_;
                    return *this;
                }

                reverse_iterator operator++(int)//后置
                {
                    reverse_iterator temp(*this);
                    --current_;
                    return temp;
                }

                reverse_iterator &operator--()
                {
                    ++current_;
                    return *this;
                }

                reverse_iterator operator--(int)
                {
                    reverse_iterator temp(*this);
                    ++current_;
                    return temp;
                }

                T &operator*()
                {
                    iterator temp = current_;
                    return *--temp;
                }

                T *operator->()
                {
                    iterator temp = current_;
                    return --temp;
                }

                friend bool operator==(const reverse_iterator &lhs,
                        const reverse_iterator &rhs)
                {
                    return lhs.current_ == rhs.current_;
                }
                friend bool operator!=(const reverse_iterator &lhs,
                        const reverse_iterator &rhs)
                {
                    return lhs.current_ != rhs.current_;
                }
            private:
                iterator current_;
        };

        Vector() { create(); }//无参构造函数
        explicit Vector(size_type n, const T &t = T()) { create(n, t); }
        Vector(const Vector &v) { create(v.begin(), v.end());}// 拷贝构造函数
        ~Vector() { uncreate();}

        Vector &operator=(const Vector &other);
        T &operator[] (size_type i) { return data_[i]; }
        const T &operator[] (size_type i) const {return data_[i]; }

        void push_back(const T &t);

        size_type size() const { return avail_ - data_;}
        size_type capacity()const { return limit_ - data_;}

        iterator begin() { return data_; }
        const_iterator begin() const {return data_;}
        iterator end() {return avail_;}
        const_iterator end() const { return avail_; }

        reverse_iterator rbegin(){return reverse_iterator(end());}
        reverse_iterator rend() {return reverse_iterator(begin());}

        void swap(Vector &rhs)
        {
            std::swap(data_, rhs.data_);
            std::swap(avail_, rhs.avail_);
            std::swap(limit_, rhs.limit_);
        }
    private:
        iterator data_;//首元素
        iterator avail_;//末尾元素的下一个
        iterator limit_;

        std::allocator<T> alloc_;//内存分配器

        void create();
        void create(size_type, const T &);
        void create(const_iterator, const_iterator);

        void  uncreate();

        void grow();
        void uncheckAppend(const T &);
};

    template <typename T>
inline Vector<T> &Vector<T>::operator=(const Vector &rhs)
{
    if(this != rhs)
    {
        uncreate();//释放原来的内存
        create(rhs.begin(), rhs.end());
    }
    return *this;
}

    template <typename T>
inline void Vector<T>::push_back(const T &t)
{
    if(avail_ == limit_)
    {
        grow();
    }
    uncheckAppend(t);
}

    template <typename T>
inline void Vector<T>::create()
{
    //分配空的数组
    data_ = avail_ = limit_ = 0;
}

    template <typename T>
inline void Vector<T>::create(size_type n, const T &val)
{
    //分配原始内存
    data_ = alloc_.allocate(n);
    limit_ = avail_ = data_ + n;
    //向原始内存填充元素
    std::uninitialized_fill(data_, limit_, val);
}

    template <typename T>
inline void Vector<T>::create(const_iterator i, const_iterator j)
{
    data_ = alloc_.allocate(j-i);
    limit_ = avail_ = std::uninitialized_copy(i, j, data_);
}

    template <typename T>
inline void Vector<T>::uncreate()
{
    if(data_)//逐个析构
    {
        iterator it = avail_;
        while(it != data_)
        {
            alloc_.destroy(--it);
        }
        alloc_.deallocate(data_, limit_ - data_ );//真正释放内存
    }
    data_ = limit_ = avail_ = 0;//重置指针
}

    template <typename T>
inline void Vector<T>::grow()
{
    //内存变为2倍
    size_type new_size = std::max(2 * (limit_ - data_), std::ptrdiff_t(1));
    //分配原始内存
    iterator new_data = alloc_.allocate(new_size);
    //复制元素
    iterator new_avail = std::uninitialized_copy(data_, avail_, new_data);

    uncreate();//释放以前内存

    data_ = new_data;
    avail_ = new_avail;
    limit_ = data_ + new_size;
}

    template <typename T>
inline void Vector<T>::uncheckAppend(const T &val)
{
    alloc_.construct(avail_++, val);
}

#endif /*VECTOR_H*/
