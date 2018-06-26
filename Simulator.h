#pragma once
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <Windows.h>
#include <tchar.h>
#define MAX_SERVER_NUM 2
using namespace std;
struct Queue_Node
{
	int custNum = NULL; // ����ȣ
	double arriveTime = NULL; // �����ð�
	Queue_Node* next = NULL; // ��ũ������
};
struct Queue_Head
{
	Queue_Node* rear = NULL;
	Queue_Node* front = NULL;
	int current_size = NULL;
	int max_size = NULL;
	int count = NULL;
}static head;
struct Queue_custStatus
{
	int custNum = NULL; // ����ȣ
	double arriveTime = NULL; // �����ð�
	double startTime = NULL; // ���� ���۽ð�
	int svcTime = NULL; // ���� �ð�
};
struct Queue_simStats
{
	int custNum = NULL; // ��ü �� ��
	int totSvcTime = NULL; // ��ü ���� �ð�
	int totWaitTime = NULL; // ��� ���ð�
	int maxQueueSize = NULL; // �ִ� ť�� ũ��
};

class Create_queue
{
protected:
	void Enqueue(double second);
	Queue_Node Dequeue();
private:
};
class New_customer
{
protected:
	bool GetCustomer();
private:
	int arrive = NULL;
};
class Server_free
{
protected:
	bool Server_State();
	void Server_ChangeFlag();
private:
	int server = 1; // Server Flag
};
class Service_complete
{
protected:
	int GetsvcTime();
	void SetCustStatus(Queue_custStatus* custStatus, Queue_Node node, double g_second);
private:
	int svc;
};
class Print_Stats
{
protected:
	void SetSimStats(Queue_simStats* simStats, Queue_custStatus* custStatus, int maxqueue, int current_queuesize);
private:
};
class Simulator : // Protected ����� ���� ���� ���Ѽ���
	protected Create_queue,
	protected New_customer,
	protected Server_free,
	protected Service_complete,
	protected Print_Stats
{
public:
	Simulator(); // �ùķ����� �ʱ�ȭ
	void Run(); // �ùķ����� �۵� �Լ�
	Queue_custStatus GetCurrentStatistic();
	Queue_simStats GetFinalStatistic();
	double GetGlobalSecond(); // ��ü �ð� ��ȯ �Լ�
private:
	void Reset(); // �� ���� Reset �Լ�
	double GetSecond(); // �� ���� ��ȯ �Լ�
	clock_t global_clock_ = NULL; // ��ü �ð� Save
	clock_t start_clock_ = NULL; // �� ���� Save
	Queue_custStatus custStatus; // �������� �� ������
	Queue_simStats simStats; // ���񽺰� ���� ���� ��ü ��� ������
};