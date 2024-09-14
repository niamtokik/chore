# chore

WARNING: This project is unstable and should not be used in
production.

A simple project to manage jobs in pure C. The idea is using screen or
tmux all the time is not the solution but it is quite important to
have a way to deal with long running jobs.

The reason of this software is really simple. When starting a long
running job on systems with ansible, salt or chef, it's always
complicated to follow its state. `cron` and `at` are not also giving
the hability to know exactly what happened with this jobs, and using
`systemd` or other application like this one is not portable when you
are dealing with different operating systems.

`chored` and `chore` want to offer a simple way to deal with this
problem.

## Usage

`chore` gives access to two commands, `chored`, a daemon used to keep
job states on the system, and `chore`, the command used to manage
`chored`.

Start jobs daemon.

```sh
chored
```

Add a new job.

```sh
chore -- ${command}
```

### `chored` flags

| version | state  | flag | value    | notes |
|---------|--------|------|----------|-------|
| 0.1.0   | stable | `-v` |          | print `chored` version
| 0.1.0   | stable | `-h` |          | print `chored` help
| -       | wip    | `-H` |          | return `chored` manpage
| -       | wip    | `-n` | `str[n]` | set `chored` session name
| -       | wip    | `-d` |          | set `chored` in debug mode
| -       | wip    | `-f` |          | put `chored` in foreground
| -       | wip    | `-p` | `str[p]` | set `chored` configuration path
| -       | wip    | `-F` |          | force start `chored

- `str[n]`: `^[0-9a-zA-Z_]{1,63}$`
- `str[p]`: standard unix path

### `chore` flags

| version | state  | flag | value    | notes |
|---------|--------|------|----------|-------|
| 0.1.0   | wip    | `-v` |          | print `chore` version
| 0.1.0   | wip    | `-h` |          | print `chore` help
| -       | wip    | `-H` |          | return `chore` manpage
| -       | wip    | `-d` |          | switch to debug mode
| -       | wip    | `-j` | `str[j]` | set job name also called job id
| -       | wip    | `-n` | `str[n]` | set `chored` session name
| -       | wip    | `-e` | `str[e]` | reset environment variables and set variables
| -       | wip    | `-l` |          | list current jobs
| -       | wip    | `-s` |          | list job state (require `-j`)
| -       | wip    | `-S` |          | list job statistics (require `-j`)
| -       | wip    | `-D` | `str[D]` | set a date to execute
| -       | wip    | `-t` |          | terminate a job with SIGTERM (require `-j`)
| -       | wip    | `-i` | `str[i]` | send input from files or stdin to stdin's process (require `-j`)
| -       | wip    | `-o` |          | redirect stdout's process to stdout (require `-j`)
| -       | wip    | `-k` | `int[k]` | send a signal to job (require `-j`)
| -       | wip    | `-T` | `int[T]` | set job timeout in seconds (no timeout by default)
| -       | wip    | `-r` | `str[r]` | set a pattern to react. read line by line or truncate long buffer to 255 chars.
| -       | wip    | `-R` | `str[R]` | set an action when a pattern is found (require `-r`)
| -       | wip    | `-x` |          | restart automatically the job in case of failure
| -       | wip    | `--` | `str[-]` | all characters after `--` until carriage retun are considered part of the command

- `str[j]`: `^[0-9a-zA-Z_]{1,63}$`
- `str[n]`: `^[0-9a-zA-Z_]{1,63}$`
- `str[e]`: to be defined
- `str[D]`: iso8601
- `str[i]`: standard unix path or `-` (from stdin)
- `str[k]`: `^[0-9]{1,2}$` (valid unix signal)
- `str[T]`: `^[0-9]+$`
- `str[r]`: regexp
- `str[R]`: `^(none|log|nolog|reload|terminate|kill|restart|deps|state|stats)$`
  - `none`: default behavior, do nothing
  - `log`: start logging stdout and stderr to log file
  - `nolog`: stop logging stdout and stderr to log file
  - `reload`: send sighup signal
  - `terminate`: send sigterm signal
  - `kill`: send sigkill signal
  - `restart`: terminate, wait and restart the job
  - `deps`: execute job dependencies
  - `state`: log job state in log file
  - `stats`: log job statistics in log file
- `str[-]`: `^[[:print]]+$`

## Build

```sh
make
```

## Test

```sh
make test
```

## Benchmark

```sh
make benchmark
```

## FAQ

### How to print help?

```sh
chored -h
chore -h
```

### How to print the version?

```sh
chored -v
chore -v
```

### How to start `chored` daemon?

state: todo

`chored` can be started by simply invoking `chored` command. It will
then use the current user/group.

```sh
chored
```

### How to start another `chored` daemon?

state: todo

The default `chored` session is called `chored`, pid file is stored in
`${HOME}/.config/chored/run/${chored_name}.pid` and socket is stored
in `${HOME}/.config/chored/sockets/${chored_name}.pid`.

```sh
chored -n ${chored_name}
```

### How to add a new job?

state: todo

A new job can be added using `chore` command. A job name can
eventually be configured using `-j` flag, if not set, a randomly
generated name is produced using the content of the command.

```sh
job=test
command=test
chore -j ${job_name} -- ${command}
```

### How to add a new job on another `chored` sessions?

state: todo

When running multiple session, one can start jobs on another `chored`
using `-n` flag.

```sh
session=test
job=test
command=test
chore -n ${session} -j ${job_name} -- ${command}
```

### How to add a new job with custom environment?

state: todo

To reset whole environment variables (except `HOME` and `PATH`).

```sh
job=test
command=test
chore -j ${job_name} -e '' -- ${command}
```

To reset whole environment and configure custom variables.

```sh
job=test
command=test
env="test=1 data=2 p=3"
chore -j ${job_name} -e "${env}" -- ${command}
```

### How to list jobs?

state: todo

The list of managed jobs can be displayed using `-l` jobs.

```sh
chore -l
```

Here an output example returned by `chore`:

```
${job_name} ${pid} ${start_time} ${state} ${command}
```

### How to get job state?

state: todo

One can use `ps` command to list those information, but to make things
easier, `chore` can output all these information returned as a list of
named item.

```sh
chore -j ${job_name} -s
```

```
name: ${job_name}
pid: ${pid}
start_time: ${start_time}
state: ${state}
command: ${command}
%cpu: ${%cpu}
%mem: ${%mem}
nice: ${nice_value}
priority: ${priority}
```

### How to get job stats?

state: todo

Job stats returns information since the job started.

```sh
chore -j ${job_name} -S
```

### How to schedule a new job?

state: todo

By default, `chore` used `-d now` but it can be configured using
ISO8601 format.

```sh
job=happy_new_year
date="2025-01-01T00:00:00Z"
command="printf happy new year"
chore -j ${job_name} -d ${date} -- ${command}
```

### Where logs are being stored?

state: todo

By default, `chored` stores logs in
`${HOME}/.config/chore/logs/chored.log`

### How to list jobs?

state: todo

```sh
chore -l -p my_own_chore
```

### How to get job `STDOUT`?

state: todo

By default, `STDOUT` is redirected to `/dev/null` but it can be
forwarded to `STDOUT` on demand.

```sh
chore -j ${job_name} -o
```

### How to send inputs to job `STDIN`?

state: todo

```sh
chore -j ${job_name}  -i file.txt
# or
echo "test" | chore -j ${job_name} -i-
# or
chore -j ${job_name} << EOF
test
EOF
```

### How to terminate a job?

state: todo

```sh
chore -j ${job_name} -t
```

### How to kill a job?

state: todo

```sh
chore -j ${job_name} -k
# or
chore -j ${job_name} -k9
```

### What happened when a job quit?

state: todo

`chored` will keep states of this job until someone asked for it. For
example, if one command started and died, then if someone is getting
its state, it will be removed from `chored` memory. If state
information needs to be stored until the end of execution of `chored`,
then the flag `-k` must be used when starting a new job.

```sh
job=test
command=test
chore -j ${job_name} -k -- ${command}
```

### What about zombies?

state: todo

At this time, no solution has been found to deal with zombies
processes.

### How to react on job `STDOUT`?

state: todo

`chored` can catch pattern from `STDOUT` application and react on them
when a line is matching a regexp. `-r` flag defines a regexp and `-R`
defines the action to do. At this time only `log` and `unlog` are
supported.

```sh
chore -j ${job_name} -r '^start' -R log -r '^stop' -R unlog
```

List of reactions are available in process stats.

```
react_regex_0: ^start
react_action_0: log
react_regex_1: ^stop
react_action_1: unlog
```

To remove them

```
chore -j ${job_name} -r '' -R drop
```

### Is it possible to create a dependent job?

state: todo

Yes. When a job ends, another one can be started if the previous one
was successful (returned 0 code).

```sh
chore -j ${job_name} -- sleep 10
chore -j ${job_name} -d ${job_name} -- printf another test
```

In the code below, when the first job has returned, the next one is
directly executed.

### What about privilege separation?

`chored` can use `sudo` or `doas` commands if needed, but its role is
not to be executed as root user. In fact, if one wants to execute
privileged command with an unprivileged user, a new system user called
`_chored` can be created with no rights and privilege. Then `sudo` and
`doas` commands can be configured using this specific user.

### Which OS are supported by `chore`?

state: todo

`chore` is a POSIX projects using C99 standard for compatibility and
portability with other systems. It should work on those OSes:

 - [ ] OpenBSD
 - [ ] Linux
 - [ ] FreeBSD
 - [ ] NetBSD
 - [ ] DragonFlyBSD
 - [ ] MacOS
 - [ ] Minix

### Where can I download a release?

state: todo

One and only one static executable can be downloaded on Github release
page. This application embeds `chored` and `chore` commands. It can be
deployed by copying this file in `/usr/local/bin` and creating a
symlink.

```sh
# download latest release
curl ${release}/chored -o chored
curl ${release}/chored.sha256 -o chored
curl ${release}/chored.gpg -o chored

# check if chored is valid using sha256, openssl,
# sha256sum or gpg.

# copy release in bin directory
doas cp chored /usr/local/bin/chored
doas chmod +x /usr/local/bin/chored
doas ln -s /usr/local/bin/chored /usr/local/bin/chore
```

### How to have the documentation?

state: todo

Man pages are stored in the static executable and can be extracted
using the following command:

```sh
chored -H
chore -H
```

Man pages for `chored` and `chore` are also available from Github
release page.

```sh
curl ${release}/chored.8 -o chored.8
curl ${release}/chored.8 -o chored.8.sha256
doas cp chored.8 /usr/local/man/man8

curl ${release}/chore.8 -o chore.8
curl ${release}/chore.8 -o chore.8.sha256
doas cp chore.8 /usr/local/man/man8
```

### Can I use crontab format to define jobs?

state: todo

No. The format is quite similar thought and it will possible to make
it compatible with
[`crontab(5)`](https://man.openbsd.org/man5/crontab.5).

```sh
# here the format
${year} ${month} ${day} ${hour} ${minute} ${second} ${flags} ${command}

# start a job at this specific time
2025 01 01 00 00 00 -j newyear -- echo happy new year!

# start a job right now
* * * * * * my command to execute

# cron compatibility
cron 0 0 * * * my command to execute
```

It will be necessary to define a config file as wel, probably in
`${HOME}/.config/chore/choretab`. To reload it during execution:

```sh
pkill -HUP chored
```

In case of error, nothing is loaded, but chored will log the issue and
keep the previous configuration.

### Is there job limitation?

state: todo

Yes. During the design phase it was a requirement to avoid heap
allocation (malloc) and use only the stack provided by the operating
system.

### What about the license?

[ISC License](https://en.wikipedia.org/wiki/ISC_license), [OpenBSD
model](https://en.wikipedia.org/wiki/ISC_license#OpenBSD_license). You
can do whatever you want with this project, that's a gift.

```
Copyright (c) 2024 Mathieu Kerjouan

Permission to use, copy, modify, and distribute this software for any
purpose with or without fee is hereby granted, provided that the above
copyright notice and this permission notice appear in all copies.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
```

see: https://www.tldrlegal.com/license/isc-license

### Where can I found developer documentation?

[DESIGN.md](./DESIGN.md) file contains all information regarding
constraints and choices made. A FAQ section for developers is also
available.

## References and References

[OpenBSD cron(8)](https://github.com/openbsd/src/tree/master/usr.sbin/cron)
