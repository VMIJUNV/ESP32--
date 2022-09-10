#include"wireless.h"

const char* ssid = "Dear Zhuang JieNi";  // Enter your SSID here
const char* password = "123456789";  //Enter your Password here

// IP Address details
IPAddress local_ip(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
WebServer server(80);  // Object of WebServer(HTTP port, 80 is defult)

File fsUploadFile;   

String HTML = "<!DOCTYPE html>\
<html lang=\"zh-CN\">\
<head>\
  <meta charset=\"GB2312\">\
</head>\
<body>\
	<center>\
    <button onclick=\"set1(\'16\')\" style=\"width:100px;height:60px\"> 小字宋体 </button>\
    <button onclick=\"set1(\'32\')\" style=\"width:100px;height:60px\"> 大字楷体 </button>\
    <button onclick=\"set2(\'1\')\" style=\"width:100px;height:60px\"> 横屏显示 </button>\
    <button onclick=\"set2(\'2\')\" style=\"width:100px;height:60px\"> 竖屏显示 </button>\
    <br/>\
    <br/>\
    <button onclick=\"set(\'refresh\')\" style=\"width:100px;height:60px\"> 古诗词 </button>\
    <button onclick=\"set(\'User\')\" style=\"width:100px;height:60px\"> 用户配置 </button>\
    <button onclick=\"test()\" style=\"width:100px;height:60px\"> 自定文字 </button>\
    <p>文字输入区</p>\
    <textarea id=\"data\"  cols=\"40\" rows=\"25\" style=\"font-size:30px;color:blue;\" placeholder=\"请输入文本\"></textarea>\
    <p>文件上传区</p>\
    <form method=\"POST\" enctype=\"multipart/form-data\">\
    <input type=\"file\" name=\"data\">\
    <input class=\"button\" type=\"submit\" value=\"上传\">\
    </form>\
    <br/>\
    <br/>\
    <button onclick=\"set3(\'Format\')\" > 格式化文件系统 </button>\
    <br/>\
    <br/>\
    <p>说明:尽量不要用文件上传(调试用的),出现问题尝试格式化文件系统。<br/>古诗词:随机显示诗词(目前只有春江花月夜)<br/>用户配置:导入用户的配置文案(功能开发中)<br/>自定文字:显示输入的文本内容<br/>作者:V秘君V 版本:1.2</p>\
	</center>\
</body>\
<script>\
	function set(arg) {\
		var xhr = new XMLHttpRequest();\
		xhr.open(\'GET\', \'/set?value=\' + arg, true);\
		xhr.send();\
	}\
  function set1(arg) {\
		var xhr = new XMLHttpRequest();\
		xhr.open(\'GET\', \'/set1?value=\' + arg, true);\
		xhr.send();\
	}\
  function set2(arg) {\
		var xhr = new XMLHttpRequest();\
		xhr.open(\'GET\', \'/set2?value=\' + arg, true);\
		xhr.send();\
	}\
  function set3(arg) {\
		var xhr = new XMLHttpRequest();\
		xhr.open(\'GET\', \'/set3?value=\' + arg, true);\
		xhr.send();\
	}\
  function test(){\
    set(document.getElementById(\"data\").value.replace(/[\\n]/g,\'|\'));\
  }\
</script>\
</html>";
//
void respondOK(){
  server.send(200);
}

void handleFileRead(void) {            //处理浏览器HTTP访问
   server.send(200, "text/html", HTML);// 并且将该文件返回给浏览器
}


void handleFileUpload(){  
  HTTPUpload& upload = server.upload();
  
  if(upload.status == UPLOAD_FILE_START){                     // 如果上传状态为UPLOAD_FILE_START
    
    String filename = upload.filename;                        // 建立字符串变量用于存放上传文件名
    if(!filename.startsWith("/")) filename = "/" + filename;  // 为上传文件名前加上"/"
    Serial.println("File Name: " + filename);                 // 通过串口监视器输出上传文件的名称

    fsUploadFile = SPIFFS.open(filename, "w");            // 在SPIFFS中建立文件用于写入用户上传的文件数据
    
  } else if(upload.status == UPLOAD_FILE_WRITE){          // 如果上传状态为UPLOAD_FILE_WRITE      
    
    if(fsUploadFile)
      fsUploadFile.write(upload.buf, upload.currentSize); // 向SPIFFS文件写入浏览器发来的文件数据
      
  } else if(upload.status == UPLOAD_FILE_END){            // 如果上传状态为UPLOAD_FILE_END 
    if(fsUploadFile) {                                    // 如果文件成功建立
      fsUploadFile.close();                               // 将文件关闭
      server.send(200, "text/html", HTML);
      server.send(200);
      Update_display_Read();
    } 
  }
}

void conf1()
{
  String state =server.arg("value");
  SPIFFS_Write((char*)"/couf1.txt",(char*)state.c_str());
  Update_display_Read();
}

void conf2()
{
  String state =server.arg("value");
  SPIFFS_Write((char*)"/couf2.txt",(char*)state.c_str());
  Update_display_Read();
}

void conf3()
{
  String state =server.arg("value");
  SPIFFS.format();
  SPIFFS_Write((char*)"/couf1.txt",(char*)"16");
  SPIFFS_Write((char*)"/couf2.txt",(char*)"2");
  SPIFFS_Write((char*)"/coufig.txt",(char*)"refresh");
  Update_display_Read();
}

void Init_wireless(){
    WiFi.softAP(ssid, password);
    WiFi.softAPConfig(local_ip, gateway, subnet);
    server.on("/",   // 如果客户端通过upload页面
                    HTTP_POST,        // 向服务器发送文件(请求方法POST)
                    respondOK,        // 则回复状态码 200 给客户端
                    handleFileUpload);// 并且运行处理文件上传函数
    server.on("/set",Update_display); 
    server.on("/set1",conf1); 
    server.on("/set2",conf2); 
    server.on("/set3",conf3); 
    server.onNotFound(handleFileRead);
    server.begin();
}