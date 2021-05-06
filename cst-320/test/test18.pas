// testing procedures with parameters
PROGRAM test18;
VAR
    a, b : integer;
PROCEDURE procl(VAR a : integer; b : integer;);
    BEGIN
        WRITE(a, b);
    END;
BEGIN
    a := 1;
    b := 2;

    procl(a,b);
END.
