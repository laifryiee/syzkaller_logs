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

#define BITMASK(bf_off, bf_len) (((1ull << (bf_len)) - 1) << (bf_off))
#define STORE_BY_BITMASK(type, htobe, addr, val, bf_off, bf_len)               \
  *(type*)(addr) =                                                             \
      htobe((htobe(*(type*)(addr)) & ~BITMASK((bf_off), (bf_len))) |           \
            (((type)(val) << (bf_off)) & BITMASK((bf_off), (bf_len))))

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

void execute_one(void)
{
  *(uint32_t*)0x20002240 = 2;
  *(uint32_t*)0x20002244 = 0x80;
  *(uint8_t*)0x20002248 = 1;
  *(uint8_t*)0x20002249 = 0;
  *(uint8_t*)0x2000224a = 0;
  *(uint8_t*)0x2000224b = 0;
  *(uint32_t*)0x2000224c = 0;
  *(uint64_t*)0x20002250 = 0;
  *(uint64_t*)0x20002258 = 0;
  *(uint64_t*)0x20002260 = 0;
  STORE_BY_BITMASK(uint64_t, , 0x20002268, 0, 0, 1);
  STORE_BY_BITMASK(uint64_t, , 0x20002268, 0, 1, 1);
  STORE_BY_BITMASK(uint64_t, , 0x20002268, 0, 2, 1);
  STORE_BY_BITMASK(uint64_t, , 0x20002268, 0, 3, 1);
  STORE_BY_BITMASK(uint64_t, , 0x20002268, 0, 4, 1);
  STORE_BY_BITMASK(uint64_t, , 0x20002268, 0, 5, 1);
  STORE_BY_BITMASK(uint64_t, , 0x20002268, 0, 6, 1);
  STORE_BY_BITMASK(uint64_t, , 0x20002268, 0, 7, 1);
  STORE_BY_BITMASK(uint64_t, , 0x20002268, 0, 8, 1);
  STORE_BY_BITMASK(uint64_t, , 0x20002268, 0, 9, 1);
  STORE_BY_BITMASK(uint64_t, , 0x20002268, 0, 10, 1);
  STORE_BY_BITMASK(uint64_t, , 0x20002268, 0, 11, 1);
  STORE_BY_BITMASK(uint64_t, , 0x20002268, 0, 12, 1);
  STORE_BY_BITMASK(uint64_t, , 0x20002268, 0, 13, 1);
  STORE_BY_BITMASK(uint64_t, , 0x20002268, 0, 14, 1);
  STORE_BY_BITMASK(uint64_t, , 0x20002268, 0, 15, 2);
  STORE_BY_BITMASK(uint64_t, , 0x20002268, 0, 17, 1);
  STORE_BY_BITMASK(uint64_t, , 0x20002268, 0, 18, 1);
  STORE_BY_BITMASK(uint64_t, , 0x20002268, 0, 19, 1);
  STORE_BY_BITMASK(uint64_t, , 0x20002268, 0, 20, 1);
  STORE_BY_BITMASK(uint64_t, , 0x20002268, 0, 21, 1);
  STORE_BY_BITMASK(uint64_t, , 0x20002268, 0, 22, 1);
  STORE_BY_BITMASK(uint64_t, , 0x20002268, 0, 23, 1);
  STORE_BY_BITMASK(uint64_t, , 0x20002268, 0, 24, 1);
  STORE_BY_BITMASK(uint64_t, , 0x20002268, 0, 25, 1);
  STORE_BY_BITMASK(uint64_t, , 0x20002268, 0, 26, 1);
  STORE_BY_BITMASK(uint64_t, , 0x20002268, 0, 27, 1);
  STORE_BY_BITMASK(uint64_t, , 0x20002268, 0, 28, 1);
  STORE_BY_BITMASK(uint64_t, , 0x20002268, 0, 29, 1);
  STORE_BY_BITMASK(uint64_t, , 0x20002268, 0, 30, 1);
  STORE_BY_BITMASK(uint64_t, , 0x20002268, 0, 31, 1);
  STORE_BY_BITMASK(uint64_t, , 0x20002268, 0, 32, 1);
  STORE_BY_BITMASK(uint64_t, , 0x20002268, 0, 33, 1);
  STORE_BY_BITMASK(uint64_t, , 0x20002268, 0, 34, 1);
  STORE_BY_BITMASK(uint64_t, , 0x20002268, 0, 35, 1);
  STORE_BY_BITMASK(uint64_t, , 0x20002268, 0, 36, 1);
  STORE_BY_BITMASK(uint64_t, , 0x20002268, 0, 37, 1);
  STORE_BY_BITMASK(uint64_t, , 0x20002268, 0, 38, 26);
  *(uint32_t*)0x20002270 = 0;
  *(uint32_t*)0x20002274 = 0;
  *(uint64_t*)0x20002278 = 0;
  *(uint64_t*)0x20002280 = 0;
  *(uint64_t*)0x20002288 = 0x10142;
  *(uint64_t*)0x20002290 = 0x8000000000000000;
  *(uint32_t*)0x20002298 = 0;
  *(uint32_t*)0x2000229c = 0;
  *(uint64_t*)0x200022a0 = 0;
  *(uint32_t*)0x200022a8 = 0;
  *(uint16_t*)0x200022ac = 0;
  *(uint16_t*)0x200022ae = 0;
  *(uint32_t*)0x200022b0 = 0;
  *(uint32_t*)0x200022b4 = 0;
  *(uint64_t*)0x200022b8 = 1;
  syscall(__NR_perf_event_open, /*attr=*/0x20002240ul, /*pid=*/0, /*cpu=*/0ul,
          /*group=*/-1, /*flags=*/0ul);
}
int main(void)
{
  syscall(__NR_mmap, /*addr=*/0x1ffff000ul, /*len=*/0x1000ul, /*prot=*/0ul,
          /*flags=MAP_FIXED|MAP_ANONYMOUS|MAP_PRIVATE*/ 0x32ul, /*fd=*/-1,
          /*offset=*/0ul);
  syscall(__NR_mmap, /*addr=*/0x20000000ul, /*len=*/0x1000000ul,
          /*prot=PROT_WRITE|PROT_READ|PROT_EXEC*/ 7ul,
          /*flags=MAP_FIXED|MAP_ANONYMOUS|MAP_PRIVATE*/ 0x32ul, /*fd=*/-1,
          /*offset=*/0ul);
  syscall(__NR_mmap, /*addr=*/0x21000000ul, /*len=*/0x1000ul, /*prot=*/0ul,
          /*flags=MAP_FIXED|MAP_ANONYMOUS|MAP_PRIVATE*/ 0x32ul, /*fd=*/-1,
          /*offset=*/0ul);
  loop();
  return 0;
}
