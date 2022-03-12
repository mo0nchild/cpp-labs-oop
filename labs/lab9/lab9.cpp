#include "lab9.h"

using namespace lab9;

const regex task0::TextDataBase::expression(SEARCH_EXPRESSION);

const vector<task0::TextDataBase::DbResult> task0::TextDataBase::get_data(string key)
{
	vector<DbResult> result;
	smatch list;

	this->file_stream = fstream(this->filename, ios::in);

	if (file_stream.is_open())
	{
		string line("");
		while (!file_stream.eof())
		{
			DbResult data_row;
			bool found_trigger = false;

			getline(file_stream, line);

			while (regex_search(line, list, expression))
			{
				if (list[1] == key || key == "") found_trigger = true;

				data_row.insert(pair<string, string>(list[1], list[2]));
				line = list.suffix();
			}
			if(found_trigger) result.push_back(data_row);
		}
		this->file_stream.close();
	}

	return result;
}

const bool task0::TextDataBase::sort_data(string key)
{
	vector<DbResult> data = this->get_data("");
	if (data.size() == 0) return false;
	
	uint16_t size = data.size();

	for (uint16_t i = 0; i < size - 1; i++)
	{
		for (uint16_t j = i + 1; j < size; j++)
		{
			if (data[i].find(key) == data[i].end()) swap<DbResult>(data[size-- - 1], data[i]);
			if (data[j].find(key) == data[j].end()) swap<DbResult>(data[size-- - 1], data[j]);

			if (size == i || size == j) continue;
			
			try 
			{
				int buffer_i = stoi(data[i][key]), buffer_j = stoi(data[j][key]);
				if (buffer_i < buffer_j) swap<DbResult>(data[i], data[j]);
				
			}
			catch (std::exception const&) { return false; }

		}
	}

	this->file_stream = fstream(this->filename, ios::out);
	if (file_stream.is_open()) 
	{
		for (auto i : data) 
		{
			for (auto k : i) file_stream << "[" << k.first << "]: " << k.second << ";\t";
			file_stream << endl;
		}

		file_stream.close();
		return true;
	}

	return false;
}

const bool task0::TextDataBase::set_data(vector<task0::TextDataBase::DbResult> data)
{
	this->file_stream = fstream(this->filename, ios::app);
	stringstream str_buffer;
	
	if (file_stream.is_open())
	{
		file_stream << endl;
		for (auto row : data) 
		{
			for (auto i : row) str_buffer << "[" << i.first << "]: " << i.second << ";\t";
			file_stream << str_buffer.str() << endl;
			str_buffer.str("");
		}

		this->file_stream.close();
		return true;
	}

	return false;
}

void task0::run(void)
{
	TextDataBase db(DB_FILE_PATH);

	// добавление данных в файл
	TextDataBase::DbResult newdata 
	{ 
		pair<string, string>("Дата и время соединения", "25.10.2012|11:01:00"),
		pair<string, string>("Номер абонента", "+7-(980)-694-20-00"),
		pair<string, string>("Продолжительность соединения", "01:00:40"),
		pair<string, string>("Стоимость переговоров", "1000 руб"),
	};

	if (!db.set_data(vector<TextDataBase::DbResult>{newdata})) cout << "fail" << endl;

	// сортировка данных в файле
	if (db.sort_data("Стоимость переговоров"))
	{
		cout << "Данные отсортированы по параметру" << endl << endl;
	}
	else cout << "Ошибка в сортировке" << endl << endl;

	// получение данных их файла
	const auto data = db.get_data("Номер абонента");
	for (auto i : data) 
	{
		for (auto j : i) cout << j.first << " = " << j.second << endl;
		cout << endl;
	}
}

void task1::run(void) 
{
	const Array<Student> int_array(5, Student(123, "Stepan"));
	Array<Student> int_array_clone(10, Student(321, "Viktor"));

	int_array_clone = int_array;
	int_array_clone[int_array_clone.size() - 1] = Student(123123, "Aleksiy");

	for (int i = 0; i < int_array_clone.size(); i++)
	{
		const auto a = int_array_clone[i];
		cout << "Значение" << i << ":\t" << a.get_name() << endl;
	}
}

void task2::run(void) 
{
	const Array<Student> int_array(5, Student(123, "Stepan"));
	Array<Student> int_array_clone(10, Student(321, "Viktor"));

	int_array_clone = int_array;
	int_array_clone[int_array_clone.size() - 1] = Student(123123, "Aleksiy");

	for (int i = 0; i < int_array_clone.size(); i++)
	{
		const auto a = int_array_clone[i];
		cout << a.get_name() << endl;
	}
}

void task3::run(void) 
{
	ICloneable* origin = new ValueHolder<int>(123);
	ICloneable* copy = origin->clone();
	delete origin;

	cout << "Значение: " << dynamic_cast<ValueHolder<int>*>(copy)->_data << endl;
	delete copy;
}

void task4::run(void) 
{
	int ints[] = { 1, 2, 3, 4 };
	double doubles[4] = {};
	copy_n(doubles, ints, 4);
	// теперь в массиве doubles содержатся
	// элементы 1.0, 2.0, 3.0 и 4.0
	for (int i = 0; i < 4; i++) cout << "Значение" << i + 1 << ":\t" << doubles[i] << endl;
	cout << endl;

	CustomTypeU origin[3] = { CustomTypeU(1, 12300), CustomTypeU(2,23411), CustomTypeU(3, 12959)};
	CustomTypeT copies[3];

	copy_n<CustomTypeT, CustomTypeU>(copies, origin, 3);
	for (int i = 0; i < 3; i++) cout << "Значение" << i + 1 << ":\t" << copies[i].name << " " << copies[i].value << endl;
}

void task5::run(void) 
{
	struct Greater
	{
		bool operator()(int a, int b) { return b < a; }
	};

	Array<int> ints(3);
	ints[0] = 10;
	ints[1] = 2;
	ints[2] = 15;
	int min = minimum<int>(ints, [](int a, int b) { return a < b; }); // в min должно попасть 2
	int max = minimum<int>(ints, Greater()); // в max должно попасть 15
	cout << "min: " << min << endl;
	cout << "max: " << max << endl;
	
	Array<Student> students(3);
	students[0] = Student("Ivan", 10);
	students[1] = Student("Oleg", 32);
	students[2] = Student("Igor", 4);

	Student older = minimum<Student>(students, Student::comparator);
	cout << "name: " << older.get_name() << endl;

}

void task6::run(void) 
{
	Array<int> ints(2, 0);
	ints[0] = 10;
	ints[1] = 20;
	cout << "Array<int>" << endl;
	flatten(ints, std::cout); // выводит на экран строку "10 20"
	cout << endl << "--------------------" << endl << endl;

	cout << "Array<Array<int>>" << endl;
	Array<Array<int>> array_of_ints(2, ints);
	flatten(array_of_ints, std::cout);
	cout << endl << "--------------------" << endl << endl;

	cout << "Array<Array<Array<int>>>" << endl;
	Array<Array<Array<int>>> array_of_array_of_int(3, array_of_ints);
	flatten(array_of_array_of_int, std::cout);
	cout << endl << "--------------------" << endl << endl;

	// выводит на экран строку "10 20 10 20"
	cout << "Array<double>" << endl;
	Array<double> doubles(10, 0.0);
	flatten(doubles, std::cout);
	cout << endl << "--------------------" << endl << endl;
	// работать должно не только для типа int
} 

void task7::run(void) 
{
	Any data(10);
	data = 100;

	try 
	{
		const string* caster = data.cast<string>();
		if (caster) cout << *caster << endl;
		else cout << "Преобразование не удалось\n";
	}
	catch (exception& error) { cout << error.what() << endl; }
}

void task8::run(void) 
{
	struct Dummy { };
	typedef int type;
	std::cout << "Значение: " << SameType<int, int>::value << std::endl;
	// выведет 1, т. е. true
	std::cout << "Значение: " << SameType<int, type>::value << std::endl;
	// 1, type == int
	std::cout << "Значение: " << SameType<int, int&>::value << std::endl;
	// 0, int и ссылка на int - различные типы
	std::cout << "Значение: " << SameType<Dummy, Dummy>::value << std::endl; // 1
	std::cout << "Значение: " << SameType<int, const int>::value << std::endl;

	// 0, const - часть типа
	// Определите шаблон SameType с двумя типовыми параметрами.
	// В шаблоне должна быть определена одна статическая константа // типа bool с именем value
}

void task9::run(void) 
{
	int value[4] = { 123, 23, 10, 20 };
	uint16_t size = array_size(value);

	cout << "value size: " << size << endl;

	struct Student 
	{
		string name;
		int age;
	};

	Student data[3] = { {"mike1", 10}, {"frenk", 12}, {"jane", 32} };

	size = array_size(data);
	cout << "data size: " << size << endl;

	/*int* pointer = &value[0];
	size = array_size(pointer);*/
}

void lab9::lab(void) 
{
	task9::run();
}