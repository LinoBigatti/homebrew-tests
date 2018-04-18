gcc -c -Wall island16.c
gcc island16.o -o island16.elf
arm-agb-elf-objcopy -O binary island16.elf island16.bin
