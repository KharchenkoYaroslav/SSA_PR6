# SSA_PR6

# Технології та запуск

## Як середовище розробки було обрано Docker-контейнер на базі образу `debian:bullseye-slim` з таких причин:

### Прозорість — усі початкові умови для виконання завдання задані в `Dockerfile`, що дозволяє бачити весь процес виконання, а також гарантує стабільність роботи коду.

### Швидкість відтворення початкових умов — Docker-контейнер дозволяє легко змінювати необхідні пакети та конфігурації. Усі зміни можна відкрутити назад за кілька секунд, тоді як у віртуальній машині це займає певний час. Це особливо актуально для завдань, які потребують змін або видалення файлів.

### Зручність розробки — Docker дозволяє швидко змінювати архітектуру, копіювати файли з основної машини та автоматизувати повторювані команди, що значно пришвидшує розробку.

### Варіативність — якщо щось неможливо або складно реалізувати на базі одного образу, завжди можна замінити його на інший.

#### *У завданнях, які неможливо реалізувати як задумано без використання повноцінної системи, буде застосовано `VM`.*

## Запуск

### Всі необхідні команди для запуску контейнерів та виконання файлів описані в `Dockerfile`

# Звіт по завданням

## Завдання (Варіант 22)

### Демонстрація експерименту з великою програмою з помилкою памʼяті

```
root@70abada7b27e:/app# gcc -g task.c -o task -lm
root@70abada7b27e:/app# gcc -g -fsanitize=address task.c -o task_asan
root@70abada7b27e:/app# valgrind ./task
==17== Memcheck, a memory error detector
==17== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==17== Using Valgrind-3.16.1 and LibVEX; rerun with -h for copyright info
==17== Command: ./task
==17==
==17== Invalid write of size 4
==17==    at 0x1091E6: main (task.c:18)
==17==  Address 0x4df2940 is 0 bytes after a block of size 4,000,000 alloc'd
==17==    at 0x483877F: malloc (vg_replace_malloc.c:307)
==17==    by 0x1091A5: main (task.c:11)
==17==
Sorted first element: 1210
==17== 
==17== HEAP SUMMARY:
==17==     in use at exit: 0 bytes in 0 blocks
==17==   total heap usage: 3 allocs, 3 frees, 8,001,024 bytes allocated
==17==
==17== All heap blocks were freed -- no leaks are possible
==17==
==17== For lists of detected and suppressed errors, rerun with: -s
==17== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
root@70abada7b27e:/app# ./task_asan
=================================================================
==18==ERROR: AddressSanitizer: heap-buffer-overflow on address 0x7f74154ff100 at pc 0x55a70de8332a bp 0x7ffe075b8de0 sp 0x7ffe075b8dd8
WRITE of size 4 at 0x7f74154ff100 thread T0
    #0 0x55a70de83329 in main /app/task.c:18
    #1 0x7f7418a7ed79 in __libc_start_main ../csu/libc-start.c:308
    #2 0x55a70de83119 in _start (/app/task_asan+0x1119)

0x7f74154ff100 is located 0 bytes to the right of 4000000-byte region [0x7f741512e800,0x7f74154ff100)
allocated by thread T0 here:
    #0 0x7f7418cd8e8f in __interceptor_malloc ../../../../src/libsanitizer/asan/asan_malloc_linux.cpp:145
    #1 0x55a70de83278 in main /app/task.c:11
    #2 0x7f7418a7ed79 in __libc_start_main ../csu/libc-start.c:308

SUMMARY: AddressSanitizer: heap-buffer-overflow /app/task.c:18 in main
Shadow bytes around the buggy address:
  0x0fef02a97dd0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0fef02a97de0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0fef02a97df0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0fef02a97e00: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0fef02a97e10: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
=>0x0fef02a97e20:[fa]fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0fef02a97e60: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0fef02a97e70: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
Shadow byte legend (one shadow byte represents 8 application bytes):
  Addressable:           00
  Partially addressable: 01 02 03 04 05 06 07
  Heap left redzone:       fa
  Freed heap region:       fd
  Stack left redzone:      f1
  Stack mid redzone:       f2
  Stack right redzone:     f3
  Stack after return:      f5
  Stack use after scope:   f8
  Global redzone:          f9
  Global init order:       f6
  Poisoned by user:        f7
  Container overflow:      fc
  Array cookie:            ac
  Intra object redzone:    bb
  ASan internal:           fe
  Left alloca redzone:     ca
  Right alloca redzone:    cb
  Shadow gap:              cc
==18==ABORTING
```

### Програма запущена через Valgrind відпрацбовує значно повільніше ніж аналогічна з ASan
