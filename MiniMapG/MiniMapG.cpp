// ConsoleApplication5.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
// для использования класса stack
#include  <stack>
// для использования функции max
#include <algorithm>  

using std::cin;  using std::cout; using std::max;

//Статический массив для проверки алгоритма
char a[5][6] =
{
{0,0,1,0,1,0},
{1,0,1,0,1,0},
{1,1,1,0,1,0},
{1,1,1,0,1,1},
{1,1,1,1,1,1}
};

//дополнительные динамики
char d[6] = { -1,-1,-1,-1,-1,-1 };
char d2[6] = { 0, 0, 0, 0, 0, 0 };
char d1[6] = { 0, 0, 0, 0, 0, 0 };

int main()
{
	int n = 5, m = 6; // высота и ширина матрицы
	int ans = 0; //результат
	std::stack<int> st; //стек
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
			ans = max(ans, (i - d[j]) * (d2[j] - d1[j] - 1));
	}

	cout << ans;
}

