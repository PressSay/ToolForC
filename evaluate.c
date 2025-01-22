#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>


struct StackNode {
    int number;
    char operator;
    struct StackNode * next;
};

typedef struct {
    struct StackNode *data;
    int len;
} Stack;


void createStack(Stack* stack) {
    stack->data = NULL;
    stack->len = 0;
}

void insertStack(Stack* stack, int number, char operator) {
    struct StackNode* newNode = malloc(sizeof(struct StackNode));
    newNode->next = stack[0].data;
    newNode->number = number;
    newNode->operator = operator;
    stack[0].data = newNode;
    stack[0].len++;
}

void popStack(Stack* stack) {
    if (stack[0].len > 0) {
    struct StackNode* tmp = stack[0].data;
    stack[0].data = stack[0].data->next;
    stack[0].len--;
    free(tmp);
    }
}

bool delim(char c) {
    return c == ' ';
}

bool is_op(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

bool is_unary(char c) {
    return c == '+' || c=='-';
}

int priority (char op) {
    if (op < 0) // unary operator
        return 3;
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return -1;
}

void process_op(Stack* st, char op) {
    if (op < 0) {

        int l = st[0].data->number;
        popStack(st);
        switch (-op) {
            case '+': insertStack(st, l, '\0'); break;
            case '-': insertStack(st, -l, '\0'); break;
        }
    } else {
        int r = st[0].data->number;
        popStack(st);
        int l = st[0].data->number;
        popStack(st);
        switch (op) {
            case '+': insertStack(st, l + r, '\0'); break;
            case '-': insertStack(st, l - r, '\0'); break;
            case '*': insertStack(st, l * r, '\0'); break;
            case '/': insertStack(st, l / r, '\0'); break;
        }
    }
}

int evaluate(char* s, int sLen) {
    Stack st;
    Stack op;
    createStack(&st);
    createStack(&op);

    bool may_be_unary = true;

    for (int i = 0; i < sLen; i++) {
        if (delim(s[i]))
            continue;

        if (s[i] == '(') {
            insertStack(&op, 0, '(');
            may_be_unary = true;
        } else if (s[i] == ')') {
            char operator = op.data->operator;
            while (operator != '(') {
                process_op(&st, operator);
                popStack(&op);
            }
            popStack(&op);
            may_be_unary = false;
        } else if (is_op(s[i])) {
            char cur_op = s[i];
            if (may_be_unary && is_unary(cur_op))
                cur_op = -cur_op;
            while (op.len > 0) {
                if ((
                    (cur_op >= 0 && priority(op.data->operator) >= priority(cur_op)) ||
                    (cur_op < 0 && priority(op.data->operator) > priority(cur_op))
                )) {
                process_op(&st, op.data->operator);
                }
                popStack(&op);
            }
            insertStack(&op, 0, cur_op);
            may_be_unary = true;
        } else {
            int number = 0;
            while (i < sLen && isalnum(s[i]))
                number = number * 10 + s[i++] - '0';
            --i;
            insertStack(&st, number, '\0');
            may_be_unary = false;
        }
    }

    while (op.len > 0) {
        char operator = op.data->operator;
        process_op(&st, operator);
        popStack(&op);
    }
    int result = st.data->number;
    popStack(&st);
    return result;
}

int main() {
    char s[] = "4+4";
    int result = evaluate(s, 3);
    printf("%d\n", result);
    return 0;
}