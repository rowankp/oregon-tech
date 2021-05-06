// testing function with parameters
PROGRAM test16;
VAR
    a, b : integer;
FUNCTION func (VAR c : integer ) : integer;
    BEGIN
        WRITE(c);
        func := c * 2;
    END;
BEGIN
    a := 1;
    b := func(a);
    WRITE(b);
END.
