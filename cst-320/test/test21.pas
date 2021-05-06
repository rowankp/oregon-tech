// testing proc and loop
PROGRAM test21;
VAR
    a : integer;
    b : integer;
PROCEDURE proc1 (a : integer; b : integer)
    BEGIN
        WRITE(a);
        WRITE(b);
    END;
BEGIN
    a := 3;
    a := 1;

    while a >= 0 DO
        BEGIN
            proc1(a, b * 2);
            a := a - 1;
        END;
END.
