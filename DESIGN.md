# Design and Development Guide

A schema is generally more easy to understand than a long speech. The
following drawing describe the role of the different bricks involved
in chore/chored system.

```
            [client]
   ________/
  |        |
  | chore  |
  |________|
      ||
      || unix socket
      ||
     _||_                 [children]                    [children]
   __\__/__              /______________               /__________
  |        |            |               |             |           |
  | chored |---[pipe]-->| chored_worker |---[stdin]-->| job       |
  |        |<--[pipe]---|               |<--[stdout]--| (command) |
  |________|            |_______________|<--[stderr]--|___________|
          /                  ||
  [daemon]                  _||_
                          __\  /_ 
                         |       \
                         |        |
                         | logs   |
                         |        |
                         |________|
```

When `chored` is started, it will initialize its environment by
creating required directories and files.

When a new job is started, `chored` spawns a new `chored_worker` for
every new job. Two pipes are opened between `chored` and
`chored_worker`.

`chored_worker` is in charge of the job to execute and can control
STDIN/STDOUT/STDERR (STDERR should always be appended to logs). 

When the job dies, `chored_worker` sends the return code to `chored`,
and closes all its file descriptor.

## Constraints

 1. **small**. This application MUST BE optimized for size, and SHOULD
    USE only required libraries.
    
 2. **portable**. This application SHOULD RUN on every Unix/Posix
    systems. If possible it COULD BE designed like an embedded app.
    
 3. **light**. This application should use a deterministic amount of
    memory. To accomplish that, strict limits must be imposed during
    compile time. For example, a relase can be compiled to only
    support 1 job.
    
 4. **stack first**. This is a bonus constraint. If light enough, the
    release SHOULD USE the stack instead of the heap.
    
 5. **secure**. This application MUST FOLLOW OpenBSD design principle
    and all best practice. If possible, when compiled for another
    operating system, it SHOULD USE local framework to make the
    application safer to use.
    
 6. **documented**. All part of the code SHOULD HAVE its
    documentation. The whole applicatoin MUST BE documented and offers
    man pages.

## Libraries

## Data structures

## Protocols

## States

### `chored` state

### `chored_worker` state

## Procedures

### `chored`

1. `chored_init`

  1. create environment
  2. initialize data structures

2. `chored_loop`

  1. check if `worker[i]` is here
  2. send ping to `worker[i]`
  3. receive ping from `worker[i]`
  4. send command to `worker[i]` (if defined)
  5. receive command result from `worker[i]`
  
3. `chored_terminate`

  1. send terminate command to all workers
  2. wait until all workers are being stopped
  3. close all file descriptors
  4. exit with specific code

### File management

| type      | path | note |
|-----------|------|------|
| directory | `${HOME}/.config/chore` | main directory
| directory | `${HOME}/.config/chore/run` | chored sessions directory
| file      | `${HOME}/.config/chore/run/${session}.pid` | chored session pid file
| unix sock | `${HOME}/.config/chore/run/${session}.sock` | chored session unix sock file
| file      | `${HOME}/.config/chore/cache/${session}/jobs/${job_name}-${date}.pid` | job pid
| file      | `${HOME}/.config/chore/cache/${session}/jobs/${job_name}-${date}.debug` | job debug (data structure dump)
| fifo      | `${HOME}/.config/chore/cache/${session}/jobs/${job_name}-${date}.stdin` | job stdin fifo (disabled by default)
| file      | `${HOME}/.config/chore/cache/${session}/jobs/${job_name}-${date}.stdout` | job stdout log file
| file      | `${HOME}/.config/chore/cache/${session}/jobs/${job_name}-${date}.stderr` | job stderr log file

## Memory view

## Operating Systems Specificities

### OpenBSD

### Linux

### FreeBSD

### NetBSD

### DragonFlyBSD

### MacOS

### Minix

## FAQ

### What is the versionning format used?

```
Major.Minor.Bugfix
```

### What was inspired from?

Mainly OpenBSD [`cron(8)`](https://man.openbsd.org/cron) daemon and by
extension [`at(1)`](https://man.openbsd.org/at.1) but also
[Hashicorp Nomad](https://www.nomadproject.io/).

## References and Resources
