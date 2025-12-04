#include <iostream>
#include <fstream>
#include <string>
#include <vector>
void check_file(std::ifstream&);
void check_file(std::ofstream&);
void finput_borders(int32_t&, int32_t&);
bool is_delim(const char, const std::string&);
void finput_rules(std::string&, int32_t&, int32_t&, std::ifstream&);
bool is_number(const char);
std::string extract_numbers(std::string&, const std::string, int32_t, int32_t);
bool is_inside(const int32_t, const int32_t, const int32_t);
int main()
{
	try
	{
		std::ifstream fin("input.txt");
		check_file(fin);
		std::ofstream fout("output.txt");
		check_file(fout);
		std::string line{};
		std::string delimiters{};
		int32_t left{};
		int32_t right{};
		finput_rules(delimiters, left, right, fin);
		while (std::getline(fin, line))
		{
			std::string numbers = extract_numbers(line, delimiters, left, right);
			if (!numbers.empty())
			{
				fout << numbers << " || ";
			}
			fout << line << std::endl;
		}
		std::cout << "text in output.txt";
	}
	catch (const char* message) // я так и не придумал подходящий тип исключений 
	{
		std::cout << message; 
	}
	return 0;
}
void check_file(std::ifstream& fin)
{
	if (!fin.good())
	{
		fin.close();
		throw "file doesnt exist";
	}
	if (fin.peek() == EOF)
	{
		fin.close();
		throw "file is empty";
	}
}
void check_file(std::ofstream& fout)
{
	if (!fout.good())
	{
		fout.close();
		throw "file doesnt exist";
	}
}
bool is_delim(const char symbol, const std::string& delimiters)
{
	bool is_del{};
	size_t delim_lenght = delimiters.size();
	for (size_t i = 0; i < delim_lenght; i++)
	{
		if (symbol == delimiters[i])
		{
			is_del = 1;
			break;
		}
	}
	return is_del;
}
void finput_borders(int32_t& left, int32_t& right, std::ifstream& fin)
{
	fin >> left >> right;
	if (left >= right)
	{
		throw "invalid borders";
	}
}
void finput_rules(std::string& delimiters, int32_t& left, int32_t& right, std::ifstream& fin)
{
	std::getline(fin, delimiters);
	if (delimiters.size() == 0)
	{
		throw "emply delimiters list";
	}
	finput_borders(left, right, fin);
	fin.ignore();
}
std::string extract_numbers(std::string& line, const std::string delimiters, int32_t left, int32_t right)
{
	size_t numbers_in_a_row{};
	std::string numbers{};
	size_t lenght = line.size();
	line.push_back(delimiters[0]);
	for (size_t i = 0; i < lenght; ++i)
	{
		if (is_number(line[i]))
		{
			numbers_in_a_row++;
			if (is_delim(line[i + 1], delimiters))
			{
				std::string number = line.substr(i - numbers_in_a_row + 1, numbers_in_a_row);
				if (is_inside(stoi(number), left, right))
				{

 					line.erase(i - numbers_in_a_row + 1, numbers_in_a_row);
					numbers += number + ' ';
					lenght -= numbers_in_a_row;
					i -= numbers_in_a_row;
				}
				numbers_in_a_row = 0;
			}
		}
		else
		{
			numbers_in_a_row = 0;
		}
	}
	line.pop_back();
	return numbers;
}
bool is_number(const char symbol)
{
	return ((symbol >= '0') && (symbol <= '9'));
}
bool is_inside(const int32_t number, const int32_t left, const int32_t right)
{
	return ((number >= left) && (number <= right));
}