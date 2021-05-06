//***********************************************
// Concurrent List Test Harness
// Rowan Parker
// Winter 2021

#include "FineGrainList.h"
#include "List.h"
#include "Node.h"
#include "ReadWriteLockList.h"
#include "SimpleList.h"
#include "SingleLockList.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <atomic>
#include <iostream>
#include <thread>
#include <vector>
using std::cout;
using std::endl;
using std::thread;
using std::vector;

// flag used to start/stop threads
std::atomic_char running;

// lock modes
#define LOCK_MODE_NONE          1
#define LOCK_MODE_COARSE        2
#define LOCK_MODE_READ_WRITE    3
#define LOCK_MODE_FINE          4

// test modes
#define TEST_MODE_READ_ONLY     1
#define TEST_MODE_WRITE_ONLY    2
#define TEST_MODE_READ_WRITE    3

// thread data
typedef struct
{
    List*   list;
    int     initial_size;
    int     test_mode;
    int     lock_mode;
    int     num_threads;
    int     parallel_delay;
    int     serial_delay;
    int     duration;
    int     reads_per_thousand;
    int     num_inserts;
    int     num_deletes;
    int     num_lookups;
} ThreadData;

//***********************************************
static void parse_args(int argc, char** argv, ThreadData* args)
{
    // set defaults
    args->initial_size = 1000;
    args->test_mode = TEST_MODE_READ_WRITE;
    args->lock_mode = LOCK_MODE_NONE;
    args->num_threads = 1;
    args->parallel_delay = 1000;
    args->serial_delay = 1000;
    args->duration = 1000000;
    args->reads_per_thousand = 10;
    args->num_inserts = 0;
    args->num_deletes = 0;
    args->num_lookups = 0;

    int opt;
    while ((opt = getopt(argc, argv, "hi:rb:wm:t:d:B:L:")) != -1)
    {
        switch (opt)
        {
            case 'h':
                printf("%s\n"
                    "-h\tPrint this help message and exit.\n"
                    "-i\t<inital list size> Default is 1000.\n"
                    "-r\tPerform a read-only test.\n"
                    "-b\t<n> Perform <n> reads per 1000 operations. Default is 10.\n"
                    "-w\tPerform a write-only test.\n"
                    "-m\t<mode> Set lock mode:\n"
                    "\t\t1 No locks\n"
                    "\t\t2 Coarse grained locking\n"
                    "\t\t3 Reader-Writer locking\n"
                    "\t\t4 Fine grained locking\n"
                    "-t\t<n> Number of threads to run. Default is 1.\n"
                    "-d\t<duration> Duration of test in microseconds. Default is 1000000.\n"
                    "-B\t<n> Delay between operations in microseconds. Default is 1000.\n"
                    "-L\t<n> Delay that a lock should be held following lookup in microseconds. Default is 1000.\n"
                    , argv[0]);
                exit(1);
            case 'i':
                args->initial_size = atol(optarg);
                break;
            case 'r':
                args->test_mode = TEST_MODE_READ_ONLY;
            case 'b':
                args->reads_per_thousand = atoi(optarg);
                break;
            case 'w':
                args->test_mode = TEST_MODE_WRITE_ONLY;
                break;
            case 'm':
                args->lock_mode = atoi(optarg);
                break;
            case 't':
                args->num_threads = atoi(optarg);
                break;
            case 'd':
                args->duration = atol(optarg);
                break;
            case 'B':
                args->parallel_delay = atol(optarg);
                break;
            case 'L':
                args->serial_delay = atol(optarg);
                break;
        }
    }

    switch (args->lock_mode)
    {
        case LOCK_MODE_NONE:
            args->list = new SimpleList(args->initial_size);
            break;
        case LOCK_MODE_COARSE:
            args->list = new SingleLockList(args->initial_size);
            break;
        case LOCK_MODE_READ_WRITE:
            args->list = new ReadWriteLockList(args->initial_size);
            break;
        case LOCK_MODE_FINE:
            args->list = new FineGrainList(args->initial_size);
            break;
    }
}

//***********************************************
void threadFunction(ThreadData *args)
{
    // init random number seed
    srand(time(NULL));
    args->num_inserts = 0;
    args->num_deletes = 0;
    args->num_lookups = 0;

    // wait until told to start
    while (!running.load())
    { }

    int operations = 0;

    while (running.load())
    {
        operations++;
        usleep(args->parallel_delay);

        if (args->test_mode == TEST_MODE_READ_ONLY)
        {
            Node* node = args->list->lookup(operations);
            args->num_lookups++;
            usleep(args->serial_delay);
            args->list->elementRelease(node);
        }
        else if (args->test_mode == TEST_MODE_WRITE_ONLY)
        {
            args->list->insertOrdered(operations * 1000);
            args->num_inserts++;
        }
        else
        {
            int option = rand() % 2 + 1;

            if (operations % 1000 == 0)
            {
                for (int ii = 0; ii < args->reads_per_thousand; ++ii)
                {
                    Node* node = args->list->lookup(ii * operations);
                    args->num_lookups++;
                    usleep(args->serial_delay);
                    args->list->elementRelease(node);
                }
            }

            if (option == 1)
            {
                args->list->insertOrdered(operations);
                args->num_inserts++;
            }
            else
            {
                args->list->remove(operations);
                args->num_deletes++;
            }
        }
    }
}

int main(int argc, char** argv)
{
    ThreadData data;
    vector<thread> threads;
    vector<ThreadData> thread_data;

    running.store(0);

    parse_args(argc, argv, &data);

    for (int ii = 0; ii < data.num_threads; ++ii)
    {
        thread_data.push_back(data);
        thread_data.back().list = data.list;
    }

    // create threads
    for (int ii = 0; ii < data.num_threads; ++ii)
    {
        threads.push_back(thread(threadFunction, &thread_data[ii]));
    }

    // wait for threads to start
    usleep(300000);

    // tell threads to start processing
    running.store(1);

    // let threads run for specified duration
    usleep(data.duration);

    // stop threads
    running.store(0);

    int total_inserts = 0;
    int total_deletes = 0;
    int total_lookups = 0;

    // join threads
    for (int ii = 0; ii < data.num_threads; ++ii)
    {
        threads[ii].join();

        cout << "Thread " << ii + 1 << " Stats"
             << "\t\ti: " << thread_data[ii].num_inserts
             << "\t\td: " << thread_data[ii].num_deletes
             << "\t\tl: " << thread_data[ii].num_lookups
             << endl;

        total_inserts += thread_data[ii].num_inserts;
        total_deletes += thread_data[ii].num_deletes;
        total_lookups += thread_data[ii].num_lookups;
    }

    // print stats
    cout << endl;
    cout << "Totaled Stats"
         << "\t\ti: " << total_inserts
         << "\t\td: " << total_deletes
         << "\t\tl: " << total_lookups
         << endl;

    delete data.list;

	return 0;
}