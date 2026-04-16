.MODEL SMALL
.STACK 64

.DATA;由于没有全局变量，所以为空，不填

.CODE
MAIN PROC FAR
    MOV AX, @DATA
    MOV DS, AX;初始化还是要写一下，防止乱七八糟的bug

    CALL FOO_FUNC;这里仍然会压入2字节的返回地址

    MOV AH, 4CH
    INT 21H
MAIN ENDP

FOO_FUNC PROC NEAR
    PUSH BP;依旧保存原来的BP
    MOV BP, SP;更新BP的位置
    SUB SP, 6;强行向下开6个字节空间，用来存新的3个数据
    ;一般整型数据用word来存！1个word是2个byte
    MOV WORD PTR [BP-2], 0;给局部变量a赋值，比如赋值为0

    MOV SP, BP;直接把SP挪回去，这样就直接删除掉了新存的3个数据
    POP BP;恢复现场，POP xx的机制是把SP（栈顶）指向的内容存到xx这个寄存器里
    RET
FOO_FUNC ENDP

END MAIN;整个代码段结束，然后给出一个起点的位置