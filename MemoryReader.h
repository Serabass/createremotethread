#ifndef CREATEREMOTETHREAD_MEMORYREADER_H
#define CREATEREMOTETHREAD_MEMORYREADER_H

class MemoryReader {
protected:

    explicit MemoryReader(int location);

    template<typename T>
    T GetValue(int offset);

    int GetIntValue(int offset);

    void SetIntValue(int offset, int value);

    float GetFloatValue(int offset);

    void SetFloatValue(int offset, float value);
public:
    int location;
};

#endif //CREATEREMOTETHREAD_MEMORYREADER_H
