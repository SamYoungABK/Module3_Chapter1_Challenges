#include <chrono>
#include <iostream>
#include <iomanip>
#include <random>
#include <time.h>
#include <vector>
#include "main.h"

using std::cout; using std::endl; using std::fixed;
using std::vector;
using namespace std::chrono;
using std::time;

void TestSort(int size);
void InsertionSort(vector<int>& arr);
void Shuffle(vector<int>& arr);
vector<int> BuildArray(int size);

void TestSort(int size)
{
	vector<int> arr = BuildArray(size);
	auto start = steady_clock::now();
	InsertionSort(arr);
	auto end = steady_clock::now();
	duration<int, std::nano> diff = end - start;
	cout << "Array Size: " << size << endl;
	cout << "Time Taken: " << fixed << diff.count() << " nanoseconds" << endl;
}

void InsertionSort(vector<int> &arr)
{
	vector<int>::iterator i = arr.begin()+1;
	
	while (i != arr.end())
	{
		vector<int>::iterator j = i;
		while (j > arr.begin() && *(j-1) > *j)
		{
			int tmp = *j;
			*j = *(j - 1);
			*(j - 1) = tmp;
			j--;
		}
		i++;
	}
}

void Shuffle(vector<int> &arr)
{
	vector<int> result;
	vector<bool> used = { false };
	int newIndex = 0;

	result.resize(arr.size(), 0);
	used.resize(arr.size(), false);

	for (int i = 0; i < arr.size(); ++i)
	{
		do
		{
			newIndex = rand() % arr.size();
		}
		while (used[newIndex]);

		result[newIndex] = arr[i];
		used[newIndex] = true;
	}

	arr = result;
}

vector<int> BuildArray(int size)
{
	vector<int> result;
	for (int i = 1; i <= size; i++)
		result.push_back(i);

	return result;
}

int main()
{
	srand(time(NULL));
	
	for(int i = 100; i < 10000000; i*=10) TestSort(i);

}