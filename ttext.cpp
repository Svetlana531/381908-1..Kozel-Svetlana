#define _CRT_SECURE_NO_WARNINGS
#define BuferLength 80
#include "ttext.h"
#include <iostream>
#include <fstream>
#include <cstring>

static int TextLevel;

TText::TText(PTTextLink pl)
{
	if (pl == nullptr)
	{
		pl = new TTextLink();
	}
	pCurrent = pFirst = pl;
}

// Навигация
void TText::GoFirstLink()
{
	while (!Path.empty())
		Path.pop(); //очистка стека
	pCurrent = pFirst;
	if (pCurrent == nullptr)
	{
		throw "GoFirstLink error: Link is not found";
	}
}

void TText::GoDownLink()
{
	if ((pCurrent != nullptr) && (pCurrent->pDown != nullptr))
	{
		Path.push(pCurrent);
		pCurrent = pCurrent->pDown;
	}
	else
	{
		throw "GoDownLink error: Link is not found";
	}
}

void TText::GoNextLink()
{
	if ((pCurrent != nullptr) && (pCurrent->pNext != nullptr))
	{
		Path.push(pCurrent);
		pCurrent = pCurrent->pNext;
	}
	else
	{
		throw "GoNextLink error: Link is not found";
	}
}

void TText::GoPrevLink()
{
	if (Path.empty())
	{
		throw "GoPrevLink error: Previous links is not found";
	}
	else
	{
		pCurrent = Path.top();
		Path.pop();
	}
}

// Доступ
std::string TText::GetLine()
{
	if (pCurrent == nullptr)
	{
		return std::string("");
	}
	else
	{
		return pCurrent->Str;
	}
}

void TText::SetLine(std::string s)
{
	if (pCurrent == nullptr)
	{
		throw "The link to the current link is empty";
	}
	else
	{
		strncpy(pCurrent->Str, s.c_str(), s.size() + 1);
	}
	pCurrent->Str[s.size()] = '\0';
}

// модификация
void TText::InsDownLine(std::string s)
{
	if (pCurrent == nullptr)
	{
		throw "The link to the current link is empty";
	}
	else
	{
		PTTextLink pd = pCurrent->pDown;
		PTTextLink pl = new TTextLink(NULL, pd, nullptr);
		strncpy(pl->Str, s.c_str(), TextLineLength);
		pl->Str[TextLineLength - 1] = '\0';
		pCurrent->pDown = pl;
	}
}

void TText::InsDownSection(std::string s)
{
	if (pCurrent == nullptr)
	{
		throw "The link to the current link is empty";
	}
	else
	{
		PTTextLink pd = pCurrent->pDown;
		PTTextLink pl = new TTextLink(NULL, nullptr, pd);
		strncpy(pl->Str, s.c_str(), TextLineLength);
		pl->Str[TextLineLength - 1] = '\0';
		pCurrent->pDown = pl;
	}
}

void TText::InsNextLine(std::string s)
{
	if (pCurrent == nullptr)
	{
		throw "The link to the current link is empty";
	}
	else {
		PTTextLink pd = pCurrent->pNext;
		PTTextLink pl = new TTextLink(NULL, pd, nullptr);
		strncpy(pl->Str, s.c_str(), TextLineLength);
		pl->Str[TextLineLength - 1] = '\0';
		pCurrent->pNext = pl;
	}
}

void TText::InsNextSection(std::string s)
{
	if (pCurrent == nullptr)
	{
		throw "The link to the current link is empty";
	}
	else {
		PTTextLink pd = pCurrent->pNext;
		PTTextLink pl = new TTextLink(NULL, nullptr, pd);
		strncpy(pl->Str, s.c_str(), TextLineLength);
		pl->Str[TextLineLength - 1] = '\0';
		pCurrent->pNext = pl;
	}
}

void TText::DelDownLine()
{
	if (pCurrent == nullptr)
	{
		throw "The link to the current link is empty";
	}
	else if (pCurrent->pDown != nullptr)
	{
		PTTextLink pl1 = pCurrent->pDown;
		PTTextLink pl2 = pl1->pNext;
		if (pl1->pDown == nullptr)
			pCurrent->pDown = pl2;
	}
}

void TText::DelDownSection()
{
	if (pCurrent == nullptr)
	{
		throw "The link to the current link is empty";
	}
	else if (pCurrent->pDown != nullptr)
	{
		PTTextLink pl1 = pCurrent->pDown;
		PTTextLink pl2 = pl1->pNext;
		pCurrent->pDown = pl2;
	}
}

void TText::DelNextLine()
{
	if (pCurrent == nullptr)
	{
		throw "The link to the current link is empty";
	}
	else if (pCurrent->pNext != nullptr)
	{
		PTTextLink pl1 = pCurrent->pNext;
		PTTextLink pl2 = pl1->pNext;
		if (pl1->pNext == nullptr)
			pCurrent->pNext = pl2;
	}
}

void TText::DelNextSection()
{
	if (pCurrent == nullptr)
	{
		throw "The link to the current link is empty";
	}
	else if (pCurrent->pNext != nullptr) {
		PTTextLink pl1 = pCurrent->pNext;
		PTTextLink pl2 = pl1->pNext;
		pCurrent->pNext = pl2;
	}
}

// Итератор
int TText::Reset()
{
	while (!St.empty())
		St.pop();
	pCurrent = pFirst;
	if (pCurrent != nullptr)
	{
		St.push(pCurrent);
		if (pCurrent->pNext != nullptr)
			St.push(pCurrent->pNext);
		if (pCurrent->pDown != nullptr)
			St.push(pCurrent->pDown);
	}
	return IsTextEnded();
}

int TText::IsTextEnded()const
{
	return !St.size();
}

int TText::GoNext()
{
	if (!IsTextEnded())
	{
		pCurrent = St.top();
		St.pop();
		if (pCurrent->pNext != nullptr)
			St.push(pCurrent->pNext);
		if (pCurrent->pDown != nullptr)
			St.push(pCurrent->pDown);
	}
	return IsTextEnded();
}

PTTextLink TText::GetFirstAtom(PTTextLink pl)
{
	PTTextLink tmp = pl;
	while (!tmp->IsAtom())
	{
		St.push(tmp);
		tmp = tmp->GetDown();
	}
	return tmp;
}

PTText TText::GetCopy()
{
	PTTextLink pl1, pl2, pl = pFirst, cpl = nullptr;

	if (pFirst != nullptr)
	{
		while (!St.empty())
			St.pop();
		while (1)
		{
			if (pl != nullptr)
			{
				pl = GetFirstAtom(pl);
				St.push(pl);
				pl = pl->GetDown();
			}
			else if (St.empty())
				break;
			else
			{
				pl1 = St.top(); St.pop();
				if (strstr(pl1->Str, "Copy") == nullptr)
				{
					pl2 = new TTextLink(NULL, pl1, cpl);
					char tmp[TextLineLength] = "Copy";
					strcpy(pl2->Str, tmp);
					St.push(pl2);
					pl = pl1->pNext;
					cpl = nullptr;
				}
				else
				{
					pl2 = pl1->GetNext();
					strcpy(pl1->Str, pl2->Str);
					pl1->pNext = cpl;
					cpl = pl1;
				}
			}
		}
	}
	return new TText(cpl);
}

// печать текста
void TText::Print()
{
	TextLevel = 0;
	PrintText(pFirst);
}

void TText::PrintText(PTTextLink ptl)
{
	if (ptl != nullptr)
	{
		for (int i = 0; i < TextLevel; i++)
		{
			std::cout << "  ";
		}

		std::cout << " " << ptl->Str << std::endl;
		TextLevel++; PrintText(ptl->GetDown());
		TextLevel--; PrintText(ptl->GetNext());
	}
}

void TText::Write(std::string PATH)
{
	std::ofstream f;
	f.open(PATH);
	if (!f.is_open())
	{
		throw "File is not open!";
	}
	TextLevel = 0;
	workOutputFile(f, pFirst);
}

void TText::workOutputFile(std::ofstream& f, PTTextLink ptl)
{
	if (ptl != NULL)
	{
		for (int i = 0; i < TextLevel; i++)
		{
			f << "  ";
		}
		f << ptl->Str << std::endl;
		TextLevel++; workOutputFile(f, ptl->GetDown());
		TextLevel--; workOutputFile(f, ptl->GetNext());
	}
}

TText TText::Read(std::string PATH)
{
	TText res;
	std::ifstream f(PATH);
	TextLevel = 0;
	if (!f.is_open())
	{
		throw "File is not open!";
	}
	res = *workInputFile(f);
	return res;
}

PTText TText::workInputFile(std::ifstream& f)
{
	char buf[BuferLength];			// Полученная строка из текста
	
	PTText res = new TText();		// Текст в который будем записывать
	// Ставим на начало и записываем пустоту
	res->GoFirstLink();
	res->SetLine("");

	int counterSpace[30] = { 0 };	// Количество пробелов в каждой строке текста
	int it = 0;		 // Счётчик для массива пробелов	
	int counter = 0; // количество считанных строк
	
	while (f.eof() == 0)	// Пока не конец файла 
	{
		f.getline(buf, BuferLength, '\n');	

		std::string tmp;	// Для хранения строки из файла
		for (int i = 0; i < BuferLength; i++)
		{
			if (buf[i] == '\0') { break; }
			if ((buf[i] == ' ') && (buf[i + 1] == ' ')) { counterSpace[it]++; }
			tmp += buf[i];
		}
		it++;
		if (buf[0] != ' ')	// Если перед словом нет пробелов
		{
			if (counter > 0)	// Встреченное слово первое?
			{
				while (!Path.empty()) { Path.pop(); }	// Отчищаем наш путь
				// Возвращаемся к "верхушке"
				for (int j = 0; j < TextLevel - 1; j++)
				{
					res->GoPrevLink();
				}
				TextLevel = 0;
				res->InsNextSection(tmp);
				res->GoNextLink();
				counter++;
			}
			else
			{
				// Заходит сюда 1 раз что бы записать начальную строку
				res->SetLine(tmp);
				counter++;
			}
		}
		else if (buf[0] == ' ') // Встречен пробел
		{
			TextLevel++;
			if (TextLevel > 1)
			{
				res->GoDownLink();
			}
			if (counterSpace[it - 2] == counterSpace[it - 1])	// Если слово находится на том же уровне
			{
				res->InsNextSection(tmp);
			}
			else
			{
				res->InsDownSection(tmp);
			}
		}
	}

	return res;
}

