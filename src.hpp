#pragma once
namespace sjtu {
class CrossArray{
private:
    int **arrays;
    int *sizes;
    int capacity;
    int count;
public:
    explicit CrossArray(int lines){
        if (lines < 0) lines = 0;
        capacity = lines;
        count = 0;
        arrays = capacity ? new int*[capacity] : nullptr;
        sizes = capacity ? new int[capacity] : nullptr;
        for (int i = 0; i < capacity; ++i){
            arrays[i] = nullptr;
            sizes[i] = 0;
        }
    }
    CrossArray(const CrossArray & o){
        capacity = o.capacity;
        count = o.count;
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
            } else arrays[i] = nullptr;
        }
    }
    CrossArray & WhichGreater(CrossArray & o){
        long long a = 0, b = 0;
        for (int i = 0; i < count; ++i) a += sizes[i];
        for (int i = 0; i < o.count; ++i) b += o.sizes[i];
        if (a >= b) return *this; return o;
    }
    bool IsSame(const CrossArray & o){ return this == &o; }
    bool InsertArrays(const int * Input, int size){
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
    void AppendArrays(const int * Input,int Line,int size){
        int oldsz = sizes[Line];
        int newsz = oldsz + size;
        int *newline = nullptr;
        if (newsz > 0){
            newline = new int[newsz];
            for (int i = 0; i < oldsz; ++i) newline[i] = arrays[Line][i];
            for (int i = 0; i < size; ++i) newline[oldsz + i] = Input[i];
        }
        if (arrays[Line]) delete [] arrays[Line];
        arrays[Line] = newline;
        sizes[Line] = newsz;
    }
    void DoubleCrossLength(){
        if (capacity == 0) return;
        int newcap = capacity * 2;
        int **newArrays = new int*[newcap];
        int *newSizes = new int[newcap];
        for (int i = 0; i < newcap; ++i){ newArrays[i] = nullptr; newSizes[i] = 0; }
        for (int i = 0; i < capacity; ++i){ newArrays[i] = arrays[i]; newSizes[i] = sizes[i]; }
        delete [] arrays; delete [] sizes;
        arrays = newArrays; sizes = newSizes; capacity = newcap;
    }
    const int * AtArray(int i){ return arrays[i]; }
    int & At(int i , int j){ return arrays[i][j]; }
    ~CrossArray(){
        if (arrays){
            for (int i = 0; i < capacity; ++i){ if (arrays[i]) delete [] arrays[i]; }
            delete [] arrays;
        }
        if (sizes) delete [] sizes;
        arrays = nullptr; sizes = nullptr; capacity = 0; count = 0;
    }
};
}
