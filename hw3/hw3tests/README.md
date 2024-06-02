you can test your hw3 question3 subtask 1-2 with this script.

first put your Subtask1.cpp Subtask2.cpp HashTable.cpp HashTable.h in the same directory with this repo.
then give executable permission to test1.sh and test2.sh ( by doing chmod +x testx.sh )
after that you can run it by make test1 and make test2

if a random generated test fails it shows it like this:

```
< 33
---
> 17
CAaABCbBCCAbaBABCBBaCbCACaCAbCCabCaBBCbaBbbCabAAaBBABaCABBAAbCBABbaCbACAbCbbaACaBaab
4
BbbC
B
bCBBbbAAb
CBCCCCCBB
```

correct answer is 17 and the answer your solution gives is 33.

you can see the test input below it.

idk how you can run this on windows or mac but it can surely run on dijkstra server

and also you can edit genx.cpp files to generate different sized inputs.

edit: it also shows the time taken by your solution now.

reference: https://www.youtube.com/watch?v=JXTVOyQpSGM
https://stackoverflow.com/questions/440133/how-do-i-create-a-random-alpha-numeric-string-in-c
