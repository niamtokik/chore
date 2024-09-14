# chore

A simple project to manage jobs in pure C. The idea is using screen or
tmux all the time is not the solution but it is quite important to
have a way to deal with long running jobs.

`chore` acts as a daemon running with the current user. Every users
can run one or many `chore` daemon, they are identified with their
pid, stored by default in `${HOME}/.config/chore/chore.pid`.

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

## Build

```sh
make
```

## Test

```sh
make test
```

## FAQ

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

`chore` is a POSIX projects using standard C89 instruction. It should
work on those systems:

 - [ ] OpenBSD
 - [ ] Linux
 - [ ] FreeBSD
 - [ ] NetBSD
 - [ ] DragonFlyBSD

## References and References
