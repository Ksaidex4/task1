// ConsoleApplication5.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

// для использования стандартных функций ввода/вывода
#include <iostream>
// для использования класса stack
#include  <stack>
// для использования функции max
#include <algorithm>  

using std::cin;  using std::cout; using std::max;

// высота и ширина мини карты
const int MinimapHeight = 5;
const int MinimapWidth = 6;

// Статический массив с исходными данными для проверки алгоритма
// Значение 0 означает, что место занято союзными войсками
// Значение 1 означает, что место занято врагом
char MiniMap[MinimapHeight][MinimapWidth] =
{
{0,0,1,0,1,0},
{1,0,1,0,1,0},
{1,1,1,0,0,0},
{1,1,1,0,0,0},
{1,1,1,1,1,1}
};

struct point // точка на мини карте
{
	int x, y; // координаты точки на мини карте
};

struct miniMapPart // прямоугольный участвок мини карты
{
	int mapArea; // площадь участка мини карты
	point TopLeftCorner, BottomLeftCorner; // левый верхний угол и нижний правый угол участка мини карты
};

// процедура поиска максимального прямоугольного участка мини карты состоящего из 0
miniMapPart miniMapPartSearch(int height, int width, char MiniMap[MinimapHeight][MinimapWidth])
{
	//дополнительные динамики
	char  d[6] = { -1,-1,-1,-1,-1,-1 }; // значение -1 указывает, что над текущей строкой нет единиц   
	char d2[6] = { 0, 0, 0, 0, 0, 0 }; // расстояние от текущего нуля до крайнего левого
	char d1[6] = { 0, 0, 0, 0, 0, 0 }; // расстояние от текущего нуля до крайнего правого

	miniMapPart answer; //результат, включающий координаты участка мини карты и его площадь

	// обнулим все значения в ответе
	answer.mapArea = 0;
	answer.TopLeftCorner.x = 0;
	answer.TopLeftCorner.y = 0;
	answer.BottomLeftCorner.x = 0;
	answer.BottomLeftCorner.y = 0;

	std::stack<int> st; //создание стека

	// цикл по строкам исходного массива
	for (int i = 0; i < MinimapHeight; ++i)
	{
		// в d помещается номер строки, в которой находится ближайшая единица сверху
		for (int j = 0; j < MinimapWidth; ++j)
			if (MiniMap[i][j] == 1)
				d[j] = i;
		while (!st.empty()) st.pop();
		for (int j = 0; j < MinimapWidth; ++j)
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
		for (int j = MinimapWidth - 1; j >= 0; --j)
		{
			while (!st.empty() && d[st.top()] <= d[j])  st.pop();
			if (st.empty())
				d2[j] = MinimapWidth;
			else d2[j] = st.top();
			st.push(j);
		}
		for (int j = 0; j < MinimapWidth; ++j)
		{
			int newMinimapHeight; // высота участка мини карты
			int newMinimapWidth; // высота участка мини карты
			newMinimapHeight = i - d[j];
			newMinimapWidth = (d2[j] - d1[j] - 1);

			// если текущее значение площади меньше нового, то обновить текущее новым значением
			if (answer.mapArea < (newMinimapHeight * newMinimapWidth))
			{
				answer.mapArea = (newMinimapHeight * newMinimapWidth);
				answer.TopLeftCorner.x = d1[j] + 1;
				answer.TopLeftCorner.y = d[j] + 1;
				answer.BottomLeftCorner.x = d2[j] - 1;
				answer.BottomLeftCorner.y = i;
			}
		}
	}
	return answer;
}



int main()
{
	miniMapPart answer; //результат, включающий координаты участка мини карты и его площадь
	answer = miniMapPartSearch(MinimapHeight, MinimapHeight, MiniMap); // поиск участка мини карты
	//вывод ответа на консоль
	printf("Max our area=%d, TopLeftCorner(X=%d,Y=%d), BottomLeftCorner(X=%d,Y=%d) \n", answer.mapArea, answer.TopLeftCorner.x, answer.TopLeftCorner.y, answer.BottomLeftCorner.x, answer.BottomLeftCorner.y);
	
	// инвертируем мини карту, чтобы 0 заменить на 1, а 1 на 0 меняем местами врага и союзников
	for (int i = 0; i < MinimapHeight; ++i)
	{
		for (int j = 0; j < MinimapWidth; ++j)	MiniMap[i][j] = !MiniMap[i][j];
	}

	answer = miniMapPartSearch(MinimapHeight, MinimapHeight, MiniMap); // поиск участка мини карты
	//вывод ответа на консоль
	printf("Max enemy Area=%d, TopLeftCorner(X=%d,Y=%d), BottomLeftCorner(X=%d,Y=%d)", answer.mapArea, answer.TopLeftCorner.x, answer.TopLeftCorner.y, answer.BottomLeftCorner.x, answer.BottomLeftCorner.y);


}

