// autogenerated by syzkaller (https://github.com/google/syzkaller)

#define _GNU_SOURCE

#include <dirent.h>
#include <endian.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/prctl.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

static void sleep_ms(uint64_t ms)
{
  usleep(ms * 1000);
}

static uint64_t current_time_ms(void)
{
  struct timespec ts;
  if (clock_gettime(CLOCK_MONOTONIC, &ts))
    exit(1);
  return (uint64_t)ts.tv_sec * 1000 + (uint64_t)ts.tv_nsec / 1000000;
}

static bool write_file(const char* file, const char* what, ...)
{
  char buf[1024];
  va_list args;
  va_start(args, what);
  vsnprintf(buf, sizeof(buf), what, args);
  va_end(args);
  buf[sizeof(buf) - 1] = 0;
  int len = strlen(buf);
  int fd = open(file, O_WRONLY | O_CLOEXEC);
  if (fd == -1)
    return false;
  if (write(fd, buf, len) != len) {
    int err = errno;
    close(fd);
    errno = err;
    return false;
  }
  close(fd);
  return true;
}

static void kill_and_wait(int pid, int* status)
{
  kill(-pid, SIGKILL);
  kill(pid, SIGKILL);
  for (int i = 0; i < 100; i++) {
    if (waitpid(-1, status, WNOHANG | __WALL) == pid)
      return;
    usleep(1000);
  }
  DIR* dir = opendir("/sys/fs/fuse/connections");
  if (dir) {
    for (;;) {
      struct dirent* ent = readdir(dir);
      if (!ent)
        break;
      if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0)
        continue;
      char abort[300];
      snprintf(abort, sizeof(abort), "/sys/fs/fuse/connections/%s/abort",
               ent->d_name);
      int fd = open(abort, O_WRONLY);
      if (fd == -1) {
        continue;
      }
      if (write(fd, abort, 1) < 0) {
      }
      close(fd);
    }
    closedir(dir);
  } else {
  }
  while (waitpid(-1, status, __WALL) != pid) {
  }
}

static void setup_test()
{
  prctl(PR_SET_PDEATHSIG, SIGKILL, 0, 0, 0);
  setpgrp();
  write_file("/proc/self/oom_score_adj", "1000");
}

static void execute_one(void);

#define WAIT_FLAGS __WALL

static void loop(void)
{
  int iter = 0;
  for (;; iter++) {
    int pid = fork();
    if (pid < 0)
      exit(1);
    if (pid == 0) {
      setup_test();
      execute_one();
      exit(0);
    }
    int status = 0;
    uint64_t start = current_time_ms();
    for (;;) {
      if (waitpid(-1, &status, WNOHANG | WAIT_FLAGS) == pid)
        break;
      sleep_ms(1);
      if (current_time_ms() - start < 5000)
        continue;
      kill_and_wait(pid, &status);
      break;
    }
  }
}

uint64_t r[4] = {0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff,
                 0xffffffffffffffff};

void execute_one(void)
{
  intptr_t res = 0;
  res = syscall(__NR_socketpair, /*domain=*/1ul, /*type=*/1ul, /*proto=*/0,
                /*fds=*/0x20000000ul);
  if (res != -1) {
    r[0] = *(uint32_t*)0x20000000;
    r[1] = *(uint32_t*)0x20000004;
  }
  res = syscall(__NR_socketpair, /*domain=*/1ul, /*type=*/5ul, /*proto=*/0,
                /*fds=*/0x20000040ul);
  if (res != -1) {
    r[2] = *(uint32_t*)0x20000040;
    r[3] = *(uint32_t*)0x20000044;
  }
  *(uint64_t*)0x20002200 = 0;
  *(uint32_t*)0x20002208 = 0;
  *(uint64_t*)0x20002210 = 0x20002140;
  *(uint64_t*)0x20002140 = 0;
  *(uint64_t*)0x20002148 = 0;
  *(uint64_t*)0x20002150 = 0x20000140;
  memset((void*)0x20000140, 235, 1);
  *(uint64_t*)0x20002158 = 1;
  *(uint64_t*)0x20002218 = 2;
  *(uint64_t*)0x20002220 = 0x20002180;
  *(uint64_t*)0x20002180 = 0x18;
  *(uint32_t*)0x20002188 = 1;
  *(uint32_t*)0x2000218c = 1;
  *(uint32_t*)0x20002190 = r[0];
  *(uint32_t*)0x20002194 = r[2];
  *(uint64_t*)0x20002198 = 0x14;
  *(uint32_t*)0x200021a0 = 1;
  *(uint32_t*)0x200021a4 = 1;
  *(uint32_t*)0x200021a8 = r[0];
  *(uint64_t*)0x200021b0 = 0x18;
  *(uint32_t*)0x200021b8 = 1;
  *(uint32_t*)0x200021bc = 1;
  *(uint32_t*)0x200021c0 = r[1];
  *(uint32_t*)0x200021c4 = r[3];
  *(uint64_t*)0x20002228 = 0x48;
  *(uint32_t*)0x20002230 = 0x800;
  syscall(__NR_sendmsg, /*fd=*/r[0], /*msg=*/0x20002200ul, /*f=*/0x4091ul);
}
int main(void)
{
  syscall(__NR_mmap, /*addr=*/0x1ffff000ul, /*len=*/0x1000ul, /*prot=*/0ul,
          /*flags=*/0x32ul, /*fd=*/-1, /*offset=*/0ul);
  syscall(__NR_mmap, /*addr=*/0x20000000ul, /*len=*/0x1000000ul, /*prot=*/7ul,
          /*flags=*/0x32ul, /*fd=*/-1, /*offset=*/0ul);
  syscall(__NR_mmap, /*addr=*/0x21000000ul, /*len=*/0x1000ul, /*prot=*/0ul,
          /*flags=*/0x32ul, /*fd=*/-1, /*offset=*/0ul);
  loop();
  return 0;
}
