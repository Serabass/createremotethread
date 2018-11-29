//
// Created by Serabass on 30.11.2018.
//

#ifndef CREATEREMOTETHREAD_MACROS_H
#define CREATEREMOTETHREAD_MACROS_H

#define DEFAULT_GETTER(T, O) return this->T(O)
#define DEFAULT_SETTER(T, O) this->T(O, value)

typedef float Float;

#define DEFAULT_PROP(C, T, t, M, O) t C::M() { DEFAULT_GETTER(T, O); } void C::M(t value) { DEFAULT_SETTER(T, O); }
#define DEFAULT_PROP_H(T, N)  T N(); void N(T value);

#endif //CREATEREMOTETHREAD_MACROS_H
