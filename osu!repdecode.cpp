#include<cstdio>
#include<cstring>
#include<Windows.h>
#include<winuser.h>
#include<TlHelp32.h>
#include<vector>
#include<algorithm>
#include"lzmadec.c"
int lzmadec(char *input, char *output);
#define ABS(x)((x)<0?-(x):(x))
#define ll long long
using namespace std;
unsigned int DecodeULEB128(unsigned char *buffer) {
	unsigned int value=0;
	int pos=0;
	int offset=0;
	while(buffer[pos]!=0) {
		value|=((buffer[pos]&0x7F)<<offset);
		offset+=7;
		if((buffer[pos++]&0x80)==0)break;
	}
	return value;
}
unsigned ll getll(FILE *fp) {
	unsigned char data[8];
	for(int i=0; i<8; i++)data[i]=fgetc(fp);
	return *(unsigned ll*)data;
}
unsigned int getInt(FILE *fp) {
	unsigned char data[4];
	for(int i=0; i<4; i++)data[i]=fgetc(fp);
	return *(unsigned int*)data;
}
unsigned short getShort(FILE *fp) {
	unsigned char data[2];
	for(int i=0; i<2; i++)data[i]=fgetc(fp);
	return *(unsigned int*)data;
}
unsigned int getULEB128(FILE *fp) {
	unsigned char data[6]= {0,0,0,0,0,0},ch,pp=0;
	do {
		ch=fgetc(fp);
		data[pp++]=ch;
	} while((ch&0x80)&&(pp<5));
	return DecodeULEB128(data);
}
void passUtf8(FILE *fp) {
	unsigned char ch=fgetc(fp);
	if((ch&0xE0)==0xC0) {
		fgetc(fp);
		return;
	}
	if((ch&0xF0)==0xE0) {
		fgetc(fp);
		fgetc(fp);
		return;
	}
	if((ch&0xF8)==0xF0) {
		fgetc(fp);
		fgetc(fp);
		fgetc(fp);
		return;
	}
}
unsigned int getStringSize(FILE *fp) {
	unsigned char ch=fgetc(fp);
	if(ch==0x00) {
		return 0;
	}
	unsigned int size=getULEB128(fp);
	for(unsigned int i=0; i<size; i++)passUtf8(fp);
	return size;
}
struct info{
	ll w;
	float x,y;
	int z;
}tmplist;
vector<info> list;
int ticks=0;
bool cmp(info &a,info &b){
	return a.w<b.w;
}
bool initREP(char *Filename) {
	FILE *fp,*fp2;
	if(!(fp=fopen(Filename,"rb")))return 1;
	else {
		unsigned int packsize=0;
		printf("Mode=%u\n",fgetc(fp));
		printf("Ver=%u\n",getInt(fp));
		printf("Map MD5 hash Size=%u\n",getStringSize(fp));
		printf("Player Name Size=%u\n",getStringSize(fp));
		printf("Rep MD5 hash Size=%u\n",getStringSize(fp));
		printf("300=%u\n",getShort(fp));
		printf("100=%u\n",getShort(fp));
		printf("50=%u\n",getShort(fp));
		printf("Gekis=%u\n",getShort(fp));
		printf("Katus=%u\n",getShort(fp));
		printf("Miss=%u\n",getShort(fp));
		printf("Score=%u\n",getInt(fp));
		printf("Combo=%u\n",getShort(fp));
		printf("FC=%u\n",fgetc(fp));
		printf("Mods=%u\n",getInt(fp));
		printf("Life bar graph Size=%u\n",getStringSize(fp));
		printf("Time stamp=%llu\n",getll(fp));
		printf("Length in bytes of compressed replay data=%u\n",packsize=getInt(fp));
		if(!(fp2=fopen("LZMA~tmp1","wb"))) {
			fclose(fp);
			return 1;
		} else {
			for(unsigned int i=0; i<packsize; i++)fputc(fgetc(fp),fp2);
			fclose(fp);
			fclose(fp2);
			int ret=lzmadec((char*)"LZMA~tmp1",(char*)"LZMA~tmp2");
			remove("LZMA~tmp1");
			if(ret!=0){
				remove("LZMA~tmp2");
				return ret;
			}
			if(!(fp=fopen("LZMA~tmp2","rb"))){
				remove("LZMA~tmp2");
				return 1;
			} else {
				while(!feof(fp)){
					fscanf(fp,"%lld|%f|%f|%d,",&tmplist.w,&tmplist.x,&tmplist.y,&tmplist.z);
					if(ticks>0)tmplist.w+=list[ticks-1].w;
					list.push_back(tmplist);ticks++;
				}
			}
			fclose(fp);
			remove("LZMA~tmp2");
			list.pop_back();ticks--;
			list.erase(list.begin());ticks--;
			list.erase(list.begin());ticks--;
			sort(list.begin(),list.end(),cmp);
		}
	}
	return 0;
}
int main(int argc,char *argv[]) {
	if(initREP(argv[1])) {
		printf("Openning Replay Failed\n");
		printf("Drag .rep on osu!repdecode.exe\n");
		system("pause");
	}
	FILE *fp;
	char szFilePath[MAX_PATH+1]={0};
	GetModuleFileName(NULL,szFilePath,MAX_PATH);
	(strrchr(szFilePath,'\\'))[1]=0;
	char* pss=strrchr(argv[1],'\\');
	if(pss==NULL)strcat(szFilePath,argv[1]);else
	strcat(szFilePath,(strrchr(argv[1],'\\')+2));
	(strrchr(szFilePath,'.'))[1]=0;
	strcat(szFilePath,"txt");
	if(!(fp=fopen(szFilePath,"w"))){
		printf("Openning output.txt Failed\n");
		return 0;
	}
	fprintf(fp,"         w          x          y          z\n");
	for(int i=0;i<ticks;i++)fprintf(fp,"%10lld %10.4f %10.4f %10d\n",list[i].w,list[i].x,list[i].y,list[i].z);
	system("pause");
	return 0;
}
