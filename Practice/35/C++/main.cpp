#include <iostream>

using namespace std;

struct IntArray{
    int *data;
    int size;
};

void create(IntArray& arr, const int size){
    arr.size = size;
}

void print (IntArray& arr){
    cout << "[";
    for (int i = 0; i < arr.size; i++){
        cout << arr.data[i];
        if (i < arr.size - 1){
            cout << ", ";
        }
    }
    cout << "]" << endl;
}

void resize(IntArray& arr, int newSize){
    int* newArr = new int[newSize];
    delete[] arr.data;
    arr.data = newArr;
    arr.size = newSize;
}

void destroy(IntArray& arr){
    delete[] arr.data;
    arr.data = nullptr;
    arr.size = 0;
}

void set(IntArray& arr, const int index, const int value){
    arr.data[index] = value;
}

int main(){
    const int size = 30;
    IntArray arr;
    create(arr, size);
    for(int i = 0; i < size; i++){
        set(arr, i, i + 1);
    }
    print(arr);
    resize(arr, 50);
    print(arr);
    resize(arr, 10);
    print(arr);
    destroy(arr);
    return 0;
}
