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

#ifndef __NR_bpf
#define __NR_bpf 321
#endif

static unsigned long long procid;

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

uint64_t r[2] = {0xffffffffffffffff, 0xffffffffffffffff};

void execute_one(void)
{
  intptr_t res = 0;
  *(uint32_t*)0x200007c0 = 0x1b;
  *(uint32_t*)0x200007c4 = 0;
  *(uint32_t*)0x200007c8 = 0;
  *(uint32_t*)0x200007cc = 0x40000;
  *(uint32_t*)0x200007d0 = 0;
  *(uint32_t*)0x200007d4 = 0;
  *(uint32_t*)0x200007d8 = 0;
  memset((void*)0x200007dc, 0, 16);
  *(uint32_t*)0x200007ec = 0;
  *(uint32_t*)0x200007f0 = 0;
  *(uint32_t*)0x200007f4 = 0;
  *(uint32_t*)0x200007f8 = 0;
  *(uint32_t*)0x200007fc = 0;
  *(uint64_t*)0x20000800 = 0;
  res = syscall(__NR_bpf, /*cmd=*/0ul, /*arg=*/0x200007c0ul, /*size=*/0x48ul);
  if (res != -1)
    r[0] = res;
  *(uint32_t*)0x20000280 = 0x18;
  *(uint32_t*)0x20000284 = 0xf;
  *(uint64_t*)0x20000288 = 0x20000200;
  *(uint8_t*)0x20000200 = 0x18;
  STORE_BY_BITMASK(uint8_t, , 0x20000201, 0, 0, 4);
  STORE_BY_BITMASK(uint8_t, , 0x20000201, 0, 4, 4);
  *(uint16_t*)0x20000202 = 0;
  *(uint32_t*)0x20000204 = 0;
  *(uint8_t*)0x20000208 = 0;
  *(uint8_t*)0x20000209 = 0;
  *(uint16_t*)0x2000020a = 0;
  *(uint32_t*)0x2000020c = 0;
  *(uint8_t*)0x20000210 = 0x18;
  STORE_BY_BITMASK(uint8_t, , 0x20000211, 1, 0, 4);
  STORE_BY_BITMASK(uint8_t, , 0x20000211, 1, 4, 4);
  *(uint16_t*)0x20000212 = 0;
  *(uint32_t*)0x20000214 = r[0];
  *(uint8_t*)0x20000218 = 0;
  *(uint8_t*)0x20000219 = 0;
  *(uint16_t*)0x2000021a = 0;
  *(uint32_t*)0x2000021c = 0;
  STORE_BY_BITMASK(uint8_t, , 0x20000220, 7, 0, 3);
  STORE_BY_BITMASK(uint8_t, , 0x20000220, 0, 3, 1);
  STORE_BY_BITMASK(uint8_t, , 0x20000220, 0xb, 4, 4);
  STORE_BY_BITMASK(uint8_t, , 0x20000221, 2, 0, 4);
  STORE_BY_BITMASK(uint8_t, , 0x20000221, 0, 4, 4);
  *(uint16_t*)0x20000222 = 0;
  *(uint32_t*)0x20000224 = 0x14;
  STORE_BY_BITMASK(uint8_t, , 0x20000228, 7, 0, 3);
  STORE_BY_BITMASK(uint8_t, , 0x20000228, 0, 3, 1);
  STORE_BY_BITMASK(uint8_t, , 0x20000228, 0xb, 4, 4);
  STORE_BY_BITMASK(uint8_t, , 0x20000229, 3, 0, 4);
  STORE_BY_BITMASK(uint8_t, , 0x20000229, 0, 4, 4);
  *(uint16_t*)0x2000022a = 0;
  *(uint32_t*)0x2000022c = 0;
  *(uint8_t*)0x20000230 = 0x85;
  *(uint8_t*)0x20000231 = 0;
  *(uint16_t*)0x20000232 = 0;
  *(uint32_t*)0x20000234 = 0x83;
  STORE_BY_BITMASK(uint8_t, , 0x20000238, 7, 0, 3);
  STORE_BY_BITMASK(uint8_t, , 0x20000238, 1, 3, 1);
  STORE_BY_BITMASK(uint8_t, , 0x20000238, 0xb, 4, 4);
  STORE_BY_BITMASK(uint8_t, , 0x20000239, 9, 0, 4);
  STORE_BY_BITMASK(uint8_t, , 0x20000239, 0, 4, 4);
  *(uint16_t*)0x2000023a = 0;
  *(uint32_t*)0x2000023c = 0;
  STORE_BY_BITMASK(uint8_t, , 0x20000240, 5, 0, 3);
  STORE_BY_BITMASK(uint8_t, , 0x20000240, 0, 3, 1);
  STORE_BY_BITMASK(uint8_t, , 0x20000240, 5, 4, 4);
  STORE_BY_BITMASK(uint8_t, , 0x20000241, 9, 0, 4);
  STORE_BY_BITMASK(uint8_t, , 0x20000241, 0, 4, 4);
  *(uint16_t*)0x20000242 = 1;
  *(uint32_t*)0x20000244 = 0;
  *(uint8_t*)0x20000248 = 0x95;
  *(uint8_t*)0x20000249 = 0;
  *(uint16_t*)0x2000024a = 0;
  *(uint32_t*)0x2000024c = 0;
  STORE_BY_BITMASK(uint8_t, , 0x20000250, 7, 0, 3);
  STORE_BY_BITMASK(uint8_t, , 0x20000250, 1, 3, 1);
  STORE_BY_BITMASK(uint8_t, , 0x20000250, 0xb, 4, 4);
  STORE_BY_BITMASK(uint8_t, , 0x20000251, 1, 0, 4);
  STORE_BY_BITMASK(uint8_t, , 0x20000251, 9, 4, 4);
  *(uint16_t*)0x20000252 = 0;
  *(uint32_t*)0x20000254 = 0;
  STORE_BY_BITMASK(uint8_t, , 0x20000258, 7, 0, 3);
  STORE_BY_BITMASK(uint8_t, , 0x20000258, 0, 3, 1);
  STORE_BY_BITMASK(uint8_t, , 0x20000258, 0xb, 4, 4);
  STORE_BY_BITMASK(uint8_t, , 0x20000259, 2, 0, 4);
  STORE_BY_BITMASK(uint8_t, , 0x20000259, 0, 4, 4);
  *(uint16_t*)0x2000025a = 0;
  *(uint32_t*)0x2000025c = 0;
  *(uint8_t*)0x20000260 = 0x85;
  *(uint8_t*)0x20000261 = 0;
  *(uint16_t*)0x20000262 = 0;
  *(uint32_t*)0x20000264 = 0x84;
  STORE_BY_BITMASK(uint8_t, , 0x20000268, 7, 0, 3);
  STORE_BY_BITMASK(uint8_t, , 0x20000268, 0, 3, 1);
  STORE_BY_BITMASK(uint8_t, , 0x20000268, 0xb, 4, 4);
  STORE_BY_BITMASK(uint8_t, , 0x20000269, 0, 0, 4);
  STORE_BY_BITMASK(uint8_t, , 0x20000269, 0, 4, 4);
  *(uint16_t*)0x2000026a = 0;
  *(uint32_t*)0x2000026c = 0;
  *(uint8_t*)0x20000270 = 0x95;
  *(uint8_t*)0x20000271 = 0;
  *(uint16_t*)0x20000272 = 0;
  *(uint32_t*)0x20000274 = 0;
  *(uint64_t*)0x20000290 = 0x200001c0;
  memcpy((void*)0x200001c0, "GPL\000", 4);
  *(uint32_t*)0x20000298 = 0;
  *(uint32_t*)0x2000029c = 0;
  *(uint64_t*)0x200002a0 = 0;
  *(uint32_t*)0x200002a8 = 0;
  *(uint32_t*)0x200002ac = 0;
  memset((void*)0x200002b0, 0, 16);
  *(uint32_t*)0x200002c0 = 0;
  *(uint32_t*)0x200002c4 = 0;
  *(uint32_t*)0x200002c8 = -1;
  *(uint32_t*)0x200002cc = 8;
  *(uint64_t*)0x200002d0 = 0;
  *(uint32_t*)0x200002d8 = 0;
  *(uint32_t*)0x200002dc = 0x10;
  *(uint64_t*)0x200002e0 = 0;
  *(uint32_t*)0x200002e8 = 0;
  *(uint32_t*)0x200002ec = 0;
  *(uint32_t*)0x200002f0 = 0;
  *(uint32_t*)0x200002f4 = 0;
  *(uint64_t*)0x200002f8 = 0;
  *(uint64_t*)0x20000300 = 0;
  *(uint32_t*)0x20000308 = 0x10;
  *(uint32_t*)0x2000030c = 0;
  res = syscall(__NR_bpf, /*cmd=*/5ul, /*arg=*/0x20000280ul, /*size=*/0x90ul);
  if (res != -1)
    r[1] = res;
  *(uint64_t*)0x200000c0 = 0x20000000;
  memcpy((void*)0x20000000, "contention_end\000", 15);
  *(uint32_t*)0x200000c8 = r[1];
  syscall(__NR_bpf, /*cmd=*/0x11ul, /*arg=*/0x200000c0ul, /*size=*/0x10ul);
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
  for (procid = 0; procid < 8; procid++) {
    if (fork() == 0) {
      loop();
    }
  }
  sleep(1000000);
  return 0;
}
