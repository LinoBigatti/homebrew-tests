gcc -c -Wall island8.c
gcc island8.o -o island8.elf
arm-agb-elf-objcopy -O binary island8.elf island8.bin
