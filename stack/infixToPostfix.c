#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct stack{
    int size;
    int top;
    char *arr;
};

int isEmpty(struct stack *ptr){
    if(ptr->top == -1){
        return 1;
    }
    else{
        return 0;
    }
}

int isFull(struct stack *ptr){
    if(ptr->top == ptr->size-1){
        return 1;
    }
    else{
        return 0;
    }
}

void push(struct stack *ptr,char val){
    if(isFull(ptr)){
        printf("Stack overflow.\n");
        printf("Cannot push %c to the stack!\n",val);
    }
    else{
        ptr->top++;
        ptr->arr[ptr->top] = val;
    }
}

char pop(struct stack *ptr){
    if(isEmpty(ptr)){
        printf("Stack underflow.\n");
        return '\0';
    }
    else{
        char val = ptr->arr[ptr->top];
        ptr->top--;
        return val;
    }
}

char peek(struct stack *ptr){
    if(isEmpty(ptr)){
        printf("Stack is empty.");
        return '\0';
    }
    else{
        return ptr->arr[ptr->top];
    }
}

int priority (char val){
    if (val == '('){
        return 5;
    }
    else if(val == '/' ){
        return 4;
    }
    else if (val == '*' ){
        return 3;
    }
    else if(val == '+'){
        return 2;
    }    
    else if(val == '-'){
        return 1;
    }
    else{
        return -1;
    }
}

char *InToPost(struct stack *ptr, char exp[]){
    char *postfix = (char*)malloc(strlen(exp)*sizeof(char)); 
    int j = 0;
    for (int i =0; exp[i]!= '\0'; i++) {
        if(exp[i] != '/' && exp[i] != '*'&& exp[i] != '+' && exp[i] != '-'){
            // printf("%c",exp[i]);
            postfix[j] = exp[i];
            j++;
        }
        else{
            //logic 
            if(isEmpty(ptr)){
                push(ptr,exp[i]);
            }
            else{
                if(priority(ptr->arr[ptr->top])>priority(exp[i])){
                    // pop(ptr);
                    postfix[j] = pop(ptr);
                    j++;
                    push(ptr,exp[i]);
                }
                else{
                    push(ptr,exp[i]);
                }
            }
        }                
    }
    for(int k = ptr->top;k>=0;k--){
        postfix[j] = pop(ptr);
        j++;
    }

    postfix[j] = '\0';
    return postfix;
}


int main(){
    struct stack *s =(struct stack*)malloc(sizeof(struct stack));
    s->size = 100;
    s->top = -1;
    s->arr = (char*)malloc(s->size*sizeof(char));

    char exp[] ="A*B+C";
    printf("Infix Expression : %s\n", exp);
    printf("Postfix Expression : %s",InToPost(s,exp));

    return 0;
}