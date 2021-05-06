// testing function without parameters
PROGRAM test15;
VAR
    a, b : integer;

FUNCTION func1 : integer;
    VAR
        c : integer;
    BEGIN
        c := 1;
        func1 := c;
    END;
BEGIN
    a := 2;
    b := func1;
    WRITE(a ,b);
END.
