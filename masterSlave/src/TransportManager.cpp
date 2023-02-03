/*
 * TransportManager.cpp
 *
 *  Created on: 21 Dec 2022
 *      Author: tasneem
 */

#include "TransportManager.h"
#include "ConnectionChanel.h"
#include "MDSMessage.h"
#include "stdlib.h"
#include "MessageTransmission.h"
#include "SlaveManager.h"
TransportManager::TransportManager() {
	// TODO Auto-generated constructor stub
	cout<<"manager empty c'tor here" <<endl;

}

TransportManager::~TransportManager() {
	// TODO Auto-generated destructor stub
}

/*void TransportManager::ReadPortsFromSetting(){
    std::ifstream ifs { R"(/home/sewar/eclipse-workspace/gpms/src/setting.json)" };
    if ( !ifs.is_open() )
    {
        std::cerr << "Could not open file for reading!\n";
        return;
    }

    IStreamWrapper isw { ifs };

    Document doc {};
    doc.ParseStream( isw );
    assert(doc.IsObject());
    assert(doc.HasMember("Key"));
    assert(doc["Key"].IsString());
    printf("Key value = %s\n", doc["Key"].GetString());
    const Value& a = doc["connections"]["tcp"];
    assert(a.IsArray());

    int temp;
    for (SizeType i = 0; i < a.Size(); i++) {
    		temp=a[i]["port"].GetInt();
            ports_list.push_back(temp);

    }
    StringBuffer buffer {};
    Writer<StringBuffer> writer { buffer };
    doc.Accept( writer );

    if ( doc.HasParseError() )
    {
        std::cout << "Error  : " << doc.GetParseError()  << '\n'
                  << "Offset : " << doc.GetErrorOffset() << '\n';
        return;
    }

}
*/

void TransportManager::StartListening(){
	cout << "istening" << endl;
	bool stay_in=1;
	do{
		int port_number = 8000;
	    sockaddr_in client;
	    socklen_t clientSize = sizeof(client);
	    char host[NI_MAXHOST];      // Client's remote name
	    char service[NI_MAXSERV];   // Service (i.e. port) the client is connect on
	    uint8_t buf[4096];
	    vector<char> temp_message;

		int listening = socket(AF_INET, SOCK_STREAM, 0);
	    if (listening == -1)
	    {
	        cerr << "Can't create a socket! Quitting" << endl;
	        exit(0);
	    }

	    // Bind the ip address and port to a socket
	    sockaddr_in hint;
	    hint.sin_family = AF_INET;
	    hint.sin_port = htons(port_number);
	    inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);
	    bind(listening, (sockaddr*)&hint, sizeof(hint));
	    listen(listening, SOMAXCONN);

	    int clientSocket = accept(listening, (sockaddr*)&client, &clientSize);

	    memset(host, 0, NI_MAXHOST); // same as memset(host, 0, NI_MAXHOST);
	    memset(service, 0, NI_MAXSERV);

	    if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
	    {
	        cout << host << " 2.connected on port " << service << endl;
	    }
	    else
	    {
	        inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
	        cout << host << " 1.connected on port " << ntohs(client.sin_port) << endl;
	    }

	    close(listening);

	    while (true)
	    {
	    	temp_message.clear();
	        memset(buf, 0, 4096);

	        // Wait for client to send data
	        int bytesReceived = recv(clientSocket, buf, 4096, 0);
	        if (bytesReceived == -1)
	        {
	            cerr << "Error in recv(). Quitting" << endl;
	            close(clientSocket);
	            //continue;
	            break;
	        }

	        if (bytesReceived == 0)
	        {
	            cout << "Client disconnected " << endl;
	            close(clientSocket);
	            //stay_in = 0;
	            break;
	        }
	        cout << bytesReceived << endl;
	        int i=0;
	        while(i<bytesReceived){
	        	printf("%c",buf[i]+'0');
	        	i++;
	        }


	        // Get the message ready to pass it using the SlaveManager::getMessage
        	// Here I made the assumption that
	        uint8_t fCode = buf[7]; //uint8_t for 1 byte and 16 for 2 bytes
	        int index = 8;

	        SlaveManager::sendMessage(fCode, buf, index);

	    }
	}while(stay_in);

}
//////////////////////// uncomplete function - try only  /////////////////////////////////////////
//MDSMessage TransportManager::HandleMessage(zvector<char> message){
//	MDSMessage* msg = new MDSMessage();
//	string function_code_1 = "0F";
//
//	string func_code_in_msg ="";
//	func_code_in_msg += message[6]+ message[5]; // concatenate two strings to get the full function code
//	string str = "0F";
//	if(!function_code_1.compare(func_code_in_msg)){
//		msg->setFunctionCode(0f);
//		cout<<"this is read function code and you should write to holding table"<<endl;
//	}
//	return msg;
//}
