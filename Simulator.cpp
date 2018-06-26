#include "Simulator.h"

void Create_queue::Enqueue(double second)
{
	if (head.rear == NULL) {
		head.rear = new Queue_Node();
		head.front = head.rear;
		head.rear->custNum = ++head.count;
		head.rear->arriveTime = second;
		head.current_size++;
		if (head.max_size < head.current_size)
			head.max_size = head.current_size;
	}
	else
	{
		Queue_Node* temp = head.front;
		head.front->next = new Queue_Node();
		head.front = head.front->next;
		temp->next = head.front;
		head.front->custNum = ++head.count;
		head.front->arriveTime = second;
		head.current_size++;
		if (head.max_size < head.current_size)
			head.max_size = head.current_size;
	}
}
Queue_Node Create_queue::Dequeue()
{
	if (head.rear != NULL) {
		Queue_Node* temp = head.rear;
		Queue_Node v_temp = *temp;
		head.rear = head.rear->next;
		if (head.front == temp)
			head.front = NULL;
		head.current_size--;
		delete temp;
		return v_temp;
	}
}

bool New_customer::GetCustomer()
{
	arrive = (rand() % (4 * MAX_SERVER_NUM)) + 1;
	if (arrive == (4 * MAX_SERVER_NUM))
		return true;
	else
		return false;
}

bool Server_free::Server_State()
{
	if (server == 1)
		return true;
	else
		return false;
}
void Server_free::Server_ChangeFlag()
{
	if (server == 1)
		server = 0;
	else
		server = 1;
}

int Service_complete::GetsvcTime()
{
	srand((unsigned int)time(NULL));
	svc = (rand() % 10) + 1;
	return svc;
}
void Service_complete::SetCustStatus(Queue_custStatus* custStatus, Queue_Node node, double g_second)
{
	custStatus->custNum = node.custNum;
	custStatus->arriveTime = node.arriveTime;
	custStatus->startTime = g_second;
	custStatus->svcTime = GetsvcTime();
}

void Print_Stats::SetSimStats(Queue_simStats* simStats, Queue_custStatus* custStatus, int max_queue, int current_queue)
{
	simStats->custNum += 1;
	simStats->maxQueueSize = max_queue;
	simStats->totSvcTime += custStatus->svcTime;
	simStats->totWaitTime = 5 * current_queue;
}

Simulator::Simulator()
{
	start_clock_ = clock();
	global_clock_ = start_clock_;
}
void Simulator::Reset()
{
	start_clock_ = clock();
}
void Simulator::Run()
{
	HWND hWnd;
	while (true)
	{
		LARGE_INTEGER seed;
		QueryPerformanceCounter(&seed);
		srand(seed.LowPart);
		// ���߾����忡�� ��ġ�� �ʴ� ����(Seed) ����

		if (GetSecond() > 1)
		{
			if (GetCustomer()) // ������ ��
			{
				Enqueue(GetGlobalSecond()); // Enqueue
			}

			if (Server_State() && head.current_size) // ť�� ���� �ְ� ���� �������� �Ǵ�
			{
				SetCustStatus(&custStatus, Dequeue(), GetGlobalSecond());
				Server_ChangeFlag(); // ���� ���� ����
			}

			if (!Server_State() && (custStatus.startTime + custStatus.svcTime) < GetGlobalSecond()) // ���� �Ϸ� �Ǵ�
			{
				SetSimStats(&simStats, &custStatus, head.max_size, head.current_size);
				Server_ChangeFlag();
			}
			hWnd = FindWindow(TEXT("Hello"), TEXT("Taffy Simulator"));
			InvalidateRect(hWnd, NULL, FALSE);
			UpdateWindow(hWnd);
			Reset();
		}
		if (GetGlobalSecond() > 480) // 480�� ����� ���α׷� ����
		{
			break;
		}
	}
}
double Simulator::GetSecond()
{
	clock_t current_clock = clock();
	return ((double)(current_clock - start_clock_) / CLOCKS_PER_SEC);
}
double Simulator::GetGlobalSecond()
{
	clock_t current_clock = clock();
	return ((double)(current_clock - global_clock_) / CLOCKS_PER_SEC);
}
Queue_custStatus Simulator::GetCurrentStatistic()
{
	return custStatus;
}
Queue_simStats Simulator::GetFinalStatistic()
{
	return simStats;
}