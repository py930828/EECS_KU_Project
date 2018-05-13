/** @file libscheduler.c
 */
#include "libscheduler.h"
#include <assert.h>
#include <stdlib.h>

typedef struct _job_t
{
  int job_number;
  int running_time;
  int arrival_time;
  int total_time;
  int waiting_time;
  int scheduled_time;
  int priority;
  bool scheduled;
} job_t;


static int corenum;
static scheme_t Scheme;
static job_t **coreptr;
static priqueue_t corequeue;
static priqueue_t q;
static float all_job_time = 0;
static float all_job_waiting_time = 0;
static float all_job_response_time = 0;
static float jobnum = 0;
static int last_update_time;
static void _updatetime                       ( int current_time );
static int _FCFS                              ( const void * a , const void * b );
static int _SJF                               ( const void * a , const void * b );
static int _PRI                               ( const void * a , const void * b );
static int _RR                                ( const void * a , const void * b );


/**
  Initalizes the scheduler.

  Assumptions:
    - You may assume this will be the first scheduler function called.
    - You may assume this function will be called once once.
    - You may assume that cores is a positive, non-zero number.
    - You may assume that scheme is a valid scheduling scheme.

  @param cores the number of cores that is available by the scheduler. These cores will be known as core(id=0), core(id=1), ..., core(id=cores-1).
  @param scheme  the scheduling scheme that should be used. This value will be one of the six enum values of scheme_t
*/
void scheduler_start_up(int cores, scheme_t scheme)
{
	corenum = cores;
	Scheme = scheme;
	coreptr = malloc( sizeof( job_t ) * corenum );
	for( int i = 0; i < corenum; i++ )
	{
		coreptr[i] = NULL;
	}
	switch( scheme ){
		case FCFS : priqueue_init( &q, _FCFS ); priqueue_init( &corequeue, _FCFS );break;
		case RR   : priqueue_init( &q, _RR   ); priqueue_init( &corequeue, _RR );break;
		case SJF  : priqueue_init( &q, _SJF ) ; priqueue_init( &corequeue, _SJF );break;
		case PRI  : priqueue_init( &q, _PRI ) ; priqueue_init( &corequeue, _PRI );break;
		case PPRI : priqueue_init( &q, _PRI ) ; priqueue_init( &corequeue, _PRI ); break;
		case PSJF : priqueue_init( &q, _SJF ) ; priqueue_init( &corequeue, _SJF ); break;
	}
}


/**
  Called when a new job arrives.

  If multiple cores are idle, the job should be assigned to the core with the
  lowest id.
  If the job arriving should be scheduled to run during the next
  time cycle, return the zero-based index of the core the job should be
  scheduled on. If another job is already running on the core specified,
  this will preempt the currently running job.
  Assumptions:
    - You may assume that every job wil have a unique arrival time.

  @param job_number a globally unique identification number of the job arriving.
  @param time the current time of the simulator.
  @param running_time the total number of time units this job will run before it will be finished.
  @param priority the priority of the job. (The lower the value, the higher the priority.)
  @return index of core job should be scheduled on
  @return -1 if no scheduling changes should be made.

 */
int scheduler_new_job(int job_number, int time, int running_time, int priority)
{
	_updatetime( time );
	jobnum++;
  int worstcore = 0;
	job_t *newjob = malloc( sizeof( struct _job_t ));
	newjob->job_number = job_number; newjob->arrival_time = time;
	newjob->running_time = running_time; newjob->priority = priority; newjob->waiting_time = 0;
	newjob->scheduled = false; newjob->scheduled_time = 0; newjob->total_time = 0;// Initalize job
  for( int i = 0; i < corenum; i++ )
  {
    if( !coreptr[i] ) // if core is in idle
    {
      newjob->scheduled = true;
      coreptr[i] = newjob;
      return i;
    }
    else
    {
      priqueue_offer( &corequeue, coreptr[i] ); // add running_core onto the queue
      if( coreptr[i] == priqueue_at( &corequeue, priqueue_size( &corequeue )-1 ) )
      { // check if this core is the worstcore
        worstcore = i;
      }
    }
  }
	// all cores are busy now!!!
  if( (Scheme == PPRI || Scheme == PSJF) && ( priqueue_offer( &corequeue, newjob ) != priqueue_size( &corequeue ) - 1 ) )
  { // preemption found!!!
    priqueue_offer( &q, priqueue_at( &corequeue, priqueue_size( &corequeue )-1) ); // push core process back to the jobqueue
    newjob->scheduled = true;
    coreptr[worstcore] = newjob;
    if( priqueue_size(&corequeue) ){ priqueue_destroy( &corequeue ); } // Destroys the corequeue
    return worstcore;
  }
  else
  {
    if( priqueue_size(&corequeue) ){ priqueue_destroy( &corequeue ); } // Destroys the corequeue
    priqueue_offer( &q, newjob ); // no idle CPU, push to the priqueue
  }
	return -1;
}


/**
  Called when a job has completed execution.

  The core_id, job_number and time parameters are provided for convenience. You may be able to calculate the values with your own data structure.
  If any job should be scheduled to run on the core free'd up by the
  finished job, return the job_number of the job that should be scheduled to
  run on core core_id.

  @param core_id the zero-based index of the core where the job was located.
  @param job_number a globally unique identification number of the job.
  @param time the current time of the simulator.
  @return job_number of the job that should be scheduled to run on core core_id
  @return -1 if core should remain idle.
 */
int scheduler_job_finished(int core_id, int job_number, int time)
{
	_updatetime( time );
	if( !( coreptr[core_id]->running_time ) ) // job done, remove from the core
	{
		all_job_time = all_job_time + coreptr[core_id]->total_time;
		all_job_waiting_time = all_job_waiting_time + coreptr[core_id]->waiting_time;
    all_job_response_time = all_job_response_time + coreptr[core_id]->scheduled_time;
		free(coreptr[core_id]); // free the job on the core
		coreptr[core_id] = NULL;
		if( q.size ) // put the job to the core from queue if there is any
		{
			job_t *job;
			job = priqueue_poll( &q );
			coreptr[core_id] = job;
			if( !job->scheduled ) // be scheduled!!! Yeah!!!
			{
				job->scheduled = true;
				job->scheduled_time = time - job->arrival_time;
			}
			return job->job_number;
		}
		else
		{
			return -1;
		}
	}
  return -2; // never reaches here.
}


/**
  When the scheme is set to RR, called when the quantum timer has expired
  on a core.

  If any job should be scheduled to run on the core free'd up by
  the quantum expiration, return the job_number of the job that should be
  scheduled to run on core core_id.

  @param core_id the zero-based index of the core where the quantum has expired.
  @param time the current time of the simulator.
  @return job_number of the job that should be scheduled on core cord_id
  @return -1 if core should remain idle
 */
int scheduler_quantum_expired(int core_id, int time)
{
	_updatetime( time );
	if( !coreptr[core_id]->running_time )
	{
		all_job_time = all_job_time + coreptr[core_id]->total_time;
		all_job_waiting_time = all_job_waiting_time + coreptr[core_id]->waiting_time;
    all_job_response_time = all_job_response_time + coreptr[core_id]->scheduled_time;
		free( coreptr[core_id] );
		coreptr[core_id] = NULL;
		if( q.size )
		{
			job_t *tempjob = priqueue_poll( &q );
			coreptr[core_id] = tempjob;
			if( !coreptr[core_id]->scheduled ) // be scheduled!!! Yeah!!!
			{
				coreptr[core_id]->scheduled = true;
				coreptr[core_id]->scheduled_time = time - coreptr[core_id]->arrival_time;
			}
			return tempjob->job_number;
		}
		return -1;
	}
	else
	{
		if( q.size )
		{
			priqueue_offer( &q, coreptr[core_id] );
			coreptr[core_id] = priqueue_poll( &q );
			if( !coreptr[core_id]->scheduled ) // be scheduled!!! Yeah!!!
			{
				coreptr[core_id]->scheduled = true;
				coreptr[core_id]->scheduled_time = time - coreptr[core_id]->arrival_time;
			}
			return coreptr[core_id]->job_number;

		}
		return coreptr[core_id]->job_number;
	}
}

/**
  Returns the average waiting time of all jobs scheduled by your scheduler.

  Assumptions:
    - This function will only be called after all scheduling is complete (all jobs that have arrived will have finished and no new jobs will arrive).
  @return the average waiting time of all jobs scheduled.
 */
float scheduler_average_waiting_time()
{
	return ( all_job_waiting_time )/jobnum;
}


/**
  Returns the average turnaround time of all jobs scheduled by your scheduler.

  Assumptions:
    - This function will only be called after all scheduling is complete (all jobs that have arrived will have finished and no new jobs will arrive).
  @return the average turnaround time of all jobs scheduled.
 */
float scheduler_average_turnaround_time()
{
	return all_job_time/jobnum;
}


/**
  Returns the average response time of all jobs scheduled by your scheduler.

  Assumptions:
    - This function will only be called after all scheduling is complete (all jobs that have arrived will have finished and no new jobs will arrive).
  @return the average response time of all jobs scheduled.
 */
float scheduler_average_response_time()
{
	return all_job_response_time/jobnum;
}


/**
  Free any memory associated with your scheduler.

  Assumptions:
    - This function will be the last function called in your library.
*/
void scheduler_clean_up()
{

}


/**
  This function may print out any debugging information you choose. This
  function will be called by the simulator after every call the simulator
  makes to your scheduler.
  In our provided output, we have implemented this function to list the jobs in the order they are to be scheduled. Furthermore, we have also listed the current state of the job (either running on a given core or idle). For example, if we have a non-preemptive algorithm and job(id=4) has began running, job(id=2) arrives with a higher priority, and job(id=1) arrives with a lower priority, the output in our sample output will be:

    2(-1) 4(0) 1(-1)

  This function is not required and will not be graded. You may leave it
  blank if you do not find it useful.
 */
void scheduler_show_queue()
{

}

/**
  This function will get called on scheduler_new_job and scheduler_job_finished

 */
static void _updatetime ( int current_time )
{
	int time_passed = current_time - last_update_time;
	for( int i = 0; i < corenum; i++ ) // update the running_time
	{
		if( coreptr[i] != NULL ) // if this core has a job running
		{
			coreptr[i]->running_time = coreptr[i]->running_time - ( time_passed );
			if( !coreptr[i]->running_time )
			{
				coreptr[i]->total_time = current_time - coreptr[i]->arrival_time;
			}
		}
	}
	for( int i = 0; i < q.size; i++ ) // update the waiting_time
	{
		job_t *tempjob = priqueue_at( &q, i );
		tempjob->waiting_time = tempjob->waiting_time + time_passed;
	}
	last_update_time = current_time;
}

static int _FCFS ( const void * a , const void * b )
{
	int newjob_arrival_time  = ( (job_t *)a )->arrival_time;
	int old_job_arrival_time = ( (job_t *)b )->arrival_time;
	return newjob_arrival_time - old_job_arrival_time ;
}


static int _RR ( const void * a , const void * b )
{
	return 1;
}

static int _SJF ( const void * a , const void * b )
{
	int newjob_running_time = ( (job_t *)a )->running_time;
	int oldjob_running_time = ( (job_t *)b )->running_time;
  int result = newjob_running_time - oldjob_running_time;
  if( !result )
  {
    if (( ((job_t *)a )->arrival_time - ( (job_t *)b )->arrival_time < 0 ) )
    {
      return 0;
    }
    else
    {
      return 1;
    }
  }
	return result;
}


static int _PRI ( const void * a , const void * b )
{
	int newjob_priority = ( (job_t *)a )->priority;
	int oldjob_priority = ( (job_t *)b )->priority;
  int result = newjob_priority - oldjob_priority;
  if( !result )
  {
    if (( ((job_t *)a )->arrival_time - ( (job_t *)b )->arrival_time < 0 ) )
    {
      return 0;
    }
    else
    {
      return 1;
    }
  }
	return result;
}
