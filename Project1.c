#define MAXSIZE 100
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
typedef struct node
{
    float data;
    struct node *next;
} node;

typedef struct
{
    node*top;
} Stack;


Stack* initialize ()
{
    Stack*s=malloc(sizeof(Stack));
    s->top=NULL;
    return s;
}

int isEmpty(Stack *s)
{
    if(s->top==NULL)
        return 1;
    else
        return 0;
}

float pop (Stack *s)
{

    if (isEmpty(s))
    {
        printf("Underflow\n");
        return -1;
    }

    node*temp=s->top;
    float x=s->top->data;
    s->top=s->top->next;
    free(temp);
    return x;
}
void push(Stack*s,float value)
{
    node*n=malloc(sizeof(node));
    if(n==NULL)
    {
        printf("Overflow\n");
        return;
    }
    n->data=value;
    n->next=s->top;
    s->top=n;

}

float peek (Stack *s)
{
    if (isEmpty(s))
    {
        printf("Stack is empty\n");
        return -1;
    }
    return s->top->data;
}

int priority(char op)
{
    if(op=='+'||op=='-')
        return 1;
    else if (op=='*'||op=='/'||op=='%')
        return 2;
    else if(op=='^')
        return 3;
    return 0;
}

int is_op(char c)
{
    if(c=='+'||c=='-'||c=='*'||c=='/'||c=='%'||c=='^')
        return 1;
    else
        return 0;
}


char* infixTopostfix(char *infix)
{
    char*post=malloc(strlen(infix)*2+1);
    Stack *s=initialize();
    post[0]='\0';
    char *token=strtok(infix," ");
    while(token!=NULL)
    {
        if(isdigit(token[0])||(token[0]=='-'&&isdigit(token[1])))
        {
            strcat(post,token);
            strcat(post," ");
        }
        else if(token[0]=='(')
            push(s,'(');
        else if(token[0]==')')
        {
            while(!isEmpty(s)&&peek(s)!='(')
            {
                char op[2]= {(char)pop(s),'\0'};
                strcat(post,op);
                strcat(post," ");
            }
            pop(s);
        }

        else if(is_op(token[0]))
        {
            while(!isEmpty(s)&&priority((char)peek(s))>=priority(token[0])&&peek(s)!='(')
            {
                char op[2]= {(char)pop(s),'\0'};
                strcat(post,op);
                strcat(post," ");
            }
            push(s,token[0]);
        }
        token=strtok(NULL," ");
    }
    while(!isEmpty(s))
    {
        char op[2]= {(char)pop(s),'\0'};
        strcat(post,op);
        strcat(post," ");
    }
    return post;
}

float evaluatePostfix(char* postfix)
{
   Stack *s=initialize();
    char*copy=strdup(postfix);
    char *token=strtok(copy," ");
    while(token!=NULL)
    {
        if(isdigit(token[0]) || (token[0] == '-' && isdigit(token[1])))
        {
            push(s,atof(token));
        }
        else if(is_op(token[0]))
        {
            float b = pop(s);
            float a = pop(s);
            if(token[0] == '+')
                push(s, a+b);

            else if(token[0] == '-')
                push(s, a-b);

            else if(token[0] == '*')
                push(s, a*b);

            else if(token[0] == '/')
                push(s, a/b);

            else if(token[0] == '%')
                push(s, fmod(a,b));

            else if(token[0] == '^')
                push(s, pow(a,b));
        }
        token = strtok(NULL, " ");
    }
    float result =pop(s);
    free(s);
    free(copy);

    return result;
}

int main()
{
    char infix[300];
    printf("Enter infix expression : ");

    if (fgets(infix, sizeof(infix), stdin))
    {

        infix[strcspn(infix, "\n")] = 0;

        char* postfix = infixTopostfix(infix);
        printf("Postfix: %s\n", postfix);
        float value=evaluatePostfix(postfix);
        printf("Value: %.3f\n",value);

        free(postfix);
    }
    return 0;
}
