#ifndef LISTA_H
#define LISTA_H

template <typename Tip>
class Lista {
  struct Cvor {
     Tip element;
     Cvor *prethodni, *sljedeci;
     Cvor(Tip element, Cvor *prethodni = nullptr, Cvor *sljedeci = nullptr)
     :element(element),prethodni(prethodni), sljedeci(sljedeci) {}
  };

  int broj_elemenata;
  Cvor *glava, *rep;

  void init();

  public:

  class Const_Iterator {
    protected:
    Cvor *pok;
    public:
    Const_Iterator(Cvor *cvor = nullptr):pok(cvor) {}
    Tip operator*() { return pok->element; }
    Const_Iterator operator++() { pok = pok->sljedeci; return *this; }
    Const_Iterator operator++(int) { Const_Iterator za_vracanje(*this); pok = pok->sljedeci; return za_vracanje; }
    Const_Iterator operator--() { pok = pok->prethodni; return *this; }
    Const_Iterator operator--(int) { Const_Iterator za_vracanje(*this); pok = pok->prethodni; return za_vracanje; }
    bool friend operator==(Const_Iterator it1, Const_Iterator it2) { return it1.pok == it2.pok; }
    bool friend operator!=(Const_Iterator it1, Const_Iterator it2) { return !(it1==it2); }
    friend class Lista<Tip>;

  };

  class Iterator : public Const_Iterator {
    public:
    Iterator(Cvor *cvor = nullptr) { this->pok = cvor; }
    Tip& operator*() { return this->pok->element; }
    Iterator operator++() { this->pok = this->pok->sljedeci; return *this; }
    Iterator operator++(int) { Iterator za_vracanje(*this); this->pok = this->pok->sljedeci; return za_vracanje; }
    Iterator operator--() { this->pok = this->pok->prethodni; return *this; }
    Iterator operator--(int) { Iterator za_vracanje(*this); this->pok = this->pok->prethodni; return za_vracanje; }
  };

  class Reverse_Iterator {
    Cvor* pok;
    public:
    Reverse_Iterator(Cvor *cvor = nullptr):pok(cvor) {}
    Tip operator*() { return pok->element; }
    Reverse_Iterator operator--() { pok = pok->sljedeci; return *this; }
    Reverse_Iterator operator--(int) { Reverse_Iterator za_vracanje(*this); pok = pok->sljedeci; return za_vracanje; }
    Reverse_Iterator operator++() { pok = pok->prethodni; return *this; }
    Reverse_Iterator operator++(int) { Reverse_Iterator za_vracanje(*this); pok = pok->prethodni; return za_vracanje; }
    bool friend operator==(Reverse_Iterator it1, Reverse_Iterator it2) { return it1.pok == it2.pok; }
    bool friend operator!=(Reverse_Iterator it1, Reverse_Iterator it2) { return !(it1==it2); }
    friend class Lista<Tip>;
  };

  Lista() { init(); }
  Lista(int n, Tip vrijednost) { init(); while(n-- > 0) Push_Back(vrijednost); }
  Lista(const Lista<Tip> &kopija);
  Lista<Tip>& operator=(const Lista<Tip> &rhs);
  ~Lista() { Clear(); delete glava; delete rep; }
  Lista(Lista<Tip> &&kopija);
  Lista<Tip>& operator=(Lista<Tip> &&rhs);

  Const_Iterator Begin() const { return glava->sljedeci; }
  Const_Iterator End() const { return rep; }
  Iterator Begin() { return glava->sljedeci; }
  Iterator End() { return rep; }
  Reverse_Iterator RBegin() {return rep->prethodni;}
  Reverse_Iterator REnd() {return glava;}

  Iterator Insert(Iterator pozicija, const Tip vrijednost);
  void Push_Back(const Tip vrijednost) { Insert(End(),vrijednost); }
  void Push_Front(const Tip vrijednost) { Insert(Begin(),vrijednost); }

  Iterator Erase(Iterator pozicija);
  void Pop_Back() { Erase(--End()); }
  void PopFront() { Erase(Begin()); }

  bool Empty() const { return broj_elemenata == 0; }
  void Clear() { while(!Empty()) PopFront(); }
  Lista<Tip>& operator+=(const Lista<Tip> &l) {*this = *this + l; return *this;}
  Lista<Tip>& operator+=(Lista<Tip> &&rhs) {rep->prethodni->slijedeci = rhs.glava->slijedeci; rep = rhs.rep; broj_elemenata += rhs.broj_elemenata;
  rhs.glava = nullptr; rhs.rep = nullptr; rhs.broj_elemenata = 0; return *this;}
  template <typename tip>
  friend Lista<tip>& operator+(Lista<tip> &l1, const Lista<tip> &l2);
};

#include "lista.cpp"


#endif // LISTA_H
