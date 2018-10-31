/*
	* 实现mutex的封装的具体实现，有以下操作：
	* 1.mutex初始化
	* 2.mutex加锁
	* 3.mutex解锁
	* 4.mutex释放
*/
 
#include "curl_lock.h"
#include <stdio.h>
#include <errno.h>
 
MutexLock::MutexLock()
{
	mutexInit();
}
 
MutexLock::~MutexLock()
{
	mutexDestroy();
}
 
/*
	* 对mutex进行初始化
*/
void MutexLock::mutexInit()
{
	
	pthread_mutex_init(&m_Mutex, NULL);
	
}
 
/*
	* 对mutex进行加锁操作
	* 返回值为整数，0表示成功，其他表示失败
*/
int MutexLock::lock()
{
	int nCode = -1;
	
	nCode = pthread_mutex_lock(&m_Mutex);
	if(0 == nCode)
	{
		return 0;
	}
	else
	{
		EPRINT("mutex lock error(%d)\n", errno);
		return -1;        //加锁失败
	}
}
 
/*
	* 对mutex进行解锁操作
	* 返回值为整数，0表示成功，其他表示失败
*/
int MutexLock::unlock()
{
	int nCode = -1;
	
	nCode = pthread_mutex_unlock(&m_Mutex);
	if(0 == nCode)
	{
		return 0;
	}
	else
	{
		EPRINT("mutex unlock error(%d)\n", errno);
		return -1;    //解锁失败
	}		
}
 
/*
	* 对mutex进行释放
*/
void MutexLock::mutexDestroy()
{
	
	pthread_mutex_destroy(&m_Mutex);
	
}
 
 
