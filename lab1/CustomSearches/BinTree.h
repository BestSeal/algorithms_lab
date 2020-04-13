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
		int GetValue() const;

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

		//Поиск с возвращением корня
		Node* Searh(const int value) const;

		//Задаёт корневой элемент
		void SetRoot(Node* root);

		//Уменьшить или увеличить кол-во элементов дерева
		void IncNumOfElements();
		void DecNumOfElements();

		int Half(int min, int max);

	public:

		BinTree(int* values, const int length, const bool sorted);

		//Возвращает количество элементов
		int GetNumOfElements() const;

		//Добавляет элемент
		void AddElement(const int value);

		//Возвращает true, если элемент был успешно удален и false, если элемент не существует
		bool DeleteElement(const int value);

		//Возвращает true, если элемент был успешно найден и false, если элемент не существует
		bool IsContaining(const int value) const;

		Node* GetRoot() const;

		//Прямой вывод дерева
		void PreorderTreePrint(const Node* node) const;

		//Центрированный вывод дерева
		void InorderTreePrint(const Node* node) const;
	};
}
