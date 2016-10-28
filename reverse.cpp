//  reverse.org    1993 jan 13    last modified 2014 feb 06
//  Modified from reverse.cpp.
//  shows "organization" of instructor's reverse.cpp.
//
//  main.cpp
//
//  CS 3240 - Assignment 1
//
//  Created by Jackson Wise on 9/24/16.
//

#include <iostream>
//#include <new.h>                          // Perhaps used with testing?
#include <stdlib.h>

using namespace std;

struct node{
    char atom;                              // 0 or 1
    char data;                              // if atom: actual data
    node *link;                             // ptr to list
    node *next;                             // ptr to next node
};

node * const nill=(node *)0;
int const maxs=80;                          // max string length
char const lefp='(', newl='\n', ritp=')';
node *stack[maxs >> 1], **top=stack-1;      // max stack size <= maxs/2 int



int main(int argc, const char * argv[]) {
    
    node *linklist(const char * );
    int getstring( char * ), newerr( size_t ), ok( const char * );
    void deleteblanks( char * ), drawline( void ), echoprint( const char * ),
    eraselist( node * ), revlist( const node * ),
    revstring( const char * ), scanlist( const node * );
    
    node *head;                     // ptr to list structure
    char s[maxs+1];                 // data string; length <= maxs

//    _set_new_handler( newerr );     // defined in new.h
    while( getstring ( s ) )
    {
        echoprint( s );
        deleteblanks( s );
        if ( !ok( s ) ) {
            cout << "** illegal list format **\n";
        }
        else {
            revstring( s );
            head = linklist( s );
            scanlist( head );
            revlist( head );
            eraselist( head );
        }
    }

    drawline();
    return 0;
}


void
deleteblanks( char *s )
{
    char *p, *q;
    
    cout << "Deblanked string:\n";
    
    for( p = q = s; *q ; q++){
        
        if((*q != ' ') && (*q != '\t')){
            *p++ = *q;
        }
        
    }
    
    *p = '\0';
    cout << s << newl;
}

void
drawline()
{
    int i;
    
    for( i = 75; i > 0; i--){
        
        cout << '-';
    }
    
    cout << newl;
}

void
echoprint( const char *s )
{
    cout << "Echo of data string:\n" << s << newl;
}

void
eraselist( node *p )
{
    if( p != nill ){
        eraselist( p->next );
        
        if( ! p ->atom ){
            eraselist( p ->link);
        }
        
        delete p;
    }
}

int
getstring( char *s )
{
    drawline();
    
    cout << "Type a string representing a generalized list, please:\n";
    
    cin.getline( s, maxs+1 );
    
    return ( (int)*s );
}

node *
linklist( const char *s )
{
    node *newnode( void );
    void pop( node *& ), push( node * );
    
    node *p=nill, *q;
    int lp;
    char ch;
    
    do{
        ch = *s++;
        
        if ( ch == ritp )
        {
            lp = 0;
            pop(p);
        }
        else{
            q = newnode();
            
            if ( p )
            {
                if ( lp ){
                    p->link = q;
                }
                else{
                    p->next = q;
                }
            }
            
            p = q;
            lp = (ch == lefp);
            q -> atom = (char)!lp;
            
            if( q -> atom ){
                q->data = ch;
            }
            else{
                push( q );
            }
        }
        
        
    }
    while( *s );
    
    return( p );
}

node *
newnode()
{
    node *q;
    
    q = new node;
    q->link = q->next = nill;
    return( q );
}

int
ok( const char *s )         // Assumes non-empty
{
    int n=0;
    
    if( *s != lefp) {
        return(0);
    }
    
    do{
        switch( *s ){
    
        case lefp:
            n++;
            break;
        case ritp:
            --n;
            break;
        default: ;}
    }while( *++s && (0 < n) );
        
    return( ( *s == '\0') && (n == 0) );
        
}


void
pop( node *& p )
{
    p = *top--;
}


void
push( node *p )
{
    *++top = p;
}

void
rev( const node *p )
{
    if( p != nill ){
        rev(p->next);
        
        if(p->atom){
            cout << p->data;
        }
        else{
            cout << lefp;
            rev( p->link );
            cout << ritp;
        }
    }
}

void
revlist( const node *p )
{
    cout << "Reversed linked list:\n";
    rev( p );
    cout << newl;
}

void
revstring( const char *s )
{
    const char *p;
    char ch;
    
    cout << "Reversed string:\n";
    p = s;
    
    while ( *p ){
        p++;
    }
    do{
        switch( ch = *--p ){
                
            case lefp:
                ch = ritp;
                break;
            case ritp:
                ch = lefp;
                break;
            default: ;}
        
        cout << ch;
        
    }
    while ( s < p );
    
    cout << newl;
    
}

void
scan( const node *p )
{
    if( p != nill)
    {
        if( p -> atom){
            cout << p->data;
        }
        else{
            cout << lefp;
            scan( p ->link );
            cout << ritp;
        }
        
        scan( p->next);
    }
}

void
scanlist( const node *p )
{
    cout << "Scan of linked list:\n";
    scan( p );
    cout << newl;
}