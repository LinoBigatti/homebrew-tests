gcc -c -Wall island16b.c
gcc island16b.o -o island16b.elf
arm-agb-elf-objcopy -O binary island16b.elf island16b.bin
