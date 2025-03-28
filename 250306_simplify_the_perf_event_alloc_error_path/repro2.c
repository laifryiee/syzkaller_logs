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
  *(uint32_t*)0x200003c0 = 5;
  *(uint32_t*)0x200003c4 = 0x80;
  *(uint8_t*)0x200003c8 = 0;
  *(uint8_t*)0x200003c9 = 0;
  *(uint8_t*)0x200003ca = 0;
  *(uint8_t*)0x200003cb = 0;
  *(uint32_t*)0x200003cc = 0;
  *(uint64_t*)0x200003d0 = 0;
  *(uint64_t*)0x200003d8 = 0;
  *(uint64_t*)0x200003e0 = 0;
  STORE_BY_BITMASK(uint64_t, , 0x200003e8, 0, 0, 1);
  STORE_BY_BITMASK(uint64_t, , 0x200003e8, 0, 1, 1);
  STORE_BY_BITMASK(uint64_t, , 0x200003e8, 0, 2, 1);
  STORE_BY_BITMASK(uint64_t, , 0x200003e8, 0, 3, 1);
  STORE_BY_BITMASK(uint64_t, , 0x200003e8, 0, 4, 1);
  STORE_BY_BITMASK(uint64_t, , 0x200003e8, 0, 5, 1);
  STORE_BY_BITMASK(uint64_t, , 0x200003e8, 0, 6, 1);
  STORE_BY_BITMASK(uint64_t, , 0x200003e8, 0, 7, 1);
  STORE_BY_BITMASK(uint64_t, , 0x200003e8, 0, 8, 1);
  STORE_BY_BITMASK(uint64_t, , 0x200003e8, 0, 9, 1);
  STORE_BY_BITMASK(uint64_t, , 0x200003e8, 0, 10, 1);
  STORE_BY_BITMASK(uint64_t, , 0x200003e8, 0, 11, 1);
  STORE_BY_BITMASK(uint64_t, , 0x200003e8, 0, 12, 1);
  STORE_BY_BITMASK(uint64_t, , 0x200003e8, 0, 13, 1);
  STORE_BY_BITMASK(uint64_t, , 0x200003e8, 0, 14, 1);
  STORE_BY_BITMASK(uint64_t, , 0x200003e8, 0, 15, 2);
  STORE_BY_BITMASK(uint64_t, , 0x200003e8, 0, 17, 1);
  STORE_BY_BITMASK(uint64_t, , 0x200003e8, 0, 18, 1);
  STORE_BY_BITMASK(uint64_t, , 0x200003e8, 0, 19, 1);
  STORE_BY_BITMASK(uint64_t, , 0x200003e8, 0, 20, 1);
  STORE_BY_BITMASK(uint64_t, , 0x200003e8, 0, 21, 1);
  STORE_BY_BITMASK(uint64_t, , 0x200003e8, 0, 22, 1);
  STORE_BY_BITMASK(uint64_t, , 0x200003e8, 0, 23, 1);
  STORE_BY_BITMASK(uint64_t, , 0x200003e8, 0, 24, 1);
  STORE_BY_BITMASK(uint64_t, , 0x200003e8, 0, 25, 1);
  STORE_BY_BITMASK(uint64_t, , 0x200003e8, 0, 26, 1);
  STORE_BY_BITMASK(uint64_t, , 0x200003e8, 0, 27, 1);
  STORE_BY_BITMASK(uint64_t, , 0x200003e8, 0, 28, 1);
  STORE_BY_BITMASK(uint64_t, , 0x200003e8, 0, 29, 1);
  STORE_BY_BITMASK(uint64_t, , 0x200003e8, 0, 30, 1);
  STORE_BY_BITMASK(uint64_t, , 0x200003e8, 0, 31, 1);
  STORE_BY_BITMASK(uint64_t, , 0x200003e8, 0, 32, 1);
  STORE_BY_BITMASK(uint64_t, , 0x200003e8, 0, 33, 1);
  STORE_BY_BITMASK(uint64_t, , 0x200003e8, 0, 34, 1);
  STORE_BY_BITMASK(uint64_t, , 0x200003e8, 0, 35, 1);
  STORE_BY_BITMASK(uint64_t, , 0x200003e8, 0, 36, 1);
  STORE_BY_BITMASK(uint64_t, , 0x200003e8, 0, 37, 1);
  STORE_BY_BITMASK(uint64_t, , 0x200003e8, 0, 38, 26);
  *(uint32_t*)0x200003f0 = 0;
  *(uint32_t*)0x200003f4 = 4;
  *(uint64_t*)0x200003f8 = 0;
  *(uint64_t*)0x20000400 = 8;
  *(uint64_t*)0x20000408 = 0;
  *(uint64_t*)0x20000410 = 0;
  *(uint32_t*)0x20000418 = 0;
  *(uint32_t*)0x2000041c = 0;
  *(uint64_t*)0x20000420 = 0xfffffffffffffffd;
  *(uint32_t*)0x20000428 = 0;
  *(uint16_t*)0x2000042c = 0;
  *(uint16_t*)0x2000042e = 0;
  *(uint32_t*)0x20000430 = 0;
  *(uint32_t*)0x20000434 = 0;
  *(uint64_t*)0x20000438 = 0;
  syscall(__NR_perf_event_open, /*attr=*/0x200003c0ul, /*pid=*/-1, /*cpu=*/0ul,
          /*group=*/-1, /*flags=*/0ul);
  *(uint32_t*)0x20002ac0 = 5;
  *(uint32_t*)0x20002ac4 = 0x80;
  *(uint8_t*)0x20002ac8 = 0;
  *(uint8_t*)0x20002ac9 = 0;
  *(uint8_t*)0x20002aca = 0;
  *(uint8_t*)0x20002acb = 0;
  *(uint32_t*)0x20002acc = 0;
  *(uint64_t*)0x20002ad0 = 0;
  *(uint64_t*)0x20002ad8 = 0;
  *(uint64_t*)0x20002ae0 = 0;
  STORE_BY_BITMASK(uint64_t, , 0x20002ae8, 0, 0, 1);
  STORE_BY_BITMASK(uint64_t, , 0x20002ae8, 0, 1, 1);
  STORE_BY_BITMASK(uint64_t, , 0x20002ae8, 0, 2, 1);
  STORE_BY_BITMASK(uint64_t, , 0x20002ae8, 0, 3, 1);
  STORE_BY_BITMASK(uint64_t, , 0x20002ae8, 0, 4, 1);
  STORE_BY_BITMASK(uint64_t, , 0x20002ae8, 0, 5, 1);
  STORE_BY_BITMASK(uint64_t, , 0x20002ae8, 0, 6, 1);
  STORE_BY_BITMASK(uint64_t, , 0x20002ae8, 0, 7, 1);
  STORE_BY_BITMASK(uint64_t, , 0x20002ae8, 0, 8, 1);
  STORE_BY_BITMASK(uint64_t, , 0x20002ae8, 0, 9, 1);
  STORE_BY_BITMASK(uint64_t, , 0x20002ae8, 0, 10, 1);
  STORE_BY_BITMASK(uint64_t, , 0x20002ae8, 0, 11, 1);
  STORE_BY_BITMASK(uint64_t, , 0x20002ae8, 0, 12, 1);
  STORE_BY_BITMASK(uint64_t, , 0x20002ae8, 0, 13, 1);
  STORE_BY_BITMASK(uint64_t, , 0x20002ae8, 0, 14, 1);
  STORE_BY_BITMASK(uint64_t, , 0x20002ae8, 0, 15, 2);
  STORE_BY_BITMASK(uint64_t, , 0x20002ae8, 0, 17, 1);
  STORE_BY_BITMASK(uint64_t, , 0x20002ae8, 0, 18, 1);
  STORE_BY_BITMASK(uint64_t, , 0x20002ae8, 0, 19, 1);
  STORE_BY_BITMASK(uint64_t, , 0x20002ae8, 0, 20, 1);
  STORE_BY_BITMASK(uint64_t, , 0x20002ae8, 0, 21, 1);
  STORE_BY_BITMASK(uint64_t, , 0x20002ae8, 0, 22, 1);
  STORE_BY_BITMASK(uint64_t, , 0x20002ae8, 0, 23, 1);
  STORE_BY_BITMASK(uint64_t, , 0x20002ae8, 0, 24, 1);
  STORE_BY_BITMASK(uint64_t, , 0x20002ae8, 0, 25, 1);
  STORE_BY_BITMASK(uint64_t, , 0x20002ae8, 0, 26, 1);
  STORE_BY_BITMASK(uint64_t, , 0x20002ae8, 0, 27, 1);
  STORE_BY_BITMASK(uint64_t, , 0x20002ae8, 0, 28, 1);
  STORE_BY_BITMASK(uint64_t, , 0x20002ae8, 0, 29, 1);
  STORE_BY_BITMASK(uint64_t, , 0x20002ae8, 0, 30, 1);
  STORE_BY_BITMASK(uint64_t, , 0x20002ae8, 0, 31, 1);
  STORE_BY_BITMASK(uint64_t, , 0x20002ae8, 0, 32, 1);
  STORE_BY_BITMASK(uint64_t, , 0x20002ae8, 0, 33, 1);
  STORE_BY_BITMASK(uint64_t, , 0x20002ae8, 0, 34, 1);
  STORE_BY_BITMASK(uint64_t, , 0x20002ae8, 0, 35, 1);
  STORE_BY_BITMASK(uint64_t, , 0x20002ae8, 0, 36, 1);
  STORE_BY_BITMASK(uint64_t, , 0x20002ae8, 0, 37, 1);
  STORE_BY_BITMASK(uint64_t, , 0x20002ae8, 0, 38, 26);
  *(uint32_t*)0x20002af0 = 0;
  *(uint32_t*)0x20002af4 = 4;
  *(uint64_t*)0x20002af8 = 0;
  *(uint64_t*)0x20002b00 = 8;
  *(uint64_t*)0x20002b08 = 0;
  *(uint64_t*)0x20002b10 = 0;
  *(uint32_t*)0x20002b18 = 0;
  *(uint32_t*)0x20002b1c = 0;
  *(uint64_t*)0x20002b20 = 0;
  *(uint32_t*)0x20002b28 = 0;
  *(uint16_t*)0x20002b2c = 0;
  *(uint16_t*)0x20002b2e = 0;
  *(uint32_t*)0x20002b30 = 0;
  *(uint32_t*)0x20002b34 = 0;
  *(uint64_t*)0x20002b38 = 0;
  syscall(__NR_perf_event_open, /*attr=*/0x20002ac0ul, /*pid=*/0, /*cpu=*/0ul,
          /*group=*/-1, /*flags=*/0ul);
  for (int i = 0; i < 32; i++) {
    syscall(__NR_perf_event_open, /*attr=*/0x20002ac0ul, /*pid=*/0, /*cpu=*/0ul,
            /*group=*/-1, /*flags=*/0ul);
  }
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
