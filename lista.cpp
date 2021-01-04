#ifndef LISTA_CPP
#define LISTA_CPP

#include "lista.h"

template <typename Tip>
void Lista<Tip>::init() {
  glava = new Cvor(Tip());
  rep = new Cvor(Tip(),glava);
  glava->sljedeci = rep;
  broj_elemenata = 0;
}

template <typename Tip>
typename Lista<Tip>::Iterator Lista<Tip>::Insert(Iterator it, Tip vrijednost) {
  it.pok->prethodni->sljedeci = new Cvor(vrijednost, it.pok->prethodni, it.pok);
  it.pok->prethodni = it.pok->prethodni->sljedeci;
  broj_elemenata++;
  return Iterator(it.pok->prethodni);
}

template <typename Tip>
typename Lista<Tip>::Iterator Lista<Tip>::Erase(Iterator it) {
  it.pok->prethodni->sljedeci = it.pok->sljedeci;
  it.pok->sljedeci->prethodni = it.pok->prethodni;
  Iterator za_vracanje(it.pok->sljedeci);
  delete it.pok;
  broj_elemenata--;
  return za_vracanje;
}

template <typename Tip>
Lista<Tip>::Lista(const Lista<Tip> &kopija) {
  init();
  for(auto it = kopija.Begin();it!=kopija.End();it++)
    Push_Back(*it);
}

template <typename Tip>
Lista<Tip>::Lista(Lista<Tip> &&kopija):glava(kopija.glava),rep(kopija.rep),
                                    broj_elemenata(kopija.broj_elemenata){
  kopija.broj_elemenata = 0;
  kopija.glava = nullptr;
  kopija.rep = nullptr;
}

template <typename Tip>
Lista<Tip>& Lista<Tip>::operator=(const Lista<Tip> &rhs) {
  if(this == &rhs)
    return *this;

  Clear();
  for(auto it = rhs.Begin();it!=rhs.End();it++)
    Push_Back(*it);
  return *this;
}

template <typename Tip>
Lista<Tip>& Lista<Tip>::operator=(Lista<Tip> &&rhs) {
  std::swap(glava,rhs.glava);
  std::swap(rep,rhs.rep);
  broj_elemenata = rhs.broj_elemenata;
  return *this;
}

template <typename tip>
Lista<tip>& operator+(Lista<tip> &l1, const Lista<tip> &l2) {
    for(auto it(l2.Begin()); it != l2.End(); it++)
        l1.Push_Back(*it);
    return l1;
}

#endif // LISTA_CPP
