/**
 * @file execute.c
 *
 * @brief Implements interface functions between Quash and the environment and
 * functions that interpret an execute commands.
 *
 * @note As you add things to this file you may want to change the method signature
 */

#include "execute.h"

#include <stdio.h>

#include "quash.h"

#include "deque.h"

#include <sys/wait.h>
/*
#define prev_pipe 0

cpdefine next_pipe 1

#define write 1

#define read 0
*/
//int mypipe[2][2];
char* cwd;
int status;
int prev_pipe[2];
int next_pipe[2];
int fileno(FILE *stream); //for testing
//int mypipe[2][2];
int counter = 0;
bool job_init = false;
pid_t pid;

//
// create a pid_queue that each node is a pid_state
//
int JOB_ID = 0;
IMPLEMENT_DEQUE_STRUCT(pid_queue, pid_t);
PROTOTYPE_DEQUE(pid_queue, pid_t);
IMPLEMENT_DEQUE(pid_queue, pid_t);
//
//
typedef struct job {     // now (struct job) is a type like int,
                        //and it holds a list of pid_t
  char* cmd;
  int jobnum;
  pid_t pid;
  pid_queue pids;
} job;


//
// create a queue that each node is a pid_queue
//
IMPLEMENT_DEQUE_STRUCT(job_queue, job);
PROTOTYPE_DEQUE(job_queue, job);
IMPLEMENT_DEQUE(job_queue, job);
//
//
job_queue my_job_queue;





/*IMPLEMENT_DEQUE_STRUCT(process, pid);
PROTOTYPE_DEQUE(process, pid);
typedef struct process_list{
  int length;

}struct_name; */

// Remove this and all expansion calls to it
/**
 * @brief Note calls to any function that requires implementation
 */
#define IMPLEMENT_ME()                                                  \
  fprintf(stderr, "IMPLEMENT ME: %s(line %d): %s()\n", __FILE__, __LINE__, __FUNCTION__)

/***************************************************************************
 * Interface Functions
 ***************************************************************************/

// Return a string containing the current working directory.
char* get_current_directory(bool* should_free) {
  // TODO: Get the current working directory. This will fix the prompt path.
  // HINT: This should be pretty simple
  *should_free = true;
	return getcwd(NULL,0);
}

// Returns the value of an environment variable env_var
const char* lookup_env(const char* env_var) {
  // TODO: Lookup environment variables. This is required for parser to be able
  // to interpret variables from the command line and display the prompt
  // correctly
  // HINT: This should be pretty simple
  return getenv (env_var);
}

// Check the status of background jobs
void  check_jobs_bg_status() {
  // TODO: Check on the statuses of all processes belonging to all background
  // jobs. This function should remove jobs from the jobs queue once all
  // processes belonging to a job have completed.
  //IMPLEMENT_ME();

  // TODO: Once jobs are implemented, uncomment and fill the following line
  pid_t pid;
  int* status = 0;
  struct job tempjob;
  if( !is_empty_job_queue(&my_job_queue))
  {
    int job_length = length_job_queue(&my_job_queue);
    for(int i = 0; i < job_length; i++)
    {
      tempjob = pop_front_job_queue(&my_job_queue); // pop the first job object, push it in if neccesary
      int pid_length = length_pid_queue(&(tempjob.pids));
      for(int j = 0; j < pid_length; j++)
      {
        pid = pop_front_pid_queue(&(tempjob.pids));
        if( !waitpid(pid, status, WNOHANG) ) // if pid still running, push back into the tempjob
        {
          push_back_pid_queue(&tempjob.pids, pid);
        }
      }
      if( !is_empty_pid_queue(&tempjob.pids) ) // if not all pids finishs, push back to the job_queue
      {
        push_back_job_queue(&my_job_queue, tempjob);
      }
      else
      {
        print_job_bg_complete(tempjob.jobnum, tempjob.pid, tempjob.cmd);
        destroy_pid_queue( &tempjob.pids );
        free( tempjob.cmd );
        JOB_ID--;
      }
    }
  }
}

// Prints the job id number, the process id of the first process belonging to
// the Job, and the command string associated with this job
void print_job(int job_id, pid_t pid, const char* cmd) {
  printf("[%d]\t%8d\t%s\n", job_id, pid, cmd);
  fflush(stdout);
}

// Prints a start up message for background processes
void print_job_bg_start(int job_id, pid_t pid, const char* cmd) {
  printf("Background job started: ");
  print_job(job_id, pid, cmd);
}

// Prints a completion message followed by the print job
void print_job_bg_complete(int job_id, pid_t pid, const char* cmd) {
  printf("Completed: \t");
  print_job(job_id, pid, cmd);
}

/***************************************************************************
 * Functions to process commands
 ***************************************************************************/
// Run a program reachable by the path environment variable, relative path, or
// absolute path
void run_generic(GenericCommand cmd) {
  // Execute a program with a list of arguments. The `args` array is a NULL
  // terminated (last string is always NULL) list of strings. The first element
  // in the array is the executable
  char* exec = cmd.args[0];
  char** args = cmd.args;
  if( execvp( exec, args ) < 0 )
  {
    fprintf((stderr), "Error executing generic. \n");
    exit (1);
  }

}

// Print strings
void run_echo(EchoCommand cmd) {
  // Print an array of strings. The args array is a NULL terminated (last
  // string is always NULL) list of strings.
  char** str = cmd.args;
  (void) str; // Silence unused variable warning

  // TODO: Implement echo
  //IMPLEMENT_ME();
  for( ; *str != '\0' ; str++ )
  {
    printf("%s", *str);
  }
  printf("\n");

  // Flush the buffer before returning
  fflush(stdout);
}

// Sets an environment variable
void run_export(ExportCommand cmd) {
  // Write an environment variable
  const char* env_var = cmd.env_var;
  const char* val = cmd.val;

  if( setenv (env_var, val, 1) < 0 )
  {
    fprintf((stderr), "Error execing find. ERROR#\n");
    exit (1);
  }
}

// Changes the current working directory
void run_cd(CDCommand cmd) {
  // Get the directory name
  const char* dir = cmd.dir;
  // Check if the directory is valid
  if (dir == NULL)
  {
    perror("ERROR: Failed to resolve path");
    return;
  }
  if ( chdir(cmd.dir) < 0 )
  {
    printf("ERROR: Failed to direct to path %s\n", cmd.dir);
    exit (1);
  }
  setenv( "PWD", dir, 1);
}

// Sends a signal to all processes contained in a job
void run_kill(KillCommand cmd) {
  int signal = cmd.sig;
  int job_id = cmd.job;
  // TODO: Kill all processes associated with a background job
  job temp_job;
  int is_empty = true;
  for( int i = 0; i < length_job_queue( &my_job_queue); i++)
  {
    is_empty = false;
    temp_job = pop_front_job_queue(&my_job_queue);
    if( job_id == temp_job.jobnum )
    {
      pid_t pid = temp_job.pid;
      kill(pid, signal);
    }
    push_back_job_queue(&my_job_queue, temp_job);
  }
  if( is_empty )
  {
    destroy_pid_queue(&temp_job.pids);
    free(temp_job.cmd);
  }
}


// Prints the current working directory to stdout
void run_pwd() {
  bool should_free = false;
  char* pwd = get_current_directory(&should_free);
  printf("%s \n", pwd);
  if(should_free)
  {
    free(pwd);
  }
  // Flush the buffer before returning
  fflush(stdout);
}

// Prints all background jobs currently in the job list to stdout
void run_jobs() {
  // TODO: Print background jobs
  job temp_job;
  bool is_empty = true;
  for( int i = 0; i < length_job_queue( &my_job_queue); i++)
  {
    is_empty = false;
    temp_job = pop_front_job_queue( &my_job_queue );
    print_job(temp_job.jobnum, temp_job.pid, temp_job.cmd);
    push_back_job_queue(&my_job_queue, temp_job);
  }
  if( is_empty )
  {
    destroy_pid_queue(&temp_job.pids);
    free(temp_job.cmd);
  }

  // Flush the buffer before returning
  fflush(stdout);
}

/***************************************************************************
 * Functions for command resolution and process setup
 ***************************************************************************/

/**
 * @brief A dispatch function to resolve the correct @a Command variant
 * function for child processes.
 *
 * This version of the function is tailored to commands that should be run in
 * the child process of a fork.
 *
 * @param cmd The Command to try to run
 *
 * @sa Command
 */
void child_run_command(Command cmd) {
  CommandType type = get_command_type(cmd);

  switch (type) {
  case GENERIC:
    run_generic(cmd.generic);
    break;

  case ECHO:
    run_echo(cmd.echo);
    break;

  case PWD:
    run_pwd();
    break;

  case JOBS:
    run_jobs();
    break;

  case EXPORT:
  case CD:
  case KILL:
  case EXIT:
  case EOC:
    break;

  default:
    fprintf(stderr, "Unknown command type: %d\n", type);
  }
}

/**
 * @brief A dispatch function to resolve the correct @a Command variant
 * function for the quash process.
 *
 * This version of the function is tailored to commands that should be run in
 * the parent process (quash).
 *
 * @param cmd The Command to try to run
 *
 * @sa Command
 */
void parent_run_command(Command cmd) {
  CommandType type = get_command_type(cmd);

  switch (type) {
  case EXPORT:
    run_export(cmd.export);
    break;

  case CD:
    run_cd(cmd.cd);
    break;

  case KILL:
    run_kill(cmd.kill);
    break;

  case GENERIC:
  case ECHO:
  case PWD:
  case JOBS:
  case EXIT:
  case EOC:
    break;

  default:
    fprintf(stderr, "Unknown command type: %d\n", type);
  }
}

/**
 * @brief Creates one new process centered around the @a Command in the @a
 * CommandHolder setting up redirects and pipes where needed
 *
 * @note Processes are not the same as jobs. A single job can have multiple
 * processes running under it. This function creates a process that is part of a
 * larger job.
 *
 * @note Not all commands should be run in the child process. A few need to
 * change the quash process in some way
 *
 * @param holder The CommandHolder to try to run
 *
 * @sa Command CommandHolder
 */
void create_process(CommandHolder holder, pid_queue* my_job_pids) {
  // Read the flags field from the parser
  bool p_in  = holder.flags & PIPE_IN;
  bool p_out = holder.flags & PIPE_OUT;
  bool r_in  = holder.flags & REDIRECT_IN;
  bool r_out = holder.flags & REDIRECT_OUT;
  bool r_app = holder.flags & REDIRECT_APPEND; // This can only be true if r_out
                                               // is true
  pid_t pid_1;
  pipe( next_pipe );
  //IMPORTANT!!! Create pipe before fork!!!!!
  pid_1 = fork(); // create child process;  bool p_in  = holder.flags & PIPE_IN;
  if( pid_1 == 0 ) // This will go to the child process, child sees pid_1 = 0;
  {
    if( p_out )
    {
      dup2( next_pipe[1], 1); //duplicate stdout to to my next writing pipe;
      //printf("I'm in p_out!!!\n");
    }
    if( p_in )
    {
      //printf("I'm in p_in!!!\n");
      // no need to create pipe for p_in, it would be already create.
      dup2( prev_pipe[0], 0 ); // duplicate stdin to to my next read pipe;
    }
    if( r_in )
    {
      freopen( holder.redirect_in, "r", stdin); // a filestream that read from the holder file;
    }
    if( r_out )
    {
      if( r_app )
      {
        freopen( holder.redirect_out, "a", stdout);
      }
      else
      {
        freopen( holder.redirect_out, "w", stdout);
      }
    }
    child_run_command(holder.cmd);
    exit(0);
  }
  else // will be in the parent process
  {
    // do I really need pid_1????? Yes, because it will always go to child and parent everytime
    if( p_out )
    {
      prev_pipe[0] = next_pipe[0];
    }
    //printf("counter : %d , p_in: %d p_out: %d r_in: %d r_out: %d r_app: %d\n", counter, p_in, p_out, r_in, r_out , r_app);
    parent_run_command(holder.cmd);
  }
  push_back_pid_queue( my_job_pids , pid_1 );
  close(next_pipe[1]); // this needs to be closed
}

void clean_my_job_queue()
{
  job temp_job;
  while( !is_empty_job_queue(&my_job_queue)){
    temp_job = pop_front_job_queue(&my_job_queue);
    free(temp_job.cmd);
    destroy_pid_queue(&temp_job.pids);
  }
  destroy_job_queue( &my_job_queue );
}
// Run a list of commands
void run_script(CommandHolder* holders) {
  if (holders == NULL)
    return;
  if( !job_init )
  {
    my_job_queue = new_job_queue(0);
    job_init = true;
    atexit(clean_my_job_queue);
  }
  check_jobs_bg_status();
  if (get_command_holder_type(holders[0]) == EXIT &&
      get_command_holder_type(holders[1]) == EOC) {
    end_main_loop();
    return;
  }

  CommandType type;
  job my_job;
  my_job.pids = new_pid_queue(0);
  // Run all commands in the `holder` array
  for (int i = 0; (type = get_command_holder_type(holders[i])) != EOC; ++i)
    create_process(holders[i], &my_job.pids);

  if (!(holders[0].flags & BACKGROUND)) {
    // Not a background Job
    // Wait for all processes under the job to complete
    while( !is_empty_pid_queue( &my_job.pids ) )
    {
      //printf( "The job that is running is %d \n", peek_front_pid_queue( &my_job.pids ) );
      waitpid( pop_front_pid_queue( &my_job.pids ), &status, 0);
    }
    destroy_pid_queue( &my_job.pids );
  }
  else {
    // A background job.
    // TODO: Push the new job to the job queue
    JOB_ID++;
    // TODO: Once jobs are implemented, uncomment and fill the following line
    //print_job_bg_start(job_id, pid, cmd);
    my_job.cmd = get_command_string();
    my_job.jobnum = JOB_ID;
    my_job.pid = peek_back_pid_queue( &my_job.pids );
    push_back_job_queue( &my_job_queue, my_job );
    print_job_bg_start(my_job.jobnum, my_job.pid , my_job.cmd);
  }
  //free(cwd);  this causes big error ( core dump )
}
