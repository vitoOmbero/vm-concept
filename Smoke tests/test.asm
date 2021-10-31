
JMP 15          ; skip lines

SET A 0
SET B 0
SET C 0
OUT A 
OUT B 
OUT C

SET A 45        ; main execution
SET B -3
SET C -1
CMP C B
UNKNOWN COMMANDs ShOuLd be ignored ; like comments

JNE 1
HLT

CMP A C 
JG 1
HLT

ADD
OUT A 
HLT
