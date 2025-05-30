# vpp-client
Simple VPP client for test

# build
```
make
```

# usage
```
Usage: ./vpp_client <command1> [command2] ...
```
# example
You can send several commands
```
./vpp_client "set terminal pager off" "show interface"
```
# compare
Compare time of execution:
```
root@vpp:/home/vyos# time sudo vppctl show interface > /dev/null

real	0m0.014s
user	0m0.002s
sys	0m0.009s
root@vpp:/home/vyos# 
---


root@vpp:/home/vyos# time printf "set terminal pager off\nshow interface\n" | socat - /run/vpp/cli.sock > /dev/null

real	0m0.006s
user	0m0.001s
sys	0m0.005s
root@vpp:/home/vyos# 


---
root@vpp:/home/vyos# time vpp_client "set terminal pager off" "show interface" > /dev/null 

real	0m0.002s
user	0m0.000s
sys	0m0.001s
root@vpp:/home/vyos# 

```