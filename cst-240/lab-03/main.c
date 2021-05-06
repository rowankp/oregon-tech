#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>
#include <pthread.h>
#include "list.h"
#include "sequence.h"

typedef struct threaded_list_s
{
	linked_list_t * linked_list;
	int64_t to_insert;
} threaded_list_t;

//*************************************************
void Fatal_Error(char *msg)
{
    fprintf(stderr, msg);
    exit(-1);
}

//*************************************************
void Check_Item(int64_t value)
{
    static int64_t last_item = INT64_MIN;

    if (last_item != INT64_MIN && last_item+1 != value)
    {
        printf("Items not in sequence: %ld %ld\n", last_item, value);
    }
    last_item = value;

    // Uncomment the following if you want to see the data
    //printf("Item: %ld\n", value);
}

//*************************************************
void * ThreadFunc(void * ptr)
{
	threaded_list_t * l = (threaded_list_t *) ptr;
	int64_t ii;
	
	for (ii=0; ii < l->to_insert; ++ii)
    {
        Insert_In_Order(l->linked_list, Next_In_Sequence());
    }
	return NULL;
}

//*************************************************
int main(int argc, char** argv)
{
    linked_list_t * list;
	threaded_list_t * t_list;
    int opt;                    // command line arg
    int ii;                     // for index
    int64_t num_to_insert = 20;
    int num_threads = 1;
 
    while ((opt = getopt(argc, argv, "hn:t:")) != -1)
    {
        switch (opt)
        {
            case 'h':
                printf("%s -h -n <inserts/thread> -t <num threads>\n", argv[0]);
                break;
            case 'n':
                num_to_insert = atol(optarg);
                if (num_to_insert < 0) 
                    Fatal_Error("-n must specify a value > 0");
                break;
            case 't':
                num_threads = atoi(optarg);
                if (num_threads < 1)
                    Fatal_Error("-t must specify a value > 0");
                break;
        }
    }
	
	// create list
    printf("Creating sorted list with %ld elements\n", num_to_insert);
    list = Init_List();

	// create struct
	t_list = (threaded_list_t *)malloc(sizeof(threaded_list_t));
	t_list->linked_list = list;
	t_list->to_insert = num_to_insert;
    
	// create threads
	if (num_threads > 0)
	{
		// create an array of threads
		pthread_t threads[num_threads];
		
		// start threads
		for (ii=0; ii < num_threads; ++ii)
		{
			pthread_create(&(threads[ii]), NULL, ThreadFunc, (void *) t_list);
		}
		
		// end threads
		for (ii=0; ii < num_threads; ++ii)
		{
			pthread_join(threads[ii], NULL);
		}
	}

    printf("Checking sorted list\n");
    Traverse(list, Check_Item);

    if (Count(list) != num_to_insert) printf("List is not tracking size\n");

	// release resources
    Delete_List(list);
	free(t_list);

	return 0;
}

