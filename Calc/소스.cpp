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

void Calculation(char m);      // ���� �Լ�
void InitializeStack(void);  // ���� �ʱ�ȭ 
void Push(char);  // �������� ����
int Ppush(char);  // �������� ����
int Pop(void);  // �������� ����


// ���� �Լ�
void Calculation(char m)
{
    NODE* indexNode;
    indexNode = (NODE*)malloc(sizeof(NODE));
    int temp = 0;

    switch (m)                  // �����ȣ Ȯ�� �� ���
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
    default:                // �����ȣ�� �ƴ϶��
        temp = m - 48;              // �ڵ� ������ -48�� �� int���� �־ 0�� 0, 1�� 1�� �ǰ��߽��ϴ�
        break;
    }

    if (temp != 0)               // ������ �����ȣ�� �ƴ϶� ���ڶ� temp�� ���� ���ٸ�
    {
        indexNode->Data = temp;         // temp���� ���ÿ� �ױ�
        indexNode->Next = head->Next;
        head->Next = indexNode;
    }
}

// ���� �ʱ�ȭ 
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

    switch (m)                  // �����ȣ Ȯ��
    {
    case '*':               // �� ���� ���ϱ⳪ �������϶�
    case '/':
        if (head->Next->Data == '/' || head->Next->Data == '*')     // top���� ���ϱ�� ��������
        {
            Pop();          // ���ϰ�
        }
        Ppush(m);           // Ǫ��
        break;
    case '+':               // �� ���� ���ϱ⳪ �����϶�
    case '-':
        if (head->Next->Data != '(')            // top���� ���� ��ȣ�� �ƴ϶��
        {
            Pop();              // ���ϰ�
        }
        Ppush(m);       // Ǫ��
        break;
    case '(':           // ���� ��ȣ�϶���
        Ppush(m);       // ������ Ǫ��
        break;
    case ')':           // �ݴ� ��ȣ�϶���
        while (1)
        {
            if (head->Next->Data == '(')        // top�� ���� ��ȣ���
            {
                Pop();          // ���ϰ� �ݺ��� Ż��
                break;
            }
            else        // ���� ��ȣ�� �ƴ϶��
            {
                Pop();  // ��� ��
            }
        }
        break;
    default:            // ���� �ƴ϶��(������ ���)
        Ppush(m);           // Ǫ���ϰ�
        Pop();              // �ٷ� ��
        break;
    }
}

// �� ������ �ݺ��Ǿ ���Ǿ �Լ�ȭ �߽��ϴ�
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
    if (head->Next == end)           // ���ÿ� �ƹ� ���� ���ٸ�
    {
        return 0;               // ���������ʾҽ��ϴ�
    }
    indexNode = (NODE*)malloc(sizeof(NODE));

    indexNode = head->Next;
    head->Next = indexNode->Next;

    if (indexNode->Data != '(' && indexNode->Data != ')')               // ��ȣ�� ����Ʈ��, ���߿� ����ϴ� ���ÿ��� �����ʾҽ��ϴ�
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
    printf("���� ǥ��� : ");
    gets_s(a, sizeof(a));

    for (int i = 0; i < 20; i++)                // ����� �ƴ� �� Ȯ��
    {
        if (a[i] == '\0')
        {
            break;
        }
        cnt++;
    }

    printf("\n���� ǥ��� : ");
    for (int i = 0; i < cnt; i++)           // ���ڼ���ŭ Ǫ��
    {
        Push(a[i]);

    }
    while (1)                   // Ǫ�ÿ� ���� ���� �� ���ÿ� ���� �� ���� while��
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

    printf("\n\n��� ��� : ");

    for (int i = 0; i < count; i++)         // ��� �� ���
    {
        Calculation(stack[i]);
    }
    printf("%d", head->Next->Data);
    printf("\n\n");

    system("pause");
}