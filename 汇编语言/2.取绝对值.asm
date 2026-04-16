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





