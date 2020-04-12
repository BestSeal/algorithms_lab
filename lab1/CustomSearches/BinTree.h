#ifndef BINTREEE_H_INCLUDED
#define BINTREEE_H_INCLUDED
namespace bintree {
	//нет балансировки дерева т.к. в задании было оговорено, что исключается сбалансированное дерево
	class BinTree {

		int numOfElements;
		//Element* root;

	public:

		BinTree();
		int getNumOfElements();
		//возвращает true, если элемент был успешно добавлен и false иначе
		bool addElement(int value);
		//возвращает true, если элемент был успешно удален и false иначе
		bool deleteElement(int value);
		//возвращает true, если элемент был успешно найден и false иначе
		bool isElementHere(int value);

	};

	class Element: public BinTree
	{
		int value;
		Element* left;
		Element* right;
		Element* parent;

	public:

		Element(int value);

	};
}
#endif
