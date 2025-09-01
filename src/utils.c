/**
 * @file utils.c
 */

#include "utils.h"

inline Color8 color_to_color8(Color* col){
    return (Color8){col->r*255, col->g*255, col->b*255, col->a*255};
}

inline Color color8_to_color(Color8* col){
    // Messy bc division by 0 bad, so just ignore
    return (Color){col->r != 0 ? col->r/255 : col->r, col->g != 0 ? col->g/255 : col->g, col->b != 0 ? col->b/255 : col->b, col->a != 0 ? col->a/255 : col->a};
}

inline SDL_FRect vec_to_rect(Vector2* pos, Vector2* size){
    return (SDL_FRect){pos->x, pos->y, size->w, size->h};
}

/**
 * @brief Search on sorted data structure
 * 
 * @param arr 
 * @param max 
 * @param target 
 * @return int Index of element
 */
inline int binary_search(int arr[], int max, int target) {
    int low = 0;
    int high = max-1;
    while (low <= high) {
        int mid = low + (high - low) / 2;

        // Check if x is present at mid
        if (arr[mid] == target)
            return mid;

        // If x greater, ignore left half
        if (arr[mid] < target)
            low = mid + 1;

        // If x is smaller, ignore right half
        else
            high = mid - 1;
    }

    // If we reach here, then element was not present
    return -1;
}