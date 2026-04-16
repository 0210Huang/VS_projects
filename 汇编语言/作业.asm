;第一题：
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



;第二题：
    .MODEL SMALL
    .STACK 64
    ;以上两行是起手式

    .DATA;定义数据段（相当于定义全局变量）
    SRC_VAL DW -42;随便写一个负数测试
    ABS_VAL DW ?;用？表示未知的数值

    .CODE;进入代码段
MAIN PROC FAR
    MOV AX,@DATA
    MOV MOV DS,AX;这两行是MAIN起手式，雷打不动，为了初始化DS

    MOV AX,SRC_VAL;必须先把数据搬进寄存器之后再操作
    CMP AX,0;实际上是偷偷把AX减0得到一个临时数值
    JGE IS_POS;JGE (Jump if Greater or Equal)，和CMP搭配使用：如果临时数值 >= 0，则跳转，跳过取反步骤

    NEG AX;Negate表示取补码，即变正负号

    IS_POS:;一个label
    MOV ABS_VAL,AX;把得到的结果（目前还在AX中）存进内存

    ;下面是经典收尾，基本每次都这样写
    MOV AH,4CH
    INT 21H
MAIN ENDP;xx(函数名) ENDP，表示xx这个函数结束了
    END MAIN;END表示整个代码结束了，MAIN 是指定入口：告诉操作系统从MAIN开始执行程序

;第三题：
    .MODEL SMALL
    .STACK 64;函数调用必须用到栈
    ;以上两行是起手式

    .DATA
    A DW -1
    B DW 1
    C DW ?
    D DW ?

    .CODE
MAIN PROC FAR
    MOV AX,@DATA;需要AX作中间的桥梁
    MOV CS,AX

    ;翻译c=abs（a）
    MOV AX,A
    PUSH AX;将AX里面的值压入栈中

    CALL ABS_FUNC;注意在CALL的时候会在栈中存放一个返回地址，占2字节，要在函数里面考虑到这一点，而退出函数的时候会自动pop掉那个地址
    ADD SP,2;由于之前压入了2个字节，所以栈顶指针SP要+2来手动丢弃掉这个废值
    MOV C,AX;把结果放到内存中去

    ;翻译d=add（a，b）
    MOV AX,B
    PUSH AX
    MOV AX,A
    PUSH AX;把这两个压入栈中，注意从右到左压入栈中，这样可以才可以做到从左到右取出参数

    CALL ADD_FUNC
    ADD SP,4;同样地，手动更新栈顶指针，丢弃废值

    MOV AH, 4CH
    INT 21H
MAIN ENDP;结束主函数MAIN，但是不写END MAIN，因为整个代码还没结束

;定义abs函数
ABS_FUNC PROC NEAR;子程序一般用NEAR
    PUSH BP;BP是基准指针，可以理解为是这个函数所用栈的临时基准指针。这里是把上一任的BP存起来保护好
    MOV BP,SP;更新BP的位置，把当前的栈顶位置设为这个函数的基准（但是注意：[BP]即BP位置的内容，是老的BP值借了这个位置存下来！）

    MOV AX,[BP+4];易错！[BP]是老的保护起来的BP值（最后压入的），[BP+2]是返回地址IP，[BP+4]才是push进来的参数A（最先压入的）
    ;注意：8086中，栈是向下生长的！即后面的内容在低地址而不是高地址。所以先弹出BP再弹出BP+2再弹出BP+4

    CMP AX,0
    JGE IS_POS
    NEG AX
    IS_POS:
    POP BP;把保护起来的BP弹出来还回去，恢复现场
    RET;弹出返回地址，这样才能成功返回到主函数往下接着执行
ABS_FUNC ENDP

;定义add函数
ADD_FUNC PROC NEAR
    PUSH BP;保存BP
    MOV BP,SP;设置新的BP，[BP]仍然是老的BP借存了
    MOV AX,[BP+4];传入的第一个参数
    ADD AX,[BP+6];传入的第二个参数

    POP BP;恢复现场
    RET

ADD_FUNC ENDP
    END MAIN;整个程序结束



;第四题：
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