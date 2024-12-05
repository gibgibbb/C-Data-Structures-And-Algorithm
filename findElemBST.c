#define MAX 23

typedef int LIST[MAX];
typedef enum {TRUE, FALSE} Boolean;

Boolean findElement(LIST L, int size, int x) {
    int left = 1;           // Starting index is 1 as per description
    int right = size;
    int mid;
    
    while (left <= right) {
        mid = (left + right) / 2;
        
        if (L[mid] == x) {
            return TRUE;     // Element found
        }
        
        if (L[mid] < x) {
            left = mid + 1;  // Search right half
        } else {
            right = mid - 1; // Search left half
        }
    }
    
    return FALSE;           // Element not found
}