#include<iostream>
#include<algorithm>
#include<queue>

using namespace std;

int convert(string n)//字符串转化成数值
{
	int num = 0;
	for (int i = 0; n[i] != '\0'; i++)num = num * 10 + int(n[i] - '0');
	return num;
}


template<class Type>
class Graph;

template<class T>
class MinHeap
{
	template<class Type>
	friend class Graph;
public:
	MinHeap(int maxheapsize = 10);
	~MinHeap() { delete[]heap; }

	int Size() const { return currentsize; }
	T Max() { if (currentsize) return heap[1]; }

	MinHeap<T>& Insert(const T& x);
	MinHeap<T>& DeleteMin(T &x);

	void Initialize(T x[], int size, int ArraySize);
	void Deactivate();
	void output(T a[], int n);
private:
	int currentsize, maxsize;
	T *heap;
};

template <class T>
void MinHeap<T>::output(T a[], int n)
{
	for (int i = 1; i <= n; i++)
		cout << a[i] << " ";
	cout << endl;
}

template <class T>
MinHeap<T>::MinHeap(int maxheapsize)
{
	maxsize = maxheapsize;
	heap = new T[maxsize + 1];
	currentsize = 0;
}

template<class T>
MinHeap<T>& MinHeap<T>::Insert(const T& x)
{
	if (currentsize == maxsize)
	{
		return *this;
	}
	int i = ++currentsize;
	while (i != 1 && x < heap[i / 2])
	{
		heap[i] = heap[i / 2];
		i /= 2;
	}

	heap[i] = x;
	return *this;
}

template<class T>
MinHeap<T>& MinHeap<T>::DeleteMin(T& x)
{
	if (currentsize == 0)
	{
		cout << "Empty heap!" << endl;
		return *this;
	}

	x = heap[1];

	T y = heap[currentsize--];
	int i = 1, ci = 2;
	while (ci <= currentsize)
	{
		if (ci < currentsize && heap[ci] > heap[ci + 1])
		{
			ci++;
		}

		if (y <= heap[ci])
		{
			break;
		}
		heap[i] = heap[ci];
		i = ci;
		ci *= 2;
	}

	heap[i] = y;
	return *this;
}

template<class T>
void MinHeap<T>::Initialize(T x[], int size, int ArraySize)
{
	delete[]heap;
	heap = x;
	currentsize = size;
	maxsize = ArraySize;

	for (int i = currentsize / 2; i >= 1; i--)
	{
		T y = heap[i];
		int c = 2 * i;
		while (c <= currentsize)
		{
			if (c < currentsize && heap[c] > heap[c + 1])
				c++;
			if (y <= heap[c])
				break;
			heap[c / 2] = heap[c];
			c *= 2;
		}
		heap[c / 2] = y;
	}
}

template<class T>
void MinHeap<T>::Deactivate()
{
	heap = 0;
}


class Flowshop;
class MinHeapNode
{
	friend Flowshop;
public:
	operator int() const{return bb;}
private:
	void Init(int n) 
	{
		x = new int[n];
		for (int i = 0; i < n; i++)
			x[i] = i;
		s = 0;
		f1 = 0;
		f2 = 0;
		sf2 = 0;
		bb = 0;
	}
	void NewNode(MinHeapNode E, int Ef1, int Ef2, int Ebb, int n)
	{
		x = new int[n];
		for (int i = 0; i < n; i++)
			x[i] = E.x[i];
		f1 = Ef1;
		f2 = Ef2;
		sf2 = E.sf2 + f2;
		bb = Ebb;
		s = E.s + 1;
	}
	int s, f1, f2, sf2, bb, *x;
};

class Flowshop
{
	friend void main(void);
public:
	int BBFlow(void);
private:
	int Bound(MinHeapNode, int&, int&, bool**);
	void Sort(void);
	int n, **M, **b, **a, *bestx, bestc;
	bool **y;
};

void Flowshop::Sort()
{
	int *c = new int[n];
	for (int j = 0; j < 2; j++)
	{
		for (int i = 0; i < n; i++)
		{
			b[i][j] = M[i][j];
			c[i] = i;
		}
		for(int i=0;i<n-1;i++)
			for(int k=n-1;k>i;k--)
				if (b[k][j] < b[k - 1][j])
				{
					swap(b[k][j], b[k - 1][j]);
					swap(c[k], c[k - 1]);
				}
		for (int i = 0; i < n; i++)
			a[c[i]][j] = i;
	}
	delete[]c;
}

int Flowshop::Bound(MinHeapNode E, int& f1, int& f2, bool **y)
{
	for (int k = 0; k < n; k++)
		for (int j = 0; j < 2; j++)
			y[k][j] = false;
	for (int k = 0; k <= E.s; k++)
		for (int j = 0; j < 2; j++)
			y[a[E.x[k]][j]][j] = true;
	f1 = E.f1 + M[E.x[E.s]][0];
	f2 = ((f1 > E.f2) ? f1 : E.f2) + M[E.x[E.s]][1];
	int sf2 = E.sf2 + f2;
	int s1 = 0, s2 = 0, k1 = n - E.s, k2 = n - E.s, f3 = f2;
	for(int j=0;j<n;j++)
		if (!y[j][0])
		{
			k1--;
			if (k1 == n - E.s - 1)
				f3 = (f2 > f1 + b[j][0]) ? f2 : f1 + b[j][0];
			s1 += f1 + k1*b[j][0];
		}
	for(int j=0;j<n;j++)
		if (!y[j][1])
		{
			k2--;
			s1 += b[j][1];
			s2 += f3 + k2*b[j][1];
		}
	return sf2 + ((s1 > s2) ? s1 : s2);
}

int Flowshop::BBFlow()
{
	Sort();
	MinHeap<MinHeapNode>H(1000);
	MinHeapNode E;
	E.Init(n);
	while (E.s <= n)
	{
		if (E.s == n)
		{
			if (E.sf2 < bestc)
			{
				bestc = E.sf2;
				for (int i = 0; i < n; i++)
					bestx[i] = E.x[i];
			}
			delete[]E.x;
		}
		else
		{
			for (int i = E.s; i < n; i++)
			{
				swap(E.x[E.s], E.x[i]);
				int f1, f2;
				int bb = Bound(E, f1, f2, y);
				if (bb < bestc)
				{
					MinHeapNode N;
					N.NewNode(E, f1, f2, bb, n);
					H.Insert(N);
				}
				swap(E.x[E.s], E.x[i]);
			}
			delete[]E.x;
		}
		if (H.Size() == 0)
		{
			break;
		}
		H.DeleteMin(E); 
	}
	return bestc;
}