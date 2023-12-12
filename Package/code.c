//PROBLEM STATEMENT:Given n non-negative integers representing an elevation map where the width of each bar is 1
//compute how much water it can trap after raining.

#include <stdio.h>
#include <stdlib.h>

int trap(int* height, int heightSize) {
    if (heightSize <= 2) {
        return 0; // Not enough elements to trap water
    }

    int* leftMax = (int*)malloc(heightSize * sizeof(int));
    int* rightMax = (int*)malloc(heightSize * sizeof(int));

    if (!leftMax || !rightMax) {
        // Memory allocation failed
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    // Initialize leftMax and rightMax arrays
    leftMax[0] = height[0];
    for (int i = 1; i < heightSize; ++i) {
        leftMax[i] = (leftMax[i - 1] > height[i]) ? leftMax[i - 1] : height[i];
    }

    rightMax[heightSize - 1] = height[heightSize - 1];
    for (int i = heightSize - 2; i >= 0; --i) {
        rightMax[i] = (rightMax[i + 1] > height[i]) ? rightMax[i + 1] : height[i];
    }

    int trappedWater = 0;

    // Calculate trapped water at each position
    for (int i = 1; i < heightSize - 1; ++i) {
        int minHeight = (leftMax[i] < rightMax[i]) ? leftMax[i] : rightMax[i];
        trappedWater += (minHeight > height[i]) ? (minHeight - height[i]) : 0;
    }

    // Free allocated memory
    free(leftMax);
    free(rightMax);

    return trappedWater;
}

int main() {
    int size;
    printf("Enter the size of the elevation map: ");
    scanf("%d", &size);

    int* elevationMap = (int*)malloc(size * sizeof(int));
    if (!elevationMap) {
        // Memory allocation failed
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    printf("Enter the elevation values:\n");
    for (int i = 0; i < size; ++i) {
        printf("Elevation at position %d: ", i);
        scanf("%d", &elevationMap[i]);
    }

    int result = trap(elevationMap, size);

    printf("Amount of trapped water: %d\n", result);

    // Free allocated memory
    free(elevationMap);

    return 0;
}
