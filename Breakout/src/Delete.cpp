#include <SDL.h>

//delete the element in the index of the array and rearrange the array.Max is the number of elements of the array
int* deleteElementOfIntArray(int* array, int index, int max) {
	for (int i = index; i < max - 1; i++) {
		array[i] = array[i + 1];
	}
	return array;
}

//delete the element in the index of the array and rearrange the array.Max is the number of elements of the array
SDL_Rect* deleteElementOfRectArray(SDL_Rect* array, int index, int max) {
	for (int i = index; i < max - 1; i++) {
		array[i] = array[i + 1];
	}
	return array;
}