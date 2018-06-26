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
	int custNum = NULL; // 고객번호
	double arriveTime = NULL; // 도착시간
	Queue_Node* next = NULL; // 링크포인터
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
	int custNum = NULL; // 고객번호
	double arriveTime = NULL; // 도착시간
	double startTime = NULL; // 서비스 시작시간
	int svcTime = NULL; // 서비스 시간
};
struct Queue_simStats
{
	int custNum = NULL; // 전체 고객 수
	int totSvcTime = NULL; // 전체 서비스 시간
	int totWaitTime = NULL; // 평균 대기시간
	int maxQueueSize = NULL; // 최대 큐의 크기
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
class Simulator : // Protected 상속을 통한 접근 권한설정
	protected Create_queue,
	protected New_customer,
	protected Server_free,
	protected Service_complete,
	protected Print_Stats
{
public:
	Simulator(); // 시뮬레이터 초기화
	void Run(); // 시뮬레이터 작동 함수
	Queue_custStatus GetCurrentStatistic();
	Queue_simStats GetFinalStatistic();
	double GetGlobalSecond(); // 전체 시간 반환 함수
private:
	void Reset(); // 분 간격 Reset 함수
	double GetSecond(); // 분 간격 반환 함수
	clock_t global_clock_ = NULL; // 전체 시간 Save
	clock_t start_clock_ = NULL; // 분 간격 Save
	Queue_custStatus custStatus; // 서비스중인 고객 데이터
	Queue_simStats simStats; // 서비스가 끝난 고객의 전체 통계 데이터
};