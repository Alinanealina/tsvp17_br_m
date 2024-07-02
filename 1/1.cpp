#include <iostream>
using namespace std;
const int n = 6;
struct sk { int s1; int s2; int s3; int s4; } S[n][n];
typedef struct st { char ch[100]; struct st* next; } spis;
spis* head;
void res(sk s)
{
	spis* p, * q, * h;
	if (s.s2 - s.s1 > 0)
	{
		for (p = head; atoi(p->ch) != s.s1 && p != NULL; p = p->next);
		q = new spis;
		strcpy_s(q->ch, "(");
		if (p != head)
		{
			for (h = head; h->next != p && h != NULL; h = h->next);
			q->next = p;
			h->next = q;
		}
		else
		{
			q->next = head;
			head = q;
		}

		for (p = head; atoi(p->ch) != s.s2 && p != NULL; p = p->next);
		q = new spis;
		q->next = p->next;
		strcpy_s(q->ch, ")");
		p->next = q;
		res(S[s.s1][s.s2]);
	}
	if (s.s4 - s.s3 > 0)
	{
		for (p = head; atoi(p->next->ch) != s.s3 && p != NULL; p = p->next);
		q = new spis;
		q->next = p->next;
		strcpy_s(q->ch, "(");
		p->next = q;

		for (p = head; atoi(p->ch) != s.s4 && p != NULL; p = p->next);
		q = new spis;
		q->next = p->next;
		strcpy_s(q->ch, ")");
		p->next = q;
		res(S[s.s3][s.s4]);
	}
	/*for (p = head; p != NULL; p = p->next)
		cout << " " << p->ch;
	cout << endl;*/
}

int main()
{
	setlocale(LC_ALL, "Russian");
	st* p, * q;
	int i, j, k, t, r[n] = {
		//10, 20, 50, 1, 100
		//10, 20, 5, 4, 30, 6
		100, 10, 20, 150, 3, 90
	}, f[n][n] = { 0 };
	for (t = 1; t < n - 1; t++)
	{
		for (k = 1; k < n - t; k++)
		{
			for (j = k; j < k + t; j++)
			{
				if ((f[k][k + t] > f[k][j] + f[j + 1][k + t] + r[k - 1] * r[j] * r[k + t]) || (j == k))
				{
					f[k][k + t] = f[k][j] + f[j + 1][k + t] + r[k - 1] * r[j] * r[k + t];
					S[k][k + t].s1 = k;
					S[k][k + t].s2 = j;
					S[k][k + t].s3 = j + 1;
					S[k][k + t].s4 = k + t;
				}
			}
		}
	}
	for (i = 1; i < n; i++)
	{
		for (j = 1; j < n; j++)
			cout << " " << f[i][j] << "\t";
		cout << endl;
	}
	cout << endl;

	for (i = 1; i < n; i++)
	{
		for (j = 1; j < n; j++)
			cout << " (" << S[i][j].s1 << ", " << S[i][j].s2 << ")(" << S[i][j].s3 << ", " << S[i][j].s4 << ") ";
		cout << endl;
	}
	cout << endl;



	head = new spis;
	_itoa_s(1, head->ch, 10);
	head->next = NULL;
	for (i = 2, p = head; i < n; i++, p = p->next)
	{
		q = new spis;
		q->next = p->next;
		_itoa_s(i, q->ch, 10);
		p->next = q;
	}

	res(S[1][n - 1]);
	for (p = head; p != NULL; p = p->next)
		cout << " " << p->ch;
	cout << endl;

	for (q = p = head; p != NULL;)
	{
		p = q->next;
		delete q;
		q = p;
	}
	head = NULL;
	return 0;
}