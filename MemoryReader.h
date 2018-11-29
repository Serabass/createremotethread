#ifndef CREATEREMOTETHREAD_MEMORYREADER_H
#define CREATEREMOTETHREAD_MEMORYREADER_H

class MemoryReader {
protected:

    explicit MemoryReader(int location);

    template<typename T>
    T Value(int offset);

    int Int(int offset);

    void Int(int offset, int value);

    float Float(int offset);

    void Float(int offset, float value);
public:
    int location;
};

#endif //CREATEREMOTETHREAD_MEMORYREADER_H
