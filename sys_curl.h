/*
    * curl的封装，有以下操作：
    * 1.设置服务器参数
    * 2.发送信息：get、post、put、delete
    * 3.上传文件处理
    * 4.下载文件
*/
 
#ifndef SYS_CURL_H
#define SYS_CURL_H
 
#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <string>
#include "curl_lock.h"
 
//for test
#define  EPRINT  printf
#define  DPRINT  printf
 
/*
    * 宏定义发送方法
*/
#define METHOD_GET     0           //get方法
#define METHOD_POST    1           //post方法
#define METHOD_PUT     2           //put方法
#define METHOD_DELETE  3           //delete方法
 
/*
    * 宏定义数据格式
*/
#define FORMAT_DEFAULT 0           //默认数据格式
#define FORMAT_XML     1           //xml数据格式
#define FORMAT_JSON    2           //json数据格式
 
/*
    * 宏定义超时时间
*/
#define CONNECT_DEFAULT_TIMEOUT  10  //连接最长时间
#define DEFAULT_TIMEOUT          600 //传输最长时间
 
 
class sys_curl
{
 
private:
    CURL*              m_pCurl;                //curl指针
    struct curl_slist* m_pHeaders;             //http消息头
    std::string        m_sIP;                  //curl请求的ip
    unsigned int       m_nPort;                //curl请求ip的端口
    std::string        m_sUser;                //需要对方验证时使用，请求对方需要的用户名
    std::string        m_sPwd;                 //需要对方验证时使用，请求对方需要的密码
    std::string        m_sUrlPath;             //url路径
    static bool        s_bGlobalInitStatus;    //判断是否已进行全局初始化，0表示未初始化，1表示已经初始化
    static MutexLock   s_MutexLock;            //mutex锁对象
    unsigned int       m_contect_timeout;      //连接最长时间
    unsigned int       m_timeout;              //传输最长时间
 
public:
 
    sys_curl();
    sys_curl(const std::string& sIP,
                const unsigned int nPort,
                const std::string& sUser,
                const std::string& sPwd);
    sys_curl(const std::string& sIP);
    ~sys_curl();
    
 
 
    // 设置等待连接最长时间
    void setConnectTimeout(unsigned int nTime);
 
    // 设置传输最长时间
    void setTimeout(unsigned int nTime);
 
    //设置服务器参数
    void setServer(const std::string& sIP,
                   const unsigned int nPort,
                   const std::string& sUser,
                   const std::string& sPwd);
 
    //设置URL路径
    void setUrlPath(const std::string& sUrlPath);
 
    //发送消息发送方式
    int sendMsg(const std::string& sMsg,
                const int nMethod,
                const int nFormat,
                std::string& sRec);
 
    //下载文件
    int downloadFile(const std::string& sFileName, const int nFormat);
 
    //从文件中读取内容post出去
    int uploadFileContent(const std::string& sFileName, const int nFormat, std::string& sRec);
 
    //上传文件
    int uploadFile(const std::string& sFileFullname, std::string& sRec);
 
    //进行所有CURL开始之前，全局变量初始化，放在主线程中
    static int globalInit();
 
    //全局资源释放，行所有CURL结束之前，放在主线程中
    static int globalCleanup();
    
    //对单一curl资源进行初始化,不封装在构造函数的好处是,可以对curl初始化异常时进行处理
    int initCurlResource();
    
    //对单一curl资源进行释放,可用可不用, 不用则留给类析构释放, 使用好处时,使用者可以对异常进行处理
    int releaseCurlResource();
 
private:
 
    //设置请求用户名和密码
    int setUserPwd();
 
    //设置数据格式
    int setDataFormat(const int nFormat);
 
    //回调函数，将文件内容读取到缓存中
    static size_t httpReadFile(void* buffer, size_t size, size_t nmemb, void* file);
 
    //回调函数，将缓存内容写到文件中
    static size_t httpWriteFile(void* buffer, size_t size, size_t nmemb, void* file);
 
    //回调函数，将返回缓存数据写出
    static size_t httpDataWriter(void* buffer, size_t size, size_t nmemb, void* content);
 
    //通过get的方式发送信息
    int getMsg(const std::string& sMsg, const int nFormat, std::string& sRec);
 
    //通过post的方式发送信息
    int postMsg(const std::string& sMsg, const int nFormat, std::string& sRec);
 
    //通过put的方式发送信息
    int putMsg(const std::string& sMsg, const int nFormat, std::string& sRec);
 
    //通过delete进行操作
    int deleteMsg(const std::string& sMsg, const int nFormat, std::string& sRec);
 
    //curl一些公用操作
    int messagePublicMethod(const int nFormat);
    
	//curl返回值处理
    int dealResCode(const CURLcode res);
 
    //从文件全路径中获取文件名指针
    const char* getFileName(const char *path);
};
 
 
#endif   //MANAGER_CURL_H_
