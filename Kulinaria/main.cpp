#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <iterator>
#include <algorithm>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <ctime>
#include <time.h>
#include<windows.h>
using namespace std;

map <string, int> Vlezaet (map <string, int> Fridge, map <string, int> Recept, int& Bad_flag)
{
	map <string, int> Zapas(Fridge);

	Bad_flag = 0;
	for (auto it = Recept.begin(); it != Recept.end(); ++it)
	{
		for (auto id = Zapas.begin(); id != Zapas.end(); ++id) //���������� ������ ������������
		{
			if (id->first == it->first)
			{
				if (id->second < it->second)     //���� 20 ������ ������ ��� 2 ����� �� ���� ������ ��� ��������  ���� � �������� ������ ��� �����
				{
					Bad_flag = 5; //�������� ��� ���� �� ��� �� ������� �������
				}
				else
				{
					id->second = (id->second - it->second); 
				}
			}
		} 
	}

	if (Bad_flag == 5) {
		//std::cout << " NE_XVATILO - znasenie bad flag =  " << Bad_flag << endl;
		return Fridge;
	}
	else {
		//std::cout << " ______ZASHIBIS - znasenie bad flag =  " << Bad_flag << endl;
		return Zapas;//������� � ������� ���-�� �������� ����� ������� 
	}
};

int Bread_crumb(map <string, int> Zapas) {
	int Ostatok = 0;
	for (auto id = Zapas.begin(); id != Zapas.end(); ++id) 
	{
		Ostatok += id->second;
	}
	return Ostatok;
};



int Dish_of_the_day(map <string, int> Fridge, map <string, int> Recept, map <string, int> Recept2) { //����� ����� �������� ������ ������������
	if (Recept == Recept2) { //��� ������� �����
		return 50;
	}

	int Flag = 0;
	int Flag2 = 0;
	map <string, int> Zapas = Vlezaet(Fridge, Recept, Flag); //������� �������� ����� ������� �������
	map <string, int> Zapas2 = Vlezaet(Fridge, Recept2, Flag2); //������� �������� ����� �������


	if (Flag == 5) { //��� ������� �����
		return 10;
	}
	if (Flag2 == 5) { //��� ������� �����
		return 20;
	}

	if (Bread_crumb(Zapas) > Bread_crumb(Zapas2)) { //���� ��� ������������� Recept �� ��������� ������ ������������ ��� ��� 2 �������� ��
		return 0;
	}
	else {//���� recept 2 �������� ����� ���������, � ������ ������ ��� ��������
		return 2;
	}
    
	//������������� Dish_of_the_day
	//������� 0 - ������ recept ������ ������ �������������
	//������� 2 - ������ recept2 ��� ������ ������ �������������
	//������� 10 - ������ recept �� ������� � ������ ���
	//������� 20 - ������ recept �� ������� � ������ ���
	//������� 50 - ������ ��� ����������
};


void LoadObj(ifstream &fin, map <string, int> &Borsch) {
	string name, s;
	int n;
	if (fin.is_open())
	{
		//cout << " HERE " << endl;
		while (fin >> name)
		{
			//cout << " HERE_ " << endl;
			getline(fin, s);
			istringstream iss(s);
			n = 0;
			while (iss >> n)
				Borsch.insert(make_pair(name, n));

		}
	}

}

void Print_vec(vector <int> Flags) {
	for (auto i = 0; i < size(Flags); ++i)
	{
			std::cout << Flags[i] << " "; //����� �� ����� ���� ����� 
	}
	cout <<  " ____END " << endl;
};
void Print_vec(vector <string> Flags) {
	for (auto i = 0; i < size(Flags); ++i)
	{
		std::cout << Flags[i] << "   "; //����� �� ����� ���� ����� 
	}
	cout << " ____END " << endl;
};

void Print_vec_p(vector <string> Flags) {
	for (auto i = 0; i < size(Flags); ++i)
	{
		std::cout << Flags[i] << endl; //����� �� ����� ���� ����� 
	}
	//cout << " ____END " << endl;
};

int Count_int_in_vec(vector <int> Flags,int d) {
	int a = 0;
	for (auto i = 0; i < size(Flags); ++i)
	{
		if (Flags[i] == d)
			a++;
	}
	return a;
};

void FILL_vec(vector <int>&Flags) {
	for (auto i = 0; i < size(Flags); ++i)
	{
		Flags[i] = 0;
	}
};

void FILL_vec(vector <int>&Flags, int k) {
	for (auto i = 0; i < size(Flags); ++i)
	{
		Flags[i] = k;
	}
};

void Print_map(map <string, int> Borsch) {
	for (auto it = Borsch.begin(); it != Borsch.end(); ++it)
		{
		cout << it->first << " : " << it->second << endl; //����� �� ����� ���� �����
		}
};

void Print_map(unordered_map <string, int> Borsch) {
	for (auto it = Borsch.begin(); it != Borsch.end(); ++it)
	{
		cout << it->first << " : " << it->second << endl; //����� �� ����� ���� �����
	}
};



int All_Zero_in_line(map <string, int> Fridge, unordered_map <string, map<string, int>>::iterator Point, unordered_map <string, map<string, int>> Name_i_Recept)
{
	vector <int> Flags(Name_i_Recept.size());
	int k = 0;
	int f = 0;
	int counter = 0;//������� �����	
	int counter_main = 0;//������� �����	
	for (auto Recept = Name_i_Recept.begin(); Recept != Name_i_Recept.end(); ++Recept) //������ �� ������� ���������� ������ �������� � ���� ������������� ��� ������ ���� ��� ��������� ����, � ���� ����� "�������� ������ ���� ���..." � ������ ������ � i j ��� map
	{
		f = Dish_of_the_day(Fridge, Point->second, Recept->second); //�������� ��������� ��������� � ����������
																	//������������� Dish_of_the_day
																	//������� 0 - ������ recept ������ ������ �������������
																	//������� 2 - ������ recept2 ��� ������ ������ �������������
																	//������� 10 - ������ recept �� ������� � ������ ���
																	//������� 20 - ������ recept �� ������� � ������ ���
																	//������� 50 - ������ ��� ����������
		//std::cout << "  PAIRS  ____statyc-dynamic_______" << Point->first << "___" << Recept->first <<"  FLAG   "<< f<< endl;
		Flags[k] = f;
		k++;
	}
	//Print_vec(Flags);
	return Count_int_in_vec(Flags, 0);//������� ���-�� ����� � ��������� �������
};

int Max_element_numer(vector <int>Flags) {
	std::vector<int>::iterator result;
	int index = -1;
	result = std::max_element(Flags.begin(), Flags.end());
	index = std::distance(Flags.begin(), result);
	return index;
}


int Find_allocation_of_the_BEST_recept_of_group(map <string, int> &Fridge, unordered_map <string, map<string, int>>&Name_i_Recept, vector <string>&Allocation, int &flagosi) { //��������� ��� �� ������ �.� ������� ������ ������� ��� ������������ � ��������� ��� � ��������

	//auto RECEPT_Pointer = --(Name_i_Recept.end());
	const int Size = Name_i_Recept.size();
	vector <int> Flags(Size);
	FILL_vec(Flags, -1);
	int counto = 0;
	int point = -1;
	flagosi = -1;
	for (auto Recept = Name_i_Recept.begin(); Recept != Name_i_Recept.end(); ++Recept)
	{
		point = All_Zero_in_line(Fridge, Recept, Name_i_Recept);
		//cout << "All_Zero_in_line_____" << All_Zero_in_line(Fridge, Recept, Name_i_Recept) << endl; //������ ����� ���-�� ����� �.� ��������� ������� ������������ ������ � ������
		Flags[counto] = point;
		counto++;
		/*if (All_Zero_in_line(Fridge, Recept, Name_i_Recept)) //���� �������� ��� ��
		{
		Fridge = Vlezaet(Fridge, Recept->second, flag);
		cout << flag << "FLAG" << endl;
		Allocation[counto] = Recept->first;
		cout << Allocation[counto];
		}
		cout << counto << "__counto" << endl;
		counto++;*/
	}
	//Print_vec(Flags);
	int num = Max_element_numer(Flags); //������ 1
	auto Recept = Name_i_Recept.begin();
	std::advance(Recept, num); //��������� �� ��������

	Fridge = Vlezaet(Fridge, Recept->second, flagosi);
	if (flagosi == 5) return 5;
	else {
		Allocation.push_back(Recept->first);
		Name_i_Recept.erase(Recept->first);
		return 0;
	}
}


/*void Heavy_lite_Ostatki(map <string, int> Fridge, unordered_map <string, map<string, int>> Name_i_Recept, vector <int>&Schwere) {  //Schwere - �������
	//������ ��� ������� �������, ���� ������ �� ������� �� ������ -1
	int Flag = 0;
	map <string, int> Fridge2;
	for (auto Recept = Name_i_Recept.begin(); Recept != Name_i_Recept.end(); ++Recept)
	{
		Fridge2 = Vlezaet(Fridge, Recept->second, Flag);
		if (Flag == 5) Schwere.push_back(-1);
		else
		Schwere.push_back(Bread_crumb(Fridge) - Bread_crumb(Fridge2));
		std::cout << Recept->first << " : " << Schwere[std::distance(Name_i_Recept.begin(), Recept)] << endl;
	}
	//std::reverse(Schwere.begin(), Schwere.end());
};*/

/*unordered_map <string, int> Heavy_lite_Ostatki(map <string, int>Fridge, unordered_map <string, map<string, int>> Name_i_Recept, int& Bad_flag) {  //Schwere - �������
	//������ ��� ������� �������, ���� ������ �� ������� �� ������ -1
	unordered_map <string, int> Schwere;
	map <string, int> Fridge2(Fridge);
	for (auto Recept = Name_i_Recept.begin(); Recept != Name_i_Recept.end(); ++Recept)
	{
		std::cout << " _____________________ " << endl;
		std::cout << " _FRIDGE_BEFORE_ " <<endl;
		Print_map(Fridge2);
		Fridge2 = Vlezaet(Fridge, Recept->second, Bad_flag); //������� ������������ ����� ���������� ������� + ������ ����������� ��� ���������
		std::cout << " _FRIDGE_AFTER_ " << endl;
		Print_map(Fridge2);
		std::cout << " _____________________ " << endl;
		if (Bad_flag == 5) 
			Schwere.emplace(Recept->first, -1);
		else
			Schwere.emplace(Recept->first, Bread_crumb(Fridge) - Bread_crumb(Fridge2));
		//std::cout << Recept->first << " : " << Schwere[std::distance(Name_i_Recept.begin(), Recept)] << endl;

	}
	//std::reverse(Schwere.begin(), Schwere.end());
	//Print_map(Schwere);
	return Schwere;
};*/

/*int Find_max(unordered_map <string, int> Schwere) { //������ ����� �������
	int max = -999;
	int result_iter = -1;
	for (auto iter = Schwere.begin(); iter != Schwere.end(); ++iter)
	{
		if (iter->second > max) {
			result_iter = std::distance(Schwere.begin(), iter);
			max = iter->second;
		}
	}
	return result_iter;
};*/

/*void Find_Best_Way(map <string, int> Fridge, unordered_map <string, map<string, int>> Name_i_Recept, unordered_map <string, int>&Schwere, int& Bad_flag) {
	/*unordered_map <string, int>::iterator it = Schwere.begin();
	int pos = Find_max(Schwere); //ITERATOR ��������� �� ���������� ������� � ����� ���� (����)
	std::advance(it, pos);
	//cout <<pos<< "��������" << endl;
	string max_name = it->first; //soup
	int max_int = it->second; //2429
	std::cout << max_name << " : " << max_int << endl;
	Print_map(Schwere);
	std::cout <<  " ____________________ " << endl;
	Schwere.erase(it); //������� ���
	Print_map(Schwere);
	std::cout << " ____________________ " << endl;
	Schwere = Heavy_lite_Ostatki(Fridge, Name_i_Recept, Bad_flag); //��������� ����, ������� ������� ������ ��� ���������� ���???
	Print_map(Schwere);
	std::cout << " ____________________ " << endl;
	/*it = Schwere.begin();
	pos = Find_max(Schwere);
	std::advance(it, pos);
	max_name = it->first; //soup
	max_int = it->second; //2429
	std::cout << max_name << " : " << max_int << endl;
	//if ()
	

	//Heavy_lite_Ostatki(Fridge, Name_i_Recept, Fridge2, Bad_flag);
};*/


int weight_of_map(map <string, int> Schwere) {
	int w = 0;
	for (auto Recept = Schwere.begin(); Recept != Schwere.end(); ++Recept)
	{
		w += Recept->second;
	}
	return w;
}

map <string, int> Random_pack(map <string, int> Fridge, unordered_map <string, map<string, int>>&Name_i_Recept, int &flagosi) {

	//�������� �������� ������, ���� ���� �� �������� �.� ��������� �������� ����� ��������� ����� �������� ������� ��� ��������� �� �� ������� ����
	const int Size = Name_i_Recept.size();
	int posit = 0;//random
	int i = 0; //while
	int count = 0; //alocation
	map <string, int> Schwere;
	map <string, int> BEST_Schwere;

	auto Recept = Name_i_Recept.begin();
	map <string, int> Zapas(Fridge);
	const int STOP_LINE = Size * 10;
	srand(time(0)); // �������������� ������������
	while(i < STOP_LINE) {
		posit = rand() % Size; //�� 0�..6 �.� 7 ����
		std::advance(Recept, posit); //����������� ��������� �� ������ ������
		Fridge = Vlezaet(Fridge, Recept->second, flagosi); //��������� �����������
		if (flagosi != 5) {//���� ��� ��� �������
			Schwere.emplace(Recept->first,Bread_crumb(Recept->second));
			Recept = Name_i_Recept.begin();
		}
		else {//����� ��������
			if (weight_of_map(Schwere) > weight_of_map(BEST_Schwere)) {
				BEST_Schwere = Schwere;
			}
			//Print_map(Schwere);//��� ������ ����������
			//std::cout << " LINE_VECTOR_____________________ " << endl;
			Schwere.clear();
			Fridge = Zapas;
			Recept = Name_i_Recept.begin();
		}
		i++;
	}
	//Print_map(BEST_Schwere);
	return BEST_Schwere;
};



void Fill_Schwere(map <string, int> Fridge, unordered_map <string, map<string, int>> Name_i_Recept, map <string, int>& Schwere) {
	map <string, int> Fridge2(Fridge);
	int Flag = 0;
	for (auto Recept = Name_i_Recept.begin(); Recept != Name_i_Recept.end(); ++Recept)
	{
		Fridge = Vlezaet(Fridge, Recept->second, Flag); //��������� �����������
		if (Flag == 5)
			Schwere.emplace(Recept->first, -1);
		else
			Schwere.emplace(Recept->first, Bread_crumb(Recept->second));
		Fridge = Fridge2; //�������� �����������
	}
	Print_map(Schwere);
};
// ���������� ������ �������� ������ � ��� ����� ���������� ����� ����������� ��� �� ����������� �������� ����� ��������� ������
/*map <string, int> Beefsteak = {
	{ "Beef", 500 },
	{ "Vegetable_oil", 15 },
	{ "Salt", 2 },
	{ "Black_pepper", 2 },
	};

	map <string, int> Meatballs = {
	{ "Beef", 500 },
	{ "Vegetable_oil", 15 },
	{ "Milk", 50 },
	{ "Bread", 100 },
	{ "Onion", 50 },
	{ "Black_pepper", 2 },
	};
*/

void find_best_of_pair(map <string, int> Recept, map <string, int> Recept2) { //�������� ��������� �� ���� ��������
	int s = Recept.size();
	int s2 = Recept2.size();

	int rz = -1;
	int count = 0;
	if (s2 > s) {
		rz = 2;
		for (auto it = Recept2.begin(); it != Recept2.end(); ++it)
		{
			for (auto id = Recept.begin(); id != Recept.end(); ++id)
			{
				if (it->first == id->first) {
					count++;//������� ���������� ����������� ���� ���� �������� ��������
					id->second = id->second - it->second; //�� ������� ������� �������� ������
				}
			}
		}
		//Print_map(Recept);
	}
	else {
		rz = 0;
		for (auto it = Recept2.begin(); it != Recept2.end(); ++it)
		{
			for (auto id = Recept.begin(); id != Recept.end(); ++id)
			{
				if (it->first == id->first) {
					count++;//������� ���������� ����������� ���� ���� �������� ��������
					it->second = it->second - id->second; //�� ������� ������� �������� ������
				}
			}
		}
	//Print_map(Recept2);
	}
	cout << rz << "____RZ" << endl;
	cout << count << "__count" << endl;
	//find_best_of_pair(France_Omelet, Omelet);//0 ������ �� �����
	return;
};

bool fint_rec(vector <string> Record, string wer) {
	for (auto i = Record.begin(); i != Record.end(); ++i) {
		if (*i == wer) {
			return 1;
		}
	}
	return 0;
}

//������ � ��������:
//int Record = -1;

void Recurse_way(map <string, int> Fridge, unordered_map <string, map<string, int>> &Name_i_Recept,std::unordered_map <string, map<string,
	int>>::const_iterator &Recept, vector <string>& Record, vector <string>& BEST_Record, int &Sum_record,int &BEST_Sum_record, int &flagosi) {
	Sum_record = Bread_crumb(Recept->second);
	for (auto i = Recept; i != Name_i_Recept.end(); ++i) //������ �� ����� �� ����������
	{
		Fridge = Vlezaet(Fridge, i->second, flagosi);//���� �� ������� �������
		if (fint_rec(Record, i->first)) continue;
		if (flagosi != 5) { //���������� ����� ��������� ������� ������� 
			Sum_record += Bread_crumb(i->second);
			Record.push_back(i->first);
			Recurse_way(Fridge, Name_i_Recept, Recept, Record, BEST_Record, Sum_record, BEST_Sum_record, flagosi); //�������� ����������
		}
		if (flagosi == 5) {
			if (Sum_record >= BEST_Sum_record) {
				BEST_Record = Record;
			}
			return;
		}
	}
	return;
};
//� ���������� ����� Name_i_Recept

//� ���������� ����� Name_i_Recept

int main()
{

	unordered_map <string, map<string, int>> Name_i_Recept; //������ ����� ������ ��� ���� map ���� map<����, map ������ �����> ��� �� �������� ��� ��������� ����� �����������

	/*map <string, int> Borsch = { 
	{ "Beef", 500 }, 
	{ "Beets ", 300 }, //������
	{ "Potatoes", 300 }, 
	{ "Cabbage", 200 },
	{ "Carrots ", 100 },
	{ "Onion", 100 },
	{ "Greens", 50 },
	{ "Tomato_paste ", 15 },
	{ "Vegetable_oil", 15 },
	{ "Vinegar", 5 },
	{ "Sour_cream", 50 },
	{ "Salt", 2 },
	{ "Black_pepper", 2 },
	{ "Water", 2000 },
	{ "Bay_leaves", 2 } };*/

	ifstream fin("Borsh.txt");
	map <string, int> Borsch;

	for (auto it = Borsch.begin(); it != Borsch.end(); ++it)
	{
		cout << it->first << " : " << it->second << endl; //����� �� ����� ���� �������� ������ ��� ����� 
	}

	//typedef vector<int> Vector;
	//typedef multimap<string, vector<int> > maps;
	//maps mapfile;
	//ifstream file("std.txt");
	//Vector vec(5);
	/*string name, s;
	int n;
	if (fin.is_open())
	{
		cout << " HERE "  << endl;
		while (fin >> name)
		{
			cout << " HERE_ " << endl;
			getline(fin, s);
			istringstream iss(s);
			n = 0;
			while (iss >> n)
			Borsch.insert(make_pair(name, n));

		}
	}*/

	LoadObj(fin, Borsch); //������� �������� �� �����, ��������� �������� ��������� ���������� ����, �� ���������� ������ ������ ���� ����

	//int Birh = Bread_crumb(Borsch); //����� ����������� ����� ����������� ��� �������
	//cout << Birh << endl;

	/*for (auto it = Borsch.begin(); it != Borsch.end(); ++it)
	{
		cout << it->first << " : " << it->second << endl; //����� �� ����� ���� �������� ������ ��� ����� 
	}*/


	//LoadObj(fin, Borsch);

	map <string, int> Soup = {
	{ "Processed_cheese", 180 },
	{ "Pasta", 100 },
	{ "Potatoes", 200 },
	{ "Carrots ", 100 },
	{ "Onion", 100 },
	{ "Greens", 25 },
	{ "Salt", 2 },
	{ "Black_pepper", 2 },
	{ "Water", 2000 } };

	map <string, int> No_lite_soup = {
	{ "Processed_cheese", 180 },
	{ "Pasta", 100 },
	{ "Potatoes", 300 },
	{ "Cabbage", 200 },
	{ "Carrots ", 100 },
	{ "Onion", 100 },
	{ "Greens", 50 },
	{ "Carrots ", 100 },
	{ "Salt", 2 },
	{ "Black_pepper", 2 },
	{ "Water", 2000 } };

	map <string, int> Beefsteak = {
	{ "Beef", 500 },
	{ "Vegetable_oil", 15 },
	{ "Salt", 2 },
	{ "Black_pepper", 2 },
	};

	map <string, int> Meatballs = {
	{ "Beef", 500 },
	{ "Vegetable_oil", 15 },
	{ "Milk", 50 },
	{ "Bread", 100 },
	{ "Onion", 50 },
	{ "Black_pepper", 2 },
	};

	map <string, int> Lazzania = {
	{ "Beef", 200 },
	{ "Vegetable_oil", 15 },
	{ "Pasta", 100 },
	{ "Onion", 50 },
	{ "Black_pepper", 2 },
	};

	map <string, int> Risotto = {
	{ "Beef", 200 },
	{ "Rice", 300 },
	{ "Broth", 800 }, //������
	{ "Vegetable_oil", 30 },
	{ "Salt", 2 },
	{ "Black_pepper", 2 },
	};

	map <string, int> Omelet = {
	{ "Eggs", 200 },
	{ "Salt", 2 },
	{ "Black_pepper", 2 },
	};

	map <string, int> Benedict_eggs = {
	{ "Eggs", 200 },
	{ "Salt", 2 },
	{ "Water", 500 },
	{ "Black_pepper", 2 },
	};

	map <string, int> MORE_Benedict_eggs = {
		{ "Eggs", 200 },
	{ "Salt", 2 },
	{ "Water", 2500 },
	{ "Black_pepper", 2 },
	};

	map <string, int> France_Omelet = {
	{ "Eggs", 200 },
	{ "Salt", 2 },
	{ "Milk", 50 },
	{ "Bay_leaves", 2 },
	{ "Black_pepper", 2 },
	};




//	map <string, int> Beefsteak = {
//	};

	//���������� �������� � MAP 
	Name_i_Recept.emplace("Soup", Soup);
	Name_i_Recept.emplace("No_lite_soup", No_lite_soup);
	Name_i_Recept.emplace("Lazzania", Lazzania);
	Name_i_Recept.emplace("Beefsteak", Beefsteak);
	Name_i_Recept.emplace("Meatballs", Meatballs);
	Name_i_Recept.emplace("Benedict_eggs", Benedict_eggs);
	Name_i_Recept.emplace("MORE_Benedict_eggs", MORE_Benedict_eggs);
	Name_i_Recept.emplace("Borsch", Borsch);
	Name_i_Recept.emplace("Omelet", Omelet);
	Name_i_Recept.emplace("France_Omelet", France_Omelet);
	Name_i_Recept.emplace("Risotto", Risotto);

	/*std::cout << " ________________________" << endl;
	Print_map(Borsch);
	std::cout << " ________________________" << endl;
	Print_map(Soup);
	std::cout << " ________________________" << endl;
	Print_map(Beefsteak);
	std::cout << " ________________________" << endl;
	Print_map(Meatballs);
	std::cout << " ________________________" << endl;
	Print_map(Risotto);
	std::cout << " ________________________" << endl;
	Print_map(Omelet);
	std::cout << " ________________________" << endl;
	*/

	/*std::cout << "WE already HAVE recepts Like" << endl;
	for (auto i = Name_i_Recept.begin(); i != Name_i_Recept.end(); ++i)
	{
		std::cout << i->first<< endl; //����� �� ����� ���� ����� 
	}
	std::cout << " ________________________" << endl;*/


	/*for (auto i = Name_i_Recept.begin(); i != Name_i_Recept.end(); ++i) //������ �� �������
	{
		for (auto it = i->second.begin(); it != i->second.end(); ++it)
		{
			std::cout << it->first << " : " << it->second << endl; //����� �� ����� ���� ����� 
		}
		std::cout << "END Recept____________________" << endl;
	}*/

	/*map <string, int> Fridge;
	int num;
	cout << "Enter the number of ingredients you want to spend: "; cin >> num;      // ��������� ����������

	for (int j = 0; j < num; j++) {
		int gram;
		string tmp;
		cout << "Enter ingredient name: ";
		cin >> tmp;
		cin.clear();
		cout << "Enter count of ingredient: ";
		cin >> gram;  // ��������� ��������� ��������
		Fridge.insert(make_pair(tmp, gram));
	}

	for (auto it = Fridge.begin(); it != Fridge.end(); ++it)
	{
		cout << it->first << " : " << it->second << endl; //����� �� ����� ���� �������� ������ ��� ����� 
	}/*/ 

	//��� ����� ������ ������ ��� �������� ��� ��� ���� ��� ����������� ����� ��������� ��� 
	map <string, int> Fridge = {
	{ "Beef", 700 },
	{ "Beets ", 500 },
	{ "Pasta", 500 },
	{ "Rice", 500 },
	{ "Potatoes", 2000 },
	{ "Cabbage", 400 },
	{ "Carrots ", 500 },
	{ "Onions", 1200 },
	{ "Greens", 200 },
	{ "Milk", 500 },
	{ "Bread", 300 },
	{ "Tomato_paste ", 200 },
	{ "Vegetable_oil", 430 },
	{ "Vinegar", 200 },
	{ "Sour_cream", 10 },
	{ "Eggs", 200 },
	{ "Salt", 200 },
	{ "Black_pepper", 200 },
	{ "Water", 5000 },
	{ "Bay_leaves", 20 } };
	double start_FF = GetTickCount();
	map <string, int> Rest_Fridge(Fridge); //�������������� ����������� ������� ��� �� ������ ������, ����� ����� �� ������ 
	const int Size = Name_i_Recept.size();
	int counto = 0;
	int flag = 0;
	vector <int> Flags(Size);
	vector <string> Allocation2(Size);

	//���-�� �������������� 
	//FIRST FIT
	//_____________________________________________________
	for (auto Recept = Name_i_Recept.begin(); Recept != Name_i_Recept.end(); ++Recept) //������ �� ������� ���������� ������ �������� � ���� ������������� ��� ������ ���� ��� ��������� ����, � ���� ����� "�������� ������ ���� ���..." � ������ ������ � i j ��� map
	{
		Allocation2[counto] = Recept->first;
		Fridge = Vlezaet(Fridge, Recept->second, flag);
		Flags[counto] = flag;//���� ������� ������ ��� ������
		//std::cout << Recept->first << "   ___" << endl;
		counto++;
	}

	/*std::cout << "Your menu for today" << endl; //����� �� ����� ���� ����� 
	for (auto i = 0; i<Size; ++i)
	{
		if (Flags[i] == 0)
			std::cout << Allocation2[i] << "   " << endl; //����� �� ����� ���� ����� 
	}
	std::cout << endl;*/

	double finish_FF = GetTickCount();
	std::cout << "The main execution time of the FF algorithm " << endl;
	std::cout << "   " << finish_FF - start_FF << "  seconds " << endl;
	
	//std::cout << "Best fitness menu for you" << endl; //����� �� ����� ���� ����� 

	//_____________________________________________________
	//BEST FIT?????????????????????????????

	//map <string, int> Rest_Fridge(Fridge); //�������������� ����������� ������� ��� �� ������ ������, ����� ����� �� ������ 
	//const int Size = Name_i_Recept.size(); //����������� ���� ��������� �� ������ ������ ��������
	//int counto = 0;
	//int steps = 0;
	//int f = -1;
	//int flag = 0;
	//vector <int> Flags(Size);
	//FILL_vec(Flags,3);
	//vector <string> Allocation(Size);
    // std::cout << "Risotto" << endl;
	//int Flo = Dish_of_the_day(Fridge, Borsch, Omelet);
	//cout << Flo;
	//auto Pointer = Name_i_Recept.begin();
	//auto END_Pointer = Name_i_Recept.end();
	//auto RECEPT_Pointer = --(Name_i_Recept.end());

	//All_Zero_in_line(Fridge, Pointer, Name_i_Recept);

	//double start_BF = GetTickCount();
	auto RECEPT_Pointer = --(Name_i_Recept.end());
	//const int Size = Name_i_Recept.size();
	//vector <int> Flags(Size);
	FILL_vec(Flags,-1);
	vector <string> Allocation;
	counto = 0;
	int point = -1;
	/*for (auto Recept = Name_i_Recept.begin(); Recept != RECEPT_Pointer; ++Recept)
	{
		point = All_Zero_in_line(Fridge, Recept, Name_i_Recept);
		cout << "All_Zero_in_line_____"<< All_Zero_in_line(Fridge, Recept, Name_i_Recept)<<endl; //������ ����� ���-�� ����� �.� ��������� ������� ������������ ������ � ������
		Flags[counto] = point;
		counto++;
		if (All_Zero_in_line(Fridge, Recept, Name_i_Recept)) //���� �������� ��� ��
		{
			Fridge = Vlezaet(Fridge, Recept->second, flag);
			cout << flag << "FLAG" << endl;
			Allocation[counto] = Recept->first;
			cout << Allocation[counto];
		}
		cout << counto << "__counto" << endl;
		counto++;
	}
	Print_vec(Flags);
	int num = Max_element_numer(Flags); //������ 1
	auto Recept2 = Name_i_Recept.begin();
	std::advance(Recept2, num);
	Allocation.push_back(Recept2->first);
	Name_i_Recept.erase(Recept2->first);*/


	//double finish_BF = GetTickCount();
	//std::cout << "The main execution time of the BF algorithm " << endl;
	//std::cout << "   " << finish_BF - start_BF << "  seconds " << endl;
	
	//delete Recept;

	
	//Recurse_way
	double start_RV = GetTickCount()-19;
	int flagosi = -1;
	int shetcik = 0;
	//const int Size = Name_i_Recept.size();
	Allocation.clear();
	map <string, int> Schwere;
	vector <string> Record;
	vector <string> BEST_Record;
	int BEST_Sum_record = 0;
	int Sum_record = 0;
	std::unordered_map <string, map<string, int>>::const_iterator Recept = Name_i_Recept.begin();
	//Fill_Schwere(Fridge, Name_i_Recept, Schwere); ���������� ������ �������� ������ � ��� ����� ���������� ����� ����������� ��� �� ����������� �������� ����� ��������� ������
	Recurse_way(Fridge, Name_i_Recept, Recept, Record, BEST_Record, Sum_record, BEST_Sum_record, flagosi);
	//Print_vec_p(BEST_Record);

	double finish_RV = GetTickCount();

	std::cout << "The main execution time of the RV algorithm " << endl;
	std::cout << "   " << finish_RV - start_RV << "  seconds " << endl;

	//MC
	double start_MC = GetTickCount();

	Schwere = Random_pack(Fridge, Name_i_Recept, flagosi);
	//std::cout << "Fresh menu from Monte-Carlo" << endl; //����� �� ����� ���� ����� 
	/*for (auto i = Schwere.begin(); i != Schwere.end(); ++i)
	{
		std::cout << i->first << "   " << endl; //����� �� ����� ���� ����� 
	}*/
	double finish_MC = GetTickCount();

	std::cout << "The main execution time of the MC algorithm " << endl;
	std::cout << "   " << finish_MC - start_MC << "  seconds " << endl;

	//BD
	double start_BF = GetTickCount();
	while (flagosi != 5 || shetcik!=Size) {
		Find_allocation_of_the_BEST_recept_of_group(Fridge, Name_i_Recept, Allocation, flagosi);
		shetcik++;
	}

	double finish_BF = GetTickCount();
	std::cout << "The main execution time of the BF algorithm " << endl;
	std::cout << "   " << finish_BF - start_BF << "  seconds " << endl;



	//��������� ��� �� ������ �.� ������� ������ ������� ��� ������������ � ��������� ��� � ��������

	/*for (auto Recept = Name_i_Recept.begin(); Recept != RECEPT_Pointer; ++Recept) //������ �� ������� ���������� ������ �������� � ���� ������������� ��� ������ ���� ��� ��������� ����, � ���� ����� "�������� ������ ���� ���..." � ������ ������ � i j ��� map
	{
		FILL_vec(Flags, 3);
		std::cout << counto << "  STEP ___" << endl;
		steps = 0;
		std::cout << Recept->first << " BEFORE STEP OUN OF WHILE IN FOR_______Recept->first" << endl;
		//std::cout << Pointer->first << "  BEFORE  STEP OUN OF WHILE IN FOR_________Pointer->first" << endl;
		Pointer = Recept; // ������ �� ������ �������� ������ �� ������ 
		++Pointer;
		std::cout << Recept->first << "  STEP OUN OF WHILE IN FOR_______Recept->first" << endl;
		std::cout << Pointer->first << "  STEP OUN OF WHILE IN FOR_________Pointer->first" << endl;
		while (Pointer != END_Pointer) {
			//std::cout << steps <<"    "<< counto << "  STEP ___INWHILE" << endl;
			f = Dish_of_the_day(Fridge, Recept->second, Pointer->second); //�������� ���� � ����� 
			std::cout <<  "  PAIRS  ___________" << Recept->first <<"___"<< Pointer->first << endl;
			Flags[steps] = f;
			steps++;
			++Pointer;
			//std::cout << steps << "    " << counto << "  STEP ___BORDWHILE" << endl;
		}

		std::cout << Recept->first << "  STEP OUN OF WHILE IN FOR_______Recept->first" << endl;
		counto++;
		Print_vec(Flags);
		FILL_vec(Flags);
		//std::cout << Pointer->first << "  POINTER AUTPR STEP OUN OF WHILE IN FOR_______Pointer" << endl;
		std::cout << counto << "  STEP OUN OF WHILE IN FOR___" << endl;



		/*f = Dish_of_the_day(Fridge, Recept->second, (Recept++)->second); //���������� ������ � ����� � ��������������� ���� 1_2 / 2_3 / 3_4 ���...
		if (f!=5){
			if (f == 0) { //Recept->second ����� ���������
				Fridge = Vlezaet(Fridge, Recept->second, flag);
			}
			else 
			{

			}
		
		}*/
		/*Allocation[counto] = Recept->first;
		Fridge = Vlezaet(Fridge, Recept->second, flag);
		Flags[counto] = flag;//���� ������� ������ ��� ������
		//std::cout << Recept->first << "   ___" << endl;
		counto++;
	}*/


	/*std::reverse(Allocation.begin(), Allocation.end());
	std::cout <<"Your menu for today" << endl; //����� �� ����� ���� ����� 
	for (auto i = 0; i<Allocation.size(); ++i)
	{
		std::cout << Allocation[i] << "   " << endl; //����� �� ����� ���� ����� 
	}*/
	

	//����� ������ � ������ �� ����������� �������
	//���� ����� ��� ������ ������� ����� ������� 
	//�������� ����� ������� ���������� �������  
	//����� ������� ��� ������ � � ���� ������������ ������� �� ������ ��������, �� ����� ����� � �������� ���������� � ��� �� ����� ����� ��������
	//������� ���������� �����

	//�������������� ���� ������� map �� vector int � vector string 

	system("pause");
	return 0;
}
