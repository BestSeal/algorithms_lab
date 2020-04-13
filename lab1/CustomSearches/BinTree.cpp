#include <iostream>
#include "BinTree.h"

//Просто сеттеры/геттеры
int bintree::Node::GetValue() const{
	return this->value;
}

bintree::Node* bintree::Node::GetLeft() const {
	return this->left;
}

bintree::Node* bintree::Node::GetRight() const {
	return this->right;
}

bintree::Node* bintree::Node::GetParent() const {
	return this->parent;
}

void bintree::Node::SetLeft(bintree::Node* left) {
	this->left = left;
}

void bintree::Node::SetRight(bintree::Node* right) {
	this->right = right;
}

void bintree::Node::SetParent(bintree::Node* parent) {
	this->parent = parent;
}


bintree::Node::Node(const int value, bintree::Node* parent = nullptr, bintree::Node* left = nullptr, bintree::Node* right = nullptr) {
	this->value = value;
	this->SetParent(parent);
	this->SetLeft(left);
	this->SetRight(right);
}

bintree::BinTree::BinTree(int* values = nullptr, const int length = 0, const bool sorted = true) {
	//sorted - ввод отсортированного массива, иначе ожидается preorder-style дерево
	std::cout << "Construction start\n";
	this->numOfElements = 0;
	if (values != nullptr and length > 0) {
		if (sorted) {
			for (int i = length / 2; i >= 0; --i) {
				this->AddElement(values[i]);
			}
			for (int i = length / 2 + 1; i < length; ++i) {
				this->AddElement(values[i]);
			}		
		}
		else {
			for (int i = 0; i < length; ++i) {
				this->AddElement(values[i]);
			}
		}

	}
	else {
		//Если не задана начальная последовательность, то зануляем корень
		this->SetRoot(nullptr);
	}
}

int bintree::BinTree::GetNumOfElements() const {
	return this->numOfElements;
}

void bintree::BinTree::SetRoot(Node* root) {
	this->root = root;
}

bintree::Node* bintree::BinTree::GetRoot() const {
	return this->root;
}

void bintree::BinTree::IncNumOfElements() {
	this->numOfElements += 1;
}

void bintree::BinTree::DecNumOfElements() {
	if (this->GetNumOfElements() > 0)
		this->numOfElements += 1;
}

bintree::Node* bintree::BinTree::Searh(const int value) const {
	Node* parentNode = this->GetRoot();
	while (parentNode != nullptr) {
		if (parentNode->GetValue() == value) {
			return parentNode;
		}
		else if (value < parentNode->GetValue()) {
			parentNode = parentNode->GetLeft();
		}
		else
			parentNode = parentNode->GetRight();
	}
	return nullptr;
}

bool bintree::BinTree::IsContaining(const int value) const {
	if (this->Searh(value) != nullptr) {
		return true;
	}
	else {
		return false;
	}
}

void bintree::BinTree::AddElement(const int value) {
	//Создаём новый узел, если нет узлов в дереве, то делаем его корнем, иначе в цикле добавляем в дерево
	Node* newNode = new Node(value);
	if (this->GetNumOfElements() == 0) {
		std::cout << "Setting a root as " << value << "\n";
		this->IncNumOfElements();
		this->SetRoot(newNode);
	}
	else {
		std::cout << "Adding ";
		//Инициализируем первый узел-родитель - корень
		Node* parentNode = this->root;
		while (parentNode != nullptr) {
			//Если значение меньше, то ищем в левом поддереве
			if (value < parentNode->GetValue()) {
				//Если нет левого узла, то ставим на это место новый узел
				if (parentNode->GetLeft() == nullptr) {
					std::cout << parentNode->GetValue() << " <- " << " " << value << "\n";
					this->IncNumOfElements();
					parentNode->SetLeft(newNode);
					newNode->SetParent(parentNode);
					break;
				}
				else {
					//Иначе меняем родителя и проверяем для него
					parentNode = parentNode->GetLeft();
					continue;
				}
			//Если значение больше, то ищем в правом поддереве
			}else if (value > parentNode->GetValue()) {
				//Если нет правого узла, то ставим на это место новый узел
				if (parentNode->GetRight() == nullptr) {
					std::cout << parentNode->GetValue() << " -> " << " " << value << "\n";
					this->IncNumOfElements();
					parentNode->SetRight(newNode);
					newNode->SetParent(parentNode);
					break;
				}
				else {
					//Иначе меняем родителя и проверяем для него
					parentNode = parentNode->GetRight();
					continue;
				}
			
			}
			if (value == parentNode->GetValue()) {
				std::cout << "Encountered existing value!\n";
				break;
			}
		}
	}
}

bool bintree::BinTree::DeleteElement(const int value) {
	//Находим указатель на удаляемый элемент
	Node* toDelete = this->Searh(value);
	if (toDelete != nullptr){
		// 1й случай: у узла нет дочерних узлов
		if (toDelete->GetLeft() == nullptr and toDelete == nullptr) {
			//Если узел является левым узлом у родителя, заменяем его на nullptr
			if (toDelete == toDelete->GetParent()->GetLeft()) {
				toDelete->GetParent()->SetLeft(nullptr);
				delete toDelete;
				return true;
			}
			else {
				//Если узел является правым узлом у родителя, заменяем его на nullptr
				toDelete->GetParent()->SetRight(nullptr);
				delete toDelete;
				return true;
			}
		}
		// 2й случай: у узла один дочерний узел
		if (toDelete->GetLeft() == nullptr or toDelete->GetRight() == nullptr) {
			//Если есть левый дочерний элемент
			if (toDelete->GetLeft() != nullptr) {
				//Если узел является левым узлом у родителя, заменяем его на левый дочерний
				if (toDelete == toDelete->GetParent()->GetLeft()) {
					toDelete->GetParent()->SetLeft(toDelete->GetLeft());
					delete toDelete;
					return true;
				}
				else {
					//Если узел является левым узлом у родителя, заменяем его на правый дочерний
					toDelete->GetParent()->SetRight(toDelete->GetLeft());
					delete toDelete;
					return true;
				}
			}
			else{
				//Если есть правый дочерний элемент
				//Если узел является правым узлом у родителя, заменяем его на левый дочерний
				if (toDelete == toDelete->GetParent()->GetLeft()) {
					toDelete->GetParent()->SetLeft(toDelete->GetRight());
					delete toDelete;
					return true;
				}
				else {
					//Если узел является правым узлом у родителя, заменяем его на правый дочерний
					toDelete->GetParent()->SetRight(toDelete->GetRight());
					delete toDelete;
					return true;
				}

			}
		}
		// 3й случай: у узла два дочерних элемента
		if (toDelete->GetLeft() != nullptr and toDelete->GetRight() != nullptr) {		
			Node* replNode = toDelete->GetRight()->GetLeft();
			//Если у правого дочернего есть левый дочерний, то заменяем на него
			if (toDelete->GetRight()->GetLeft() != nullptr) {
				toDelete->GetRight()->SetLeft(nullptr);
				replNode->SetParent(toDelete->GetParent());
				replNode->SetLeft(toDelete->GetLeft());
				replNode->SetRight(toDelete->GetRight());
				delete toDelete;
				return true;
			}
			else{
				Node* replNode = toDelete->GetRight();
				replNode->SetParent(toDelete->GetParent());
				replNode->SetLeft(toDelete->GetLeft());
				delete toDelete;
				return true;
			}

		}
	}
	else {
		return false;
	}
}
void bintree::BinTree::PreorderTreePrint(const Node* node) const {
	if (node == nullptr) {
		return;
	}
	std::cout << node->GetValue() << " ";
	//Вывод левого поддерева
	this->PreorderTreePrint(node->GetLeft());
	//Вывод праваого поддерева
	this->PreorderTreePrint(node->GetRight());
}

void bintree::BinTree::InorderTreePrint(const Node* node) const {
	if (node == nullptr) {
		return;
	}
	//Вывод левого поддерева
	this->InorderTreePrint(node->GetLeft());
	std::cout << node->GetValue() << " ";
	//Вывод праваого поддерева
	this->InorderTreePrint(node->GetRight());

}
