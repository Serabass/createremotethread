//
// Created by Serabass on 30.11.2018.
//

#ifndef CREATEREMOTETHREAD_MACROS_H
#define CREATEREMOTETHREAD_MACROS_H

#define DEFAULT_GETTER(T, O) return this->T(O)
#define DEFAULT_SETTER(T, O) this->T(O, value)

typedef float Float;

#define DEFAULT_PROP(CLASS, TYPE, type, METHOD, OFFSET) \
    type CLASS::METHOD() { \
        DEFAULT_GETTER(TYPE, OFFSET); \
    } \
    void CLASS::METHOD(type value) { \
        DEFAULT_SETTER(TYPE, OFFSET); \
    }

#define DEFAULT_PROP_H(TYPE, METHOD) \
    TYPE METHOD(); \
    void METHOD(TYPE value);

#endif //CREATEREMOTETHREAD_MACROS_H
