#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
using namespace std;
class app{
    private:
        int sock;
        int port;
        string ipAddress;
        sockaddr_in hint;
        int connectRes;
        char buf[4096];
        string userInput;
        int bytesReceived;
        char* error;
        int reVal;
        char* nut;
        string result;
    public:
        app();
        void toServer(string );
};
int main(){
    app ap;
}
app :: app(){
    sock = socket(AF_INET, SOCK_STREAM, 0);
    port = 54000;
    string ipAddress = "127.0.0.1";
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);
    connectRes = connect(sock, (sockaddr*)&hint, sizeof(hint));
    while(true){
        memset(buf, 0, 4096);
        cout<<"\n1.to register\n"
            <<"2.to login\n"
            <<"3.to tweet\n"
            <<"4.to view tweets\n"
            <<"5.to like a tweet\n"
            <<"6.to view likes of tweet\n"
            <<"7.to retweet\n"
            <<"8.to delete account\n";
        cout << "> ";
        getline(cin, userInput);
        if(userInput=="1"){
            string Uname; string pass;
            cout<<"Enter username:"; cin>>Uname;
            cout<<"Enter password:"; cin>>pass;
            userInput+="."+Uname+" "+pass;
            toServer(userInput);
            reVal=read(sock,buf,4096);
            if(buf!="---"){
                cout<<buf;
            }
        }
        if(userInput=="2"){
            string Uname;
            cout<<"Enter username:"; cin>>Uname;
            userInput+="."+Uname;
            toServer(userInput);
            reVal=read(sock,buf,4096);
            cout<<buf;
        }
        if(userInput=="3"){
            string tweet;
            cout<<"Enter tweet:";
            getline(cin,tweet);
            userInput+="."+tweet;
            toServer(userInput);
        }
        if(userInput=="4"){
            toServer(userInput);
            reVal=read(sock,buf,4096);
            int n=sizeof(buf)/sizeof(buf[0]);
            for(int i=0;i<n;i++){
                if(buf[i]!='|'){
                    cout<<buf[i];
                }
                else if(buf[i]=='|'){
                    cout<<endl;
                }
            }
        }
        if(userInput=="5"){
            string tweetID;
            cout<<"Enter tweet id:"; cin>>tweetID;
            userInput+="."+tweetID;
            toServer(userInput);
        }
        if(userInput=="6"){
            string id;
            cout<<"Enter tweet id:"; cin>>id;
            userInput+=id;
            toServer(userInput);
            reVal=read(sock,buf,4096);
            int n=sizeof(buf)/sizeof(buf[0]);
            for(int i=0;i<n;i++){
                if(buf[i]!='|'){
                    cout<<buf[i];
                }
                else if(buf[i]=='|'){
                    cout<<endl;
                }
            }
        }
        if(userInput=="7"){
            string tweetID;
            cout<<"Enter tweet id:"; cin>>tweetID;
            userInput+=tweetID;
            toServer(userInput);
        }
        if(userInput=="8"){
            toServer(userInput);
        }
    } ;
    close(sock);
}
void app :: toServer(string s){
    int sendRes=send(sock,s.c_str(),s.size()+1,0);
}