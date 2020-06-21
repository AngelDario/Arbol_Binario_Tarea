#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

struct Cgreater {
	inline bool operator()(int a, int b) {
		return a > b;
	}
};

struct Cless {
	inline bool operator()(int a, int b) {
		return a < b;
	}
};

template <class T>
class STACK {
public:
	int size, top;
	T* PILA;
	
	STACK(int _size) : size(_size) {
		top = -1;
		PILA = new T[size];
	}

	~STACK() {
		delete[] PILA;
	}

	void p_push(T x) {
		if (top < (size - 1)) {
			++top;
			PILA[top] = x;
			return;
		}
		cout << "Stack overflow: El stack es de " << size << " elementos";
		exit(0);
	}

	void p_pop() {
		if (top > -1) {
			--top;
		}
	}

	T TOP() {
		return PILA[top];
	}
};

template <class T>
struct NODE {
	T val;
	NODE<T>* nodes[2];

	NODE(T _val) : val(_val) {
		nodes[0] = nodes[1] = 0;
	}
};

template<class l>
struct nodeX {
	int estado;
	NODE<l>* x;

	nodeX() {}

	nodeX(NODE<l>* n) {
		estado = 0;
		x = n;
	}

	void update(NODE<l>* newNODE) {
		estado = 0;
		x = newNODE;
	}

	void cambio() {
		++estado;
	}

	void print() {
		cout << x->val;
	}
};


template <class T, class O>
class CTREE {
public:
	NODE<T>* m_root;
	O order;

	CTREE() {
		m_root = 0;
	}

	void destruir(NODE<T>* k) {
		if (!k) return;
		destruir(k->nodes[0]);
		destruir(k->nodes[1]);
		delete k;
	}

	bool find(T x, NODE<T>**& p) {
		p = &m_root;
		while (*p && (*p)->val != x) {
			p = &((*p)->nodes[order(x, (*p)->val)]);
		}
		return *p != 0;
	}

	bool insert(T x) {
		NODE<T>** p;
		if (find(x, p)) {
			return 0;
		}
		*p = new NODE<T>(x);
		return 1;
	}

	bool REP(NODE<T>**& p) {
		srand(time(NULL));
		bool random = rand() % 2;
		if ((*p)->nodes[random]) {
			p = &((*p)->nodes[random]);
			while ((*p)->nodes[!random]) {
				p = &((*p)->nodes[!random]);
			}
			return 1;
		}
		p = &((*p)->nodes[!random]);
		while ((*p)->nodes[random]) {
			p = &((*p)->nodes[random]);
		}
		return 1;
	}

	bool remove(T x) {
		NODE<T>** p;
		if (!find(x, p)) {
			return 0;
		}
		if ((*p)->nodes[0] && (*p)->nodes[1]) {
			NODE<T>** q;
			REP(q);
			(*p)->val = (*q)->val;
			p = q;
		}
		NODE<T>* temp = *p;
		*p = (*p)->nodes[!(*p)->nodes[0]];
		delete temp;
		return 1;
	}

	void inorder() {
		STACK<nodeX<T>> lista(100);
		NODE<T>* k = m_root;
		nodeX<T> i(k);

		lista.p_push(i);

		while (lista.top != -1) {

			if (lista.TOP().estado == 0) {
				lista.PILA[lista.top].estado++;
				i.update(lista.TOP().x->nodes[0]);
				lista.p_push(i);
				if (!(lista.TOP().x)) {
					lista.p_pop();
				}
			}else if (lista.TOP().estado == 1) {
				lista.PILA[lista.top].estado++;
				cout << lista.TOP().x->val;
				i.update(lista.TOP().x->nodes[1]);
				lista.p_push(i);
				if (!(lista.TOP().x)) {
					lista.p_pop();
				}
			}else if (lista.TOP().estado == 2) {
				lista.p_pop();
			}
			
		}
	}

	void preorder() {
		STACK<nodeX<T>> lista(100);
		NODE<T>* k = m_root;
		nodeX<T> i(k);

		lista.p_push(i);

		while (lista.top != -1) {

			if (lista.TOP().estado == 0) {
				lista.PILA[lista.top].estado++;
				cout << lista.TOP().x->val;
				i.update(lista.TOP().x->nodes[0]);
				lista.p_push(i);
				if (!(lista.TOP().x)) {
					lista.p_pop();
				}
			}
			else if (lista.TOP().estado == 1) {
				lista.PILA[lista.top].estado++;
				i.update(lista.TOP().x->nodes[1]);
				lista.p_push(i);
				if (!(lista.TOP().x)) {
					lista.p_pop();
				}
			}
			else if (lista.TOP().estado == 2) {
				lista.p_pop();
			}

		}
	}

	void postorder() {
		STACK<nodeX<T>> lista(100);
		NODE<T>* k = m_root;
		nodeX<T> i(k);

		lista.p_push(i);

		while (lista.top != -1) {

			if (lista.TOP().estado == 0) {
				lista.PILA[lista.top].estado++;
				i.update(lista.TOP().x->nodes[0]);
				lista.p_push(i);
				if (!(lista.TOP().x)) {
					lista.p_pop();
				}
			}
			else if (lista.TOP().estado == 1) {
				lista.PILA[lista.top].estado++;
				i.update(lista.TOP().x->nodes[1]);
				lista.p_push(i);
				if (!(lista.TOP().x)) {
					lista.p_pop();
				}
			}
			else if (lista.TOP().estado == 2) {
				cout << lista.TOP().x->val;
				lista.p_pop();
			}

		}
	}

	void reverse() {
		STACK<nodeX<T>> lista(100);
		NODE<T>* k = m_root;
		nodeX<T> i(k);

		lista.p_push(i);

		while (lista.top != -1) {

			if (lista.TOP().estado == 0) {
				lista.PILA[lista.top].estado++;
				i.update(lista.TOP().x->nodes[1]);
				lista.p_push(i);
				if (!(lista.TOP().x)) {
					lista.p_pop();
				}
			}
			else if (lista.TOP().estado == 1) {
				lista.PILA[lista.top].estado++;
				cout << lista.TOP().x->val;
				i.update(lista.TOP().x->nodes[0]);
				lista.p_push(i);
				if (!(lista.TOP().x)) {
					lista.p_pop();
				}
			}
			else if (lista.TOP().estado == 2) {
				lista.p_pop();
			}

		}
	}

};

template<class T, class O>
void print(int& x, CTREE<T, O> arbol) {

	switch (x) {
	case 1:
		cout << "Inorder: \n";
		arbol.inorder();
		cout << endl;
		break;
	case 2:
		cout << "Preorder: \n";
		arbol.preorder();
		cout << endl;
		break;
	case 3:
		cout << "Postorder: \n";
		arbol.postorder();
		cout << endl;
		break;
	case 4:
		cout << "Reverse: \n";
		arbol.reverse();
		cout << endl;
		break;
	}

}

template<class T, class O>
void menu(CTREE<T, O>& arbol) {
	int x;
	int orden;

	cout << "Escoge que el tipo de recorrido: " << endl;
	cout << "1. Inorder \n";
	cout << "2. Preorder \n";
	cout << "3. Postorder \n";
	cout << "4. Reverse \n";
	cin >> orden;

	while (1) {
		system("cls");
		print<T, O>(orden, arbol);
		cout << "Que quieres haccer?" << endl;
		cout << "1. Add \n";
		cout << "2. Del \n";
		cout << "3. Cambiar tipo de recorrido\n";
		cout << "4. Salir del Programa\n";
		cin >> x;

		switch (x) {
		case 1:
			T intTemp;
			cout << "Ingresa elemento para insertar: ";
			cin >> intTemp;
			arbol.insert(intTemp);
			continue;
		case 2:
			T intTemp2;
			cout << "Ingresa elemento para remover: ";
			cin >> intTemp2;
			arbol.remove(intTemp2);
			continue;
		case 3:
			cout << "Escoge que el tipo de recorrido: " << endl;
			cout << "1. Inorder \n";
			cout << "2. Preorder \n";
			cout << "3. Postorder \n";
			cout << "4. Reverse \n";
			cin >> orden;
			continue;
		case 4:
			arbol.destruir(arbol.m_root);
			cout << "Arbol Destruido.";
			exit(0);
		}
	}
}

int main()
{
	CTREE<int, Cgreater> arbol;

	menu<int, Cgreater>(arbol);
	return 0;
}