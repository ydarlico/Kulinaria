#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <iterator>
#include <algorithm>
#include <unordered_map>
#include <fstream>
#include <sstream>
using namespace std;

map <string, int> Vlezaet (map <string, int>& Fridge, map <string, int> Recept, int& Bad_flag)
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

void LoadObj(ifstream &inFile, map <string, int> &Borsch) {
	while (!inFile.eof()) {
		string key;
		int pt;
		inFile >> key >> pt;
	}
	for (map <string, int>::iterator it = Borsch.begin(); it != Borsch.end(); ++it)
	{
		cout << it->first << "\t" << it->second << "\n";
	}
}

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
	{ "Tomato paste ", 15 },
	{ "Vegetable_oil", 15 },
	{ "Vinegar", 5 },
	{ "Sour_cream", 50 },
	{ "Salt", 2 },
	{ "Black_pepper", 2 },
	{ "Water", 2000 },
	{ "Bay_leaves", 2 } };*/

	ifstream fin("Borsch.txt");
	map <string, int> Borsch;

	/*ifstream fin("Borsch.txt");
	string name, s;
	int n;
	if (fin.is_open())
	{
		map <string, int> addin;
		while (fin) {
			for (map <string, int>::iterator it = addin.begin(); it != addin.end(); ++it)
			{
				cout << it->first << "\t" << it->second << "\n";
			}
		}
	}

	for (auto i = Borsch.begin(); i != Borsch.end(); ++i)
	{
		std::cout << i->first << " : " << i->second << endl; //вывод на экран всей карты 
	}*/

	LoadObj(fin, Borsch);

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



//	map <string, int> Beefsteak = {
//	};


	Name_i_Recept.emplace("Borsch", Borsch); //добавление рецептов в MAP 
	Name_i_Recept.emplace("Soup", Soup);
	Name_i_Recept.emplace("Beefsteak", Beefsteak);
	Name_i_Recept.emplace("Meatballs", Meatballs);
	Name_i_Recept.emplace("Risotto", Risotto);
	Name_i_Recept.emplace("Omelet", Omelet);


	std::cout << "WE already HAVE recepts Like" << endl;
	for (auto i = Name_i_Recept.begin(); i != Name_i_Recept.end(); ++i)
	{
		std::cout << i->first<< endl; //вывод на экран всей карты 
	}
	std::cout << " ________________________" << endl;


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
	{ "Tomato paste ", 200 },
	{ "Vegetable_oil", 430 },
	{ "Vinegar", 200 },
	{ "Sour_cream", 10 },
	{ "Eggs", 500 },
	{ "Salt", 200 },
	{ "Black_pepper", 200 },
	{ "Water", 5000 },
	{ "Bay_leaves", 20 } };

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

	map <string, int> Rest_Fridge(Fridge); //Первоначальный холодильник Оставлю так на всякий случай, чтобы потом не побить 
	const int Size = Name_i_Recept.size();
	int counto = 0;
	int flag = 0;
	vector <int> Flags(Size);
	vector <string> Allocation(Size);

	//Что-то вырисовывается 
	for (auto Recept = Name_i_Recept.begin(); Recept != Name_i_Recept.end(); ++Recept) //Проход по вектору перебираем список рецептов а ниже разворачиваем сам рецепт типа это нназвание борщ, а ниже пошло "морковка свекла мясо итд..." в данном случае и i j это map
	{
		Allocation[counto] = Recept->first;
		Fridge = Vlezaet(Fridge, Recept->second, flag);
		Flags[counto] = flag;//тому который только что пришел
		//std::cout << Recept->first << "   ___" << endl;
		counto++;
	}

	std::cout <<"Your menu for today" << endl; //вывод на экран всей карты 
	for (auto i = 0; i<Size; ++i)
	{
		if (Flags[i]==0)
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