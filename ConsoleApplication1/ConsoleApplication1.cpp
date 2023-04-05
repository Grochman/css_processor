#include <iostream>
#include <cstdlib>
#include "String.h"
#include "Sekcja.h"

#define ENTER char(10)

enum mode {
    css,
    comand
};
enum cssElement {
    selektor,
    atrybut
};
enum atrElement {
    nazwa,
    watrosc
};
enum comandElement {
    first,
    second,
    third
};

struct Block {
    const int t = 3;
    Sekcja* tabSekcji = new Sekcja[t];
    int zajete = 0;
    Block* next = nullptr;
    Block* prev = nullptr;
};
struct ElemKomend {
    int liczba = 0;
    char litera = '\0';
    String napis;
};

void resetElement(ElemKomend* e) {
    e->liczba = 0;
    e->litera = '\0';
    e->napis.Zeroj();
}

int getToI(struct Block* blok, int x) {
    while (blok->prev != nullptr) blok = blok->prev;
    while (x > blok->zajete) {
        x -= blok->zajete;
        if (blok->next != nullptr) blok = blok->next;
        else return -1;
    }
    return x;
}
struct Block* getToBlock(struct Block* blok, int x) {
    while (blok->prev != nullptr) blok = blok->prev;
    while (x > blok->zajete) {
        x -= blok->zajete;
        if (blok->next != nullptr) blok = blok->next;

    }
    return blok;
}
//dodatkowy struct zamiast dwoch funkcji - to samo (a moze pointer to pointer **)

void RemoveNode(struct Block* blok) {
    if (blok->prev != nullptr) {
        if (blok->next != nullptr) {
            blok->prev->next = blok->next;
            blok->next->prev = blok->prev;
            delete blok;
        }
    }
    else if (blok->next != nullptr) {
        blok->next->prev = nullptr;
        delete blok;
    }
}

void NumberOfSections(struct Block* blok, const String& a) {
    int result = 0;
    result += blok->zajete;
    while (blok->prev != nullptr) {
        blok = blok->prev;
        result += blok->zajete;
    }
    std::cout << a << " == " << result << '\n'; //?
}
void DeleteFunctions(struct Block* blok, ElemKomend& el3, String& a, int x) {
    int deletesekcja = 0;
    if (el3.napis.GetSize() > 0) {
        if (blok->tabSekcji[x - 1].DeleteAtr(el3.napis) != -1) {
            std::cout << a << " == " << "deleted" << '\n';;
            if (blok->tabSekcji[x - 1].NumberOfAtributes() == 0) {
                deletesekcja = 1;
            }
        }
    }
    if (el3.litera == '*' || deletesekcja == 1) {
        if(x==blok->zajete)blok->tabSekcji[x - 1].ResetValues(); // dodaj usuwanie prawdziwe

        while (x < blok->zajete) {
            //blok->tabSekcji[x - 1] = blok->tabSekcji[x]; //przepisywanie adresow wiec kopiarka customowa
            blok->tabSekcji[x - 1].Kopiarka(blok->tabSekcji[x]); // dodaj usuwanie prawdziwe
            x++;
        }
        blok->zajete--;
        if(deletesekcja != 1)std::cout << a << " == " << "deleted" << '\n';
    }
    if (blok->zajete == 0) RemoveNode(blok);
}
void Efunction(struct Block* blok, ElemKomend& el1, ElemKomend& el3, String& a) {
    int zajete = blok->zajete;
    int found = 0;
    while (found != 1) { // w razie selektora w paru miejscach
        while (zajete > 0) {
            if (blok->tabSekcji[zajete - 1].IsSel(el1.napis) > 0 && blok->tabSekcji[zajete - 1].WartoscArt(el3.napis).GetSize() > 0) {
                found = 1;
                break;
            }
            zajete--;
        }
        if (found == 1) break;
        else if (blok->prev != nullptr) {
            blok = blok->prev;
            zajete = blok->zajete;
        }
        else return;
    }
    //jesli chcemy wziac pod uwage logike css (selektor dziedziczy po *) to jesli result.GetSize() == 0 szukamy E dal */' '
    String result = blok->tabSekcji[zajete - 1].WartoscArt(el3.napis);
    if (result.GetSize() > 0)
        std::cout << a << " == " << result << '\n'; //z,E,n
}

void komendy(struct Block* blok, ElemKomend& el1, char el2, ElemKomend& el3, String& a) {
    if (el1.litera == '?') {
        NumberOfSections(blok, a);
    }
    else if (el1.liczba != 0) {
        int x = el1.liczba;
        int xcp = x;
        x = getToI(blok, x);
        if (x == -1) return;
        blok = getToBlock(blok, xcp);
        
        if (el3.litera == '?') {
            if (el2 == 'S') std::cout << a << " == " << blok->tabSekcji[x - 1].NumberOfSelectors() << '\n'; //i,S,?
            else if (el2 == 'A') std::cout << a << " == " << blok->tabSekcji[x - 1].NumberOfAtributes() << '\n'; //i,A,?
        }
        else if (el3.liczba != 0 && el2 == 'S') {
            String result = blok->tabSekcji[x - 1].JSelektor(el3.liczba);
            if(result.GetSize()>0)
                std::cout << a << " == " << result << '\n'; //i,S,j
        }
        else if (el2 == 'D') {
            DeleteFunctions(blok, el3, a, x);
        }
        else if(el2 == 'A') {
            String result = blok->tabSekcji[x - 1].WartoscArt(el3.napis);
            if (result.GetSize() > 0)
                std::cout << a << " == " << result << '\n'; //i,A,n
        }
    }
    else if (el2 == 'A' || el2 == 'S') {
        std::cout << a << " == ";
        int result = 0;
        int zajete = blok->zajete;
        while (true) {
            while (zajete > 0) {
                if(el2 == 'A')result += blok->tabSekcji[zajete - 1].IsAtr(el1.napis); //n,A,?
                else result += blok->tabSekcji[zajete - 1].IsSel(el1.napis); //n,S,?
                zajete--;
            }
            
            if (blok->prev != nullptr) {
                blok = blok->prev;
                zajete = blok->zajete;
            }
            else break;
        }
        std::cout << result << '\n';
    }
    else if (el2 == 'E') {
        Efunction(blok, el1, el3, a);
    }    
}

void addCss(struct Block* curBlok, String& a,String& atrname, char b, cssElement& currentEl, atrElement& currentAteEl) {
    if (currentEl == selektor) {
        if (b == '{') {
            currentEl = atrybut;
            a.DeleteLast();
            if (int(a.GetLast(1)) == 32) a.DeleteLast();
            curBlok->tabSekcji[curBlok->zajete].AddSelektor(a);
            a.Zeroj();
        }
        else if (b == ',') {
            a.DeleteLast();
            curBlok->tabSekcji[curBlok->zajete].AddSelektor(a);
            a.Zeroj();
        }
    }
    else if (currentEl == atrybut) {
        if (b == ':') {
            currentAteEl = watrosc;
            a.DeleteLast();
            curBlok->tabSekcji[curBlok->zajete].AddAtrybutNazwa(a);
            atrname = a;
            a.Zeroj();
        }
        else if (b == ';') {
            currentAteEl = nazwa;
            a.DeleteLast();
            curBlok->tabSekcji[curBlok->zajete].AddAtrybutWartosc(a, atrname);
            a.Zeroj();
        }
        else if (b == '}') {
            if (a.GetSize() > 1) {
                a.DeleteLast();
                curBlok->tabSekcji[curBlok->zajete].AddAtrybutWartosc(a, atrname);
            }
            currentAteEl = nazwa;
            currentEl = selektor;
            curBlok->zajete++;
            a.Zeroj();
        }
    }
}

int main()
{
    mode currentMode = css;
    cssElement currentEl = selektor;
    atrElement currentAteEl = nazwa;
    comandElement comandEl = first;
    ElemKomend el1;
    ElemKomend el3;
    char el2 = '\0';
    char b;
    String a;
    String atrname;
    struct Block* curBlok = new struct Block();

    while (std::cin.get(b)) {
        if (isspace(b) == 0 || b == ' ' && a.GetSize() != 0 && 
            (currentAteEl == watrosc || currentMode == comand || (currentEl == selektor && currentMode == css)))
            a.AddChar(b);
        
        if (currentMode == css) {
            if (a == "????") {
                currentMode = comand;
                a.Zeroj();
                continue;
            }

            if (curBlok->zajete >= curBlok->t) {
                curBlok->next = new Block();
                struct Block* tempBlok = curBlok;
                curBlok = curBlok->next;
                curBlok->prev = tempBlok;
            }

            addCss(curBlok, a, atrname, b, currentEl, currentAteEl);
        }
        else if (currentMode == comand) {
            if (a == "****") {
                currentMode = css;
                a.Zeroj();
                resetElement(&el1);
                continue;
            }
            
            if (comandEl == first && b != ENTER) {
                if (int(b) > 47 && int(b) < 58 && el1.napis.GetSize()<1) {
                    el1.liczba *= 10;
                    el1.liczba += b - '0';
                }
                else if (b == ',') comandEl = second;
                else if (b == '?') {
                    el1.litera = b;
                    comandEl = third;
                }
                else if (isspace(b) == 0 || (int(b) == 32 && a.GetSize()>0)) el1.napis.AddChar(b);
            }
            else if (comandEl == second) {
                if (b == ',') comandEl = third;
                else el2 = b;
            }
            else if (comandEl == third) {
                if (int(b) > 47 && int(b) < 58 && el1.napis.GetSize() < 1) {
                    el3.liczba *= 10;
                    el3.liczba += b - '0';
                }
                else if (b == '?' || b == '*') el3.litera = b;
                else if(isspace(b) == 0) el3.napis.AddChar(b);

                if (b == ENTER && a.GetSize() > 0) {
                    komendy(curBlok, el1, el2, el3, a);
                    
                    a.Zeroj();
                    resetElement(&el1);
                    resetElement(&el3);
                    el2 = '\0';
                    comandEl = first;
                }
            }           
        }
    }
    if (std::cin.eof()) {
        komendy(curBlok, el1, el2, el3, a);
    }
    return 0;
}
