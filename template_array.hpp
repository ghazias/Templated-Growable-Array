#ifndef TEMPLATE_ARRAY
#define TEMPLATE_ARRAY

#include <stdexcept>

constexpr std::size_t DEFAULTCAP = 3;

namespace dsc {
template <typename T>
class Array {
  public:
    Array() : data_{new T[DEFAULTCAP]{}}, size_{0}, capacity_{DEFAULTCAP} {} // empty constructor
	Array(std::size_t size) : data_{new T[size]{}}, size_{0}, capacity_{size} {} // constructor
	~Array() { delete[] data_; } // destructor
	Array(const Array& original) : data_{new T[original.capacity()]{}}, size_{original.size()}, capacity_{original.capacity()} {
	  	for (std::size_t i = 0; i < size(); i++) { data_[i] = original[i]; }
	} // copy constructor

	Array(Array&& other) : data_{other.data()}, size_{other.size()}, capacity_{other.capacity()} {
		other.data_ = nullptr;
	} // move constructor

	T& operator[](std::size_t i) { return data_[i]; } // index dereference operator
	const T& operator[](std::size_t i) const { return data_[i]; }
	bool operator==(const Array& other) const {
	  if (size() != other.size()) { return false; }

	  for(std::size_t i = 0; i < size(); ++i) {
        if (data_[i] != other.data_[i]) { return false; }
      }
      return true;
	} // equality operator
	bool operator!=(const Array& other) const {
		return !(*this == other);
	}
	Array& operator=(const Array& other) {
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
	
	Array& operator=(Array&& other) {
		if (this != other) {
			delete[] data_;
			data_ = other.data_;
			other.data_ = nullptr;
		}
		
		return *this;
	} // move assignment
	std::size_t size() const { return size_; }
	std::size_t capacity() const { return capacity_; }
	
	T& at(std::size_t index) {
		if (index > size() || index < 0 || size() == 0) {
			throw std::out_of_range("index out of array bounds");
		} else {
			return data_[index];
		}
	}
	
	const T& at(std::size_t index) const {
		if (index > size() || index < 0 || size() == 0) {
			throw std::out_of_range("index out of array bounds");
		} else { 
			return data_[index];
		}
	}
	T& front() { return data_[0]; }
	T& back() { return data_[size() - 1]; }
	T* data() { return data_; }
	
	T* begin() { return data_; }
	T* end() { return data_ + size(); }
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
	  T* data_{};
	  std::size_t size_{};
	  std::size_t capacity_{};
};
} // namespace dsc

#endif // TEMPLATE_ARRAY
