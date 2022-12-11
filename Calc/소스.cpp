#include <stdio.h>
#include <stdlib.h>

typedef struct _NODE {
    char Data;
    struct _NODE* Next;
} NODE;

NODE* head, * end;
NODE* ptrNode;

int sum = 0;
int x = 0, y = 0;

char stack[20] = { 0 };

int count = 0;

void Calculation(char m);      // 계산용 함수
void InitializeStack(void);  // 스택 초기화 
void Push(char);  // 데이터의 삽입
int Ppush(char);  // 데이터의 삽입
int Pop(void);  // 데이터의 삭제


// 계산용 함수
void Calculation(char m)
{
    NODE* indexNode;
    indexNode = (NODE*)malloc(sizeof(NODE));
    int temp = 0;

    switch (m)                  // 연산기호 확인 후 계산
    {
    case '+':
        head->Next->Next->Data += head->Next->Data;
        indexNode = head->Next;
        head->Next = indexNode->Next;
        free(indexNode);
        break;
    case '-':
        head->Next->Next->Data -= head->Next->Data;
        indexNode = head->Next;
        head->Next = indexNode->Next;
        free(indexNode);
        break;
    case '*':
        head->Next->Next->Data *= head->Next->Data;
        indexNode = head->Next;
        head->Next = indexNode->Next;
        free(indexNode);
        break;
    case '/':
        head->Next->Next->Data /= head->Next->Data;
        indexNode = head->Next;
        head->Next = indexNode->Next;
        free(indexNode);
        break;
    default:                // 연산기호가 아니라면
        temp = m - 48;              // 코드 값에서 -48을 빼 int형에 넣어서 0은 0, 1은 1이 되게했습니다
        break;
    }

    if (temp != 0)               // 위에서 연산기호가 아니라 숫자라서 temp에 값이 들어갔다면
    {
        indexNode->Data = temp;         // temp값을 스택에 쌓기
        indexNode->Next = head->Next;
        head->Next = indexNode;
    }
}

// 스택 초기화 
void InitializeStack(void)
{
    head = (NODE*)malloc(sizeof(NODE));
    end = (NODE*)malloc(sizeof(NODE));
    head->Next = end;
    end->Next = end;

}

void Push(char m)
{
    ptrNode = (NODE*)malloc(sizeof(NODE));

    switch (m)                  // 연산기호 확인
    {
    case '*':               // 들어갈 값이 곱하기나 나누기일때
    case '/':
        if (head->Next->Data == '/' || head->Next->Data == '*')     // top값이 곱하기와 나누기라면
        {
            Pop();          // 팝하고
        }
        Ppush(m);           // 푸시
        break;
    case '+':               // 들어갈 값이 더하기나 빼기일때
    case '-':
        if (head->Next->Data != '(')            // top값이 여는 괄호가 아니라면
        {
            Pop();              // 팝하고
        }
        Ppush(m);       // 푸시
        break;
    case '(':           // 여는 괄호일때는
        Ppush(m);       // 무조건 푸시
        break;
    case ')':           // 닫는 괄호일때는
        while (1)
        {
            if (head->Next->Data == '(')        // top이 여는 괄호라면
            {
                Pop();          // 팝하고 반복문 탈출
                break;
            }
            else        // 여는 괄호가 아니라면
            {
                Pop();  // 계속 팝
            }
        }
        break;
    default:            // 전부 아니라면(숫자인 경우)
        Ppush(m);           // 푸시하고
        Pop();              // 바로 팝
        break;
    }
}

// 긴 문장이 반복되어서 사용되어서 함수화 했습니다
int Ppush(char m)
{
    ptrNode->Data = m;
    ptrNode->Next = head->Next;
    head->Next = ptrNode;

    return 0;
}

int Pop(void)
{
    NODE* indexNode;
    if (head->Next == end)           // 스택에 아무 값도 없다면
    {
        return 0;               // 실행하지않았습니다
    }
    indexNode = (NODE*)malloc(sizeof(NODE));

    indexNode = head->Next;
    head->Next = indexNode->Next;

    if (indexNode->Data != '(' && indexNode->Data != ')')               // 괄호는 프린트도, 나중에 계산하는 스택에도 넣지않았습니다
    {
        printf("%c", indexNode->Data);
        stack[count++] = indexNode->Data;
    }

    free(indexNode);

    return 0;
}

void main()
{
    InitializeStack();
    char a[20];
    int cnt = 0;
    printf("중위 표기식 : ");
    gets_s(a, sizeof(a));

    for (int i = 0; i < 20; i++)                // 몇글자 쳤는 지 확인
    {
        if (a[i] == '\0')
        {
            break;
        }
        cnt++;
    }

    printf("\n후위 표기식 : ");
    for (int i = 0; i < cnt; i++)           // 글자수만큼 푸시
    {
        Push(a[i]);

    }
    while (1)                   // 푸시와 팝이 끝난 후 스택에 남은 값 빼는 while문
    {
        if (head->Next != end)
        {
            Pop();
        }
        else
        {
            break;
        }
    }

    printf("\n\n계산 결과 : ");

    for (int i = 0; i < count; i++)         // 계산 값 출력
    {
        Calculation(stack[i]);
    }
    printf("%d", head->Next->Data);
    printf("\n\n");

    system("pause");
}