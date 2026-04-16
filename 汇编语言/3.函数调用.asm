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


    

    