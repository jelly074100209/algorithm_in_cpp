#ifndef SORTING_H
#define SORTING_H

template<class T>
void insertionsort(T data[], const int n)
{
	for (int i = 1, j; i < n; i++)
	{
		T tmp = data[i];
		for (j = i; j > 0 && tmp < data[j - 1]; j--)
		{
			data[j] = data[j - 1];
		}
		data[j] = tmp;
	}
}

template<class T>
void selectionsort(T data[], const int n)
{
	for (int i = 0, least, j; i < n - 1; i++)
	{
		for (j = i + 1, least = i; j < n; j++)
		{
			if (data[j] < data[least])
				least = j;
		}
		swap(data[least], data[i]);
	}
}

template<class T>
void bubblesort(T data[], const int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = n - 1; j > i; j--)
		{
			if (data[j] < data[j - 1])
			{
				swap(data[j], data[j - 1]);
			}
		}
	}
}

template<class T>
void combsort(T data[], const int n)
{
	int step = n, j, k;
	while ((step = int(step / 1.3)) > 1)
	{
		for (j = n - 1; j >= step; j--)
		{
			k = j - step;
			if (data[j] < data[k])
			{
				swap(data[j], data[k]);
			}
		}
	}
	bool again = true;
	for (int i = 0; i < n - 1 && again; i++)
	{
		for (j = n - 1, again = false; j > i; j--)
		{
			if (data[j] < data[j - 1])
			{
				swap(data[j], data[j - 1]);
				again = true;
			}
		}
	}
}

template<class T>
void Shellsort(T data[], const int n)
{
	register int i, j, hCnt, h;
	int increments[20], k;
	for (h = 1, i = 0; h < n; i++)
	{
		increments[i] = h;
		h = 3 * h + 1;
	}
	for (i--; i >= 0; i--)
	{
		h = increments[i];
		for (hCnt = h; hCnt < 2 * h; hCnt++)
		{
			for (j = hCnt; j < n;)
			{
				T tmp = data[j];
				k = j;
				while (k - h >= 0 && tmp < data[k - h])
				{
					data[k] = data[k - h];
					k -= h;
				}
				data[k] = tmp;
				j += h;
			}
		}
	}
}

template<class T>
void moveDown(T data[], int first, int last)
{
	int largest = 2 * first + 1;
	while (largest <= last)
	{
		if (largest < last && data[largest] < data[largest + 1])
		{
			largest++;
		}
		if (data[first] < data[largest])
		{
			swap(data[first], data[largest]);
			first = largest;
			largest = 2 * first + 1;
		}
		else
		{
			largest = last + 1;
		}
	}
}

template<class T>
void heapsort(T data[], const int n)
{
	int i;
	for (i = n / 2 - 1; i >= 0; i--)
	{
		moveDown(data, i, n - 1);
	}
	for (i = n - 1; i >= 1; i--)
	{
		swap(data[0], data[i]);
		moveDown(data, 0, i - 1);
	}
}

template<class T>
void quicksort(T data[], int first, int last)
{
	int lower = first + 1, upper = last;
	swap(data[first], data[(first + last) / 2]);
	T bound = data[first];
	while (lower <= upper)
	{
		while (data[lower] < bound)
			lower++;
		while (bound < data[upper])
			upper--;
		if (lower < upper)
			swap(data[lower++], data[upper--]);
		else
			lower++;
	}
	swap(data[upper], data[first]);
	if (first < upper - 1)
		quicksort(data, first, upper - 1);
	if (upper + 1 < last)
		quicksort(data, upper + 1, last);
}

template<class T>
void quicksort(T data[], const int n)
{
	int i, max;
	if (n < 2)
		return;
	for (i = 1, max = 0; i < n; i++)
	{
		if (data[max] < data[i])
			max = i;
	}
	swap(data[n - 1], data[max]);
	quicksort(data, 0, n - 2);
}

template<class T>
void display(T data[], const int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << data[i] << " ";
	}
	cout << endl;
}

#endif