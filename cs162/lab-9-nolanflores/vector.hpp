#ifndef VECTOR_HPP
#define VECTOR_HPP

template<typename T>
class vector {
private:
	T* data = nullptr;
	int num_data = 0;
	int num_elements = 0;
public:
	vector() = default;

	~vector() {
		if(this->data != nullptr){
			delete[] this->data;
			this->data = nullptr;
		}
	}

	vector(const vector<T>& other) {
		this->num_data = other.num_data;
		this->num_elements = other.num_elements;
		this->data = new T[this->num_elements];
		for(int i = 0; i < this->num_data; i++){
			this->data[i] = other.data[i];
		}
	}

	void operator=(const vector<T>& other) {
		if(this == &other){
			return;
		}
		if(this->data != nullptr){
			delete[] this->data;
		}
		this->num_data = other.num_data;
		if(this->num_elements < other.num_elements){
			this->num_elements = other.num_elements;
		}
		this->data = new T[this->num_elements];
		for(int i = 0; i < this->num_data; i++){
			this->data[i] = other.data[i];
		}
	}

	void push_back(const T& value) {
		if(this->num_elements == this->num_data){
			T* temp = new T[this->num_elements+1];
			for(int i = 0; i < this->num_data; i++){
				temp[i] = this->data[i];
			}
			temp[this->num_data] = value;
			delete[] this->data;
			this->data = temp;
			this->num_elements++;
		}else{
			this->data[this->num_data] = value;
		}
		this->num_data++;
	}

	int size() const {
		return this->num_data;
	}

	int capacity() const{
		return this->num_elements;
	}

	// TODO Implement an operator[] function. I've written the header for
	// you. The parameter is the index supplied to the square brackets when
	// indexing a vector. For example, in the context of my_vector[i], i is
	// the argument to this [] operator overload.
	T& operator[](int index) {
		// TODO Fix the below line of code. It's incorrect; it's just provided
		// as a placeholder to make the program compile.
		return data[index];
	}

	// The insert() function receives a value to insert and the index at which
	// to insert it in the vector. It should then insert the value at that
	// index, moving other elements over to make room for it (hint: much like
	// the push_back function, the insert function will need to create a new,
	// bigger array to make room for the new value)
	void insert(int index, const T& value) {
		if(this->num_elements == this->num_data){
			T* temp = new T[this->num_elements+1];
			for(int i = 0; i < index; i++){
				temp[i] = this->data[i];
			}
			temp[index] = value;
			for(int i = index + 1; i < this->num_data + 1; i++){
				temp[i] = this->data[i-1];
			}
			delete[] this->data;
			this->data = temp;
			this->num_elements++;
		}else{
			for(int i = this->num_data-1; i >= index; i--){
				this->data[i+1] = this->data[i];
				this->data[i] = value;
			}
		}
		this->num_data++;
	}

	void reserve(int n){
		if(this->num_elements < n){
			T* temp = new T[n];
			for(int i = 0; i < this->num_data; i++){
				temp[i] = this->data[i];
			}
			delete[] this->data;
			this->data = temp;
			this->num_elements = n;
		}
	}
};

#endif
