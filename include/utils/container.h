/**
 * @file container.h
 * @brief Contains the definition of the Container class template.
 * @author Matthieu FREITAG (Zapharaos)
 * @date 23/03/2023
 */

#ifndef PACMAN_CONTAINER_H
#define PACMAN_CONTAINER_H

/**
 * @brief A container class that holds a fixed amount of elements of type T.
 *
 * The Container class template is a fixed-size container that can hold elements
 * of any type T. The maximum number of elements that the container can hold
 * is determined by the template parameter N, which defaults to the maximum
 * legal size of the array for the type T.
 *
 * @tparam T The type of elements that the container can hold.
 * @tparam N The maximum number of elements that the container can hold
 */
template<typename T, int N = getMaximumLegalSize<T>()>
class Container
{

private:

    /** Array. */
    std::array <T, N> array_{};

public:

    /** Effective amount of elements. */
    int size_ = 0;

    /**
     * @brief Default constructor that creates an empty container.
     */
    inline constexpr Container() = default;

    /**
     * @brief Constructs a container with a given size and array of elements.
     * @param size The number of elements in the array.
     * @param array An array of elements of type T.
     */
    inline constexpr Container(int size, std::array<T, N> array) : size_(size), array_(shrinkArray<T, N>(array)) {}

    /**
     * @brief Reference accessor to array elements by index.
     * @param index The index of the element to retrieve.
     * @return A reference to the element at the given index.
     */
    T& operator[](std::size_t index)
    { return array_[index]; }

    /**
     * @brief Reference accessor to array elements by index.
     * @param index The index of the element to retrieve.
     * @return A reference to the element at the given index.
     */
    T& at(std::size_t index)
    { return array_.at(index); }

    /**
     * @brief Adds an element to the end of the container.
     * @tparam T Type of the elements in the container.
     * @param element Element to add to the container.
     */
    inline void emplace(T element)
    { array_[size_++] = element; }

    /**
     * Checks whether the container contains a specific element.
     * @tparam T Type of the elements in the container.
     * @param element Element to check for in the container.
     * @return True if the element is found in the container, false otherwise.
     */
    inline bool contains(T element) const
    { return std::find(array_.begin(), array_.end(), element) != array_.end(); }

    /**
     * @brief Iterator class for the Container class template.
     *
     * The Iterator class is a forward iterator that provides access to the
     * elements of the container.
     */
    class Iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        /**
         * @brief Constructor that creates an iterator from a pointer to an element of the container.
         * @param ptr Pointer to an element of the container.
         */
        Iterator(pointer ptr) : ptr_(ptr) {}

        /**
         * @brief Dereference operator that returns a reference to the element pointed to by the iterator.
         * @return A reference to the element pointed to by the iterator.
         */
        reference operator*() const { return *ptr_; }

        /**
         * @brief Member access operator that returns a pointer to the element pointed to by the iterator.
         * @return A pointer to the element pointed to by the iterator.
         */
        pointer operator->() const { return ptr_; }

        /**
         * @brief Pre-increment operator that moves the iterator to the next element in the container.
         * @return A reference to the iterator after it has been incremented.
         */
        Iterator& operator++() { ptr_++; return *this; }

        /**
         * @brief Post-increment operator that moves the iterator to the next element in the container.
         * @return A copy of the iterator before it has been incremented.
         */
        Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }

        /**
         * @brief Equality comparison operator that checks whether two iterators point to the same element in the container.
         * @param a The first iterator.
         * @param b The second iterator.
         * @return true if the two iterators point to the same element in the container, false otherwise.
         */
        friend bool operator== (const Iterator& a, const Iterator& b) { return a.ptr_ == b.ptr_; };

        /**
         * @brief Inequality comparison operator that checks whether two iterators point to different elements in the container.
         * @param a The first iterator.
         * @param b The second iterator.
         * @return true if the two iterators point to different elements in the container, false otherwise.
         */
        friend bool operator!= (const Iterator& a, const Iterator& b) { return a.ptr_ != b.ptr_; };

    private:
        pointer ptr_;
    };

    /**
     * Returns an iterator pointing to the first element in the container.
     * @return Iterator to the first element in the container.
     */
    Iterator begin() { return Iterator(&array_[0]); }

    /**
     * Returns an iterator pointing to the past-the-end element in the container.
     * @return Iterator to the past-the-end element in the container.
     */
    Iterator end() { return Iterator(&array_[size_]); }
};

#endif //PACMAN_CONTAINER_H
