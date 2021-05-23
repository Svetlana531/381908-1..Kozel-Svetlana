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
	std::stack<PTTextLink> Path; //���� ����������� �������� �� ������
	// pCurrent � ���� �� ������

	std::stack<PTTextLink> St;
	PTTextLink GetFirstAtom(PTTextLink pl);

public:
	TText(PTTextLink pl = nullptr);
	~TText() { pFirst = nullptr; }

	PTText GetCopy();	// ����������� ������

	// ���������
	void GoFirstLink(void); // ������� � ������ ������
	void GoDownLink(void);  // ������� � ��������� ������ �� Down
	void GoNextLink(void);  // ������� � ��������� ������ �� Next
	void GoPrevLink(void);  // ������� � ���������� ������� � ������

	// ������
	std::string GetLine(void);		// ������ ������� ������
	void SetLine(std::string s);	// ������ ������� ������ 

	// �����������
	void InsDownLine(std::string s);    // ������� ������ � ����������
	void InsDownSection(std::string s); // ������� ������� � ����������
	void InsNextLine(std::string s);    // ������� ������ � ��� �� ������
	void InsNextSection(std::string s); // ������� ������� � ��� �� ������

	void DelDownLine(void);        // �������� ������ � ���������
	void DelDownSection(void);     // �������� ������� � ���������
	void DelNextLine(void);        // �������� ������ � ��� �� ������
	void DelNextSection(void);     // �������� ������� � ��� �� ������

	// ��������
	int Reset();			// ���������� �� ������ ������
	int IsTextEnded()const; // ������� ���������
	int GoNext();			// ������� � ��������� ������

	// ������ � �������
	void Write(std::string PATH);	// ����� ������ � ����
	void workOutputFile(std::ofstream& f, PTTextLink ptl);

	TText Read(std::string PATH);	// ������ ������ �� �����
	PTText workInputFile(std::ifstream& f);

	// ������
	void Print();
	void PrintText(PTTextLink ptl);
};

