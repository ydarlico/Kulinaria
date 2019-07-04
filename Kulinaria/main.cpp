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

	unordered_map <string, map<string, int>> Name_i_Recept; //������ ����� ������ ��� ���� map ���� map<����, map ������ �����> ��� �� �������� ��� ��������� ����� �����������

	/*map <string, int> Borsch = { 
	{ "Beef", 500 }, 
	{ "Beets ", 300 }, //������
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
		std::cout << i->first << " : " << i->second << endl; //����� �� ����� ���� ����� 
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



//	map <string, int> Beefsteak = {
//	};


	Name_i_Recept.emplace("Borsch", Borsch); //���������� �������� � MAP 
	Name_i_Recept.emplace("Soup", Soup);
	Name_i_Recept.emplace("Beefsteak", Beefsteak);
	Name_i_Recept.emplace("Meatballs", Meatballs);
	Name_i_Recept.emplace("Risotto", Risotto);
	Name_i_Recept.emplace("Omelet", Omelet);


	std::cout << "WE already HAVE recepts Like" << endl;
	for (auto i = Name_i_Recept.begin(); i != Name_i_Recept.end(); ++i)
	{
		std::cout << i->first<< endl; //����� �� ����� ���� ����� 
	}
	std::cout << " ________________________" << endl;


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
		cout << it->first << " : " << it->second << endl; //����� �� ����� ���� �������� ������ ��� ����� 
	}
	std::cout << "STOP_____XOLODILNOK______" << '\n';

	flag = 0;
	std::cout << "VLEZAET_________ " << '\n';
	Fridge = Vlezaet(Fridge, Risotto, flag);
	std::cout << "XOLODILNOK______" << '\n';
	for (auto it = Fridge.begin(); it != Fridge.end(); ++it)
	{
		cout << it->first << " : " << it->second << endl; //����� �� ����� ���� �������� ������ ��� ����� 
	}
	std::cout << "STOP_____XOLODILNOK______" << '\n';*/





	//map <string, int> Rest_Fridge(Fridge); //�������������� ����������� ������� ��� �� ������ ������, ����� ����� �� ������ 

	//std::cout << "Count of Potatos in your Fridge => " << Fridge.find("Potatoes")->second << '\n'; //�������� ��� ����������

	//�������� 

	//vector <string> Good_formulas; //������� ������� �� ������ ����� ������ ��� ���� map ���� map<����, map ������ �����> ��� �� �������� ��� ��������� ����� �����������

	/*for (auto i = Name_i_Recept.begin(); i != Name_i_Recept.end(); ++i) //������ �� �������
	{
		//������� ������ ���
		for (auto it = i->second.begin(); it != i->second.end(); ++it) //���������� �� ����� �������� � ���, � i �������� ����� ������� � ������� �� ������ ����� 
		{

			for (auto id = Fridge.begin(); id != Fridge.end(); ++id) 
			{ // ������� ����������� � ������� ������
				if (id->first == it->first) 
				{
					if (id->second < it->second)     //���� 20 ������ ������ ��� 2 ����� �� ���� ������ ��� ��������  ���� � �������� ������ ��� �����
					{
						//std::cout << "BAD ingredient  " << id->first << it->first << endl; //�������� �� ��������� �.� �� ����� 10 ���� � ����� 200 ������
						Ostatok = 0;
						break; //���� ���� ��� ������� ��� ���������� - ������ ���� ������ � �������
					}
					else
					{
						//std::cout << "Good ingredient  " << id->first << it->first << endl; //����������� ������� ��� ������� id - �������  it -������
						Ostatok += (id->second - it->second); //�������� �������, �.� ��� ��������� � �������� ����� ��������������� ������������� 
						//std::cout << "OSTATOK SEGOTO TAM _   " << id->first << " || " << Ostatok << endl;


					}
				}
				//�������� ���� ���� ��� ������� ��� ���������� - ������ ���� ������ � �������
				//��������� �� ������ 

				//����������� - ���� � ������� �������� ��������� ������� ���������� ����� ���� ���� 500� ���� 
				// ����� ������� ���� � ��������� 400/500 ������� 100 
				//��� ������� �� �� ���� ������� � ��������� 50/500 � ��������� 450 ��� ��� ����������� 

				//�, ���� ���������� ��� ������� � ������/����������� � ���������� � ����� ������� ������ ����� �� ����� ������� � ��� ����� ������� ������ ��� � ��� ������ 


			} //������� ����������� ������� ������ ���������. �� ��� �� ������ ������� ����� ������ 
			//cout << it->first << " : " << it->second << endl; //����� �� ����� ���� �����  ���� ��������-����������
		}
		Good_formulas.emplace_back(Ostatok);
		Ostatok = 0;
		//std::cout << "END FORMULA____________________" << endl;
	}

	std::vector<int>::iterator min = std::min_element(Good_formulas.begin(), Good_formulas.end());
	int iter = std::distance(Good_formulas.begin(), min); //�������� ������� �������� �.� ���� ��� ��������
	std::cout << "Min element " << *min << " on position " << iter << endl;

	//std::cout << "The best formulas for you is " << Name_i_Recept[iter]->first << endl; //�� ���� ��� ������ ���������/��������� ��� ����� �������� ��� ��������� � ��������� ��������� ��� iter �������
	int j = 1;

	for (auto i = Name_i_Recept.begin(); j < iter; ++i) //������ �� �������
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
	//��������/���������� ��� �.� �� ������ �������� ������ � ������ ������ �� ������ ������ ����� ����� � ���������� ���������� map � ������� 
	/*const int Size = Name_i_Recept.size();
	const int Size_k = Fridge.size();
	cout << Size << "Size ==" << endl;

	map <string, int> Rest_Fridge(Fridge); //������� � ������������// ������ ����� �������� 
	vector <int> Flags (Size); //���-�� �������� �.� ����������� i ����� ������ ������
	vector <int> Allocation(Size); //���������� 
	
	for (int j = 0; j < Size; j++)
	{
		Flags[j] = 0; 
		Allocation[j] = -1;
	}

	int k,n,temp;

	//������� ������� ���� �� first-fit

	for (auto i = Name_i_Recept.begin(); i != Name_i_Recept.end(); ++i) //������ �� ������� ���������� ������ �������� � ���� ������������� ��� ������ ���� ��� ��������� ����, � ���� ����� "�������� ������ ���� ���..."
	{
		n = 0;//������ �����������
		for (auto it = i->second.begin(); it != i->second.end(); ++it) //���������� �� ����� �������� � ���, � i �������� ����� ������� � ������� �� ������ ����� �.� ������ ���� ����� ��� ����� ��� ���-��
		{
			k = 0;
			for (auto id = Fridge.begin(); id != Fridge.end(); ++id)
			{ // ������� ����������� � ������� ������
			  std::cout << "__NOW_ingredient  " << id->first << it->first << endl; //����������� ������� ��� ������� id - �������  it -������
				if (id->first == it->first) //���������� ���������� �������� ��� ���
				{
					std::cout << "__NOW_GOOOD_ingredient  " << id->first << it->first << endl; //����������� ������� ��� ������� id - �������  it -������
					if ((Flags[n] == 0) &&(id->second >= it->second))     //���� ��� ������� ����� � ������ ��� �� ��� ��������� �.� ��� �� ����� ����� 
					{
						Allocation[n] = k; //��������� ����� ����������
						Flags[n] = 1;      // ������� ��� ���� ������ ��� �� �����
						cout << "SHA BUDET BREAK" << "   " << endl;
						break;             // ����� �������, ������ �� ������� ��������

					}
					
				}
			k++; if (k == Size) break;
			cout << "===k=      " <<k << "=k     " << endl;
			}
			n++; if (n == Size) break;
			cout << "=====n      " << n << "=====n      " << endl;
		}//������� ������ �� ��� �� ������� �����, i �������� ����� ������� � ������� �� ������ ����� �.� ������ ���� ����� ��� ����� ��� ���-��, �� ������ �������� � ��� �������� "����-"����

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
		std::cout << id->first << " : " << id->second << endl; //����� �� ����� ���� ����� 
	}

	std::cout << "What we hawe in end" << endl;
	for (auto i = 0; i<Good_formulas.size(); ++i)
	{
		std::cout << Good_formulas[i] <<"   "<< endl; //����� �� ����� ���� ����� 
	}*/

	map <string, int> Rest_Fridge(Fridge); //�������������� ����������� ������� ��� �� ������ ������, ����� ����� �� ������ 
	const int Size = Name_i_Recept.size();
	int counto = 0;
	int flag = 0;
	vector <int> Flags(Size);
	vector <string> Allocation(Size);

	//���-�� �������������� 
	for (auto Recept = Name_i_Recept.begin(); Recept != Name_i_Recept.end(); ++Recept) //������ �� ������� ���������� ������ �������� � ���� ������������� ��� ������ ���� ��� ��������� ����, � ���� ����� "�������� ������ ���� ���..." � ������ ������ � i j ��� map
	{
		Allocation[counto] = Recept->first;
		Fridge = Vlezaet(Fridge, Recept->second, flag);
		Flags[counto] = flag;//���� ������� ������ ��� ������
		//std::cout << Recept->first << "   ___" << endl;
		counto++;
	}

	std::cout <<"Your menu for today" << endl; //����� �� ����� ���� ����� 
	for (auto i = 0; i<Size; ++i)
	{
		if (Flags[i]==0)
		std::cout << Allocation[i] << "   " << endl; //����� �� ����� ���� ����� 
	}

	//����� ������ � ������ �� ����������� �������
	//���� ����� ��� ������ ������� ����� ������� 
	//�������� ����� ������� ���������� �������  
	//����� ������� ��� ������ � � ���� ������������ ������� �� ������ ��������, �� ����� ����� � �������� ���������� � ��� �� ����� ����� ��������
	//������� ���������� �����

	//�������������� ���� ������� map �� vector int � vector string 

	system("pause");
	return 0;
}