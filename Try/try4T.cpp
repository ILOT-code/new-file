class Point{
    private:
    double x,y;
    public:
    Point(double x=0,double y=0):x(x),y(y){};
    double getx(){
        return x;
    }
    double gety(){
        return y;
    }
};
class Line:public Point{
    private:
    class Point a,b;
    public:
    Line(Point p1,Point p2){
        a=p1;
        b=p2;
    }
}
class Polyline:public Line{
    private:
    class Line l1,l2;
    public:
    Polyline(Line l,Line ll){
        l1=l;
        l2=ll;
    }
}
class triangle:public Line{
    privata:
    class Line a,b,c;
    public:
    triangle(Line a1,Line b1,Line c1){
        a=a1;
        b=b1;
        c=c1;
    }
}
class rectangle:public Point{
    private:
    class Point a,b,c,d;
    public:
    rectangle(Point a1,Point b1,Point c1,Point d1){
        a=a1;
        b=b1;
        c=c1;
        d=d1;
    }
};
class polygon:public Point{
    private:
    int n;
    vector<Point> points;
    private:
    polygon(int i):n(i){};
    void get_polygon(){
        for(int i=0;i<n;++i){
            double x,y;
            cin>>x>>y;
            points.push_back(Point(x,y));
        }
    }
};
