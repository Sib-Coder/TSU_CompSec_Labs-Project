# Лабораторная работа 4
## Задание: Написать модуль ядра который открывает сокет на прослушивание 


```fish
root@sib:/home/sib/src/lkm_example# make test
ss -ltn
State     Recv-Q    Send-Q         Local Address:Port         Peer Address:Port    Process    
LISTEN    0         4096           127.0.0.53%lo:53                0.0.0.0:*                  
LISTEN    0         128                  0.0.0.0:22                0.0.0.0:*                  
LISTEN    0         128                     [::]:22                   [::]:*                  
sudo dmesg -C
sudo insmod lkm_example.ko
ss -ltn
State     Recv-Q    Send-Q         Local Address:Port         Peer Address:Port    Process    
LISTEN    0         4096           127.0.0.53%lo:53                0.0.0.0:*                  
LISTEN    0         128                  0.0.0.0:22                0.0.0.0:*                  
LISTEN    0         5                    0.0.0.0:8080              0.0.0.0:*                  
LISTEN    0         128                     [::]:22                   [::]:*                  
sudo rmmod lkm_example.ko
dmesg
[ 1044.383154] Socket listening on port 8080
```