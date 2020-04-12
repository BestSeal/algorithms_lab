#ifndef BINTREEE_H_INCLUDED
#define BINTREEE_H_INCLUDED
namespace bintree {
	//��� ������������ ������ �.�. � ������� ���� ���������, ��� ����������� ���������������� ������
	class BinTree {

		int numOfElements;
		//Element* root;

	public:

		BinTree();
		int getNumOfElements();
		//���������� true, ���� ������� ��� ������� �������� � false �����
		bool addElement(int value);
		//���������� true, ���� ������� ��� ������� ������ � false �����
		bool deleteElement(int value);
		//���������� true, ���� ������� ��� ������� ������ � false �����
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
