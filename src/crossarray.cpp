#include "crossarray.hpp"
namespace sjtu {
CrossArray::CrossArray(int lines): arrays(nullptr), sizes(nullptr), capacity(lines), count(0){
    if (capacity < 0) capacity = 0;
    arrays = capacity ? new int*[capacity] : nullptr;
    sizes = capacity ? new int[capacity] : nullptr;
    for (int i = 0; i < capacity; ++i){
        arrays[i] = nullptr;
        sizes[i] = 0;
    }
}

CrossArray::CrossArray(const CrossArray & o): arrays(nullptr), sizes(nullptr), capacity(o.capacity), count(o.count){
    arrays = capacity ? new int*[capacity] : nullptr;
    sizes = capacity ? new int[capacity] : nullptr;
    for (int i = 0; i < capacity; ++i){
        arrays[i] = nullptr;
        sizes[i] = 0;
    }
    for (int i = 0; i < count; ++i){
        int sz = o.sizes[i];
        sizes[i] = sz;
        if (sz > 0 && o.arrays[i]){
            arrays[i] = new int[sz];
            for (int j = 0; j < sz; ++j) arrays[i][j] = o.arrays[i][j];
        } else {
            arrays[i] = nullptr;
        }
    }
    for (int i = count; i < capacity; ++i){
        arrays[i] = nullptr;
        sizes[i] = 0;
    }
}

CrossArray & CrossArray::WhichGreater(CrossArray & o){
    long long a = 0, b = 0;
    for (int i = 0; i < count; ++i) a += sizes[i];
    for (int i = 0; i < o.count; ++i) b += o.sizes[i];
    if (a >= b) return *this;
    return o;
}

bool CrossArray::IsSame(const CrossArray & o){
    return this == &o;
}

bool CrossArray::InsertArrays(const int * Input, int size){
    if (count >= capacity) return false;
    int *line = nullptr;
    if (size > 0){
        line = new int[size];
        for (int i = 0; i < size; ++i) line[i] = Input[i];
    }
    arrays[count] = line;
    sizes[count] = size;
    ++count;
    return true;
}

void CrossArray::AppendArrays(const int * Input,int Line,int size){
    int oldsz = sizes[Line];
    int newsz = oldsz + size;
    int *newline = nullptr;
    if (newsz > 0){
        newline = new int[newsz];
        // copy old
        for (int i = 0; i < oldsz; ++i) newline[i] = arrays[Line][i];
        // append new
        for (int i = 0; i < size; ++i) newline[oldsz + i] = Input[i];
    }
    if (arrays[Line]) delete [] arrays[Line];
    arrays[Line] = newline;
    sizes[Line] = newsz;
}

void CrossArray::DoubleCrossLength(){
    int newcap = capacity * 2;
    if (newcap <= capacity){
        // handle zero capacity -> stay zero
        if (capacity == 0){
            // no change
            return;
        }
    }
    int **newArrays = new int*[newcap];
    int *newSizes = new int[newcap];
    for (int i = 0; i < newcap; ++i){
        newArrays[i] = nullptr;
        newSizes[i] = 0;
    }
    for (int i = 0; i < capacity; ++i){
        newArrays[i] = arrays[i];
        newSizes[i] = sizes[i];
    }
    // remaining set to nullptr/0
    delete [] arrays;
    delete [] sizes;
    arrays = newArrays;
    sizes = newSizes;
    capacity = newcap;
}

const int * CrossArray::AtArray(int i){
    return arrays[i];
}

int & CrossArray::At(int i , int j){
    return arrays[i][j];
}

CrossArray::~CrossArray(){
    if (arrays){
        for (int i = 0; i < capacity; ++i){
            if (arrays[i]){
                delete [] arrays[i];
                arrays[i] = nullptr;
            }
        }
        delete [] arrays;
        arrays = nullptr;
    }
    if (sizes){
        delete [] sizes;
        sizes = nullptr;
    }
    capacity = 0;
    count = 0;
}
}
