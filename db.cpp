#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include <stdio.h>
#include <time.h>
using namespace std;
class DB{
    private:
        vector<string> Lines;
        vector<string> tables_name;
        vector<string> types;
        vector<string> field_name;
        vector<int> sizes;
        vector<int> is_unique;
        vector<int> rows_of_table;
    public:
        int co;
        DB();
        vector<string> simple_parse(string );
        int insert(vector<string> , vector<string> , vector<int> , vector<int> , vector<int> , vector<string> );
        int select(vector<string> ,vector<int> ,vector<string> ,string );
        int Delete(vector<string> ,vector<int> ,vector<string> ,string );
        int update(vector<string> ,vector<int> ,vector<string> ,string );
        string **file_to_array(string ,int ,int );
        string clear_space(string );
        int file_line_counter(ifstream& );
        bool is_int(string );
        bool is_bool(string );
        void getOrder();
        vector<string> Union(vector<string> , vector<string> );
        vector<string> Intersection(vector<string> , vector<string> );
        string vector_to_string(vector<string> );
        vector<string> string_to_vector(string );
        vector<int> strVect_to_intVect(vector<string> );
        vector<string> intVect_to_strVect(vector<int> );
        vector<string> parse_expr(string );
        vector<string> new_parse(string );
        vector<string> getID(string ,vector<string> ,string );
        vector<string> paar_for_ex(string );
        vector<string> parse_for_select(string );
        int largest(vector<int> );
        void print_vector(vector<string> vec ){
            for(int i=0; i<vec.size(); i++){
        cout<<vec[i]<<' ';
    }
    cout<<'\n';
}
};
class server{
    private:
        int listening;
        sockaddr_in hint;
        sockaddr_in client;
        socklen_t clientSize;
        int clientSocket;
        char host[NI_MAXHOST];
        char service[NI_MAXSERV];
        char buf[4096];
        string logedIn;
        char* error;
        char* nut;
        string result;
        vector<vector<string> > fileVect_delete_tweet;
    public:
        server();
        void register_new_user(string ,string );
        void login(string );
        string re(string );
        const string currentDateTime();
        void tweet(string ,string );
        void view();
        void like(string ,string );
        void view_likes_of_tweet(string );
        void retweet(string ,string );
        void delteAccount(string );
};
int main(){
    cout<<"1.Shell\n"
        <<"2.Run the server\n";
    cout<<">>";
    int c; cin>>c;
    if(c==1){
        DB database;
    }
    else if(c==2){
        cout<<"Running server......\n";
        server srv;
    }
    else{
        cout<<"Invalid.\n";
        main();
    }
}
DB :: DB(){
    co=0;
    ifstream readSchema("schema.txt",ios::in);
    string line;
    int counter=0;
    while(getline(readSchema,line)){
        if(line!=""){
            Lines.push_back(line);
        }
        else{
            Lines.push_back(",");
        }
        counter++;
    }
    tables_name.push_back(Lines[0]);
    for(int l=1; l<counter; l++){
        if(Lines[l]==","){
            tables_name.push_back(Lines[l+1]);
        }
    }
    for(int k=0; k<counter; k++){
        if(Lines[k]!=","){
            vector<string> temp;
            string t="";
            for(int q=0; q<Lines[k].length(); q++){
                string line0 = Lines[k];
                if(line0[q]!=' '){
                    t+=line0[q];
                }
                else if(line0[q]==' '){
                    temp.push_back(t);
                    t="";
                }
            }
            temp.push_back(t);
            for(int i=0; i<temp.size(); i++){
                if(temp[i]=="UNIQUE"){
                    field_name.push_back(temp[0]);
                    is_unique.push_back(1);
                    if(temp[i+1].substr(0,4)=="CHAR"){
                        types.push_back("CHAR");
                        string sizee="";
                        for(int n=5;n<temp[i+1].length(); n++){
                            if(temp[i+1][n]!=')'){
                                sizee+=temp[i+1][n];
                            }
                        }
                        int b = stoi(sizee);
                        sizes.push_back(b);
                        sizee="";
                    }
                    else if(temp[i+1]=="INTEGER"){
                        types.push_back("INTEGER");
                        sizes.push_back(0);
                    }
                    else if(temp[i+1]=="BOOLEAN"){
                        types.push_back("BOOLEAN");
                        sizes.push_back(0);
                    }
                    else if(temp[i+1]=="TIMESTAMP"){
                        types.push_back("TIMESTAMP");
                        sizes.push_back(0);
                    }
                    i++;
                }
                else if(temp[i]=="INTEGER"){
                    field_name.push_back(temp[0]);
                    types.push_back("INTEGER");
                    sizes.push_back(0);
                    is_unique.push_back(0);
                }
                else if(temp[i]=="BOOLEAN"){
                    field_name.push_back(temp[0]);
                    types.push_back("BOOLEAN");
                    sizes.push_back(0);
                    is_unique.push_back(0);
                }
                else if(temp[i]=="TIMESTAMP"){
                    field_name.push_back(temp[0]);
                    types.push_back("TIMESTAMP");
                    sizes.push_back(0);
                    is_unique.push_back(0);
                }
                else if(temp[i].substr(0,4)=="CHAR"){
                    field_name.push_back(temp[0]);
                    types.push_back("CHAR");
                    string sizee0="";
                    for(int m=5;m<temp[i].length(); m++){
                        if(temp[i][m]!=')'){
                            sizee0+=temp[i][m];
                        }
                    }
                    int a = stoi(sizee0);
                    sizes.push_back(a);
                    is_unique.push_back(0);
                }
            }
        }
    }
    int cntr(0);
    for(int ii=0; ii<Lines.size(); ii++){
        if(Lines[ii]!=","){
            cntr++;
        }
        else if(Lines[ii]==","){
            cntr--;
            rows_of_table.push_back(cntr);
            cntr=0;
        }
    }
    cntr--;
    rows_of_table.push_back(cntr);
    getOrder();
}
void DB :: getOrder(){
    while(true){
        string input;
        cout<<" >>";
        cin.ignore();
        getline(cin,input);
        int r=input.length();
        if(input[r-1]!=';'){
            cout<<"need ;\n";
            getOrder();
        }
        if(co>0){
            if(input[0]=='N'){
                input="I"+input;
            }
            if(input.substr(0,4)=="ELEC"){
                input="S"+input;
            }
            if(input.substr(0,4)=="ELET"){
                input="D"+input;
            }
            if(input[0]=='P'){
                input="U"+input;
            }
        }
        if(input.substr(0,6)=="INSERT"){
            vector<string> order=simple_parse(input);
            order=simple_parse(input);
            insert(tables_name,types,sizes,rows_of_table,is_unique,order);
        }
        else if(input.substr(0,6)=="SELECT"){
            vector<string> order=simple_parse(input);
            order=simple_parse(input);
            select(tables_name,rows_of_table,field_name,input);
        }
        else if(input.substr(0,6)=="DELETE"){
            vector<string> order=simple_parse(input);
            order=simple_parse(input);
            Delete(tables_name,rows_of_table,field_name,input);
        }
        else if(input.substr(0,6)=="UPDATE"){
            vector<string> order=simple_parse(input);
            order=simple_parse(input);
            update(tables_name,rows_of_table,field_name,input);
        }
        else{
            cout<<"0Invalid input.\n";
            getOrder();
        }
        co++;
    }
}
bool DB :: is_int(string s){
    for(int i=0; i<s.length(); i++){
        if(!(s[i]+0>47 && s[i]+0<58))
            return false;
    }
    return true;
}
bool DB :: is_bool(string s){
    if(s=="true" || s=="false")
        return true;
    return false;
}
vector<string> DB :: simple_parse(string in){
    vector<string> parse;
    string str="";
    for(int i=0; i<in.length(); i++){
        if(in[i]!=' ' && in[i]!='(' && in[i]!=')' && in[i]!=','){
            str+=in[i];
        }
        else if(in[i]=='('){
            parse.push_back(str);
            str="";
            for(int k=i+1; k<in.length(); k++){
                if(in[k]!='(' && in[k]!=')' && in[k]!=','){
                    str+=in[k];
                }
                else{
                    parse.push_back(str);
                    str="";
                }
            }
            break;
        }
        else{
            parse.push_back(str);
            str="";
        }
    }
    vector<string> clean_parse;
    for(int j=0; j<parse.size(); j++){
        if(parse[j]!=""){
            clean_parse.push_back(parse[j]);
        }
    }
    return clean_parse;
}
string** DB :: file_to_array(string file_name,int valnum,int rows){
    string **arr;
    ifstream file(file_name,ios::in);
    arr = new string *[rows];
    for(int i=0; i<rows; i++){
        arr[i]=new string[valnum];
    } 
    for(int j=0;j<rows;j++){
        for(int k=0; k<valnum;k++)
            arr[j][k]="00";
    }
    string a;
    for(int n=0; n<rows; n++){
        for(int m=0; m<valnum; m++){
            file>>a;
            arr[n][m]=a;
        }
    }
    return arr;
}
int DB :: file_line_counter(ifstream& file){
    string s;
    int c=0;
    while(getline(file,s)){c++;}
    return c;
}
int DB :: insert(vector<string> tables, vector<string> types, vector<int> sizes, vector<int> number_of_fields, vector<int> is_unique, vector<string> order){
    string filename; int val_counter(0);
    int indexName; vector<string> values;
    if(order[1]!="INTO"){
        cout<<"invalid input.\n";
        getOrder();
    }
    if(order[3]!="VALUES"){
        cout<<"invalid input.\n";
        getOrder();
    }
    for(int i=0; i<order.size(); i++){
        if(order[i]=="INTO"){
            filename=order[i+1];
        }
        if(order[i]=="VALUES"){
            for(int j=i+1; j<order.size(); j++){
                val_counter++;
                values.push_back(order[j]);
            }
        }
    }
    
    int nameCtr=0;
    for(int x=0; x<tables.size(); x++){
        if(tables[x]==filename)
            nameCtr++;
    }
    if(nameCtr==0){
        cout<<"Invalid input.\n";
        getOrder();
    }
    if(filename=="users_table" or filename=="likes_table" or filename=="tweets_table"){
        cout<<"Don't touch that table!!!\n";
        getOrder();
    }
    string file_name=filename+".txt";
    ofstream makefile(file_name,ios::app);
    ifstream read_table(file_name,ios::in);
    int rows=file_line_counter(read_table);
    string l; int id_line_counter;

    int number_of_vals;
    for(int n=0; n<tables.size(); n++){
        if(tables[n]==filename){
            indexName=n;
            number_of_vals=number_of_fields[n];
        }
    }
    if(number_of_vals!=val_counter){
        cout<<"Invalid input.\n";
        getOrder();
    }
    vector<string> ty; vector<string> si; vector<string> u; int start(0); int end;
    for(int m=0; m<=indexName; m++){
        start+=number_of_fields[m];
    }
    start-=number_of_vals;
    end=start+number_of_vals;
    for(int k=start; k<end; k++){
        ty.push_back(types[k]);
        si.push_back(to_string(sizes[k]));
        u.push_back(to_string(is_unique[k]));
    }
    for(int q=0; q<values.size(); q++){
        if(ty[q]=="CHAR"){
            if(values[q].length()>stoi(si[q])){
                cout<<"Invalid input.\n";
                getOrder();
            }
        }
        if(ty[q]=="INTEGER"){
            if(!(is_int(values[q]))){
                cout<<"Invalid input.\n";
                getOrder();
            }
        }
        if(ty[q]=="BOOLEAN"){
            if(!(is_bool(values[q]))){
                cout<<"Invalid input.\n";
                getOrder();
            }
        }
    }
    string **file_arr;
    file_arr = file_to_array(file_name,number_of_vals+1,rows);
    for(int e=0; e<values.size(); e++){
        if(u[e]=="1"){
            for(int p=0;p<rows;p++){
                if(values[e]==file_arr[p][e+1]){
                    cout<<"Invalid value.\n";
                    getOrder();
                }
            }
        }
    }
    ofstream file_to_write(file_name,ios::app);
    file_to_write<<rows+1<<' ';
    for(int h=0;h<values.size();h++){
        if(u[h]!="00"){
            if(ty[h]=="CHAR")
                if(values[h].length()<stoi(si[h]))
                    file_to_write<<values[h]<<' ';
            if(ty[h]=="INTEGER")
                if(is_int(values[h]))
                    file_to_write<<values[h]<<' ';
            if(ty[h]=="BOOLEAN")
                if(is_bool(values[h]))
                    file_to_write<<values[h]<<' ';
            if(ty[h]=="TIMESTAMP")
                file_to_write<<values[h]<<' ';
        }  
    }
    file_to_write<<endl;
    return 1;
}
int DB :: select(vector<string> tables,vector<int> number_of_fields,vector<string> field_name,string expr){
    vector<string> v=parse_for_select(expr); 
    int nnn=v.size();
    string exx=v[nnn-1];
    vector<string> ka=paar_for_ex(exx);
    if(v[1]!="FROM"){
        cout<<"Invalid input.\n";
        getOrder();
    }
    string filename=v[2];
    if(filename=="users_table" or filename=="likes_table" or filename=="tweets_table"){
        cout<<"Don't touch that table!!!\n";
        getOrder();
    }
    vector<string> need_id;
    for(int i=0;i<ka.size();i++){
        if(ka[i]!="|" && ka[i]!="&" && ka[i]!="(" && ka[i]!=")"){
            need_id.push_back(ka[i]);
        }
    }
    int number_of_vals; int indexName;
    for(int n=0; n<tables.size(); n++){
        if(tables[n]==filename){
            indexName=n;
            number_of_vals=number_of_fields[n];
        }
    }
    vector<string> fields; int start(0); int end;
    for(int m=0; m<=indexName; m++){
        start+=number_of_fields[m];
    }
    start-=number_of_vals;
    end=start+number_of_vals;
    for(int k=start; k<end; k++){
        fields.push_back(field_name[k]);
    }
    string file=filename+".txt";
    vector<string> stringIDz; string lil; vector<string> temp;
    for(int i=0;i<need_id.size();i++){
        temp=getID(need_id[i],fields,file);
        lil=vector_to_string(temp);
        stringIDz.push_back(lil);
    }
    vector <string> m;
    m=parse_for_select(expr);
    int n=m.size();
    string ex=m[n-1]; vector<string> vectEx; vector<string> t; int c(0); string exprStr="";
    vectEx=paar_for_ex(ex);
    for(int j=0; j<vectEx.size();j++){
        if(vectEx[j]=="(" or vectEx[j]==")" or vectEx[j]=="&" or vectEx[j]=="|"){
            t.push_back(vectEx[j]);
        }
        else{
            t.push_back(stringIDz[c]);
            c++;
        }
    }
    for(int z=0;z<t.size();z++){
        exprStr+=t[z];
    }
    vector<string> parse_shode;
    parse_shode = parse_expr(exprStr);
    vector<string> idiz; string ttt="";
    for(int x=0;x<parse_shode[0].length();x++){
        if(parse_shode[0][x]!='.'){
            ttt+=parse_shode[0][x];
        }
        else{
            idiz.push_back(ttt);
            ttt="";
        }
    }
    idiz.push_back(ttt);
    string **Lofi;
    ifstream ff(file,ios::in);
    int lines=file_line_counter(ff);
    int valnum=fields.size();
    Lofi=file_to_array(file,valnum+1,lines);
    for(int a=0;a<idiz.size();a++){
        for(int b=0;b<lines;b++){
            if(idiz[a]==Lofi[b][0]){
                for(int w=0;w<valnum+1;w++){
                    cout<<Lofi[b][w]<<' ';
                }
            }
        }
        cout<<endl;
    }
    return 1;
}
int DB :: Delete(vector<string> tables,vector<int> number_of_fields,vector<string> field_name,string expr){
    vector<string> v=parse_for_select(expr); 
    int nnn=v.size();
    string exx=v[nnn-1];
    vector<string> ka=paar_for_ex(exx);
    if(v[1]!="FROM"){
        cout<<"Invalid input.\n";
        getOrder();
    }
    string filename=v[2];
    if(filename=="users_table" or filename=="likes_table" or filename=="tweets_table"){
        cout<<"Don't touch that table!!!\n";
        getOrder();
    }
    vector<string> need_id;
    for(int i=0;i<ka.size();i++){
        if(ka[i]!="|" && ka[i]!="&" && ka[i]!="(" && ka[i]!=")"){
            need_id.push_back(ka[i]);
        }
    }
    int number_of_vals; int indexName;
    for(int n=0; n<tables.size(); n++){
        if(tables[n]==filename){
            indexName=n;
            number_of_vals=number_of_fields[n];
        }
    }
    vector<string> fields; int start(0); int end;
    for(int m=0; m<=indexName; m++){
        start+=number_of_fields[m];
    }
    start-=number_of_vals;
    end=start+number_of_vals;
    for(int k=start; k<end; k++){
        fields.push_back(field_name[k]);
    }
    string file=filename+".txt";
    vector<string> stringIDz; string lil; vector<string> temp;
    for(int i=0;i<need_id.size();i++){
        temp=getID(need_id[i],fields,file);
        lil=vector_to_string(temp);
        stringIDz.push_back(lil);
    }
    vector <string> m;
    m=parse_for_select(expr);
    int n=m.size();
    string ex=m[n-1]; vector<string> vectEx; vector<string> t; int c(0); string exprStr="";
    vectEx=paar_for_ex(ex);
    for(int j=0; j<vectEx.size();j++){
        if(vectEx[j]=="(" or vectEx[j]==")" or vectEx[j]=="&" or vectEx[j]=="|"){
            t.push_back(vectEx[j]);
        }
        else{
            t.push_back(stringIDz[c]);
            c++;
        }
    }
    for(int z=0;z<t.size();z++){
        exprStr+=t[z];
    }
    vector<string> parse_shode;
    parse_shode = parse_expr(exprStr);
    vector<string> idiz; string ttt="";
    for(int x=0;x<parse_shode[0].length();x++){
        if(parse_shode[0][x]!='.'){
            ttt+=parse_shode[0][x];
        }
        else{
            idiz.push_back(ttt);
            ttt="";
        }
    }
    idiz.push_back(ttt);
    string **Lofi;
    ifstream ff(file,ios::in);
    int lines=file_line_counter(ff);
    int valnum=fields.size();
    Lofi=file_to_array(file,valnum+1,lines);
    for(int a=0;a<idiz.size();a++){
        for(int b=0;b<lines;b++){
            if(idiz[a]==Lofi[b][0]){
                for(int w=0;w<valnum+1;w++){
                    Lofi[b][0]="00";
                }
            }
        }
    }
    ofstream write(file,ios::out);
    for(int e=0;e<lines;e++){
        if(Lofi[e][0]!="00")
            for(int r=0;r<valnum+1;r++){
                write<<Lofi[e][r]<<' ';
            }
        write<<endl;
    }
    return 1;
}
int DB :: update(vector<string> tables,vector<int> number_of_fields,vector<string> field_name,string s){
    string s1=""; string s2="";
    for(int ja=0; ja<s.length(); ja++){
        if(s.substr(ja,6)=="VALUES"){
            for(int g=ja+6;g<s.length();g++){
                s2+=s[g];
            }
            break;
        }
        s1+=s[ja];
    }
    vector<string> update_vals;
    update_vals=simple_parse(s2); string gg;
    for(int mm=0;mm<update_vals.size();mm++){
        gg=clear_space(update_vals[mm]);
        update_vals[mm]=gg;
    }
    string expr=s1;
    vector<string> v=new_parse(expr);
    if(v[2]!="WHERE"){
        cout<<"Invalid input.\n";
        getOrder();
    }
    string filename=v[1];
    if(filename=="users_table" or filename=="likes_table" or filename=="tweets_table"){
        cout<<"Don't touch that table!!!\n";
        getOrder();
    }
    vector<string> need_id;
    for(int i=3;i<v.size();i++){
        if(v[i]!="OR" && v[i]!="AND"){
            need_id.push_back(v[i]);
        }
    }
    int number_of_vals; int indexName;
    for(int n=0; n<tables.size(); n++){
        if(tables[n]==filename){
            indexName=n;
            number_of_vals=number_of_fields[n];
        }
    }
    vector<string> fields; int start(0); int end;
    for(int m=0; m<=indexName; m++){
        start+=number_of_fields[m];
    }
    start-=number_of_vals;
    end=start+number_of_vals;
    for(int k=start; k<end; k++){
        fields.push_back(field_name[k]);
    }
    string file=filename+".txt";
    vector<string> stringIDz; string lil; vector<string> temp;
    for(int i=0;i<fields.size();i++){
        temp=getID(need_id[i],fields,file);
        lil=vector_to_string(temp);
        stringIDz.push_back(lil);
    }
    stringIDz.push_back(lil);
    vector <string> m;
    m=parse_for_select(expr);
    int n=m.size();
    string ex=m[n-1]; vector<string> vectEx; vector<string> t; int c(0); string exprStr="";
    vectEx=paar_for_ex(ex);
    for(int j=0; j<vectEx.size();j++){
        if(vectEx[j]=="(" or vectEx[j]==")" or vectEx[j]=="&" or vectEx[j]=="|"){
            t.push_back(vectEx[j]);
        }
        else{
            t.push_back(stringIDz[c]);
            c++;
        }
    }
    for(int z=0;z<t.size();z++){
        exprStr+=t[z];
    }
    vector<string> parse_shode;
    parse_shode = parse_expr(exprStr);
    vector<string> idiz; string ttt="";
    for(int x=0;x<parse_shode[0].length();x++){
        if(parse_shode[0][x]!='.'){
            ttt+=parse_shode[0][x];
        }
        else{
            idiz.push_back(ttt);
            ttt="";
        }
    }
    idiz.push_back(ttt);
    string **Lofi;
    ifstream ff(file,ios::in);
    int lines=file_line_counter(ff);
    int valnum=fields.size();
    Lofi=file_to_array(file,valnum+1,lines);
    Lofi=file_to_array(file,valnum+1,lines);
    for(int a=0;a<idiz.size();a++){
        for(int b=0;b<lines;b++){
            if(idiz[a]==Lofi[b][0]){
                for(int w=0;w<valnum;w++){
                    Lofi[b][w+1]=update_vals[w];
                }
            }
        }
    }
    ofstream write(file,ios::out);
    for(int e=0;e<lines;e++){
        for(int r=0;r<valnum+1;r++){
            write<<Lofi[e][r]<<' ';
        }
        write<<endl;
    }
    return 1;
}
vector<string> DB :: getID(string s,vector<string> fields,string file){
    string **file_array;
    int col=fields.size()+1;
    ifstream fg(file,ios::in);
    int row=file_line_counter(fg);
    file_array=file_to_array(file,col,row);
    vector<string> v;
    string b=""; string a=""; string c="";
    for(int i=0; s.length(); i++){
        if(s[i]!='=' and s[i]!='!'){
            b+=s[i];
        }
        else if(s.substr(i,2)=="!="){
            for(int j=i+2; j<s.length(); j++){
                c+=s[j];
            }
            int indx1=0;
            for(int kk=0; kk<col;kk++){
                if(fields[kk]==b){
                    indx1=kk;
                }
            }
            indx1++;
            for(int zz=0; zz<row; zz++){
                if(file_array[zz][indx1]!=c){
                    if(file_array[zz][0]!="00")
                        v.push_back(file_array[zz][0]);
                }
            }
            break;
        }
        else if(s[i]=='='){
            for(int r=i+1; r<s.length(); r++){
                a+=s[r];
            }
            int indx=0;
            for(int k=0; k<col;k++){
                if(fields[k]==b){
                    indx=k;
                }
            }
            indx++;
            for(int z=0; z<row; z++){
                if(file_array[z][indx]==a){
                    if(file_array[z][0]!="00")
                        v.push_back(file_array[z][0]);
                }
            }
            break;
        }
    }
    return v;
}
vector<string> DB :: parse_expr(string ex){
    vector<string> idz;
    vector<string> nidz;
    vector<string> opz;
    vector<int> vals; int par_counter(0); string s=""; string p;
    for(int i=0;i<ex.length();i++){
        if(ex[i]=='(')
            par_counter++;
        else if(ex[i]==')')
            par_counter--;
        else if(ex[i]=='|'){
            p="|";
            opz.push_back(p);
            vals.push_back(par_counter);
        }
        else if(ex[i]=='&'){
            p="&";
            opz.push_back(p);
            vals.push_back(par_counter);
        }
    }
    for(int j=0; j<ex.length();j++){
        if(ex[j]!='(' && ex[j]!=')' && ex[j]!='|' && ex[j]!='&'){
            s+=ex[j];
        }
        else{
            idz.push_back(s);
            s="";
        }
    }
    idz.push_back(s);
    for(int k=0;k<idz.size();k++){
        if(idz[k]!=""){
            nidz.push_back(idz[k]);
        }
    }
    int siz=opz.size();
    for(int h=0; h<siz; h++){
        int l;//1
        int la=largest(vals);
        for(int z=0;z<vals.size();z++){
            if(vals[z]==la){
                l=z;
                break;
            }
        }
        if(opz[l]=="&"){
            vector<string>v1;
            vector<string>v2;
            vector<string>inV;
            string inS;
            v1=string_to_vector(nidz[l]);
            v2=string_to_vector(nidz[l+1]);
            inV=Intersection(v1,v2);
            inS=vector_to_string(inV);
            nidz[l+1]=inS;
            nidz.erase(nidz.begin()+l);
            opz.erase(opz.begin()+l);
            vals.erase(vals.begin()+l);
            v1.clear();
            v2.clear();
            inV.clear();
        }
        else if(opz[l]=="|"){
            vector<string>v3;
            vector<string>v4;
            vector<string>unV;
            string unS;
            v3=string_to_vector(nidz[l]);
            v4=string_to_vector(nidz[l+1]);
            unV=Union(v3,v4);
            unS=vector_to_string(unV);
            nidz[l+1]=unS;
            nidz.erase(nidz.begin()+l);
            opz.erase(opz.begin()+l);
            vals.erase(vals.begin()+l);
            v3.clear();
            v4.clear();
            unV.clear();
        }
    }
    if(nidz[0]=="0"){
        cout<<"Invalid input.\n";
        getOrder();
    }
    return nidz;
}
vector<string> DB :: Union(vector<string> arr1, vector<string> arr2) {
    vector<int> narr1;
    narr1=strVect_to_intVect(arr1);
    vector<int> narr2;
    narr2=strVect_to_intVect(arr2);
    int m=narr1.size();
    int n=narr2.size();
    vector<int> v;
    int i = 0, j = 0; 
    while (i < m && j < n) 
    { 
        if (narr1[i] < narr2[j]) 
            v.push_back(narr1[i++]); 
        else if (narr2[j] < narr1[i]) 
            v.push_back(narr2[j++]); 
        else{
            v.push_back(narr2[j++]);
            i++;
        }
    }
    while(i < m) 
        v.push_back(narr1[i++]); 
    while(j < n) 
        v.push_back(narr2[j++]); 
    vector<string> nv;
    nv=intVect_to_strVect(v);
    return nv;    
}
vector<string> DB :: Intersection(vector<string> arr1, vector<string> arr2) {   
    vector<int> narr1;
    narr1=strVect_to_intVect(arr1);
    vector<int> narr2;
    narr2=strVect_to_intVect(arr2);
    int m=narr1.size();
    int n=narr2.size();
    vector<int> v;
    int i = 0, j = 0; 
    while (i < m && j < n){ 
        if (narr1[i] < narr2[j]) 
            i++; 
        else if (narr2[j] < narr1[i]) 
            j++; 
        else{ 
            v.push_back(narr2[j]); 
            i++; 
            j++; 
        } 
    }
    vector<string> nv;
    nv=intVect_to_strVect(v);
    if(nv.size()==0){
        nv.push_back("0");
    }
    return nv;
} 
string DB :: vector_to_string(vector<string> v){
    string s="";
    for(int i=0; i<v.size()-1; i++){
        s+=v[i]+".";
    }
    s+=v[v.size()-1];
    return s;
}
vector<string> DB :: string_to_vector(string s){
    vector<string> v;
    string t="";
    for(int i=0; i<s.length(); i++){
        if(s[i]!='.'){
            t+=s[i];
        }
        else if(s[i]=='.'){
            v.push_back(t);
            t="";
        }
    }
    v.push_back(t);
    return v;
}
vector<int> DB :: strVect_to_intVect(vector<string> v){
    vector<int> t;
    for(int i=0;i<v.size(); i++){
        t.push_back(stoi(v[i]));
    }
    return t;
}
vector<string> DB :: intVect_to_strVect(vector<int> v){
    vector<string> t;    
    for(int i=0; i<v.size(); i++){
        t.push_back(to_string(v[i]));
    }
    return t;
}
int DB :: largest(vector<int> arr){
    int n = arr.size();
    int i; int i_max;
    int max = arr[0];  
    for (i = 1; i < n; i++) 
        if (arr[i] > max){
            max = arr[i]; 
        }
    return max; 
}
vector<string> DB :: new_parse(string in){
    vector<string> parse;
    string str="";
    for(int i=0; i<in.length(); i++){
        if(in[i]!=' ' && in[i]!='(' && in[i]!=')' && in[i]!=','){
            str+=in[i];
        }
        else{
            parse.push_back(str);
            str="";
        }
    }
    vector<string> clean_parse;
    for(int j=0; j<parse.size(); j++){
        if(parse[j]!=""){
            clean_parse.push_back(parse[j]);
        }
    }
    return clean_parse;
}
vector<string> DB :: paar_for_ex(string ex){
    string t=""; vector<string> v; string par; vector<string> lastOne;
    for(int j=0;j<ex.length();j++){
        if(ex[j]=='(' or ex[j]==')'){
            par=ex[j];
            v.push_back(t);
            v.push_back(par);
            t="";
        }
        else if(ex[j]!=' ' ){
            t+=ex[j];
        }
        else{
            v.push_back(t);
            t="";
        }
    }
    v.push_back(t);
    for(int k=0; k<v.size(); k++){
        if(v[k]!=""){
            lastOne.push_back(v[k]);
        }
    }
    for(int z=0; z<lastOne.size(); z++){
        if(lastOne[z]=="OR"){
            lastOne[z]="|";
        }
        if(lastOne[z]=="AND"){
            lastOne[z]="&";
        }
    }
    return lastOne;
}
vector<string> DB :: parse_for_select(string in){
    string s="";
    string expr="";
    vector<string> v;
    for(int i=0; i<in.length(); i++){
        if(in[i]!=' '){
            s+=in[i];
        }
        if(in[i]==' '){
            v.push_back(s);
            s="";
        }
        if(in.substr(i,5)=="WHERE"){
            v.push_back("WHERE");
            for(int j=i+5; j<in.length(); j++){
                if(in[j]!=';')
                    expr+=in[j];
            }
            v.push_back(expr);
            break;
        }
    }
    return v;
}
string DB :: clear_space(string s){
    string clean="";
    for(int i=0; i<s.length(); i++){
        if(s[i]!=' ')
            clean+=s[i];
    }
    return clean;
}

////(1.4.6.7.78)|6|2        user=kaveh
/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
server :: server(){
    listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening == -1){
        cerr << "Can't create a socket! Quitting" << endl;
    }
    // Bind the ip address and port to a socket
    hint.sin_family = AF_INET;
    hint.sin_port = htons(54000);
    inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);
    bind(listening, (sockaddr*)&hint, sizeof(hint));
    // Tell Winsock the socket is for listening
    listen(listening, SOMAXCONN);
    // Wait for a connection
    clientSize = sizeof(client);
    clientSocket = accept(listening, (sockaddr*)&client, &clientSize);
    memset(host, 0, NI_MAXHOST); // same as memset(host, 0, NI_MAXHOST);
    memset(service, 0, NI_MAXSERV);
    if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0){
        cout << host << " connected on port " << service << endl;
    }
    else{
        inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
        cout << host << " connected on port " << ntohs(client.sin_port) << endl;
    }
    // Close listening socket
    close(listening);
    // While loop: accept and echo message back to client
    while (true){
        memset(buf, 0, 4096);
        // Wait for client to send data
        int bytesReceived = recv(clientSocket, buf, 4096, 0);
        if (bytesReceived == -1){
            cerr << "Error in recv(). Quitting" << endl;
            break;
        }
        if (bytesReceived == 0){
            cout << "Client disconnected " << endl;
            break;
        }
        string dastor;
        dastor=string(buf, 0, bytesReceived);
        if(dastor[0]=='1'){
            string ss1=""; string ss2="";
            for(int i0=2;i0<dastor.length();i0++){
                if(dastor[i0]!=' ')
                    ss1+=dastor[i0];
                else if(dastor[i0]==' '){
                    for(int j0=i0+1;j0<dastor.length();j0++){
                        ss2+=dastor[j0];
                    }
                    break;
                }    
            }
            register_new_user(ss1,ss2);
        }
        else if(dastor[0]=='2'){
            string s0="";
            for(int i1=2;i1<dastor.length();i1++){
                s0+=dastor[i1];
            }
            login(s0);
        }
        else if(dastor[0]=='3'){
            string s1="";
            for(int i2=2;i2<dastor.length();i2++){
                s1+=dastor[i2];
            }
            tweet(logedIn,s1);
        }
        else if(dastor[0]=='4'){
            view();
        }
        else if(dastor[0]=='5'){
            string s5="";
            for(int i3=2;i3<dastor.length();i3++){
                s5+=dastor[i3];
            }
            like(logedIn,s5);
        }
        else if(dastor[0]=='6'){
            string s6="";
            for(int i4=1;i4<dastor.length();i4++){
                s6+=dastor[i4];
            }
            view_likes_of_tweet(s6);
        }
        else if(dastor[0]=='7'){
            string s7="";
            for(int i5=1;i5<dastor.length();i5++){
                s7+=dastor[i5];
            }
            retweet(logedIn,s7);
        }
        else if(dastor[0]=='8'){
            delteAccount(logedIn);
        }
        // Echo message back to client
        //send(clientSocket, buf, bytesReceived + 1, 0);
    }
    // Close the socket
    close(clientSocket);
}
void server :: register_new_user(string newName,string newPass){
    ifstream user("users_table.txt", ios :: in);
    if(!user){
        cout<<"File could not be opened\n";
        exit(1);
    }
    int user_id; char username[30]; char password[30]; int check=1;
    int counterU=0;
    while(user>>user_id>>username>>password){
        counterU++;
        if(newName==username){
            error="This user name has already taken!";
            send(clientSocket,error,strlen(error),0);
            check=0;
        }
    }
    int lastID = user_id;
    ofstream app_user("users_table.txt", ios::app);
    if (!app_user) {
        cout << "File could not be opened\n";
        exit(1);
    }
    
    int newID;
    if(counterU!=0)
        newID = lastID + 1;
    else{
        newID=1;
    }
    if(check){
        app_user << newID << ' ' << newName << ' ' << newPass << endl;  
        nut="---";
        send(clientSocket,nut,strlen(nut),0); 
    }
}
void server :: login(string s){
    ifstream user("users_table.txt", ios :: in);
    int user_id; char username[30]; char password[30]; int check=1; int c(0);
    int counterU=0;
    while(user>>user_id>>username>>password){
        counterU++;
        if(s==username){
            c++;
        }
    }
    if(c){
        nut="Welcome\n";
        send(clientSocket,nut,strlen(nut),0);
        logedIn=s;
    }
    else{
    error="wrong username";
    send(clientSocket,error,strlen(error),0);
    check=0;
    }
}
void server :: tweet(string u,string tweet1){
    string ti=currentDateTime();
    ifstream userT("users_table.txt",ios::in);
    if(!userT){
        cout<<"File could not be opened\n";
        exit(1);
    }
    int uid; char user[30]; char pass[30];
    int tweet_1stpart_id;
    while(userT>>uid>>user>>pass){
        string name=user;
        if(name==u){
            tweet_1stpart_id=uid;
        }
    }
    int tweet_2ndpart_id=1;
    ifstream user_tweets("tweets_table.txt",ios::in);
    if(!user_tweets){
        cout<<"File could not be opened\n";
        exit(1);
    }
    int p1; int p2; string tweet; string Sid;
    while(user_tweets>>p1>>p2>>Sid){
        getline(user_tweets,tweet);
        if(p1==tweet_1stpart_id)
            tweet_2ndpart_id++;
    }
    tweet1+=" "+ti;
    ofstream in_user_tweets("tweets_table.txt",ios::app);
    if(!in_user_tweets){
        cout<<"File could not be opened\n";
        exit(1);
    }
    string stringID = "0";
    in_user_tweets<<tweet_1stpart_id<<' '<<tweet_2ndpart_id<<' '<<stringID<<' '<<tweet1<<endl;
}
void server :: view(){
    ifstream user("users_table.txt", ios :: in);
    if(!user){
        cout<<"File could not be opened\n";
        exit(1);
    }
    int user_id; char username[30]; char password[30];
    int counterU=0;
    while(user>>user_id>>username>>password){
        counterU++;
    }
    vector<vector<string> > fileVect1;
    for (int i = 0; i < counterU; i++) {
        vector<string> v1;
        for (int j = 0; j < 3; j++)
            v1.push_back("0");
        fileVect1.push_back(v1);
    }
    ifstream vectFile1("users_table.txt", ios::in);
    string ID1; char Uzzzi1[30]; char UziPass1[30]; int i = 0;
    while (vectFile1 >> ID1 >> Uzzzi1 >> UziPass1) {
        string Uzzzziname;
        Uzzzziname = Uzzzi1;
        string UzzzziP;
        UzzzziP = UziPass1;
        fileVect1[i][0]= ID1;
        fileVect1[i][1] = Uzzzziname;
        fileVect1[i][2] = UzzzziP;
        i++;
    }
    ifstream tweetc("tweets_table.txt",ios::in);
    string ss; int tCounter(0);
    while(getline(tweetc,ss)){
        tCounter++;
    }
     vector<string> idd;
    for (int k = 0; k < tCounter; k++) {
        vector<string> v1;
        for (int j = 0; j < 4; j++)
            v1.push_back("0");
        fileVect_delete_tweet.push_back(v1);
    }
    ifstream vectFile6("tweets_table.txt", ios::in);
    string id_1; string id_2; string re_id; string tweet; int w(0);
    while(vectFile6>>id_1>>id_2>>re_id){
        getline(vectFile6,tweet);
        idd.push_back(id_1);
        fileVect_delete_tweet[w][0]=id_1;
        fileVect_delete_tweet[w][1]=id_2;
        fileVect_delete_tweet[w][2]=re_id;
        fileVect_delete_tweet[w][3]=tweet;
        w++;
    }
    for(int h=0;h<counterU;h++){
        for(int f=0;f<tCounter;f++){
            if(fileVect1[h][0]==fileVect_delete_tweet[f][0]){
                fileVect_delete_tweet[f][0]=fileVect1[h][1];
            }
        }
    }
    result="";
    for(int o=0;o<tCounter;o++){
        if(fileVect_delete_tweet[o][2]=="0"){
            result+=idd[o]+"."+fileVect_delete_tweet[o][1]+" "+fileVect_delete_tweet[o][0]+":"+fileVect_delete_tweet[o][3];
        }
        else{
            int ee; string jk=""; string retweeted_from;
            for(int n=fileVect_delete_tweet[o][2].length()-1;n>=0;n--){
                if(fileVect_delete_tweet[o][2][n]=='.'){
                    ee=n;
                    break;
                }
            }
            for(int rt=ee+1;rt<fileVect_delete_tweet[o][2].length();rt++){
                jk+=fileVect_delete_tweet[o][2][rt];
            }
            for(int gt=0;gt<counterU;gt++){
                if(fileVect1[gt][0]==jk){
                    retweeted_from=fileVect1[gt][1];
                    break;
                }
            }
            result+=idd[o]+"."+fileVect_delete_tweet[o][1]+" "+fileVect_delete_tweet[o][0]+" retweeted from "+retweeted_from+":"+fileVect_delete_tweet[o][3];
        }
        result+="|";
    }
    send(clientSocket,result.c_str(),strlen(result.c_str()),0);
}
void server :: like(string Uzer,string tweet_Id){
    int id1; int id2; int i(0); string idid1=""; string idid2="";
    while(i<tweet_Id.length()){
        if(tweet_Id[i]!='.'){
            idid1+=tweet_Id[i];
        }
        if(tweet_Id[i]=='.'){
            for(int j=i+1; j<tweet_Id.length();j++){
                idid2+=tweet_Id[j];
            }
            break;
        }
        i++;
    }
    id1 = stoi(idid1);id2 = stoi(idid2);
    ifstream find_user_id("users_table.txt",ios::in);
    if(!find_user_id){
        cout<<"File could not be opened.\n";
        exit(1);
    }
    int ii; char UN[30]; char Upass[30]; string user_liked;
    while(find_user_id>>ii>>UN>>Upass){
        string s=UN;
        if(s==Uzer){
            user_liked=Uzer;
        }
    }
    ofstream likes("likes_table.txt",ios::app);
    if(!likes){
        cout<<"File could not be opened.\n";
        exit(1);
    }
    string likeID=to_string(id1)+"."+to_string(id2);
    likes<<likeID<<' '<<user_liked<<endl;
}
void server :: view_likes_of_tweet(string s){
    ifstream f("likes_table.txt",ios::in);
    string id; string name; vector<string> v;
    while(f>>id>>name){
        if(id==s)
            v.push_back(name);
    }
    string result="";
    for(int i=0;i<v.size();i++){
        result+=v[i]+"|";
    }
    send(clientSocket,result.c_str(),strlen(result.c_str()),0);
}
void server :: retweet(string user_wants_to_retweet,string tweet_to_retweet_id){
    ifstream user("users_table.txt", ios :: in);
    if(!user){
        cout<<"File could not be opened\n";
        exit(1);
    }
    int user_id; char username[30]; char password[30];
    int counterU=0;
    while(user>>user_id>>username>>password){
        counterU++;
    }
    vector<vector<int> > fileVect6;
    vector<string> tweetsVect;
    vector<string> strID;
    for (int i = 0; i < 100; i++) {
        vector<int> v1;
        for (int j = 0; j < 2; j++)
            v1.push_back(0);
        fileVect6.push_back(v1);
    }
    ifstream vectFile6("tweets_table.txt", ios::in);
    if (!vectFile6) {
        cout << "File could not be opened\n";
        exit(1);
    }
    int id_1; int id_2; string re_id; string tweet; int i(0);
    while(vectFile6>>id_1>>id_2>>re_id){
        getline(vectFile6,tweet);
        fileVect6[i][0]=id_1;
        fileVect6[i][1]=id_2;
        strID.push_back(re_id);
        tweetsVect.push_back(tweet);
        i++;
    }
    vector<vector<string> > fileVect1;
    vector<int> idVect1;
    for (int i = 0; i < counterU; i++) {
        vector<string> v1;
        for (int j = 0; j < 2; j++)
            v1.push_back("0");
        fileVect1.push_back(v1);
    }
    ifstream vectFile1("users_table.txt", ios::in);
    if (!vectFile1) {
        cout << "File could not be opened\n";
        exit(1);
    }
    int ID1;char Uzzzi1[30];char UziPass1[30];int l(0);
    while (vectFile1 >> ID1 >> Uzzzi1 >> UziPass1) {
        string Uzzzziname;
        Uzzzziname = Uzzzi1;
        string UzzzziP;
        UzzzziP = UziPass1;
        idVect1.push_back(ID1);
        fileVect1[l][0] = Uzzzziname;
        fileVect1[l][1] = UzzzziP;
        l++;
    }
    
    int id1; int id2; int k(0); string idid1=""; string idid2="";
    while(k<tweet_to_retweet_id.length()){
        if(tweet_to_retweet_id[k]!='.'){
            idid1+=tweet_to_retweet_id[k];
        }
        if(tweet_to_retweet_id[k]=='.'){
            for(int j=k+1;j<tweet_to_retweet_id.length(); j++){
                idid2+=tweet_to_retweet_id[j];
            }
            break;
        }
        k++;
    }
    id1 = stoi(idid1); id2 = stoi(idid2);
    int vi(0); ///////strID,tweetsVect
    while(vi<fileVect6.size()){
        if(fileVect6[vi][0]==id1 && fileVect6[vi][1]==id2){
            string new_str_id=strID[vi];
            int id_part_1;
            string retweet=tweetsVect[vi];
            new_str_id +='.'+to_string(id1);
            for(int a=0;a<fileVect1.size();a++){
                if(fileVect1[a][0]==user_wants_to_retweet){
                    id_part_1=idVect1[a];
                }
            }
            int tweet_2ndpart_id=1;
            ifstream user_tweets("tweets_table.txt",ios::in);
            if(!user_tweets){
                cout<<"File could not be opened\n";
                exit(1);
            }
            int p1; int p2; string tweet; string Sid;
            while(user_tweets>>p1>>p2>>Sid){
                getline(user_tweets,tweet);
                if(p1==id_part_1)
                    tweet_2ndpart_id++;
            }
            ofstream in_user_Retweets("tweets_table.txt",ios::app);
            if(!in_user_Retweets){
                cout<<"File could not be opened\n";
                exit(1);
            }
            string nt=re(retweet);
            in_user_Retweets<<id_part_1<<' '<<tweet_2ndpart_id<<' '<<new_str_id<<' '<<nt<<endl;
        }
        vi++;
    }
}
string server :: re(string s){
    int cntr; string ns=""; string t;
    for(int i=s.size()-1;i>=0;i--){
        if(s[i]==' '){
            cntr=i;
            break;
        }
    }
    for(int j=0;j<=cntr;j++){
        ns+=s[j];
    }
    t = currentDateTime();
    ns+=t;
    return ns;
}
const string server :: currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}
void server :: delteAccount(string name){
    ifstream user("users_table.txt", ios :: in);
    if(!user){
        cout<<"File could not be opened\n";
        exit(1);
    }
    int user_id; char username[30]; char password[30];
    int counterU=0;
    while(user>>user_id>>username>>password){
        counterU++;
    }
    vector<vector<string> > fileVect1;
    vector<int> idVect1;
    for (int i = 0; i < counterU; i++) {
        vector<string> v1;
        for (int j = 0; j < 2; j++)
            v1.push_back("0");
        fileVect1.push_back(v1);
    }
    ifstream vectFile1("users_table.txt", ios::in);
    if (!vectFile1) {
        cout << "File could not be opened\n";
        exit(1);
    }
    int ID1; char Uzzzi1[30]; char UziPass1[30]; int i = 0;
    while (vectFile1 >> ID1 >> Uzzzi1 >> UziPass1) {
        string Uzzzziname;
        Uzzzziname = Uzzzi1;
        string UzzzziP;
        UzzzziP = UziPass1;
        idVect1.push_back(ID1);
        fileVect1[i][0] = Uzzzziname;
        fileVect1[i][1] = UzzzziP;
        i++;
    }
    vector<vector<int> > fileVect_delete_tweet;
    vector<string> tweetsVect;
    vector<string> strID;
    for (int i = 0; i < 100; i++) {
        vector<int> v1;
        for (int j = 0; j < 2; j++)
            v1.push_back(0);
        fileVect_delete_tweet.push_back(v1);
    }
    ifstream vectFile6("tweets_table.txt", ios::in);
    if (!vectFile6) {
        cout << "File could not be opened\n";
        exit(1);
    }
    int id_1; int id_2; string re_id; string tweet; int w(0);
    while(vectFile6>>id_1>>id_2>>re_id){
        getline(vectFile6,tweet);
        fileVect_delete_tweet[w][0]=id_1;
        fileVect_delete_tweet[w][1]=id_2;
        strID.push_back(re_id);
        tweetsVect.push_back(tweet);
        w++;
    }
    int tweetFirst_id;
    for (int j = 0; j < i; j++) {
        if (fileVect1[j][0] == name) {
            tweetFirst_id=idVect1[j];
            idVect1[j] = 0;
        }
    }/////////fileVect_delete_tweet,    strID
    for(int x=0;x<fileVect_delete_tweet.size();x++){/////////Deleting tweets;
        if(fileVect_delete_tweet[x][0]==tweetFirst_id){
            fileVect_delete_tweet[x][0]*=(-1);
        }
    }
    for(int y=0; y<strID.size(); y++){////////Deleting retweets;
        string strID_1=strID[y]; string ToosieSlide=""; vector<int> str_to_int_ID;
        for(int h=0; h<strID_1.length(); h++){
            if(strID_1[h]!='.'){
                ToosieSlide+=strID_1[h];
            }
            else if(strID_1[h]=='.'){
                str_to_int_ID.push_back(stoi(ToosieSlide));
                ToosieSlide="";
            }
        }
        str_to_int_ID.push_back(stoi(ToosieSlide));
        for(int q=0; q<str_to_int_ID.size(); q++){
            if(str_to_int_ID[q]==tweetFirst_id){
                strID[y]="00";
            }
        }
    }
    ofstream clear_tweets("tweets_table.txt", ios::out);
    clear_tweets.clear();
    ofstream write_tweet("tweets_table.txt",ios::out);
    for(int z=0; z<strID.size(); z++){
        if(fileVect_delete_tweet[z][0]>0 && strID[z]!="00"){
            write_tweet<<fileVect_delete_tweet[z][0]<<' '<<fileVect_delete_tweet[z][1]<<' '<<strID[z]<<' '<<tweetsVect[z]<<endl;
        }
    }
    ofstream cleanfile1("users_table.txt", ios::out);
    cleanfile1.clear();
    ofstream update_file1("users_table.txt", ios::out);
    int updatedID1;
    for (int k = 0; k < i; k++) {
        updatedID1 = idVect1[k];
        if (idVect1[k] > 0) {
            update_file1 << updatedID1 << ' ' << fileVect1[k][0] << ' ' << fileVect1[k][1] << endl;
        }
    }
    ifstream beshmar_like("likes_table.txt",ios::in);
    if(!beshmar_like){
        cout<<"File could not be opened.\n";
        exit(1);
    }
    int a; int b; int c; int likeCntr_total=0;
    while(beshmar_like>>a>>b>>c){likeCntr_total++;}
    vector<vector<int> > likeList;
    for (int i = 0; i < likeCntr_total; i++) {
        vector<int> v1;
        for (int j = 0; j < 3; j++)
            v1.push_back(0);
        likeList.push_back(v1);
    }
    ifstream likee("likes_table.txt",ios::in);
    if(!likee){
        cout<<"File could not be opened.\n";
        exit(1);
    }
    int like_id1; int like_id2; int like_id3; int li=0;
    while(likee>>like_id1>>like_id2>>like_id3){
        likeList[li][0]=like_id1;
        likeList[li][1]=like_id2;
        likeList[li][2]=like_id3;
        li++;
    }/////tweetFirst_id;
    for(int sp=0; sp<likeList.size();sp++){
        if(likeList[sp][2]==tweetFirst_id){
            likeList[sp][2]=0;
        }
    }
    ofstream clear_like("likes_table.txt",ios::out);
    if(!clear_like){
        cout<<"File could not be opened.\n";
        exit(1);
    }
    ofstream newLike("likes_table.txt",ios::out);
    if(!newLike){
        cout<<"File could not be opened.\n";
        exit(1);
    }
    for(int nl=0; nl<likeList.size(); nl++){
        if(likeList[nl][2]>0){
            newLike<<likeList[nl][0]<<' '<<likeList[nl][1]<<' '<<likeList[nl][2]<<endl;
        }
    }
}