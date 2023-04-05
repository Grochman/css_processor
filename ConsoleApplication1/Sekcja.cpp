#include "Sekcja.h"
Sekcja::Sekcja() {
}

void Sekcja::AddSelektor(const String& data) {
	lista_sel->nazwa = data;
	//std::cout << lista_sel->nazwa << '\n';
	lista_sel->next = new selektor();
	lista_sel = lista_sel->next;
	lista_sel->next = nullptr;
	
}
void Sekcja::AddAtrybutNazwa(const String& data) {
	struct atrybut* temp = atrhead;
	while (temp->next != nullptr) {
		if (temp->nazwa == data)
			return;
		temp = temp->next;
	}
	lista_atr->nazwa = data;
	//std::cout << lista_atr->nazwa << '\n';
	lista_atr->next = new atrybut();
	lista_atr = lista_atr->next;
	lista_atr->next = nullptr;
	
}
void Sekcja::AddAtrybutWartosc(const String& data, const String& name) {
	struct atrybut* temp = atrhead;
	while (true) {
		if (temp->nazwa == name) {
			temp->wartosc = data;
			break;
		}
		if (temp->next != nullptr)
			temp = temp->next;
		else break;
	}
	//std::cout << temp->wartosc << '\n';
}

int Sekcja::NumberOfSelectors() const {
	int x = 0;
	struct selektor* temp = selhead;
	
	while (temp->next != nullptr) {
		if(temp->nazwa.GetSize()>0)x++;
		temp = temp->next;
	}
	return x;
}
int Sekcja::NumberOfAtributes() const{
	int x = 0;
	struct atrybut* temp = atrhead;

	while (temp->next != nullptr) {
		x++;
		temp = temp->next;
	}
	return x;
}
String Sekcja::JSelektor(int j) const {
	struct selektor* temp = selhead;
	String a;
	while (j>1) {
		if (temp->next->next != nullptr)
			temp = temp->next;
		else {
			return a;
		}
		j--;
	}
	return temp->nazwa;
}
String Sekcja::WartoscArt(const String& n) const {
	struct atrybut* temp = atrhead;
	String a;
	while (temp->next != nullptr) {
		if (temp->nazwa == n) return temp->wartosc;
		temp = temp->next;
	}
	return a;
}
int Sekcja::IsAtr(const String& n) const {
	struct atrybut* temp = atrhead;
	while (true) {
		if (temp->nazwa == n) return 1;
		if (temp->next != nullptr)temp = temp->next;
		else return 0;
	}
}
int Sekcja::IsSel(const String& z) const {
	struct selektor* temp = selhead;
	while (true) {
		if (temp->nazwa == z) return 1; // || temp->nazwa.GetSize() == 0) co jesli nie ma atrybutu w tym bloku
		if (temp->next != nullptr)temp = temp->next;
		else return 0;
	}
}
int Sekcja::DeleteAtr(const String& n) {
	int x = 0;
	struct atrybut* temp = atrhead;
	while (true) {
		if (temp->nazwa == n) break;
		if (temp->next != nullptr) {
			temp = temp->next;
			x++;
		}
		else return -1;
	}
	temp = atrhead;
	
	if (x == 0) {
		atrhead = atrhead->next;
	}
	else {
		for (int i = 0; i < x-1; i++) {
			temp = temp->next;
		}
		delete temp->next;
		if (temp->next->next != nullptr)temp->next = temp->next->next;
		else temp->next = nullptr;
	}
	
	return x;
}
void Sekcja::ResetValues() {
	FreeMemory();
	selhead = lista_sel;
	atrhead = lista_atr;
}
void Sekcja::Kopiarka(Sekcja& other) {
	FreeMemory();
	delete selhead;
	delete atrhead;

	this->selhead = other.selhead;
	this->atrhead = other.atrhead;
	this->lista_atr = other.lista_atr;
	this->lista_sel = other.lista_sel;
	other.selhead = new selektor();
	other.atrhead = new atrybut();
	other.lista_sel = other.selhead;
	other.lista_atr = other.atrhead;
}

Sekcja::~Sekcja() {
	FreeMemory();
	delete selhead;
	delete atrhead;
}

void Sekcja::FreeMemory() {
	struct selektor* tempsel = selhead;
	while (tempsel->next != nullptr) {
		tempsel = tempsel->next;
		delete selhead;
		selhead = tempsel;
	}
	struct atrybut* tempatr = atrhead;
	while (tempatr->next != nullptr) {
		tempatr = tempatr->next;
		delete atrhead;
		atrhead = tempatr;
	}
}