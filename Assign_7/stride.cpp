#include <stdlib.h>
#include<bits/stdc++.h>
#define rel 50
#define ll long long int
using namespace std;

struct process{
	float percentage_share;
	float current_share;
	ll tickets;
	vector<pair<ll,int>>cpu;
	vector<ll>ip;
	vector<ll>op;
	int cpu_i;
	int ip_i;
	int op_i;
	ll tim_cpu;
	ll tim_ip;
	ll tim_op;
	ll stride;
	int turnaround;
	int response;
	int waiting;
	int burst;
};

void split(char a[],char delimeter,int *n,char result[][rel]){
	int i,j,p=0,new_s=1;
	for(i=0;i<strlen(a);i++){
		if(a[i]==delimeter){
			if(new_s==1){
				result[*n][p]='\0';
				p=0;
				*n=*n+1;
				new_s=0;
			}
		}
		else{
			result[*n][p]=a[i];
			p++;
			new_s=1;
		}
	}
	if(a[strlen(a)-1]!=delimeter){
		result[*n][p]='\0';
		*n=*n+1;
	}
}

void distribute_tickets(struct process pdes[],int np,ll nt,int available[],int asize){
	ll sum=0,last=-1;
	int c=0;
	for(int i=1;i<=np;i++){
		if(available[i]==1){
			c++;
			if(asize==c){
				pdes[i].tickets=nt-sum;
			}
			else{
				pdes[i].tickets=(ll)((pdes[i].current_share*nt)/100);
				sum=pdes[i].tickets+sum;

			}
		}
		else{
			pdes[i].tickets=-1;
		}
	}
	cout << "tic dis"<<endl;
	for(int i=1;i<=np;i++){
		cout << pdes[i].tickets<<' '<<available[i]<< " ";
	}
	cout << endl;
}


void distribute_share(struct process pdes[],int np,int currp,int signal_process_end,int available[],int asize){
	int i,c=0,sum=0;
	int tmp=pdes[currp].current_share;
	pdes[currp].current_share=0;
	if(signal_process_end==1){
		pdes[currp].percentage_share=0;
	}
	available[currp]=0;
	if(asize==0){
		return ;
	}
	for(i=1;i<=np;i++){
		if(available[i]==1){
			c++;
			if(c==asize){
				pdes[i].current_share=100-sum;
			}
			else{
				pdes[i].current_share=pdes[i].current_share+(tmp/asize);
				sum=sum+pdes[i].current_share;
			}

		}
	}
	if(signal_process_end==1){
		for(i=1;i<=np;i++){
			if(available[i]==1){
				pdes[i].percentage_share=pdes[i].current_share;
			}
		}
	}
	cout << "cpu dis"<<endl;
	for(int i=1;i<=np;i++){
		cout << pdes[i].current_share<<' '<<available[i]<< " ";
	}
	cout << endl;

}

void gain_cpu_share(struct process pdes[],int np,int currp,int available[],int asize){
	int i,c=0,tmp;
	available[currp]=1;
	for(i=1;i<=np;i++){
		if(available[i]==1){
			pdes[i].current_share=pdes[i].percentage_share;
		}
	}
}

int find_min_stride(struct process pdes[],int np,int available[]){
	ll minv=1000000000000000,mini=-1;
	for(int i=1;i<=np;i++){
		if(available[i]==1 && pdes[i].stride<minv){
			mini=i;
			minv=pdes[i].stride;
		}
	}
	return mini;
}

int main(){
	FILE *fp=fopen("lottery.dat","r");
	if(fp==NULL){
		cout << "file not found";
	}
	else{
		int i,j,np,n=0,pid=0,tmpint;
		ll nt,stride_div,tmpll;

		pair<ll,int>tmp_pair;


		char buffer[1000];
		char result[1000][rel];

		fgets(buffer,1000,fp);
		sscanf(buffer,"%lld",&nt);

		fgets(buffer,1000,fp);
		sscanf(buffer,"%d",&np);

		fgets(buffer,1000,fp);
		sscanf(buffer,"%lld",&stride_div);


		struct process pdes[np+1];
		int available[np+1]={0},asize=0;

		queue<int>ipq,opq;

		for(i=1;i<=np;i++){

			available[i]=1;
			asize++;

			n=0;
			fgets(buffer,1000,fp);
			split(buffer,' ',&n,result);

			sscanf(result[0],"%d",&pid);


			sscanf(result[1],"%f",&pdes[pid].percentage_share);
			pdes[pid].current_share=pdes[pid].percentage_share;

			pdes[i].ip_i=pdes[i].cpu_i=pdes[i].op_i=pdes[i].tim_cpu=pdes[i].tim_ip=pdes[i].tim_op=pdes[i].burst=pdes[i].tickets=pdes[i].stride=0;

			for(j=2;j<n;j++){
				if(strcmp("P",result[j])==0){
					sscanf(result[j+1],"%lld",&tmpll);

					if(strcmp("I",result[j+2])==0){
						tmp_pair.first=tmpll;
						tmp_pair.second=1;
					}
					else if(strcmp("O",result[j+2])==0){
						tmp_pair.first=tmpll;
						tmp_pair.second=2;
					}
					else{
						tmp_pair.first=tmpll;
						tmp_pair.second=0;
					}
					pdes[pid].cpu.push_back(tmp_pair);

				}
				else if(strcmp("I",result[j])==0){
					sscanf(result[j+1],"%lld",&tmpll);
					pdes[pid].ip.push_back(tmpll);
				}
				else if(strcmp("O",result[j])==0){
					//cout <<"debug "<< pid << " "<<j<<endl;
					sscanf(result[j+1],"%lld",&tmpll);
					pdes[pid].op.push_back(tmpll);
				}

			}

		}

//		for(i=1;i<=np;i++){
//			cout << pdes[i].percentage_share<<endl;
//			for(j=0;j<pdes[i].cpu.size();j++){
//				cout << pdes[i].cpu[j].first<<' '<<pdes[i].cpu[j].second<<endl;
//			}
//			for(j=0;j<pdes[i].ip.size();j++){
//				cout << pdes[i].ip[j]<<' ';
//			}
//			cout << endl;
//			for(j=0;j<pdes[i].op.size();j++){
//				cout << pdes[i].op[j]<<' ';
//			}
//			cout << endl;
//
//		}

		int currp;
		int ti=0;

		while(1){

			if(ti>1000000 || (asize<=0 && ipq.size()==0 && opq.size()==0)){
				break;
			}

			distribute_tickets(pdes,np,nt,available,asize);

			currp=find_min_stride(pdes,np,available);

			if(currp>0){
				pdes[currp].tim_cpu++;
				if(pdes[currp].cpu_i==0 && pdes[currp].tim_cpu==1){
						pdes[currp].response=ti;
				}

				if(pdes[currp].tim_cpu==pdes[currp].cpu[pdes[currp].cpu_i].first){
					int signal_process_end=0;

					if(pdes[currp].cpu[pdes[currp].cpu_i].second==1){
						ipq.push(currp);
					}
					else if(pdes[currp].cpu[pdes[currp].cpu_i].second==2){
						opq.push(currp);
					}
					pdes[currp].cpu_i=pdes[currp].cpu_i+1;
					pdes[currp].tim_cpu=0;
					if(pdes[currp].cpu_i==pdes[currp].cpu.size()){
						pdes[currp].turnaround=ti+1;
						signal_process_end=1;
						//cout << "process "<<currp <<" completed"<<endl;
					}
					asize--;
					distribute_share(pdes,np,currp,signal_process_end,available,asize);
					//
					//cout << "process "<<currp <<" finished cpuburst at "<<ti<<endl;
				}
				pdes[currp].stride=pdes[currp].stride+(stride_div/pdes[i].tickets);
			}

			if(!ipq.empty()){
			currp=ipq.front();
			//if(cpucurr!=currp){
			pdes[currp].tim_ip++;
			//pdes[currp].burst=pdes[currp].burst+pdes[currp].ip[pdes[currp].ip_i];
			if(pdes[currp].tim_ip==pdes[currp].ip[pdes[currp].ip_i]){
				ipq.pop();
				pdes[currp].ip_i=pdes[currp].ip_i+1;
				pdes[currp].tim_ip=0;
				//
				//cout << "process "<<currp <<" finished ipburst at "<<ti<<endl;
				asize++;
				gain_cpu_share(pdes,np,currp,available,asize);

			}//}
			}

			//op started
			if(!opq.empty()){
			currp=opq.front();
			//if(cpucurr!=currp){
			pdes[currp].tim_op++;
			//pdes[currp].burst=pdes[currp].burst+pdes[currp].ip[pdes[currp].ip_i];
			if(pdes[currp].tim_op==pdes[currp].op[pdes[currp].op_i]){
				opq.pop();
				pdes[currp].op_i=pdes[currp].op_i+1;
				pdes[currp].tim_op=0;
				//
				//cout << "process "<<currp <<" finished opburst at "<<ti<<endl;
				asize++;
				gain_cpu_share(pdes,np,currp,available,asize);

			}//}
			}

			ti++;


		}


		for(i=1;i<=np;i++){
			for(j=0;j<pdes[i].cpu.size();j++){
				pdes[i].burst=pdes[i].burst+pdes[i].cpu[j].first;
			}
			//cout << pdes[i].turnaround<<' '<<pdes[i].response<<" "<<pdes[i].turnaround-pdes[i].burst<<endl;
			pdes[i].waiting=pdes[i].turnaround-pdes[i].burst;
			//cout << pdes[i].waiting<<endl;
		}
		int sum=0;
		for(i=1;i<=np;i++){
			cout << pdes[i].turnaround<<" ";
			sum=sum+pdes[i].turnaround;
		}
		cout <<sum/np<<endl;

		sum=0;
		for(i=1;i<=np;i++){
			cout << pdes[i].response<<" ";
			sum=sum+pdes[i].response;
		}
		cout <<sum/np<<endl;

		sum=0;
		for(i=1;i<=np;i++){
			cout << pdes[i].waiting<<" ";
			sum=sum+pdes[i].waiting;
		}
		cout <<sum/np<<endl;


	}
}
