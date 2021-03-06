#define _CRT_SECURE_NO_WARNINGS

#include "ttextlink.h"
#include "ttext.h"
#include <iostream>
#include <cstring>

PTTextMem TTextLink::MemHeader = new TTextMem();
void TTextLink::InitMemSystem(int size) // ????????????? ??????
{
	MemHeader->pFirst = (PTTextLink) new char[sizeof(TTextLink) * size];
	MemHeader->pFree = MemHeader->pFirst;
	MemHeader->pLast = MemHeader->pFirst + (size - 1);
	PTTextLink pLink = MemHeader->pFirst;
	for (int i = 0; i < size - 1; ++i, pLink++)
		pLink->pNext = pLink + 1;
	pLink->pNext = nullptr;
}

void TTextLink::PrintFreeLink()//?????? ????????? ???????
{
	PTTextLink pLink = MemHeader->pFree;
	std::cout << "List of free links" << std::endl;
	while (pLink != nullptr)
	{
		std::cout << pLink->Str << std::endl;
		pLink = pLink->pNext;
	}
}

void* TTextLink::operator new(size_t size)
{
	PTTextLink pLink = MemHeader->pFree;
	if (MemHeader->pFree != nullptr)
		MemHeader->pFree = pLink->pNext;
	return pLink;
}

void TTextLink::operator delete(void* pM)
{
	PTTextLink pLink = (PTTextLink)pM;
	pLink->pNext = MemHeader->pFree;
	MemHeader->pFree = pLink;
}

void TTextLink::MemCleaner(TText& txt)
{
	std::string st;

	for (txt.Reset(); !txt.IsTextEnded(); txt.GoNext())
	{
		if (st.find("&&&") != 0)
		{
			txt.SetLine("&&&" + txt.GetLine());
		}
	}
	PTTextLink pLink = MemHeader->pFree;
	while (pLink != nullptr)
	{
		strcpy(pLink->Str, "&&&");
		pLink = pLink->pNext;
	}
	pLink = MemHeader->pFirst;
	for (; pLink <= MemHeader->pLast; pLink++)
		if (strstr(pLink->Str, "&&&") != nullptr)
			strcpy(pLink->Str, pLink->Str + 3);
		else
			delete pLink;
}

