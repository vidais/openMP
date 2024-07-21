#include <omp.h>
#include <stdio.h>

static long num_steps=10000;
#define NUM_THREADS 16

void main(){
	int i, nthreads;
	double pi,step, sum[NUM_THREADS];
	step = 1.0/(double) num_steps;

	omp_set_num_threads(NUM_THREADS);

#pragma omp parallel
	{
	int i, id, nthrds;
	double x;
	id = omp_get_thread_num();
	nthrds = omp_get_num_threads();
	if (id==0) nthreads = nthrds;
	for(i=id, sum[id]=0.0;i<num_steps;i=i+nthrds){
		x = (i+0.5)*step;
		sum[id]+=4.0/(1.0+x*x);
	}
	}
	for(i=0, pi=0.0; i<nthreads; i++) pi += sum[i]*step;

	printf("Approximate value of pi is %f in %ld steps running on %d threads", pi, num_steps, NUM_THREADS);
	return;
}


