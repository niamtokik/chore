/*
 * Copyright (c) 2024 Mathieu Kerjouan
 *
 * Permission to use, copy, modify, and distribute this software for
 * any purpose with or without fee is hereby granted, provided that
 * the above copyright notice and this permission notice appear in all
 * copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 * AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS
 * OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
 * NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 */
#define CHORE_VERSION "0.1.0"

/* job management
 */
#define JOB_NAME_LEN 255
#define JOB_COMMAND_ARG_LEN 255
#define JOB_COMMAND_LEN 255
// #define JOB_DEPENDENT_JOB_LEN 1
// #define JOB_REACTS_LEN 2

typedef struct job {
  char name[JOB_NAME_LEN];
  char command[JOB_COMMAND_LEN][JOB_COMMAND_ARG_LEN];
  int pid;
  char *start_at;
  // state = RUNNING | STOPPED | KILLED
  // dependent_job *job;
  // stdin
  // stdout
  // stderr
  // struct *react {}
} job;

/* jobs management */
#define JOBS_LIMIT 255

typedef struct jobs {
  int counter;
  job jobs[JOBS_LIMIT];
} jobs;

/* main functions from chored.c */
void chored_usage();
void chored_version();
int chored_main(int, char **);
int chored_check();
int chored_init();
int chored_loop(jobs *);
int chored_terminate(jobs *);

/* chored_lib.c */
int chored_check_dir(char *, char *);

/* chored_jobs.c */
int chored_jobs_init(jobs *);
int chored_jobs_exist(jobs *, char *);
int chored_jobs_add(jobs *, job*);
int chored_jobs_del(jobs *, char *);
job* chored_jobs_search(jobs *, char *);
int chored_jobs_check(jobs *);
