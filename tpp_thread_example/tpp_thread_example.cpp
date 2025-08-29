/*
    Example: Windows Thread Pool API Usage
    Author: Swabra

    -------------------------------------------------------------
    Description:
      This example demonstrates how to create a thread using the
      Windows Thread Pool API.

      Note: This code is provided for educational purposes only.
      In production code, proper error handling and resource
      management should always be implemented.
*/

#include <iostream>
#include <windows.h>

struct thread_data
{
    void (*t_pointer)();
    HANDLE t_event;
};

void function_handler()
{
    while (true)
    {
        // tpp thread code work
    }
}


VOID CALLBACK threadpool_callback(PTP_CALLBACK_INSTANCE, PVOID Context, PTP_WORK)
{
    thread_data* data = reinterpret_cast<thread_data*>(Context);
    if (data && data->t_pointer)
    {
        SetEvent(data->t_event); data->t_pointer();
    }
}

PTP_WORK create_tpp_worker(void (*func)())
{
    TP_CALLBACK_ENVIRON env;
    PTP_POOL pool = CreateThreadpool(nullptr);
    InitializeThreadpoolEnvironment(&env);
    SetThreadpoolThreadMaximum(pool, 1000);
    SetThreadpoolThreadMinimum(pool, 1);
    SetThreadpoolCallbackPool(&env, pool);
    thread_data* data = new thread_data;
    data->t_pointer = func;

    PTP_WORK work = CreateThreadpoolWork(threadpool_callback, data, &env);
    if (!work)
    {
        delete data;
        DestroyThreadpoolEnvironment(&env);
        CloseThreadpool(pool);
        return nullptr;
    }

    SubmitThreadpoolWork(work);

    return work;
}

int main()
{
    PTP_WORK thread_work = create_tpp_worker(function_handler);
}

