#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "matrix.h"

#define     NUM_THREADS     2

typedef struct {
    unsigned int id;
    TMatrix *m, *n, *t;
} thread_arg_t;

/* the main function of threads */
static void * thread_main(void * p_arg)
{
    // TODO
    thread_arg_t *arg = (thread_arg_t*)p_arg;
    int start_row, end_row;
    int row_thread = arg->m->nrows / NUM_THREADS;
    start_row = arg->id * row_thread;
    end_row = start_row + row_thread;
    if (arg->id == NUM_THREADS - 1) {
        end_row = arg->m->nrows; 
    }
    for (int i = start_row; i < end_row; i++) {
        for (int j = 0; j < arg->m->ncols; j++) {
            arg->t->data[i][j] = arg->m->data[i][j] + arg->n->data[i][j];
        }
    }
    return NULL;
}

/* Return the sum of two matrices. The result is in a newly creaed matrix. 
 *
 * If a pthread function fails, report error and exit. 
 * Return NULL if something else is wrong.
 *
 * Similar to addMatrix, but this function uses 2 threads.
 */
TMatrix * addMatrix_thread(TMatrix *m, TMatrix *n)
{
    if (    m == NULL || n == NULL
         || m->nrows != n->nrows || m->ncols != n->ncols )
        return NULL;

    TMatrix * t = newMatrix(m->nrows, m->ncols);
    if (t == NULL)
        return t;

    // TODO
    pthread_t threads[NUM_THREADS];
    thread_arg_t args[NUM_THREADS];
    for (unsigned int i = 0; i < NUM_THREADS; i++) {
        args[i].id = i;
        args[i].m = m;
        args[i].n = n;
        args[i].t = t;

        if (pthread_create(&threads[i], NULL, thread_main, &args[i]) != 0) {
            perror("Failed to create thread");
            freeMatrix(t);
            return NULL;
        }
    }

    for (unsigned int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    return t;
}
