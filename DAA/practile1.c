#include <stdio.h>

int binarySearch(int arr[], int low, int high, int x) {
    if (high >= low) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == x)
            return mid;
        else if (arr[mid] > x)
            return binarySearch(arr, low, mid - 1, x);
        else
            return binarySearch(arr, mid + 1, high, x);
    }

    return -1; // Element not found
}

int main() {
    int array[] = {3, 4, 5, 6, 7, 8, 9};
    int x = 4;
    int result = binarySearch(array, 0, sizeof(array) / sizeof(array[0]) - 1, x);

    if (result != -1)
        printf("Element is present at index %d\n", result);
    else
        printf("Not found\n");

    return 0;
}
