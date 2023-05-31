#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <cmath>


/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T("Code::Blocks Template Windows App"),       /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           544,                 /* The programs width */
           375,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}

/*---------------------------------------------------------TASK J---------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------------------------------------------*/
/*
void Draw8Points(HDC hdc, int xc, int yc, int x, int y, COLORREF c)
{
    SetPixel(hdc, xc+x, yc+y,c);
    SetPixel(hdc, xc+x, yc-y,c);
    SetPixel(hdc, xc-x, yc+y,c);
    SetPixel(hdc, xc-x, yc-y,c);
    SetPixel(hdc, xc+y, yc+x,c);
    SetPixel(hdc, xc+y, yc-x,c);
    SetPixel(hdc, xc-y, yc+x,c);
    SetPixel(hdc, xc-y, yc-x,c);
}

void DirectCircle(HDC hdc, int xc, int yc, int r, COLORREF c)
{
    int x=0;
    double y=r;
    int r2=r*r;
    Draw8Points(hdc, xc, yc, 0, r, c);
    while (x<y)
    {
        x++;
        y=(double)sqrt(r2-(x*x));
        Draw8Points(hdc, xc, yc, x, round(y), c);
    }
}

void PolarCircle(HDC hdc, int xc, int yc, int R, COLORREF c)
{
    double d_theta=1.0/R;
    for (double theta=0; theta<6.28; theta+=d_theta)
    {
        double x=xc+R*cos(theta);
        double y=yc+R*sin(theta);
        SetPixel(hdc, x, y, c);
    }
}

void ModifiedPolar(HDC hdc, int xc, int yc, int R, COLORREF c)
{
    double d_theta=1.0/R;
    double x=R, y=0.0, theta=0.0;
    Draw8Points(hdc, xc, yc, R, 0, c);
    while (x>y)
    {
        theta+=d_theta;
        x=xc+R*cos(theta);
        y=yc+R*sin(theta);
        Draw8Points(hdc, xc, yc, round(x), round(y), c);
    }
}

void IterativePolar(HDC hdc, int xc, int yc, int R, COLORREF c)
{
    double d_theta = 1.0/R;
    double ct=cos(d_theta), st=sin(d_theta);
    double x=R, y=0;
    Draw8Points(hdc, xc, yc, R, 0, c);
    while (x>y)
    {
        double x1= (x*ct)-(y*st);
        y=(x*st)+(y*ct);
        x=x1;
        Draw8Points(hdc, xc, yc, round(x), round(y), c);
    }
}

void MidPoint(HDC hdc,int xc,int yc, int R,COLORREF c)
{
    int x=0,y=R;
    int d=1-R;
    Draw8Points(hdc,xc,yc,x,y,c);
    while(x<y)
    {
        if(d<0)
            d+=2*x+2;
        else
        {
            d+=2*(x-y)+5;
            y--;
        }
        x++;
        Draw8Points(hdc,xc,yc,x,y,c);
    }
}

void ModifiedMidPoint(HDC hdc,int xc,int yc, int R,COLORREF color)
{
    int x=0,y=R;
    int d=1-R;
    int c1=3, c2=5-2*R;
    Draw8Points(hdc,xc,yc,x,y,color);
    while(x<y)
    {
        if(d<0)
        {
            d+=c1;
            c2+=2;
        }
        else
        {
            d+=c2;
            c2+=4;
            y--;
        }
        c1+=2;
        x++;
        Draw8Points(hdc,xc,yc,x,y,color);
    }
}

/*---------------------------------------------------------TASK L---------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------------------------------------------*/
/*
void FillCircle(HDC hdc, int xc, int yc, int R, int quarter, COLORREF c)
{
    int x=0,y=R;
    int d=1-R;
    int c1=3, c2=5-2*R;
    while(x<y)
    {
        if(d<0)
        {
            d+=c1;
            c2+=2;
        }
        else
        {
            d+=c2;
            c2+=4;
            y--;
        }
        c1+=2;
        switch (quarter)
        {
            case 1:
                SetPixel(hdc, xc + x, yc - y, c);
                SetPixel(hdc, xc + y, yc - x, c);
                break;
            case 2:
                SetPixel(hdc, xc - x, yc - y, c);
                SetPixel(hdc, xc - y, yc - x, c);
                break;
            case 3:
                SetPixel(hdc, xc - x, yc + y, c);
                SetPixel(hdc, xc - y, yc + x, c);
                break;
            case 4:
                SetPixel(hdc, xc + x, yc + y, c);
                SetPixel(hdc, xc + y, yc + x, c);
                break;
            default:
                cout<<"....Wrong Input..../n";
        }
        x++;
    }
}

/*---------------------------------------------------------TASK P---------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------------------------------------------*/
/*
void recursionFloodFill(HDC hdc, int x, int y, COLORREF bc, COLORREF fc)
{
    COLORREF c=GetPixel(hdc, x, y);
    if (c==bc || c==fc) return;
    SetPixel(hdc, x, y, fc);
    recursionFloodFill(hdc, x+1, y, bc, fc);
    recursionFloodFill(hdc, x-1, y, bc, fc);
    recursionFloodFill(hdc, x, y-1, bc, fc);
    recursionFloodFill(hdc, x, y+1, bc, fc);
}

class Point{
    public:
        int x , y ;

    Point(int x = 0 , int y = 0 )
    {
        this->x = x;
        this-> y = y;
    }
};

void non_recFloodFill(HDC hdc, int x, int y, COLORREF bc, COLORREF fc)
{
    stack<Point> s;
    s.push(Point(x,y));
    while(!s.empty())
    {
        Point p=s.top();
        s.pop();
        COLORREF c=GetPixel(hdc, p.x, p.y);
        if(c==bc || c==fc) continue;
        SetPixel(hdc, p.x, p.y, fc);
        s.push(Point(p.x+1,p.y));
        s.push(Point(p.x-1,p.y));
        s.push(Point(p.x,p.y+1));
        s.push(Point(p.x,p.y-1));
    }
}

/*  This function is called by the Windows function DispatchMessage()  */
void Draw8Points(HDC hdc, int xc, int yc, int x, int y, COLORREF c)
{
    SetPixel(hdc, xc+x, yc+y,c);
    SetPixel(hdc, xc+x, yc-y,c);
    SetPixel(hdc, xc-x, yc+y,c);
    SetPixel(hdc, xc-x, yc-y,c);
    SetPixel(hdc, xc+y, yc+x,c);
    SetPixel(hdc, xc+y, yc-x,c);
    SetPixel(hdc, xc-y, yc+x,c);
    SetPixel(hdc, xc-y, yc-x,c);
}

void DirectCircle(HDC hdc, int xc, int yc, int r, COLORREF c)
{
    int x=0;
    double y=r;
    int r2=r*r;
    Draw8Points(hdc, xc, yc, 0, r, c);
    while (x<y)
    {
        x++;
        y=(double)sqrt(r2-(x*x));
        Draw8Points(hdc, xc, yc, x, round(y), c);
    }
}
LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    DirectCircle(GetDC(hwnd),100,100,50,RGB(255,255,255));
    switch (message)                  /* handle the messages */
    {
        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
