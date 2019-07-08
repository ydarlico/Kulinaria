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
using namespace std;

map <string, int> Vlezaet (map <string, int> Fridge, map <string, int> Recept, int& Bad_flag)
{
	map <string, int> Zapas(Fridge);

	Bad_flag = 0;
	for (auto it = Recept.begin(); it != Recept.end(); ++it)
	{
		for (auto id = Zapas.begin(); id != Zapas.end(); ++id) //Пользуемся копией холодильника
		{
			if (id->first == it->first)
			{
				if (id->second < it->second)     //если 20 листье больше чем 2 листа то этот рецепт нам подходит  типа в холодосе больше чем нужно
				{
					Bad_flag = 5; //Показали что чего то уже не хватило рецепту
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
		return Zapas;//Холодос в котором что-то осталось после рецепта 
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



int Dish_of_the_day(map <string, int> Fridge, map <string, int> Recept, map <string, int> Recept2) { //Какое блюдо потратит БОЛЬШЕ ингридиентов
	if (Recept == Recept2) { //бан первого блюда
		return 50;
	}

	int Flag = 0;
	int Flag2 = 0;
	map <string, int> Zapas = Vlezaet(Fridge, Recept, Flag); //Остаток холодоса после первого рецепта
	map <string, int> Zapas2 = Vlezaet(Fridge, Recept2, Flag2); //Остаток холодоса после ВТОРОГО


	if (Flag == 5) { //бан первого блюда
		return 10;
	}
	if (Flag2 == 5) { //бан второго блюда
		return 20;
	}

	if (Bread_crumb(Zapas) > Bread_crumb(Zapas2)) { //Если при использовании Recept мы потратили БОЛЬШЕ ингридинетов ЧЕМ при 2 варианте то
		return 0;
	}
	else {//Если recept 2 оказался более затратным, а значит БОЛЬШЕ НАМ ПОДХОДИТ
		return 2;
	}
    
	//Распознавание Dish_of_the_day
	//Вернули 0 - Значит recept тратит больше иншгридиентов
	//Вернули 2 - Значит recept2 ДВА тратит больше иншгридиентов
	//Вернули 10 - Значит recept НЕ ВЛЕЗАЕТ а значит бан
	//Вернули 20 - Значит recept НЕ ВЛЕЗАЕТ а значит бан
	//Вернули 50 - Значит ОНИ ОДИНАКОВЫЕ
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
			std::cout << Flags[i] << " "; //вывод на экран всей карты 
	}
	cout <<  " ____END " << endl;
};
void Print_vec(vector <string> Flags) {
	for (auto i = 0; i < size(Flags); ++i)
	{
		std::cout << Flags[i] << "   "; //вывод на экран всей карты 
	}
	cout << " : " << endl;
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
		cout << it->first << " : " << it->second << endl; //вывод на экран всей карты
		}
};

void Print_map(unordered_map <string, int> Borsch) {
	for (auto it = Borsch.begin(); it != Borsch.end(); ++it)
	{
		cout << it->first << " : " << it->second << endl; //вывод на экран всей карты
	}
};



int All_Zero_in_line(map <string, int> Fridge, unordered_map <string, map<string, int>>::iterator Point, unordered_map <string, map<string, int>> Name_i_Recept)
{
	vector <int> Flags(Name_i_Recept.size());
	int k = 0;
	int f = 0;
	int counter = 0;//счетчик нудей	
	int counter_main = 0;//счетчик нудей	
	for (auto Recept = Name_i_Recept.begin(); Recept != Name_i_Recept.end(); ++Recept) //Проход по вектору перебираем список рецептов а ниже разворачиваем сам рецепт типа это нназвание борщ, а ниже пошло "морковка свекла мясо итд..." в данном случае и i j это map
	{
		f = Dish_of_the_day(Fridge, Point->second, Recept->second); //сравнили статичный указатель с движущимся
																	//Распознавание Dish_of_the_day
																	//Вернули 0 - Значит recept тратит больше иншгридиентов
																	//Вернули 2 - Значит recept2 ДВА тратит больше иншгридиентов
																	//Вернули 10 - Значит recept НЕ ВЛЕЗАЕТ а значит бан
																	//Вернули 20 - Значит recept НЕ ВЛЕЗАЕТ а значит бан
																	//Вернули 50 - Значит ОНИ ОДИНАКОВЫЕ
		//std::cout << "  PAIRS  ____statyc-dynamic_______" << Point->first << "___" << Recept->first <<"  FLAG   "<< f<< endl;
		Flags[k] = f;
		k++;
	}
	//Print_vec(Flags);
	return Count_int_in_vec(Flags, 0);//Считаем кол-во нулей в полученой строчке
};

int Max_element_numer(vector <int>Flags) {
	std::vector<int>::iterator result;
	int index = -1;
	result = std::max_element(Flags.begin(), Flags.end());
	index = std::distance(Flags.begin(), result);
	return index;
}


int Find_allocation_of_the_BEST_recept_of_group(map <string, int> &Fridge, unordered_map <string, map<string, int>>&Name_i_Recept, vector <string>&Allocation, int &flagosi) { //Последние два по ссылке т.к удаляем рецепт который уже использовали и добавляем его в алокэйшн

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
		//cout << "All_Zero_in_line_____" << All_Zero_in_line(Fridge, Recept, Name_i_Recept) << endl; //Вернет числа кол-во нулей т.е приоритет рецепта находящегося сейчас в рецепт
		Flags[counto] = point;
		counto++;
		/*if (All_Zero_in_line(Fridge, Recept, Name_i_Recept)) //Если выкинуло тру то
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
	int num = Max_element_numer(Flags); //вернет 1
	auto Recept = Name_i_Recept.begin();
	std::advance(Recept, num); //указывает на бифстейк

	Fridge = Vlezaet(Fridge, Recept->second, flagosi);
	if (flagosi == 5) return 5;
	else {
		Allocation.push_back(Recept->first);
		Name_i_Recept.erase(Recept->first);
		return 0;
	}
}


/*void Heavy_lite_Ostatki(map <string, int> Fridge, unordered_map <string, map<string, int>> Name_i_Recept, vector <int>&Schwere) {  //Schwere - тяжесть
	//ВЕрнет вес каждого рецепта, если рецепт не влезает то вернет -1
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

/*unordered_map <string, int> Heavy_lite_Ostatki(map <string, int>Fridge, unordered_map <string, map<string, int>> Name_i_Recept, int& Bad_flag) {  //Schwere - тяжесть
	//ВЕрнет вес каждого рецепта, если рецепт не влезает то вернет -1
	unordered_map <string, int> Schwere;
	map <string, int> Fridge2(Fridge);
	for (auto Recept = Name_i_Recept.begin(); Recept != Name_i_Recept.end(); ++Recept)
	{
		std::cout << " _____________________ " << endl;
		std::cout << " _FRIDGE_BEFORE_ " <<endl;
		Print_map(Fridge2);
		Fridge2 = Vlezaet(Fridge, Recept->second, Bad_flag); //остаток холодильника после применения рецепта + вернет холодильник уже измененым
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

/*int Find_max(unordered_map <string, int> Schwere) { //вернет номер позиции
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
	int pos = Find_max(Schwere); //ITERATOR указывает на наибольший элемент в карте веса (швеа)
	std::advance(it, pos);
	//cout <<pos<< "ИТЕРАТОР" << endl;
	string max_name = it->first; //soup
	int max_int = it->second; //2429
	std::cout << max_name << " : " << max_int << endl;
	Print_map(Schwere);
	std::cout <<  " ____________________ " << endl;
	Schwere.erase(it); //удалили суп
	Print_map(Schwere);
	std::cout << " ____________________ " << endl;
	Schwere = Heavy_lite_Ostatki(Fridge, Name_i_Recept, Bad_flag); //изменится швеа, холодос прежний ПОЧЕМУ ТУТ ПОЯВЛЯЕТСЯ СУП???
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

map <string, int> Random_pack(map <string, int> Fridge, unordered_map <string, map<string, int>>&Name_i_Recept, map <string, int> Schwere, int &flagosi) {

	//Рандомно собирает рюкзак, упор идет на скорость т.к перебрать длпустим сотню вариантов будет всеравно быстрее чем вычислять их же циклами выше
	const int Size = Name_i_Recept.size();
	int posit = 0;//random
	int i = 0; //while
	int count = 0; //alocation

	map <string, int> BEST_Schwere;

	auto Recept = Name_i_Recept.begin();
	map <string, int> Zapas(Fridge);

	srand(time(0)); // автоматическая рандомизация
	while(i < 300) {
		posit = rand() % Size; //от 0ю..6 т.е 7 штук
		std::advance(Recept, posit); //Пододвинули указатель на нужный рецепт
		Fridge = Vlezaet(Fridge, Recept->second, flagosi); //Испортили холодильник
		if (flagosi != 5) {//если все еще влезает
			Schwere.emplace(Recept->first,Bread_crumb(Recept->second));
			Recept = Name_i_Recept.begin();
		}
		else {//Сброс настроек
			if (weight_of_map(Schwere) > weight_of_map(BEST_Schwere)) {
				BEST_Schwere = Schwere;
			}
			//Print_map(Schwere);//что успели насобирать
			//std::cout << " LINE_VECTOR_____________________ " << endl;
			Schwere.clear();
			Fridge = Zapas;
			Recept = Name_i_Recept.begin();
		}
		i++;
	}
	Print_map(BEST_Schwere);
	return BEST_Schwere;
};

//В итоераторе сидит Name_i_Recept

int main()
{

	unordered_map <string, map<string, int>> Name_i_Recept; //Кажись нужно делать еще один map типа map<БОРЩ, map РЕЦЕПТ БОРЩА> Что бы выводить что конкретно можно приготовить

	/*map <string, int> Borsch = { 
	{ "Beef", 500 }, 
	{ "Beets ", 300 }, //свекла
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
		cout << it->first << " : " << it->second << endl; //вывод на экран всей ВВЕДЕНОЙ ТОЛЬКО ЧТО карты 
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

	LoadObj(fin, Borsch); //функция загрузки из файла, поскольку забивать текстовки немножечко лень, то подготвлен сейчас только один файл

	//int Birh = Bread_crumb(Borsch); //Выпод колличество грамм необходимое для рецепта
	//cout << Birh << endl;

	/*for (auto it = Borsch.begin(); it != Borsch.end(); ++it)
	{
		cout << it->first << " : " << it->second << endl; //вывод на экран всей ВВЕДЕНОЙ ТОЛЬКО ЧТО карты 
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

	map <string, int> Risotto = {
	{ "Beef", 200 },
	{ "Rice", 300 },
	{ "Broth", 800 }, //бульон
	{ "Vegetable_oil", 30 },
	{ "Salt", 2 },
	{ "Black_pepper", 2 },
	};

	map <string, int> Omelet = {
	{ "Eggs", 200 },
	{ "Salt", 2 },
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

	//добавление рецептов в MAP 
	Name_i_Recept.emplace("Soup", Soup);
	Name_i_Recept.emplace("Beefsteak", Beefsteak);
	Name_i_Recept.emplace("Meatballs", Meatballs);
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
		std::cout << i->first<< endl; //вывод на экран всей карты 
	}
	std::cout << " ________________________" << endl;*/


	/*for (auto i = Name_i_Recept.begin(); i != Name_i_Recept.end(); ++i) //Проход по вектору
	{
		for (auto it = i->second.begin(); it != i->second.end(); ++it)
		{
			std::cout << it->first << " : " << it->second << endl; //вывод на экран всей карты 
		}
		std::cout << "END Recept____________________" << endl;
	}*/

	/*map <string, int> Fridge;
	int num;
	cout << "Enter the number of ingredients you want to spend: "; cin >> num;      // считываем количество

	for (int j = 0; j < num; j++) {
		int gram;
		string tmp;
		cout << "Enter ingredient name: ";
		cin >> tmp;
		cin.clear();
		cout << "Enter count of ingredient: ";
		cin >> gram;  // считываем введенные значения
		Fridge.insert(make_pair(tmp, gram));
	}

	for (auto it = Fridge.begin(); it != Fridge.end(); ++it)
	{
		cout << it->first << " : " << it->second << endl; //вывод на экран всей ВВЕДЕНОЙ ТОЛЬКО ЧТО карты 
	}/*/ 

	//Для теста лениво каждый раз набирать так что пока что холодильник будет выглядеть так 
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

	/*auto Pointer = Name_i_Recept.begin();
	int Bad_flag = 5;
	//Recurse(Fridge, Pointer, Bad_flag);
	//vector <int> Schwere;
	unordered_map <string, int> Schwere;
	Schwere = Heavy_lite_Ostatki(Fridge, Name_i_Recept, Bad_flag); 
	//Print_vec(Schwere);

	Find_Best_Way(Fridge,Name_i_Recept, Schwere,Bad_flag);*/

	//Heavy_lite_Ostatki(Fridge, Name_i_Recept, Fridge2, Bad_flag); //map
	//Print_map(Fridge2);
	//cout << Find_max(Fridge2);

	/*int h = 0;
	cout << "Dish_of_the_day" << Dish_of_the_day(Fridge, Soup, Soup) << endl;//2
	cout << "Dish_of_the_day" << Dish_of_the_day(Fridge, Soup, Beefsteak) << endl;//2
	cout << "Dish_of_the_day" << Dish_of_the_day(Fridge, Soup, Meatballs) << endl;//0
	cout << "Dish_of_the_day" << Dish_of_the_day(Fridge, Soup, Borsch) << endl;//20
	cout << "Dish_of_the_day" << Dish_of_the_day(Fridge, Soup, Risotto) << endl;//10
	cout << "Dish_of_the_day" << Dish_of_the_day(Fridge, Soup, Omelet) << endl;//2*/

	//int Flo = Dish_of_the_day(Fridge, Borsch, Omelet);
	//cout << Flo;

	/*int flag = 0;
	std::cout << "VLEZAET_________ "<< '\n';
	Fridge = Vlezaet(Fridge, Borsch, flag);

	std::cout << "XOLODILNOK______" << '\n';
	for (auto it = Fridge.begin(); it != Fridge.end(); ++it)
	{
		cout << it->first << " : " << it->second << endl; //вывод на экран всей ВВЕДЕНОЙ ТОЛЬКО ЧТО карты 
	}
	std::cout << "STOP_____XOLODILNOK______" << '\n';

	flag = 0;
	std::cout << "VLEZAET_________ " << '\n';
	Fridge = Vlezaet(Fridge, Risotto, flag);
	std::cout << "XOLODILNOK______" << '\n';
	for (auto it = Fridge.begin(); it != Fridge.end(); ++it)
	{
		cout << it->first << " : " << it->second << endl; //вывод на экран всей ВВЕДЕНОЙ ТОЛЬКО ЧТО карты 
	}
	std::cout << "STOP_____XOLODILNOK______" << '\n';*/





	//map <string, int> Rest_Fridge(Fridge); //Первоначальный холодильник Оставлю так на всякий случай, чтобы потом не побить 

	//std::cout << "Count of Potatos in your Fridge => " << Fridge.find("Potatoes")->second << '\n'; //Проверка как обращаться

	//алгоритм 

	//vector <string> Good_formulas; //Рецепты которые ок Кажись нужно делать еще один map типа map<БОРЩ, map РЕЦЕПТ БОРЩА> Что бы выводить что конкретно можно приготовить

	/*for (auto i = Name_i_Recept.begin(); i != Name_i_Recept.end(); ++i) //Проход по вектору
	{
		//Создать массив тут
		for (auto it = i->second.begin(); it != i->second.end(); ++it) //Докопались до карты работаем с ней, в i хранится номер рецепта в котором мы сейчас сидим 
		{

			for (auto id = Fridge.begin(); id != Fridge.end(); ++id) 
			{ // Открыли холодильник и смотрим внутрь
				if (id->first == it->first) 
				{
					if (id->second < it->second)     //если 20 листье больше чем 2 листа то этот рецепт нам подходит  типа в холодосе больше чем нужно
					{
						//std::cout << "BAD ingredient  " << id->first << it->first << endl; //Сметанка не проканала т.к ее всего 10 грам а нужно 200 кажись
						Ostatok = 0;
						break; //Если хоть раз попался бэд ингредиент - рецепт идет далеко и надолго
					}
					else
					{
						//std::cout << "Good ingredient  " << id->first << it->first << endl; //Ингридиента хватает для рецепта id - холодос  it -рецепт
						Ostatok += (id->second - it->second); //Закинули остаток, т.е что останется в холодосе после гипотетического приготовления 
						//std::cout << "OSTATOK SEGOTO TAM _   " << id->first << " || " << Ostatok << endl;


					}
				}
				//Добавить Если хоть раз попался бэд ингредиент - рецепт идет далеко и надолго
				//Остальные на выдачу 

				//Оптимизация - если в ХОРОШИХ рецептах отстается минимум свободного места типа было 500г мяса 
				// можно бахнуть борщ и потратить 400/500 остаток 100 
				//Или бахнуть ну не знаю яишенку и потратить 50/500 с состатком 450 вот это оптимизейшн 

				//О, идея Записывать эти остатки в массив/суммировать в переменную и потом сделать просто сумму по всему массиву и где будет остаток меньше тот и ТОП рецепт 


			} //Закрыли холодильник получив данные сравнения. но еще не успели открыть новый рецепт 
			//cout << it->first << " : " << it->second << endl; //вывод на экран всей карты  типа название-количество
		}
		Good_formulas.emplace_back(Ostatok);
		Ostatok = 0;
		//std::cout << "END FORMULA____________________" << endl;
	}

	std::vector<int>::iterator min = std::min_element(Good_formulas.begin(), Good_formulas.end());
	int iter = std::distance(Good_formulas.begin(), min); //Получили нулевое значение т.к борщ нам подходит
	std::cout << "Min element " << *min << " on position " << iter << endl;

	//std::cout << "The best formulas for you is " << Name_i_Recept[iter]->first << endl; //Не жрет эту связку вспомнить/загуглить как будет интернет как прибавить к итератору непонятно что iter интовое
	int j = 1;

	for (auto i = Name_i_Recept.begin(); j < iter; ++i) //Проход по вектору
	{
		if (j == iter) 
		{
		std::cout << "The best formulas for you is ___ " << i->first << endl;
		std::cout << "Because this way have less count of rubbish than another" << endl;  
		}
		if (j > iter) break;
		j++;
	}
	*/
	//Допилить/перечитать код т.к он выдает неверные данные и иногда просто их теряет скорее всего косяк в конектинге основоного map и вектора 
	/*const int Size = Name_i_Recept.size();
	const int Size_k = Fridge.size();
	cout << Size << "Size ==" << endl;

	map <string, int> Rest_Fridge(Fridge); //Остаток в холодильнике// Полная копия холодоса 
	vector <int> Flags (Size); //кол-во рецептов т.е размерности i будет массив флагов
	vector <int> Allocation(Size); //Размещение 
	
	for (int j = 0; j < Size; j++)
	{
		Flags[j] = 0; 
		Allocation[j] = -1;
	}

	int k,n,temp;

	//Попытка завести хотя бы first-fit

	for (auto i = Name_i_Recept.begin(); i != Name_i_Recept.end(); ++i) //Проход по вектору перебираем список рецептов а ниже разворачиваем сам рецепт типа это нназвание борщ, а ниже пошло "морковка свекла мясо итд..."
	{
		n = 0;//ячейка ингридиента
		for (auto it = i->second.begin(); it != i->second.end(); ++it) //Докопались до карты работаем с ней, в i хранится номер рецепта в котором мы сейчас сидим т.е первый борщ потом суп потом еще что-то
		{
			k = 0;
			for (auto id = Fridge.begin(); id != Fridge.end(); ++id)
			{ // Открыли холодильник и смотрим внутрь
			  std::cout << "__NOW_ingredient  " << id->first << it->first << endl; //Ингридиента хватает для рецепта id - холодос  it -рецепт
				if (id->first == it->first) //Сравниваем одинаковые элементы иил нет
				{
					std::cout << "__NOW_GOOOD_ingredient  " << id->first << it->first << endl; //Ингридиента хватает для рецепта id - холодос  it -рецепт
					if ((Flags[n] == 0) &&(id->second >= it->second))     //если нам хватает места и РЕЦЕПТ еще не был обработан т.е ему не нашли место 
					{
						Allocation[n] = k; //созранили номер размещения
						Flags[n] = 1;      // сказали что этот рецепт уже на полке
						cout << "SHA BUDET BREAK" << "   " << endl;
						break;             // вышли нахренЮ, ничего не сделали холодосу

					}
					
				}
			k++; if (k == Size) break;
			cout << "===k=      " <<k << "=k     " << endl;
			}
			n++; if (n == Size) break;
			cout << "=====n      " << n << "=====n      " << endl;
		}//Закрыли рецепт но еще не открыли новый, i хранится номер рецепта в котором мы сейчас сидим т.е первый борщ потом суп потом еще что-то, на первой итерации в тут хранится "борщ-"борщ

	}*/

	/*cout << "Flags[j]" << "   " << endl;

	for (int j = 0; j < Size; j++)
	{
		cout << Flags[j] << "   " <<endl;
	}

	cout << "Allocation[j]" << "   " << endl;

	for (int j = 0; j < Size; j++)
	{
		cout << Allocation[j] << "   " << endl;
	}*/


	/*std::cout << "OSTATKI____ " << endl;
	for (auto id = Fridge.begin(); id != Fridge.end(); ++id)
	{
		std::cout << id->first << " : " << id->second << endl; //вывод на экран всей карты 
	}

	std::cout << "What we hawe in end" << endl;
	for (auto i = 0; i<Good_formulas.size(); ++i)
	{
		std::cout << Good_formulas[i] <<"   "<< endl; //вывод на экран всей карты 
	}*/





	/*map <string, int> Rest_Fridge(Fridge); //Первоначальный холодильник Оставлю так на всякий случай, чтобы потом не побить 
	const int Size = Name_i_Recept.size();
	int counto = 0;
	int flag = 0;
	vector <int> Flags(Size);
	vector <string> Allocation(Size);*/

	//Что-то вырисовывается 
	//FIRST FIT
	//_____________________________________________________
	/*for (auto Recept = Name_i_Recept.begin(); Recept != Name_i_Recept.end(); ++Recept) //Проход по вектору перебираем список рецептов а ниже разворачиваем сам рецепт типа это нназвание борщ, а ниже пошло "морковка свекла мясо итд..." в данном случае и i j это map
	{
		Allocation[counto] = Recept->first;
		Fridge = Vlezaet(Fridge, Recept->second, flag);
		Flags[counto] = flag;//тому который только что пришел
		//std::cout << Recept->first << "   ___" << endl;
		counto++;
	}

	std::cout << "Your menu for today" << endl; //вывод на экран всей карты 
	for (auto i = 0; i<Size; ++i)
	{
		if (Flags[i] == 0)
			std::cout << Allocation[i] << "   " << endl; //вывод на экран всей карты 
	}*/




	//_____________________________________________________
	//BEST FIT?????????????????????????????

	//map <string, int> Rest_Fridge(Fridge); //Первоначальный холодильник Оставлю так на всякий случай, чтобы потом не побить 
	//const int Size = Name_i_Recept.size(); //Колличество всех доступных на данный момент рецептов
	//int counto = 0;
	//int steps = 0;
	//int f = -1;
	//int flag = 0;
	//vector <int> Flags(Size);
	//FILL_vec(Flags,3);
	//vector <string> Allocation(Size);

	//int Flo = Dish_of_the_day(Fridge, Borsch, Omelet);
	//cout << Flo;
	//auto Pointer = Name_i_Recept.begin();
	//auto END_Pointer = Name_i_Recept.end();
	//auto RECEPT_Pointer = --(Name_i_Recept.end());

	//All_Zero_in_line(Fridge, Pointer, Name_i_Recept);

	/*
	auto RECEPT_Pointer = --(Name_i_Recept.end());
	const int Size = Name_i_Recept.size();
	vector <int> Flags(Size);
	FILL_vec(Flags,-1);
	vector <string> Allocation;
	int counto = 0;
	int point = -1;
	for (auto Recept = Name_i_Recept.begin(); Recept != RECEPT_Pointer; ++Recept)
	{
		point = All_Zero_in_line(Fridge, Recept, Name_i_Recept);
		cout << "All_Zero_in_line_____"<< All_Zero_in_line(Fridge, Recept, Name_i_Recept)<<endl; //Вернет числа кол-во нулей т.е приоритет рецепта находящегося сейчас в рецепт
		Flags[counto] = point;
		counto++;
		/*if (All_Zero_in_line(Fridge, Recept, Name_i_Recept)) //Если выкинуло тру то
		{
			Fridge = Vlezaet(Fridge, Recept->second, flag);
			cout << flag << "FLAG" << endl;
			Allocation[counto] = Recept->first;
			cout << Allocation[counto];
		}
		cout << counto << "__counto" << endl;
		counto++;*/
	/*}
	Print_vec(Flags);
	int num = Max_element_numer(Flags); //вернет 1
	auto Recept = Name_i_Recept.begin();
	std::advance(Recept, num);
	Allocation.push_back(Recept->first);
	Name_i_Recept.erase(Recept->first);*/

	int flagosi = -1;
	int shetcik = 0;
	const int Size = Name_i_Recept.size();
	vector <string> Allocation;
	map <string, int> Schwere;

	Random_pack(Fridge, Name_i_Recept, Schwere, flagosi);
	while (flagosi != 5 || shetcik!=Size) {
		Find_allocation_of_the_BEST_recept_of_group(Fridge, Name_i_Recept, Allocation, flagosi);
		shetcik++;
	}

	//Последние два по ссылке т.к удаляем рецепт который уже использовали и добавляем его в алокэйшн

	/*for (auto Recept = Name_i_Recept.begin(); Recept != RECEPT_Pointer; ++Recept) //Проход по вектору перебираем список рецептов а ниже разворачиваем сам рецепт типа это нназвание борщ, а ниже пошло "морковка свекла мясо итд..." в данном случае и i j это map
	{
		FILL_vec(Flags, 3);
		std::cout << counto << "  STEP ___" << endl;
		steps = 0;
		std::cout << Recept->first << " BEFORE STEP OUN OF WHILE IN FOR_______Recept->first" << endl;
		//std::cout << Pointer->first << "  BEFORE  STEP OUN OF WHILE IN FOR_________Pointer->first" << endl;
		Pointer = Recept; // рецепт на первом элементе поинтр на втором 
		++Pointer;
		std::cout << Recept->first << "  STEP OUN OF WHILE IN FOR_______Recept->first" << endl;
		std::cout << Pointer->first << "  STEP OUN OF WHILE IN FOR_________Pointer->first" << endl;
		while (Pointer != END_Pointer) {
			//std::cout << steps <<"    "<< counto << "  STEP ___INWHILE" << endl;
			f = Dish_of_the_day(Fridge, Recept->second, Pointer->second); //сравнили борщ с супом 
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



		/*f = Dish_of_the_day(Fridge, Recept->second, (Recept++)->second); //Сравниваем борщец с супом и последовательно пары 1_2 / 2_3 / 3_4 итд...
		if (f!=5){
			if (f == 0) { //Recept->second БОЛЕЕ затратный
				Fridge = Vlezaet(Fridge, Recept->second, flag);
			}
			else 
			{

			}
		
		}*/
		/*Allocation[counto] = Recept->first;
		Fridge = Vlezaet(Fridge, Recept->second, flag);
		Flags[counto] = flag;//тому который только что пришел
		//std::cout << Recept->first << "   ___" << endl;
		counto++;
	}*/



	std::reverse(Allocation.begin(), Allocation.end());
	std::cout <<"Your menu for today" << endl; //вывод на экран всей карты 
	for (auto i = 0; i<Allocation.size(); ++i)
	{
		std::cout << Allocation[i] << "   " << endl; //вывод на экран всей карты 
	}

	//Метод ветвей и границ те оптимальный перебор
	//Цель найти ГДЕ МЕНЬШЕ ОСТАТОК ЭТОГО рецепта 
	//Остатком можно считать пемеренную интовую  
	//Можно бахнуть еще массив и в него складировать остатки по каждой итерации, то тогда нужно и итерацию запоминать и что по итогу выдал алокэйшн
	//Внешнее считывание файла

	//Дополнительная идея разбить map на vector int и vector string 

	system("pause");
	return 0;
}
