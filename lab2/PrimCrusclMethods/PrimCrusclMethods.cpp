#include <iostream>
#include <vector>
#include <algorithm>
//Григорьев И.А. ПИН-24, построение остовного дерева методами Крускала и Прима
//Реализации графа, рёбер и узлов и простых функций для работы с ними
//Возможна нехватка комментариев, готов ответить не вопросы по реализации. Почта: docucraft@yandex.ru
class Edge
{
    int length;
    int vertexes[2];

public:
    Edge (int V1, int len, int V2)
    {
        length = len;
        vertexes[0] = V1;
        vertexes[1] = V2;
    }
    int ConnectedTo(int num)
    {
        if (vertexes[0] == num)
            return vertexes[1];
        if (vertexes[1] == num)
            return vertexes[0];
        return 0;
    }

    int GetLength()
    {
        return length;
    }

    std::vector<int> GetVertexesNums()
    {
        return std::vector<int>{vertexes[0], vertexes[1]};
    }

    void Print()
    {
        std::cout << "\n" <<vertexes[0] << "-" << length << "-" << vertexes[1] << "\n";
    }
};

class Vertex
{
    int number;
    std::vector<Edge*> edges;

public:
    Vertex(int num)
    {
        number = num;
    }

    bool HasEdge(Edge* edge)
    {
        for (auto i : edges)
        {
            if (i == edge)
            {
                return true;
            }
        }
        return false;
    }

    void AddEdge(Edge* edge)
    {
        if (!this->HasEdge(edge))
        {
            edges.push_back(edge);
        }
    }

    std::vector<int> ConnectedVertexes()
    {
        std::vector<int> out;
        for (auto i : edges)
        {
            int temp = i->ConnectedTo(number);
            if (temp)
                out.push_back(temp);
        }

        return out;
    }

    int GetVertexNum()
    {
        return number;
    }
};

class Graph
{
    std::vector<Vertex*> vertexes;
    std::vector<Edge*> edges;


public:
    bool HasVertex(int num)
    {
        if (vertexes.size() == 0)
            return false;
        for (auto i : vertexes)
        {
            if (i->GetVertexNum() == num)
                return true;
        }
        return false;
    }

    void AddVertex(int num)
    {
        if (!this->HasVertex(num))
            vertexes.push_back(new Vertex(num));
    }

    bool  ConnectVertexes( int num1, int length ,int num2)
    {
        if (!(HasVertex(num1) || HasVertex(num2)))
        {
            return 1;
        }

        edges.push_back(new Edge(num1, length, num2));

        return 0;
    }

    void Print()
    {
        for (auto i : edges)
        {
            i->Print();
        }
    }

    void Sort()
    {
        std::sort(edges.begin(), edges.end(), [](Edge* e1, Edge* e2) {return e1->GetLength() < e2->GetLength(); });
    }

    int NumOfEdges()
    {
        return edges.size();
    }

    int NumOfVertexes()
    {
        return vertexes.size();
    }
    std::vector<int> GetVertexes()
    {
        std::vector<int> out;
        for (auto i : vertexes)
            out.push_back(i->GetVertexNum());
        return out;
    }

    Graph* Kruskal()
    {
        //Создаём начально мн-во вершин
        std::vector<std::vector<int>> outVertexes;
        std::vector<Edge*> outEdges;
        //Вычисляем условие окончания алгоритма
        int cicleNum = edges.size() - vertexes.size() + 1;
        //Сортируем рёбра по убыванию
        this->Sort();
        for (std::size_t i = 0; i < vertexes.size(); ++i)
        {
            outVertexes.push_back({ int(i) + 1 });
        }

        //Идём по рёбрам и проверяем их на принадлежность мн-вам и объединяем мн-ва или исключаем рёбра 
        for (auto i : edges)
        {

            int v1 = i->GetVertexesNums()[0];
            int v2 = i->GetVertexesNums()[1];
            for (auto j : outVertexes)
            {
                bool contain1 = std::count(j.begin(), j.end(), v1);
                bool contain2 = std::count(j.begin(), j.end(), v2);
                //исключаем ребро
                if (contain1 && contain2)
                {

                    break;
                }
                //Проверяем, что мн-во содержит одну из вершине и не содержит другую
                if (contain1) 
                {

                    for (auto k : outVertexes)
                    {
                        if (std::count(k.begin(), k.end(), v2))
                        {

                            for (auto h : k)
                            {
                                j.push_back(h);
                            }

                            k.clear();
                            outEdges.push_back(i);
                            break;
                        }
                    }
                    break;
                }

                if (contain2)
                {
                    for (auto k : outVertexes)
                    {
                        if (std::count(k.begin(), k.end(), v1))
                        {
                            for (auto h : k)
                            {
                                j.push_back(h);
                            }
                            k.clear();
                            outEdges.push_back(i);
                            break;
                        }
                    }
                    break;
                }
            }
            if (edges.size() - outEdges.size() == cicleNum)
               break;
        }
        Graph* out = new Graph();
        for (auto i : outEdges)
        {
            std::vector<int> tempVert = i->GetVertexesNums();
            out->AddVertex(tempVert[0]);
            out->AddVertex(tempVert[1]);
            if (out->ConnectVertexes(tempVert[0], i->GetLength(), tempVert[1]))
                exit;
        }
        return out;
    }
};

int main()
{
    Graph* wow = new Graph();
    int vertexes;
    int edges;
    std::cout << "Enter number of vertexes and edges:\n";
    std::cin >> vertexes >> edges;
    for (int i = 1; i <= vertexes; ++i)
    {
        wow->AddVertex(i);
    }
    std::cout << "Enter edges and vertexes they are connected to:\n";
    for (int i = 0; i < edges; ++i)
    {
        int v1, len, v2;
        std::cin >> v1 >> len >>v2;
        wow->ConnectVertexes( v1, len, v2);
    }


    Graph* ostTree = wow->Kruskal();


    ostTree->Print();

}
