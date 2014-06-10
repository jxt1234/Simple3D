#ifndef INTERFACE_HEAD_H
#define INTERFACE_HEAD_H

#define INTERFACE(x)\
    x(){}\
    virtual ~x(){}

#define EMPTYCONSTRUCT(x)\
    x(){}\
    virtual ~x(){}
#endif
