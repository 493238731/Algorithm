//1） l[x], r[x], u[x], d[x],分别表示该节点的左右上下结点，构成一个双向十字链表。
//2） c[x] 记录该节点所在的列结点，因为我们在一开始留了一行存总的头指针和各列的头指针。head定义为0指向总的头指针。
//3） row[x] 还有时候需要row[x]]记录该节点所在矩阵中的行数;有时候根据需要要开个行指针头数组。
//4） s[x]记录每列列链表中结点的个数。
//5） o[x]记录搜索结果。
const int MAX=INT_MAX;
int s[MAx],l[MAX],r[MAX],u[MAX],d[MAX],c[MAX],row[MAX],o[MAX];
int head=0,cnt=0;
bool mat[MAX][MAX];
void DLX_makegraph(){
	//将输入条件转化为01矩阵
}


//将n行m列01矩阵转化为十字链表，cnt表示节点个数 
void DLX_initial(){
	int rowh;
	int memset(s,0,sizeof(s));
	for(itn i=head;i<=m;++i){
		r[i]=(i+1)%(m+1);
		l[i]=(m+1+r-1)%(m+1);
		u[i]=d[i]=i;
	}
	cnt=m+1;
	for(int i=1;i<=n;++i){
		rowh=-1;
		for(int j=1;j<=m;++j){
			if(mat[i][j]){
				s[j]++;
				u[cnt]=u[j],	d[u[j]=cnt;  //u[j] and cnt link
				d[cnt]=j,	u[j]=cnt;		// j and cnt link
				row[cnt]=i;
				c[cnt]=j;
				if(rowh==-1){
					l[cnt]=r[cnt]=i;
					rowh=cnt;
				}else{
					l[cnt]=l[rowh],		r[l[rowh]]=cnt;
					r[cnt]=rowh,		l[rowh]=cnt;
				}
				cnt++;
			}
		}
	}
}

//remove column c and all row i that A[i][c] == 1	
void DLX_remove(const int& cur){
	l[r[cur]]=l[cur];
	r[l[cur]]=r[cur];//remove column c;
	for(int i=d[cur];i!=cur;i=d[i]){
		//remove i that A[i][c] == 1
		for(int j=r[i];j!=i;j=r[j]){
			u[d[j]]=u[j];
			d[i[j]]=d[j];
			--s[c[j]];//decrease the count of column C[j];
		}
	}
}

//resume 

void DLX_resume(const int& cur){
	for(int i=u[cur];i!=cur;i=u[i]){
		for(int j=l[i];j!=i;j=l[j]){
			++s[c[j]];
			u[d[j]]=j;
			d[u[j]]=j;
		}
	}
	l[r[cur]]=r[l[cur]]=cur;
}

//version 1 for one valid solution
// main function call dfs(0);
bool DLX_dfs1(const int& k){
	if(r[head]==head){
		//input result o[0..k];
		return true;
	}
	int ms=INT_MAX,cur=0;
	for(int t=r[head];t!=head;t=r[t]){ //select the columne c which has the fewest number of elemnet
		if(s[t]<ms)		ms=s[t],cur=t;
	}
	DLX_remove(cur);
	for(int i=d[cur];i!=cur;i=d[i]){
		o[k]=row[i];//record the answer
		for(int j=r[i];j!=i;j=r[i]){
			DLX_remove(c[j]);
		}
		if(DLX_dfs1(k+1))	return true;
		for(int j=l[i];j!=i;j=l[j]){
			DLX_resume(c[j])
		}
	}
	DLX_resume(cur);
	return false;
}

//version 2 for optimal  input the min number of row 
// main function call dfs(0)
void DLX_dfs2(const int& k){
	if(r[head]==head){
		if(k<num)	num=k;
		//input result int o[0..k];
		return;
	}
	if(k>=num)	return;
	int ms=INT_MAX,cur=0;
	for(int t=r[head];t!=head;t=r[t]){ //select the columne c which has the fewest number of elemnet
		if(s[t]<ms)		ms=s[t],cur=t;
	}
	DLX_remove(cur);
	for(int i=d[cur];i!=cur;i=d[i]){
		o[k]=row[i];//record the answer
		for(int j=r[i];j!=i;j=r[i]){
			DLX_remove(c[j]);
		}
		DLX_dfs2(k+1);
		for(int j=l[i];j!=i;j=l[j]){
			DLX_resume(c[j])
		}
	}
	DLX_resume(cur);
	return;
}
