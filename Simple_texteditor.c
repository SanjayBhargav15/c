#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct node
{
    char data[100];
    struct node* next;
};
int elements = 0;
struct node* add(struct node* stack, char *str)
{
    struct node* tp = (struct node*)malloc(sizeof(struct node)) ;
    strcpy(tp->data,str);
    tp->next = stack;
    elements++;
    return tp;
}
void redo()
{
    elements++;
}
void undo()
{
    elements--;
}
int print(struct node* stack,int idx)
{
    if(stack == NULL)
    {
        printf("\n");
        return 0;
    }
    idx = print(stack->next,idx);
    if(idx<elements)
        printf("%s\n",stack->data);
    return idx+1;
}
int save_command(FILE* filePointer, struct node* stack,int idx)
{
    if(stack == NULL)
    {
        return 0;
    }
    idx = save_command(filePointer, stack->next,idx);
    if(idx<elements)
        fprintf(filePointer,"%s\n",stack->data);
    return idx+1;
}
int main()
{
    struct node *stack1=NULL;
    char input[100];
    int ch;
    while(1)
    {
        printf("Enter content  :   ");
        gets(input);
        printf("1.undo\t2.redo\t3.print\t4.save\t5.quit\nEnter your option :  ");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1 :undo();
                    printf(">>>");
                    print(stack1,elements);
                    break;
            case 2 :redo();
                    printf(">>>");
                    print(stack1,elements);
                    break;
            case 3 :printf(">>>");
                    print(stack1,elements);
                    break;
            case 4 :{
                        FILE* filePointer;
                        filePointer=fopen("output.txt","w");
                        
                        save_command(filePointer,stack1,elements);
                        fclose(filePointer);
                    }break;
            case 5 :{
                        FILE* filePointer;
                        filePointer=fopen("output.txt","w");
                        save_command(filePointer,stack1,elements);
                        fclose(filePointer);
                        printf("result > Good Bye!\n");
                        exit(0);
                    }break;
            default :printf("INVALID INPUT!\n");break;
        }
        stack1 = add(stack1,input);
    }
}

