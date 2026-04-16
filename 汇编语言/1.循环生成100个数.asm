.MODEL SMALL
.STACK 64

.DATA;数据段
    ARRAY DB 100 DUP(?)

.CODE;代码段
MAIN PROC FAR;主程序必须用FAR，子函数一般用NEAR
    MOV AX,@DATA
    MOV DS,AX;要访问自己定义的变量，必须让DS寄存器指向.DATA的地址，这是DS的初始化

    MOV SI,OFFSET ARRAY;获取变量地址
    MOV CX,100;CX是循环计数器（count register）
    MOV,AL,0;要写进内存的数据，从0开始

    BACK:
        MOV [SI],AL;写入数据
        INC AL
        INC SI;指针可以直接加一，变到下一个格子里
        LOOP BACK;2个作用：1.把CX自动减一  2.判断CX是否为0，如果不为0就自动跳转到BACK
        ;总而言之，这个LOOP BACK相当于每一次循环结束的计数器部分，和CX搭配使用

    ;接下来是标准的结束程序指令，记下来即可
    MOV AH,4CH
    INT 21H
MAIN ENDP
END MAIN


