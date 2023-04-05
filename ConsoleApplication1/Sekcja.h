#pragma once
#include "String.h"

struct selektor {
	String nazwa;
	selektor* next = nullptr;
};
struct atrybut {
	String nazwa;
	String wartosc;
	atrybut* next = nullptr;
};

class Sekcja
{
	struct selektor* selhead = new struct selektor();
	struct selektor* lista_sel = selhead;
	struct atrybut* atrhead = new struct atrybut();
	struct atrybut* lista_atr = atrhead;

	void FreeMemory();
public:
	Sekcja();
	
	void AddSelektor(const String& data);
	void AddAtrybutNazwa(const String& data);
	void AddAtrybutWartosc(const String& data, const String& name);

	int NumberOfSelectors() const;
	int NumberOfAtributes() const;
	String JSelektor(int j) const;
	String WartoscArt(const String& n) const;
	int IsAtr(const String& n) const;
	int IsSel(const String& z) const;
	int DeleteAtr(const String& n);
	void ResetValues();
	void Kopiarka(Sekcja& other);
	
	~Sekcja();
};

