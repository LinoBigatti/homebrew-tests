gcc -c -Wall projamain.c
gcc projamain.o -o projamain.elf
arm-agb-elf-objcopy -O binary projamain.elf projagba.bin
