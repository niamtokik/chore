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

int chored_check_dir(char *home, char *path) {
  char local_home[255];
  bzero(local_home, 255);
  char local_path[255];
  bzero(local_path, 255);
  char full_path[510];
  bzero(full_path, 510);
  struct stat tmp = {};

  strlcpy(local_home, home, 255);
  strlcpy(local_path, path, 255);
  strlcat(full_path, local_home, 510);
  strlcat(full_path, local_path, 510);

  if ((stat(full_path, &tmp)) == ENOENT) {
    printf("debug: creates %s\n", full_path);
    mkdir(full_path, S_IRWXU);
    return 1;
  }
  return 0;
}
