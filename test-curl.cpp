#include <stdio.h>
#include <string>
#include "sys_curl.h"
 
//for test
#define  EPRINT  printf
#define  DPRINT  printf
 
/*
    * 通过get 、delete方式发送数据
    * 返回值int, 0表示成功,1表示超时, 其它表示失败
*/
int curl_get_message()
{
    int nCode = -1;
    std::string sIP = "www.merchandise.com";
    unsigned int nPort = 80;
    std::string sUser = "";   //可为空
    std::string sPwd = "";     //可为空 
 
    //这边用智能指针更好
    sys_curl* pCluster_Curl = new sys_curl(sIP);
    if(NULL == pCluster_Curl)
    {
        //创建Curl对象失败
        EPRINT("new object failure!!!!!\n");
        return -1;
    }
    
    //curl初始化
    nCode = pCluster_Curl->initCurlResource();
    if(0 != nCode)
    {
        EPRINT("curl init failure!!!!!\n");
        delete pCluster_Curl;
        pCluster_Curl = NULL;
        return -1;
    }
    
    //设置路径
    std::string sUrlPath = "/index.php?user=user&name=name";
    pCluster_Curl->setUrlPath(sUrlPath);
    
    //发送方式为get,数据格式为默认,内容为空
    int nMethod = METHOD_GET;
    //int nMethod = METHOD_DELETE;
    int nFormat = FORMAT_DEFAULT;
    std::string sMsg;
    std::string sRec;
    nCode = pCluster_Curl->sendMsg(sMsg, nMethod, nFormat,sRec);
    // printf("%d\n", nCode);
    printf("%s\n", sRec.c_str());
        
    delete pCluster_Curl;
    
    return nCode;
    
}
 
/*
    * 通过post 、put方式发送数据
    * 返回值int, 0表示成功,1表示超时, 其它表示失败
*/
int curl_post_message()
{
    int nCode = -1;
    std::string sIP = "www.merchandise.com";
    unsigned int nPort = 80;
    std::string sUser = "";   //可为空
    std::string sPwd = "";     //可为空 
 
    //这边用智能指针更好
    sys_curl* pCluster_Curl = new sys_curl(sIP, nPort, sUser, sPwd);
    if(NULL == pCluster_Curl)
    {
        //创建Curl对象失败
        printf("new object failure!!!!!\n");
        return -1;
    }
    
    //curl初始化
    nCode = pCluster_Curl->initCurlResource();
    if(0 != nCode)
    {
        EPRINT("curl init failure!!!!!\n");
        delete pCluster_Curl;
        pCluster_Curl = NULL;
        return -1;
    }
    
    //设置路径
    std::string sUrlPath = "/index.php";
    pCluster_Curl->setUrlPath(sUrlPath);
    
    //发送方式为post,数据格式为json,发送数据为json
    int nMethod = METHOD_POST;
    //int nMethod = METHOD_PUT;
    int nFormat = FORMAT_DEFAULT;
    std::string sRec;
    std::string sMsg = "f=8&rsv_bp=1&rsv_idx=1&word=picture&tn=98633779_hao_pg";
    
    nCode = pCluster_Curl->sendMsg(sMsg, nMethod, nFormat,sRec);
    printf("%d\n", nCode);
     printf("%s\n", sRec.c_str());
    delete pCluster_Curl;
    return nCode;
    
}
 
/*
    * 上传文件
    * 返回值int, 0表示成功,1表示超时, 其它表示失败
*/
int curl_upload_file()
{
    int nCode = -1;
    std::string sIP = "10.200.0.225";
    unsigned int nPort = 80;
    std::string sUser = "USER";   //可为空
    std::string sPwd = "PWD";     //可为空 
 
    //这边用智能指针更好
    sys_curl* pCluster_Curl = new sys_curl(sIP, nPort, sUser, sPwd);
    if(NULL == pCluster_Curl)
    {
        //创建Curl对象失败
        printf("new object failure!!!!!\n");
        return -1;
    }
    
    //curl初始化
    nCode = pCluster_Curl->initCurlResource();
    if(0 != nCode)
    {
        EPRINT("curl init failure!!!!!\n");
        delete pCluster_Curl;
        pCluster_Curl = NULL;
        return -1;
    }
    
    //设置路径
    std::string sUrlPath = "";
    pCluster_Curl->setUrlPath(sUrlPath);
    
    //上传文件名
    std::string sFileName = "./b.zip";
    std::string sRec;
    nCode = pCluster_Curl->uploadFile(sFileName, sRec);
    printf("%d\n", nCode);
    printf("%s\n", sRec.c_str());
        
    delete pCluster_Curl;
    
    return nCode;
    
}
 
/*
    * 下载文件
    * 返回值int, 0表示成功,1表示超时, 其它表示失败
*/
int curl_download_file()
{
    int nCode = -1;
    std::string sIP = "10.200.0.225";
    unsigned int nPort = 80;
    std::string sUser = "USER";   //可为空
    std::string sPwd = "PWD";     //可为空 
 
    //这边用智能指针更好
    sys_curl* pCluster_Curl = new sys_curl(sIP, nPort, sUser, sPwd);
    if(NULL == pCluster_Curl)
    {
        //创建Curl对象失败
        printf("new object failure!!!!!\n");
        return -1;
    }
    
    //curl初始化
    nCode = pCluster_Curl->initCurlResource();
    if(0 != nCode)
    {
        EPRINT("curl init failure!!!!!\n");
        delete pCluster_Curl;
        pCluster_Curl = NULL;
        return -1;
    }
    
    //设置路径
    std::string sUrlPath = "";
    pCluster_Curl->setUrlPath(sUrlPath);
    
    //下载文件名
    std::string sFileName = "./index.php";
    int nFormat = FORMAT_JSON;
    nCode = pCluster_Curl->downloadFile(sFileName, nFormat);
    printf("%d\n", nCode);
        
    delete pCluster_Curl;
    
    return nCode;
}
 
 
/*
    * curl使用方式
    * 1.curl全局资源初始化,放在主线程中
    * 2.创建curl对象，进行curl参数初始化
    * 3.调用发送数据函数sendMsg,上传文件函数uploadFile,下载文件函数downloadFile
    * 4.curl全局资源清除,放在主线程中
*/
 
int main()
{
    //全局资源初始化，放在主线程
    sys_curl::globalInit();
    
    
    //发送数据操作
    // curl_get_message();
    curl_post_message();
 
    //上传,下载操作
    //curl_download_file();
    // curl_upload_file();
    
    
    //全局资源清除，放在主线程中
    sys_curl::globalCleanup();
        
    return 0;
    
            
}
