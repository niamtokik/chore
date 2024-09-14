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

/* global_jobs variable will contain all jobs managed by the
 * application. It can be availabe everywhere (global variable).
 */
jobs global_jobs = {};


/* print chored usage. */
void chored_usage() {
  printf("Usage: chored [-hv]\n");
}

/* print chored version. */
void chored_version() {
  printf("Version: chored %s\n", CHORE_VERSION);
}

/* chored entry point. */
int chored_main(int argc, char **argv) {
  int hflag, vflag, ch;
  hflag = 0;
  vflag = 0;
  while ((ch = getopt(argc, argv, "hv")) != -1) {
    switch(ch) {
    case 'h':
      hflag = 1;
      break;
    case 'v':
      vflag = 1;
      break;
    default:
      chored_usage();
      break;
    }
  }
  argc -= optind;
  argv += optind;

  if (hflag) {
    chored_usage();
    return 0;
  }
  if (vflag) {
    chored_version();
    return 0;
  }
  chored_init();
  return 0;
}

/* check chored required environment and paths. */
int chored_check() {
  // get home variable and check it
  char *home = NULL;
  if ((home = getenv("HOME")) == NULL) {
    printf("error: can't find HOME variable\n");
    return 1;
  }

  int home_stat_ret;
  struct stat home_stat;
  if ((home_stat_ret = stat(home, &home_stat)) != 0) {
    printf("error %d: %s\n", home_stat_ret, home);
    return 1;
  }

  // check config path
  chored_check_dir(home, "/.config");
  chored_check_dir(home, "/.config/chore");
  chored_check_dir(home, "/.config/chore/run");
  chored_check_dir(home, "/.config/chore/sockets");

  // - check for pid file in /.config/chore/run/chored.pid
  //   if pid == chored pid then stop

  // - check for control socket in /.config/chore/run/chored.socket
  //   if socket == listening then stop

  // - init chored state
  //   - job store
  // 
  
  return 0;
}

/* initialize chored before being started. */
int chored_init() {
  if ((chored_check()) != 1)
    return 1;
  
  if ((chored_jobs_init(&global_jobs)) != 1)
    return 1;
  
  chored_loop(&global_jobs);
  chored_terminate(&global_jobs);
  return 0;
}

/* chored main loop, where all the magic happens. */
int chored_loop(jobs *global_jobs) {
  // job j = {};
  // strcpy(j.name, "test");
  // memcpy(main_jobs.jobs+1, &j, sizeof(j));
  // int r = chored_jobs_exist(&main_jobs, "test");
  return 0;
}

/* chored cleanup function */
int chored_terminate(jobs *global_jobs) {
  return 0;
}
