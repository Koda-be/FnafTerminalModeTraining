#ifndef THREADFUNC_H_
#define THREADFUNC_H_

void* PrepThrFunc(void*);
void* GameThrFunc(void*);
void* AnimatronicThrFunc(void*);
void* ClockThrFunc(void*);
void* PlayerThrFunc(void*);
void setThreadID();

#endif