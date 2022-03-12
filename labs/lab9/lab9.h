#pragma once
#include <iostream>
#include <fstream>
#include <sstream>

#include <string>
#include <vector>
#include <map>

#include <regex>
#include <cstddef>
#include <new>
#include <functional>

#define DB_FILE_PATH ".\\labs\\lab9\\files\\input.txt"
#define SEARCH_EXPRESSION "(?:\\s*\\[)\\s*([�-��-�\\w]+(?:\\s[�-��-�\\w]+)*)\\s*(?:\\]):\\s([�-��-�\\w\\-+().|:\\s]+);\\s*"

namespace lab9 
{
	using namespace std;

	namespace task0 
	{
		class TextDataBase
		{
			const string filename;
			fstream file_stream;
			static const regex expression;
		public:
			using DbResult = map<string, string>;

			explicit TextDataBase(string filename): filename(filename){ }
			~TextDataBase() { file_stream.close(); }

			string get_filename(void) const noexcept { return this->filename; }

			const vector<DbResult> get_data(string key);
			const bool sort_data(string key);
			const bool set_data(vector<DbResult> data);
		};

		void run(void);
	}

	namespace task1 
	{
		struct Student 
		{
			explicit Student(int record_book_id = 0, string name = "none")
				: record_book_id(record_book_id), name(name)
			{ }

			~Student() { }

			Student& operator=(const Student& copy) 
			{
				this->record_book_id = copy.get_id();
				this->name = copy.get_name();

				return *this;
			}

			void study(void) { cout << "� �����" << endl; }

			string get_name(void) const noexcept { return this->name; }
			int get_id(void) const noexcept { return this->record_book_id; }

		private:
			int record_book_id;
			string name;
		};

		template <typename T>
		class Array
		{
			T* myArray;
			size_t n;
		public:
			// ������ ��������:
			explicit Array(size_t size = 0, const T& value = T()) : n(size)
				// ����������� ������, ������� �������
				// Array ������� size, ����������� ����������
				// value ���� T. �������� ��� � ���� T ����
				// �����������, ������� ����� ������� ���
				// ��� ����������, ���� �� ��� �� �����.
			{
				this->myArray = new T[n] ;
				for (uint16_t i = 0; i < n; i++) this->myArray[i] = value;
			}
			explicit Array(const Array& mas) : n(mas.size())
				// ����������� �����������, ������� �������
				// ����� ���������. ��������, ��� ��� ����
				// T ��������� �������� ������������.
			{ 
				this->myArray = new T[n];
				for (int i = 0; i < n; i++) this->myArray[i] = mas[i];
			}
			~Array()
				// ����������, ���� �� ��� ���������.
			{
				delete[] myArray;
			}
			Array& operator=(const Array& mas)
				// �������� ������������.
			{
				delete[] this->myArray;
				this->n = mas.size();

				this->myArray = new T[mas.size()];
				for (int i = 0; i < mas.size(); i++) this->myArray[i] = mas[i];

				return *this;
			}
			//
			// ��� ������ ��������� ������� �� �������.
			T& operator[](size_t idx)
			{
				if (idx >= n) throw exception("������ ��� ���������� ��������� �������");
				return this->myArray[idx];
			}
			const T& operator[](size_t idx) const
			{
				if (idx >= n) throw exception("������ ��� ���������� ��������� �������");
				return this->myArray[idx];
			}
			size_t size() const { return this->n; }
		};

		void run(void);
	}

	namespace task2
	{
		struct Student
		{
			explicit Student(int record_book_id = 0, string name = "none")
				: record_book_id(record_book_id), name(name)
			{ }

			~Student() { }

			void study(void) { cout << "� �����" << endl; }

			string get_name(void) const noexcept { return this->name; }
			int get_id(void) const noexcept { return this->record_book_id; }

		private:
			int record_book_id;
			string name;
		};

		template <typename T>
		class Array
		{
		private:
			char* arrayBuffer;
			T* myArray;
			size_t n;
		public:
			// ������ ��������:
			explicit Array(size_t size = 0, const T& value = T()) : n(size)
				// ����������� ������, ������� �������
				// Array ������� size, ����������� ����������
				// value ���� T. �������� ��� � ���� T ����
				// �����������, ������� ����� ������� ���
				// ��� ����������, ���� �� ��� �� �����.
			{
				this->arrayBuffer = new char[n * sizeof(T)];
				this->myArray = (T*)arrayBuffer;

				for (uint16_t i = 0; i < n; i++) new(myArray + i) T(value);
			}
			Array(const Array& mas) : n(mas.size())
				// ����������� �����������, ������� �������
				// ����� ���������. ��������, ��� ��� ����
				// T ��������� �������� ������������.
			{
				this->arrayBuffer = new char[n * sizeof(T)];
				this->myArray = (T*)arrayBuffer;

				for (int i = 0; i < n; i++)new(myArray + i) T(mas[i]);
				
			}
			~Array()
				// ����������, ���� �� ��� ���������.
			{ 
				for (int i = 0; i < n; i++) this->myArray[i].~T();
				delete[] arrayBuffer;
			}
			Array& operator=(const Array& mas)
				// �������� ������������.
			{ 
				this->~Array();
				this->n = mas.size(); 

				this->arrayBuffer = new char[n * sizeof(T)];
				this->myArray = (T*)arrayBuffer;

				for (int i = 0; i < n; i++) 
				{
					new(myArray + i) T(mas[i]);
				}

				return *this;
			}
			// ��� ������ ��������� ������� �� �������.
			T& operator[](size_t idx)
			{
				if (idx >= n) throw exception("������ ��� ���������� ��������� �������");
				return this->myArray[idx];
			}
			const T& operator[](size_t idx) const
			{
				if (idx >= n) throw exception("������ ��� ���������� ��������� �������");
				return this->myArray[idx];
			}
			size_t size() const { return this->n; }
		};

		void run(void);
	}

	namespace task3 
	{
		using task1::Student;

		struct ICloneable
		{
			virtual ICloneable* clone() const = 0;
			virtual ~ICloneable() { }
		};
		// ������ ValueHolder � ������� ���������� T,
		// ������ ��������� ���� �������� ���� data_
		// ���� T.
		// � ������� ValueHolder ������ ���� ���������
		// ����������� �� ������ ��������� ���� T,
		// ������� �������������� ���� data_.
		//
		// ������ ValueHolder ������ �������������
		// ��������� ICloneable, � ���������� ���������
		// �� ����� ������� ��������� � ���� �� ������
		// clone.

		template<typename T>
		struct ValueHolder : public ICloneable 
		{
			T _data;

			explicit ValueHolder(const T& value): _data(value) { }
			~ValueHolder() { }

			ICloneable* clone() const { return new ValueHolder(_data); }
		};

		void run(void);
	}

	namespace task4 
	{
		struct CustomTypeT
		{
			string name;
			int value;
			explicit CustomTypeT(string name = "none", int value = 1) : name(name), value(value) { }
		};

		struct CustomTypeU
		{
			int value, id;
			explicit CustomTypeU(int id = 0, int value = 1): id(id), value(value) { }
		
			operator CustomTypeT() 
			{
				return CustomTypeT(to_string(id), value);
			}
		};

		template<class T, class U>
		void copy_n(T* copy, U* origin, uint16_t size) 
		{
			size_t origin_size = sizeof(origin) / sizeof(U),
				copy_size = sizeof(copy) / sizeof(T);

			if (size > origin_size || size > copy_size) throw exception("������� �� ������������");

			for (uint16_t i = 0; i < size; i++) copy[i] = origin[i];
		}

		void run(void);
	}

	namespace task5
	{
		struct Student
		{
			explicit Student(string name = "", int age = 0) : name(name), age(age) { }

			string get_name(void) const noexcept { return name; }
			int get_age(void) const noexcept { return age; }

			static bool comparator(Student value1, Student value2) 
			{
				return value1.age > value2.age;
			}

		private:
			string name;
			int age;
		};

		template <typename T>
		class Array
		{
		public:
			explicit Array(size_t size = 0, const T& value = T())
				: size_(size)
			{
				this->data_ = new T[size_];
				for (uint16_t i = 0; i < size_; i++) this->data_[i] = value;
			}

			Array(const Array& other) : size_(other.size())
			{
				this->data_ = new T[size_];
				for (uint16_t i = 0; i < size_; i++)this->data_[i] = other[i];
			}
			~Array()
			{
				delete[] this->data_;
			}

			Array& operator=(Array other);
			void swap(Array& other);

			size_t size() const { return this->size_; }

			T& operator[](size_t idx)
			{
				if (idx >= size_) throw exception("������ ��� ���������� ��������� �������");
				return this->data_[idx];
			}

			const T& operator[](size_t idx) const
			{
				if (idx >= size_) throw exception("������ ��� ���������� ��������� �������");
				return this->data_[idx];
			}

		private:
			size_t size_;
			T* data_;
		};

		template<typename T>
		Array<T>& Array<T>::operator=(Array other)
		{
			delete[] this->data_;

			this->size_ = other.size();
			this->data_ = new T[size_];

			for (uint16_t i = 0; i < size_; i++) this->data_[i] = other[i];

			return *this;
		}

		template<typename T>
		void Array<T>::swap(Array& other)
		{
			Array<T> buffer = this->data_;
			this->data_ = other;
			other = buffer;
		}

		template<class T, class C = function<bool(T, T)>>
		T minimum(Array<T> arr, C comparator)
		{
			T min = arr[0];
			for (uint16_t i = 1; i < arr.size(); i++) 
			{
				if (!comparator(min, arr[i])) min = arr[i];
			}
			return min;
		}

		void run(void);
	}
 
	namespace task6
	{
		using task5::Array;

		template<class T>
		void flatten(const Array<T>& arr, ostream& out) 
		{
			for (uint16_t i = 0; i < arr.size(); i++) out << arr[i] << endl;
		}

		template<class T>
		void flatten(const Array<Array<T>>& arr, ostream& out)
		{
			for (uint16_t i = 0; i < arr.size(); i++) flatten(arr[i], out);
		}

		void run(void);
	}

	namespace task7
	{
		using task3::ICloneable;
		using task3::ValueHolder;
		// ��� �����, ������� ��� ����� �����������
		class Any
		{
			ICloneable* value;
		public:
			// � ������ Any ������ ���� �����������, ������� ����� �������
			// ��� ����������, ����� ������� ��������� ���:
			// Any empty; // empty ������ �� ������
			explicit Any() : value(nullptr) { }

			// � ������ Any ������ ���� ��������� ����������� �� ������
			// ���������, ����� ����� ���� ��������� ������� ���� Any,
			// ��������, ��������� �������:
			// Any i(10); // i ������ �������� 10
			template<class T>
			explicit Any(T value) : value(new ValueHolder<T>(value))
			{ }

			// ����������: ���������� ������� ����� ����������.
			virtual ~Any() { delete value; }
			
			// � ������ Any ����� ������ ���� ����������� ����������� (���
			// ������� ����� clone ���������� ICloneable)
			explicit Any(const Any& origin) : value(origin.value->clone())
			{ }

			// � ������ ������ ���� �������� ������������ �/��� ���������
			// �������� ������������, ����� ������� ��������� ���:
			// Any copy(i); // copy ������ 10, ��� � i
			// empty = copy; // empty ������ 10, ��� � copy
			// empty = 0; // � ������ empty ������ 0
			template<class T>
			Any& operator=(const T& obj) 
			{
				delete this->value;
				this->value = new ValueHolder<T>(obj);

				return *this;
			}

			Any& operator=(const Any& obj)
			{
				delete this->value;
				this->value = obj.value->clone();

				return *this;
			}

			// ����� �������� �������� ��������, ���������� � ������ Any
			// ��������� ����� cast, ������� ���������� ��������� ��
			// �������� ��������, ��� ������� ��������� � ������
			// �������������� ����� ��� ���� ������ Any ������ �� ������:
			// int *iptr = i.cast<int>(); // *iptr == 10
			// char *cptr = i.cast<char>(); // cptr == 0,
			// // ������ ��� i ������ int, � �� char
			// Any empty2;
			// int *p = empty2.cast<int>(); // p == 0
			// ��� ���������� ����������� dynamic_cast.
			template<class T>
			const T* cast(void) const 
			{
				if (!value) throw exception("������ ��������");

				ValueHolder<T>* buffer = dynamic_cast<ValueHolder<T>*>(value);
				if (buffer) return &buffer->_data;
				
				return 0;
			}


		};
		void run(void);
	}

	namespace task8
	{

		template<class T1, class T2>
		struct SameType { static const bool value; };

		template<class T1, class T2> const bool SameType<T1, T2>::value = false;

		template<class T>
		struct SameType<T, T> { static const bool value; };

		template<class T> const bool SameType<T, T>::value = true;

		void run(void);
	}

	namespace task9
	{
		template<class T, uint16_t S> 
		uint16_t array_size(T (&arr)[S]) { return sizeof(arr) / sizeof(T); }

		void run(void);
	}

	void lab(void);
}