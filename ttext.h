#pragma once

#include <stack>
#include <iostream>
#include <fstream>
#include <string>
#include "defines.h"
#include "ttextlink.h"

class TText
{
protected:
	PTTextLink pFirst;
	PTTextLink pCurrent;
	std::stack<PTTextLink> Path; //стек траекториии движения по тексту
	// pCurrent в стек не входит

	std::stack<PTTextLink> St;
	PTTextLink GetFirstAtom(PTTextLink pl);

public:
	TText(PTTextLink pl = nullptr);
	~TText() { pFirst = nullptr; }

	PTText GetCopy();	// Копирование текста

	// Навигация
	void GoFirstLink(void); // Переход к первой строке
	void GoDownLink(void);  // Переход к следующей строке по Down
	void GoNextLink(void);  // Переход к следующей строке по Next
	void GoPrevLink(void);  // Переход к предыдущей позиции в тексте

	// Доступ
	std::string GetLine(void);		// Чтение текущей строки
	void SetLine(std::string s);	// Замена текущей строки 

	// Модификация
	void InsDownLine(std::string s);    // Вставка текста в подуровень
	void InsDownSection(std::string s); // Вставка раздела в подуровень
	void InsNextLine(std::string s);    // Вставка текста в том же уровне
	void InsNextSection(std::string s); // Вставка раздела в том же уровне

	void DelDownLine(void);        // Удаление текста в подуровне
	void DelDownSection(void);     // Удаление раздела в подуровне
	void DelNextLine(void);        // Удаление текста в том же уровне
	void DelNextSection(void);     // Удаление раздела в том же уровне

	// Итератор
	int Reset();			// Установить на первую запись
	int IsTextEnded()const; // Таблица завершена
	int GoNext();			// Переход к следующей записи

	// Работа с файлами
	void Write(std::string PATH);	// Вывод текста в файл
	void workOutputFile(std::ofstream& f, PTTextLink ptl);

	TText Read(std::string PATH);	// Чтение текста из файла
	PTText workInputFile(std::ifstream& f);

	// Печать
	void Print();
	void PrintText(PTTextLink ptl);
};

