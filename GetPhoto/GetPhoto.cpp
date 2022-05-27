// GetPhoto.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#define IBPP_WINDOWS
#include <iostream>
#include <ibpp.h>
#include <all_in_one.cpp>
#include <fstream>
#include <clocale>

using namespace std;

int main()
{
	int assetId = 0;
	
	string srv("");
	string pth("");
	string req_list("");
	string req_photo("select OS_PHOTO from TAB_TECHINFO where id_main_tab = 520");
	string username("");
	string passw("");

	//string req_photo("");
	int id_mt;
	string inv;
	string subdiv_name;
	string asset_name;
	string items_list_name("items_list.csv");

	void *a = new char[10000000];
	
	int *size = 0;
	int *largest = 0;
	int *segments = 0;

	setlocale(LC_CTYPE, "rus");

	/*cout << "Please enter server address: " << "\n";
	cin >> srv;
	cout << "Please enter db path: " << "\n";
	cin >> pth;
	cout << "Please enter username: " << "\n";
	cin >> username;
	cout << "Please enter password: " << "\n";
	cin >> passw;*/

	//cout << "Pleae enter path to database using DB Master format:\n";
	try
	{
		ofstream items_file;
		items_file.open(items_list_name);
		items_file << "ID" << " ; " << "INV" << ";" << "SUBDIV_NAME" << " ; " << "NAME" << "\n";

		IBPP::Database db = IBPP::DatabaseFactory(srv, pth, username, passw);
		db->Connect();
		IBPP::Transaction tr = IBPP::TransactionFactory(db);
		tr->Start();

		IBPP::Statement st = IBPP::StatementFactory(db, tr);
		st->Execute(req_list);
		while (st->Fetch())
		{
			st->Get(1, id_mt);
			st->Get(2, inv);
			st->Get(3, subdiv_name);
			st->Get(4, asset_name);
			cout << id_mt << " - " << inv << " - " << subdiv_name << " - " << asset_name.c_str() << "\n";
			items_file << id_mt << " ; " << inv << " ; " << subdiv_name << " ; " << asset_name.c_str() << "\n";
		}
		cout << "Перечень активов, для которых есть фото, сохранён в файл " << items_list_name << "\n";
		items_file.close();

		ofstream photo_file;
		photo_file.open("photo.jpg");

		IBPP::Blob bl = BlobFactory(db, tr);
		st->Execute(req_photo);
		st->Fetch();
		st->Get(1, bl);

		bl->Open();

		bl->Info(size, largest, segments);
		cout << size << largest << segments;

		while (bl->Read(a, 63999)) {
			bl->Read(a, 63999);
			photo_file << a;
		}
		

		//ofstream wf("photo.jpg", ios::out | ios::binary);
		//wf.write(bl);
		//wf.close();
		photo_file.close();

		bl->Close();
		


		tr->Rollback();
		db->Disconnect();
		
	}
	catch (IBPP::Exception& e)
	{
		cout << e.ErrorMessage();
	}

	//cout << "Pleae enter asset ID:\n";
	//cin >> assetId;
	system("pause");
	return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
