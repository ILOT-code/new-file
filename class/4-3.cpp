#include <iostream>
using namespace std;
class Matrix{
    private:
    int row,col;
    bool flag=1;
    double** data;
    public:
    Matrix(int a,int b){
        row=a;col=b;
        data=new double*[row];
        for(int i=0;i<row;++i) data[i]=new double[col];
    }
    ~Matrix(){
        for(int i=0;i<row;++i) delete []data[i];
        delete []data;
    }
    void Matrix_ass(){
        for(int i=0;i<row;++i)
        for(int j=0;j<col;++j)
        cin>>data[i][j];
    }
    double table(int i,int j) { return data[i][j];}
    Matrix& operator+=(const Matrix& p){
        if(row!=p.row||col!=p.col){ flag=0; return *this; }
        for(int i=0;i<row;++i)
        for(int j=0;j<col;++j)
        data[i][j]+=p.data[i][j];
        return *this;
    }
    Matrix& operator*=(const Matrix& p){
        if(col!=p.row) { flag=0; return *this; }
        Matrix pp(row,p.col);
        for(int i=0;i<row;++i)
        for(int j=0;j<p.col;++j)
        for(int k=0;k<p.row;++k)
            pp.data[i][j]+=data[i][k]*p.data[k][j];
        *this=pp;
        return *this;
    }
    Matrix& operator=(const Matrix&p){
        row=p.row;
        col=p.col;
        data=new double*[row];
        for(int i=0;i<row;++i) data[i]=new double[col];
        for(int i=0;i<row;++i)
        for(int j=0;j<col;++j)
        data[i][j]=p.data[i][j];
        return *this;
    }
    friend ostream& operator<<(ostream& output,Matrix &p){
        if(p.flag){
            for(int i=0;i<p.row;++i){
            for(int j=0;j<p.col;++j)
            output<<p.data[i][j]<<' ';
            output<<endl;
        }}
        else {p.flag=1;output<<"ERROR!"<<endl;}
        return output;
    }
};
int main(){
    int row1,col1,row2,col2;
    cin>>row1>>col1;Matrix a(row1,col1); a.Matrix_ass();
    cin>>row2>>col2;Matrix b(row2,col2); b.Matrix_ass();
    cout<<a.table(row1/2,col1/2)<<endl;
    cout<<(a*=b);
    cout<<(a+=b);
    cout<<(a=b);
    return 0;
}