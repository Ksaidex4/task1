// ConsoleApplication5.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
// для использования класса stack
#include  <stack>
// для использования функции max
#include <algorithm>  

using std::cin;  using std::cout; using std::max;

struct point // точка на мини карте
{
	int x, y; // координаты точки на мини карте
};

struct miniMapPart // прямоугольный участвок мини карты
{
	int mapArea; // площадь участка мини карты
	point TopLeftCorner, BottomLeftCorner; // левый верхний угол и нижний правый угол участка мини карты
};

//Статический массив для проверки алгоритма
char a[5][6] =
{
{0,0,1,0,1,0},
{1,0,1,0,1,0},
{1,1,1,0,0,0},
{1,1,1,0,0,0},
{1,1,1,1,1,1}
};

//дополнительные динамики
char d[6] = { -1,-1,-1,-1,-1,-1 };
char d2[6] = { 0, 0, 0, 0, 0, 0 };
char d1[6] = { 0, 0, 0, 0, 0, 0 };

int main()
{
	int n = 5, m = 6; // высота и ширина матрицы
	miniMapPart answer; //результат, включающий координаты участка мини карты и его площадь
	int height; // высота участка мини карты
	int width; // высота участка мини карты

	// обнулим все значения в ответе
	answer.mapArea = 0;
	answer.TopLeftCorner.x = 0;
	answer.TopLeftCorner.y = 0;
	answer.BottomLeftCorner.x = 0;
	answer.BottomLeftCorner.y = 0;

	std::stack<int> st; //создание стека

	// цикл по строкам исходного массива
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
			if (a[i][j] == 1)
				d[j] = i;
		while (!st.empty()) st.pop();
		for (int j = 0; j < m; ++j)
		{
			while (!st.empty() && d[st.top()] <= d[j])
			{
				st.pop();
			}
			if (st.empty())
				d1[j] = -1;
			else d1[j] = st.top();
			st.push(j);
		}
		while (!st.empty()) st.pop();
		for (int j = m - 1; j >= 0; --j)
		{
			while (!st.empty() && d[st.top()] <= d[j])  st.pop();
			if (st.empty())
				d2[j] = m;
			else d2[j] = st.top();
			st.push(j);
		}
		for (int j = 0; j < m; ++j)
		{
			height = i - d[j];
			width = (d2[j] - d1[j] - 1);

			// если текущее значение площади меньше нового, то обновить текущее новым значением
			if (answer.mapArea < (height * width)) 
			{
				answer.mapArea = (height * width);
				answer.TopLeftCorner.x = d1[j]+1;
				answer.TopLeftCorner.y = d[j]+1;	
				answer.BottomLeftCorner.x = d2[j] - 1;
				answer.BottomLeftCorner.y = i;
			}
		}

	}
	//вывод ответа на консоль
	printf("Area=%d, TopLeftCorner(X=%d,Y=%d), BottomLeftCorner(X=%d,Y=%d)", answer.mapArea, answer.TopLeftCorner.x, answer.TopLeftCorner.y, answer.BottomLeftCorner.x, answer.BottomLeftCorner.y);
}

