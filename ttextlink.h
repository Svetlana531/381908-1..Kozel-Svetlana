#pragma once

#include "ttext.h"

class TText;
class TTextLink;
typedef TTextLink* PTTextLink;

class TTextMem
{
	PTTextLink pFirst;	// ������ 
	PTTextLink pLast;	// ���������
	PTTextLink pFree;	// ��������� ������
	friend class TTextLink;
};
typedef TTextMem* PTTextMem;

class TTextLink
{
protected:
	TStr Str;
	PTTextLink pNext, pDown;
	static  PTTextMem MemHeader;

public:
	static void InitMemSystem(int size = MemSize);		// �������������� ������
	static void PrintFreeLink();						// ������� ��������� ������

	void* operator new (size_t size);
	void operator delete(void* pM);

	static void MemCleaner(TText& txt);		// ������ ������
	TTextLink(TStr s = nullptr, PTTextLink pn = nullptr, PTTextLink pd = nullptr)
	{
		pNext = pn;
		pDown = pd;
		if (s != nullptr)
		{
			strcpy(Str, s);
		}
		else
		{
			Str[0] = '\0';
		}
	}
	~TTextLink() {}
	bool IsAtom() { return pDown == nullptr; }
	PTTextLink GetNext() { return pNext; }
	PTTextLink GetDown() { return pDown; }

protected:
	virtual void Print(std::ostream& os) { os << Str; }
	friend class TText;
};

