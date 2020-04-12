#pragma once

namespace bintree {
	class Node

	{
		int value;
		Node* left;
		Node* right;
		Node* parent;

	public:

		Node(const int value, Node* parent, Node* left, Node* right);

		//Возвращает значение элемента
		int GetValue();

		//Возвращают соответсвующие указатели на элементы
		Node* GetLeft() const;
		Node* GetRight() const;
		Node* GetParent() const;

		//Задают соответсвующие указатели на элементы
		void SetLeft(Node* left);
		void SetRight(Node* right);
		void SetParent(Node* parent);

	};

	class BinTree {

		int numOfElements;
		Node* root;

	public:

		BinTree(int* values, const int length);

		//Возвращает количество элементов
		int GetNumOfElements() const;
		//Уменьшить или увеличить кол-во элементов дерева
		void IncNumOfElements();
		void DecNumOfElements();

		//Добавляет элемент
		void AddElement(const int value);

		//Возвращает true, если элемент был успешно удален и false, если элемент не существует
		bool DeleteElement(const int value);

		//Возвращает true, если элемент был успешно найден и false, если элемент не существует
		bool IsContaining(const int value) const;

		//Задаёт корневой элемент
		void SetRoot(Node* root);

	};

	
}

