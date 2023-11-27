#include <iostream>


template <class T>
class ArbolBusqueda;


template <class T>
class Nodo {
private:
    T elem;
    Nodo<T>* der;
    Nodo<T>* izq;
public:
    Nodo() :izq(nullptr), der(nullptr) {};
    friend class ArbolBusqueda<T>;
};

template <class T>
class ArbolBusqueda {
private:
    Nodo<T>* arbol;
    void insertaR(Nodo<T>* &arbolr, T elem);
    Nodo<T>* localizar(Nodo<T>* arbolr, T elem);
    Nodo<T>* menorr(Nodo<T>* arbolr);
    Nodo<T>* mayorr(Nodo<T>* arbolr);
    void recorrido_preorder_r(Nodo<T>* arbolr);
    void recorrido_inorder_r(Nodo<T>* arbolr);
    void recorrido_postorder_r(Nodo<T>* arbolr);
    void elimina_r(Nodo<T>* arbolr, Nodo<T>* pos);
    int altura_r(Nodo<T>* arbolr);
public:
    ArbolBusqueda() :arbol(nullptr) {};
    bool vacia() const;
    Nodo<T>* localiza(T elem);
    void inserta(T elemento);
    Nodo<T>* menor();
    Nodo<T>* mayor();
    bool es_hoja(Nodo<T>* arbolr);
    void recorrido_preorder();
    void recorrido_inorder();
    void recorrido_postorder();
    void elimina(Nodo<T>* pos);
    int altura();
    int fact_eq(Nodo<T>* arbolr);
    void balanceo();
    void rot_sim_der(Nodo<T>* arbolr);
    void rot_sim_izq(Nodo<T>* arbolr);
    void rot_dbl_der(Nodo<T>* arbolr);
    void rot_dbl_izq(Nodo<T>* arbolr);
};

template <class T>
bool ArbolBusqueda<T>::vacia() const {
    if (arbol == nullptr) {
        return true;
    }

    return false;
}

template <class T>
void ArbolBusqueda<T>::inserta(T elem) {
    insertaR(arbol, elem);
}

template <class T>
void ArbolBusqueda<T>::insertaR(Nodo<T>* &arbolr, T elem) {
    if (arbolr == nullptr) {
        Nodo<T>* aux = new Nodo<T>;
        aux->elem = elem;
        arbolr = aux;
    }
    else {
        if (elem < arbolr->elem) {
            insertaR(arbolr->izq, elem);
        }
        else {
            insertaR(arbolr->der, elem);
        }
    }
}

template <class T>
Nodo<T>* ArbolBusqueda<T>::localiza(T elem) {
    return localizar(arbol, elem);
}

template <class T>
Nodo<T>* ArbolBusqueda<T>::localizar(Nodo<T>* arbolr, T elem){
    if (arbolr == nullptr) {
        return nullptr;
    }
    else if (elem == arbolr->elem) {
        return arbolr;
    }
    else if (elem < arbolr->elem) {
        return localizar(arbolr->izq, elem);
    }
    else {
        return localizar(arbolr->der, elem);
    }
}

template <class T>
Nodo<T>* ArbolBusqueda<T>::menor() {
    return menorr(arbol);
}

template <class T>
Nodo<T>* ArbolBusqueda<T>::mayor() {
    return mayorr(arbol);
}

template <class T>
Nodo<T>* ArbolBusqueda<T>::menorr(Nodo<T>* arbolr) {
    if (arbolr == nullptr) {
        return nullptr;
    }
    else {
        if (arbolr->izq == nullptr) {
            return arbolr;
        }
        else {
            return menorr(arbolr->izq);
        }
    }
}

template <class T>
Nodo<T>* ArbolBusqueda<T>::mayorr(Nodo<T>* arbolr){
    if (arbolr == nullptr) {
        return nullptr;
    }
    else {
        if (arbolr->der == nullptr) {
            return arbolr;
        }
        else {
            return mayorr(arbolr->der);
        }
    }
}

template <class T>
bool ArbolBusqueda<T>::es_hoja(Nodo<T>* arbolr) {
    if (arbolr == nullptr) {
        return false;
    }

    if (arbolr->izq == nullptr && arbolr->der == nullptr) {
        return true;
    }
    else {
        return false;
    }
}

template <class T>
void ArbolBusqueda<T>::recorrido_preorder() {
    recorrido_preorder_r(arbol);
}

template <class T>
void ArbolBusqueda<T>::recorrido_preorder_r(Nodo<T>* arbolr) {
    if (arbolr == nullptr) {
        return;
    }

    std::cout << arbolr->elem << std::endl;

    recorrido_preorder_r(arbolr->izq);
    recorrido_preorder_r(arbolr->der);
}

template <class T>
void ArbolBusqueda<T>::recorrido_inorder() {
    recorrido_inorder_r(arbol);
}

template <class T>
void ArbolBusqueda<T>::recorrido_inorder_r(Nodo<T>* arbolr) {
    if (arbolr == nullptr) {
        return;
    }

    recorrido_inorder_r(arbolr->izq);
    std::cout << arbolr->elem << std::endl;
    recorrido_inorder_r(arbolr->der);
}

template <class T>
void ArbolBusqueda<T>::recorrido_postorder() {
    recorrido_postorder_r(arbol);
}

template <class T>
void ArbolBusqueda<T>::recorrido_postorder_r(Nodo<T>* arbolr) {
    if (arbolr == nullptr) {
        return;
    }

    recorrido_postorder_r(arbolr->izq);
    recorrido_postorder_r(arbolr->der);
    std::cout << arbolr->elem << std::endl;
}

template <class T>
void ArbolBusqueda<T>::elimina(Nodo<T>* pos) {
    elimina_r(arbol, pos);
}

template <class T>
void ArbolBusqueda<T>::elimina_r(Nodo<T>* arbolr, Nodo<T>* pos) {
    if (arbolr == nullptr || pos == nullptr) {
        std::cerr << "Error: Árbol o posición son nulos." << std::endl;
        return;
    }

    if (es_hoja(pos)) {
        delete pos;
        pos = nullptr;
    }
    else {
        Nodo<T>* pos_reemplazo = nullptr;

        if (arbolr->izq != nullptr) {
            pos_reemplazo = mayorr(arbolr->izq);
        }
        else {
            pos_reemplazo = menorr(arbolr->der);
        }

        pos->elem = pos_reemplazo->elem;

        elimina_r(arbolr, pos_reemplazo);
    }
}

template <class T>
int ArbolBusqueda<T>::altura() {
    return altura_r(arbol);
}

template <class T>
int ArbolBusqueda<T>::altura_r(Nodo<T>* arbolr) {
    if (arbolr == nullptr) {
        return 0;
    }
    else {
        int alt_izq = altura_r(arbolr->izq);
        int alt_der = altura_r(arbolr->der);

        if (alt_izq > alt_der) {
            return alt_izq + 1;
        }
        else {
            return alt_der + 1;
        }
    }
}

template <class T>
int ArbolBusqueda<T>::fact_eq(Nodo<T>* arbolr) {
    if (arbolr == nullptr) {
        return 0;
    }
    else {
        return altura_r(arbolr->der) - altura_r(arbolr->izq);
    }
}

template <class T>
void ArbolBusqueda<T>::balanceo() {
    if (fact_eq(arbol) < -1) {
        if (fact_eq(arbol->izq) == -1) {
            rot_sim_der(arbol);
        }
        else {
            rot_dbl_der(arbol);
        }

        return;
    }

    if (fact_eq(arbol) > 1) {
        if (fact_eq(arbol->izq) == 1) {
            rot_sim_izq(arbol);
        }
        else {
            rot_dbl_izq(arbol);
        }

        return;
    }
}

template <class T>
void ArbolBusqueda<T>::rot_sim_der(Nodo<T>* arbolr) {
    Nodo<T>* aux1 = arbolr->izq;
    Nodo<T>* aux2 = arbolr->izq->der;

    arbolr->izq = aux2;
    aux1->der = arbolr;
    arbolr = aux1;
}

template <class T>
void ArbolBusqueda<T>::rot_sim_izq(Nodo<T>* arbolr) {
    Nodo<T>* aux1 = arbolr->der;
    Nodo<T>* aux2 = arbolr->der->izq;

    arbolr->der = aux2;
    aux1->izq = arbolr;
    arbolr = aux1;
}

template <class T>
void ArbolBusqueda<T>::rot_dbl_der(Nodo<T>* arbolr) {
    Nodo<T>* aux1 = arbolr->izq;
    Nodo<T>* aux2 = aux1->der;
    Nodo<T>* aux3 = aux2->izq;
    Nodo<T>* aux4 = aux2->der;

    arbolr->izq = aux4;
    aux1->der = aux3;
    aux2->izq = aux1;
    arbolr = aux2;
}

template <class T>
void ArbolBusqueda<T>::rot_dbl_izq(Nodo<T>* arbolr) {
    Nodo<T>* aux1 = arbolr->der;
    Nodo<T>* aux2 = aux1->izq;
    Nodo<T>* aux3 = aux2->der;
    Nodo<T>* aux4 = aux2->izq;

    arbolr->der = aux4;
    aux1->izq = aux3;
    aux2->der = aux1;
    arbolr = aux2;
}

int main()
{
    ArbolBusqueda<int> miarbol;

    miarbol.inserta(5);
    miarbol.balanceo();
    miarbol.inserta(3);
    miarbol.balanceo();
    miarbol.inserta(9);
    miarbol.balanceo();
    miarbol.inserta(4);
    miarbol.balanceo();

    std::cout << miarbol.localiza(3) << std::endl;
    std::cout << miarbol.localiza(4) << std::endl;
    std::cout << miarbol.localiza(9) << std::endl;

    std::cout << miarbol.menor() << std::endl;
    std::cout << miarbol.mayor() << std::endl;

    miarbol.elimina(miarbol.localiza(3));
    
    std::cout << miarbol.localiza(3) << std::endl;
    std::cout << miarbol.menor() << std::endl;

    return 0;
}
