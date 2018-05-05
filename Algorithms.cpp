//Ahmed Eltoukhy
//Project 2

#include<iostream>
using namespace std;
#include <functional> //for std::hash
#include <string>


//---------------------------------------------Quick Sort--------------------------------------
void swap(int* a, int* b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

int partition (int arr[], int low, int high)
{
	int pivot = arr[high];    // pivot
	int i = (low - 1);  // Index of smaller element

	for (int j = low; j <= high- 1; j++)
	{
		// If current element is smaller than or
		// equal to pivot
		if (arr[j] <= pivot)
		{
			i++;    // increment index of smaller element
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}

void quickSort(int arr[], int low, int high)
{
	if (low < high)
	{
		int pi = partition(arr, low, high);
		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}

//----------------------------------------Binary Search------------------------------
int binarySearch(int arr[], int l, int r, int x)
{
	if (r >= l)
	{
		int mid = l + (r - l)/2;

		// If the element is present at the middle 
		// itself
		if (arr[mid] == x)  
			return mid;

		// If element is smaller than mid, then 
		// it can only be present in left subarray
		if (arr[mid] > x) 
			return binarySearch(arr, l, mid-1, x);

		// Else the element can only be present
		// in right subarray
		return binarySearch(arr, mid+1, r, x);
	}

	// We reach here when element is not 
	// present in array
	return -1;
}
//----------------------------------------Merge Sort-----------------------------------------


void merge(int arr[], int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 =  r - m;

	int* L=new int [n1];
	int* R=new int [n2];


	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1+ j];


	i = 0; 
	j = 0; 
	k = l; 
	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	/* Copy the remaining elements of L[], if there
	are any */
	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}

	/* Copy the remaining elements of R[], if there
	are any */
	while (j < n2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}
}

/* l is for left index and r is right index of the
sub-array of arr to be sorted */
void mergeSort(int arr[], int l, int r)
{
	if (l < r)
	{
		// Same as (l+r)/2, but avoids overflow for
		// large l and h
		int m = l+(r-l)/2;

		// Sort first and second halves
		mergeSort(arr, l, m);
		mergeSort(arr, m+1, r);

		merge(arr, l, m, r);
	}
}


//-----------------------------------------Hashing-------------------------------


void Hashed(string str){

	std::hash<std::string> hasher;
	auto hashed = hasher(str); //returns std::size_t
	std::cout << hashed << '\n'; //outputs 2146989006636459346 on my machine


}

void printArray(int A[], int size)
{
	int i;
	for (i=0; i < size; i++)
		printf("%d ", A[i]);
	printf("\n");
}


void main(){


	int arr[] = {12, 11, 13, 5, 6, 7};
	int arr_size = sizeof(arr)/sizeof(arr[0]);

	printf("Given array is \n");
	printArray(arr, arr_size);

	mergeSort(arr, 0, arr_size - 1);

	printf("\nSorted array is \n");
	printArray(arr, arr_size);

	int arr1[] = {2, 3, 4, 10, 40};
	int n1 = sizeof(arr1)/ sizeof(arr1[0]);
	int x = 10;
	int result = binarySearch(arr1, 0, n1-1, x);
	(result == -1)? printf("Element is not present"
		" in array")
		: printf("Element is present at "
		"index %d", result);

	int arr3[] = {10, 7, 8, 9, 1, 5};
	int n2 = sizeof(arr3)/sizeof(arr3[0]);
	quickSort(arr3, 0, n2-1);
	printf("Sorted array: n");
	printArray(arr3, n2);

	string ABC;
	cout<<"Enter String to test Hashing "<<endl;
	cin>>ABC;
	Hashed(ABC);
	system("pause");


}


