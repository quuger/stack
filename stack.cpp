#include <iostream>
#include <memory>

template <typename T, typename Alloc = std::allocator<T>>
class Stack {
private:
    T* data;
    size_t capacity;
    size_t size;
    Alloc allocator;

public:
    Stack() : capacity(1), size(0) {
        data = allocator.allocate(capacity);
    }

    ~Stack() {
        allocator.deallocate(data, capacity);
    }

    void push(const T& value) {
        if (size == capacity) {
            size_t new_capacity = capacity * 2;
            T* new_data;
            try {
                new_data = allocator.allocate(new_capacity);
            } catch (const std::bad_alloc& e) {
                std::cerr << "Failed to allocate memory: " << e.what() << std::endl;
                return;
            }
            for (size_t i = 0; i < size; ++i) {
                new_data[i] = std::move(data[i]);
            }
            allocator.deallocate(data, capacity);
            data = new_data;
            capacity = new_capacity;
        }
        data[size++] = value;
    }

    T pop() {
        if (size == 0) {
            throw std::out_of_range("Stack is empty");
        }
        return data[--size];
    }

    T& top() {
        if (size == 0) {
            throw std::out_of_range("Stack is empty");
        }
        return data[size - 1];
    }

    [[nodiscard]] bool empty() const {
        return size == 0;
    }
};
