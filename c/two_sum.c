#include <stdio.h>
#include <stdlib.h>

// Define the structure for a hash node
typedef struct HashNode {
    int key;                // The number from the array
    int value;              // The index of the number
    struct HashNode* next;  // Pointer to the next node (for handling collisions)
} HashNode;

// Define the structure for the hash table
typedef struct HashTable {
    int size;               // Size of the hash table
    HashNode** table;       // Array of pointers to hash nodes
} HashTable;

// Function to create a new hash node
HashNode* createHashNode(int key, int value) {
    HashNode* newNode = (HashNode*)malloc(sizeof(HashNode));
    if (!newNode) {
        printf("Memory allocation failed for HashNode.\n");
        exit(EXIT_FAILURE);
    }
    newNode->key = key;
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

// Simple hash function
int hashFunction(int key, int size) {
    // To handle negative keys, take absolute value
    // and ensure the result is within table size
    unsigned int ukey = (unsigned int)key;
    return ukey % size;
}

// Function to create a hash table
HashTable* createHashTable(int size) {
    HashTable* newTable = (HashTable*)malloc(sizeof(HashTable));
    if (!newTable) {
        printf("Memory allocation failed for HashTable.\n");
        exit(EXIT_FAILURE);
    }
    newTable->size = size;
    newTable->table = (HashNode**)malloc(sizeof(HashNode*) * size);
    if (!newTable->table) {
        printf("Memory allocation failed for HashTable's table.\n");
        exit(EXIT_FAILURE);
    }
    // Initialize all buckets to NULL
    for (int i = 0; i < size; i++) {
        newTable->table[i] = NULL;
    }
    return newTable;
}

// Function to insert a key-value pair into the hash table
void insertHashTable(HashTable* ht, int key, int value) {
    int index = hashFunction(key, ht->size);
    HashNode* current = ht->table[index];
    // Check if the key already exists; if so, update the value
    while (current) {
        if (current->key == key) {
            current->value = value; // Update the index
            return;
        }
        current = current->next;
    }
    // If key not found, create a new node and insert at the beginning
    HashNode* newNode = createHashNode(key, value);
    newNode->next = ht->table[index];
    ht->table[index] = newNode;
}

// Function to search for a key in the hash table
// Returns the value (index) if found, else -1
int searchHashTable(HashTable* ht, int key) {
    int index = hashFunction(key, ht->size);
    HashNode* current = ht->table[index];
    while (current) {
        if (current->key == key) {
            return current->value;
        }
        current = current->next;
    }
    return -1; // Not found
}

// Function to free the hash table
void freeHashTable(HashTable* ht) {
    if (!ht) return;
    for (int i = 0; i < ht->size; i++) {
        HashNode* current = ht->table[i];
        while (current) {
            HashNode* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(ht->table);
    free(ht);
}

// The Two Sum function
int* twoSum(int* nums, int numsSize, int target, int* returnSize){
    // Define the size of the hash table
    // A good practice is to use a prime number to reduce collisions
    // Here, we'll choose a size greater than numsSize
    int hashSize = 20011; // A prime number greater than 10^4
    HashTable* ht = createHashTable(hashSize);
    
    // Allocate memory for the result
    int* result = (int*)malloc(2 * sizeof(int));
    if (!result) {
        printf("Memory allocation failed for result.\n");
        exit(EXIT_FAILURE);
    }
    
    // Iterate through the array
    for (int i = 0; i < numsSize; i++) {
        int complement = target - nums[i];
        int complementIndex = searchHashTable(ht, complement);
        if (complementIndex != -1) {
            // Found the complement
            result[0] = complementIndex;
            result[1] = i;
            *returnSize = 2;
            freeHashTable(ht);
            return result;
        }
        // Insert the current number and its index into the hash table
        insertHashTable(ht, nums[i], i);
    }
    
    // If no solution is found, though the problem guarantees one
    *returnSize = 0;
    freeHashTable(ht);
    return NULL;
}

// Function to print the result
void printResult(int* result, int returnSize){
    if (returnSize == 2) {
        printf("[ %d, %d ]\n", result[0], result[1]);
    } else {
        printf("No solution found.\n");
    }
}

// Main function with test cases
int main() {
    // Example 1
    int nums1[] = {2, 7, 11, 15};
    int target1 = 9;
    int returnSize1;
    int* result1 = twoSum(nums1, sizeof(nums1)/sizeof(nums1[0]), target1, &returnSize1);
    printf("Example 1 Output: ");
    printResult(result1, returnSize1);
    free(result1);
    
    // Example 2
    int nums2[] = {3, 2, 4};
    int target2 = 6;
    int returnSize2;
    int* result2 = twoSum(nums2, sizeof(nums2)/sizeof(nums2[0]), target2, &returnSize2);
    printf("Example 2 Output: ");
    printResult(result2, returnSize2);
    free(result2);
    
    // Example 3
    int nums3[] = {3, 3};
    int target3 = 6;
    int returnSize3;
    int* result3 = twoSum(nums3, sizeof(nums3)/sizeof(nums3[0]), target3, &returnSize3);
    printf("Example 3 Output: ");
    printResult(result3, returnSize3);
    free(result3);
    
    return 0;
}

