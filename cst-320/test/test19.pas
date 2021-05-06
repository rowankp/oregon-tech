// testing procedures and functions together
PROGRAM test19;
VAR
    c : integer;
FUNCTION func1( a : integer);
    VAR
        z : integer;
    BEGIN
        z := a * 5;
        WRITE(a);
        WRITE(z);
        func1 := z;
    END;
PROCEDURE proc1( b : integer);
    BEGIN
        WRITE(b);
    END;
BEGIN
    c := func1(5);
    proc1(c);
END.
