#include <iostream>
#include <chrono>

const int SIZE_BIG = 300;
const int SIZE = 15;
const int COUNT = 10;
const int OPTIM_SIZE = 10;

void quickSort(int* array, const int& begin, const int& end);
int partition(int* array, const int& begin, const int& end);
void insertionSort(int* array, const int& begin, const int& end);
bool isSorted(int* array, const int& size);
void randomArr(int* array, const int& size);
void worstArr(int* array, const int& size);
void printArr(const int* array, const int& size);
void checkBest(int* array, const int& size);
void checkMedium(int* array, const int& size);
void checkWorst(int* array, const int& size);
void checkTwo(int* array, const int& size);
long long checkTime(int* array, const int& size);

int main() {

	try {
		int arr[SIZE];
		int good_arr[SIZE] = { 1, 3, 2, 5, 7, 6, 4, 9, 11, 10, 13, 15, 14, 12, 8 };
		char buf = 0;
		while (buf != '5') {
			std::cout << "\n1. Check Best.\n2. Check Worst.\n3. Check Medium.\n4. Check Medium and Worst for big array.\n5. Exit.\n";
			std::cout << "Enter num that you whant check: ";
			std::cin >> buf;
			switch (buf) {
			case '1': checkBest(good_arr, SIZE); continue;
			case '2': checkWorst(arr, SIZE); continue;
			case '3': checkMedium(arr, SIZE); continue;
			case '4': checkTwo(arr, SIZE_BIG); continue;
			case '5': exit(0); break;
			default: break;
			}
		}
	}
	catch (std::exception& e) {
		std::cerr << "Error: " << e.what() << '\n';
		exit(-1);
	}
	return 0;
}
void quickSort(int* array, const int& begin, const int& end) {
	if (begin >= end) {
		return;
	}
	int sup = partition(array, begin, end);
	if (end - begin <= OPTIM_SIZE) {
		insertionSort(array, begin, end);
		return;
	}
	else {
		quickSort(array, begin, sup - 1);
		quickSort(array, sup + 1, end);
	}
}
int partition(int* array, const int& begin, const int& end) {
	int sup = array[end];
	int index = begin;
	for (int i = begin; i < end; i++) {
		if (array[i] >= sup) {
			std::swap(array[i], array[index]);
			index++;
		}
	}
	std::swap(array[index], array[end]);
	return index;
}
void insertionSort(int* array, const int& begin, const int& end) {
	int temp;
	for (int i = begin + 1; i <= end; i++) {
		temp = array[i];
		for (int j = i - 1; j >= 0; j--) {
			if (array[j] >= temp) {
				break;
			}
			std::swap(array[j], array[j + 1]);
		}
	}
}
bool isSorted(int* array, const int& size) {
	for (int i = 0; i < size-1; i++) {
		if (array[i] < array[i+1]) {
			return false;
		}
	}
	return true;
}
void randomArr(int* array, const int& size) {
	for (int i = 0; i < size; i++) {
		array[i] = rand() % 1000;
	}
}
void checkBest(int* array, const int& size) {
	std::cout << "Best version\n";
	printArr(array, size);
	std::cout << "Best time: " << checkTime(array, size) << " ncs\n";
	printArr(array, size);
}
void checkMedium(int* array, const int& size) {
	std::cout << "Medium version\n";
	randomArr(array, size);
	printArr(array, size);
	std::cout << "Medium time: " << checkTime(array, size) << " ncs\n";
	printArr(array, size);
}
void checkWorst(int* array, const int& size) {
	std::cout << "Worst version\n";
	worstArr(array, size);
	printArr(array, size);
	std::cout << "Worst time: " << checkTime(array, size) << " ncs\n";
	printArr(array, size);
}
void checkTwo(int* array, const int& size) {
	worstArr(array, size);
	std::cout << "Worst time: " << checkTime(array, size) << " ncs\n";
	double ans = 0;
	for (int i = 0; i < COUNT; i++) {
		randomArr(array, size);
		ans += checkTime(array, size);
	}
	std::cout << "Medium time: " << ans/COUNT << " ncs\n";
}
long long checkTime(int* array, const int& size) {
	auto begin = std::chrono::high_resolution_clock::now();
	quickSort(array, 0, size - 1);
	auto end = std::chrono::high_resolution_clock::now();
	if (!isSorted(array, size)) {
		throw std::exception("array wasn't sorted");
	}
	std::chrono::nanoseconds time_took = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
	return time_took.count();
}
void printArr(const int* array, const int& size) {
	for (int i = 0; i < size; i++) {
		std::cout << array[i] << " ";
	}
	std::cout << '\n';
}
void worstArr(int* array, const int& size) {
	int j = size;
	for (int i = 0; i < size; i++) {
		array[i] = j--;
	}
}