#include "BinTree.h"
#include "CustomSorts.cpp"

bintree::Node::Node(const int value, bintree::Node* parent = nullptr, bintree::Node* left = nullptr, bintree::Node* right = nullptr) {
	this->value = value;
	this->parent = parent;
	this->left = left;
	this->right = right;
}

int bintree::Node::GetValue() {
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

void bintree::Node::SetRight(bintree::Node* Right) {
	this->right = right;
}

void bintree::Node::SetParent(bintree::Node* parent) {
	this->parent = parent;
}


bintree::BinTree::BinTree(int* values = nullptr, const int length = 0) {

	std::cout << "Construction start\n";
	this->numOfElements = 0;

	if (values != nullptr and length > 0) {
		//Сортируем заданный массив для удобства 
		customsorts::ShellSort(values, length);
		//Вносим левую половину массива в левое поддерево
		for (int i = length / 2; i >= 0; --i) {
			this->AddElement(values[i]);
		}
		//Вносим правую половину массива в правое поддерево
		for (int i = length / 2 + 1; i < length; ++i) {
			this->AddElement(values[i]);
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

void bintree::BinTree::IncNumOfElements() {
	this->numOfElements += 1;
}

void bintree::BinTree::DecNumOfElements() {
	if (this->GetNumOfElements() > 0)
		this->numOfElements += 1;
}

void bintree::BinTree::AddElement(const int value) {
	std::cout << "Adding\n";
	//Создаём новый узел, если нет узлов в дереве, то делаем его корнем, иначе в цикле добавляем в дерево
	Node* newNode = new Node(value);
	if (this->GetNumOfElements() == 0) {
		this->IncNumOfElements();
		this->SetRoot(newNode);
	}
	else {
		//Инициализируем первый узел-родитель - корень
		Node* parentNode = this->root;
		while (parentNode != nullptr) {
			//Если значение меньше, то ищем в левом поддереве
			if (value < parentNode->GetValue()) {
				//Если нет левого узла, то ставим на это место новый узел
				if (parentNode->GetLeft() == nullptr) {
					this->IncNumOfElements();
					parentNode->SetLeft(newNode);
					newNode->SetParent(parentNode);
					parentNode = nullptr;
				}
				else {
					//Иначе меняем родителя и проверяем для него
					parentNode = parentNode->GetLeft();
				}
			}
			//Если значение больше, то ищем в правом поддереве
			else if (value > parentNode->GetValue()) {
				//Если нет правого узла, то ставим на это место новый узел
				if (parentNode->GetRight() == nullptr) {
					this->IncNumOfElements();
					parentNode->SetRight(newNode);
					newNode->SetParent(parentNode);
					parentNode = nullptr;
				}
				else {
					//Иначе меняем родителя и проверяем для него
					parentNode = parentNode->GetRight();
				}
			}
		}
	}
}


