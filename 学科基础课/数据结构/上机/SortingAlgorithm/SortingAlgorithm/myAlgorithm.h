#pragma once
#pragma warning(disable:6031 6385 6386 26451)
#include <vector>
#include <iterator>
#include <functional>
#include <algorithm>
#include <stack>
#include <assert.h>

/*
**
**	infor :SortAlgorithm
**	author: acooz
**	data  : 2019.12.11
**
**/

using namespace std;

//static int IncrementSequenceHibbard[30] = { 30,1,3,7,15,31,63,127,255,511,1023,2047,4095,8191,16383,32767,65535,131071,262143,524287,1048575,2097151,4194303,8388607,16777215,33554431,67108863,134217727,268435455,536870911 };

//���ٷǵݹ��Ż���STLջ���ܲ��ߣ���ʵ��һ��ջ
class myStack
{
public:
	myStack() { data = new int[100](); size = 100; length = 0; }
	bool isEmpty() { return length == 0; }
	bool isFull() { return length == size; }
	
	void push(int elem){
		if (isFull())
			expan();
		data[length++] = elem;
	}
	int  pop(){
		if (isEmpty())
			return -1;
		return data[--length];
	}
	
private:
	int* data;
	int size;
	int length;

	void expan() {
		int* newData = new int[size * 10]();
		for (int i = 0; i < size; i++)
			newData[i] = data[i];
		size = size * 10;
		delete data;
		data = newData;
	}
};


class Solution
{
	//Ϊ�˷��㴫�뺯��ָ�룬����Ա������Ϊstatic//
public:


	static void noSort(int arr[], int length)
	{
		if (length <= 1 || arr == nullptr)
			return;
		//������
		for (int i = 0; i < length; i++)
			heapInsert(arr, i);

		for (int i = 0; i < 100; i++){
			cout << arr[i] << " ";
		}
	}


	static void bubbleSort(int arr[], int length)
	{
		if (length <= 1||arr==nullptr) 
			return;  
		for (int i = 0; i < length; i++) {
			bool flag = false;
			for (int j = 0; j < length - i - 1; j++) {
				if (arr[j] > arr[j+1]) {
					swap(arr, j, j+1);
					flag = true;		//ͨ����־����ѭ������
				}
			}
			if (!flag)
				break;
		}
	}

	static void selectSort(int arr[], int length)
	{
		if (length <= 1 || arr == nullptr)
			return;
		for (int i = 0; i < length - 1; i++){
			int minIndex = i;
			for (int j = i + 1; j < length; j++) {
				if (arr[minIndex] > arr[j])
					minIndex = j;		//�������飬ѡ����С����
			}
			swap(arr, minIndex, i);
		}
	}

	static void insertSort(int arr[], int length)
	{
		if (length <= 1 || arr == nullptr)
			return; 
		for (int i = 1; i < length; i++) {
			int value = arr[i];
			int j = i - 1;
// ���Ҳ����λ��
			for (; j >= 0; j--) {
				if (arr[j] > value)
					arr[j+1] = arr[j]; // �����ƶ� 
				else
					break; 
			}
			arr[j+1] = value; // �������� 
		}
	}

	//����gap��ѡȡ�� ���Ӷ�O(n ^ (1.3��2))
	static void shellSort(int arr[], int length)
	{
		for (int gap = (length >> 1); gap > 0; gap >>= 1) {//xxxtag
			//ħ�Ĳ�������
			for (int i = gap; i < length; i++) {
				for (int j = i; j - gap >= 0 && arr[j - gap] > arr[j]; j -= gap)
					swap(arr, j - gap, j);
			}
		}
	}

	static void mergeSort(int arr[], int length)
	{
		if (arr == nullptr || length < 2)
			return;
		mergeSort(arr, 0, length - 1);
	}

	static void mergeSortN(int arr[], int length)
	{
		if (arr == nullptr || length < 2)
			return;
		mergeSortN(arr, 0, length - 1);
	}

	static void quickSort(int arr[], int length)
	{
		if (length <= 1 || arr == nullptr)
			return;
		quickSort(arr, 0, length - 1);
	}

	static void heapSort(int arr[], int length)
	{
		if (length <= 1 || arr == nullptr)
			return;
		//������
		for (int i = 0; i < length; i++)
			heapInsert(arr, i);
		int size = length;
		while (size > 0) {
			swap(arr, 0, --size);
			heapify(arr, 0, size);
		}
	}

	static void countingSort(int arr[], int length)
	{
		if (length <= 1 || arr == nullptr)
			return;
		int max = arr[0];
		int lastIndex = 0;
		for (int i = 1; i < length; i++)
			max = arr[i] > max ? arr[i] : max;

		int* sortArr = new int[max + 1]();
		for (int j = 0; j < length; j++)
			sortArr[arr[j]]++;
		for (int k = 0; k < max + 1; k++) {
			while (sortArr[k] > 0) {
				arr[lastIndex++] = k;
				sortArr[k]--;
			}
		}
		delete[] sortArr;
	}

	static void bucketSort(int arr[], int length)
	{
		if (length < 2)
			return;
		
		int size=10;		//size Ϊһ��Ͱ�����������ķ�Χ
		//�õ������Сֵ
		int min = arr[0], max = arr[0];
		for (int i = 1; i < length; i++) {
			min = arr[i] < min ? arr[i] : min;
			max = arr[i] > max ? arr[i] : max;
		}

		if (min == max)
			return;

		//����Ͱ
		int bucketSize = (max - min) / size + 1;
		vector<vector<int>> bucket(bucketSize+1);		//����vectorʱֱ�Ӷ�����һ������ֹ���
		int bid = 0;		

		//�������е��� �ӽ�Ͱ��
		for (int i = 0; i < length; i++) {
			bid = getGroupCount(arr[i], bucketSize, min, max);
			bucket[bid].push_back(arr[i]);
		}

		for (int i = 0; i < bucketSize; i++) {
		//��Ͱ�ڽ��в������򡣰������򣬱�֤�ȶ���
			int bucketLenth = int(bucket[i].size());

			if (bucketLenth <= 1)
				break;

			for (int j = 1; j < bucketLenth; j++) {
				int value = bucket[i][j];
				int k = j - 1;
				for (; k >= 0; k--) {
					if (bucket[i][k] > value)
						bucket[i][k + 1] = bucket[i][k];
					else
						break;
				}
				bucket[i][k+1] = value; // ��������
			}
		}

	//������õ�Ͱ�����ݸ��Ƶ�������
		int index = 0;
		for (int i = 0; i < bucketSize+1; i++) {
			for (int j = 0; j < int(bucket[i].size()); j++) {
				arr[index++] = bucket[i][j];
			}
		}

		bucket.~vector();
	}

	static void radixSort(int arr[], int length)
	{
		if (length <= 1 || arr == nullptr)
			return;

		int d = maxbit(arr, length);
		int* tmp = new int[length];
		int* count = new int[10]; //������
		int i, j, k;
		int radix = 1;
		//����d������
		for (i = 1; i <= d; i++) {

			//ÿ�η���ǰ��ռ�����
			for (j = 0; j < 10; j++)
				count[j] = 0; 

			//ͳ��ÿ��Ͱ�еļ�¼��
			for (j = 0; j < length; j++){
				k = (arr[j] / radix) % 10; 
				count[k]++;
			}

			//��tmp�е�λ�����η����ÿ��Ͱ
			for (j = 1; j < 10; j++)
				count[j] = count[j - 1] + count[j]; 

			//������Ͱ�м�¼�����ռ���tmp��
			for (j = length - 1; j >= 0; j--) {
				k = (arr[j] / radix) % 10;
				tmp[count[k] - 1] = arr[j];
				count[k]--;
			}

			//����ʱ��������ݸ��Ƶ�data��
			for (j = 0; j < length; j++) 
				arr[j] = tmp[j];
			radix = radix * 10;
		}

		delete[] tmp;
		delete[] count;
	}

	static void quickSortN(int arr[], int length)
	{
		//STLջ
		if (length <= 1 || arr == nullptr)
			return;
		quickSortN(arr, 0, length - 1);
	}

	static void quickSortNM(int arr[], int length)
	{
		//�Զ���ջ
		if (length <= 1 || arr == nullptr)
			return;
		quickSortNM(arr, 0, length - 1);
	}

private:
	static void swap(int arr[], int a, int b){
		int tmp = arr[a];
		arr[a] = arr[b];
		arr[b] = tmp;
	}

	static void mergeSort(int arr[], int L, int R) {
		if (L == R)
			return;
		int mid = ((L + R) >> 1);
		mergeSort(arr, L, mid);
		mergeSort(arr, mid + 1, R);
		merge(arr, L, mid, R);
	}

	static void mergeSortN(int arr[], int L, int R) 
	{
		if (L == R)
			return;
		int length = R - L + 1;
		int gap = 1, left, mid, right;

		while (gap < length) {
			left = 0;
			while (left + gap < length) {
				mid = left + gap - 1;
				right = mid + gap;
				if (right > length - 1)
					right = length - 1;
				merge(arr, left, mid, right);
				left = right + 1;//��һ�ι鲢ʱ��һ�����е��½� 
			}
			gap *= 2;
		}
	}

	static void merge(int arr[], int L, int M, int R) {
		int* temp = new int[R - L + 1]();
		int i = 0;
		int pFirst = L, pSecond = M + 1;
		while (pFirst <= M && pSecond <= R)
			temp[i++] = arr[pFirst] < arr[pSecond] ? arr[pFirst++] : arr[pSecond++];

		while (pFirst <= M)
			temp[i++] = arr[pFirst++];

		while (pSecond <= R)
			temp[i++] = arr[pSecond++];

		//������arr
		for (int j = 0; j < (R - L + 1); j++)
			arr[L + j] = temp[j];
		delete[] temp;
	}

	static void quickSort(int arr[], int p, int r)
	{
		if (p >= r)
			return;
		//��ÿ��partitionȡ���/��ǰ��������������/��������»��˻�Ϊð�����򣬼����Ӷ�ΪO(n^2)

		if (r - p + 1 < 15){
			int* start = arr + p;
			insertSort(start,r-p+1);
			return;
		}

		int q = partition(arr, p, r);
		quickSort(arr, p, q - 1);
		quickSort(arr, q + 1, r);
	}

	static void quickSortN(int arr[], int left, int right)
	{
		//�ֶ�����ջ���洢ÿ�ηֿ���ŵ���ʼ��
		//ջ�ǿ�ʱѭ����ȡ������ջ
		stack<int> s;
		if (left < right){
			int boundary = partition(arr, left, right);
			//ȷ�����ҷ�������
			if (boundary - 1 > left) {
				s.push(left);
				s.push(boundary - 1);
			}
			if (boundary + 1 < right) {
				s.push(boundary + 1);
				s.push(right);
			}

			while (!s.empty()){
				//�õ�ĳ���������ұ߽� 
				int r = s.top();
				s.pop();
				int l = s.top();
				s.pop();
				boundary = partition(arr, l, r);
				if (boundary - 1 > l) {
					s.push(l);
					s.push(boundary - 1);
				}
				if (boundary + 1 < r) {
					s.push(boundary + 1);
					s.push(r);
				}
			}
		}

	}

	static void quickSortNM(int arr[], int left, int right)
	{
		//�ֶ�����ջ���洢ÿ�ηֿ���ŵ���ʼ��
		//ջ�ǿ�ʱѭ����ȡ������ջ
		myStack s;
		int q = partition(arr, left, right);
		//ȷ�����ҷ�������
		if (q - 1 > left) {
			s.push(left);
			s.push(q - 1);
		}
		if (q + 1 < right) {
			s.push(q + 1);
			s.push(right);
		}
		while (!s.isEmpty()) {
			//�õ�ĳ���������ұ߽� 
			int r = s.pop();
			int l = s.pop();

			if (r - l + 1 < 15){
				insertSort(arr + l, r - l + 1);
			}
			else{
				q = partition(arr, l, r);
				if (q - 1 > l) {
					s.push(l);
					s.push(q - 1);
				}
				if (q + 1 < r) {
					s.push(q + 1);
					s.push(r);
				}
			}
		}
	}

	static void doPivot(int arr[],int left,int right)
	{
	//��������ѡ����ʵ�pivot,�����������������Ҷ�,��ֹ����������˻�
		
		int pivot = right;

		//ÿ��ȡ�м�ֵ
		pivot = left + ((right - left) >> 1);		

		//����ȡ�з���ʵ��
		//int mid = left + ((right - left) >> 1);
		//if (((arr[left] < arr[mid]) && (arr[right] > arr[mid])) || ((arr[left] > arr[mid]) && (arr[right] < arr[mid])))
		//	pivot = mid;
		//else if (((arr[left] < arr[right]) && (arr[mid] > arr[right])) || ((arr[left] > arr[right]) && (arr[mid] < arr[right])))
		//	pivot = right;
		//else
		//	pivot = left;

		//�����
		//int rand1 = rand() % 10000;	int rand2 = rand() % 10000;
		//pivot= ((rand1 * 10000 + rand2) % (right - left) + left);
		 
		swap(arr, pivot, right);
	}

	static int	partition(int arr[], int left, int right)
	{
		doPivot(arr, left, right);
		int i = left;
		for (int j = left; j < right; j++) {
			if (arr[j] < arr[right]) {
				if (j != i)
					swap(arr, i, j);
				i++;
			}
		}
		swap(arr, i, right);
		return i;
	}

	static void heapInsert(int arr[], int index) {
		while (arr[index] > arr[(index - 1)>>1]) {
			swap(arr, index, ((index - 1)>>1));
			index = ((index - 1) >> 1);
		}
	}

	static void heapify(int arr[], int index, int size) {
		int leftChild = (index << 1) + 1;
		while (leftChild < size) {
			int maxChild = leftChild + 1 < size && arr[leftChild + 1] > arr[leftChild] ? leftChild + 1 : leftChild;
			int maxAll = arr[maxChild] > arr[index] ? maxChild : index;
			if (maxAll == index)
				break;
			swap(arr, maxAll, index);
			index = maxAll;
			leftChild = (index << 1) + 1;
		}
	}

	static int	getGroupCount(int value, int bucketSize, int min, int max) {
		float difference = float(max - min);
		float Vdifference = float(value - min);
		int count = int(Vdifference / difference * bucketSize);
		return count;
	}

	static int	maxbit(int arr[], int length) //�����ݵ����λ��
	{
		int maxData = arr[0];
		for (int i = 1; i < length; i++){
			if (arr[i]>maxData)
				maxData = arr[i];
		}

		int num = 1;
		while (maxData >= 10){
			maxData /= 10;
			++num;
		}

		return num;
	}
};