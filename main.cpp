#define _CRT_SECURE_NO_WARNINGS

#include <locale>
#include "ttextlink.h"

#define PATH "C:\\out.txt"

void menu(TText p)
{
	std::cout << "\t!МЕНЮ!\n";
	std::cout << "1) Просмотреть весь текст\n";
	std::cout << "Изменение текста: \n";
	std::cout << "2) Заменить строку\n";
	std::cout << "Навигация: \n";
	std::cout << "3) Переход к первой строке\n";
	std::cout << "4) След. строка по Down\n";
	std::cout << "5) След. строка по Next\n";
	std::cout << "6) Предыдущая позиция\n";
	std::cout << "Добавление текста: \n";
	std::cout << "7) Вставка строки в подуровень\n";
	std::cout << "8) Вставка раздела в подуровень\n";
	std::cout << "9) Вставка строки в тот же уровень\n";
	std::cout << "10) Вставка раздела в тот же уровень\n";
	std::cout << "Удаление текста: \n";
	std::cout << "11) Удаление строки из подуровня\n";
	std::cout << "12) Удаление раздела из подуровня\n";
	std::cout << "13) Удаление строки на том же уровне\n";
	std::cout << "14) Удаление раздела на том же уровне\n";
	std::cout << "Работа с файлами: \n";
	std::cout << "15) Вывести текст в файл\n";
	std::cout << "16) Чтение текста с файла\n\n";

	std::cout << "Выбранная строка: " << p.GetLine() << "\n";

	std::cout << "> ";
}

int main()
{
	setlocale(LC_ALL, "RUS");
	TTextLink tl;
	tl.InitMemSystem(50);

	TText p;

	int choice;
	std::string tmp;

	p.SetLine("Zagolovok");

	p.InsDownSection("podurov_1");

	p.GoDownLink();
	p.InsDownSection("podurov_2");

	p.GoDownLink();
	p.InsDownSection("podurov_3");

	p.GoDownLink();
	p.InsNextLine("Text for podurov_3");

	p.GoFirstLink();
	p.InsNextSection("Oglav_2");

	p.GoNextLink();
	p.InsDownSection("poduroven_Oglav_1");

	p.GoDownLink();
	p.InsDownSection("poduroven_Oglav_2");

	p.GoFirstLink();


	/*//Проверка работы копирования
	TText* p_2;
	p_2 = p.GetCopy();
	p_2->Print();
	system("pause");
	*/

	while (true)
	{
		system("cls");
		menu(p);
		std::cin >> choice;

		switch (choice)
		{
		case 1:
			system("cls");
			p.Print();
			system("pause");
			break;
		case 2:
			system("cls");
			std::cout << "Введите строку: ";
			std::cin >> tmp;
			p.SetLine(tmp);
			system("pause");
			break;
		case 3:
			system("cls");
			p.GoFirstLink();
			system("pause");
			break;
		case 4:
			system("cls");
			p.GoDownLink();
			system("pause");
			break;
		case 5:
			system("cls");
			p.GoNextLink();
			system("pause");
			break;
		case 6:
			system("cls");
			p.GoPrevLink();
			system("pause");
			break;
		case 7:
			system("cls");
			std::cout << "Введите строку: ";
			std::cin >> tmp;
			p.InsDownLine(tmp);
			system("pause");
			break;
		case 8:
			system("cls");
			std::cout << "Введите строку: ";
			std::cin >> tmp;
			p.InsDownSection(tmp);
			system("pause");
			break;
		case 9:
			system("cls");
			std::cout << "Введите строку: ";
			std::cin >> tmp;
			p.InsNextLine(tmp);
			system("pause");
			break;
		case 10:
			system("cls");
			std::cout << "Введите строку: ";
			std::cin >> tmp;
			p.InsNextSection(tmp);
			system("pause");
			break;
		case 11:
			system("cls");
			p.DelDownLine();
			system("pause");
			break;
		case 12:
			system("cls");
			p.DelDownSection();
			system("pause");
			break;
		case 13:
			system("cls");
			p.DelNextLine();
			system("pause");
			break;
		case 14:
			system("cls");
			p.DelNextSection();
			system("pause");
			break;
		case 15:
			system("cls");
			p.Write(PATH);
			system("pause");
			break;
		case 16:
			system("cls");
			p = p.Read(PATH);
			p.GoFirstLink();
			system("pause");
			break;
		default:
			system("cls");
			std::cout << "Пункт выбран некоректно!\n";
			system("pause");
			break;
		}
	}
	return 0;
}
