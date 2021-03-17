#ifndef TEMPLATE_ARRAY
#define TEMPLATE_ARRAY

#include <stdexcept>

namespace dsc {
template <typename T>
class Array {
  public:
    Array() : data_{new T[2]{}}, size_{0}, capacity_{2} {}
	Array(std::size_t size) : size_{size}, data_{new T[size]{}} {} // constructor
	~Array() { delete[] data_; } // destructor
	Array(const dsc::Array& original) {
	  	
	}
	T& operator[](std::size_t i) { return data_[i]; }
	const T& operator[](std::size_t i) const { return data_[i]; }
	bool operator==(const dsc::Array& other) const {
	  if (size() != other.size()) { return false; }
	  
	  for(std::size_t i = 0; i < size(); i++) {
        if (array_[i] != other.array_[i]) { return false; }
      }
      return true;
	}
	bool operator!=(const dsc::Array& other) const {
		return !(*this == other);
	}
	Array& operator=(const dsc::Array&) {
		if (this == &other) {
			return *this;
		}
		
		size_ = other.size();
		capacity_ = other.capacity_;
		
		delete[] data_;
		data_ = new T[capacity()]{};
		
		for (std::size_t i = 0; i < size(); ++i) {
			(*this)[i] = other[i];
		}
		
		return *this;
	} // copy assignment
	std::size_t size() const { return size_; }
	std::size_t capacity() const { return capacity_; }
	
	T& at(std::size_t index) {
		if (index > size()) {
			throw std::out_of_range("index out of array bounds");
		} else {
			return array_[index];
		}
	}
	T& front() { return data_[0]; }
	T& back() { return data_[size() - 1]; }
	T* data() { return data_;}
	
	T* begin() { return data_; }
	T* end() { return data_ + size() }
	const T* begin() const { return data_; }
	const T* end() const { return data_ + size(); }
	
	void reserve(std::size_t n) {
		if (n <= capacity_) {
			return;
		}
		
		capacity_ = n;
		T* resized_array = new T[capacity_];
		for (std::size_t i = 0; i < size(); ++i) {
			resized_array[i] = data_[i];
		}
		
		delete[] data_;
		data_ = resized_array;
	}
	T pop_back() {
		T result = (*this)[size() - 1];
		(*this)[size() - 1] = nullptr;
		--size_;
		
		return result;
	}
	void push_back(T value) {
		if (size() < capacity()) {
			reserve(capacity());
		}
		(*this)[size()] = value;
		++size_;
	}
	void insert(T value, std::size_t index) {
		if (size() == capacity()) { reserve(capacity()); }
		for(std::size_t i = size() - 1; i > index; --i) {
			(*this)[i] = (*this)[i - 1];
		}
		++size_;
		(*this)[index] = value;
	}
	  
	private:
	  std::size_t size_{};
	  std::size_t capacity_{};
	  T* data_{};
}
} // namespace dsc

#endif // TEMPLATE_ARRAY
