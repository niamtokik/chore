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
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include "chore.h"

/* init jobs struct with default values.
 */
int chored_jobs_init(jobs *jobs) {
  jobs->counter = 0;
  bzero(jobs->jobs, sizeof(job)*JOBS_LIMIT);
  return 0;
}

/* add a new job into jobs struct.
 */
int chored_jobs_add(jobs *jobs, job *job) {
  return 0;
}

/* return true if a job exist, else false.
 */
int chored_jobs_exist(jobs *jobs, char *job_name) {
  int i;
  for (i=0; i<JOBS_LIMIT; ++i) {
    job *local_job = &jobs->jobs[i];
    char *name = local_job->name;
    if ((strncmp(name, job_name, 255)) == 0) {
      return 0;
    }
  }
  return 1;
}

/* search a job_name into jobs data structure.
 */
job* chored_jobs_search(jobs *jobs, char *job_name) {
  job *j = NULL;
  return j;
}

/* delete a job from jobs strut
 */
int chored_jobs_del(jobs *jobs, char *job_name) {
  return 0;
}

/* check if all jobs are active
 */
int chored_jobs_check(jobs *jobs) {
  return 0;
}
