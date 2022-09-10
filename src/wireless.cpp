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
    <button onclick=\"set1(\'16\')\" style=\"width:100px;height:60px\"> С������ </button>\
    <button onclick=\"set1(\'32\')\" style=\"width:100px;height:60px\"> ���ֿ��� </button>\
    <button onclick=\"set2(\'1\')\" style=\"width:100px;height:60px\"> ������ʾ </button>\
    <button onclick=\"set2(\'2\')\" style=\"width:100px;height:60px\"> ������ʾ </button>\
    <br/>\
    <br/>\
    <button onclick=\"set(\'refresh\')\" style=\"width:100px;height:60px\"> ��ʫ�� </button>\
    <button onclick=\"set(\'User\')\" style=\"width:100px;height:60px\"> �û����� </button>\
    <button onclick=\"test()\" style=\"width:100px;height:60px\"> �Զ����� </button>\
    <p>����������</p>\
    <textarea id=\"data\"  cols=\"40\" rows=\"25\" style=\"font-size:30px;color:blue;\" placeholder=\"�������ı�\"></textarea>\
    <p>�ļ��ϴ���</p>\
    <form method=\"POST\" enctype=\"multipart/form-data\">\
    <input type=\"file\" name=\"data\">\
    <input class=\"button\" type=\"submit\" value=\"�ϴ�\">\
    </form>\
    <br/>\
    <br/>\
    <button onclick=\"set3(\'Format\')\" > ��ʽ���ļ�ϵͳ </button>\
    <br/>\
    <br/>\
    <p>˵��:������Ҫ���ļ��ϴ�(�����õ�),�������Ⳣ�Ը�ʽ���ļ�ϵͳ��<br/>��ʫ��:�����ʾʫ��(Ŀǰֻ�д�������ҹ)<br/>�û�����:�����û��������İ�(���ܿ�����)<br/>�Զ�����:��ʾ������ı�����<br/>����:V�ؾ�V �汾:1.2</p>\
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

void handleFileRead(void) {            //���������HTTP����
   server.send(200, "text/html", HTML);// ���ҽ����ļ����ظ������
}


void handleFileUpload(){  
  HTTPUpload& upload = server.upload();
  
  if(upload.status == UPLOAD_FILE_START){                     // ����ϴ�״̬ΪUPLOAD_FILE_START
    
    String filename = upload.filename;                        // �����ַ����������ڴ���ϴ��ļ���
    if(!filename.startsWith("/")) filename = "/" + filename;  // Ϊ�ϴ��ļ���ǰ����"/"
    Serial.println("File Name: " + filename);                 // ͨ�����ڼ���������ϴ��ļ�������

    fsUploadFile = SPIFFS.open(filename, "w");            // ��SPIFFS�н����ļ�����д���û��ϴ����ļ�����
    
  } else if(upload.status == UPLOAD_FILE_WRITE){          // ����ϴ�״̬ΪUPLOAD_FILE_WRITE      
    
    if(fsUploadFile)
      fsUploadFile.write(upload.buf, upload.currentSize); // ��SPIFFS�ļ�д��������������ļ�����
      
  } else if(upload.status == UPLOAD_FILE_END){            // ����ϴ�״̬ΪUPLOAD_FILE_END 
    if(fsUploadFile) {                                    // ����ļ��ɹ�����
      fsUploadFile.close();                               // ���ļ��ر�
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
    server.on("/",   // ����ͻ���ͨ��uploadҳ��
                    HTTP_POST,        // ������������ļ�(���󷽷�POST)
                    respondOK,        // ��ظ�״̬�� 200 ���ͻ���
                    handleFileUpload);// �������д����ļ��ϴ�����
    server.on("/set",Update_display); 
    server.on("/set1",conf1); 
    server.on("/set2",conf2); 
    server.on("/set3",conf3); 
    server.onNotFound(handleFileRead);
    server.begin();
}