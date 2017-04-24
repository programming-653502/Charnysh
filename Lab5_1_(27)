struct QueueItem
{
	QueueItem* Next;
	//int NumberOfQueue;
	char QInfo;
};

class TQueues // Класс-очередь
{
	QueueItem *First, *Head;

public:
	TQueues();
	TQueues(int);
	void Push(char NextChar);
	char Pop();
	~TQueues();
};

TQueues::TQueues()
{
	Head = 0;
	First = 0;
}
TQueues::TQueues(int t)
{
}
void TQueues::Push(char NextChar)
{
	if (!First)
	{
		First = new QueueItem;
		First->QInfo = NextChar;
		First->Next = NULL;
		Head = First;
		return;
	}
		Head->Next = new QueueItem;
		Head->Next->QInfo = NextChar;
		Head->Next->Next = NULL;
		Head = Head->Next;
}

char TQueues::Pop()
{
	if (First)
	{
		char ToReturn = First->QInfo;
		QueueItem *Temp = First->Next;
		delete First;
		First = Temp;
		return ToReturn;
	}
	else
	{
		return -1;
	}
}


TQueues::~TQueues()
{
	while (First)
	{
		QueueItem *Temp = First->Next;
		delete First;
		First = Temp;
	}
}




struct OperationList
{
	OperationList* Previous;
	OperationList* Next;
	int QueueToChange;
	char Operation;
	char data;
};


class TOperationsList // Cписок для работы с очередями
{
	OperationList *First, *Head;
	TQueues* QueuesArray;// Массив очередей
	int SizeOfArray;
public:
	TOperationsList(TQueues*,int);
	void Push(int, char, char data = '\0');
	int PopExecute();
	~TOperationsList();
};
OperationsList::TOperationsList(TQueues* QueuesArray, int SizeOfArray)
{
	int i = 0;
	this->QueuesArray = new TQueues[SizeOfArray];
	
	while (i < SizeOfArray)
	{
		this->QueuesArray[i] = (QueuesArray[i]);
		i++;
	}
	First = Head = NULL;
	this->SizeOfArray = SizeOfArray;
}
void TOperationsList::Push(int Number, char Operation, char data)
{
	if (!First)
	{
		First = new OperationList;
		First->Operation = Operation;
		First->QueueToChange = Number;
		First->Next = NULL;
		First->Previous = NULL;
		First->data = data;
		 Head = First;
		return;
	}
	Head->Next = new OperationList;
	Head->Next->Operation = Operation;
	Head->Next->QueueToChange = Number;
	Head->Next->Next = NULL;
	Head->Next->Previous = Head;
	Head->Next->data = data;
	Head = Head->Next;
}
int TOperationsList::PopExecute()
{
	if (!First)
	{
		return -1;//Заменить на инт
	}
	switch (First->Operation)
	{
		case 'A':
		{
			QueuesArray[First->QueueToChange].Push(First->data);
			printf_s("\nAdd operation executed <%c added to %d queue>", First->data, First->QueueToChange);
			OperationList* temp = First->Next;
			delete First;
			First = temp;
			//First->Previous = 0;
			return 0;
		}
		case 'D':
		{
			char Info = QueuesArray[First->QueueToChange].Pop();
			if (Info < 0)
			{
				printf_s("\nQueue #%d has no elements", First->QueueToChange);
				
			}
			else
			{
				printf_s("\nDeleting operation executed <%c deleted from %d queue>", Info, First->QueueToChange);
			}
				OperationList* temp = First->Next;
				delete First;
				First = temp;
				return 0;
			
		}
		default:
		{
			return -1;
		}
		}



}

TOperationsList::~TOperationsList()
{
	while (First)
	{
		OperationList* temp = First->Next;
		delete First;
		First = temp;
	}
}


TQueues *QueuesToOperate = new TQueues[QUEUES_QUANTITY];

TOperationsList* MyList1 = new TOperationsList(QueuesToOperate, QUEUES_QUANTITY);
void FulFillTheOperationList() //Функция для заполнения списка (случайный порядок операций и символов)
{
	char Operations[] = { 'A','D' };
	char Data[] = { 's','c','k','g','l','t','f','g','k','d','l' };
	int OperQuantity = 2;
	int DataQuantity = 6;
	
	for (int j = 0; j < 3; j++)
	{
		int i = 0;
		while (i < QUEUES_QUANTITY)
		{
			int RandomOperation = rand() % 100 / 10 % 2;
			int RandomData = rand() % 11;
			MyList1->Push(i, Operations[RandomOperation], Data[RandomData]);
			i++;
		}
	}
}



int main()
{
	FulFillTheOperationList();
	while (MyList1->PopExecute() >= 0)  //Пока не кончился список, выполняется каждая следующая операция. 
	{
      printf_s("\nPress any key to do next operation\n\n\n");
      _getch();
	}

	printf_s("\nSo, all operations executed. Press any key to exit!");
	_getch();
    return 0;
}


