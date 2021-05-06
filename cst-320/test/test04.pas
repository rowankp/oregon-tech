// testing writing variables assigned to variables

PROGRAM test4;
VAR
    a : integer;
    b : integer;
    c, d : integer;
BEGIN
    a := 1;
    b := 2;

    WRITE(a);
    WRITE(b);
    
    c := a;
    d := b;

    WRITE(c);
    WRITE(d);   
END.
